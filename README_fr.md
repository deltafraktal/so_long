*Ce projet a été créé dans le cadre du cursus 42 par dgeara.*

# PUSH_SWAP

## Description

**push_swap** est un projet d'algorithmie de tri du cursus 42.

Tu reçois une liste d'entiers, et ton objectif est de les trier par ordre croissant en utilisant uniquement deux piles (`a` et `b`) et un ensemble limité d'opérations prédéfinies. Le défi : y arriver en **le moins de mouvements possible**.

### Opérations disponibles

| Opération | Description |
|-----------|-------------|
| `sa` / `sb` | Échange les 2 premiers éléments de la pile a / b |
| `ss` | `sa` + `sb` en même temps |
| `pa` / `pb` | Pousse le sommet de b sur a / le sommet de a sur b |
| `ra` / `rb` | Rotation vers le haut — le premier élément devient le dernier |
| `rr` | `ra` + `rb` en même temps |
| `rra` / `rrb` | Rotation inverse — le dernier élément devient le premier |
| `rrr` | `rra` + `rrb` en même temps |

### Stratégie de tri

- **2–3 éléments** → logique optimale codée en dur
- **4–5 éléments** → on pousse les plus petits sur b, on trie les 3 restants dans a, on remet
- **plus de 5 éléments** → **tri par base (radix sort)** sur des index normalisés (les valeurs sont remplacées par leur rang 0, 1, 2... puis triées bit par bit)

---

## Instructions

### Compilation

```bash
make
```

Produit le binaire `push_swap`.

```bash
make clean   # supprime les fichiers objets
make fclean  # supprime les fichiers objets + le binaire
make re      # fclean + make
```

### Utilisation

```bash
./push_swap 4 67 3 87 23
```

Le programme affiche la liste des opérations sur stdout, une par ligne. Si la liste est déjà triée, il n'affiche rien.

Tu peux aussi passer tous les nombres en une seule chaîne entre guillemets :

```bash
./push_swap "4 67 3 87 23"
```

### Gestion des erreurs

Le programme affiche `Error` sur stderr et quitte dans ces cas :
- Argument non entier
- Nombre hors de la plage INT
- Doublons

---

## Tests

### Vérifier les fuites mémoire

```bash
valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./push_swap 4 67 3 87 23
```

### Entrée aléatoire petite (5 nombres)

```bash
ARG=$(shuf -i 1-100 -n 5 | tr '\n' ' '); echo $ARG; ./push_swap $ARG
```

### Entrée aléatoire grande (500 nombres) avec comptage des opérations

```bash
ARG=$(shuf -i 0-10000 -n 500 | awk '{print $1 - 5000}' | tr '\n' ' '); echo $ARG; ./push_swap $ARG | wc -l
```

---

## Choix techniques

### Radix sort (grandes entrées)

J'ai choisi le radix sort parce que c'est un algorithme bien connu qui s'applique dans de nombreux contextes réels — pas seulement ce projet. Je voulais aussi travailler avec les bits (`>>`, masquage de bits), ce qui était une bonne occasion d'apprendre. Ce n'est pas la meilleure option pour minimiser le nombre d'opérations, mais c'est propre, structuré, et ça répond aux critères de notation.

### Quicksort (petites entrées)

Pour les petites piles j'ai utilisé une approche inspirée du quicksort. C'est plus rapide que le tri à bulles et suffisamment simple à comprendre. Un bon équilibre entre efficacité et simplicité.

---

## Ressources

### Algorithmes de tri
- [Radix sort — Wikipédia](https://en.wikipedia.org/wiki/Radix_sort)
- [Radix sort — GeeksForGeeks](https://www.geeksforgeeks.org/radix-sort/)
- [Quicksort — GeeksForGeeks](https://www.geeksforgeeks.org/quick-sort/)
- [Michael Sambol - Quick sort en 4 minutes](https://www.youtube.com/watch?v=Hoixgm4-P4M)
- [Opérateurs bitwise en C — W3Schools](https://www.w3schools.com/c/c_bitwise_operators.php)

### push_swap spécifique
- [Tutoriel push_swap par Léa Gris (Medium)](https://medium.com/nerd-for-tech/push-swap-tutorial-fa746e6aba1e)
- [Explication push_swap par Jamie Dawson (Medium)](https://medium.com/@jamierobertdawson/push-swap-the-least-amount-of-moves-with-two-stacks-d1e76a71789a)
- [Visualiseur push_swap](https://push-swap42-visualizer.vercel.app/)
- [Guide 42 push_swap](https://42-cursus.gitbook.io/guide/2-rank-02/push_swap/building-the-thing)

### Débogage
- [Documentation Valgrind](https://valgrind.org/docs/manual/mc-manual.html)
- [Démarrage rapide Valgrind](https://valgrind.org/docs/manual/quick-start.html)

### Utilisation de l'IA

Claude (Anthropic) a été utilisé pendant ce projet pour :

- **Débogage** — interpréter les sorties Valgrind, comprendre les appels `free()` invalides
- **Concepts** — clarifier la gestion mémoire en C (quand libérer, ce qui fuit et pourquoi, les doubles free, le comportement indéfini)
- **Compréhension d'algorithme** — fonctionnement des opérateurs de décalage binaire (`>>`)