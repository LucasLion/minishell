# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    TODO.md                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llion <llion@student.42mulhouse.fr >       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/24 16:04:33 by llion             #+#    #+#              #
#    Updated: 2023/03/29 17:25:00 by llion            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# A faire


# Problemes

	- Gerer le pipe a la fin d'un input
	- Implementer le "command not found"
	- gerer les permissions

# shell break

	- [OK] >> ok segfault ---  | segfault  ---- << segfault - antoine
	- [OK] il faut un heredoc pour echo ok > ok > toto < ok << ok - antoine
	- [OK] pb echo "toto""$USER" ou echo "toto"+"$USER" ou echo '"toto"' "$USER"'' - antoine
	- [OK] echo $USER$USE pb de taille - antoine
	-      chevron vers la droite il faut une erreur (command not found) - antoine
	-      il faut un heredoc pour echo | - antoine
	- [OK] ambigous redirect : export out="file1 file2" echo hello > $out - antoine

	- [OK] double quotes donne un path - on verra
	- [OK] export toto=10 -> segfault quand creation->unset->export - lucas
	- [OK] une variable declaree puis initialisee est cree 2 fois - lucas
	- [OK] unset bug en gros (il y a un -1 ligne dans le calcul) - lucas
	- [OK] env n'affiche pas une variable non initialisee (pas cense) - lucas
	- [OK] export ne peut pas commencer par des quotes ou par des nombres seuls les ca alphanum et _ peuvent aller dans export - lucas
	- [OK] sortie de cat: rapelle 2 fois minishell - antoine
	- [OK] mieux gerer les -n - lucas
	-      on peut enlever le ^c dans ctrl+c - >var env de readline - lucas
	-      \ doit quitter en mode bloque - lucas
	-      il faut mettre un parametre a exit - lucas
	-      exit sdkfjsdlf sdf doit renvoyer une erreur - lucas
