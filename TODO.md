# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    TODO.md                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llion <llion@student.42mulhouse.fr >       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/24 16:04:33 by llion             #+#    #+#              #
#    Updated: 2023/03/31 10:01:16 by llion            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# A faire

# shell break

[  ]	ERROR_LOG: exit 60 > donne le message que ce n est pas numerique et ne resort pas le bon error code ($?) 

[ok]	cat > lors du ctrl+C, il affiche 2 fois le prompt ==> ^+C s'affiche desormais a voir si on peut le changer
[OK]       et le retour d erreur est 0 au lieu de 130  ==> a faire

[ok]	ls <invalide> > resort Minishell: ls: Operation not permitted  

[ok]	Probleme de conversion de variables d env > Il devrait ne prendre que des alphanumeriques et underscores (a-z A-Z 0-9 _ et ne commence pas par 0-9)
==> TEST : echo "[$USER]"+'[$USER]' 

[OK]	unset 
[  ]    cd sans argument plus de segfault mais il faut revenir a la home (meme chose pour cd suivi de ligne avec des espaces ou tabulations)
[  ]    cd ~ : not allocated    

[OK]	Tant que le PATH est unset > plus aucune commande ne fonctionne sauf builtin (PS: ceux qui fonctionne)
