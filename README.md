# GTKmm Domino Game

Un projet C++ interactif pour apprendre et maîtriser le langage C++ en développant un jeu de dominos avec GTKmm et Cairo.

## Présentation

Ce projet est une implémentation d'un jeu de dominos interactif écrit en C++ en utilisant la librairie **GTKmm** (un wrapper C++ pour GTK) et **Cairo** pour le rendu graphique. Le jeu propose une interface intuitive et illustre des concepts clés de la programmation en C++ tels que :

- La **modularité**.
- L'utilisation des **vecteurs** pour la gestion dynamique des données.
- L'**encapsulation** et le **polymorphisme** pour concevoir un système extensible.
- Les **templates** et l'**injection de dépendance** pour un code générique.
- Une **grille magnétique** et des **règles de jeu intégrées**.

## Fonctionnalités

### Jeu de Dominos
- Dessin et manipulation des dominos en utilisant Cairo et GTKmm.
- Gestion des interactions avec la souris : cliquer, déplacer et déposer.

### Encapsulation et Polymorphisme
- Système extensible basé sur des classes polymorphiques permettant l'ajout d'éléments de jeu.

### Sabot de Dominos
- Gestion des pièces via des templates, permettant une organisation flexible des dominos dans un sabot.

### Grille Magnétique
- Placement automatique des dominos sur une grille avec alignement précis.

### Règles du Jeu
- Implémentation des règles classiques du jeu de dominos pour valider les mouvements.

## Technologies Utilisées

- **Langage :** C++
- **GUI :** GTKmm
- **Graphisme :** Cairo
- **Gestion des données :** STL (Standard Template Library)

## Installation

### Prérequis

- **GTKmm** (version minimale recommandée : `3.24`)
- **Cairo** (pour le dessin vectoriel)
- Un compilateur C++ compatible (`g++` avec prise en charge de C++17 ou plus).

### Étapes d'installation

1. Clonez le dépôt GitHub :
   ```bash
   git clone git@github.com:BOUBACAR-GOUNOU/gtkmm-domino-game.git
   cd gtkmm-domino-game
   ```

2. Installez les dépendances nécessaires :
   ```bash
   sudo apt-get install libgtkmm-3.0-dev libcairomm-1.0-dev
   ```

3. Compilez le projet :
   ```bash
   make all
   ```

4. Lancez l'application :
   ```bash
   ./domino
   ```

## Structure du Projet

```plaintext
├── src/
│   ├── app.cpp                # Point d'entrée du programme
│   ├── main_window.hpp/.cpp   # Classe principale pour l'interface
│   ├── board.hpp/.cpp         # Gestion des dominos et de la grille
│   ├── domino.hpp/.cpp        # Classe Domino
│   ├── piece.hpp/.cpp         # Classe polymorphe pour les pièces graphiques
│   ├── deck.hpp/.cpp          # Gestion de la pioche
│   ├── utils.hpp/tpp          # Templates et utilitaires divers
│   └── my_data.hpp/.cpp       # Gestion des données partagées
├── resources/                 # Fichiers supplémentaires (images, thèmes, etc.)
├── README.md                  # Documentation du projet
└── Makefile                   # Automatisation de la compilation
```

## Usage

- **Déplacer un domino :** Cliquez et glissez pour positionner un domino.
- **Valider un mouvement :** Les règles de placement sont automatiquement vérifiées.
- **Système extensible :** Ajoutez facilement de nouvelles fonctionnalités ou de nouvelles règles.

## Auteur

- Projet réalisé pat **Boubacar Gounou**




## Remerciements

- Ce projet a été réalisé dans le cadre d'un travail pratique visant à approfondir les compétences en C++ à l'**Université d'Aix-Marseille** (AMU).  
- Le plan de ce TP a été proposé par **Édouard Thiel**, enseignant à l'Université d'Aix-Marseille.  

