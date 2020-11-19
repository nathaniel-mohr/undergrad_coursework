#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define _USE_MATH_DEFINES
#include <math.h>

#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4996)
#include "glew.h"
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include "glut.h"

#include "heli.550"


//	This is CS450 Final Project
//
//	The objective is to draw a robot going into a city with helicopters above
//
//	The left mouse button does rotation
//	The middle mouse button does scaling
//	The user interface allows:
//		1. The axes to be turned on and off
//		2. The color of the axes to be changed
//		3. The projection to be changed
//		4. The transformations to be reset
//		5. The program to quit
//
//	Author:			Nathaniel Mohr

// NOTE: There are a lot of good reasons to use const variables instead
// of #define's.  However, Visual C++ does not allow a const variable
// to be used as an array size or as the case in a switch( ) statement.  So in
// the following, all constants are const variables except those which need to
// be array sizes or cases in switch( ) statements.  Those are #defines.


// title of these windows:

const char *WINDOWTITLE = { "Final Project -- Nathaniel Mohr" };
const char *GLUITITLE   = { "User Interface Window" };


// what the glui package defines as true and false:

const int GLUITRUE  = { true  };
const int GLUIFALSE = { false };


// the escape key:

#define ESCAPE		0x1b


// initial window size:

const int INIT_WINDOW_SIZE = { 600 };


// multiplication factors for input interaction:
//  (these are known from previous experience)

const float ANGFACT = { 1. };
const float SCLFACT = { 0.005f };


// minimum allowable scale factor:

const float MINSCALE = { 0.05f };


// active mouse buttons (or them together):

const int LEFT   = { 4 };
const int MIDDLE = { 2 };
const int RIGHT  = { 1 };


// which projection:

enum Projections
{
	ORTHO,
	PERSP
};


// which button:

enum ButtonVals
{
	RESET,
	QUIT
};


// window background color (rgba):

const GLfloat BACKCOLOR[] = {0,0,0, 1. };


// line width for the axes:

const GLfloat AXES_WIDTH   = { 3. };


// the color numbers:
// this order must match the radio button order

enum Colors
{
	RED,
	YELLOW,
	GREEN,
	CYAN,
	BLUE,
	MAGENTA,
	WHITE,
	BLACK
};

char * ColorNames[ ] =
{
	"Red",
	"Yellow",
	"Green",
	"Cyan",
	"Blue",
	"Magenta",
	"White",
	"Black"
};


// the color definitions:
// this order must match the menu order

const GLfloat Colors[ ][3] = 
{
	{ 1., 0., 0. },		// red
	{ 1., 1., 0. },		// yellow
	{ 0., 1., 0. },		// green
	{ 0., 1., 1. },		// cyan
	{ 0., 0., 1. },		// blue
	{ 1., 0., 1. },		// magenta
	{ 1., 1., 1. },		// white
	{ 0., 0., 0. },		// black
};



// non-constant global variables:

int		ActiveButton;			// current button that is down
GLuint	AxesList;				// list to hold the axes
int		AxesOn;					// != 0 means to draw the axes
GLuint	HeliList;				// object display list
GLuint	BladeList;
GLuint	BodyList;
GLuint	HeadList;
GLuint	MouthList;
GLuint	EyeList;
GLuint	ImmobileRobotList;
GLuint	UpperAppendageList;
GLuint	LowerAppendageList;
GLuint	EndAppendageList;
GLuint	BuildingList;
GLuint	CityList;
GLuint	FloorList;
int		MainWindow;				// window id for main graphics window
float	Scale;					// scaling factor
int		WhichColor;				// index into Colors[ ]
int		WhichProjection;		// ORTHO or PERSP
int		Xmouse, Ymouse;			// mouse values
float	Xrot, Yrot;				// rotation angles in degrees
float	Time;
float	BladeSpeed = 20;
bool	headLights = true;
bool	heliLight1 = true;
bool	heliLight2 = true;
bool	heliLight3 = true;
bool	eyeLights = true;


// function prototypes:

void	Animate( );
void	Display( );
void	DoAxesMenu( int );
void	DoColorMenu( int );
void	DoMainMenu( int );
void	DoProjectMenu( int );
void	DoRasterString( float, float, float, char * );
void	DoStrokeString( float, float, float, float, char * );
float	ElapsedSeconds( );
void	InitGraphics( );
void	InitLists( );
void	InitMenus( );
void	Keyboard( unsigned char, int, int );
void	MouseButton( int, int, int, int );
void	MouseMotion( int, int );
void	Reset( );
void	Resize( int, int );
void	Visibility( int );

void	Axes( float );
void	HsvRgb( float[3], float [3] );



#define BLADE_RADIUS		 1.0
#define BLADE_WIDTH		 0.4
#define MS_IN_THE_ANIMATION_CYCLE	10000

float White[] = { 1.,1.,1.,1. };

// utility to create an array from 3 separate values:
float* Array3(float a, float b, float c) {
	static float array[4];
	array[0] = a;
	array[1] = b;
	array[2] = c;
	array[3] = 1.;
	return array;
}

// utility to create an array from a multiplier and an array:
float* MulArray3(float factor, float array0[3]) {
	static float array[4];
	array[0] = factor * array0[0];
	array[1] = factor * array0[1];
	array[2] = factor * array0[2];
	array[3] = 1.;
	return array;
}

