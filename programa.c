
#define FALSE 0
#define TRUE 1


//Con esta funcion comprobamos todos los posibles destinos a los que podemos ir desde un punto dado.

int calcular_posibles_destinos(int n, int tablero[][],int x,int y, int cola[] ){
    int posible_mover=FALSE;

    int x_temp;
    int y_temp;

    int posibles_destinos[8][2];

    int vecto_movimientos[8][2]= {{1,2},{2,1},{2,-1},{1,-2},{-1,2},{-2,1},{-2,-1},{-1,-2}};

    for(int i=0;i<8;++i)
    {
        x_temp = x +vecto_movimientos[i][0];
        y_temp = y + vecto_movimientos[i][1];

        if(es_posible(n,x_temp,y_temp,tablero)){
            posibles_destinos[i][0]= x_temp;
            posibles_destinos[i][1]=y_temp;
        }        
    }

    if(posible_mover!=FALSE)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

//Esta funcion ayuda a la anterior a saber si un punto es un obstaculo o si esta dentro del rango de NxN

int es_posible(int n, int x,int y, int tablero[][]){
    if((x<0) || (y<0) ||  (x>=n) || y>=n)
    {
        return FALSE;
    }
    else{

        if(tablero[x][y]==1){
            return FALSE;
        }
        else{
            return TRUE;
        }
    }
}

//Esta funcion comprueba si ya ha sido visitado para si poderlo ingnorar

int comprueba_visitado(int x, int y, int tabla_visitados[][]){

    if(tabla_visitados[x][y]==NULL)
    {
        return FALSE;
    }
    else{
        return TRUE;
    }
}

//Esta funcion extrae de la cola y mueve al resto una posicion menos para que no se quede con el primer elemento vacio

int extrae_cola( int n,int cola[n], int *x,int *y){
    
    x= cola[0];
    y= cola[1];

    for(int i=0;i<n-1;++i)
    {
        //Sin acabar
    }
}

//Con esta funcion guardamos en la matriz NxNx2 los datos

void guardar_recorrido(int interaccion,int posicion_x,int posicion_y, int padre_x, int padre_y,int tabla_ruta[][][],int tablero [][]){

    tabla_ruta[posicion_x][posicion_y][0]= interaccion;
    tabla_ruta[posicion_x][posicion_y][1]= padre_x;
    tabla_ruta[posicion_x][posicion_y][2]= padre_y;

    tablero[posicion_x][posicion_y] =1;
}

//Esta funcion comprueba si se ha llegado a la meta

int comprueba_meta(int x,int y, int meta_x,int meta_y){
    if((x==meta_x) && (y==meta_y))
    {
        return TRUE;
    }else{
        return FALSE;
    }
}


//Esta funcion inserta un elemento en la cola. La recorremos hasta encontrarnos un NULL, que es donde insertaremos los nuevos valores. 0 para exito, 1 para error.

int insertar_cola(int x, int y, int cola[],int n){
    for(int i=0;i<n*n;++i)
    {
        if(cola[i]==NULL)
        {
            if(cola[i+1])
            {
                cola[i]=x;
                cola[i+1]=y;
                return FALSE;
            }
            else{
                return TRUE;
            }
        }
    }
}