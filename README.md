# Smart-Backpack
Objectif: Transformer un sac à dos classique en un sac qui améliore la sécurité, le confort et la gestion des objets
Ce sac à dos possède plusieurs fonctionnalités clés:
1- Alarme antivol:
Le sac sera équipé d'un capteur d'ouverture, d'un système authentification et d'un buzzer qui déclenche un alarme dans le cas où quelqu'un ouvre le sac
sans s'être authentifié.
2- Detecteur d'humidité
Un capteur d'humidité à l'interieur du sac vérifie si de l'eau a penetré le sac, envoyant un signal/message vers le propriétaire
3- Systeme de verification du contenu + detection d'oubli
Un ESP32-cam vérifie le contenu du sac et traque les objets du sac, il notifie l'utilisateur des objets dans le sac et des objets sortis du sac. Il envoi un signal
au propriétaire au cas où le propriétaire a oublié quelque chose.