void SetPointLight(int ilight, float x, float y, float z, float r, float g, float b) {
	glLightfv(ilight, GL_POSITION, Array3(x, y, z));
	glLightfv(ilight, GL_AMBIENT, Array3(0., 0., 0.));
	glLightfv(ilight, GL_DIFFUSE, Array3(r, g, b));
	glLightfv(ilight, GL_SPECULAR, Array3(r, g, b));
	glLightf(ilight, GL_CONSTANT_ATTENUATION, 1.);
	glLightf(ilight, GL_LINEAR_ATTENUATION, 0.);
	glLightf(ilight, GL_QUADRATIC_ATTENUATION, 0.);
	glEnable(ilight);
}

void SetSpotLight(int ilight, float x, float y, float z, float xdir, float ydir, float zdir, float r, float g, float b) {
	glLightfv(ilight, GL_POSITION, Array3(x, y, z));
	glLightfv(ilight, GL_SPOT_DIRECTION, Array3(xdir, ydir, zdir));
	glLightf(ilight, GL_SPOT_EXPONENT, 1.);
	glLightf(ilight, GL_SPOT_CUTOFF, 45.);
	glLightfv(ilight, GL_AMBIENT, Array3(0., 0., 0.));
	glLightfv(ilight, GL_DIFFUSE, Array3(r, g, b));
	glLightfv(ilight, GL_SPECULAR, Array3(r, g, b));
	glLightf(ilight, GL_CONSTANT_ATTENUATION, 1.);
	glLightf(ilight, GL_LINEAR_ATTENUATION, 0.);
	glLightf(ilight, GL_QUADRATIC_ATTENUATION, 0.);
	glEnable(ilight);
}

void SetMaterial(float r, float g, float b, float shininess) {
	glMaterialfv(GL_BACK, GL_EMISSION, Array3(0., 0., 0.));
	glMaterialfv(GL_BACK, GL_AMBIENT, Array3(r, g, b));
	glMaterialfv(GL_BACK, GL_DIFFUSE, Array3(r, g, b));
	glMaterialfv(GL_BACK, GL_SPECULAR, MulArray3(.8f, White));
	glMaterialf(GL_BACK, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, Array3(0., 0., 0.));
	glMaterialfv(GL_FRONT, GL_AMBIENT, Array3(r, g, b));
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Array3(r, g, b));
	glMaterialfv(GL_FRONT, GL_SPECULAR, MulArray3(.8f, White));
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}

