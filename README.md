# Motor_Feedback_control
Controle d'un moteur avec un microcontroleur STM32 
ENSEA - TP MSC -Système d'acquisition et de commande

    Rédaction : Laodjassonod Londou

Présentation du TP

Objectifs

   A partir d'un hacheur complet et d'une carte Nucleo-STM32G474RE, nous allons :

    1. Réaliser un shell pour commander le hacheur,
    2. Réaliser la commande des 4 transistors du hacheur en commande complémentaire décalée,
    3. Faire l'acquisition des différents capteurs pour mesurer la vitesse et les différents courants,
    4. Réaliser l'asservissement en temps réel du moteur.
    
    Projet open-source (disponible sur github),
    
Cahier des charges

    La liaison UART devra avoir comme fonctionnalité :
    La présence d'un écho pour tous les caractères pour voir ce que l'on envoie.
    Lorsque le caractère "ENTER" est détecté (voir sa valeur dans la table ASCII), traiter la chaine de caractères en la comparant aux commandes connues, pour le moment nous resterons à un nombre limitée de commandes :
        help : qui affiche toutes les commandes disponibles,
        pinout : qui affiche toutes les broches connectées et leur fonction,
        start : qui allume l'étage de puissance du moteur (pour l'instant nous ne ferons qu'afficher un message de "Power ON" dans la console),
        stop : qui éteind l'étage de puissance du moteur (pour l'instant nous ne ferons qu'afficher un message de "Power OFF" dans la console),
        Speed xxx : qui permet d'e commander le moteur à la vitesse "xxx" tr/min,
        Mesure_Courant : qui permet de mesurer le courant du moteur et l'aficher dans le shell,
        Mesure_Vitesse : qui permet de mesurer la vitesse du moteur et l'aficher dans le shell,
        toute autre commande renverra un message dans la console "Command not found".
    Vider la chaine de caractère et mettez l'index pointant vers le prochain caractère à remplir à 0,
    Génération des PWM,
    Mesure de courants (hall) dans les 3 phases + entrée,
    Mesure de tension dans les 3 phases + entrée,
    Asservissement du moteur en temps réel,
    Aquisition par la methode pooling,
    Aquisition avec le DMA,
    Mise en place d'une chaine d'aquisition timer/ADC/DMA,
    

    
Composants
    
    Carte Nucleo-STM32G474RE,
    Hacheur 4 cadrants,
    Moteur à courant continue 48V-12.2A-3000tr/min,
    Commande de mise sous tension,
    Pilotage par liaison UART over USB,
    Capteurs à effet hall,
    Encodeurs,

    
Input / Output labels
Communication avec le micro-controleur présent sur la carte-mère

    UART_TX_STM32 : UART vers le micro-controleur
    UART_RX_STM32 : UART depuis le micro-controleur
    NRST_STM32 : signal pour faire un reset du micro-controleur de la carte

Communication avec le module encodeur

    Enc_A : entrée du signal A de l'encodeur
    Enc_B : entrée du signal B de l'encodeur
    Enc_Z : entrée du signal Z de l'encodeur

Mesure de tension

    Bus_V : mesure de la tension du bus d'alimentation
    U_Vph : mesure de la tension de la sortie U (entre les 2 transistors)
    V_Vph : mesure de la tension de la sortie V (entre les 2 transistors)
   
Mesure de courant

    Bus_Imes : mesure de courant du bus d'alimentation
    U_Imes
    V_Imes
   
Génération de PWM

    U_PWM_H
    U_PWM_L
    V_PWM_H
    V_PWM_L
   
