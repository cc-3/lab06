#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

void transpose( int n, int blocksize, int *dst, int *src ) {
    int i,j;
    /*
        TODO:
        Implementar blocking (agregar 2 ciclos mas)
    */
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            dst[j + i*n] = src[i + j*n];
}

int main( int argc, char **argv ) {
    int n = 2000,i,j;
    int blocksize = 20; /* TODO: encontrar un tamano de bloque mejor */

    /* reservar un bloque de memoria de nxn de numeros enteros*/
    int *A = (int*)malloc( n*n*sizeof(int) );
    int *B = (int*)malloc( n*n*sizeof(int) );

    /* inicializamos A y B con numeros random */
    srand48( time( NULL ) );
    for( i = 0; i < n*n; i++ ) A[i] = lrand48( );
    for( i = 0; i < n*n; i++ ) B[i] = lrand48( );

    /* medimos el performance */
    struct timeval start, end;

    gettimeofday( &start, NULL );
    transpose( n, blocksize, B, A );
    gettimeofday( &end, NULL );

    double seconds = (end.tv_sec - start.tv_sec) +
        1.0e-6 * (end.tv_usec - start.tv_usec);
    printf( "%g ms\n", seconds*1e3 );

    /* Verificamos que la respuesta sea correcta */
    for( i = 0; i < n; i++ )
        for( j = 0; j < n; j++ )
            if( B[j+i*n] != A[i+j*n] ) {
                printf("Error!!!! La transpuesta no es correcta!!\n");
                exit( -1 );
            }

    /* liberamos la memoria */
    free( A );
    free( B );
    return 0;
}