float
Dot(float v1[3], float v2[3])
{
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

void
Cross(float v1[3], float v2[3], float vout[3])
{
	float tmp[3];
	tmp[0] = v1[1] * v2[2] - v2[1] * v1[2];
	tmp[1] = v2[0] * v1[2] - v1[0] * v2[2];
	tmp[2] = v1[0] * v2[1] - v2[0] * v1[1];
	vout[0] = tmp[0];
	vout[1] = tmp[1];
	vout[2] = tmp[2];
}

float
Unit(float vin[3], float vout[3])
{
	float dist = vin[0] * vin[0] + vin[1] * vin[1] + vin[2] * vin[2];
	if (dist > 0.0)
	{
		dist = sqrt(dist);
		vout[0] = vin[0] / dist;
		vout[1] = vin[1] / dist;
		vout[2] = vin[2] / dist;
	}
	else
	{
		vout[0] = vin[0];
		vout[1] = vin[1];
		vout[2] = vin[2];
	}
	return dist;
}

// main program:

int
main( int argc, char *argv[ ] )
{
	// turn on the glut package:
	// (do this before checking argc and argv since it might
	// pull some command line arguments out)

	glutInit( &argc, argv );


	// setup all the graphics stuff:

	InitGraphics( );


	// create the display structures that will not change:

	InitLists( );


	// init all the global variables used by Display( ):
	// this will also post a redisplay

	Reset( );


	// setup all the user interface stuff:

	InitMenus( );


	// draw the scene once and wait for some interaction:
	// (this will never return)

	glutSetWindow( MainWindow );
	glutMainLoop( );


	// this is here to make the compiler happy:

	return 0;
}


// this is where one would put code that is to be called
// everytime the glut main loop has nothing to do
//
// this is typically where animation parameters are set
//
// do not call Display( ) from here -- let glutMainLoop( ) do it

void
Animate( )
{
	// put animation stuff in here -- change some global variables
	// for Display( ) to find:

	int ms = glutGet(GLUT_ELAPSED_TIME);	// milliseconds
	ms %= MS_IN_THE_ANIMATION_CYCLE;
	Time = (float)ms / (float)MS_IN_THE_ANIMATION_CYCLE;

	// force a call to Display( ) next time it is convenient:

	glutSetWindow( MainWindow );
	glutPostRedisplay( );
}


// draw the complete scene:

void
Display( )
{

	// set which window we want to do the graphics into:

	glutSetWindow( MainWindow );


	// erase the background:

	glDrawBuffer( GL_BACK );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glEnable( GL_DEPTH_TEST );

	// specify shading to be flat:

	glShadeModel( GL_FLAT );


	// set the viewport to a square centered in the window:

	GLsizei vx = glutGet( GLUT_WINDOW_WIDTH );
	GLsizei vy = glutGet( GLUT_WINDOW_HEIGHT );
	GLsizei v = vx < vy ? vx : vy;			// minimum dimension
	GLint xl = ( vx - v ) / 2;
	GLint yb = ( vy - v ) / 2;
	glViewport( xl, yb,  v, v );


	// set the viewing volume:
	// remember that the Z clipping  values are actually
	// given as DISTANCES IN FRONT OF THE EYE
	// USE gluOrtho2D( ) IF YOU ARE DOING 2D !

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
	if( WhichProjection == ORTHO )
		glOrtho( -3., 3.,     -3., 3.,     0.1, 1000. );
	else
		gluPerspective( 90., 1.,	0.1, 1000. );


	// place the objects into the scene:

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );


	// set the eye position, look-at position, and up-vector:

	gluLookAt(-50., 120., 120., 0., 0., 0., 0., 1., 0.);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, MulArray3(.75, White));
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	// rotate the scene:

	glRotatef( (GLfloat)Yrot, 0., 1., 0. );
	glRotatef( (GLfloat)Xrot, 1., 0., 0. );


	// uniformly scale the scene:

	if( Scale < MINSCALE )
		Scale = MINSCALE;
	glScalef( (GLfloat)Scale, (GLfloat)Scale, (GLfloat)Scale );


	// possibly draw the axes:

	if( AxesOn != 0 )
	{
		glColor3fv( &Colors[WhichColor][0] );
		glCallList( AxesList );
	}


	// since we are using glScalef( ), be sure normals get unitized:

	glEnable( GL_NORMALIZE );


	// draw the current object:

	glTranslatef(0, 40, 0);

	glPushMatrix();
		glTranslatef(10, 51, 10);
		glColor3f(1, 0, 0);
		glutSolidSphere(1, 50, 50);
	glPopMatrix();
	if (headLights) {
		SetSpotLight(GL_LIGHT0, 10, 51, 10, cos(36 * Time), 0, 1, 1, 0, 0);
		SetSpotLight(GL_LIGHT1, 10, 51, 10, -cos(36 * Time), 0, -1, 1, 0, 0);
	}
	else {
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
	}


	glPushMatrix();
		glTranslatef(31.5, 54, 34);
		glColor3f(1, 1, 1);
		glutSolidSphere(1, 50, 50);
	glPopMatrix();
	if (heliLight1) {
		SetSpotLight(GL_LIGHT2, 31.5, 54, 34, -1, 0, -1, .2, .2, .2);
	}
	else {
		glDisable(GL_LIGHT2);
	}

	glPushMatrix();
	glTranslatef(-11.5, 54, 34);
	glColor3f(1, 1, 1);
	glutSolidSphere(1, 50, 50);
	glPopMatrix();
	if (heliLight2) {
		SetSpotLight(GL_LIGHT3, -11.5, 54, 34, 1, 0, -1, .2, .2, .2);
	}
	else {
		glDisable(GL_LIGHT3);
	}

	glPushMatrix();
	glTranslatef(10, 54, -13);
	glColor3f(1, 1, 1);
	glutSolidSphere(1, 50, 50);
	glPopMatrix();
	if (heliLight3) {
		SetSpotLight(GL_LIGHT4, 10, 54, -13, 0, 0, 1, .2, .2, .2);
	}
	else {
		glDisable(GL_LIGHT4);
	}

	glPushMatrix();
		glCallList(EyeList);
		if (eyeLights) {
			SetSpotLight(GL_LIGHT5, 8, 47, 15, 0, 0, 1, 0, .75, 0);
			SetSpotLight(GL_LIGHT6, 12, 47, 15, 0, 0, 1, 0, .75, 0);
		}
		else {
			glDisable(GL_LIGHT5);
			glDisable(GL_LIGHT6);
		}
	glPopMatrix();

	glCallList(FloorList);

	glEnable(GL_LIGHTING);

	glCallList(ImmobileRobotList);

	// Right Leg
	glPushMatrix();
		glTranslatef(0, -20, 10);
		glRotatef(-30, 1, 0, 0);
		glCallList(UpperAppendageList);

		glTranslatef(0, -5, -10);
		glRotatef(45, 1, 0, 0);
		glCallList(LowerAppendageList);

		glTranslatef(0, -5, 0);
		glCallList(EndAppendageList);
	glPopMatrix();

	// Left Leg
	glPushMatrix();
		glTranslatef(10, -20, 2.5);
		glCallList(UpperAppendageList);

		glTranslatef(0, -15, 0);
		glCallList(LowerAppendageList);

		glTranslatef(0, -5, 0);
		glCallList(EndAppendageList);
	glPopMatrix();

	// Right Arm
	glPushMatrix();
		glTranslatef(-10, 15, 10);
		glRotatef(-30, 1, 0, 0);
		glCallList(UpperAppendageList);

		glTranslatef(0, -15, 10);
		glRotatef(-45, 1, 0, 0);
		glCallList(LowerAppendageList);

		glTranslatef(0, -5, 0);
		glCallList(EndAppendageList);
	glPopMatrix();

	// Left Arm
	glPushMatrix();
		glTranslatef(20, 15, 10);
		glRotatef(-30, 1, 0, 0);
		glCallList(UpperAppendageList);

		glTranslatef(0, -15, 10);
		glRotatef(-45, 1, 0, 0);
		glCallList(LowerAppendageList);

		glTranslatef(0, -5, 0);
		glCallList(EndAppendageList);
	glPopMatrix();


	// Helicopter
	glPushMatrix();
	glTranslatef(-15, 55, 40);
	glRotatef(-30, 0, 1, 0);

		glCallList(HeliList);

		// Rear Blade
		glPushMatrix();
		glTranslatef(.5, 2.5, 9.);
		glRotatef(Time * 360. * 3 * BladeSpeed, 1., 0., 0.);
		glRotatef(90., 0., 1., 0.);
		glScalef(1.5, 1.5, 1.5);
		glCallList(BladeList);
		glPopMatrix();

		// Top Blade
		glPushMatrix();
		glTranslatef(0., 2.9, -2.);
		glRotatef(Time * 360. * BladeSpeed, 0., 1., 0.);
		glRotatef(90., 1., 0., 0.);
		glScalef(5.0, 5.0, 5.0);
		glCallList(BladeList);
		glPopMatrix();

	glPopMatrix();

	// Helicopter
	glPushMatrix();
	glTranslatef(35, 55, 40);
	glRotatef(30, 0, 1, 0);

		glCallList(HeliList);

		// Rear Blade
		glPushMatrix();
		glTranslatef(.5, 2.5, 9.);
		glRotatef(Time * 360. * 3 * BladeSpeed, 1., 0., 0.);
		glRotatef(90., 0., 1., 0.);
		glScalef(1.5, 1.5, 1.5);
		glCallList(BladeList);
		glPopMatrix();

		// Top Blade
		glPushMatrix();
		glTranslatef(0., 2.9, -2.);
		glRotatef(Time * 360. * BladeSpeed, 0., 1., 0.);
		glRotatef(90., 1., 0., 0.);
		glScalef(5.0, 5.0, 5.0);
		glCallList(BladeList);
		glPopMatrix();

	glPopMatrix();

	// Helicopter
	glPushMatrix();
	glTranslatef(10, 55, -20);
	glRotatef(180, 0, 1, 0);

		glCallList(HeliList);

		// Rear Blade
		glPushMatrix();
		glTranslatef(.5, 2.5, 9.);
		glRotatef(Time * 360. * 3 * BladeSpeed, 1., 0., 0.);
		glRotatef(90., 0., 1., 0.);
		glScalef(1.5, 1.5, 1.5);
		glCallList(BladeList);
		glPopMatrix();

		// Top Blade
		glPushMatrix();
		glTranslatef(0., 2.9, -2.);
		glRotatef(Time * 360. * BladeSpeed, 0., 1., 0.);
		glRotatef(90., 1., 0., 0.);
		glScalef(5.0, 5.0, 5.0);
		glCallList(BladeList);
		glPopMatrix();

	glPopMatrix();

	glCallList(CityList);

	glDisable(GL_LIGHTING);

	// swap the double-buffered framebuffers:

	glutSwapBuffers( );

	// be sure the graphics buffer has been sent:
	// note: be sure to use glFlush( ) here, not glFinish( ) !

	glFlush( );
}


