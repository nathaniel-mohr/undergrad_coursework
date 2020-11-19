#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <ctype.h>

#include "keytime.h"

#ifndef WIN32
#include <sys/time.h>
#endif

#ifdef WIN32
#pragma warning(disable:4996)
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include "glut.h"
#include "glui.h"


// title of these windows:

const char *WINDOWTITLE = { "Project 6: Keytime Animation -- Nathaniel Mohr" };
const char *GLUITITLE   = { "User Interface Window" };


// what the glui package defines as true and false:

const int GLUITRUE  = { true  };
const int GLUIFALSE = { false };


// the escape key:

#define ESCAPE		0x1b


// initial window size:

const int INIT_WINDOW_SIZE = { 800 };



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

const int ORTHO = { GLUIFALSE };
const int PERSP = { GLUITRUE  };


// which button:

#define RESET		0
#define QUIT		1


// window background color (rgba):

const float BACKCOLOR[ ] = { 0., 0., 0., 0. };


// color and line width for the axes:

const float AXES_COLOR[ ] = { 1., .5, 0. };
const float AXES_WIDTH   = 3.;


// time in milliseconds for cycle to complete:

const int MSEC = { 10*1000 };


// handy to have around:

const int OFF = { 0 };
const int ON  = { 1 };

#define FALSE	0
#define TRUE	1

// window background color (rgba): = {

const float BACKGROUND_COLOR[4] = { 0.,0.,0.,0. };

// projecting the shadow:

const float FLOOR = { -100. };
const float CEILING = { 1100. };
const float DSHADOW = { 10. };
const float LEFT_WALL = { -100. };
const float RIGHT_WALL = { 1100. };
const float BACK_WALL = { -100. };
const float FRONT_WALL = { 1100. };
const float FLOOR_COLOR[3] = { .5f,.5f,.5f };
const float LEFT_WALL_COLOR[3] = { .2f,.2f,.2f };
const float BACK_WALL_COLOR[3] = { .3f,.3f,.3f };
const float KEYTIME_COLOR[3] = { 0.6f,0.6f,0. };

const float SCALE_FACTOR = 100.;


 // non-constant global variables:

int	ActiveButton;		// current button that is down
int	AnimateOn;		// TRUE means we are animating
int	AxesList;		// list to hold the axes
int	AxesOn;			// ON or OFF
int	Debug;			// ON means print debug info
GLUI *	Glui;			// instance of glui window
int	GluiWindow;		// the glut id for the glui window
int	GrWindow;		// window id for graphics window
int	KeytimeList;		// list to hold the keyframes
int	KeytimeMenu;		// id of the keyframe pop-up menu
int	KeytimeOn;		// ON or OFF
int	ObjectList;		// list to hold the object
float	RotMatrix[4][4];	// set by glui rotation widget
float	Scale, Scale2;		// scaling factors
int	WallList;		// list to hold the wall
int	WhichProjection;	// ORTHO or PERSP
int	Xmouse, Ymouse;		// mouse values
float	Xrot, Yrot;		// rotation angles in degrees
float	TransXYZ[3];		// set by glui translation widgets

GLUI_Rotation	*GluiRot;

Keytimes Xpos, Ypos, Zpos;
Keytimes ThetaX, ThetaY, ThetaZ;
Keytimes Hue;
Keytimes Xscale, Yscale, Zscale;

float	White[ ] = { 1.,1.,1.,1. };	// handy to have around

 // function prototypes:

void	Animate( void );
float *	Array3( float, float, float );
void	Axes( float length );
void	Buttons( int );
void	Display( void );
void	DoRasterString( float, float, float, char * );
void	DoStrokeString( float, float, float, float, char * );
void	HsvRgb( float [3], float [3] );
void	InitGraphics( void );
void	InitLists( void );
void	InitGlui( void );
void	Keyboard( unsigned char, int, int );
void	MouseButton( int, int, int, int );
void	MouseMotion( int, int );
float *	MulArray3( float, float [3] );
void	Reset( void );
void	Resize( int, int );
void	SetAnimate( int );
void	Visibility( int );


 // main program:

