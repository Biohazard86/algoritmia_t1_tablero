// Trabajo 1 - Algoritmia
// Autores: David Barrios Portales & Sergios Barrios Portales
// Fecha: 23/11/2021
//-----------------------------------------------------------------------------
/*
ENUNCIADO:

Se desea encontrar un recorrido de caballo en un tablero N*N que permita viajar de la casilla (1,1) a la casilla (N,N),
 en tiempo mínimo (medido por el número de saltos), sabiendo que en el tablero hay N obstáculos, situados aleatoriamente 
 en casillas del tablero, y indicados mediante un array obstaculo(X,Y) que es verdadero si la casilla (X,Y) contiene un 
 obstáculo y falso si no lo contiene.

1. Desarrollar un algoritmo empleando programación dinámica para resolver el problema, es decir, dados los obstáculos, 
encontrar el recorrido del caballo que minimize el número de saltos a dar sin pasar por esos obstáculos para ir de (1,1) a (N,N).
2. Calcular el tiempo que precisa para ejecutarse en función de N.
3. Traducir el algoritmo anterior a C.

Observación 1: La tabla a construir podría ser MINS(X,Y) que contendría el mínimo número de saltos para ir de (1,1) a (X,Y).

Observación 2: La práctica es obligatoria para todos, para los que hayan optado por los exámenes, la práctica no tendrá defensa, 
y será la única del curso, para el resto habrá una segunda práctica, y ambas serán con defensa.

*/





// Librerias usadas
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NO_OBSTACULO 8 // Porcentaje de casillas no obstaculos en el tablero (0-10) 


//Funcion de presentacion que se ejecuta al inicio del programa
void presentacion(){
    fprintf(stdout, "------------------------------------------------------------\n");
    fprintf(stdout, "--                TRABAJO 1 / CURSO 2021/2022             --\n");
    fprintf(stdout, "--  Recorrido de un caballo en un tablero con obstaculos  --\n");
    fprintf(stdout, "------------------------------------------------------------\n");
    fprintf(stdout, "--           David Barrios   &   Sergio Barrios           --\n");
    fprintf(stdout, "------------------------------------------------------------\n\n");
}


//Funcion que genera el array de obstaculos del tablero
void genera_obstaculos(int N, int *vector_obstaculos){
   int i, temp;
   srand (time(NULL));
   for(i=0; i<N; i++){
       temp = rand()%11;
       if(temp > NO_OBSTACULO){
           vector_obstaculos[i] = 1;
       }
       else{
           vector_obstaculos[i] = 0;
       }
   }

}

// Funcion para imprimir los obstaculos del tablero
void imprime_obstaculos(int N, int *vector_obstaculos){
    int i;
    for(i=0; i<N; i++){
        printf("%d ", vector_obstaculos[i]);
    }
    printf("\n");
} 


// Funcion que valida los parametros de entrada
int comprobar_parametros(int N, int x1, int y1){
    if(N<=0 || x1<=0 || y1<=0 || x1>N || y1>N){
        return 0;
    }
    else{
        // N tiene que ser mayor de 2 para que el algoritmo funcione
        if(N<=2){
            return 0;
        }
        else{
            return 1;
        }  
    }
}




//Funcion que imprime la matriz tablero 
void imprime_tablero(int N, int *tablero){
    int i, j;
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            printf(" %d ", tablero[i*N+j]);
        }
        printf("\n");
    }
}


//Funcion que limpia el tablero poniendo todos los valores a 0
void limpia_tablero(int N, int *tablero){
    int i, j;
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            tablero[i*N+j] = 0;
        }
    }
}

//Comprueba si en la casilla (x,y) hay un obstaculo y si lo hay lo quita
void comprueba_posicion_final_inicio(int N, int *tablero, int x, int y){
    if(tablero[x*N+y] == 1){
        tablero[x*N+y] = 0;
    }
}


// Funcion que calcula el camino mas corto para llegar de (1,1) a (N,N)
int camino_mas_corto(int N, int *tablero, int x0, int y0, int x1, int y1){

}
    