void
DoAxesMenu( int id )
{
	AxesOn = id;

	glutSetWindow( MainWindow );
	glutPostRedisplay( );
}


void
DoColorMenu( int id )
{
	WhichColor = id - RED;

	glutSetWindow( MainWindow );
	glutPostRedisplay( );
}

// main menu callback:

void
DoMainMenu( int id )
{
	switch( id )
	{
		case RESET:
			Reset( );
			break;

		case QUIT:
			// gracefully close out the graphics:
			// gracefully close the graphics window:
			// gracefully exit the program:
			glutSetWindow( MainWindow );
			glFinish( );
			glutDestroyWindow( MainWindow );
			exit( 0 );
			break;

		default:
			fprintf( stderr, "Don't know what to do with Main Menu ID %d\n", id );
	}

	glutSetWindow( MainWindow );
	glutPostRedisplay( );
}


void
DoProjectMenu( int id )
{
	WhichProjection = id;

	glutSetWindow( MainWindow );
	glutPostRedisplay( );
}


// use glut to display a string of characters using a raster font:

void
DoRasterString( float x, float y, float z, char *s )
{
	glRasterPos3f( (GLfloat)x, (GLfloat)y, (GLfloat)z );

	char c;			// one character to print
	for( ; ( c = *s ) != '\0'; s++ )
	{
		glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, c );
	}
}


// use glut to display a string of characters using a stroke font:

void
DoStrokeString( float x, float y, float z, float ht, char *s )
{
	glPushMatrix( );
		glTranslatef( (GLfloat)x, (GLfloat)y, (GLfloat)z );
		float sf = ht / ( 119.05f + 33.33f );
		glScalef( (GLfloat)sf, (GLfloat)sf, (GLfloat)sf );
		char c;			// one character to print
		for( ; ( c = *s ) != '\0'; s++ )
		{
			glutStrokeCharacter( GLUT_STROKE_ROMAN, c );
		}
	glPopMatrix( );
}


// return the number of seconds since the start of the program:

float
ElapsedSeconds( )
{
	// get # of milliseconds since the start of the program:

	int ms = glutGet( GLUT_ELAPSED_TIME );

	// convert it to seconds:

	return (float)ms / 1000.f;
}


// initialize the glui window:

void
InitMenus( )
{
	glutSetWindow( MainWindow );

	int numColors = sizeof( Colors ) / ( 3*sizeof(int) );
	int colormenu = glutCreateMenu( DoColorMenu );
	for( int i = 0; i < numColors; i++ )
	{
		glutAddMenuEntry( ColorNames[i], i );
	}

	int axesmenu = glutCreateMenu( DoAxesMenu );
	glutAddMenuEntry( "Off",  0 );
	glutAddMenuEntry( "On",   1 );

	int projmenu = glutCreateMenu( DoProjectMenu );
	glutAddMenuEntry( "Orthographic",  ORTHO );
	glutAddMenuEntry( "Perspective",   PERSP );

	int mainmenu = glutCreateMenu( DoMainMenu );
	glutAddSubMenu(   "Axes",          axesmenu);
	glutAddSubMenu(   "Colors",        colormenu);
	glutAddSubMenu(   "Projection",    projmenu );
	glutAddMenuEntry( "Reset",         RESET );
	glutAddMenuEntry( "Quit",          QUIT );

// attach the pop-up menu to the right mouse button:

	glutAttachMenu( GLUT_RIGHT_BUTTON );
}



// initialize the glut and OpenGL libraries:
//	also setup display lists and callback functions

