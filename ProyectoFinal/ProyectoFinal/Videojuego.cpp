/// <summary>
/// Simple racing game using OpenGL as graphics library. The road map is loaded based o the player position so it never ends
/// The game enables changing to a night mode, fog mode, wired mode and a simple interface. The punctuation of the game is showed on console
/// </summary>
#define PROYECTO "Beach City Racing"
//Import the necessary libraries to use OpenGL and this project
#include <iostream>
#include <GL/freeglut.h>
#include <time.h>
#include <sstream>
#include <Utilidades.h>
//Defining some variables that are needed for the project
static float distancia = 0; //distance
static float velocidad = 0; //speed
static const int tasaFPS = 60; //FPSr rate
using namespace std;
float pxc = 0; //define x coordinate of the camera
float pyc = 1; //define y coordinate of the camera
float pzc = 0; //define z coordinate of the camera
float pxl = 0; //define x coordinate of the point of interest of the camera
float pyl = 1; //define y coordinate of the point of interest of the camera
float pzl = -1; //define z coordinate of the point of interest of the camera
float angulo = 0;
float angulo2 = 0;
static GLuint tex[5]; //Array for the textures
//Variables to enable/disble the different game modes
bool light = FALSE;
bool wired = FALSE;
bool cam = FALSE;
bool niebla = FALSE;
//Initial coordinates in the z axis to generate the road and the environment. As the player moves forward, they are changed.
int zmin = 3;
int zmax = -3;
int zmax2 = -10;
int zmax3 = -15;
int zmax4 = -5;
float giro; 
int puntuacion = 0;
// GLuint references for the 3D objects
static GLuint triangulo; //triangle
static GLuint rectangulo; //rectangle
static GLuint flecha; //arrow
static GLuint arbol; //tree
static GLuint estrella; //Basic star
static GLuint estrella3D; //3D Star

