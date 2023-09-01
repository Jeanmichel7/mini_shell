# Minishell - 42 School Project

## 📋 Résumé

Minishell est un projet visant à créer un shell minimaliste. Il s'agit d'une réplique simplifiée du shell bash, avec une prise en charge des fonctionnalités de base comme l'exécution de commandes, la gestion des variables d'environnement, et la manipulation de l'entrée/sortie.

## 💻 Technologies Utilisées

- C
- Libft (Bibliothèque personnelle)

## 📦 Installation

```bash
git clone https://github.com/Jeanmichel7/minishell.git
cd minishell
make
```

## 📜 Règles du Projet

- Écrit en C conformément à la Norme 42.
- Pas de fuites mémoire.
- Utilisation du Makefile avec les règles standard (\$(NAME), all, clean, fclean, re).
- Libft autorisée.

## 🛠️ Utilisation

1. Lancez `./minishell` dans le terminal.
2. Un prompt s'affiche pour entrer les commandes.
3. Pour quitter le shell, utilisez `ctrl-D`.

### Fonctionnalités

- Affichage de prompt
- Gestion de l'historique des commandes
- Recherche et exécution du bon exécutable (basé sur la variable PATH ou un chemin relatif ou absolu)
- Gestion des guillemets simples et doubles
- Redirections (`<`, `>`, `<<`, `>>`)
- Pipes (`|`)
- Gestion des variables d'environnement
- Gestion des signaux `ctrl-C`, `ctrl-D` et `ctrl-\`
- Commandes built-in comme -`echo`,
  - `cd`,
  - `pwd`,
  - `export`,
  - `unset`,
  - `env`,
  - `exit`.
