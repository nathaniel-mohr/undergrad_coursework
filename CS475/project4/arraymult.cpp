#include "simd.p5.h"

#ifndef SIZE
#define SIZE       	1000
#endif
#ifndef NUMT
#define NUMT		    2
#endif
#define NUMTRIES        20

#define NUM_ELEMENTS_PER_CORE SIZE/NUMT

unsigned int seed = 0;

float A[SIZE];
float B[SIZE];
float C[SIZE];

float	Ranf( unsigned int*, float, float );
void    fill_array(float*, int);

int
main( )
{
    FILE* fp;

    omp_set_num_threads(NUMT);

    fill_array(A, SIZE);
    fill_array(B, SIZE);

    printf("Array size: %d, NumThreads: %d\n", SIZE, NUMT);

    printf("Non-SIMD Multiply\n");

    double peakTime = 0.;
    double sumTime = 0.;
    double avgTime = 0.;

    for( int t = 0; t < NUMTRIES; t++ )
    {
        double time0 = omp_get_wtime( );

        #pragma omp parallel
        {
            int first = omp_get_thread_num() * NUM_ELEMENTS_PER_CORE;
            NonSimdMul(&A[first], &B[first], &C[first], NUM_ELEMENTS_PER_CORE);
        }

        double time1 = omp_get_wtime( );
        double elapsedTime = SIZE/(time1-time0)/1000000.;

        sumTime += elapsedTime;
        if( elapsedTime > peakTime )
            peakTime = elapsedTime;
    }
    printf( "Peak Performance = %8.2lf\n", peakTime );
    
    avgTime = sumTime/(double)NUMTRIES;
    printf( "Average Performance = %8.2lf\n\n", avgTime);

    fp = fopen("nsmTime.csv", "a");
    fprintf(fp, ",%.2lf", peakTime);
    fclose(fp);

    

    printf("SIMD Multiply\n");
    peakTime = 0.;
    sumTime = 0.;

    for( int t = 0; t < NUMTRIES; t++ )
    {
        double time0 = omp_get_wtime( );

        #pragma omp parallel
        {
            int first = omp_get_thread_num() * NUM_ELEMENTS_PER_CORE;
            SimdMul(&A[first], &B[first], &C[first], NUM_ELEMENTS_PER_CORE);
        }
        
        double time1 = omp_get_wtime( );
        double elapsedTime = SIZE/(time1-time0)/1000000.;

        sumTime += elapsedTime;
        if( elapsedTime > peakTime )
            peakTime = elapsedTime;
    }
    printf( "Peak Performance = %8.2lf\n", peakTime );
    avgTime = sumTime/(double)NUMTRIES;
    printf( "Average Performance = %8.2lf\n\n", avgTime);

    fp = fopen("smTime.csv", "a");
    fprintf(fp, ",%.2lf", peakTime);
    fclose(fp);



    printf("Non-SIMD MultSum\n");
    peakTime = 0.;
    sumTime = 0.;

    for( int t = 0; t < NUMTRIES; t++ )
    {
        double time0 = omp_get_wtime( );

        #pragma omp parallel
        {
            int first = omp_get_thread_num() * NUM_ELEMENTS_PER_CORE;
            float sum = NonSimdMulSum(&A[first], &B[first], NUM_ELEMENTS_PER_CORE);
        }
        
        double time1 = omp_get_wtime( );
        double elapsedTime = SIZE/(time1-time0)/1000000.;

        sumTime += elapsedTime;
        if( elapsedTime > peakTime )
            peakTime = elapsedTime;
    }
    printf( "Peak Performance = %8.2lf\n", peakTime );
    avgTime = sumTime/(double)NUMTRIES;
    printf( "Average Performance = %8.2lf\n\n", avgTime);

    fp = fopen("nsmsTime.csv", "a");
    fprintf(fp, ",%.2lf", peakTime);
    fclose(fp);



    printf("SIMD MultSum\n");
    peakTime = 0.;
    sumTime = 0.;

    for( int t = 0; t < NUMTRIES; t++ )
    {
        double time0 = omp_get_wtime( );

        #pragma omp parallel
        {
            int first = omp_get_thread_num() * NUM_ELEMENTS_PER_CORE;
            float sum = SimdMulSum(&A[first], &B[first], NUM_ELEMENTS_PER_CORE);
        }
        
        double time1 = omp_get_wtime( );
        double elapsedTime = SIZE/(time1-time0)/1000000.;

        sumTime += elapsedTime;
        if( elapsedTime > peakTime )
            peakTime = elapsedTime;
    }
    printf( "Peak Performance = %8.2lf\n", peakTime );
    avgTime = sumTime/(double)NUMTRIES;
    printf( "Average Performance = %8.2lf\n\n", avgTime);

    fp = fopen("smsTime.csv", "a");
    fprintf(fp, ",%.2lf", peakTime);
    fclose(fp);

    return 0;
}


void	
NonSimdMul( float *a, float *b,  float *c, int len)
{
    for(int i = 0; i < len; i++)
    {
        c[i] = a[i] * b[i];
    }
}

float
NonSimdMulSum( float *a, float *b, int len)
{
    float sum = 0;
    for(int i = 0; i < len; i++)
    {
        sum += a[i] * b[i];
    }
    return sum;
}

float
Ranf( unsigned int *seedp,  float low, float high )
{
    float r = (float) rand_r( seedp );              // 0 - RAND_MAX

    return(   low  +  r * ( high - low ) / (float)RAND_MAX   );
}

void
fill_array(float *array, int size)
{
    for(int i = 0; i < size; i++)
    {
        array[i] = Ranf(&seed, -1, 1);
    }
}

/*
    double peakTime = 0.;
    double sumTime = 0.;
    double avgTime = 0.;

    for( int t = 0; t < NUMTRIES; t++ )
    {
        double time0 = omp_get_wtime( );

        NonSimdMul(A,B,C,SIZE);

        double time1 = omp_get_wtime( );
        double elapsedTime = SIZE/(time1-time0)/1000000.;

        sumTime += elapsedTime;
        if( elapsedTime > peakTime )
            peakTime = elapsedTime;
    }
    printf( "Peak Performance = %8.2lf\n", peakTime );
    
    avgTime = sumTime/(double)NUMTRIES;
    printf( "Average Performance = %8.2lf\n\n", avgTime);
*/
