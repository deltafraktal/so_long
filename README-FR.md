*This project has been created as part of the 42 curriculum by dgeara.*

# SO_LONG

## Description

so_long est un petit projet de jeu 2D du cursus 42, développé entièrement en C avec **MiniLibX** — une bibliothèque graphique minimaliste basée sur X11.

Tu incarnes un personnage sur une carte en tuiles. L'objectif est simple : **ramasser tous les collectibles, puis atteindre la sortie** — en le moins de déplacements possible. Le jeu affiche les sprites, gère les entrées clavier, comptabilise les mouvements, et valide la carte avant même que la partie commence.

Le vrai défi se passe avant le lancement : implémenter un algorithme de **flood fill** pour vérifier que tous les collectibles et la sortie sont bien accessibles depuis la position de départ du joueur.

### Fonctionnalités

**Obligatoire**
- Carte en tuiles rendue avec MiniLibX (murs, sol, joueur, collectibles, sortie)
- Déplacement au clavier (W/A/S/D ou touches directionnelles) avec détection des murs
- Compteur de mouvements affiché dans le terminal à chaque déplacement
- Validation de la carte : forme rectangulaire, entourée de murs, exactement un joueur, une sortie, au moins un collectible
- Vérification d'accessibilité par flood fill — la carte doit être completable

**Bonus**
- Ennemis qui tuent le joueur au contact
- Sprites animés (boucle d'animation par images)
- Compteur de mouvements affiché directement à l'écran (pas uniquement dans le terminal)

---

## MiniLibX

MiniLibX est une bibliothèque graphique légère développée à 42, conçue pour donner aux étudiants un moyen simple d'ouvrir des fenêtres, dessiner des pixels, charger des images et gérer les événements clavier/souris — sans la complexité d'un framework graphique complet.

Elle repose sur **X11** (le système de fenêtrage utilisé sous Linux) et **AppKit** sous macOS. Sous le capot, elle encapsule juste ce qu'il faut de ces APIs pour afficher des pixels à l'écran et réagir aux entrées.

Voici ce qu'elle expose :

| Famille de fonctions | Ce qu'elle fait |
|---|---|
| `mlx_init` / `mlx_new_window` | Crée la connexion à l'affichage et ouvre une fenêtre |
| `mlx_xpm_file_to_image` | Charge un sprite XPM depuis le disque en mémoire |
| `mlx_put_image_to_window` | Dessine une image à une position (x, y) dans la fenêtre |
| `mlx_hook` | Enregistre un callback pour un événement donné (touche, fermeture...) |
| `mlx_loop` / `mlx_loop_hook` | Lance la boucle événementielle — garde la fenêtre active et appelle les hooks à chaque frame |

Le modèle mental clé : **MiniLibX est orientée événements**. Tu n'écris pas de `while(1)` toi-même — tu enregistres des hooks et c'est `mlx_loop` qui les appelle. Toute la logique du jeu vit à l'intérieur de ces hooks.

Pour trouver le keycode d'une touche spécifique, tu peux l'afficher temporairement :
```c
ft_printf("%d\n", keycode);
```
Puis appuyer sur la touche en jeu et lire la valeur dans le terminal.

---

## Instructions

### Compilation

```
make
```

Produit le binaire `so_long`.

```
make clean    # supprime les fichiers objets
make fclean   # supprime les fichiers objets + le binaire
make re       # fclean + make
```

Pour la version bonus :

```
make bonus
```

### Format de la carte

Les cartes sont des fichiers `.ber`. Les caractères valides sont :

| Caractère | Signification      |
|-----------|--------------------|
| `1`       | Mur                |
| `0`       | Sol vide           |
| `P`       | Position du joueur |
| `E`       | Sortie             |
| `C`       | Collectible        |
| `X`       | Ennemi             |

Exemple de carte :

```
1111111111
10C0000001
1000011101
1P0011E001
1111111111
```

Règles :
- Doit être rectangulaire
- Doit être entièrement entourée de murs (`1`)
- Exactement **un** `P` et **un** `E`
- Au moins **un** `C`
- Tous les collectibles et la sortie doivent être accessibles depuis `P`

### Utilisation

```
./so_long maps/map.ber
```

```
./so_long_bonus maps/map.ber
```

### Gestion des erreurs

Le programme affiche `Error` sur stderr et quitte dans les cas suivants :
- Le fichier de carte est manquant ou illisible
- La carte ne respecte pas le format requis
- La carte n'est pas completable (le flood fill échoue)

### Contrôles

| Touche     | Action                |
|------------|-----------------------|
| `W` / `↑` | Déplacer vers le haut |
| `S` / `↓` | Déplacer vers le bas  |
| `A` / `←` | Déplacer à gauche     |
| `D` / `→` | Déplacer à droite     |
| `ESC`      | Quitter               |

---

## Ressources

### MiniLibX
- [Débuter avec MiniLibX — Aurélien Brabant](https://aurelienbrabant.fr/blog/getting-started-with-the-minilibx)

### Algorithmes
- [Flood fill — Wikipédia](https://en.wikipedia.org/wiki/Flood_fill)
- [Flood fill — GeeksForGeeks](https://www.geeksforgeeks.org/problems/flood-fill-algorithm1856/1)

### Format XPM
- [X PixMap — Wikipédia](https://en.wikipedia.org/wiki/X_PixMap)

### Pour aller plus loin
- [Oscillateur (automate cellulaire) — Wikipédia](https://en.wikipedia.org/wiki/Oscillator_(cellular_automaton))
- [Référence des oscillateurs de Conway's Life](https://conwaylife.com/book/oscillators)

---

### Utilisation de l'IA

Claude (Anthropic) a été utilisé durant ce projet pour :

- **MiniLibX** — comprendre le fonctionnement de la boucle événementielle, comment enregistrer des hooks clavier, et comment pousser des images dans la fenêtre
- **Flood fill** — clarifier la logique de l'algorithme (récursif vs itératif), comprendre comment marquer les cases visitées sans corrompre la carte originale
- **Débogage** — interpréter les segfaults et erreurs mémoire, comprendre quand et pourquoi libérer de la mémoire dans un contexte graphique