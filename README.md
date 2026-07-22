# Smart-Backpack

## Objectif

Le Smart-Backpack est un sac à dos intelligent conçu pour améliorer la sécurité, protéger les objets de valeur et faciliter la gestion du contenu du sac. Il permet à l'utilisateur de surveiller son sac en temps réel grâce à différents capteurs et modules électroniques.

## Fonctionnalités

### 1. Alarme antivol

Le sac est équipé d'un capteur d'ouverture, d'un système d'authentification et d'un buzzer. Avant d'ouvrir le sac, l'utilisateur doit s'authentifier. Si une personne tente d'ouvrir le sac sans autorisation, le buzzer se déclenche immédiatement et une notification est envoyée au propriétaire. Cette fonctionnalité permet de protéger le contenu du sac contre les accès non autorisés.

### 2. Détecteur d'humidité

Un capteur d'humidité est installé à l'intérieur du sac afin de détecter toute infiltration d'eau. Lorsqu'une présence d'humidité est détectée, le système envoie une notification au propriétaire pour lui permettre de protéger rapidement les objets sensibles, comme un ordinateur portable ou des documents.

### 3. Système de vérification du contenu et détection d'oubli

Une caméra ESP32-CAM vérifie le contenu du sac en capturant une image des objets présents. Le système identifie les objets détectés, les compare avec une liste prédéfinie et informe l'utilisateur des objets présents, retirés ou oubliés. Si un objet important est absent, une notification est envoyée afin d'éviter tout oubli.
