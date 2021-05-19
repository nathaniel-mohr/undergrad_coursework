// System includes
#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <math.h>
#include <stdlib.h>

// CUDA runtime
#include <cuda_runtime.h>

// Helper functions and utilities to work with CUDA
#include "helper_functions.h"
#include "helper_cuda.h"


#ifndef BLOCKSIZE
#define BLOCKSIZE		64	// number of threads in each block
#endif

#ifndef NUMTRIALS
#define NUMTRIALS			( 8*1024 )	// size of the array
#endif

#define NUMBLOCKS NUMTRIALS/BLOCKSIZE


// these two #defines are just to label things
// other than that, they do nothing:
#define IN
#define OUT

// ranges for the random numbers:
const float GMIN =	20.0;	// ground distance in meters
const float GMAX =	30.0;	// ground distance in meters
const float HMIN =	10.0;	// cliff height in meters
const float HMAX =	40.0;	// cliff height in meters
const float DMIN  =	10.0;	// distance to castle in meters
const float DMAX  =	20.0;	// distance to castle in meters
const float VMIN  =	30.0;	// intial cnnonball velocity in meters / sec
const float VMAX  =	50.0;	// intial cnnonball velocity in meters / sec
const float THMIN = 70.0;	// cannonball launch angle in degrees
const float THMAX =	80.0;	// cannonball launch angle in degrees

const float GRAVITY =	-9.8;	// acceleraion due to gravity in meters / sec^2
const float TOL = 5.0;		// tolerance in cannonball hitting the castle in meters
				// castle is destroyed if cannonball lands between d-TOL and d+TOL

unsigned int seed = 0;

float Ranf(unsigned int*,  float, float);
int Ranf(unsigned int*,  int, int);
void CudaCheckError();
__device__ float Radians(float);
__global__ void MonteCarlo(float*, float*, float*, float*, float*, int*);


// main program:

int
main( int argc, char* argv[ ] )
{
	int dev = findCudaDevice(argc, (const char **)argv);

	// better to define these here so that the rand() calls don't get into the thread timing:
	float *hvs   = new float [NUMTRIALS];
	float *hths  = new float [NUMTRIALS];
	float *hgs   = new float [NUMTRIALS];
	float *hhs   = new float [NUMTRIALS];
	float *hds   = new float [NUMTRIALS];
	int   *hhits = new int   [NUMTRIALS];

	// fill the random-value arrays:

	for( int n = 0; n < NUMTRIALS; n++ )
	{
		hvs[n]  = Ranf( &seed, VMIN,  VMAX );
		hths[n] = Ranf( &seed, THMIN, THMAX );
 		hgs[n]  = Ranf( &seed, GMIN,  GMAX );
 		hhs[n]  = Ranf( &seed, HMIN,  HMAX );
 		hds[n]  = Ranf( &seed, DMIN,  DMAX );
	}

	// allocate device memory:
	float *dvs, *dths, *dgs, *dhs, *dds;
	int   *dhits;

	cudaMalloc( &dvs,   NUMTRIALS*sizeof(float) );
	cudaMalloc( &dths,  NUMTRIALS*sizeof(float) );
	cudaMalloc( &dgs,   NUMTRIALS*sizeof(float) );
	cudaMalloc( &dhs,   NUMTRIALS*sizeof(float) );
	cudaMalloc( &dds,   NUMTRIALS*sizeof(float) );
	cudaMalloc( &dhits, NUMTRIALS*sizeof(int) );
	CudaCheckError( );

	// copy host memory to the device:
	cudaMemcpy( dvs,  hvs,  NUMTRIALS*sizeof(float), cudaMemcpyHostToDevice );
	cudaMemcpy( dths, hths, NUMTRIALS*sizeof(float), cudaMemcpyHostToDevice );
	cudaMemcpy( dgs,  hgs,  NUMTRIALS*sizeof(float), cudaMemcpyHostToDevice );
	cudaMemcpy( dhs,  hhs,  NUMTRIALS*sizeof(float), cudaMemcpyHostToDevice );
	cudaMemcpy( dds,  hds,  NUMTRIALS*sizeof(float), cudaMemcpyHostToDevice );
	CudaCheckError( );

	// setup the execution parameters:
	dim3 grid( NUMBLOCKS, 1, 1 );
	dim3 threads( BLOCKSIZE, 1, 1 );

	// allocate cuda events that we'll use for timing:
	cudaEvent_t start, stop;
	cudaEventCreate( &start );
	cudaEventCreate( &stop  );
	CudaCheckError( );

	// let the gpu go quiet:
	cudaDeviceSynchronize( );

	// record the start event:
	cudaEventRecord( start, NULL );
	CudaCheckError( );

	// execute the kernel:
	MonteCarlo<<< grid, threads >>>( IN dvs, IN dths, IN dgs, IN dhs, IN dds,   OUT dhits );

	// record the stop event:
	cudaEventRecord( stop, NULL );
	CudaCheckError( );

	// wait for the stop event to complete:
	cudaDeviceSynchronize( );
	cudaEventSynchronize( stop );
	CudaCheckError( );

	float msecTotal = 0.0f;
	cudaEventElapsedTime( &msecTotal, start, stop );
	CudaCheckError( );

	// compute and print the performance

	double secondsTotal = 0.001 * (double)msecTotal;
	double multsPerSecond = (double)NUMTRIALS / secondsTotal;
	double megaMultsPerSecond = multsPerSecond / 1000000.;
	fprintf( stderr, "%12d\t%4d\t%10.2lf\n", NUMTRIALS, BLOCKSIZE, megaMultsPerSecond );

	// copy result from the device to the host:
	cudaMemcpy( hhits, dhits, NUMTRIALS*sizeof(int), cudaMemcpyDeviceToHost );
	CudaCheckError( );

	// add up the hhits[ ] array:
	int numHits = 0;
	for( int n = 0; n < NUMTRIALS; n++ )
	{
		numHits += hhits[n];
	}

	// compute and print the probability:
	float probability = (float)numHits/(float)( NUMTRIALS );	// just get for last NUMTRIES run
	fprintf(stderr, "probability = %6.2f%%\n",100.*probability);

	FILE* fp = fopen("project5.csv", "a");
	fprintf(fp, ",%.2f", megaMultsPerSecond);
	fclose(fp);

	// clean up host memory:
	delete [ ] hvs;
	delete [ ] hths;
	delete [ ] hgs;
	delete [ ] hhs;
	delete [ ] hds;
	delete [ ] hhits;

	// clean up device memory:
	cudaFree( dvs );
	cudaFree( dths );
	cudaFree( dgs );
	cudaFree( dhs );
	cudaFree( dds );
	cudaFree( dhits );
	CudaCheckError( );

	return 0;
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

void
CudaCheckError()
{
	cudaError_t e = cudaGetLastError();
	if (e != cudaSuccess)
	{
		fprintf(stderr, "CUDA failure %s:%d: '%s'\n", __FILE__, __LINE__, cudaGetErrorString(e));
	}
}

// degrees-to-radians -- callable from the device:
__device__
float
Radians( float d )
{
	return (M_PI/180.f) * d;
}

__global__
void
MonteCarlo( float *dvs, float *dths, float *dgs, float *dhs, float *dds, int *dhits )
{
	unsigned int gid      = blockIdx.x*blockDim.x + threadIdx.x;

	// randomize everything:
	float v   = dvs[gid];
	float thr = Radians( dths[gid] );
	float vx  = v * cos(thr);
	float vy  = v * sin(thr);
	float  g  =  dgs[gid];
	float  h  =  dhs[gid];
	float  d  =  dds[gid];

	int numHits = 0;

	// see if the ball doesn't even reach the cliff:
	float t = -vy / ( 0.5*GRAVITY );
	float x = vx * t;
	if( x > g )
	{
		t = g / vx;
		float y = (vy * t) + (.5 * GRAVITY * t * t);
		if (y > h)
		{
			// the ball hits the upper deck:
			// the time solution for this is a quadratic equation of the form:
			// at^2 + bt + c = 0.
			// where 'a' multiplies time^2
			//       'b' multiplies time
			//       'c' is a constant
			float a = .5 * GRAVITY;
			float b = vy;
			float c = -h;
			float disc = b*b - 4.f*a*c;	// quadratic formula discriminant

			// successfully hits the ground above the cliff:
			// get the intersection:
			disc = sqrtf( disc );
			float t1 = (-b + disc ) / ( 2.f*a );	// time to intersect high ground
			float t2 = (-b - disc ) / ( 2.f*a );	// time to intersect high ground

			// only care about the second intersection
			float tmax = t1;
			if( t2 > t1 )
				tmax = t2;

			// how far does the ball land horizontlly from the edge of the cliff?
			float upperDist = vx * tmax  -  g;

			if(  fabs( upperDist - d ) <= TOL )
			{
				numHits = 1;

			}
		}
	}

	dhits[gid] = numHits;
}