void init()
// Self-init function
{

	cout << "Version: OpenGL " << glGetString(GL_VERSION) << endl;
	glClearColor(0.0, 0.0, 0.0, 1.0); // Black background colour
	std::cout << "¡Welcome to Rose Cuarz´s Road! \n Game controls:\n Up/down arrows: accelerate/brake \n Right & left arrows: direction \n l: Night mode \n n: Fog mode \n s: Wired mode \n c: Shows a simple user Interface \n f: Total brake \n Pick stars on the road to increase your score ¡Good luck! \n" << std::endl;
	std::cout << "Tu puntuacion: " << puntuacion << std::endl;
	GLfloat difuso[] = { 0.8,0.8,0.8,1 };
	GLfloat especular[] = { 0.3,0.3,0.3,1 };

	//Creates and stores a reference for a rectangle shape
	rectangulo = glGenLists(1); // Obtains the ID for this shape
	glNewList(rectangulo, GL_COMPILE);
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, difuso);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, especular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 3);
	glScalef(0.2, 1, 0.001);
	glutSolidCube(0.3);
	glPopMatrix();
	glEndList();

	//Creates and stores a reference for a triangle shape
	triangulo = glGenLists(1); // Obtains the ID for this shape
	glNewList(triangulo, GL_COMPILE); // Opens the list of the reference
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, difuso);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, especular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 3);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(0, 0.125, 0);
	glVertex3f(-0.075, 0, 0);
	glVertex3f(0.075, 0, 0);
	glEnd();
	glPopMatrix();
	glEndList();

	//Creates and stores a reference for an arrow shape
	flecha = glGenLists(1);
	glNewList(flecha, GL_COMPILE);
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, difuso);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, especular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 3);
	glCallList(rectangulo);
	glTranslatef(0,0.15,0);
	glCallList(triangulo);
	glPopMatrix();
	glEndList();

	////Creates and stores a reference for a tree
	arbol = glGenLists(1);
	glNewList(arbol, GL_COMPILE);
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, difuso);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, especular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 3);
	glColor3f(0.7, 0.5, 0.8);
	glTranslatef(0, 0, 0.0);
	glRotatef(-90, 1, 0, 0);
	glutSolidCylinder(0.5, 2, 20, 20);
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.9, 0.5, 0.8);
	glTranslatef(0, 2, 0.0);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(1.7, 5, 30, 30);
	glPopMatrix();
	glColor3f(1, 1, 1);
	glEndList();

	////Creates and stores a reference for a star shape
	estrella = glGenLists(1); // Obtains the ID of yhe list
	glNewList(estrella, GL_COMPILE); 
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, difuso);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, especular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 3);
	glBegin(GL_TRIANGLE_STRIP);

	glVertex3f(0.0*cos(0 * 2 * 3.1415926 / 6) - 1.0*sin(0 * 2 * 3.1415926 / 6), 1.0*cos(0 * 2 * 3.1415926 / 6) + 0.0*sin(0 * 2 * 3.1415926 / 6), 0.0);
	glVertex3f(0.0*cos(0 * 2 * 3.1415926 / 6) - 0.7*sin(0 * 2 * 3.1415926 / 6), 0.7*cos(0 * 2 * 3.1415926 / 6) + 0.0*sin(0 * 2 * 3.1415926 / 6), 0.0);
	glVertex3f(0.0*cos(2 * 2 * 3.1415926 / 6) - 1.0*sin(2 * 2 * 3.1415926 / 6), 1.0*cos(2 * 2 * 3.1415926 / 6) + 0.0*sin(2 * 2 * 3.1415926 / 6), 0.0);
	glVertex3f(0.0*cos(2 * 2 * 3.1415926 / 6) - 0.7*sin(2 * 2 * 3.1415926 / 6), 0.7*cos(2 * 2 * 3.1415926 / 6) + 0.0*sin(2 * 2 * 3.1415926 / 6), 0.0);
	glVertex3f(0.0*cos(4 * 2 * 3.1415926 / 6) - 1.0*sin(4 * 2 * 3.1415926 / 6), 1.0*cos(4 * 2 * 3.1415926 / 6) + 0.0*sin(4 * 2 * 3.1415926 / 6), 0.0);
	glVertex3f(0.0*cos(4 * 2 * 3.1415926 / 6) - 0.7*sin(4 * 2 * 3.1415926 / 6), 0.7*cos(4 * 2 * 3.1415926 / 6) + 0.0*sin(4 * 2 * 3.1415926 / 6), 0.0);
	glVertex3f(0.0*cos(0 * 2 * 3.1415926 / 6) - 1.0*sin(0 * 2 * 3.1415926 / 6), 1.0*cos(0 * 2 * 3.1415926 / 6) + 0.0*sin(0 * 2 * 3.1415926 / 6), 0.0);
	glVertex3f(0.0*cos(0 * 2 * 3.1415926 / 6) - 0.7*sin(0 * 2 * 3.1415926 / 6), 0.7*cos(0 * 2 * 3.1415926 / 6) + 0.0*sin(0 * 2 * 3.1415926 / 6), 0.0);

	glEnd();
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, difuso);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, especular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 3);
	glBegin(GL_TRIANGLE_STRIP);

	//glColor3f(0.0, 0.0, 0.8);

	glVertex3f(0.0*cos(0 * 2 * 3.1415926 / 6) + 1.0*sin(0 * 2 * 3.1415926 / 6), -1.0*cos(0 * 2 * 3.1415926 / 6) + 0.0*sin(0 * 2 * 3.1415926 / 6), 0.0);
	glVertex3f(0.0*cos(0 * 2 * 3.1415926 / 6) + 0.7*sin(0 * 2 * 3.1415926 / 6), -0.7*cos(0 * 2 * 3.1415926 / 6) + 0.0*sin(0 * 2 * 3.1415926 / 6), 0.0);
	glVertex3f(0.0*cos(2 * 2 * 3.1415926 / 6) + 1.0*sin(2 * 2 * 3.1415926 / 6), -1.0*cos(2 * 2 * 3.1415926 / 6) + 0.0*sin(2 * 2 * 3.1415926 / 6), 0.0);
	glVertex3f(0.0*cos(2 * 2 * 3.1415926 / 6) + 0.7*sin(2 * 2 * 3.1415926 / 6), -0.7*cos(2 * 2 * 3.1415926 / 6) + 0.0*sin(2 * 2 * 3.1415926 / 6), 0.0);
	glVertex3f(0.0*cos(4 * 2 * 3.1415926 / 6) + 1.0*sin(4 * 2 * 3.1415926 / 6), -1.0*cos(4 * 2 * 3.1415926 / 6) + 0.0*sin(4 * 2 * 3.1415926 / 6), 0.0);
	glVertex3f(0.0*cos(4 * 2 * 3.1415926 / 6) + 0.7*sin(4 * 2 * 3.1415926 / 6), -0.7*cos(4 * 2 * 3.1415926 / 6) + 0.0*sin(4 * 2 * 3.1415926 / 6), 0.0);
	glVertex3f(0.0*cos(0 * 2 * 3.1415926 / 6) + 1.0*sin(0 * 2 * 3.1415926 / 6), -1.0*cos(0 * 2 * 3.1415926 / 6) + 0.0*sin(0 * 2 * 3.1415926 / 6), 0.0);
	glVertex3f(0.0*cos(0 * 2 * 3.1415926 / 6) + 0.7*sin(0 * 2 * 3.1415926 / 6), -0.7*cos(0 * 2 * 3.1415926 / 6) + 0.0*sin(0 * 2 * 3.1415926 / 6), 0.0);

	glEnd();
	glEndList(); // Closes the star reference list

	//G
	estrella3D = glGenLists(1); // Creates and stores a reference for a 3D star shape
	glNewList(estrella3D, GL_COMPILE);
	glPushAttrib(GL_CURRENT_BIT);
	for (int i = 0; i < 5; i++) {
		glPushMatrix();
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, difuso);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, especular);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 3);
		glColor3f(1, i*0.1, 0.9);
		glRotatef(360 / 5 * i, 0, 1, 0);
		glCallList(estrella);
		glPopMatrix();
	}
	glPopAttrib();
	glEndList();

	//Defines ambient light
	GLfloat Al0[] = { 0.05,0.05,0.05,1.0 };
	GLfloat Dl0[] = { 0.05,0.05,0.05,1.0 };
	GLfloat Sl0[] = { 0,0,0,0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, Al0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Dl0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Sl0);
	glEnable(GL_LIGHT0);

	// Defines the lights for the car´s flashlights
	GLfloat Al2[] = { 0.2,0.2,0.2,1.0 };
	GLfloat Dl2[] = { 1.0,1.0,1.0,1.0 };
	GLfloat Sl2[] = { 0.3,0.3,0.3,1.0 };
	glLightfv(GL_LIGHT2, GL_AMBIENT, Al2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, Dl2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, Sl2);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 25.0);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 20.0);
	glEnable(GL_LIGHT2);
	
	// light for the streetlight 1
	glLightfv(GL_LIGHT3, GL_AMBIENT, Al2);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, Dl2);
	glLightfv(GL_LIGHT3, GL_SPECULAR, Sl2);
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 20.0);
	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 10.0);
	glEnable(GL_LIGHT3);

	// light for the streetlight 2
	glLightfv(GL_LIGHT4, GL_AMBIENT, Al2);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, Dl2);
	glLightfv(GL_LIGHT4, GL_SPECULAR, Sl2);
	glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 20.0);
	glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, 10.0);
	glEnable(GL_LIGHT4);

	// light for the streetlight 3
	glLightfv(GL_LIGHT5, GL_AMBIENT, Al2);
	glLightfv(GL_LIGHT5, GL_DIFFUSE, Dl2);
	glLightfv(GL_LIGHT5, GL_SPECULAR, Sl2);
	glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, 20.0);
	glLightf(GL_LIGHT5, GL_SPOT_EXPONENT, 10.0);
	glEnable(GL_LIGHT5);

	//Road´s tecture
	glEnable(GL_TEXTURE_2D);
	// obtains an ID for it
	glGenTextures(1, &tex[0]);
	// Selects the texture
	glBindTexture(GL_TEXTURE_2D, tex[0]);
	// loads the image
	loadImageFile("road.jpg");

	//Texture for the advert post
	glGenTextures(1, &tex[1]);
	glBindTexture(GL_TEXTURE_2D, tex[1]);
	loadImageFile("steven.jpg");

	//Backgorund/sky texture
	glGenTextures(1, &tex[2]);
	glBindTexture(GL_TEXTURE_2D, tex[2]);
	loadImageFile("fondo2.jpg");

	//Texture for the metal part of the advert post
	glGenTextures(1, &tex[3]);
	glBindTexture(GL_TEXTURE_2D, tex[3]);
	loadImageFile("metal.jpg");

	//Ground texture
	glGenTextures(1, &tex[4]);
	glBindTexture(GL_TEXTURE_2D, tex[4]);
	loadImageFile("suelo.jpg");
	
	glEnable(GL_DEPTH_TEST);
}
void display()
// Function that draws the map and game objects
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Shows speed on the title of the game window
	stringstream titulo;
	titulo << "Velocidad: " << velocidad << " m/s "; //Showed 1 time per second
	glutSetWindowTitle(titulo.str().c_str());

	//Light mode
	if (light == FALSE) {
		glDisable(GL_LIGHTING);
	}
	else {
		glEnable(GL_LIGHTING);
	}
	//Wired mode
	if (niebla == FALSE) {
		glDisable(GL_FOG);
	}
	else {
		//Day fog
		glEnable(GL_FOG);
		if (light == FALSE) {
			static GLfloat cniebla[] = { 1.0,1.0,1.0,1.0 }; // Colour of the fog
			glFogfv(GL_FOG_COLOR, cniebla);
			glFogf(GL_FOG_DENSITY, 0.3);
		}
		//Night fog
		else {
			static GLfloat cniebla[] = { 0.1,0.1,0.1,1.0 }; // Colour of the fog
			glFogfv(GL_FOG_COLOR, cniebla);
			glFogf(GL_FOG_DENSITY, 0.3);
		}
		
		
	}

	//Wired mode
	if (wired == FALSE) {
		glEnable(GL_TEXTURE_2D);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else {
		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	//Function to update the z values for the procedural generated road
	if (pzc < zmax) {
		zmin = zmin - 3;
		zmax = zmax - 3;
	}
	if (pzc > zmin) {
		zmin = zmin + 3;
		zmax = zmax + 3;
	}
	//Function to update the z values for the procedural generated environment and decorations
	if (pzc < zmax2-1.5) {
		zmax2 = zmax2 - 10;
	}
	if (pzc < zmax3 - 2) {
		zmax3 = zmax3 - 15;
	}
	
	if (pzc < zmax4 - 2) {
		zmax4 = zmax4 - 15;
	}
	//Define the elements that move in a relative position to the game camera, such as the UI or the car´s spotlights
	if (cam == TRUE) {
		
		glPushMatrix();
		
		glTranslatef(0.0, -0.7, -0.5);
		glRotatef(angulo2, 0, 0, 1);
		glCallList(flecha);
		glPopMatrix();
		glPushMatrix();
		glColor3f(1.0, 0.2, 0.8);
		glTranslatef(-0.8, -0.86, -0.5);
		glScalef(1.3,velocidad,1);
		glCallList(rectangulo);
		glPopMatrix();
		glColor3f(1, 1, 1);

	}

	//Rotation of the velocity vector
	float pxlaux = pxl;
	float pzlaux = pzl;

	pxl = cosf(angulo)*pxlaux + sinf(angulo)*pzlaux;
	pzl = -sinf(angulo)*pxlaux + cosf(angulo)*pzlaux;

	angulo = 0;

	//Calculation of the camera´s position for each frame
	pxc = pxc + (distancia*pxl);
	pzc = pzc + (distancia*pzl);

	GLfloat posicion[] = { 0.0, 10.0, 0.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, posicion);

	//Defines car´s spotlights
	GLfloat posicion2[] = { 0, 0.7, 0, 1.0 }; //Position of the light
	GLfloat dir_central[] = { 0.0, -1.0, -1.5 }; //angle of the camera
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, dir_central);
	glLightfv(GL_LIGHT2, GL_POSITION, posicion2);

	//Defines the position of the camera and its point of interest (the point where it´s looking at)
	gluLookAt(pxc, pyc, pzc, pxc + pxl, pyl, pzc + pzl, 0, 1, 0);
	
	//Generation and update of the trees and their position
	int z = zmax3;
	for (int i = 1; i <= 3; i++) {
		float xini = 5 * sin(z * PI / 25);
		glPushMatrix();
		glTranslatef(xini-5, 0, z);
		glCallList(arbol);
		glPopMatrix();
		z = z - 15;
	}
	z = zmax4;
	for (int i = 1; i <= 3; i++) {
		float xini = 5 * sin(z * PI / 25);
		glPushMatrix();
		glTranslatef(xini + 5, 0, z);
		glCallList(arbol);
		glPopMatrix();
		z = z - 15;
	}
	
	//Generation and update of the streetlights and their position, relative to the road´s sinusoidal shape
	float xini = 5 * sin(zmax2 * PI / 25);
	//Streetlight 1
	GLfloat posicion3[] = { xini, 7.5, zmax2+0.5, 1.0 };
	GLfloat dir_central2[] = { 0.0, -1.0, 0.0 };
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, dir_central2);
	glLightfv(GL_LIGHT3, GL_POSITION, posicion3);

	xini = 5 * sin((zmax2-10) * PI / 25);
	//Streetlight 2
	GLfloat posicion4[] = { xini, 7.5, zmax2 -10 + 0.5, 1.0 };
	GLfloat dir_central4[] = { 0.0, -1.0, 0.0 };
	glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, dir_central4);
	glLightfv(GL_LIGHT4, GL_POSITION, posicion4);

	xini = 5 * sin((zmax2 - 20) * PI / 25);
	//Streetlight 3
	GLfloat posicion5[] = { xini, 7.5, zmax2 - 20 + 0.5, 1.0 };
	GLfloat dir_central5[] = { 0.0, -1.0, 0.0 };
	glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, dir_central5);
	glLightfv(GL_LIGHT5, GL_POSITION, posicion5);


	//Define the road texture
	glBindTexture(GL_TEXTURE_2D, tex[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	
	//Define the road material
	GLfloat difuso[] = { 0.8,0.8,0.8,1 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, difuso);
	GLfloat especular[] = { 0.3,0.3,0.3,1 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, especular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 3);
	
	//Generation of the road based on a sinusoidal function
	
	z = zmin;
	//Calculation of the value of the x centered at the z value of the sinusoidal function
	xini = 5 * sin(z * PI / 25);
	float angulorad = atan((PI / 5) * cos(z * PI / 25));
	//Coordinate at the left point of the road at that position of z in the sinusoidal function
	float tz = -1 / sqrtf(1 + (tanf(angulorad)*tanf(angulorad)));
	float tx = tanf(angulorad) / sqrtf(1 + (tanf(angulorad)*tanf(angulorad)));
	//Calculation of the left and right points of the quad for the road at that z value of the sinusoidal function
	GLfloat v0[3] = { 3 * tz + xini, 0.0, 3 * tx + z };
	GLfloat v1[3] = { -3 * tz + xini, 0.0, -3 * tx + z };
	int zsig = zmin - 3;

	for (int i = 1; i <= 20; i++) {
		//X value centered on the zsig point of the sinusoidal function
		float xfin = 5 * sin(zsig * PI / 25);
		//Obtain the the final angle in radians
		float anguloradfin = atan((PI / 5) * cos(zsig * PI / 25));   
		//Left point of the road at that x value
		float tz2 = -1 / sqrtf(1 + (tanf(anguloradfin)*tanf(anguloradfin)));
		float tx2 = tanf(anguloradfin) / sqrtf(1 + (tanf(anguloradfin)*tanf(anguloradfin)));
		//Calculation of the left and right points of the quad for the road at that zsig value of the sinusoidal function
		GLfloat v2[3] = { 3 * tz2 + xfin, 0.0, 3 * tx2 + zsig };
		GLfloat v3[3] = { -3 * tz2 + xfin, 0.0, -3 * tx2 + zsig };
		//Draw the road wuad
		quad(v0, v1, v3, v2, 60, 60);
		//Decrement zsig
		zsig = zsig - 3;
		//Update the values for the next road
		v0[0] = v2[0];
		v0[1] = v2[1];
		v0[2] = v2[2];
		v1[0] = v3[0];
		v1[1] = v3[1];
		v1[2] = v3[2];

	}
	
	//Generation of the forund and its texture
	glBindTexture(GL_TEXTURE_2D, tex[4]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	z = zmax2;
	for (int i = 1; i <= 2; i++) {

		GLfloat v0[3] = { -30,-0.01,z+20 };
		GLfloat v1[3] = { 30,-0.01,z + 20 };
		GLfloat v2[3] = { -30,-0.01,z - 20 };
		GLfloat v3[3] = { 30,-0.01,z - 20 };

		quad(v0, v1, v3, v2, 200, 200);

		z = z - 20;
	}


	//Advert post texture
	glBindTexture(GL_TEXTURE_2D, tex[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Calculation of the position of the advert
	z = zmax2;
	for (int i = 1; i <= 3; i++) {

		float xini = 5 * sin(z * PI / 25);
		float angulorad = atan((PI / 5) * cos(z * PI / 25));   //Obtengo el angulo en radianes

		if (pzc <= z && pxc >= xini - 0.7 && pxc <= xini + 0.7) {
			puntuacion += 1;
			std::cout << "Tu puntuacion: " << puntuacion << std::endl;
			zmax2 = zmax2 - 10;
		}else {
		//Draw the 3D start that increases the punctuation every 2 posts
		glPushMatrix();
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, difuso);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, especular);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 3);
		glTranslatef(xini, 1, z);
		glScalef(0.7, 0.7, 0.7);
		glRotatef(giro, 0, 1, 0);
		glCallList(estrella3D);
		glPopMatrix();
	}
	    
		float tz = -1 / sqrtf(1 + (tanf(angulorad)*tanf(angulorad)));
		float tx = tanf(angulorad) / sqrtf(1 + (tanf(angulorad)*tanf(angulorad)));
		//Final coordinates for the advert post 
		GLfloat v0[3] = { 3 * tz + xini, 3.0, 3 * tx + z };
		GLfloat v1[3] = { -3 * tz + xini, 3.0, -3 * tx + z };
		GLfloat v2[3] = { 3 * tz + xini, 6.0, 3 * tx + z };
		GLfloat v3[3] = { -3 * tz + xini, 6.0, -3 * tx + z };
		GLfloat difuso2[] = { 0.8,0.8,0.8,1 };
		quad(v0, v1, v3, v2, 60, 60);
		z = z - 10;

	}

	//Draws and calculates the position of the metal posts of the advert
	glBindTexture(GL_TEXTURE_2D, tex[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	z = zmax2;
	for (int i = 1; i <= 3; i++) {

		float xini = 5 * sin(z * PI / 25);
		float angulorad = atan((PI / 5) * cos(z * PI / 25));   //Obtengo el angulo en radianes

															   //Punto a la izquierda ini
		float tz = -1 / sqrtf(1 + (tanf(angulorad)*tanf(angulorad)));
		float tx = tanf(angulorad) / sqrtf(1 + (tanf(angulorad)*tanf(angulorad)));

		GLfloat v0[3] = { 3 * tz + xini, 0.0, 3 * tx + z };
		GLfloat v1[3] = { 2.5 * tz + xini, 0.0, 2.5 * tx + z };
		GLfloat v2[3] = { 3 * tz + xini, 3.0, 3 * tx + z };
		GLfloat v3[3] = { 2.5 * tz + xini, 3.0, 2.5 * tx + z };
		glPushMatrix();
		//glColor3f(0.7, 0.5, 0.8);
		//glColor3f(0.2, 0.2, 0.2);
		quad(v0, v1, v3, v2, 30, 30);
		glPopMatrix();

		GLfloat v4[3] = { -3 * tz + xini, 0.0, -3 * tx + z };
		GLfloat v5[3] = { -2.5 * tz + xini, 0.0, -2.5 * tx + z };
		GLfloat v6[3] = { -3 * tz + xini, 3.0, -3 * tx + z };
		GLfloat v7[3] = { -2.5 * tz + xini, 3.0, -2.5 * tx + z };
		GLfloat difuso2[] = { 0.8,0.8,0.8,1 };
		glPushMatrix();
		//glColor3f(0.2, 0.2, 0.2);
		quad(v5, v4, v6, v7, 30, 30);
		glPopMatrix();

		

		z = z - 10;
		

	}
	//glColor3f(1, 1, 1);

	//Background texture
	glBindTexture(GL_TEXTURE_2D, tex[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//Define the way to combine the texture
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	//Generation of a cilinder that acts as the sky
	glPushMatrix();
	glTranslatef(pxc, 70, pzc);
	glRotatef(90, 1, 0, 0);
	glutSolidCylinder(30, 80, 50, 50);
	glPopMatrix();
	glPopAttrib();

	glutSwapBuffers();

}void onKey(int specialKey, int x, int y)
// Function that handles the input
{

	switch (specialKey) {
	case GLUT_KEY_LEFT:
		angulo = angulo + (PI*2 / 360);
		angulo2 = angulo2 + 2;

		if (angulo == 360) { angulo = 0;  angulo2 = 0;
		}
		break;
	case  GLUT_KEY_RIGHT:
		angulo = angulo - (PI * 2 / 360);
		angulo2 = angulo2 - 2;
		if (angulo == 360) { angulo = 0;  angulo2 = 0;
		}

		break;
	case GLUT_KEY_UP:
		velocidad = velocidad + 0.1;

		break;
	case  GLUT_KEY_DOWN:
		velocidad = velocidad - 0.1;
		if (velocidad < 0.0002) {
			velocidad = 0;
		}

		break;
	}
	glutPostRedisplay();
}void onKey2(unsigned char tecla, int x, int y)
// Another input handling function for the different vision modes
{
	
	switch (tecla) {
	case 'l':
		light = !light;
		break;
	case 's':
		wired = !wired;
		break;
	case 'c':
		cam = !cam;
		break;
	case 'n':
		niebla = !niebla;
		break;
	case 'f':
		velocidad = 0;
		break;
	case 27: // Pulso escape
		exit(0);
	}
	glutPostRedisplay();
}void reshape(GLint w, GLint h)
// Function that resizes the game based on the size of the game window
{
	// We use the whole viewport
	glViewport(0, 0, w, h);
	// Define the proyection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float razon = (float)w / h;
	/* Perspective camera */
	gluPerspective(120, razon, 0.1, 30);
}void muestraFPS()
// Calculates the FPS Rate and shows it on the title of the game window
{
	int ahora, tiempo_transcurrido;
	static int antes = 0;
	static int FPS = 0;
	//stringstream titulo;
	//Counts the number of calls each second
	FPS++;
	ahora = glutGet(GLUT_ELAPSED_TIME); //Time since begining
	tiempo_transcurrido = ahora - antes; //Time elapsed
	if (tiempo_transcurrido>1000) { //after a second
		antes = ahora; //Update the before and now variables
		FPS = 0; //Reset the count
	}
}void onTimer(int valor)
// Timer function to control the spped 
{
	//std::cout << min << std::endl;
	//Calculamos el tiempo transcurrido desde la última vez
	static int antes = glutGet(GLUT_ELAPSED_TIME);
	float ahora, tiempo_transcurrido;
	ahora = glutGet(GLUT_ELAPSED_TIME); //Tiempo transcurrido desde el inicio
	tiempo_transcurrido = (ahora - antes) / 1000; //Tiempo transcurrido desde antes en sg.
	distancia = tiempo_transcurrido*velocidad;
	//std::cout << tiempo_transcurrido << std::endl;
	antes = ahora;
	giro = giro + 3;
	glutTimerFunc(1000 / tasaFPS, onTimer, tasaFPS); // Se encola un nuevo timer
	glutPostRedisplay();
}
void main(int argc, char** argv)
// Main function of the game
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	//Size of the game window
	glutInitWindowSize(500, 500);
	//Screen position
	glutInitWindowPosition(50, 600 - 400);
	//Creates the window
	glutCreateWindow("Interfaz de conducción");
	//Callbacks register
	//Display
	glutDisplayFunc(display);
	//Reshape
	glutReshapeFunc(reshape);

	glutTimerFunc(1000 / tasaFPS, onTimer, tasaFPS); // Initialization of the timer function
	glutSpecialFunc(onKey); // Initialization of the input function
	glutKeyboardFunc(onKey2); // Initialization of the input function
	init(); //Init function
	glutMainLoop(); //Main game loop function
}