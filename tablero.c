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
ALGORITMO
1 - Creamos la tabla NxN que almacenara los visitados, 0 = no visitado / 1 = visitado
    Creamos la tabla NxNx3 que almacenara los padres para llegar a esa posicion, es decir si a la casilla 1,1 hemos llegado desde la 0,0 en la casilla 1,1 vamos a guardar 0,0. Los no visitados estan a NULL
    Creamos la tabla NxN de obstaculos, la cual las casillas con obstaculo tendran un 1 y el resto un 0.
    Creaamos el vector cola, donde almacenaremos los puntos a procesar. Esto puede ser un vector dimensional, para la X y la Y
    Creamos la variable entera iteraccion la cual la inicializamos a 0
    
2 - Ponemos la casilla de salida como visitada y ponemos esta casilla en el primer puesto de la cola, para ser la primera en ser procesada.
    En esta cola se meteran las casillas aun no visitadas, desde la cual se puede ir en la ultima comprobada.
3 - hacer lo siguiente hasta que la cola este vacia o hasta que se llegue a la posicion deseada:
    3.1 - Sacamos el primer elemento de la cola y lo guardamos como padre en esta iteraccion.	------------------------------------------------------	extrae_cola
    3.2 - Comprobamos todas las posiciones a las que se puede ir desde dicho elemento y las guardamos en la cola si no han sido visitadas ya*  -------  calcular_posibles_destinos + insertar_cola
    3.3 - Guardamos en la matriz de los padres estas posiciones y todas tienen como padre la que sacamos en el paso 3.1	------------------------------  guarda_recorrido + 
    3.3 - Comprobamos si la posicion del punto 3.1 es la meta.	--------------------------------------------------------------------------------------  comprueba_meta
    3.4 - Incrementamos la variable de iteraccion
    
    *Si una posicion ya ha sido visitada, esto significa que no tenemos que sobrescribir esa posicion con una menos optima.
*/





// Librerias usadas
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NO_OBSTACULO 7 // Porcentaje de casillas no obstaculos en el tablero (0-10) 
#define FALSE 0
#define TRUE 1



//----------------------------------------------------------------------------------------------------------------------
// Funcion presentacion
//----------------------------------------------------------------------------------------------------------------------
// Funcion que presenta el programa
//----------------------------------------------------------------------------------------------------------------------
// PARAMETROS
//----------------------------------------------------------------------------------------------------------------------
void presentacion(){
    fprintf(stdout, "------------------------------------------------------------\n");
    fprintf(stdout, "--                TRABAJO 1 / CURSO 2021/2022             --\n");
    fprintf(stdout, "--  Recorrido de un caballo en un tablero con obstaculos  --\n");
    fprintf(stdout, "------------------------------------------------------------\n");
    fprintf(stdout, "--           David Barrios   &   Sergio Barrios           --\n");
    fprintf(stdout, "------------------------------------------------------------\n\n");
}


//----------------------------------------------------------------------------------------------------------------------
// Funcion genera_obstaculos
//----------------------------------------------------------------------------------------------------------------------
// Funcion que genera el array de obstaculos del tablero
//----------------------------------------------------------------------------------------------------------------------
// PARAMETROS
//      N: tamaño del tablero
//      vector_obstaculos: array de obstaculos
//----------------------------------------------------------------------------------------------------------------------

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



//----------------------------------------------------------------------------------------------------------------------
// Funcion imprime_obstaculos
//----------------------------------------------------------------------------------------------------------------------
// Funcion que imprime los obstaculos del tablero
//----------------------------------------------------------------------------------------------------------------------
// PARAMETROS
//      N: tamaño del tablero
//      vector_obstaculos: array de obstaculos
//----------------------------------------------------------------------------------------------------------------------

void imprime_obstaculos(int N, int *vector_obstaculos){
    int i;
    for(i=0; i<N; i++){
        printf("%d ", vector_obstaculos[i]);
    }
    printf("\n");
} 


//----------------------------------------------------------------------------------------------------------------------
// Funcion comprobar_parametros
//----------------------------------------------------------------------------------------------------------------------
// Funcion que comprueba los parametros que se han introducido por la linea de comandos
//----------------------------------------------------------------------------------------------------------------------
// PARAMETROS
//      N: tamaño del tablero
//      x1: posicion en x
//      y1: posicion en y
//----------------------------------------------------------------------------------------------------------------------

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


//----------------------------------------------------------------------------------------------------------------------
// Funcion imprime_tablero
//----------------------------------------------------------------------------------------------------------------------
// Funcion que imprime la matriz tablero
//----------------------------------------------------------------------------------------------------------------------
// PARAMETROS
//      N: tamaño del tablero
//      tablero
//----------------------------------------------------------------------------------------------------------------------