int
main( int argc, char *argv[ ] )
{
	// turn on the glut package:

	glutInit( &argc, argv );

	// setup all the graphics stuff:

	InitGraphics( );

	// create the display structures that will not change:

	InitLists( );

	// init all the global variables used by Display( ):
	// this will also post a redisplay
	// it is important to call this before InitGlui( ):
	// so that the variables that glui will control are correct
	// when each glui widget is created

	Reset( );

	// setup all the user interface stuff:

	InitGlui( );

	// draw the scene once and wait for some interaction:
	// (will never return)

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
Animate( void )
{
	// force a call to Display( ) next time it is convenient:

	glutSetWindow( GrWindow );
	glutPostRedisplay( );
}



 // glui buttons callback:

void
Buttons( int id )
{
	switch( id )
	{
		case RESET:
			Reset( );
			break;

		case QUIT:
			// gracefully close the glui window:
			// gracefully close out the graphics:
			// gracefully close the graphics window:
			// gracefully exit the program:

			Glui->close( );
			glFinish( );
			glutDestroyWindow( GrWindow );
			exit( 0 );
	}

	Glui->sync_live( );
}



 // draw the complete scene:

void
Display( void )
{
	glutSetWindow( GrWindow );

	// erase the background:

	glDrawBuffer( GL_BACK );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glEnable( GL_DEPTH_TEST );

	// specify shading to be flat:

	glShadeModel( GL_FLAT );

	// set the viewport to a square centered in the window:

	int dx = glutGet( GLUT_WINDOW_WIDTH );
	int dy = glutGet( GLUT_WINDOW_HEIGHT );
	int d = dx < dy ? dx : dy;			// minimum dimension
	int xl = ( dx - d ) / 2;
	int yb = ( dy - d ) / 2;
	glViewport( xl, yb,  d, d );

	// set the viewing volume:
	// remember that the eye is at the origin looking in -Z
	// remember that the Z values are actually
	// given as DISTANCES IN FRONT OF THE EYE

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );

	if( WhichProjection == ORTHO )
		glOrtho( -800., 800.,     -800., 800.,     0.8, 4000. );
	else
		gluPerspective( 70., 1.,	10., 4000. );

	// place the object into the viewing volume:

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );
	gluLookAt( 0., 0., 2000.,	0., 0., 0.,	0., 1., 0. );

	// light position:

	glLightfv( GL_LIGHT0, GL_POSITION,  Array3( 0., 1000., 0. ) );
	glLightfv( GL_LIGHT1, GL_POSITION,  Array3( 1000., 0., 0. ) );


	// rotate the scene:

	glRotatef( Yrot, 0., 1., 0. );
	glRotatef( Xrot, 1., 0., 0. );
	glMultMatrixf( (const GLfloat *) RotMatrix );


	// scale the scene:

	glScalef( Scale, Scale, Scale );
	float scale2 = 1.f + Scale2;		// because glui translation starts at 0.
	if( scale2 < MINSCALE )
		scale2 = MINSCALE;
	glScalef( scale2, scale2, scale2 );


	// possibly draw the axes:

	glDisable( GL_LIGHTING );
	glDisable( GL_LIGHT0 );
	glDisable( GL_LIGHT1 );

	if( AxesOn )
		glCallList( AxesList );

	// translate the object:
	// note the minus sign on the z value
	// this is to make the appearance of the glui z translate
	// widget more intuitively match the translate behavior

	glTranslatef( TransXYZ[0], TransXYZ[1], -TransXYZ[2] );
	glTranslatef( -350., -350., -500. );

	// draw the walls:

	glCallList(WallList);

	// the key positions:

	if( KeytimeOn == ON )
	{
		glColor3fv( KEYTIME_COLOR );
		glCallList( KeytimeList );
	}

	// turn # msec into the cycle ( 0 - MSEC-1 ):

	int msec = glutGet( GLUT_ELAPSED_TIME )  %  MSEC;

	// turn that into a time:

	float nowTime = (float)msec  / 1000.f;

	// material color:

	float hsv[3], rgb[4];
	hsv[0] = Hue.GetValue( nowTime );;
	hsv[1] = hsv[2] = rgb[3] = 1.;
	HsvRgb( hsv, rgb );
	glMaterialfv( GL_FRONT, GL_AMBIENT, rgb );
	glMaterialfv( GL_FRONT, GL_DIFFUSE, rgb );

	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
	glEnable( GL_LIGHT1 );

	float xpos = Xpos.GetValue( nowTime );
	float ypos = Ypos.GetValue( nowTime );
	float zpos = Zpos.GetValue( nowTime );
	float ax = ThetaX.GetValue( nowTime );
	float ay = ThetaY.GetValue( nowTime );
	float az = ThetaZ.GetValue( nowTime );
	float sx = Xscale.GetValue(nowTime);
	float sy = Yscale.GetValue(nowTime);
	float sz = Zscale.GetValue(nowTime);
	glPushMatrix( );
		glTranslatef( xpos, ypos, zpos );
		glRotatef( ax,  1., 0., 0. );
		glRotatef( ay,  0., 1., 0. );
		glRotatef( az,  0., 0., 1. );
		glScalef(sx, sy, sz);
		glCallList( ObjectList );
	glPopMatrix( );

	glDisable( GL_LIGHT1 );
	glDisable( GL_LIGHT0 );
	glDisable( GL_LIGHTING );


	// swap the double-buffered framebuffers:

	glutSwapBuffers( );

	// be sure the graphics buffer has been sent:

	glFlush( );
}



 // use glut to display a string of characters using a raster font:

