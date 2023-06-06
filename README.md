## RAPPORT HOVERCRAFT

## Introduction

Un hovercraft (en français aéroglisseur) est un véhicule amphibie à portance aérostatique et à propulsion aérienne, qui en général possède une ou plusieurs hélices aériennes. La portance est assurée par un coussin d'air sous faible pression relative, entretenu par une soufflante à l'intérieur d'une enceinte dont les parois latérales, appelées jupes, sont suffisamment déformables pour suivre au plus près le relief de la surface survolée et ainsi réduire les fuites. Les aéroglisseurs se déplacent le plus souvent sur la mer, mais aussi sur toute surface terrestre ne présentant pas d'obstacles importants.


## Analyse technique du problème posé

|Objectifs à remplir|Contraintes|
|-------------------|-----------|
|Avancer, décoller|Pas de contrôle à distance|
|Avancer "droit"|Pas de contrôle à distance|
|Avancer 10m|Pas de contrôle à distance|
|Avancer 10m le plus rapidement possible|Pas de contrôle à distance|

## Méthodologie

Pour mener à bien ce projet, nous avons eu à utiliser plusieurs logiciels : 
* **Github** : logiciel qui nous permet de rassembler toute nos travaux dans un seul endroit
* **Draw.io** : logiciel qui nous permet de tracer des graphes
* **Redmine** : logiciel qui nous permet de nous créer un emploi du temps (diagramme de Gantt) et nous a permis de nous répartir les différentes taches
* **Kicad** : logiciel qui nous permet de faire nos schematic ainsi que nos PCB
* **STM32CubeIDE** : logiciel qui nous permet de programmer notre microprocesseur

## Problèmes rencontrés

Lorsque nous avons commencé à souder l'un de nos PCB, il y avait un problème de court-circuit entre la masse et du 3V3. Nous avons analysé notre PCB afin de déterminer l'erreur et nous avons corrigé le problème. Cependant nous avions oublié le connecteur qui alimentait le système en 3V3 nous avons donc dû refaire une V2 de notre deuxième PCB.
Par mégarde, nous avons arraché un connecteur ce qui a arraché une piste cuivre de notre PCB. Nous avons réparé le problème en plaçant un fil.
Lors de la réalisation du 2éme PCB concernant les régulateurs nous avons rencontré des problèmes lors de la conception (notamment l'optimisation de la taille et certaines empreintes) et lors du soudage de certains composants.

Durant l'étape de programmation, nous nous sommes heurtés à de nombreuses difficultés notamment sur les différents pins de sortie.
Le codage des pins en PWM,USART et en I2C étant non traité en TP de microprocesseurs, nous avons eu du mal à écrire les commandes.
En particulier pour programmer le driver des moteurs, qui nécessitent la génération de signal PWM. 
> Note : Tout nos [schémas Kicad](https://github.com/0reoAurelien/projet-hovercraft/tree/main/Hardware) et nos [codes](https://github.com/0reoAurelien/projet-hovercraft/tree/main/Software) sont disponibles sur notre github
## Résultats

Les PCB réalisés ont été concluants après de nombreux essais.
Nous avons allumé une LED avec génération PWM sur la STM32H7A3Zi-Q utilisée en TP.
Nous avons réussi à programmer le driver des LEDs qui s'allument selon un pattern lorsque nous appuyons sur un bouton et l'observer sur le PCB réalisé.
Concernant le PCB avec les régulateur de tension, on arrive à avoir la tension souhaité en sortie.


## Développement durable

**Quelle réflexion avez-vous mené au cours de ce projet autour de la réutilisation d'éléments matériels pour la création de votre projet ?**

Durant notre projet, nous avons beaucoup réfléchi à la réutilisation d'éléments matériels pour la création de notre Hovercraft. En effet, notre projet est un Hovercraft, constitué d'un support en plastique ainsi que de moteurs alimentés en électricité. Le support est fait à base de plastique recyclable imprimé en 3D

**Votre projet limite-t-il les quantités de pollutions ou de déchets rejetés dans les écosystèmes ?**

Comme dit plus haut, notre projet est un Hovercraft, constitué d'un support en plastique ainsi que de moteurs alimentés en électricité. Les batteries qui alimentent les moteurs sont rechargées via le réseau d'électricité de l'ENSEA. De plus, notre hovercraft ne consomme pas beaucoup d'électricité et ne rejette rien dans l'atmosphère ou dans les écosystèmes. Cela en fait un projet à empreinte carbone faible.

## Conclusion

## Sources

(1):https://fr.wikipedia.org/wiki/Aéroglisseur

(2):https://stackoverflow.com/questions/43483762/using-stm32-hal-timer-and-adjusting-the-duty-cycle-of-a-pwm-signal

(3):https://moons.link/post-632/

(4):http://news.eeworld.com.cn/mcu/ic467303.html

(5):https://polybot-grenoble.fr/wiki/index.php?title=Guide_STM32CubeIDE&mobileaction=toggle_view_mobile