void
InitGraphics( )
{
	// request the display modes:
	// ask for red-green-blue-alpha color, double-buffering, and z-buffering:

	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );

	// set the initial window configuration:

	glutInitWindowPosition( 0, 0 );
	glutInitWindowSize( INIT_WINDOW_SIZE, INIT_WINDOW_SIZE );

	// open the window and set its title:

	MainWindow = glutCreateWindow( WINDOWTITLE );
	glutSetWindowTitle( WINDOWTITLE );

	// set the framebuffer clear values:

	glClearColor( BACKCOLOR[0], BACKCOLOR[1], BACKCOLOR[2], BACKCOLOR[3] );

	// setup the callback functions:
	// DisplayFunc -- redraw the window
	// ReshapeFunc -- handle the user resizing the window
	// KeyboardFunc -- handle a keyboard input
	// MouseFunc -- handle the mouse button going down or up
	// MotionFunc -- handle the mouse moving with a button down
	// PassiveMotionFunc -- handle the mouse moving with a button up
	// VisibilityFunc -- handle a change in window visibility
	// EntryFunc	-- handle the cursor entering or leaving the window
	// SpecialFunc -- handle special keys on the keyboard
	// SpaceballMotionFunc -- handle spaceball translation
	// SpaceballRotateFunc -- handle spaceball rotation
	// SpaceballButtonFunc -- handle spaceball button hits
	// ButtonBoxFunc -- handle button box hits
	// DialsFunc -- handle dial rotations
	// TabletMotionFunc -- handle digitizing tablet motion
	// TabletButtonFunc -- handle digitizing tablet button hits
	// MenuStateFunc -- declare when a pop-up menu is in use
	// TimerFunc -- trigger something to happen a certain time from now
	// IdleFunc -- what to do when nothing else is going on

	glutSetWindow( MainWindow );
	glutDisplayFunc( Display );
	glutReshapeFunc( Resize );
	glutKeyboardFunc( Keyboard );
	glutMouseFunc( MouseButton );
	glutMotionFunc( MouseMotion );
	glutPassiveMotionFunc( NULL );
	glutVisibilityFunc( Visibility );
	glutEntryFunc( NULL );
	glutSpecialFunc( NULL );
	glutSpaceballMotionFunc( NULL );
	glutSpaceballRotateFunc( NULL );
	glutSpaceballButtonFunc( NULL );
	glutButtonBoxFunc( NULL );
	glutDialsFunc( NULL );
	glutTabletMotionFunc( NULL );
	glutTabletButtonFunc( NULL );
	glutMenuStateFunc( NULL );
	glutTimerFunc( -1, NULL, 0 );
	glutIdleFunc( Animate );

	// init glew (a window must be open to do this):

#ifdef WIN32
	GLenum err = glewInit( );
	if( err != GLEW_OK )
	{
		fprintf( stderr, "glewInit Error\n" );
	}
	else
		fprintf( stderr, "GLEW initialized OK\n" );
	fprintf( stderr, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
#endif

}


// initialize the display lists that will not change:
// (a display list is a way to store opengl commands in
//  memory so that they can be played back efficiently at a later time
//  with a call to glCallList( )