void
DoRasterString( float x, float y, float z, char *s )
{
	char c;			// one character to print

	glRasterPos3f( x, y, z );
	for( ; ( c = *s ) != '\0'; s++ )
	{
		glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, c );
	}
}



 // use glut to display a string of characters using a stroke font:

void
DoStrokeString( float x, float y, float z, float ht, char *s )
{
	char c;			// one character to print

	glPushMatrix( );
		glTranslatef( x, y, z );
		float sf = ht / ( 119.05f + 33.33f );
		glScalef( sf, sf, sf );
		for( ; ( c = *s ) != '\0'; s++ )
		{
			glutStrokeCharacter( GLUT_STROKE_ROMAN, c );
		}
	glPopMatrix( );
}



 // initialize the glut and OpenGL libraries:
 //	also setup display lists and callback functions

void
InitGraphics( void )
{
	// setup the display mode:
	// ( *must* be done before call to glutCreateWindow( ) )
	// ask for color, double-buffering, and z-buffering:

	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
	glutInitWindowSize( INIT_WINDOW_SIZE, INIT_WINDOW_SIZE );
	GrWindow = glutCreateWindow( WINDOWTITLE );
	glutSetWindowTitle( WINDOWTITLE );
	glClearColor( BACKCOLOR[0], BACKCOLOR[1], BACKCOLOR[2], BACKCOLOR[3] );


	// setup the callback routines:
	// DisplayFunc -- redraw the window
	// ReshapeFunc -- handle the user resizing the window
	// KeyboardFunc -- handle a keyboard input
	// MouseFunc -- handle the mouse button going down or up
	// MotionFunc -- handle the mouse moving with a button down
	// PassiveMotionFunc -- handle the mouse moving with a button up*/
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
	// IdleFunc -- what to do when nothing else is going on
	// TimerFunc -- trigger something to happen every so often

	glutSetWindow( GrWindow );
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

	// DO NOT SET THE GLUT IDLE FUNCTION HERE !!
	// glutIdleFunc( NULL );
	// let glui take care of it in InitGlui( )

	glutTimerFunc( 0, NULL, 0 );


	// init the lighting:

	glShadeModel( GL_FLAT );
	glLightModelfv( GL_LIGHT_MODEL_AMBIENT, MulArray3( .2f, White ) );
	glLightfv( GL_LIGHT0, GL_AMBIENT,   Array3( 0., 0., 0. ) );
	glLightf ( GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1. );
	glLightf ( GL_LIGHT0, GL_LINEAR_ATTENUATION, 0. );
	glLightf ( GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0. );
	glLightfv( GL_LIGHT0, GL_DIFFUSE,   Array3( 1., 1., 1. )  );
	glLightfv( GL_LIGHT0, GL_SPECULAR,  Array3( 1., 1., 1. )  );
	glLightfv( GL_LIGHT1, GL_AMBIENT,   Array3( 0., 0., 0. ) );
	glLightf ( GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1. );
	glLightf ( GL_LIGHT1, GL_LINEAR_ATTENUATION, 0. );
	glLightf ( GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0. );
	glLightfv( GL_LIGHT1, GL_DIFFUSE,   Array3( .8f, .8f, .8f )  );
	glLightfv( GL_LIGHT1, GL_SPECULAR,  Array3( .8f, .8f, .8f )  );
	glEnable( GL_NORMALIZE );
	glLightModeli ( GL_LIGHT_MODEL_TWO_SIDE, TRUE );
	glMaterialf ( GL_FRONT, GL_SHININESS, 8. );
	glMaterialfv( GL_FRONT, GL_SPECULAR, MulArray3( .7f, Array3( 1., 1., 1. )  ) );


	
	Xpos.AddTimeValue(    150.f,    0.f );
	Ypos.AddTimeValue(    0.f,    0.f );
	Zpos.AddTimeValue(    0.f,    0.f );
	ThetaX.AddTimeValue(  0.f,    0.f );
	ThetaY.AddTimeValue(  0.f,    0.f );
	ThetaZ.AddTimeValue(  0.f,    0.f );
	Xscale.AddTimeValue(0.f, 1.f);
	Yscale.AddTimeValue(0.f, 1.f);
	Zscale.AddTimeValue(0.f, 1.f);

	Xpos.AddTimeValue(1.f, 150.f);
	Ypos.AddTimeValue(1.f, 1000.f);
	Zpos.AddTimeValue(1.f, 1000.f);
	ThetaX.AddTimeValue(1.f, 0.f);
	ThetaY.AddTimeValue(1.f, 0.f);
	ThetaZ.AddTimeValue(1.f, 0.f);
	Xscale.AddTimeValue(1.f, 2.f);
	Yscale.AddTimeValue(1.f, 2.f);
	Zscale.AddTimeValue(1.f, 2.f);

	Xpos.AddTimeValue(2.f, 1000.f);
	Ypos.AddTimeValue(2.f, 1000.f);
	Zpos.AddTimeValue(2.f, 0.f);
	ThetaX.AddTimeValue(2.f, 90.f);
	ThetaY.AddTimeValue(2.f, 90.f);
	ThetaZ.AddTimeValue(2.f, 0.f);
	Xscale.AddTimeValue(2.f, 1.f);
	Yscale.AddTimeValue(2.f, 1.f);
	Zscale.AddTimeValue(2.f, 1.f);

	Xpos.AddTimeValue(3.f, 1000.f);
	Ypos.AddTimeValue(3.f, 0.f);
	Zpos.AddTimeValue(3.f, 1000.f);
	ThetaX.AddTimeValue(3.f, 0.f);
	ThetaY.AddTimeValue(3.f, 180.f);
	ThetaZ.AddTimeValue(3.f, 0.f);
	Xscale.AddTimeValue(3.f, 0.5f);
	Yscale.AddTimeValue(3.f, 0.5f);
	Zscale.AddTimeValue(3.f, 0.5f);

	Xpos.AddTimeValue(4.f, 150.f);
	Ypos.AddTimeValue(4.f, 1000.f);
	Zpos.AddTimeValue(4.f, 0.f);
	ThetaX.AddTimeValue(4.f, 0.f);
	ThetaY.AddTimeValue(4.f, 0.f);
	ThetaZ.AddTimeValue(4.f, 90.f);
	Xscale.AddTimeValue(4.f, 2.f);
	Yscale.AddTimeValue(4.f, 2.f);
	Zscale.AddTimeValue(4.f, 2.f);

	Xpos.AddTimeValue(5.f, 500.f);
	Ypos.AddTimeValue(5.f, 500.f);
	Zpos.AddTimeValue(5.f, 500.f);
	ThetaX.AddTimeValue(5.f, 180.f);
	ThetaY.AddTimeValue(5.f, 90.f);
	ThetaZ.AddTimeValue(5.f, 45.f);
	Xscale.AddTimeValue(5.f, 0.5f);
	Yscale.AddTimeValue(5.f, 0.5f);
	Zscale.AddTimeValue(5.f, 0.5f);

	Xpos.AddTimeValue(6.f, 1000.f);
	Ypos.AddTimeValue(6.f, 150.f);
	Zpos.AddTimeValue(6.f, 0.f);
	ThetaX.AddTimeValue(6.f, 180.f);
	ThetaY.AddTimeValue(6.f, 0.f);
	ThetaZ.AddTimeValue(6.f, 0.f);
	Xscale.AddTimeValue(6.f, 1.f);
	Yscale.AddTimeValue(6.f, 1.f);
	Zscale.AddTimeValue(6.f, 1.f);

	Xpos.AddTimeValue(7.f, 200.f);
	Ypos.AddTimeValue(7.f, 300.f);
	Zpos.AddTimeValue(7.f, 1000.f);
	ThetaX.AddTimeValue(7.f, 0.f);
	ThetaY.AddTimeValue(7.f, 0.f);
	ThetaZ.AddTimeValue(7.f, 0.f);
	Xscale.AddTimeValue(7.f, 3.f);
	Yscale.AddTimeValue(7.f, 3.f);
	Zscale.AddTimeValue(7.f, 3.f);

	Xpos.AddTimeValue(8.f, 1000.f);
	Ypos.AddTimeValue(8.f, 1000.f);
	Zpos.AddTimeValue(8.f, 1000.f);
	ThetaX.AddTimeValue(8.f, 180.f);
	ThetaY.AddTimeValue(8.f, 90.f);
	ThetaZ.AddTimeValue(8.f, 0.f);
	Xscale.AddTimeValue(8.f, 2.f);
	Yscale.AddTimeValue(8.f, 2.f);
	Zscale.AddTimeValue(8.f, 2.f);

	Xpos.AddTimeValue(9.f, 150.f);
	Ypos.AddTimeValue(9.f, 0.f);
	Zpos.AddTimeValue(9.f, 0.f);
	ThetaX.AddTimeValue(9.f, 0.f);
	ThetaY.AddTimeValue(9.f, 0.f);
	ThetaZ.AddTimeValue(9.f, 0.f);
	Xscale.AddTimeValue(9.f, 1.f);
	Yscale.AddTimeValue(9.f, 1.f);
	Zscale.AddTimeValue(9.f, 1.f);

	for (int i = 0; i <= 9; i++) {
		Hue.AddTimeValue(i, 40. * i);
	}
}




 // initialize the display lists that will not change:

void
InitLists( void )
{
	// create the display of the keytimes:

	KeytimeList = glGenLists( 1 );
	glNewList( KeytimeList, GL_COMPILE );

	for (float i = 0; i <= 9; i++) {
		glPushMatrix();
		glTranslatef(Xpos.GetValue(i ), Ypos.GetValue(i ), Zpos.GetValue(i ));
		glRotatef(ThetaX.GetValue(i ), 1., 0., 0.);
		glRotatef(ThetaY.GetValue(i ), 0., 1., 0.);
		glRotatef(ThetaZ.GetValue(i ), 0., 0., 1.);
		glScalef(SCALE_FACTOR * Xscale.GetValue(i), SCALE_FACTOR * Yscale.GetValue(i), SCALE_FACTOR * Zscale.GetValue(i));
		glutWireIcosahedron();
		glPopMatrix();
	}

	
	glEndList( );

	// create the object:

	ObjectList = glGenLists( 1 );
	glNewList( ObjectList, GL_COMPILE );
		glMaterialfv( GL_BACK, GL_AMBIENT, MulArray3( .4f, White ) );
		glMaterialfv( GL_BACK, GL_DIFFUSE, MulArray3( 1., White ) );
		glMaterialfv( GL_BACK, GL_SPECULAR, Array3( 0., 0., 0. ) );
		glMaterialf ( GL_BACK, GL_SHININESS, 5.f );
		glMaterialfv( GL_BACK, GL_EMISSION, Array3( 0., 0., 0. ) );
		glMaterialfv( GL_FRONT, GL_EMISSION, Array3( 0., 0., 0. ) );
		glScalef(SCALE_FACTOR, SCALE_FACTOR, SCALE_FACTOR);
		glutSolidIcosahedron();
	glEndList( );

	// create the walls:

	WallList = glGenLists( 1 );
	glNewList( WallList, GL_COMPILE );
		glColor3fv( FLOOR_COLOR );
		glBegin( GL_QUADS );
			glVertex3f( LEFT_WALL, FLOOR, FRONT_WALL );
			glVertex3f( LEFT_WALL, FLOOR, BACK_WALL );
			glVertex3f( RIGHT_WALL, FLOOR, BACK_WALL );
			glVertex3f( RIGHT_WALL, FLOOR, FRONT_WALL );
		glEnd( );
		glColor3fv( LEFT_WALL_COLOR );
		glBegin( GL_QUADS );
			glVertex3f( LEFT_WALL, FLOOR, FRONT_WALL );
			glVertex3f( LEFT_WALL, FLOOR, BACK_WALL );
			glVertex3f( LEFT_WALL, CEILING, BACK_WALL );
			glVertex3f( LEFT_WALL, CEILING, FRONT_WALL );
		glEnd( );
	glEndList( );

	// create the axes:

	AxesList = glGenLists( 1 );
	glNewList( AxesList, GL_COMPILE );
		glColor3fv( AXES_COLOR );
		glLineWidth( AXES_WIDTH );
			Axes( 400. );
		glLineWidth( 1. );
	glEndList( );
}


 // initialize the glui window:

