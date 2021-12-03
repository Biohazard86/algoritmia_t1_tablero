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
#define NO_OBSTACULO 6 // Probabilidad de que una casilla no sea obstaculo (0-10)
#define FALSE 0
#define TRUE 1
#define DEBUG 0         // 1 = activa, 0 = desactiva
#define ASEGURAR_META 0 // Se asegura de que en la meta no haya obstaculos si esta a 1. Si esta a 0 no hace esa comprobacion



//----------------------------------------------------------------------------------------------------------------------
// Funcion presentacion
//----------------------------------------------------------------------------------------------------------------------
// Funcion que presenta el programa
//----------------------------------------------------------------------------------------------------------------------
// PARAMETROS
//----------------------------------------------------------------------------------------------------------------------
void presentacion(){
    fprintf(stdout, "------------------------------------------------------------\n");
    fprintf(stdout, "--                TRABAJO 1 - CURSO 2021/2022             --\n");
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
//      tablero: array de obstaculos
//      matriz_visitados: array de visitados
//----------------------------------------------------------------------------------------------------------------------

void genera_obstaculos(int N, int **tablero,int **matriz_visitados){
   int i, temp1, temp2, contador_obstaculos = 0;
   srand (time(NULL));
   for(i=0; i<N; i++){
       temp1 = rand()%N;
       temp2 = rand()%N;

       if(tablero[temp1][temp2] == 0){
           matriz_visitados[temp1][temp2] = 1;
           tablero[temp1][temp2] = 1;
           contador_obstaculos++;
       }
       // Nos aseguramos que en la meta no haya obstaculos si en la constante ASEGURAR_META esta a 1
       if(ASEGURAR_META){
           tablero[0][0] = 0;
           matriz_visitados[0][0] = 0;
           tablero[N-1][N-1] = 0;
            matriz_visitados[N-1][N-1] = 0;  
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

void imprime_tablero(int N, int **tablero){
    int i, j;
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            printf(" %d ", tablero[i][j]);
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
// Funcion que recibe un punto y lo inserta en la cola en el ultimo lugar posible
//----------------------------------------------------------------------------------------------------------------------
// PARAMETROS
//      x: coordenada x del punto inicio
//      y: coordenada y del punto inicio
//      cola_x: cola de coordenadas x
//      cola_y: cola de coordenadas y
//      N: tamaño del tablero
//----------------------------------------------------------------------------------------------------------------------

int insertar_cola(int x, int y, int *cola_x, int *cola_y, int N){
    int i, tam_vector = N*N;

    // Recorremos la cola hasta encontrar un numero negativo
    for(i=0; i<tam_vector; i++){
        if((cola_x[i] < 0) && (cola_y[i] < 0)){
            // Si encontramos un numero negativo, insertamos el punto en esa posicion, ya que esta libre
            cola_x[i] = x;
            cola_y[i] = y;
            return 1;
        }
        
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
//      colax: cola de puntos a consultar
//      colay: cola de puntos a consultar
//      matriz_padres: matriz de padres y visitados
//----------------------------------------------------------------------------------------------------------------------

int comprobar_posibles_destinos(int N, int **tablero, int x, int y, int *cola_x, int *cola_y, int **matriz_visitados){
    int posible_mover=0;

    // Todos los movimientos posibles que puede hacer el caballo en el tablero
    int vector_movimientos[8][2] = {{1,2},{2,1},{2,-1},{1,-2},{-1,2},{-2,1},{-2,-1},{-1,-2}};
    // for desde 0 a 8 para realizar todos los posibles movimientos
    
    
    for(int i=0; i<8; i++){

        // x_temp y y_temp son las coordenadas del destino
        int x_temp = x + vector_movimientos[i][0];
        int y_temp = y + vector_movimientos[i][1];
        // Si es posible moverse a esa posicion
        if(es_posible(N, x_temp, y_temp, tablero)){     // Si es posible moverse a esa posicion
            if(matriz_visitados[y_temp][x_temp] != 1 ){  // Si no hemos visitado esa posicion
                /*
                fprintf(stdout,"===\n");
                imprime_tablero(N, tablero);
                fprintf(stdout,"===\n");
                fprintf(stdout,"%d -> %d,%d\n", tablero[y_temp][x_temp], x_temp, y_temp);
                fprintf(stdout,"===\n");
                */
                if(tablero[y_temp][x_temp] != 1){
                    posible_mover++;
                    //int insertar_cola(int x, int y, int *cola_x, int *cola_y, int N){
                    insertar_cola(x_temp, y_temp, cola_x, cola_y, N);
                    //Lo marcamos como visitado
                    matriz_visitados[y_temp][x_temp] = 1;
                }
                /*else if(tablero[x_temp][y_temp] == 1){
                    printf("\nNo se puede mover a esa posicion\n");
                }*/
                
            }
        }
    }
    // Si no hay posibles movimientos, devolvemos 0 ya que hay un error.
    if(posible_mover == 0){
        return posible_mover;
    }
    else{
        // Si hay posibles movimientos, devolvemos >0 indicando que no hay error.
        return posible_mover;
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
//      colax: vector de la cola
//      colay: vector de la cola
//      x: coordenada x del punto
//      y: coordenada y del punto
//----------------------------------------------------------------------------------------------------------------------

int extraer_cola( int *cola_x, int *cola_y, int *x,int *y, int N){
    
    int tam_vector = N*N, i;

    //Extraemos el primer elemento de la cola
    if((cola_x[0] >= 0) && (cola_y[0] >= 0)){
        *x = cola_x[0];
        *y = cola_y[0];
    }
    else{
        // Esto significa que la cola esta vacia y no hay nada que extraer
        return 0;
    }
    

    
    for(int i=0;i<tam_vector;++i){
        // Recorremos todo el vector para mover todos los elementos una posicion hacia la izquierda si no es negativo
        if((cola_x[i] >= 0) && (cola_y[i] >= 0)){
            cola_x[i] = cola_x[i+1];
            cola_y[i] = cola_y[i+1];
        }
        else{
            cola_x[i] = -1;
            cola_y[i] = -1;
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
//      x_padre: coordenada x del punto padre
//      y_padre: coordenada y del punto padre
//      matriz_padres: matriz de los padres
//      iteraccion
//      x_cola: coordenada x del punto actual
//      y_cola: coordenada y del punto actual
//----------------------------------------------------------------------------------------------------------------------

int insertar_matriz_padres(int x_padre, int y_padre, int ***matriz_padres, int iteraccion, int *cola_x, int *cola_y,int N){

    int x_temp,y_temp, tam_cola = N*N, i;

    // recorremos toda la cola para almacenar los valores que haya en ella
    for(i=0;i<tam_cola;++i)
    {
        // Cogemos los elementos de la cola que sean positivos
        if((cola_x[i] >= 0) && (cola_y[i] >= 0))
        {
            if(DEBUG){
                printf("Se procede a insertar en la matriz de padres.\n");
            }
            x_temp = cola_x[i];
            y_temp = cola_y[i];
            // Insertamos los valores en la matriz de padres
            // Realizamos una comprobacion de errores que no es necesaria pero nunca esta de mas
            // Si en el punto hay algo diferente a un 0 no debemos sobreescribirlo
            if(matriz_padres[x_temp][y_temp][0] > 0){
                
                if(DEBUG){
                    printf("Error, algo ha salido mal en la inserccion de matriz de padres\n");
                }
                return 0; // Error, algo ha salido mal y lo indicamos
            }
            else{
                if(DEBUG){
                    printf("Exito al insertar en la matriz de padres.\n");
                }
                // Si no hay nada, lo insertamos
                matriz_padres[x_temp][y_temp][0]=iteraccion;          // Los pasos que hemos dado para llegar ahi
                matriz_padres[x_temp][y_temp][1]=y_padre;             // La coordenada x del punto padre (el punto que hemos llegado de)
                matriz_padres[x_temp][y_temp][2]=x_padre;             // La coordenada y del punto padre (el punto que hemos llegado de)
                return 1;                                               // Significa que todo ha ido bien
            }// FIN else
        }// FIN IF
    }// FIN FOR
    
    
}// FIN FUNCION insertar_matriz_padres



//----------------------------------------------------------------------------------------------------------------------
// Funcion mostrar_ruta
//----------------------------------------------------------------------------------------------------------------------
// Funcion que se llama una vez acabada la ejecucion y reconstruye el camino desde la meta hasta el punto inicial
// Usa la matriz de padres para reconstruir el camino
//----------------------------------------------------------------------------------------------------------------------
// PARAMETROS
//      matriz_padres: matriz de los padres donde esta la informacion
//      x_inicio: coordenada x del punto final
//      y_inicio: coordenada y del punto final
//      N: tamaño del tablero
//      contador_saltos: contador de saltos que se realizan para llegar a la salida
//----------------------------------------------------------------------------------------------------------------------

int mostrar_ruta(int ***matriz_padres, int x, int y, int N, int contador_saltos){

    int i,j;
    
    /*
    if(DEBUG){
        fprintf(stdout,"\n\nLa matriz:\n");
        for(i=0;i<N;++i){
            for(j=0;j<N;++j){
                printf("%d,%d    ", matriz_padres[i][j][1], matriz_padres[i][j][2]);
            }
            printf("\n");
        }
    }
    printf("----------------\n");
    */
    
    if((matriz_padres[x][y][1] < 0) && (matriz_padres[x][y][2] < 0)){
        fprintf(stdout,"%d,%d",x, y);
        fprintf(stdout,"\n-------------------------\n");
        fprintf(stdout,"El numero de saltos ha sido: %d\n", contador_saltos);
        return 0;
    }
    else{
        fprintf(stdout,"%d,%d <- ",x, y);
        contador_saltos++;
        mostrar_ruta(matriz_padres, matriz_padres[x][y][2], matriz_padres[x][y][1], N, contador_saltos);
    }
}





//----------------------------------------------------------------------------------------------------------------------
// Funcion contar_buffer
//----------------------------------------------------------------------------------------------------------------------
// Funcion que cuenta los elementos que hay en el buffer
//----------------------------------------------------------------------------------------------------------------------
// PARAMETROS
//      cola_x: cola de coordenadas x
//      cola_y: cola de coordenadas y
//      N: tamaño del tablero
//----------------------------------------------------------------------------------------------------------------------

int contar_buffer(int *cola_x, int *cola_y, int N){

    int tam_cola = N*N, i, numero_elementos = 0;

    for(i=0;i<tam_cola;++i)
    {
        if((cola_x[i] >= 0) && (cola_y[i] >= 0))
        {
            numero_elementos++;
            //if(DEBUG){
            //    printf(" ->Incremento contador buffer\n");
            //}
        }
    }

    return numero_elementos;
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
    int *posibles_destinosx;   //En esta matriz vamos a almacenar los posibles destinos
    int *posibles_destinosy;   //En esta matriz vamos a almacenar los posibles destinos 
    int *posibles_destinos_padres_x; //En esta matriz vamos a almacenar los posibles destinos padres
    int *posibles_destinos_padres_y; //En esta matriz vamos a almacenar los posibles destinos padres 
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
    int devueltos_consultados;  // Contador de los devueltos consultados por la funcion que calcula a cuales se puede ir
    int *nada;
    int while_contador = 0;

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
    fprintf(stdout, "-> Tablero de %dx%d posiciones. (De 0 a %d)\n", N, N, N-1);
    fprintf(stdout, "-> Posicion final del caballo: (%d,%d)\n", x1-1, y1-1);
    // Se genera el array de obstaculos con calloc
    vector_obstaculos = (int *)calloc(N*N, sizeof(int));
    // Se genera el array de obstaculos aleatoriamente
    
    // Se imprime el array de obstaculos

    if(DEBUG){
        fprintf(stdout, "Obstaculos:\n");
        imprime_obstaculos(N*N, vector_obstaculos);
    }
        
    

    // Se reserva memoria para la matriz del tablero
    //solicitamos la memoria con calloc para la matriz en funcion de los argumentos que nos pase el usuario
    matriz_tablero = (int **)calloc(N, sizeof(int *));
    for(int i = 0; i < N; i++){
        matriz_tablero[i] = (int *)calloc(N, sizeof(int));
    }

    //Limpiamos la tabla poniendo todos sus valores a 0
    limpia_tablero(N, *matriz_tablero);
    
    //Imprimimos la matriz del tablero
    if(DEBUG){
        fprintf(stdout, "Tablero sin obstaculos:\n");
        imprime_tablero(N, matriz_tablero);
    }

    

    //Pasamos los obstaculos (cuando haya un 1 en el array de obstaculos) a la matriz del tablero
    /*
    for(i=0; i<N*N; i++){
        if(vector_obstaculos[i] == 1){
            matriz_tablero[i/N][i%N] = 1;
        }
    }
    */

    // Se reserva memoria para la matriz de visitados
    matriz_visitados = (int **)calloc(N, sizeof(int *));
    for(i = 0; i < N; i++){
        matriz_visitados[i] = (int *)calloc(N, sizeof(int));
    }

    genera_obstaculos(N, matriz_tablero, matriz_visitados);

    //Imprimimos la matriz del tablero
    fprintf(stdout, "Tablero con obstaculos:\n");
    imprime_tablero(N, matriz_tablero);


    

    // Se reserva memoria para la matriz de padres
    matriz_padres = (int ***)calloc(N, sizeof(int **));
    for(i = 0; i < N; i++){
        matriz_padres[i] = (int **)calloc(N, sizeof(int *));
        for(j = 0; j < N; j++){
            matriz_padres[i][j] = (int *)calloc(3, sizeof(int));
        }
    }

    //

    //recorremos toda la matriz de padres para ponerle los valores a 0
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            for(k=0; k<3; k++){
                matriz_padres[i][j][k] = -1;
            }
        }
    } 

    //Reservamos memoria para la cola de posibles destinos
    // Vamos a reservar n*n posiciones para los posibles destinos
    // De esta forma podriamos guardar toda la matriz sin procesar si hiciese falta.
    posibles_destinosx = (int *)calloc(N*N, sizeof(int));
    posibles_destinosy = (int *)calloc(N*N, sizeof(int));
    posibles_destinos_padres_x = (int *)calloc(N*N, sizeof(int));
    posibles_destinos_padres_y = (int *)calloc(N*N, sizeof(int));

    // ponemos en estos dos vectores valores negativos para indicar que estan libres.
    for(j=0; j<N*N; j++){
        posibles_destinosx[j] = -1;
        posibles_destinosy[j] = -1;
        posibles_destinos_padres_x[j] = -1;
        posibles_destinos_padres_y[j] = -1;
    }
    
    
    
    //----------------------------------------------------------------------------------------------------------------------
    //COMIENZO DEL ALGORITMO
    //----------------------------------------------------------------------------------------------------------------------

    fprintf(stdout, "\nComienza el algoritmo...\n");

    // Ponemos la casilla de salida como visitada
    matriz_visitados[x0][y0] = 1;

    // introducimos la casilla de inicio en la cola
    //int insertar_cola(int x, int y, int *cola_x, int *cola_y, int N){
    insertar_cola(x0, y0, posibles_destinosx, posibles_destinosy, N);
    // Y lo marcamos como que ya ha sido visitado
    matriz_visitados[x0][y0] = 1;

    iteraciones++;


    if(DEBUG){
        fprintf(stdout, "El valor de flag_continuar es %d .\n", flag_continuar);
        fprintf(stdout, "Se ha cargado la posicion inicial y se procede al bucle.\n");
    }
    

    // hacemos esto hasta que la bandera este a FALSE
    while(flag_continuar){

        // Extraemos el primer valor de la cola y los guardamos en vars temporales
        x_temporal = posibles_destinosx[0];
        y_temporal = posibles_destinosy[0];

        //int extraer_cola( int *cola_x, int *cola_y, int *x,int *y, int N){
        extraer_cola(posibles_destinosx, posibles_destinosy, &x_temporal, &y_temporal, N);

        if(DEBUG){
            fprintf(stdout, "Iteracion %d\n", iteraciones);
            fprintf(stdout, "Se ha extraido la casilla %d,%d\n", x_temporal, y_temporal);
        }


        // Calculamos a las posiciones que se pueden ir desde la casilla que acabamos de extraer
        // int comprobar_posibles_destinos(int N, int **tablero, int x, int y, int *cola_x, int *cola_y, int **matriz_visitados){
        devueltos_consultados=comprobar_posibles_destinos(N, matriz_tablero, x_temporal, y_temporal, posibles_destinosx, posibles_destinosy, matriz_visitados);

        for(int g=0; g<devueltos_consultados; g++){
            //int insertar_cola(int x, int y, int *cola_x, int *cola_y, int N){
            insertar_cola(x_temporal, y_temporal, posibles_destinos_padres_x, posibles_destinos_padres_y, N);
        }

        if(DEBUG){
            fprintf(stdout, "Se han devuelto %d posibles destinos.\n", devueltos_consultados);
        }
        
        //Insertamos en la matriz de padres los valores de la cola
        //int insertar_matriz_padres(int x_padre, int y_padre, int ***matriz_padres, int iteraccion, int *cola_x, int *cola_y,int N){
        insertar_matriz_padres(posibles_destinos_padres_x[while_contador], posibles_destinos_padres_y[while_contador], matriz_padres, iteraciones, posibles_destinosx, posibles_destinosy, N);

        //Comprobamos si es la meta el punto en el que estamos, ya que si estamos tenemos que acabar el bucle
        if(comprueba_meta(x_temporal, y_temporal, N-1, N-1)){
            // Ponemos la flag a cero
            fprintf(stdout, "\n-> Se ha encontrado la meta. <-\n");
            flag_continuar = 0;     // Finalizamos
        }

        // comprobamos el tamanio del vector de ocupados de la cola, ya que esto es otra condicion de parada.
        if(contar_buffer(posibles_destinosx, posibles_destinosy, N) == 0){
            flag_continuar = 0;
        }
        

        if(DEBUG){
            fprintf(stdout, "\n\nMatriz visitados:\n");
            for(i=0; i<N; i++){
                for(j=0; j<N; j++){
                    fprintf(stdout, "%d ", matriz_visitados[i][j]);
                }
                fprintf(stdout, "\n");
            }

            fprintf(stdout, "Matriz padres\n");
            fprintf(stdout, "-------------------------\n");
            for(int q=0; q<N; q++){
                for(int w=0; w<N; w++){
                    fprintf(stdout, "%d,%d\t", matriz_padres[q][w][1], matriz_padres[q][w][2]);
                }
                fprintf(stdout, "\n");
            }
            fprintf(stdout, "-------------------------\n");
            fprintf(stdout, "El valor de flag_continuar es %d .\n", flag_continuar);
            fprintf(stdout, "El buffer\n");
            for(int k=0; k<N*N; k++){
                fprintf(stdout, "%d,%d\t", posibles_destinosx[k], posibles_destinosy[k]);
            }
            fprintf(stdout, "\n");
            
        }


        // Incrementamos la iteracion
        iteraciones++;      // Las iteracciones que llevamos/pasos hasta este punto
        while_contador++;   // El contador de bucle while
        

        //Si estamos en modo depuracion en cada iteraccion debemos presionar intro
        if(DEBUG){
            printf("Pulsa intro para seguir\n");
            int c = getchar();
        }
        
    }//END WHILE


    // int reconstruir_camino(int ***matriz_padres, int **ruta, int x_destino, int y_destino, int iteraccion)
    // Reconstruimos la ruta

    if(DEBUG){
        // Comprobamos si hay padre de la casilla de destino
        fprintf(stdout, "Matriz padres\n");
        fprintf(stdout, "-------------------------\n");
        for(int q=0; q<N; q++){
            for(int w=0; w<N; w++){
                fprintf(stdout, "%d\t", matriz_padres[q][w][0]);
            }
            fprintf(stdout, "\n");
        }
        fprintf(stdout, "1\t2\t3\t4\t5\t6\t7\t8\t9\n");
        fprintf(stdout, "-------------------------------------------------------------------\n");

        for(int q=0; q<N; q++){
            for(int w=0; w<N; w++){
                fprintf(stdout, "%d,%d\t", matriz_padres[q][w][1], matriz_padres[q][w][2]);

            }
            fprintf(stdout, "\n");
        }
        fprintf(stdout, "-------------------------\n");
        

        fprintf(stdout, "Matriz visitados\n");
        fprintf(stdout, "-------------------------\n");
        for(int q=0; q<N; q++){
            for(int w=0; w<N; w++){
                fprintf(stdout, "%d\t", matriz_visitados[q][w]);
            }
            fprintf(stdout, "\n");
        }
    }

    
    fprintf(stdout, "\n-------------------------\n");
    fprintf(stdout, "\nSOLUCION:\n");
    
    if(matriz_padres[N-1][N-1][0] < 0){
        fprintf(stdout, "No hay camino posible\n");
        return 0;
    } 
    else{
        // Si hay padre, reconstruimos la ruta
        //reconstruir_camino(matriz_padres, ruta_seguida, N-1, N-1, N);
        fprintf(stdout, "La ruta desde N,N hasta 0,0 es:\n");
        
        //int mostrar_ruta(int ***matriz_padres, int x, int y){
        mostrar_ruta(matriz_padres, N-1, N-1, N, 0);
        printf("\n");
    }


    /*

     int **matriz_visitados;     // Matriz de visitados 0 si no ha sido visitado, 1 si si lo ha sido
    int *vector_obstaculos;     // Vector que contiene los obstaculos del tablero
    int **matriz_tablero;       //Matriz que vamos a usar en funcion de las posiciones que nos pase el usuario. Es un puntero a punteros de enteros
    int *posibles_destinosx;   //En esta matriz vamos a almacenar los posibles destinos
    int *posibles_destinosy;   //En esta matriz vamos a almacenar los posibles destinos 
    int *posibles_destinos_padres_x; //En esta matriz vamos a almacenar los posibles destinos padres
    int *posibles_destinos_padres_y; //En esta matriz vamos a almacenar los posibles destinos padres 
    int ***matriz_padres
    */
    

   //Liberamos la memoria de la matriz_visitados
    for(i=0; i<N; i++){
        free(matriz_visitados[i]);
    }
    free(matriz_visitados);
    //liberamos la memoria del vector_obstaculos
    free(vector_obstaculos);
    //liberamos la memoria de la matriz_tablero

    free(matriz_tablero);
    //liberamos la memoria del vector posibles_destinosx
    free(posibles_destinosx);
    //liberamos la memoria del vector posibles_destinosy
    free(posibles_destinosy);
    //liberamos la memoria del vector posibles_destinos_padres_x
    free(posibles_destinos_padres_x);
    //liberamos la memoria del vector posibles_destinos_padres_y
    free(posibles_destinos_padres_y);
    //liberamos la memoria de la matriz_padres
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            free(matriz_padres[i][j]);
        }
        free(matriz_padres[i]);
    }
    free(matriz_padres);

    






}
