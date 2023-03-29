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

	- double quotes donne un path
	- export toto=10 -> segfault quand creation->unset->export
	- une variable declaree puis initialisee est cree 2 fois
	- unset bug en gros (il y a un -1 ligne dans le calcul)
	- env n'affiche pas une variable non initialiseei (pas cense)
	- export ne peut pas commencer par des quotes ou par des nombres seuls les ca alphanum et _ peuvent aller dans export
	- pb echo "toto""$USER" ou echo "toto"+"$USER" ou echo '"toto"' "$USER"''
	- echo $USER$USE pb de taille
	- quand on enleve le path, cree un fichier ls puis commande ls -> on doit avoir command not found (checker les commandes avant)
	- mieux gerer les -n
	- meme nom qu'un executable dans le dossier courant ou pas
	- chevron vers la droite il faut une erreur (command not found)
	- >> ok segfault ---  | segfault  ---- << segfault
	- il faut un heredoc pour echo |
	- il faut un heredoc pour echo ok > ok > toto < ok << ok
	- on peut enlever le ^c dans ctrl+c - >var env de readline
	- ambigous redirect : export out="file1 file2" echo hello > $out
	- sortie de cat: rapelle 2 fois minishell
	- \ doit quitter en mode bloque
	- il faut mettre un parametre a exit
	- exit sdkfjsdlf sdf doit renvoyer une erreur
	-