void
InitLists( )
{
	
	// create the object:

	HeliList = glGenLists( 1 );
	glNewList( HeliList, GL_COMPILE );

		int i;
		struct point* p0, * p1, * p2;
		struct tri* tp;
		float p01[3], p02[3], n[3];

		glPushMatrix();
		glTranslatef(0., -1., 0.);
		glRotatef(97., 0., 1., 0.);
		glRotatef(-15., 0., 0., 1.);
		glBegin(GL_TRIANGLES);
		for (i = 0, tp = Helitris; i < Helintris; i++, tp++)
		{
			p0 = &Helipoints[tp->p0];
			p1 = &Helipoints[tp->p1];
			p2 = &Helipoints[tp->p2];

			// fake "lighting" from above:

			p01[0] = p1->x - p0->x;
			p01[1] = p1->y - p0->y;
			p01[2] = p1->z - p0->z;
			p02[0] = p2->x - p0->x;
			p02[1] = p2->y - p0->y;
			p02[2] = p2->z - p0->z;
			Cross(p01, p02, n);
			Unit(n, n);
			n[1] = fabs(n[1]);
			n[1] += .25;
			if (n[1] > 1.)
				n[1] = 1.;
			SetMaterial(.472 * n[1], .453 * n[1], .429 * n[1], 1);

			glVertex3f(p0->x, p0->y, p0->z);
			glVertex3f(p1->x, p1->y, p1->z);
			glVertex3f(p2->x, p2->y, p2->z);
		}
		glEnd();
		glPopMatrix();

	glEndList( );

	BladeList = glGenLists(1);
	glNewList(BladeList, GL_COMPILE);
	SetMaterial(1, 1, 1, 1);
		glBegin(GL_TRIANGLES);
		glVertex2f(BLADE_RADIUS, BLADE_WIDTH / 2.);
		glVertex2f(0., 0.);
		glVertex2f(BLADE_RADIUS, -BLADE_WIDTH / 2.);

		glVertex2f(-BLADE_RADIUS, -BLADE_WIDTH / 2.);
		glVertex2f(0., 0.);
		glVertex2f(-BLADE_RADIUS, BLADE_WIDTH / 2.);
		glEnd();
	glEndList();


	BodyList = glGenLists(1);
	glNewList(BodyList, GL_COMPILE);
		glPushMatrix();
		SetMaterial(.730, .695, .676, 1);
		glBegin(GL_QUADS);
			glVertex3f(0,0,0);
			glVertex3f(20,0,0);
			glVertex3f(20,40,0);
			glVertex3f(0,40,0);

			glVertex3f(20,40,0);
			glVertex3f(20,40,20);
			glVertex3f(20,0,20);
			glVertex3f(20,0,0);

			glVertex3f(20,40,20);
			glVertex3f(20,0,20);
			glVertex3f(0,0,20);
			glVertex3f(0,40,20);

			glVertex3f(0,40,20);
			glVertex3f(0,40,0);
			glVertex3f(0,0,0);
			glVertex3f(0,0,20);

			glVertex3f(0,40,0);
			glVertex3f(20,40,0);
			glVertex3f(20,40,20);
			glVertex3f(0,40,20);

			glVertex3f(0,0,0);
			glVertex3f(20,0,0);
			glVertex3f(20,0,20);
			glVertex3f(0,0,20);
		glEnd();
		glPopMatrix();
	glEndList();

	HeadList = glGenLists(1);
	glNewList(HeadList, GL_COMPILE);
		glPushMatrix();
		glTranslatef(10, 45, 10);
		SetMaterial(.730, .695, .676, 1);
		glutSolidCube(10);
		glPopMatrix();
	glEndList();

	MouthList = glGenLists(1);
	glNewList(MouthList, GL_COMPILE);
		glPushMatrix();
		glTranslatef(9, 42.5, 16);
		SetMaterial(1, 1, 0, .5);
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(-1, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 1, 0);
		glVertex3f(2, 0, 0);
		glVertex3f(2, 1, 0);
		glVertex3f(3, 1, 0);
		glEnd();

		SetMaterial(.113,.113,.113,1);
		glBegin(GL_QUADS);
		glVertex3f(-1, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, -1);
		glVertex3f(-1, 1, -1);

		glVertex3f(0, 0, 0);
		glVertex3f(2, 0, 0);
		glVertex3f(2, 0, -1);
		glVertex3f(0, 0, -1);

		glVertex3f(3, 1, 0);
		glVertex3f(2, 0, 0);
		glVertex3f(2, 0, -1);
		glVertex3f(3, 1, -1);

		glVertex3f(-1, 1, 0);
		glVertex3f(3, 1, 0);
		glVertex3f(3, 1, -1);
		glVertex3f(-1, 1, -1);
		glEnd();
		glPopMatrix();
	glEndList();

	EyeList = glGenLists(1);
	glNewList(EyeList, GL_COMPILE);
		glPushMatrix();
		glColor3f(0, .75, 0);
		glTranslatef(8, 47, 15);
		glutSolidSphere(1, 50, 50);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(12, 47, 15);
		glutSolidSphere(1, 50, 50);
		glPopMatrix();
	glEndList();

	ImmobileRobotList = glGenLists(1);
	glNewList(ImmobileRobotList, GL_COMPILE);
		glCallList(BodyList);
		glCallList(HeadList);
		glCallList(MouthList);
	glEndList();

	UpperAppendageList = glGenLists(1);
	glNewList(UpperAppendageList, GL_COMPILE);
		SetMaterial(.472, .453, .429, 1);
		glBegin(GL_QUADS);
			glVertex3f(0, 0, 0);
			glVertex3f(10, 0, 0);
			glVertex3f(10, 20, 0);
			glVertex3f(10, 20, 0);

			glVertex3f(10, 20, 0);
			glVertex3f(10, 20, 15);
			glVertex3f(10, 0, 15);
			glVertex3f(10, 0, 0);

			glVertex3f(10, 20, 15);
			glVertex3f(10, 0, 15);
			glVertex3f(0, 0, 15);
			glVertex3f(0, 20, 15);

			glVertex3f(0, 20, 15);
			glVertex3f(0, 20, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 0, 15);

			glVertex3f(0, 20, 0);
			glVertex3f(10, 20, 0);
			glVertex3f(10, 20, 15);
			glVertex3f(0, 20, 15);

			glVertex3f(0, 0, 0);
			glVertex3f(10, 0, 0);
			glVertex3f(10, 0, 15);
			glVertex3f(0, 0, 15);
		glEnd();
	glEndList();

	LowerAppendageList = glGenLists(1);
	glNewList(LowerAppendageList, GL_COMPILE);
		SetMaterial(.45,.45,.45, 1);
		glBegin(GL_QUADS);
			glVertex3f(0, 0, 0);
			glVertex3f(10, 0, 0);
			glVertex3f(10, 15, 0);
			glVertex3f(10, 15, 0);

			glVertex3f(10, 15, 0);
			glVertex3f(10, 15, 15);
			glVertex3f(10, 0, 15);
			glVertex3f(10, 0, 0);

			glVertex3f(10, 15, 15);
			glVertex3f(10, 0, 15);
			glVertex3f(0, 0, 15);
			glVertex3f(0, 15, 15);

			glVertex3f(0, 15, 15);
			glVertex3f(0, 15, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 0, 15);

			glVertex3f(0, 15, 0);
			glVertex3f(10, 15, 0);
			glVertex3f(10, 15, 15);
			glVertex3f(0, 15, 15);

			glVertex3f(0, 0, 0);
			glVertex3f(10, 0, 0);
			glVertex3f(10, 0, 15);
			glVertex3f(0, 0, 15);
		glEnd();
	glEndList();

	EndAppendageList = glGenLists(1);
	glNewList(EndAppendageList, GL_COMPILE);
		SetMaterial(.472, .453, .429, 1);
		glBegin(GL_QUADS);
			glVertex3f(0, 0, 0);
			glVertex3f(10, 0, 0);
			glVertex3f(10, 5, 0);
			glVertex3f(10, 5, 0);

			glVertex3f(10, 5, 0);
			glVertex3f(10, 5, 15);
			glVertex3f(10, 0, 15);
			glVertex3f(10, 0, 0);

			glVertex3f(10, 5, 15);
			glVertex3f(10, 0, 15);
			glVertex3f(0, 0, 15);
			glVertex3f(0, 5, 15);

			glVertex3f(0, 5, 15);
			glVertex3f(0, 5, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 0, 15);

			glVertex3f(0, 5, 0);
			glVertex3f(10, 5, 0);
			glVertex3f(10, 5, 15);
			glVertex3f(0, 5, 15);

			glVertex3f(0, 0, 0);
			glVertex3f(10, 0, 0);
			glVertex3f(10, 0, 15);
			glVertex3f(0, 0, 15);
		glEnd();
	glEndList();

	BuildingList = glGenLists(1);
	glNewList(BuildingList, GL_COMPILE);
		glBegin(GL_QUADS);
			glVertex3f(0, 0, 0);
			glVertex3f(1, 0, 0);
			glVertex3f(1, 2, 0);
			glVertex3f(1, 2, 0);

			glVertex3f(1, 2, 0);
			glVertex3f(1, 2, 1);
			glVertex3f(1, 0, 1);
			glVertex3f(1, 0, 0);

			glVertex3f(1, 2, 1);
			glVertex3f(1, 0, 1);
			glVertex3f(0, 0, 1);
			glVertex3f(0, 2, 1);

			glVertex3f(0, 2, 1);
			glVertex3f(0, 2, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 0, 1);

			glVertex3f(0, 2, 0);
			glVertex3f(1, 2, 0);
			glVertex3f(1, 2, 1);
			glVertex3f(0, 2, 1);

			glVertex3f(0, 0, 0);
			glVertex3f(1, 0, 0);
			glVertex3f(1, 0, 1);
			glVertex3f(0, 0, 1);
		glEnd();
	glEndList();

	CityList = glGenLists(1);
	glNewList(CityList, GL_COMPILE);
		SetMaterial(.113,.113,.113, 0);
		glPushMatrix();
		glTranslatef(-60, -40, 40);
		for (int l = 0; l < 10; l++) {
			glPushMatrix();
			for (int k = 0; k < 10; k++) {
				glPushMatrix();
				for (int j = 0; j < 5; j++) {
					glPushMatrix();
					for (int i = 0; i < 5; i++) {
						glTranslatef(2, 0, 0);
						glCallList(BuildingList);
					}
					glPopMatrix();
					glTranslatef(0, 0, -2);
				}
				glPopMatrix();
				glTranslatef(0, 0, 15);
			}
			glPopMatrix();
			glTranslatef(15, 0, 0);
		}
		glPopMatrix();
	glEndList();

	FloorList = glGenLists(1);
	glNewList(FloorList, GL_COMPILE);
		glColor3f(.012, .664, .016);
		glBegin(GL_POLYGON);
			glVertex3f(-100, -40, -100);
			glVertex3f(100, -40, -100);
			glVertex3f(100, -40, 200);
			glVertex3f(-100, -40, 200);
		glEnd();
	glEndList();

	// create the axes:

	AxesList = glGenLists( 1 );
	glNewList( AxesList, GL_COMPILE );
		glLineWidth( AXES_WIDTH );
			Axes( 1.5 );
		glLineWidth( 1. );
	glEndList( );
}


