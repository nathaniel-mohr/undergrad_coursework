#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

unsigned int seed = 0;

// Step Constants
const float GRAIN_GROWS_PER_MONTH =		9.0;
const float ONE_DEER_EATS_PER_MONTH =		1.0;
const float ONE_PEASANT_PLANTS_PER_MONTH = .1;

const float AVG_PRECIP_PER_MONTH =		7.0;	// average
const float AMP_PRECIP_PER_MONTH =		6.0;	// plus or minus
const float RANDOM_PRECIP =			2.0;	// plus or minus noise

const float AVG_TEMP =				60.0;	// average
const float AMP_TEMP =				20.0;	// plus or minus
const float RANDOM_TEMP =			10.0;	// plus or minus noise

const float MIDTEMP =				40.0;
const float MIDPRECIP =				10.0;

// State Variables
int	NowYear;		// 2021 - 2026
int	NowMonth;		// 0 - 11

float	NowPrecip;		// inches of rain per month
float	NowTemp;		// temperature this month
float	NowHeight;		// grain height in inches
int	    NowNumDeer;		// number of deer in the current population
int     NowNumPeasants; // number of peasants in the current population

// Function Prototypes
void    Deer();
void    Grain();
void    Watcher();
void    Peasant();
float	Ranf( unsigned int*, float, float );
int		Ranf( unsigned int*,  int, int );
float   SQR( float x );
void    DateGen();

// main program:
int
main( int argc, char *argv[ ] )
{
#ifndef _OPENMP
	fprintf( stderr, "No OpenMP support!\n" );
	return 1;
#endif

    // starting date and time:
    NowMonth =    0;
    NowYear  = 2021;

    // starting state (feel free to change this if you want):
    NowNumDeer = 5;
    NowNumPeasants = 10;
    NowHeight =  12.;

    omp_set_num_threads( 4 );	// same as # of sections    
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            Deer( );
        }

        #pragma omp section
        {
            Grain( );
        }

        #pragma omp section
        {
            Watcher( );
        }

        #pragma omp section
        {
            Peasant( );	// your own
        }
    }   // implied barrier -- all functions must return in order
        // to allow any of them to get past here

}

void Deer()
{
    while( NowYear < 2027 )
    {
        // compute a temporary next-value for this quantity
        // based on the current state of the simulation:

        int nextNumDeer = NowNumDeer;
        int carryingCapacity = (int)( NowHeight );
        if( nextNumDeer < carryingCapacity )
                nextNumDeer++;
        else
                if( nextNumDeer > carryingCapacity )
                        nextNumDeer--;

        if( nextNumDeer < 0 )
                nextNumDeer = 0;

        // DoneComputing barrier:
        #pragma omp barrier

        NowNumDeer = nextNumDeer;

        // DoneAssigning barrier:
        #pragma omp barrier

        // DonePrinting barrier:
        #pragma omp barrier
    }
}

void Grain()
{
    while( NowYear < 2027 )
    {
        // compute a temporary next-value for this quantity
        // based on the current state of the simulation:

        float tempFactor = exp(   -SQR(  ( NowTemp - MIDTEMP ) / 10.  )   );

        float precipFactor = exp(   -SQR(  ( NowPrecip - MIDPRECIP ) / 10.  )   );

        float nextHeight = NowHeight;
        nextHeight += tempFactor * precipFactor * GRAIN_GROWS_PER_MONTH;
        nextHeight -= (float)NowNumDeer * ONE_DEER_EATS_PER_MONTH;
        nextHeight += (float)NowNumPeasants * ONE_PEASANT_PLANTS_PER_MONTH;
        if( nextHeight < 0. ) nextHeight = 0.;

        // DoneComputing barrier:
        #pragma omp barrier

        NowHeight = nextHeight;

        // DoneAssigning barrier:
        #pragma omp barrier

        // DonePrinting barrier:
        #pragma omp barrier
    }
}

void Watcher()
{
    FILE *fp;
    fp = fopen("project3.csv", "a");

    while( NowYear < 2027 )
    {
        // compute a temporary next-value for this quantity
        // based on the current state of the simulation:

        // DoneComputing barrier:
        #pragma omp barrier

        // DoneAssigning barrier:
        #pragma omp barrier

        // Print current state of global variables
        DateGen();
        printf("     Number of Deer:   %d\n",                 NowNumDeer);
        printf(" Number of Peasants:   %d\n",                 NowNumPeasants);
        printf("    Height of Grain:   %.2f inches\n",        NowHeight);
        printf("        Temperature:   %.2f °F\n",            NowTemp);
        printf("      Precipitation:   %.2f inches\n\n\n",    NowPrecip);

        // month, deer, height, temp, precip, (MyAgent)
        int total_month = NowMonth + 12 * (NowYear - 2021) + 1;
        fprintf(fp, "%d, %d, %d, %.2f, %.2f, %.2f\n", total_month, NowNumDeer, NowNumPeasants, NowHeight, NowTemp, NowPrecip);

        // Increase month and (maybe) year
    
        NowMonth++;

        if(NowMonth == 12){
            NowMonth = 0;
            NowYear++;
        }

        // Compute new values

        float ang = (  30.*(float)NowMonth + 15.  ) * ( M_PI / 180. );

        float temp = AVG_TEMP - AMP_TEMP * cos( ang );
        NowTemp = temp + Ranf( &seed, -RANDOM_TEMP, RANDOM_TEMP );

        float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin( ang );
        NowPrecip = precip + Ranf( &seed,  -RANDOM_PRECIP, RANDOM_PRECIP );
        if( NowPrecip < 0. )
            NowPrecip = 0.;

        // DonePrinting barrier:
        #pragma omp barrier
    }
    fclose(fp);
}

void Peasant()
{
    while( NowYear < 2027 )
    {
        // compute a temporary next-value for this quantity
        // based on the current state of the simulation:
        int nextNumPeasants = NowNumPeasants;
        int carryingCapacity = NowNumDeer + NowHeight;
        if( nextNumPeasants < carryingCapacity )
                nextNumPeasants++;
        else
                if( nextNumPeasants > carryingCapacity )
                        nextNumPeasants--;

        if( nextNumPeasants < 0 )
                nextNumPeasants = 0;

        // DoneComputing barrier:
        #pragma omp barrier

        NowNumPeasants = nextNumPeasants;

        // DoneAssigning barrier:
        #pragma omp barrier

        // DonePrinting barrier:
        #pragma omp barrier
    }
}

float
Ranf( unsigned int *seedp,  float low, float high )
{
        float r = (float) rand_r( seedp );              // 0 - RAND_MAX

        return(   low  +  r * ( high - low ) / (float)RAND_MAX   );
}


int
Ranf( unsigned int *seedp, int ilow, int ihigh )
{
        float low = (float)ilow;
        float high = (float)ihigh + 0.9999f;

        return (int)(  Ranf(seedp, low,high) );
}

float
SQR( float x )
{
        return x*x;
}

void
DateGen( )
{
    printf("\t   ");
    switch(NowMonth)
    {
        case 0:
            printf("January");
            break;
        case 1:
            printf("February");
            break;
        case 2:
            printf("March");
            break;
        case 3:
            printf("April");
            break;
        case 4:
            printf("May");
            break;
        case 5:
            printf("June");
            break;
        case 6:
            printf("July");
            break;
        case 7:
            printf("August");
            break;
        case 8:
            printf("September");
            break;
        case 9:
            printf("October");
            break;
        case 10:
            printf("November");
            break;
        case 11:
            printf("December");
            break;
    }
    printf(", %d\n", NowYear);
    printf("----------------------------------\n");
}