# Description de `libft`

`libft` est une bibliothèque en C que j'ai codée pour l'école 42. Elle contient des fonctions de base pour manipuler des chaînes de caractères, des tableaux, des listes chaînées, des nombres, etc.

Le but de cette bibliothèque est de fournir des fonctions personnalisées pour manipuler des données en C, sans avoir à réécrire du code de base chaque fois que cela est nécessaire. Elle peut être utilisée comme une alternative à certaines fonctions de la bibliothèque standard du langage C, ou pour ajouter des fonctionnalités supplémentaires.

## Utilisation

Pour utiliser la bibliothèque `libft`, il faut la compiler en utilisant la commande	`make` dans le terminal. Une fois compilée, elle peut être utilisée en incluant le fichier d'en-tête `libft.h` dans votre code C, comme suit :

``` C
#include "libft.h"

int main()
{
  char str[] = "Hello world";
  ft_putstr(str);
  return (0);
}
```

Le programme affiche ensuite le texte "Hello world" à l'écran. Il est important de noter que la bibliothèque `libft` contient de nombreuses fonctions utiles pour la manipulation de données en C, et qu'il est recommandé de consulter la documentation pour savoir quelle fonction utiliser dans quelle situation.

## Fonctionnement

La bibliothèque `libft` est divisée en plusieurs catégories, chacune contenant des fonctions pour manipuler des données spécifiques. Par exemple, la catégorie `ft_string` contient des fonctions pour manipuler des chaînes de caractères, tandis que la catégorie `ft_mem` contient des fonctions pour manipuler des blocs de mémoire.

Les fonctions de la bibliothèque `libft` sont conçues pour être modulaires et indépendantes les unes des autres. Elles ont été testées et optimisées pour être utilisées dans des applications en C de manière efficace et fiable.

## Conclusion

`libft` est une bibliothèque utile pour la manipulation de données en C. Elle peut être utilisée comme alternative à certaines fonctions de la bibliothèque standard du langage C, ou pour ajouter des fonctionnalités supplémentaires. La bibliothèque est disponible sur la plateforme GitHub de l'école 42 et peut être améliorée pour ajouter de nouvelles fonctions ou pour optimiser les fonctions existantes.

