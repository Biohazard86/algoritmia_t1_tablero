# algoritmia_t1_tablero
Trabajo 1 de la asignatura de algoritmia.


Se desea encontrar un recorrido de caballo en un tablero N*N que permita viajar de la casilla (1,1) a la casilla (N,N), en tiempo mínimo (medido por el número de saltos), sabiendo que en el tablero hay N obstáculos, situados aleatoriamente en casillas del tablero, y indicados mediante un array obstaculo(X,Y) que es verdadero si la casilla (X,Y) contiene un obstáculo y falso si no lo contiene.

1. Desarrollar un algoritmo empleando programación dinámica para resolver el problema, es decir, dados los obstáculos, encontrar el recorrido del caballo que minimize el número de saltos a dar sin pasar por esos obstáculos para ir de (1,1) a (N,N).
2. Calcular el tiempo que precisa para ejecutarse en función de N.
3. Traducir el algoritmo anterior a C.

Observación 1: La tabla a construir podría ser MINS(X,Y) que contendría el mínimo número de saltos para ir de (1,1) a (X,Y).

Observación 2: La práctica es obligatoria para todos, para los que hayan optado por los exámenes, la práctica no tendrá defensa, y será la única del curso, para el resto habrá una segunda práctica, y ambas serán con defensa.