// the keyboard callback:

void
Keyboard( unsigned char c, int x, int y )
{
	
	switch( c )
	{
		case '0':
			headLights = !headLights;
			break;

		case '1':
			heliLight1 = !heliLight1;
			break;

		case '2':
			heliLight2 = !heliLight2;
			break;

		case '3':
			heliLight3 = !heliLight3;
			break;

		case '4':
			eyeLights = !eyeLights;
			break;

		case 'o':
		case 'O':
			WhichProjection = ORTHO;
			break;

		case 'p':
		case 'P':
			WhichProjection = PERSP;
			break;

		case 'r':
		case 'R':
			Reset();
			break;

		case 'q':
		case 'Q':
		case ESCAPE:
			DoMainMenu( QUIT );	// will not return here
			break;				// happy compiler

		default:
			fprintf( stderr, "Don't know what to do with keyboard hit: '%c' (0x%0x)\n", c, c );
	}

	// force a call to Display( ):

	glutSetWindow( MainWindow );
	glutPostRedisplay( );
}


// called when the mouse button transitions down or up:

void
MouseButton( int button, int state, int x, int y )
{
	int b = 0;			// LEFT, MIDDLE, or RIGHT
	
	// get the proper button bit mask:

	switch( button )
	{
		case GLUT_LEFT_BUTTON:
			b = LEFT;		break;

		case GLUT_MIDDLE_BUTTON:
			b = MIDDLE;		break;

		case GLUT_RIGHT_BUTTON:
			b = RIGHT;		break;

		default:
			b = 0;
			fprintf( stderr, "Unknown mouse button: %d\n", button );
	}


	// button down sets the bit, up clears the bit:

	if( state == GLUT_DOWN )
	{
		Xmouse = x;
		Ymouse = y;
		ActiveButton |= b;		// set the proper bit
	}
	else
	{
		ActiveButton &= ~b;		// clear the proper bit
	}
}


// called when the mouse moves while a button is down:

void
MouseMotion( int x, int y )
{

	int dx = x - Xmouse;		// change in mouse coords
	int dy = y - Ymouse;

	if( ( ActiveButton & LEFT ) != 0 )
	{
		Xrot += ( ANGFACT*dy );
		Yrot += ( ANGFACT*dx );
	}


	if( ( ActiveButton & MIDDLE ) != 0 )
	{
		Scale += SCLFACT * (float) ( dx - dy );

		// keep object from turning inside-out or disappearing:

		if( Scale < MINSCALE )
			Scale = MINSCALE;
	}

	Xmouse = x;			// new current position
	Ymouse = y;

	glutSetWindow( MainWindow );
	glutPostRedisplay( );
}


