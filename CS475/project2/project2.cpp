#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

// setting the number of threads:       
#ifndef NUMT
#define NUMT		    2
#endif

// setting the number of nodes:         
#ifndef NUMNODES
#define NUMNODES	4
#endif

// how many tries to discover the maximum performance:
#ifndef NUMTRIES
#define NUMTRIES	10
#endif

#define XMIN     -1.
#define XMAX      1.
#define YMIN     -1.
#define YMAX      1.

#define N	0.70

// function prototypes:
float		Ranf( float, float );
int		Ranf( int, int );
void		TimeOfDaySeed( );
float Height( int, int );	


int main( int argc, char *argv[ ] )
{
#ifndef _OPENMP
	fprintf( stderr, "No OpenMP support!\n" );
	return 1;
#endif

	TimeOfDaySeed( );		// seed the random number generator

	omp_set_num_threads( NUMT );	// set the number of threads to use in parallelizing the for-loop:
		
	// the area of a single full-sized tile:
	// (not all tiles are full-sized, though)

	float fullTileArea = (  ( ( XMAX - XMIN )/(float)(NUMNODES-1) )  *
				( ( YMAX - YMIN )/(float)(NUMNODES-1) )  );
	
	// sum up the weighted heights into the variable "volume"
	// using an OpenMP for loop and a reduction:

	float volume = 0;

	double time0 = omp_get_wtime();

	#pragma omp parallel for default(none), shared(fullTileArea), reduction(+:volume)
	for( int i = 0; i < NUMNODES*NUMNODES; i++ )
	{
		int iu = i % NUMNODES;
		int iv = i / NUMNODES;
		float z = Height( iu, iv );

		bool uEdge = iu == 0 || iu == NUMNODES - 1;
		bool vEdge = iv == 0 || iv == NUMNODES - 1;

		// Tiles in the corners
		if( uEdge && vEdge )
		{
			volume += (fullTileArea / 4) * z;
		}
		// Tiles on the edges
		else if( uEdge || vEdge)
		{
			volume += (fullTileArea / 2) * z;
		}
		// Tiles in the middle
		else
		{
			volume += fullTileArea * z;
		}
	}
	double time1 = omp_get_wtime( );

	double megaHeights = (double)(NUMNODES*NUMNODES)/(time1-time0)/1000000.;

	fprintf(stderr, "%2d threads : %8d nodes ; volume = %8.3lf ; megaHeights/sec = %6.2lf\n",
		NUMT, NUMNODES, volume, megaHeights);

	FILE *fp;
    fp = fopen("project2_performance.csv", "a");
    fprintf(fp, ",%.2lf",megaHeights);
    fclose(fp);

    fp = fopen("project2_volume.csv", "a");
    fprintf(fp, ",%.3lf", volume);
    fclose(fp);
	return 0;
}

float
Height( int iu, int iv )	// iu,iv = 0 .. NUMNODES-1
{
	float x = -1.  +  2.*(float)iu /(float)(NUMNODES-1);	// -1. to +1.
	float y = -1.  +  2.*(float)iv /(float)(NUMNODES-1);	// -1. to +1.

	float xn = pow( fabs(x), (double)N );
	float yn = pow( fabs(y), (double)N );
	float r = 1. - xn - yn;
	if( r <= 0. )
	        return 0.;
	float height = pow( r, 1./(float)N );
	return height;
}

float
Ranf( float low, float high )
{
        float r = (float) rand();               // 0 - RAND_MAX
        float t = r  /  (float) RAND_MAX;       // 0. - 1.

        return   low  +  t * ( high - low );
}

int
Ranf( int ilow, int ihigh )
{
        float low = (float)ilow;
        float high = ceil( (float)ihigh );

        return (int) Ranf(low,high);
}

// call this if you want to force your program to use
// a different random number sequence every time you run it:
void
TimeOfDaySeed( )
{
	struct tm y2k = { 0 };
	y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
	y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;

	time_t  timer;
	time( &timer );
	double seconds = difftime( timer, mktime(&y2k) );
	unsigned int seed = (unsigned int)( 1000.*seconds );    // milliseconds
	srand( seed );
}