void
InitGlui( void )
{
	// setup the glui window:

	glutInitWindowPosition( INIT_WINDOW_SIZE+50, 0 );
	Glui = GLUI_Master.create_glui( (char *) GLUITITLE );


	Glui->add_statictext( (char *) GLUITITLE );
	Glui->add_separator( );

	Glui->add_checkbox( "Axes", &AxesOn );

	Glui->add_checkbox( "Perspective", &WhichProjection );

	Glui->add_checkbox( "Keyframes", &KeytimeOn );

	GLUI_Panel * panel = Glui->add_panel( "Animation" );
		GLUI_RadioGroup *group = Glui->add_radiogroup_to_panel( panel, &AnimateOn, 0, (GLUI_Update_CB) SetAnimate );
			Glui->add_radiobutton_to_group( group, "Off" );
			Glui->add_radiobutton_to_group( group, "On" );

	panel = Glui->add_panel( "Object Transformation" );

		GluiRot = Glui->add_rotation_to_panel( panel, "Rotation", (float *) RotMatrix );
		GluiRot->set_spin( 1. );

		Glui->add_column_to_panel( panel, FALSE );
		GLUI_Translation *scale = Glui->add_translation_to_panel( panel, "Scale",  GLUI_TRANSLATION_Y , &Scale2 );
		scale->set_speed( 0.01f );

		Glui->add_column_to_panel( panel, FALSE );
		GLUI_Translation *trans = Glui->add_translation_to_panel( panel, "Trans XY", GLUI_TRANSLATION_XY, &TransXYZ[0] );
		trans->set_speed( 0.1f );

		Glui->add_column_to_panel( panel, FALSE );
		trans = Glui->add_translation_to_panel( panel, "Trans Z",  GLUI_TRANSLATION_Z , &TransXYZ[2] );
		trans->set_speed( 0.1f );


	panel = Glui->add_panel( "", FALSE );

	Glui->add_button_to_panel( panel, "Reset", RESET, (GLUI_Update_CB) Buttons );
	Glui->add_column_to_panel( panel, FALSE );
	Glui->add_button_to_panel( panel, "Quit", QUIT, (GLUI_Update_CB) Buttons );
	Glui->add_column_to_panel( panel, FALSE );
	Glui->add_checkbox_to_panel( panel, "Debug", &Debug );

	// tell glui what graphics window it needs to post a redisplay to:

	Glui->set_main_gfx_window( GrWindow );

	// set the graphics window's idle function:

	if (AnimateOn)
	{
		GLUI_Master.set_glutIdleFunc(Animate);
	}
	else
	{
		GLUI_Master.set_glutIdleFunc(NULL);
	}
}



 // the keyboard callback:

void
Keyboard( unsigned char c, int x, int y )
{
	if( Debug )
		fprintf( stderr, "DoKeyboard: '%c' (0x%0x)\n", c, c );

	switch( c )
	{
		case 'q':
		case 'Q':
		case ESCAPE:
			Buttons( QUIT );	// will not return here
			break;			// happy compiler

		case 'f':
		case 'F':
			KeytimeOn = ! KeytimeOn;
			break;

		case 'o':
		case 'O':
			WhichProjection = ORTHO;
			break;

		case 'p':
		case 'P':
			WhichProjection = PERSP;
			break;

		default:
			fprintf( stderr, "Don't know what to do with keyboard hit:: '%c' (0x%0x)\n", c, c );
	}


	// synchronize the GLUI display with the variables:

	Glui->sync_live( );

	// force a call to Display( ):

	glutSetWindow( GrWindow );
	glutPostRedisplay( );
}



 // called when the mouse button transitions down or up:

void
MouseButton
(
	int button,		// GLUT_*_BUTTON
	int state,		// GLUT_UP or GLUT_DOWN
	int x, int y		// where mouse was when button hit
)
{
	if( Debug )
		fprintf( stderr, "MouseButton: %d, %d, %d, %d\n", button, state, x, y );

	
	// get the proper button bit mask:

	int b;			// LEFT, MIDDLE, or RIGHT
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
		ActiveButton &= ~b;		// clear the proper bit
}



 // called when the mouse moves while a button is down:

void
MouseMotion( int x, int y )
{
	if( Debug )
		fprintf( stderr, "MouseMotion: %d, %d\n", x, y );


	int dx = x - Xmouse;		// change in mouse coords
	int dy = y - Ymouse;

	if( ActiveButton & LEFT )
	{
		Xrot += ( ANGFACT*dy );
		Yrot += ( ANGFACT*dx );
	}

	if( ActiveButton & MIDDLE )
	{
		Scale += SCLFACT * (float) ( dx - dy );

		// keep object from turning inside-out or disappearing:

		if( Scale < MINSCALE )
			Scale = MINSCALE;
	}

	Xmouse = x;			// new current position
	Ymouse = y;

	glutSetWindow( GrWindow );
	glutPostRedisplay( );
}



 // reset the transformations and the colors:
 //
 // this only sets the global variables --
 // the glut main loop is responsible for redrawing the scene

void
Reset( void )
{
	AnimateOn = TRUE;

	ActiveButton = 0;
	AxesOn = GLUITRUE;
	Debug = GLUIFALSE;
	Scale  = 1.0;
	Scale2 = 0.0;		// because add 1. to it in Display( )
	WhichProjection = PERSP;
	Xrot = Yrot = 0.;
	TransXYZ[0] = TransXYZ[1] = TransXYZ[2] = 0.;

	                  RotMatrix[0][1] = RotMatrix[0][2] = RotMatrix[0][3] = 0.;
	RotMatrix[1][0]                   = RotMatrix[1][2] = RotMatrix[1][3] = 0.;
	RotMatrix[2][0] = RotMatrix[2][1]                   = RotMatrix[2][3] = 0.;
	RotMatrix[3][0] = RotMatrix[3][1] = RotMatrix[3][3]                   = 0.;
	RotMatrix[0][0] = RotMatrix[1][1] = RotMatrix[2][2] = RotMatrix[3][3] = 1.;

	glutSetWindow( GrWindow );
	glutPostRedisplay( );
}


 // called when user resizes the window:

void
Resize( int width, int height )
{
	// don't really need to do anything since window size is
	// checked each time in Display( ):

	glutSetWindow( GrWindow );
	glutPostRedisplay( );
}


void
SetAnimate( int id )
{
	if( AnimateOn )
	{
		GLUI_Master.set_glutIdleFunc( Animate );
	}
	else
	{
		GLUI_Master.set_glutIdleFunc( NULL );
	}
}



 // handle a change to the window's visibility:

void
Visibility( int state )
{
	if( state == GLUT_VISIBLE )
	{
		glutSetWindow( GrWindow );
		glutPostRedisplay( );
	}
	else
	{
		// could optimize by keeping track of the fact
		// that the window is not visible and avoid
		// animating or redrawing it ...
	}
}



// the stroke characters 'X' 'Y' 'Z' :

static float xx[ ] = {
		0., 1., 0., 1.
	      };

static float xy[ ] = {
		-.5, .5, .5, -.5
	      };

static int xorder[ ] = {
		1, 2, -3, 4
		};


static float yx[ ] = {
		0., 0., -.5, .5
	      };

static float yy[ ] = {
		0., .6f, 1., 1.
	      };

static int yorder[ ] = {
		1, 2, 3, -2, 4
		};


static float zx[ ] = {
		1., 0., 1., 0., .25, .75
	      };

static float zy[ ] = {
		.5, .5, -.5, -.5, 0., 0.
	      };

static int zorder[ ] = {
		1, 2, 3, 4, -5, 6
		};


// fraction of the length to use as height of the characters:

#define LENFRAC		0.10f


// fraction of length to use as start location of the characters:

#define BASEFRAC	1.10f

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



float *
MulArray3( float factor, float array0[3] )
{
	static float array[4];

	array[0] = factor * array0[0];
	array[1] = factor * array0[1];
	array[2] = factor * array0[2];
	array[3] = 1.;
	return array;
}


float *
Array3( float a, float b, float c )
{
	static float array[4];

	array[0] = a;
	array[1] = b;
	array[2] = c;
	array[3] = 1.;
	return array;
}



void
HsvRgb( float hsv[3], float rgb[3] )
{
	// guarantee valid input:

	float h = hsv[0] / 60.f;
	while( h >= 6.f )	h -= 6.;
	while( h <  0.f ) 	h += 6.;

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
	
	float i = (float)floor( h );
	float f = h - i;
	float p = v * ( 1.f - s );
	float q = v * ( 1.f - s*f );
	float t = v * ( 1.f - ( s * (1.f-f) ) );
	float r, g, b;

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

#include "keytime.cpp"