// reset the transformations and the colors:
// this only sets the global variables --
// the glut main loop is responsible for redrawing the scene

void
Reset( )
{
	ActiveButton = 0;
	AxesOn = 1;
	Scale  = 1.0;
	WhichColor = WHITE;
	WhichProjection = PERSP;
	Xrot = Yrot = 0.;
	headLights = heliLight1 = heliLight2 = heliLight3 = eyeLights = true;
}


// called when user resizes the window:

void
Resize( int width, int height )
{

	// don't really need to do anything since window size is
	// checked each time in Display( ):

	glutSetWindow( MainWindow );
	glutPostRedisplay( );
}


// handle a change to the window's visibility:

void
Visibility ( int state )
{
	if( state == GLUT_VISIBLE )
	{
		glutSetWindow( MainWindow );
		glutPostRedisplay( );
	}
	else
	{
		// could optimize by keeping track of the fact
		// that the window is not visible and avoid
		// animating or redrawing it ...
	}
}



///////////////////////////////////////   HANDY UTILITIES:  //////////////////////////


// the stroke characters 'X' 'Y' 'Z' :

static float xx[ ] = {
		0.f, 1.f, 0.f, 1.f
	      };

static float xy[ ] = {
		-.5f, .5f, .5f, -.5f
	      };

static int xorder[ ] = {
		1, 2, -3, 4
		};

static float yx[ ] = {
		0.f, 0.f, -.5f, .5f
	      };

static float yy[ ] = {
		0.f, .6f, 1.f, 1.f
	      };

static int yorder[ ] = {
		1, 2, 3, -2, 4
		};

static float zx[ ] = {
		1.f, 0.f, 1.f, 0.f, .25f, .75f
	      };

static float zy[ ] = {
		.5f, .5f, -.5f, -.5f, 0.f, 0.f
	      };

static int zorder[ ] = {
		1, 2, 3, 4, -5, 6
		};

// fraction of the length to use as height of the characters:
const float LENFRAC = 0.10f;

// fraction of length to use as start location of the characters:
const float BASEFRAC = 1.10f;

//	Draw a set of 3D axes:
//	(length is the axis length in world coordinates)

void
Axes( float length )
{
	glBegin( GL_LINE_STRIP );
		glVertex3f( length, 0., 0. );
		glVertex3f( 0., 0., 0. );
		glVertex3f( 0., length, 0. );
	glEnd( );
	glBegin( GL_LINE_STRIP );
		glVertex3f( 0., 0., 0. );
		glVertex3f( 0., 0., length );
	glEnd( );

	float fact = LENFRAC * length;
	float base = BASEFRAC * length;

	glBegin( GL_LINE_STRIP );
		for( int i = 0; i < 4; i++ )
		{
			int j = xorder[i];
			if( j < 0 )
			{
				
				glEnd( );
				glBegin( GL_LINE_STRIP );
				j = -j;
			}
			j--;
			glVertex3f( base + fact*xx[j], fact*xy[j], 0.0 );
		}
	glEnd( );

	glBegin( GL_LINE_STRIP );
		for( int i = 0; i < 5; i++ )
		{
			int j = yorder[i];
			if( j < 0 )
			{
				
				glEnd( );
				glBegin( GL_LINE_STRIP );
				j = -j;
			}
			j--;
			glVertex3f( fact*yx[j], base + fact*yy[j], 0.0 );
		}
	glEnd( );

	glBegin( GL_LINE_STRIP );
		for( int i = 0; i < 6; i++ )
		{
			int j = zorder[i];
			if( j < 0 )
			{
				
				glEnd( );
				glBegin( GL_LINE_STRIP );
				j = -j;
			}
			j--;
			glVertex3f( 0.0, fact*zy[j], base + fact*zx[j] );
		}
	glEnd( );

}


// function to convert HSV to RGB
// 0.  <=  s, v, r, g, b  <=  1.
// 0.  <= h  <=  360.
// when this returns, call:
//		glColor3fv( rgb );

void
HsvRgb( float hsv[3], float rgb[3] )
{
	// guarantee valid input:

	float h = hsv[0] / 60.f;
	while( h >= 6. )	h -= 6.;
	while( h <  0. ) 	h += 6.;

	float s = hsv[1];
	if( s < 0. )
		s = 0.;
	if( s > 1. )
		s = 1.;

	float v = hsv[2];
	if( v < 0. )
		v = 0.;
	if( v > 1. )
		v = 1.;

	// if sat==0, then is a gray:

	if( s == 0.0 )
	{
		rgb[0] = rgb[1] = rgb[2] = v;
		return;
	}

	// get an rgb from the hue itself:
	
	float i = floor( h );
	float f = h - i;
	float p = v * ( 1.f - s );
	float q = v * ( 1.f - s*f );
	float t = v * ( 1.f - ( s * (1.f-f) ) );

	float r, g, b;			// red, green, blue
	switch( (int) i )
	{
		case 0:
			r = v;	g = t;	b = p;
			break;
	
		case 1:
			r = q;	g = v;	b = p;
			break;
	
		case 2:
			r = p;	g = v;	b = t;
			break;
	
		case 3:
			r = p;	g = q;	b = v;
			break;
	
		case 4:
			r = t;	g = p;	b = v;
			break;
	
		case 5:
			r = v;	g = p;	b = q;
			break;
	}


	rgb[0] = r;
	rgb[1] = g;
	rgb[2] = b;
}
