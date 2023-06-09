# RAPPORT HOVERCRAFT

## Introduction

Un hovercraft (en français aéroglisseur) est un véhicule amphibie à portance aérostatique et à propulsion aérienne, qui en général possède une ou plusieurs hélices aériennes. La portance est assurée par un coussin d'air sous faible pression relative, entretenu par une soufflante à l'intérieur d'une enceinte dont les parois latérales, appelées jupes, sont suffisamment déformables pour suivre au plus près le relief de la surface survolée et ainsi réduire les fuites. Les aéroglisseurs se déplacent le plus souvent sur la mer, mais aussi sur toute surface terrestre ne présentant pas d'obstacles importants.

Nous avons ainsi pour but d'en réaliser un avec le matériel proposé.


## Analyse technique du problème posé

|Objectifs à remplir|Contraintes|
|-------------------|-----------|
|Avancer, décoller|Pas de contrôle à distance (autonome)|
|Avancer "droit"|Pas de contrôle à distance (autonome)|
|Avancer 10m|Pas de contrôle à distance (autonome)|
|Avancer 10m le plus rapidement possible|Pas de contrôle à distance (autonome)|


Nous avons utilisé les composants suivants :
* 2 régulateurs de tension BUCK MAX5033 qui ont un fort rendement (entre 80 et 90%)
* Une centrale inertielle MPU6050
* Un microprocesseur STM32 qui communique en I2C avec la centrale inertielle
* 2 ESC qui communique en PWM avec le microprocesseur, les ESC contrôlent 2 moteurs
* Une batterie qui délivre une tension de 11,1 V
* Une sonde de programmation
* Un servo-moteur XL320 qui communique en UART avec le microprocesseur

