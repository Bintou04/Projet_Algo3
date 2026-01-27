📄 README.md — PROJET ALGO 3

Gestion des supports de cours en langage C

⸻

📌 Description du projet

Ce projet a pour objectif de gérer des supports de cours (PDF, PPT, etc.) en utilisant les structures de données vues en Algorithme 3 :
	•	Liste chaînée
	•	Pile (stack)
	•	File (queue)

Chaque structure est utilisée dans un contexte réel :
	•	la liste pour stocker les supports
	•	la pile pour l’historique
	•	la file pour les notifications

⸻

🧱 Structure du projet

Projet_Algo3/
│
├── include/              # Fichiers d'en-tête (.h)
│   ├── support.h
│   ├── liste.h
│   ├── pile.h
│   └── file.h
│
├── src/                  # Fichiers source (.c)
│   ├── support.c
│   ├── liste.c
│   ├── pile.c
│   ├── file.c
│   └── main.c
│
├── docs/                 # Documents du projet
│   ├── rapport.pdf
│   └── presentation.pptx
│
└── README.md


⸻

🧠 Structures de données utilisées

🔹 Liste chaînée

Utilisée pour stocker les supports de cours de manière dynamique.

🔹 Pile (LIFO)

Utilisée pour conserver l’historique des supports ajoutés.

🔹 File (FIFO)

Utilisée pour gérer les notifications dans l’ordre d’arrivée.

⸻

⚙️ Compilation et exécution

📌 Compilation

Depuis le dossier racine du projet, exécuter la commande suivante :

gcc src/main.c src/liste.c src/pile.c src/file.c -Iinclude -o test_algo

▶️ Exécution

./test_algo


⸻

📤 Exemple d’affichage

==============================
       LISTE DES SUPPORTS
==============================

ID          : 1
Titre       : Algorithmique
Module      : Informatique
--------------------------------
ID          : 2
Titre       : Langage C
Module      : Programmation
--------------------------------

==============================
          HISTORIQUE
==============================

1) Langage C
2) Algorithmique

==============================
        NOTIFICATIONS
==============================

1) Support Algorithmique ajouté
2) Support Langage C ajouté


⸻

👨‍💻 Répartition du travail
	•	Aliou : Gestion de la liste chaînée
	•	Fatou Bintou : Gestion de la pile (historique)
	•	Couro : Gestion de la file (notifications) et intégration

⸻

🏁 Conclusion

Ce projet permet d’appliquer les concepts théoriques des structures de données dans un projet concret et bien structuré en langage C.

⸻

✅ COMMENT L’AJOUTER RAPIDEMENT

Dans ton terminal (à la racine du projet) :

touch README.md

>>>>>>> 446b10ea85391791abb2ff782bca0e416e318948
