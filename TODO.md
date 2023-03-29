# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    TODO.md                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llion <llion@student.42mulhouse.fr >       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/24 16:04:33 by llion             #+#    #+#              #
#    Updated: 2023/03/29 12:09:07 by llion            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# A faire


# Problemes

	- Gerer le pipe a la fin d'un input
	- Implementer le "command not found"
	- gerer les permissions
	-

# shell break

	- double quotes donne un path ==> valeur d'erreur a revoir EXEC FORMAT ERROR AU LIEU DE COMMAND NOT FOUND
	L export toto=10 -> segfault quand creation->unset->export
	L une variable declaree puis initialisee est cree 2 fois
	L unset bug en gros (il y a un -1 ligne dans le calcul)
	L env n'affiche pas une variable non initialiseei (pas cense)
	L export ne peut pas commencer par des quotes ou par des nombres seuls les ca alphanum et _ peuvent aller dans export
	A pb echo "toto""$USER" ou echo "toto"+"$USER" ou echo '"toto"' "$USER"''
	A echo $USER$USE pb de taille
	L mieux gerer les -n
	A chevron vers la droite il faut une erreur (command not found)
	A >> ok segfault ---  | segfault  ---- << segfault
	A il faut un heredoc pour echo |
	A il faut un heredoc pour echo ok > ok > toto < ok << ok
	L on peut enlever le ^c dans ctrl+c - >var env de readline
	A ambigous redirect : export out="file1 file2" echo hello > $out
	A sortie de cat: rapelle 2 fois minishell ==> OK
	L \ doit quitter en mode bloque
	L il faut mettre un parametre a exit
	L exit sdkfjsdlf sdf doit renvoyer une erreur

