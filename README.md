## RAPPORT HOVERCRAFT

## Introduction

Un hovercraft (en français aéroglisseur) est un véhicule amphibie à portance aérostatique et à propulsion aérienne, qui en général possède une ou plusieurs hélices aériennes.
La portance est assurée par un coussin d'air sous faible pression relative, entretenu par une soufflante à l'intérieur d'une enceinte dont les parois latérales, appelées jupes, sont suffisamment déformables pour suivre au plus près le relief de la surface survolée et ainsi réduire les fuites. Les aéroglisseurs se déplacent le plus souvent sur la mer, mais aussi sur toute surface terrestre ne présentant pas d'obstacles importants (1).


## Analyse technique du problème posé

Nous avons plusieurs objectifs à remplir : 
* Avancer, décoller
* Avancer "droit"
* Avancer 10m
* Avancer 10m le plus rapidement possible

## Méthodologie

Pour mener à bien ce projet, nous avons eu à utiliser plusieurs logiciels : 
* Github : logiciel qui nous permet de rassembler toute nos travaux dans un seul endroit
* Draw.io : logiciel qui nous permet de tracer des graphes
* Redmine : logiciel qui nous permet de nous créer un emploi du temps (diagramme de Gantt) et nous a permis de nous répartir les différentes taches
* Kicad : logiciel qui nous permet de faire nos schematic ainsi que nos PCB
* STM32CubeIDE : logiciel qui nous permet de programmer notre microprocesseur

## Problèmes rencontrés

Quand nous avons codé, nous nous sommes heurtés à de nombreuses difficultés notamment sur les différents pins de sortie.
Lorsque nous avons commencé à souder l'un de nos PCB, il y avait un problème de court-circuit entre la masse et du 3V3. Nous avons analysé notre PCB afin de déterminer l'erreur et malheureusement, l'erreur a nécessité la création d'un nouveau PCB.

## Résultats

Nous avons réussi à coder des Leds qui s'allument selon un pattern quand nous appuyons sur un bouton. 
Les PCB réalisés ont été concluants après de nombreux essais.

## Analyse des résultats

## Développement durable

- Quelle réflexion avez-vous mené au cours de ce projet autour de la réutilisation d'éléments matériels pour la création de votre projet ?

- Votre projet limite-t-il les quantités de pollutions ou de déchets rejetés dans les écosystèmes ?

Notre projet est un Hovecraft, constitué d'un support en plastique ainsi que de moteurs alimentés en électricité. Le support est fait à base de plastique recyclable imprimé en 3d, et les batteries qui alimentent les moteurs sont rechargées via le réseau d'électricité de l'ENSEA. De plus, notre hovercraft ne consomme pas beaucoup d'électricité. Cela en fait un projet à empreinte carbone faible.

## Conclusion

## Sources

(1):https://fr.wikipedia.org/wiki/Aéroglisseur
