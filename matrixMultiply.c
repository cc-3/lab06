#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

/*
    Para ahorrar tiempo, les hemos incluido 6 variantes de ciclo donde
    solo se ha cambiado el orden solamente (ejmplo ijk, kji, ikj, ... etc) y
    las hemos puesto como funciones y despues las llamamos usando punteros de
    funciones. El motivo de que esten por separado las funciones es para evitar
    contar procesos extraños durante el computo de la multiplicacion de
    matrices. Esto incluye I/O (printf) y condicionales (if/switch). Los
    accesos a I/O como los saltos y condicionales pueden cambiar drasticamente
    los resultados en tiempo.
*/

void multMat1( int n, float *A, float *B, float *C ) {
    int i,j,k;
    /* ijk */
    for( i = 0; i < n; i++ )
        for( j = 0; j < n; j++ )
            for( k = 0; k < n; k++ )
                C[i+j*n] += A[i+k*n]*B[k+j*n];
}

void multMat2( int n, float *A, float *B, float *C ) {
    int i,j,k;
    /* ikj */
    for( i = 0; i < n; i++ )
        for( k = 0; k < n; k++ )
            for( j = 0; j < n; j++ )
                C[i+j*n] += A[i+k*n]*B[k+j*n];
}

void multMat3( int n, float *A, float *B, float *C ) {
    int i,j,k;
    /* jik */
    for( j = 0; j < n; j++ )
        for( i = 0; i < n; i++ )
            for( k = 0; k < n; k++ )
                C[i+j*n] += A[i+k*n]*B[k+j*n];
}

void multMat4( int n, float *A, float *B, float *C ) {
    int i,j,k;
    /* jki */
    for( j = 0; j < n; j++ )
        for( k = 0; k < n; k++ )
            for( i = 0; i < n; i++ )
                C[i+j*n] += A[i+k*n]*B[k+j*n];
}

void multMat5( int n, float *A, float *B, float *C ) {
    int i,j,k;
    /* kij */
    for( k = 0; k < n; k++ )
        for( i = 0; i < n; i++ )
            for( j = 0; j < n; j++ )
                C[i+j*n] += A[i+k*n]*B[k+j*n];
}

void multMat6( int n, float *A, float *B, float *C ) {
    int i,j,k;
    /* kji */
    for( k = 0; k < n; k++ )
        for( j = 0; j < n; j++ )
            for( i = 0; i < n; i++ )
                C[i+j*n] += A[i+k*n]*B[k+j*n];
}

// Esto es el default para la parte 1. Para la parte 2 pueden pasarle
// argumentos

// ** Este codigo utiliza algunas caracteristicas que ustedes jamas han visto
// seria genial que las estudien como el timing y asi
int main( int argc, char **argv ) {
    int nmax = 1000,i,n;

    // Arreglo de funciones (super weird xd)
    void (*orderings[])(int,float *,float *,float *) =
        {&multMat1,&multMat2,&multMat3,&multMat4,&multMat5,&multMat6};
    char *names[] = {"ijk","ikj","jik","jki","kij","kji"};

    float *A = (float *)malloc( nmax*nmax * sizeof(float));
    float *B = (float *)malloc( nmax*nmax * sizeof(float));
    float *C = (float *)malloc( nmax*nmax * sizeof(float));

    struct timeval start, end;

    if( argv[1] ) {
        printf("Corriendo parte B...\n\n");

        /* Llenamos las matrices con numeros random */
        for( i = 0; i < nmax*nmax; i++ ) A[i] = drand48()*2-1;
        for( i = 0; i < nmax*nmax; i++ ) B[i] = drand48()*2-1;
        for( i = 0; i < nmax*nmax; i++ ) C[i] = drand48()*2-1;

        for( i = 0; i < 6; i++) {
            /* Multiplicamos y medimos el tiempo */
            gettimeofday( &start, NULL );
            (*orderings[i])( nmax, A, B, C );
            gettimeofday( &end, NULL );

            /* convertimos el tiempo a Gflop/s */
            double seconds = (end.tv_sec - start.tv_sec) +
                1.0e-6 * (end.tv_usec - start.tv_usec);
            double Gflops = 2e-9*nmax*nmax*nmax/seconds;
            printf( "%s:\tn = %d, %.3f Gflop/s\n", names[i], nmax, Gflops );
        }
    } else {
        printf("Corriendo parte A...\n\n");
        // Aqui solo se prueba el orden ijk en diferentes tamanos de matriz
        for( n = 10; n <= nmax; n = n<nmax && n+1+n/3>nmax ? nmax : n+1+n/3 ) {
            /* Llenamos las matrices con numeros random */
            for( i = 0; i < n*n; i++ ) A[i] = drand48()*2-1;
            for( i = 0; i < n*n; i++ ) B[i] = drand48()*2-1;
            for( i = 0; i < n*n; i++ ) C[i] = drand48()*2-1;

            /* Multiplicamos y medimos el tiempo */
            gettimeofday( &start, NULL );
            multMat1( n, A, B, C );
            gettimeofday( &end, NULL );

            /* convertimos el tiempo a Gflop/s */
            double seconds = (end.tv_sec - start.tv_sec) +
                1.0e-6 * (end.tv_usec - start.tv_usec);
            double Gflops = 2e-9*n*n*n/seconds;
            printf( "n = %d, %.3f Gflop/s\n", n, Gflops );
        }
    }

    // Liberamos la memoria

    free( A );
    free( B );
    free( C );

    printf("\n\n");

    return 0;
}