Nous employons des régulateurs de tension afin d'adapter les niveaux de tension pour les composants utilisés. Le microprocesseur nécessite une tension de 3,3 V, tandis que la sonde de programmation requiert 7,4 V. Cependant, la batterie fournit une tension de 11,1 V.
Le microprocesseur lui sert à contrôler les ESC et donc les moteurs pour qu'on puisse accomplir les objectifs fixés. Le microprocesseur est complété par l'ajout du servo-moteur pour l'asservissement.
On a alors ce [diagramme](https://github.com/0reoAurelien/projet-hovercraft/blob/main/Hardware/DIAGRAMME_VF.png) qui résume cela.

L'I2C et l'UART sont des protocoles de communication. L'UART permet l'échange de données entre un émetteur et un récepeteur dans les 2 sens et l'I2C permet à un système maître de controler des systèmes esclaves.

## Méthodologie

Pour mener à bien ce projet, nous avons eu à utiliser plusieurs logiciels : 
* **Github** : logiciel qui nous permet de rassembler toute nos travaux dans un seul endroit
* **Draw.io** : logiciel qui nous permet de tracer des graphes
* **Redmine** : logiciel qui nous permet de nous créer un emploi du temps (diagramme de Gantt) et nous a permis de nous répartir les différentes taches
* **Kicad** : logiciel qui nous permet de faire nos schematic ainsi que nos PCB
* **STM32CubeIDE** : logiciel qui nous permet de programmer notre microprocesseur

Nous avons décidé de nous séparer en 2 groupes, un qui s'occupe de la partie hardware (conception de PCB et soudure) et l'autre qui s'occupe de la partie software.

## Problèmes rencontrés

Lorsque nous avons commencé à souder l'un de nos PCB, il y avait un problème de court-circuit entre la masse et du 3V3. Ce problème a pu être révélé grâce à la caméra thermique. Nous avons analysé notre PCB et déterminé qu'il s'agissait d'un défaut à la fabrication de la carte. Nous avons pu corriger le problème en coupant une zone du PCB pour retirer le court-circuit. Cependant nous avions aussi oublié le connecteur qui alimentait le système en 3V3 donc nous avons donc dû refaire une V2 de notre deuxième PCB.

Par mégarde, nous avons arraché un connecteur ce qui a arraché une piste cuivre de notre PCB. Nous avons réparé le problème en repositionnant la connecteur et en soudant un fil à la place du circuit arraché.
Lors de la réalisation du 2ème PCB concernant les régulateurs, nous avons rencontré des problèmes lors de la conception (notamment l'optimisation de la taille et certaines empreintes) et lors de la soudure de certains composants.

Durant l'étape de programmation, nous nous sommes heurtés à de nombreuses difficultés notamment sur les différents pins de sortie.
Nous avons divisé notre code en plusieurs parties. Le programme de sélection du mode se trouve dans le main.c et permet de sélectionner l'un des 4 objectifs de notre hovercraft, puis de l'exécuter. Pour réalier cela, notre main.c faisait appel à plusieurs autres fichiers que nous avons réalisés dont le fichier functions.c chargé de gérer l'affichage du mode avec notre LED_USR, ainsi que de la lecture du bouton de sélection. Cette partie a pu être réalisée rapidement sans rencontrer de grandes difficultés. Les autres fichiers appelés devaient servir à commander les moteurs, gérer la centrale inertielle, et utiliser le servomoteur pour contrôler la trajectoire de l'aéroglisseur, mais nous avons fait face à plusieurs difficultés.
Le codage des pins en PWM, USART et en I2C n'ayant pas été traitées en TP de microprocesseurs, nous avons eu du mal à écrire les programmes.

En particulier, nous ne sommes pas parvenus à programmer les drivers des moteurs, qui nécessitent la génération de signaux PWM. Tester le code d'abord sur le PCB réalisé n'était pas une très bonne idée, car cela gênait l'identification de la cause lorsque le résultat n'est pas celui attendu. Nous pensons que le PCB était incapable de générer un signal PWM car, malgré une initialisation valide des pins en PWM, CubeMX indiquait toujours un conflit entre les pins associés aux PWM et nos connexions en I2C et GPIO. De plus, l'activation des moteurs nécessitait un processus précis (disponible sur la page 6 de la datasheet PICHLER_XQ_ESC.pdf), que l'on devait suivre en se basant uniquement sur des sons émis par les moteurs. Ce processus est celui qui doit permettre de fixer les valeurs hautes et basses de vitesse des moteurs. Comme nous manquions de temps et nous rencontrions des difficultés ici, nous avons du renoncer aux autres fonctionnalités liées à la centrale inertielle ou au servomoteur, afin d'augmenter l'effectif et concentrer nos efforts pour faire fonctionner les moteurs de l'aéroglisseur. Nous avions tout de même réalisé des recherches sur leur fonctionnement et trouvé des informations utiles concernant leur utilisation et leur programmation (la source (4) aurait pu servir).

Bien que nous avons obtenu des résultats sur l'alimentation pour la régulation de tension lorsque nous avons branché le PCB sur la batterie nous avons fait cramé certains composants (un condensateur, puis un régulateur après avoir remplacé le condensateur) mais nous ne savons pas pourquoi.
> Note : Tous nos [schémas Kicad](https://github.com/0reoAurelien/projet-hovercraft/tree/main/Hardware) et nos [codes](https://github.com/0reoAurelien/projet-hovercraft/tree/main/Software) sont disponibles sur notre github
## Résultats

Nous avons pu tester notre PCB à l'aide de différents programmes. Ainsi, le microprocesseur fonctionne correctement et fait très bien tourner la fonction de "menu de sélection" que nous avons écrite. Cette fonction atteste aussi du bon fonctionnement des communications GPIO car la carte est en mesure d'éclairer les LEDs et elle détecte nos appuis court et long sur le bouton de sélection.
Avec la carte Nucleo STM32H7A3Zi-Q utilisée en TP, nous avons réussi à émettre un signal PWM pour éclairer une led avec l'intensité souhaitée. 
Sur cette même carte, nous avons généré un signal PWM sur des pins de sortie et nous l'avons observé à l'oscilloscope. Nous avons ainsi testé 3 pins de la carte. L'un ne générait pas de signal, ceci peut être causé par une erreur de configuration sur CubeMX ou l'occupation du pin par une autre fonctionnalité; sur les deux autres, la génération de signal PWM était valide. En revanche, lors de la première observation, le signal affiché sur l'oscilloscope était déformé (ce défaut a disparu la séance suivante). Ceci peut être causé par un faux contact, ou un défaut des fils que nous avons utilisés pour le premier essai.

Photo du montage utilisé: [My image](PWMsurH7A3.jpg)

Nous avons ensuite testé ce signal sur le moteur (avec le régulateur XQ et une batterie 14V), cependant par mauvais choix de fréquence de signal PWM et/ou de consignes de démarrage dans le code, nous n'avons réussi qu'à entendre les bips provenant du moteur testé.

Nous avons réussi à programmer le driver des LEDs qui s'allument et suivent un pattern lorsque nous appuyons sur un bouton. Ce programme a pu être observé avec le PCB réalisé.

Concernant le PCB avec les régulateur de tension, on arrive à avoir la tension souhaitée en sortie avec une alimentation branchée sur le réseau. Cependant, lors des essais sur batteries, nous avons rencontrés des problèmes comme décrit dans la partie précédente.

Plus d'informations sur la partie Software sont disponibles dans le fichier Readme_Software.


## Développement durable

### Quelle réflexion avez-vous mené au cours de ce projet autour de la réutilisation d'éléments matériels pour la création de votre projet ?

Durant notre projet, nous avons beaucoup réfléchi à la réutilisation d'éléments matériels pour la création de notre Hovercraft. En effet, notre projet emploie des moteurs qui pourraient être réutilisés pour d'autres projets, et son support est fait à base de plastique recyclable (imprimé en 3D). Les hélices en plastique peuvent aussi être réutilisées pour concevoir des drones ou autres véhicules.

### Votre projet limite-t-il les quantités de pollutions ou de déchets rejetés dans les écosystèmes ?

Comme dit précédemment, notre projet est un Hovercraft, constitué d'un support imprimé 3D en plastique recyclable ainsi que de moteurs alimentés en électricité. Les batteries qui alimentent les moteurs sont rechargées via le réseau d'électricité de l'ENSEA. De plus, notre hovercraft ne consomme pas beaucoup d'électricité et ne rejette rien dans l'atmosphère ou dans les écosystèmes. Enfin, nous avons attaché une certaine importance à limiter le nombre de composants dans nos PCB. Nous souhaitions initialement utiliser deux boutons pour sélectionner les modes, puis exécuter le programme sélectionné. Au lieu de celà, nous n'avons utilisé qu'un bouton en distinguant les appuis courts et les appuis longs. De même, nous souhaitions utiliser 4 LEDs pour indiquer la fonction actuellement sélectionné. Nous avons réduit notre quantité de déchet en utilisant une seule LED que l'on fait clignoter n fois. Cela en fait un projet à empreinte carbone faible, et dont le nombre de déchets sera limité après sa fin de vie.

## Conclusion

Ce projet de Hovercraft a été une expérience enrichissante qui nous a permis d'explorer les aspects techniques de la création d'un véhicule autonome. Nous avons pris en compte des contraintes environnementales en minimisant notre utilisations de composants pour les PCB, en utilisant un plastique recyclable pour la coque du hovercraft, et nous avons pensé à la réutilisation future de certains composants tels que les moteurs.

Durant ce projet, nous avons été mis en conditions réélles, avec des objectifs à atteindre comme pour convenir à un cahier des charges. Nous avions un temps limité et nous devions produire un hovercraft capable de répondre à des exigences. Bien que nous ne soyons pas parvenus à réaliser un hovercraft fonctionnel, nous avons été en mesure de produire des PCB exploitables et de fournir un programme organisé afin de contrôler le véhicule. Cela a donc été une expérience véritablement enrichissante car nous avons pu, au fil des séances, affûter nos connaissances et avancer sur les différents objectifs tout en assurant une cohésion d'équipe. Ce travail en groupe nous a réellement permis d'améliorer notre communication ainsi que notre organisation. En effet, nous avons réparti les différentes tâches en suivant un diagramme de Gantt, que ce soit pour le software ou le hardware. Nous avons ainsi pu fixer des échéances et optimiser notre temps afin d'aller le plus loin possible dans ce projet. Nous n'avons malheureusement pas pu achever le projet comme nous l'avions espéré mais cela n'enlève pas les apprentissages que nous en avons tirés.

Finalement, malgré les difficultés rencontrées, ce projet nous a permis d'acquérir de précieuses compétences techniques, de prendre conscience des enjeux environnementaux et de développer notre esprit d'innovation et de collaboration. 
## Sources

(1):https://fr.wikipedia.org/wiki/Aéroglisseur

(2):https://stackoverflow.com/questions/43483762/using-stm32-hal-timer-and-adjusting-the-duty-cycle-of-a-pwm-signal

(3):https://moons.link/post-632/

(4):http://news.eeworld.com.cn/mcu/ic467303.html

(5):https://polybot-grenoble.fr/wiki/index.php?title=Guide_STM32CubeIDE&mobileaction=toggle_view_mobile

(6):https://www.youtube.com/watch?v=qUFhDOTz160

(7):http://matsubara-ui-design.net/2021/06/i2c/