void imprime_tablero(int N, int *tablero){
    int i, j;
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            printf(" %d ", tablero[i*N+j]);
        }
        printf("\n");
    }
}


//----------------------------------------------------------------------------------------------------------------------
// Funcion limpia_tablero
//----------------------------------------------------------------------------------------------------------------------
// Funcion que limpia el tablero antes de hacer nada con el
//----------------------------------------------------------------------------------------------------------------------
// PARAMETROS
//      N: tamaño del tablero
//      tablero
//----------------------------------------------------------------------------------------------------------------------

void limpia_tablero(int N, int *tablero){
    int i, j;
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            tablero[i*N+j] = 0;
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------
// Funcion comprueba_posicion_final_inicio
//----------------------------------------------------------------------------------------------------------------------
// Funcion que comprueba si en la casilla (x,y) hay un obstaculo y si lo hay lo quita
//----------------------------------------------------------------------------------------------------------------------
// PARAMETROS
//      N: tamaño del tablero
//      tablero
//      x: posicion en x
//      y: posicion en y
//----------------------------------------------------------------------------------------------------------------------

void comprueba_posicion_final_inicio(int N, int *tablero, int x, int y){
    if(tablero[x*N+y] == 1){
        tablero[x*N+y] = 0;
    }
}



//----------------------------------------------------------------------------------------------------------------------
// Funcion es_posible
//----------------------------------------------------------------------------------------------------------------------
// Funcion que recibe un punto y el tablero y decide si es posible dicho punto, devuelve 1 si es posible
// y 0 si no lo es
//----------------------------------------------------------------------------------------------------------------------
// PARAMETROS
//      N: tamaño del tablero
//      x: coordenada x del punto
//      y: coordenada y del punto
//      tablero: matriz del tablero
//----------------------------------------------------------------------------------------------------------------------

int es_posible(int N, int x, int y, int **tablero){
    // Comprobamos que el punto esta dentro del tablero
    if(x<0 || y<0 || x>=N || y>=N){

        return 0;
    }
    // Comprobamos que el punto no es un obstaculo
    else{
        // Comprobamos si hay un 1 en esa posicion del tablero (obstaculo)
        if(tablero[x][y] == 1){
            //si hay un obstaculo, devolvemos 0, ya que no se puede
            return 0;
        }
        else{   // Si no hay obstaculo, devolvemos 1
            return 1;
        }
    }
}


//----------------------------------------------------------------------------------------------------------------------
// Funcion insertar_cola
//----------------------------------------------------------------------------------------------------------------------
// Funcion que recibe un punto y lo inserta en la cola
//----------------------------------------------------------------------------------------------------------------------
// PARAMETROS
//      x: coordenada x del punto inicio
//      y: coordenada y del punto inicio
//      x_meta: coordenada x del punto meta
//      y_meta: coordenada y del punto meta
//----------------------------------------------------------------------------------------------------------------------

int insertar_cola(int x, int y, int **cola,int *tam_cola, int *tam_cola_ocupado){
    // Vamos al ultimo ocupado +1

    // Comprobamos que donde vamos a escribir haya memoria
    if(*tam_cola_ocupado < *tam_cola){
        cola[*tam_cola_ocupado+1][0]=x;
        cola[*tam_cola_ocupado+1][1]=y;

        tam_cola_ocupado++;
    }
    else{
        //reservamos memoria con calloc en la cola
        cola = (int **)calloc(1,sizeof(int *));
        cola[*tam_cola_ocupado+1] = (int *)calloc(1,sizeof(int));

        cola[*tam_cola_ocupado+1][0]=x;
        cola[*tam_cola_ocupado+1][1]=y;

        tam_cola_ocupado++;
        tam_cola++;
    }
    


}


//----------------------------------------------------------------------------------------------------------------------
// Funcion comprobar_posibles_destinos
//----------------------------------------------------------------------------------------------------------------------
// Funcion que recibe un punto de inicio y devuelve un array con todos los posibles destinos teniendo en cuenta
// los movimientos del caballo dentro del tablero y los obstaculos, asi como la matriz de visitados
//----------------------------------------------------------------------------------------------------------------------
// PARAMETROS
//      N: tamaño del tablero
//      tablero: matriz del tablero
//      x: coordenada x del punto de inicio
//      y: coordenada y del punto de inicio
//      cola: cola de puntos a consultar
//      matriz_padres: matriz de padres y visitados
//----------------------------------------------------------------------------------------------------------------------

int comprobar_posibles_destinos(int N, int **tablero, int x, int y, int **cola, int **matriz_visitados, int *tam_cola, int *tam_cola_ocupada){
    int posible_mover=0;

    int vector_movimientos[8][2] = {{1,2},{2,1},{2,-1},{1,-2},{-1,2},{-2,1},{-2,-1},{-1,-2}};
    // for desde 0 a 8 para realizar todos los posibles movimientos
    for(int i=0; i<8; i++){
        // x_temp y y_temp son las coordenadas del destino
        int x_temp = x + vector_movimientos[i][0];
        int y_temp = y + vector_movimientos[i][1];
        // Si es posible moverse a esa posicion
        if(es_posible(N, x_temp, y_temp, tablero)){     // Si es posible moverse a esa posicion
            if(matriz_visitados[x_temp][y_temp] != 1){  // Si no hemos visitado esa posicion
                cola[i][0] = x_temp;
                cola[i][1] = y_temp;
                posible_mover++;
                insertar_cola(x_temp, y_temp, cola, tam_cola, tam_cola_ocupada);
            }
        }
    }
    // Si no hay posibles movimientos, devolvemos 1 ya que hay un error.
    if(posible_mover == 0){
        return 1;
    }
    else{
        // Si hay posibles movimientos, devolvemos 0 indicando que no hay error.
        return 0;
    }
}



//----------------------------------------------------------------------------------------------------------------------
// Funcion comprueba_visitado
//----------------------------------------------------------------------------------------------------------------------
// Funcion que recibe una posicion y la matriz de padres y devuelve 1 si la posicion esta visitada y 0 si no
//----------------------------------------------------------------------------------------------------------------------
// PARAMETROS
//      N: tamaño del tablero
//      x: coordenada x del punto
//      y: coordenada y del punto
//      matriz_padres: matriz del los padres/visitados
//----------------------------------------------------------------------------------------------------------------------

int comprueba_visitado(int N, int x, int y, int ***matriz_padres){

    //
    if(matriz_padres[x][y][0] != 1){
        return 1;
    }
    else{
        return 0;
    }
}





//----------------------------------------------------------------------------------------------------------------------
// Funcion extraer_cola
//----------------------------------------------------------------------------------------------------------------------
// Funcion que recibe una cola y devuelve los primeros valores de dicha cola
//----------------------------------------------------------------------------------------------------------------------
// PARAMETROS
//      N: tamaño del vector
//      cola: vector de la cola
//      x: coordenada x del punto
//      y: coordenada y del punto
//----------------------------------------------------------------------------------------------------------------------

int extraer_cola( int *tam_vec, int *tam_vec_ocupado, int **cola, int x,int y){
    
    x= cola[0][0];
    y= cola[0][1];

    // Recorremos todo el vector
    for(int i=0;i<*tam_vec;++i)
    {
        //i es destino
        //i+1 es origen

        // Si el tamanio del vector
        if(*tam_vec_ocupado < i){
            cola[i][0]=cola[i+1][0];
            cola[i][1]=cola[i+1][1];
        }
        else{
            //Para la parte no ocupada del vector
            cola[i][0]=-1;
            cola[i][1]=-1;
        }

    }
}



//----------------------------------------------------------------------------------------------------------------------
// Funcion comprueba_meta
//----------------------------------------------------------------------------------------------------------------------
// Funcion que recibe dos puntos y comprueba si son iguales. Devuelve 1 si se ha llegado a la meta y 0 si no.
//----------------------------------------------------------------------------------------------------------------------
// PARAMETROS
//      x: coordenada x del punto inicio
//      y: coordenada y del punto inicio
//      x_meta: coordenada x del punto meta
//      y_meta: coordenada y del punto meta
//----------------------------------------------------------------------------------------------------------------------


int comprueba_meta(int x,int y, int meta_x,int meta_y){
    if((x==meta_x) && (y==meta_y))
    {
        return TRUE;
    }else{
        return FALSE;
    }
}





//----------------------------------------------------------------------------------------------------------------------
// Funcion insertar_matriz_padres
//----------------------------------------------------------------------------------------------------------------------
// Funcion que recibe dos puntos, el punto padre y el punto actual. Inserta en la matriz estos datos
//----------------------------------------------------------------------------------------------------------------------
// PARAMETROS
//      x: coordenada x del punto actual
//      y: coordenada y del punto actual
//      x_padre: coordenada x del punto padre
//      y_padre: coordenada y del punto padre
//      matriz_padres: matriz de los padres
//----------------------------------------------------------------------------------------------------------------------

int insertar_matriz_padres(int x_padre, int y_padre, int ***matriz_padres, int iteraccion, int **cola, int *tam_cola, int *tam_cola_ocupado){

    int x_temp,y_temp;

    // recorremos toda la cola para almacenar los valores que haya en ella
    for(int i=0;i<*tam_cola_ocupado;++i)
    {
        x_temp = cola[i][0];
        y_temp = cola[i][1];

        // Realizamos una comprobacion de errores que no es necesaria pero nunca esta de mas
        // Si en el punto hay algo diferente a un 0 no debemos sobreescribirlo
        if(matriz_padres[x_temp][y_temp][0] != 0){
            return 0;
        }
        else{
            // Si no hay nada, lo insertamos
            matriz_padres[x_temp][y_temp][0]=iteraccion;          // Los pasos que hemos dado para llegar ahi
            matriz_padres[x_temp][y_temp][1]=x_padre;             // La coordenada x del punto padre (el punto que hemos llegado de)
            matriz_padres[x_temp][y_temp][2]=y_padre;             // La coordenada y del punto padre (el punto que hemos llegado de)
            return 1;                                               // Significa que todo ha ido bien
        }
        

    }
    
    
}




//----------------------------------------------------------------------------------------------------------------------
// Funcion reconstruir_camino
//----------------------------------------------------------------------------------------------------------------------
// Funcion que se llama una vez acabada la ejecucion y reconstruye el camino desde la meta hasta el punto inicial
// Usa la matriz de padres para reconstruir el camino
//----------------------------------------------------------------------------------------------------------------------
// PARAMETROS
//      matriz_padres: matriz de los padres donde esta la informacion
//----------------------------------------------------------------------------------------------------------------------

int reconstruir_camino(int ***matriz_padres, int **ruta, int x_destino, int y_destino, int iteraccion){

    int x_ini,y_ini, x_fin, y_fin, iteraccion_ruta = 0, i;

    //Nos situamos en la posicion de destino x,y
    x_fin=x_destino;
    y_fin=y_destino;

    fprintf(stdout, "La ruta desde el fin hasta el inicio es:\n");


    while ((x_ini != 0) || (y_ini != 0)){
        
        // Nos movemos al punto padre (cogemos los datos desde donde se llego a esa casilla)
        x_ini=matriz_padres[x_fin][y_fin][1];
        y_ini=matriz_padres[x_fin][y_fin][2];

        //Pedimos memoria con calloc para el vector ruta
        ruta = (int **)calloc(1, sizeof(int *));
        for(int i = 0; i < iteraccion_ruta; i++){
            ruta[i] = (int *)calloc(1, sizeof(int));
        }



        // Insertamos el punto en la ruta
        ruta[0][0]=x_ini;
        ruta[0][1]=y_ini;
        iteraccion_ruta++;  // Incrementamos para comprobar que nos sale los mismo que con el que se nos pasa mediante parametro

        // Y ahora ponemos el inicio como final
        x_fin=x_ini;
        y_fin=y_ini;


        // Imprimimos la ruta
        fprintf(stdout, "%d, %d\n", x_ini, y_ini);
    }
    
    
}





//----------------------------------------------------------------------------------------------------------------------
// Funcion main
//----------------------------------------------------------------------------------------------------------------------
// Funcion que recibe un entero que es el numero de parametros introducidos por el usuario y un puntero a char
//----------------------------------------------------------------------------------------------------------------------
// PARAMETROS
//      argc: numero de parametros introducidos por el usuario
//      argv: puntero a char con las opciones introducidas por el usuario
//----------------------------------------------------------------------------------------------------------------------

// Funcion principal
int main(int argc, char *argv[]){

    // Definicio de las variables
    int N;                      // Numero de filas y columnas que va a tener el tablero
    int **matriz_visitados;     // Matriz de visitados 0 si no ha sido visitado, 1 si si lo ha sido
    int *vector_obstaculos;     // Vector que contiene los obstaculos del tablero
    int **matriz_tablero;       //Matriz que vamos a usar en funcion de las posiciones que nos pase el usuario. Es un puntero a punteros de enteros
    int **posibles_destinos;    //En esta matriz vamos a almacenar los posibles destinos (Vector de 2x?)
    int ***matriz_padres;       //Matriz de NxNn3 En ests matriz vamos a almacenar la posicion respecto el inicio m[][][0], la coordenada x m[][][1]y la coordenada y m[][][2]
    int i, j, k;                      // Contador
    int iteraciones;            // Contador de iteraciones
    int x0 = 0,y0 = 0;          // Posicion inicial del caballo  
    int x1,y1;                  // Posicion final del caballo
    int *tam_cola = 0;           // Tamaño de la cola
    int *tam_cola_ocupado = 0;   // Tamaño de la cola ocupada
    int flag_continuar = TRUE;  // Bandera para saber si seguimos o no
    int x_temporal, y_temporal; // Posiciones temporales para almacenar las posiciones de los destinos
    int **ruta_seguida;         // Vector que almacena la ruta seguida para mostrarla al finalizar la ejecucion


    // Presentacion del programa
    presentacion();

    // Pedimos al usuario el numero de filas/columnas del tablero y el punto de destino
    if(argc > 1){
        N = atoi(argv[1]);
        x1 = N;
        y1 = N;
    }
    else{
        fprintf(stderr, "Error: No se han introducido todos los datos.\n");
        fprintf(stderr, "./tablero N\n");
        fprintf(stderr, "N=Dimension del tablero N*N posiciones\n");
        //fprintf(stderr, "B=Posicion final de la coordenada X\n");
        //fprintf(stderr, "C=Posicion final de la coordenada Y\n");
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


    // Se reserva memoria para la matriz de visitados
    matriz_visitados = (int **)calloc(N, sizeof(int *));
    for(i = 0; i < N; i++){
        matriz_visitados[i] = (int *)calloc(N, sizeof(int));
    }

    // Se reserva memoria para la matriz de padres
    matriz_padres = (int ***)calloc(N, sizeof(int **));
    for(i = 0; i < N; i++){
        matriz_padres[i] = (int **)calloc(N, sizeof(int *));
        for(j = 0; j < N; j++){
            matriz_padres[i][j] = (int *)calloc(3, sizeof(int));
        }
    }
    
    
    
    //----------------------------------------------------------------------------------------------------------------------
    //COMIENZO DEL ALGORITMO
    //----------------------------------------------------------------------------------------------------------------------

    fprintf(stdout, "Comienza el algoritmo\n");

    // Ponemos la casilla de salida como visitada
    matriz_visitados[x0][y0] = 1;

    // introducimos la casilla de inicio en la cola
    //int insertar_cola(int x, int y, int **cola,int *tam_cola, int *tam_cola_ocupado){
    insertar_cola(x0, y0, posibles_destinos, tam_cola, tam_cola_ocupado);
    iteraciones++;


    fprintf(stdout, "Se ha cargado la posicion inicial y se procede al bucle.\n");

    // hacemos esto hasta que la bandera este a FALSE
    while(flag_continuar){

        fprintf(stdout, "Iteracion %d\n", iteraciones);

        // Extraemos el primer valor de la cola y los guardamos en vars temporales
        x_temporal = posibles_destinos[0][0];
        y_temporal = posibles_destinos[0][1];
        //int extraer_cola( int *tam_vec, int *tam_vec_ocupado, int **cola, int x,int y){
        extraer_cola(tam_cola, tam_cola_ocupado, posibles_destinos, x_temporal, y_temporal);

        // Calculamos a las posiciones que se pueden ir desde la casilla que acabamos de extraer
        comprobar_posibles_destinos(N, matriz_tablero, x_temporal, y_temporal, posibles_destinos, matriz_visitados, tam_cola, tam_cola_ocupado);
_destino,
        //int insertar_matriz_padres(int x_padre, int y_padre, int ***matriz_padres, int iteraccion, int **cola, int *tam_cola, int *tam_cola_ocupado)
        //Insertamos en la matriz de padres los valores de la cola
        insertar_matriz_padres(x_temporal, y_temporal, matriz_padres, iteraciones, posibles_destinos, tam_cola, tam_cola_ocupado);

        //Comprobamos si es la meta el punto en el que estamos
        if(comprueba_meta(x_temporal, y_temporal, N, N)){
            // Ponemos la flag a cero
            flag_continuar = 0;
        }
        // comprobamos el tamanio del vector de ocupados de la cola
        // ya que si esta a cero seria una condicion para parar
        if(tam_cola_ocupado == 0){
            flag_continuar = 0;
        }



        // Incrementamos la iteracion
        iteraciones++;      // Las iteracciones que llevamos/pasos hasta este punto
    }

    // int reconstruir_camino(int ***matriz_padres, int **ruta, int x_destino, int y_destino, int iteraccion)
    // Reconstruimos la ruta
    reconstruir_camino(matriz_padres, ruta_seguida, x1, y1, iteraciones);



    // Liberamos la memoria solicitada para el tablero.
    free(matriz_tablero);

}