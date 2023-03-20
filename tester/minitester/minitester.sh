#!/bin/bash

MODE=$1

# Couleurs pour l'affichage
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

MINISHELL="../minishell" # Remplacez ceci par le chemin de votre exécutable Minishell
COMMANDS_FILE="commands.txt"
LOG_FILE="test_log.txt"

# Variables pour compter les tests réussis et le nombre total de tests
success_count=0
total_count=0
current_test_type=""
test_results_by_type=""
failed_tests_details=""

if [ ! -f $MINISHELL ]; then
    echo "Minishell not found. Please set the correct path to your Minishell executable."
    exit 1
fi

rm -rf tmp
mkdir tmp

# Ajoutez un timestamp et un séparateur au début du fichier de logs
echo "Test run at $(date)" > $LOG_FILE
echo "-------------------------" >> $LOG_FILE

while read -r command; do
    if [[ $command == "#"* ]]; then
        # Détecte le type de test et stocke-le
        current_test_type=$command
        test_results_by_type+="\n$current_test_type"
    else
        echo "Testing command: $command" >> $LOG_FILE

		echo "$command" | $MINISHELL 2> >(grep -v "Minishell\$ " >&1) | grep -v "Minishell\$ " > .minishell_output.txt
		echo "$command" | bash > .bash_output.txt 2>&1

        # Écrire les résultats de Minishell et Bash dans le fichier de log
		echo "-------------------------------------------------">> $LOG_FILE
        echo "Minishell output:" >> $LOG_FILE
        cat .minishell_output.txt >> $LOG_FILE
		echo >> $LOG_FILE
        echo "Bash output:" >> $LOG_FILE
        cat .bash_output.txt >> $LOG_FILE
		echo "-------------------------------------------------">> $LOG_FILE

        total_count=$((total_count + 1))

        # Comparez les résultats et affichez les différences
        diff_output=$(diff <(grep -v "Minishell\$" .minishell_output.txt) <(grep -v "bash:" .bash_output.txt))

        if [ $? -eq 0 ] || [ -z "$diff_output" ]; then
            success_count=$((success_count + 1))
            test_results_by_type+="${GREEN}✓${NC}"
        else
            # Vérifiez si les deux sorties sont des erreurs
            minishell_error=$(grep "minishell: " .minishell_output.txt)
            bash_error=$(grep "bash: " .bash_output.txt)

            if [ -n "$minishell_error" ] && [ -n "$bash_error" ]; then
                success_count=$((success_count + 1))
                test_results_by_type+="${GREEN}✓${NC}"
            else
                test_results_by_type+="${RED}✗${NC}"
                failed_tests_details+="\n${RED}FAIL:${NC} $command\n$diff_output\n-------------------------"
            fi
        fi
    fi
done < $COMMANDS_FILE

# Nettoyez les fichiers temporaires
rm -f .minishell_output.txt
rm -f .bash_output.txt
rm -f test
rm -f test_output.txt
rm -rf tmp

# Affichez les symboles de réussite ou d'échec pour chaque test par type
echo -e "\nTest results by type:"
echo -e "$test_results_by_type"

# Affichez les détails des tests échoués
echo -e "\nFailed tests details:"
echo -e "$failed_tests_details"

# Affichage du résumé des tests
echo -e "\nTest summary:"
echo -e "$test_summary"
echo -e "\nTotal tests: $total_count"
echo -e "${GREEN}Successful tests: $success_count${NC}"
echo -e "${RED}Failed tests: $(($total_count - $success_count))${NC}"

# Mode Valgrind
if [ "$MODE" == "valgrind" ]; then
    echo -e "\nRunning Valgrind on Minishell for each command..."
    valgrind_log_file="valgrind_log.txt"
    rm -f $valgrind_log_file
    touch $valgrind_log_file

    while read -r command; do
        # Ignore les lignes commentées
        if [[ "$command" =~ ^# ]]; then
            continue
        fi

        echo -e "\nRunning command: $command" >> $valgrind_log_file
        valgrind --leak-check=full --show-leak-kinds=definite --track-origins=yes --verbose --log-file=valgrind_output.txt $MINISHELL -c "$command"
        cat valgrind_output.txt >> $valgrind_log_file
    done < $COMMANDS_FILE

    echo -e "\nValgrind results saved in $valgrind_log_file"
fi

# Nettoyez les fichiers temporaires
rm -f .minishell_output.txt
rm -f .bash_output.txt
rm -f test
rm -f test_output.txt
rm -rf tmp
rm -f test_file.txt