//Funcion que calcula los pasos minimos para llegar de (1,1) a (N,N)
int pasos(int N, int *tablero, int x0, int y0, int x1, int y1){
    

    // En caso de que el punto de destino sea igual que el de inicio
    if(x0 == x1 && y0 == y1){
        return 0;
    }
    
}

// Funcion principal
int main(int argc, char *argv[]){

    // Definicio de las variables
    int N;                      // Numero de filas y columnas que va a tener el tablero
    int *vector_obstaculos;     // Vector que contiene los obstaculos del tablero
    int **matriz_tablero;       //Matriz que vamos a usar en funcion de las posiciones que nos pase el usuario. Es un puntero a punteros de enteros
    int i;                      // Contador
    int x0 = 0,y0 = 0;          // Posicion inicial del caballo  
    int x1,y1;                  // Posicion final del caballo

    // Presentacion del programa
    presentacion();

    // Pedimos al usuario el numero de filas/columnas del tablero y el punto de destino
    if(argc > 3){
        N = atoi(argv[1]);
        x1 = atoi(argv[2]);
        y1 = atoi(argv[3]);
    }
    else{
        fprintf(stderr, "Error: No se han introducido todos los datos.\n");
        fprintf(stderr, "./tablero A B C.\n");
        fprintf(stderr, "A=Dimension del tablero A*A posiciones\n");
        fprintf(stderr, "B=Posicion final de la coordenada X\n");
        fprintf(stderr, "C=Posicion final de la coordenada Y\n");
        return 1;
    }

    // Comprobamos que los parametros introducidos son correctos
    if(!comprobar_parametros(N, x1, y1)){
        // Si no lo son entonces finalizamos la ejecucion del programa
        fprintf(stderr, "Error: Los parametros introducidos no son posibles.\n");
        return 0;
    }
    
    fprintf(stdout, "Datos de la ejecucion:\n");
    fprintf(stdout, "-> Tablero de %dx%d\n", N, N);
    fprintf(stdout, "-> Posicion final del caballo: (%d,%d)\n", x1, y1);
    // Se genera el array de obstaculos con calloc
    vector_obstaculos = (int *)calloc(N*N, sizeof(int));
    // Se genera el array de obstaculos aleatoriamente
    genera_obstaculos(N*N, vector_obstaculos);
    // Se imprime el array de obstaculos
    fprintf(stdout, "Obstaculos:\n");
    imprime_obstaculos(N*N, vector_obstaculos);

    // Se reserva memoria para la matriz del tablero
    //solicitamos la memoria con calloc para la matriz en funcion de los argumentos que nos pase el usuario
    matriz_tablero = (int **)calloc(N, sizeof(int *));
    for(int i = 0; i < N; i++){
        matriz_tablero[i] = (int *)calloc(N, sizeof(int));
    }

    //Limpiamos la tabla poniendo todos sus valores a 0
    limpia_tablero(N, *matriz_tablero);
    
    //Imprimimos la matriz del tablero
    fprintf(stdout, "Tablero sin obstaculos:\n");
    imprime_tablero(N, matriz_tablero[0]);

    //Pasamos los obstaculos (cuando haya un 1 en el array de obstaculos) a la matriz del tablero
    for(i=0; i<N*N; i++){
        if(vector_obstaculos[i] == 1){
            matriz_tablero[i/N][i%N] = 1;
        }
    }

    //Imprimimos la matriz del tablero
    fprintf(stdout, "Tablero con obstaculos:\n");
    imprime_tablero(N, matriz_tablero[0]);

    // Comprobamos que ni en la posicion final ni en la de inicio haya un obstaculo
    comprueba_posicion_final_inicio(N, matriz_tablero[0], x0, y0);
    comprueba_posicion_final_inicio(N, matriz_tablero[0], x1, y1);


    //Imprimimos la matriz del tablero
    fprintf(stdout, "Tablero con obstaculos:\n");
    imprime_tablero(N, matriz_tablero[0]);

    //se llama a la funcion que calcula el camino mas corto
    camino_mas_corto(N, matriz_tablero, x0, y0, x1, y1);





    // Liberamos la memoria solicitada para el tablero.
    free(matriz_tablero);

}
