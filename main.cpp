#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000
#include <windows.h>
#include <MMSystem.h>

using namespace std;
int iFondo = 0;
int iDibujo = 1;
int ipared = 2;
int ipuerta = 6;
typedef enum
{FONDO1,FONDO2,FONDO3,FONDO4,DIBUJO1,DIBUJO2,DIBUJO3,DIBUJO4,pared1,pared2,pared3,pared4,puerta1,puerta2,puerta3,puerta4,Sala,Cochera,Patio,Cuarto1,Cuarto2,Pasillo,Bano,Cocina,Carro1,Carro2,Carro3,Radio1,Radio2,Radio3,Luces1,Luces2}
opcionesMenu;
void LineaCubo(int x);
float posXPericote = 6.0;
float posYPericote = -1;
float posYPJ=0.0,PY=0.0,PA=0;
float RED1=0.0, GREEN1=0.0, BLUE1=0.0,RED2=0.0,GREEN2=0.0,BLUE2=0.0,RED3=0.0,GREEN3=0.0,BLUE3=0.0,RED4=0.0,GREEN4=0.0,BLUE4=0.0;
int random = 0;
float colores[9][3] = {
{0.035 , 0.843 , 0.843}, // 0 - cielo
{ 0.06f, 0.25f, 0.13f}, // 1 - verde oscuro
{ 0.921 , 0.894 , 0.635}, // 2 - beige
{0.686 , 0.682 , 0.674}, // 3 - PLOMO
{ 0.12f, 0.50f, 0.26f}, // 4 - verde claro
{ 0.20f, 0.14f, 0.66f}, // 5 - azul claro
{0.921 , 0.415 , 0.321},// 6 -  naranja
{ 0.419 , 0.964 , 0.533},// 7 -  verde claro
{0 , 0 ,0} // 8 - negro

};
float radio=2,calx,calz;
GLUquadricObj *cilindro;
float posX=0,posY=0,posZ=0;
int girax = 0, giray = 0, giraz= 0 ,zoom=2;
float angle=0,a=1;
double rx=100,ry=-230,rz=6,px=100,py=300,pz=6,tx=0,ty=0,tz=1;

float ratio = WINDOW_WIDTH * 1.0 / WINDOW_HEIGHT;
void idleFunc();

void vehiculo();
// @param w : ancho de la ventana
 // @param h :largo de la ventana
void reshape(int w, int h) // GLsizei para entero no negativo
{
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	//GOD!
	glViewport(0, 0, w, h);
	// Set the correct perspective.
	gluPerspective(90.0f, ratio, 0.1f, 900.0f);
	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);

}
/*void initGL(void) {
glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Negra y opaca
glShadeModel(GL_FLAT);
glEnable(GL_DEPTH_TEST);

}*/


//LUCES
GLfloat Ambient[] = { 0.8, 0.8, 0.8,1.0 };
GLfloat Diffuse[] = {1.0, 1.0, 0.5, 1.0}; // Luz ambiente de la fuente
GLfloat Specular[] = {0.3, 0.5, 1.0, 1.0}; // Luz especular

GLfloat mat1_ambiente[] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat mat1_difusa[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat1_especular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat1_Position3[] = {33.0, 54.0, 7.0, 1.0};

GLfloat Position[] = {20.0, 30.0, 50.0, 1.0}; // Posicion de la luz
GLfloat Position2[] = {30.0, 50.0, 3.0, 1.0};
void Dia();
void MediaNoche();

void Dia()
{
//glClearColor(0.0, 0.0, 0.0, 0.0); // Color de Fondo
//glEnable(GL_TEXTURE_2D);
//glShadeModel (GL_SMOOTH);
	 // Aquí va, verificarlo en el repintado
glPushMatrix();
glLightfv(GL_LIGHT0, GL_POSITION, Position);
glMaterialfv(GL_FRONT, GL_AMBIENT, Ambient);
glMaterialfv(GL_FRONT, GL_DIFFUSE, Diffuse);
//glMaterialfv(GL_FRONT, GL_SPECULAR, Specular);
glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Position2);

glEnable(GL_LIGHTING); //Activar luces
glEnable(GL_LIGHT0);
glEnable(GL_LIGHT1);
//glEnable(GL_LIGHT0);
glEnable(GL_COLOR_MATERIAL); //Activar colores definidos al objeto*/
glClearDepth(1.0); // Configuramos Depth Buffer
glEnable(GL_DEPTH_TEST);// Habilitamos Depth Testing
glDepthFunc(GL_LEQUAL); // Tipo de Depth Testing a realizar
glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
}
void MediaNoche()
{
glClearColor(0.0, 0.0, 0.0, 0.0); // Color de Fondo
//glEnable(GL_TEXTURE_2D);
//glShadeModel (GL_SMOOTH);

//glPopMatrix();
//glPushMatrix();
glLightfv(GL_LIGHT0, GL_POSITION, mat1_Position3);
glMaterialfv(GL_FRONT, GL_SPECULAR, mat1_especular);
glMaterialf(GL_FRONT, GL_SHININESS, 65);
//glPopMatrix();
//glLightfv(GL_LIGHT0, GL_POSITION, mat1_Position3);
//glMaterialfv(GL_FRONT, GL_AMBIENT, Ambient);
//glMaterialfv(GL_FRONT, GL_DIFFUSE, Diffuse);
//glMaterialfv(GL_FRONT, GL_SPECULAR, Specular);
glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION,Position2);

glEnable(GL_LIGHTING); //Activar luces
glEnable(GL_LIGHT0);
//glEnable(GL_LIGHT0);
glEnable(GL_COLOR_MATERIAL); //Activar colores definidos al objeto*/
glClearDepth(1.0); // Configuramos Depth Buffer
glEnable(GL_DEPTH_TEST);// Habilitamos Depth Testing
glDepthFunc(GL_LEQUAL); // Tipo de Depth Testing a realizar
glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
}

void idleFunc2 (){
	
glutPostRedisplay();
if(posX<50){
posX+=0.5;
}else{
if(angle<90){
angle+=0.5;
}else{
if(posY<300)
 posY+=0.5;
}
	
}
}




void idleFunc3 (){
	
glutPostRedisplay();
if(posY>0){
 posY-=0.5;
}else{
if(angle>0){
angle-=0.5;
}else{
if(posX>0)
posX-=0.5;	
}
}
}

void mover_PJ(){
glutPostRedisplay();
 if(posYPJ>-650){
      if(PY<1&&PA<20.0){ 
	      PY+=0.05;
		  PA+=0.1;
	   posYPJ -= 0.1;
	  }else
	      PY=0;
		  PA=0;
        posYPJ -= 0.1;
    }
    else{
        posYPJ = 0.0;
    }
}



void onMenu(int opcion) {
switch(opcion) {
case FONDO1:
iFondo = 0;
break;
case FONDO2:
iFondo = 1;
break;
case FONDO3:
iFondo = 2;
break;
case FONDO4:
iFondo = 7;
break;
case DIBUJO1:
iDibujo = 3;
break;
case DIBUJO2:
iDibujo = 4;
break;
case DIBUJO3:
iDibujo = 5;
break;
case DIBUJO4:
iDibujo = 6;
break;

case pared1:
ipared = 3;
break;
case pared2:
ipared = 4;
break;
case pared3:
ipared  = 5;
break;
case pared4:
ipared  = 6;
break;

case puerta1:
ipuerta = 3;
break;
case puerta2:
ipuerta = 4;
break;
case puerta3:
ipuerta  = 5;
break;
case puerta4:
ipuerta  = 6;
break;

}
glutPostRedisplay();
}

void onMenu2(int opcion) {
switch(opcion) {
case Sala:
 rx=30,ry=0,rz=10,px=30,py=80,pz=10;
break;

case Cochera:
rx=20,ry=-30,rz=12;
px=80,py=30,pz=12;
break;

case Patio:
rx=-40,ry=-32,rz=11;
px=40,pz=11,py=80;
break;

case Cuarto1:
rx=+62,ry=58,rz=10;
px=-10,pz=10,py=70;
break;

case Cuarto2:
rx=-40,ry=58,rz=10;
px=+10,pz=10,py=70;
break;

case Pasillo:
rx=-38,ry=47,rz=10;
px=-38,pz=10,py=80;
break;

case Bano:
rx=10,ry=58,rz=10;
px=+10,pz=10,py=70;
break;

case Cocina:
 rx=0,ry=0,rz=10,px=0,py=10,pz=10;
break;

}
glutPostRedisplay();
}

void onMenu3(int opcion) {
switch(opcion) {
case Radio1:
PlaySound("facha.wav", NULL, SND_ASYNC|SND_FILENAME);
break;

case Radio2:
PlaySound("Duro 2 horas.wav", NULL, SND_ASYNC|SND_FILENAME);
break;


case Radio3:
PlaySound("Maldito alcohol.wav", NULL, SND_ASYNC|SND_FILENAME);
break;

case Carro1:
PlaySound("Encender.wav", NULL, SND_ASYNC|SND_FILENAME);
break;


case Carro2:
glutIdleFunc(idleFunc);
PlaySound("acelerando.wav", NULL, SND_ASYNC|SND_FILENAME);
break;

case Carro3:
glutIdleFunc(idleFunc3);
PlaySound("Salida.wav", NULL, SND_ASYNC|SND_FILENAME);
break;
case Luces1:
iFondo = 8;
Dia();
break;
case Luces2:
iFondo = 8;
rx=100,ry=-230,rz=6,px=100,py=300,pz=6,tx=0,ty=0,tz=1;
MediaNoche();
glutIdleFunc(idleFunc2);
PlaySound("Grito.wav", NULL, SND_ASYNC|SND_FILENAME);
break;
}
glutPostRedisplay();

}


void creacionMenu(void) {
int menuFondo, menuDibujo, menuPrincipal,menuParedes,menuPuerta,menuCamara,menuColores,menuRadio ,menuCarro,menuLuces;
menuFondo = glutCreateMenu(onMenu);
glutAddMenuEntry("celeste", FONDO1);
glutAddMenuEntry("Verde oscuro", FONDO2);
glutAddMenuEntry("beige", FONDO3);
glutAddMenuEntry("color verde", FONDO4);
menuDibujo = glutCreateMenu(onMenu);
glutAddMenuEntry("Plomo", DIBUJO1);
glutAddMenuEntry("Verde claro", DIBUJO2);
glutAddMenuEntry("Azul claro", DIBUJO3);
glutAddMenuEntry("color naranja", DIBUJO4);	

menuCamara = glutCreateMenu(onMenu2);
glutAddMenuEntry("blanco", puerta1);
glutAddMenuEntry("verde", puerta2);
glutAddMenuEntry("Azul claro", puerta3);
glutAddMenuEntry("color naranja", puerta4);

menuParedes = glutCreateMenu(onMenu);
glutAddMenuEntry("Blanco", pared1);
glutAddMenuEntry("Verde claro", pared2);
glutAddMenuEntry("Azul claro", pared3);
glutAddMenuEntry("color naranja", pared4);

menuPuerta = glutCreateMenu(onMenu);
glutAddMenuEntry("Blanco", puerta1);
glutAddMenuEntry("Verde claro", puerta2);
glutAddMenuEntry("Azul claro", puerta3);
glutAddMenuEntry("color naranja", puerta4);

menuColores = glutCreateMenu(onMenu);
glutAddSubMenu("Color de fondo", menuFondo);
glutAddSubMenu("Color de refri", menuDibujo);
glutAddSubMenu("Color de paredes", menuParedes);
glutAddSubMenu("Color de puerta", menuPuerta);

menuCamara  = glutCreateMenu(onMenu2);
glutAddMenuEntry("Sala", Sala);
glutAddMenuEntry("Cochera", Cochera);
glutAddMenuEntry("Patio",Patio);
glutAddMenuEntry("Cuarto1", Cuarto1);
glutAddMenuEntry("Cuarto2", Cuarto2);
glutAddMenuEntry("Pasillo",Pasillo);
glutAddMenuEntry("Baño", Bano);
glutAddMenuEntry("Cocina", Cocina);

menuRadio  = glutCreateMenu(onMenu3);
glutAddMenuEntry("92.5", Radio1);
glutAddMenuEntry("84.7", Radio2);
glutAddMenuEntry("98.3", Radio3);

menuCarro  = glutCreateMenu(onMenu3);
glutAddMenuEntry("Encender", Carro1);
glutAddMenuEntry("Salida", Carro2);
glutAddMenuEntry("Regreso", Carro3);

menuLuces  = glutCreateMenu(onMenu3);
glutAddMenuEntry("Encender", Luces1);
glutAddMenuEntry("Miedo", Luces2);

menuPrincipal = glutCreateMenu(onMenu);
glutAddSubMenu("Colores", menuColores );
glutAddSubMenu("Camara", menuCamara );
glutAddSubMenu("Emisora", menuRadio );
glutAddSubMenu("Carro", menuCarro );
glutAddSubMenu("Luces", menuLuces );
glutAttachMenu(GLUT_RIGHT_BUTTON);
}

//------------------------------------------------------------------------------------------------------------------------------------------------
//casa 1
//////////////////////////////////////// COCINA /////////////////////////////////////////////
//------------------------------------------------------------------------------------------------------------------------------------------------
///////////////////////////// PAREDES /////////////////////////////////////
void paredes(){
	//------PAREDES Y PISO DE LA SALA----------------
//PISO
glBegin(GL_QUADS);
glColor3f(0.4, 0.2, 0.1);
glVertex3f(-15, -25, 0.1);
glVertex3f(15, -25, 0.1);
glVertex3f(15, 25, 0.1); 
glVertex3f(-15, 25, 0.1);
glEnd();

//--PARED DERECHA------
//--pared interior
glBegin(GL_QUADS);
glColor3f(colores[ipared ][0], colores[ipared ][1], colores[ipared ][2]);
glVertex3f(15, -25, 0.1);
glVertex3f(15, 25, 0.1);
glVertex3f(15, 25, 20); 
glVertex3f(15, -25, 20);
glEnd();

//--PARED FONDO------

glBegin(GL_QUADS);
glColor3f(colores[ipared ][0], colores[ipared ][1], colores[ipared ][2]);
glVertex3f(-15, 25, 0.1);
glVertex3f(15, 25, 0.1);
glVertex3f(15, 25, 20); 
glVertex3f(-15, 25, 20);
glEnd();

//--PARED IZQUIERDA------

glBegin(GL_QUADS);
glColor3f(colores[ipared ][0], colores[ipared ][1], colores[ipared ][2]);
glVertex3f(-15, -25, 0.0);
glVertex3f(-15, -25, 20);
glVertex3f(-15, -19, 16.5); 
glVertex3f(-15, -19, 0);
glEnd();

glBegin(GL_QUADS);
glColor3f(colores[ipared ][0], colores[ipared ][1], colores[ipared ][2]);
glVertex3f(-15, 25, 0);
glVertex3f(-15, 19, 0);
glVertex3f(-15, 19, 16.5);
glVertex3f(-15, 25, 20);
glEnd();

glBegin(GL_QUADS);
glColor3f(colores[ipared ][0], colores[ipared ][1], colores[ipared ][2]);
glVertex3f(-15, 19, 16.5);
glVertex3f(-15, -19, 16.5);
glVertex3f(-15, -25, 20);
glVertex3f(-15, 25, 20);
glEnd();

// PASO QUE ESTA EN LA MAMPARA
glBegin(GL_QUADS);
glColor3f(colores[ipared ][0], colores[ipared ][1], colores[ipared ][2]);
glVertex3f(-18, 19, 0);
glVertex3f(-18, 19, 2);
glVertex3f(-12, 19, 2);
glVertex3f(-12, 19, 0);
glEnd();

glBegin(GL_QUADS);
glColor3f(colores[ipared ][0], colores[ipared ][1], colores[ipared ][2]);
glVertex3f(-12, 19, 0);
glVertex3f(-12, 19, 2);
glVertex3f(-12, -19, 2);
glVertex3f(-12, -19, 0);
glEnd();

glBegin(GL_QUADS);
glColor3f(colores[ipared ][0], colores[ipared ][1], colores[ipared ][2]);
glVertex3f(-12, -19, 0);
glVertex3f(-12, -19, 2);
glVertex3f(-18, -19, 2);
glVertex3f(-18, -19, 0);
glEnd();

glBegin(GL_QUADS);
glColor3f(colores[ipared ][0], colores[ipared ][1], colores[ipared ][2]);
glVertex3f(-18, 19, 2);
glVertex3f(-12, 19, 2);
glVertex3f(-12, -19, 2);
glVertex3f(-18, -19, 2);
glEnd();

glBegin(GL_QUADS);
glColor3f(colores[ipared ][0], colores[ipared ][1], colores[ipared ][2]);
glVertex3f(-18, 19, 0);
glVertex3f(-18, 19, 2);
glVertex3f(-18, -19, 2);
glVertex3f(-18, -19, 0);
glEnd();

//--PARED ALFRENTE------
glBegin(GL_QUADS);
glColor3f(colores[ipared ][0], colores[ipared ][1], colores[ipared ][2]);
glVertex3f(-15, -25, 0);
glVertex3f(-15, -25, 20);
glVertex3f(15, -25, 20); 
glVertex3f(15, -25, 0);
glEnd();
//TECHO

glBegin(GL_QUADS);
glColor3f(colores[ipared ][0], colores[ipared ][1], colores[ipared ][2]); 
glVertex3f(15, 25, 20);
glVertex3f(15, -25, 20);
glVertex3f(-15, -25, 20); 
glVertex3f(-15, 25, 20);
glEnd();


//madera de techo 1
//cara izquierda
glBegin(GL_QUADS);
glColor3f( 0.184 , 0.133 , 0.109 ); 
glVertex3f(15, 24.9, 18.5);
glVertex3f(15, 24.9, 20);
glVertex3f(-15, 24.9, 20); 
glVertex3f(-15, 24.9, 18.5); 
glEnd();
//cara de abajo
glBegin(GL_QUADS);
glColor3f( 0.184 , 0.133 , 0.109 );
glVertex3f(15, 25, 18.5);
glVertex3f(15, 22, 18.5);
glVertex3f(-15, 22, 18.5); 
glVertex3f(-15, 25, 18.5); 
glEnd();
//cara derecha
glBegin(GL_QUADS);
glColor3f( 0.184 , 0.133 , 0.109 );
glVertex3f(15, 22, 18.5);
glVertex3f(15, 22, 20);
glVertex3f(-15, 22, 20); 
glVertex3f(-15, 22, 18.5); 
glEnd();  

//madera de techo 8
//cara izquierda
glBegin(GL_QUADS);
glColor3f( 0.184 , 0.133 , 0.109 ); 
glVertex3f(-15, -23, 18.5);
glVertex3f(-15, -23, 20);
glVertex3f(15, -23, 20); 
glVertex3f(15, -23, 18.5); 
glEnd();
//cara de abajo
glBegin(GL_QUADS);
glColor3f( 0.184 , 0.133 , 0.109 );
glVertex3f(-15, -23, 18.5);
glVertex3f(-15, -25, 18.5);
glVertex3f(15, -25, 18.5); 
glVertex3f(15, -23, 18.5); 
glEnd();

//------------------------------
//madera de techo 2

glPushMatrix();
glTranslatef(0.0f, -7.0f, 0.0f);//TRASLADADO
//cara izquierda
glBegin(GL_QUADS);
glColor3f( 0.184 , 0.133 , 0.109 ); 
glVertex3f(15, 24.9, 18.5);
glVertex3f(15, 24.9, 20);
glVertex3f(-15, 24.9, 20); 
glVertex3f(-15, 24.9, 18.5); 
glEnd();
//cara de abajo
glBegin(GL_QUADS);
glColor3f( 0.184 , 0.133 , 0.109 );
glVertex3f(15, 25, 18.5);
glVertex3f(15, 22, 18.5);
glVertex3f(-15, 22, 18.5); 
glVertex3f(-15, 25, 18.5); 
glEnd();
//cara derecha
glBegin(GL_QUADS);
glColor3f( 0.184 , 0.133 , 0.109 );
glVertex3f(15, 22, 18.5);
glVertex3f(15, 22, 20);
glVertex3f(-15, 22, 20); 
glVertex3f(-15, 22, 18.5); 
glEnd();  
glPopMatrix();

//madera de techo 3

glPushMatrix();
glTranslatef(0.0f, -14.0f, 0.0f);//TRASLADADO
//cara izquierda
glBegin(GL_QUADS);
glColor3f( 0.184 , 0.133 , 0.109 ); 
glVertex3f(15, 24.9, 18.5);
glVertex3f(15, 24.9, 20);
glVertex3f(-15, 24.9, 20); 
glVertex3f(-15, 24.9, 18.5); 
glEnd();
//cara de abajo
glBegin(GL_QUADS);
glColor3f( 0.184 , 0.133 , 0.109 );
glVertex3f(15, 25, 18.5);
glVertex3f(15, 22, 18.5);
glVertex3f(-15, 22, 18.5); 
glVertex3f(-15, 25, 18.5); 
glEnd();
//cara derecha
glBegin(GL_QUADS);
glColor3f( 0.184 , 0.133 , 0.109 );
glVertex3f(15, 22, 18.5);
glVertex3f(15, 22, 20);
glVertex3f(-15, 22, 20); 
glVertex3f(-15, 22, 18.5); 
glEnd();  
glPopMatrix();

//madera de techo 4

glPushMatrix();
glTranslatef(0.0f, -21.0f, 0.0f);//TRASLADADO
//cara izquierda
glBegin(GL_QUADS);
glColor3f( 0.184 , 0.133 , 0.109 ); 
glVertex3f(15, 24.9, 18.5);
glVertex3f(15, 24.9, 20);
glVertex3f(-15, 24.9, 20); 
glVertex3f(-15, 24.9, 18.5); 
glEnd();
//cara de abajo
glBegin(GL_QUADS);
glColor3f( 0.184 , 0.133 , 0.109 );
glVertex3f(15, 25, 18.5);
glVertex3f(15, 22, 18.5);
glVertex3f(-15, 22, 18.5); 
glVertex3f(-15, 25, 18.5); 
glEnd();
//cara derecha
glBegin(GL_QUADS);
glColor3f( 0.184 , 0.133 , 0.109 );
glVertex3f(15, 22, 18.5);
glVertex3f(15, 22, 20);
glVertex3f(-15, 22, 20); 
glVertex3f(-15, 22, 18.5); 
glEnd();  
glPopMatrix();

//madera de techo 5

glPushMatrix();
glTranslatef(0.0f, -28.0f, 0.0f);//TRASLADADO
//cara izquierda
glBegin(GL_QUADS);
glColor3f( 0.184 , 0.133 , 0.109 ); 
glVertex3f(15, 24.9, 18.5);
glVertex3f(15, 24.9, 20);
glVertex3f(-15, 24.9, 20); 
glVertex3f(-15, 24.9, 18.5); 
glEnd();
//cara de abajo
glBegin(GL_QUADS);
glColor3f( 0.184 , 0.133 , 0.109 );
glVertex3f(15, 25, 18.5);
glVertex3f(15, 22, 18.5);
glVertex3f(-15, 22, 18.5); 
glVertex3f(-15, 25, 18.5); 
glEnd();
//cara derecha
glBegin(GL_QUADS);
glColor3f( 0.184 , 0.133 , 0.109 );
glVertex3f(15, 22, 18.5);
glVertex3f(15, 22, 20);
glVertex3f(-15, 22, 20); 
glVertex3f(-15, 22, 18.5); 
glEnd();  
glPopMatrix();

//madera de techo 6

glPushMatrix();
glTranslatef(0.0f, -35.0f, 0.0f);//TRASLADADO
//cara izquierda
glBegin(GL_QUADS);
glColor3f( 0.184 , 0.133 , 0.109 ); 
glVertex3f(15, 24.9, 18.5);
glVertex3f(15, 24.9, 20);
glVertex3f(-15, 24.9, 20); 
glVertex3f(-15, 24.9, 18.5); 
glEnd();
//cara de abajo
glBegin(GL_QUADS);
glColor3f( 0.184 , 0.133 , 0.109 );
glVertex3f(15, 25, 18.5);
glVertex3f(15, 22, 18.5);
glVertex3f(-15, 22, 18.5); 
glVertex3f(-15, 25, 18.5); 
glEnd();
//cara derecha
glBegin(GL_QUADS);
glColor3f( 0.184 , 0.133 , 0.109 );
glVertex3f(15, 22, 18.5);
glVertex3f(15, 22, 20);
glVertex3f(-15, 22, 20); 
glVertex3f(-15, 22, 18.5); 
glEnd();  
glPopMatrix();

//madera de techo 7

glPushMatrix();
glTranslatef(0.0f, -42.0f, 0.0f);//TRASLADADO
//cara izquierda
glBegin(GL_QUADS);
glColor3f( 0.184 , 0.133 , 0.109 ); 
glVertex3f(15, 24.9, 18.5);
glVertex3f(15, 24.9, 20);
glVertex3f(-15, 24.9, 20); 
glVertex3f(-15, 24.9, 18.5); 
glEnd();
//cara de abajo
glBegin(GL_QUADS);
glColor3f( 0.184 , 0.133 , 0.109 );
glVertex3f(15, 25, 18.5);
glVertex3f(15, 22, 18.5);
glVertex3f(-15, 22, 18.5); 
glVertex3f(-15, 25, 18.5); 
glEnd();
//cara derecha
glBegin(GL_QUADS);
glColor3f( 0.184 , 0.133 , 0.109 );
glVertex3f(15, 22, 18.5);
glVertex3f(15, 22, 20);
glVertex3f(-15, 22, 20); 
glVertex3f(-15, 22, 18.5); 
glEnd();  
glPopMatrix();

//------------------lineas para detallado-----------------------------
//paso que esta en la mampara
glLineWidth(2); 
glBegin(GL_LINES);
glColor3f(0.0f, 0.0f, 0.0f);

glVertex3f(-12, -19, 2);
glVertex3f(-12, -19, 0);

glVertex3f(-12, -19, 2);
glVertex3f(-12, 19, 2);

glVertex3f(-12, -19, 0);
glVertex3f(-12, 19, 0);

glVertex3f(-12, -19, 2);
glVertex3f(-15, -19, 2);

glVertex3f(-12, -19, 0);
glVertex3f(-15, -19, 0);

glVertex3f(-12, 19, 2);
glVertex3f(-12, 19, 0);


glVertex3f(-12, 19, 2);
glVertex3f(-15, 19, 2);

glVertex3f(-12, 19, 0);
glVertex3f(-15, 19, 0);

glEnd();

//madera de techo

glLineWidth(3); 
glBegin(GL_LINES);
glColor3f(0.0f, 0.0f, 0.0f);

glVertex3f(-15, 25, 18.5);
glVertex3f(15, 25, 18.5);
glVertex3f(-15, 22, 18.5);
glVertex3f(15, 22, 18.5);

glVertex3f(-15, -23, 18.5); 
glVertex3f(15, -23, 18.5); 
glEnd();

glPushMatrix();
glTranslatef(0.0f, -7.0f, 0.0f);//TRASLADADO
glLineWidth(3); 
glBegin(GL_LINES);
glColor3f(0.0f, 0.0f, 0.0f);

glVertex3f(-15, 25, 18.5);
glVertex3f(15, 25, 18.5);
glVertex3f(-15, 22, 18.5);
glVertex3f(15, 22, 18.5);

glEnd();
glPopMatrix();

glPushMatrix();
glTranslatef(0.0f, -14.0f, 0.0f);//TRASLADADO
glLineWidth(3); 
glBegin(GL_LINES);
glColor3f(0.0f, 0.0f, 0.0f);

glVertex3f(-15, 25, 18.5);
glVertex3f(15, 25, 18.5);
glVertex3f(-15, 22, 18.5);
glVertex3f(15, 22, 18.5);

glEnd();
glPopMatrix();

glPushMatrix();
glTranslatef(0.0f, -21.0f, 0.0f);//TRASLADADO
glLineWidth(3); 
glBegin(GL_LINES);
glColor3f(0.0f, 0.0f, 0.0f);

glVertex3f(-15, 25, 18.5);
glVertex3f(15, 25, 18.5);
glVertex3f(-15, 22, 18.5);
glVertex3f(15, 22, 18.5);

glEnd();
glPopMatrix();

glPushMatrix();
glTranslatef(0.0f, -28.0f, 0.0f);//TRASLADADO
glLineWidth(3); 
glBegin(GL_LINES);
glColor3f(0.0f, 0.0f, 0.0f);

glVertex3f(-15, 25, 18.5);
glVertex3f(15, 25, 18.5);
glVertex3f(-15, 22, 18.5);
glVertex3f(15, 22, 18.5);

glEnd();
glPopMatrix();

glPushMatrix();
glTranslatef(0.0f, -35.0f, 0.0f);//TRASLADADO
glLineWidth(3); 
glBegin(GL_LINES);
glColor3f(0.0f, 0.0f, 0.0f);

glVertex3f(-15, 25, 18.5);
glVertex3f(15, 25, 18.5);
glVertex3f(-15, 22, 18.5);
glVertex3f(15, 22, 18.5);

glEnd();
glPopMatrix();

glPushMatrix();
glTranslatef(0.0f, -42.0f, 0.0f);//TRASLADADO
glLineWidth(3); 
glBegin(GL_LINES);
glColor3f(0.0f, 0.0f, 0.0f);

glVertex3f(-15, 25, 18.5);
glVertex3f(15, 25, 18.5);
glVertex3f(-15, 22, 18.5);
glVertex3f(15, 22, 18.5);

glEnd();
glPopMatrix();

glEnd();

}

void pared()
{
	 glPushMatrix();
	glColor3f(1.0f, 1.4f, 1.0f);
	glTranslatef(34, 65.8, 10.5);
	glScalef(4, 0.04, 1.87);
	glutSolidCube(10);
	glColor3f(0.0f, 0.0f, 0.0f);
	LineaCubo(2);	
	glEnd ();	
	glPopMatrix();
	//_----Techo1
	 glPushMatrix();
	glColor3f(1.0f, 1.4f, 1.0f);
	glTranslatef(35,50.8, 19.7);
	glScalef(4, 3.1, 0.005);
	glutSolidCube(10);
	glColor3f(0.0f, 0.0f, 0.0f);
	LineaCubo(2);	
	glEnd ();	
	glPopMatrix();
	
		//_----Techo2
	 glPushMatrix();
	glColor3f(1.0f, 1.4f, 1.0f);
	glTranslatef(-32.5,50, 20);
	glScalef(3.5, 3, 0.005);
	glutSolidCube(10);
	glColor3f(0.0f, 0.0f, 0.0f);
	LineaCubo(2);	
	glEnd ();	
	glPopMatrix();
}
void espejo_y_puerta(){
	
	glPushMatrix();
	glTranslatef(5.0f, 0.0f, 0.0f);//TRASLADADO
	//cuadrado de fondo del espejo
	
	glBegin(GL_QUADS);
	glColor3f( 0.0, 0.0 , 0.0 );
	glVertex3f(-18, 24.98, 0);
    glVertex3f(-18, 24.98, 13);
    glVertex3f(-10, 24.98, 13); 
    glVertex3f(-10, 24.98, 0); 
    glEnd();
   
    //cuadrado blanco del espejo
    
    glBegin(GL_QUADS);
    glColor3f( 1.0, 1.0 , 1.0 );
	glVertex3f(-17, 24.97, 1);
    glVertex3f(-17, 24.97, 12);
    glVertex3f(-11, 24.97, 12); 
    glVertex3f(-11, 24.97, 1); 
    glEnd();
    glPopMatrix();
    
  
    //----PUERTA
    
    glPushMatrix();
	glColor3f(1.0f, 1.4f, 1.0f);
	glTranslatef(1, 25.05, 7.8);
	glScalef(0.75, 0.04, 1.54);
	glutSolidCube(10);
	glColor3f(0.0f, 0.0f, 0.0f);
	LineaCubo(2);	
	glEnd ();	
	glPopMatrix();
	

	//-------BORDES DE LA PEURTA
	//----PARTE IZQUIERDA
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
    glTranslatef(5, 25.05, 8.00);
	glScalef(0.057, 0.089, 1.59);
	glutSolidCube(10);
	glColor3f(0.0f, 0.0f, 0.0f);
	LineaCubo(2);	
	glEnd ();			
	glPopMatrix();
	
	
	
	//-----------PARTE DERECHA 
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
    glTranslatef(-3, 25.05, 8.00);
	glScalef(0.057, 0.089, 1.59);
	glutSolidCube(10);
	glColor3f(0.0f, 0.0f, 0.0f);
	LineaCubo(2);	
		glEnd ();			
	glPopMatrix();
	
	
	
	//--PARTE INFERIOR
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
    glTranslatef(1, 25.05, 0.21);
	glScalef(0.75, 0.10, 0.035);
	glutSolidCube(10);
    glColor3f(0.0f, 0.0f, 0.0f);
    LineaCubo(2);	
	glEnd ();			
	glPopMatrix();
	
	
	
	//-----------PARTE SUPERIOR
	
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(1, 25.05, 15.71);
    glScalef(0.75, 0.10, 0.035);	
	glutSolidCube(10);	
	glColor3f(0.0f, 0.0f, 0.0f);
	LineaCubo(2);	
	glEnd ();			
	glPopMatrix();
	
	
	//MANIJA
	

	
	//----DETALLE CUBO
	
    glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(3, 24.75, 8.00);
	glScalef(0.03, 0.05, 0.03);	
	glutSolidCube(10);	
	glColor3f(0.0f, 0.0f, 0.0f);
	LineaCubo(2);	
	glEnd ();	
	glPopMatrix();
	
	
	
	
	//-----MANIJA HORIZONTAL
	
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(2.5, 24.35, 8.00);
    glScalef(0.23, 0.03, 0.03);
	glutSolidCube(10);
	glColor3f(0.0f, 0.0f, 0.0f);
	LineaCubo(2);	
	glEnd ();			
	glPopMatrix();

	
	
	//---DETALLE CUBO
	//--------PARTE DERECHA
	
    glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(3, 25.45, 8.00);
	glScalef(0.03, 0.05, 0.03);
	glutSolidCube(10);
	glColor3f(0.0f, 0.0f, 0.0f);
		
	LineaCubo(2);	
	glEnd ();	
	glPopMatrix();
	

	//---MANIJA VERTICAL
	
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(3, 25.75, 7.50);
	glScalef(0.03, 0.03, 0.23);
	glutSolidCube(10);
	glColor3f(0.0f, 0.0f, 0.0f);
	LineaCubo(2);	
	glEnd ();			
	glPopMatrix();

    
}
/////////////////////// PARA LINEAS DE MAMPARA Y TRAGALUZ ///////////////////////

void LineaCubo(int x){
	glPushMatrix();
	glScalef(10.0, 10.0, 10.0);

	//linea
	glLineWidth(x);    // grosor de la línea
	glBegin (GL_LINE_STRIP); 
	glVertex3f( 0.5, -0.5, -0.5 );
	glVertex3f( 0.5, 0.5, -0.5 );
	glVertex3f( -0.5, 0.5, -0.5 );
	glVertex3f( -0.5, -0.5, -0.5 );
	glVertex3f( 0.5, -0.5, -0.5 );
	glEnd ();	

	//linea
	glLineWidth(x);    // grosor de la línea
	glBegin (GL_LINE_STRIP);
	glVertex3f( 0.5, -0.5, 0.5 );
	glVertex3f( 0.5, 0.5, 0.5 );
	glVertex3f( -0.5, 0.5, 0.5 );
	glVertex3f( -0.5, -0.5, 0.5 );
	glVertex3f( 0.5, -0.5, 0.5 );
	glEnd ();

	//linea
	glLineWidth(x);    // grosor de la línea
	glBegin (GL_LINE_STRIP); 
	glVertex3f( 0.5, -0.5, -0.5 );
	glVertex3f( 0.5, 0.5, -0.5 );
	glVertex3f( 0.5, 0.5, 0.5 );
	glVertex3f( 0.5, -0.5, 0.5 );
	glVertex3f( 0.5, -0.5, -0.5 );
	glEnd ();

	//linea
	glLineWidth(x);    // grosor de la línea
	glBegin (GL_LINE_STRIP); 
	glVertex3f( -0.5, -0.5, 0.5 );
	glVertex3f( -0.5, 0.5, 0.5 );
	glVertex3f( -0.5, 0.5, -0.5 );
	glVertex3f( -0.5, -0.5, -0.5 );
	glVertex3f( -0.5, -0.5, 0.5 );
	glEnd ();

	//linea
	glLineWidth(x);    // grosor de la línea
	glBegin (GL_LINE_STRIP); 
	glVertex3f( 0.5, 0.5, 0.5 );
	glVertex3f( 0.5, 0.5, -0.5 );
	glVertex3f( -0.5, 0.5, -0.5 );
	glVertex3f( -0.5, 0.5, 0.5 );
	glVertex3f( 0.5, 0.5, 0.5 );
	glEnd ();

	//linea
	glLineWidth(x);    // grosor de la línea
	glBegin (GL_LINE_STRIP); 
	glVertex3f( 0.5, -0.5, -0.5 );
	glVertex3f( 0.5, -0.5, 0.5 );
	glVertex3f( -0.5, -0.5, 0.5 );
	glVertex3f( -0.5, -0.5, -0.5 );
	glVertex3f( 0.5, -0.5, -0.5 );
	glEnd ();
		
	glPopMatrix();		
}

///////////////////////////// MAMPARA /////////////////////////////////////

void Mampara(){

/// varilla inferior general

glPushMatrix();
		
		//glColor3f(1.0, 1.0, 0.960);
		glColor3f(0.0, 0.0, 0.0);
	
		glTranslatef(-15.3,-0.05,2.15);
	
		glScalef(0.13, 3.796, 0.038);	
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();

//varilla superior general
glPushMatrix();
		
		//glColor3f(1.0, 1.0, 0.960);
		glColor3f(0.0, 0.0, 0.0);
	
		glTranslatef(-15.3,-0.05,16.65);
	
		//glScalef(0.65, 0.02, 0.032);
		glScalef(0.13, 3.796, 0.038);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();			
		glPopMatrix();

///+++++ para lunas esquinas

//varilla izquierda general
	glPushMatrix();
		
		glColor3f(1.0, 1.0, 0.960);
		
		glTranslatef(-15.1, 18.65, 9.31);
		
		glScalef(0.03, 0.06, 1.44);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();
		
//varilla derecha general
	glPushMatrix();
		
		glColor3f(1.0, 1.0, 0.960);
	
		glTranslatef(-15.1, -18.65, 9.31);
	
		glScalef(0.03, 0.06, 1.44);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();

//*********para lunas 1

//varilla derecha delante 1
	glPushMatrix();
		
		glColor3f(1.0, 1.0, 0.960);
		
		glTranslatef(-15.1, -9.65, 9.31);
		
		glScalef(0.03, 0.06, 1.44);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();


//**********para lunas 2

// varilla izquierda delante 2
	glPushMatrix();
		
		glColor3f(1.0, 1.0, 0.960);
		
		glTranslatef(-15.1, 9.65, 9.31);
		
		glScalef(0.03, 0.06, 1.44);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();



//***********para lunas 3
//detras
// varilla derecha detras 3

	glPushMatrix();
		
		glColor3f(1.0, 1.0, 0.960);
		
		glTranslatef(-15.35, 9.65, 9.31);
	
		glScalef(0.03, 0.06, 1.44);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();

		
// varilla izquierda detras 3
//para la puerta der
	glPushMatrix();
		
		glColor3f(1.0, 1.0, 0.960);
		
		glTranslatef(-15.35, -0.5, 9.31);
		
		glScalef(0.03, 0.09, 1.44);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();

//***********para lunas 4
//detras
// varilla derecha detras 4
//para la puerta izq
	glPushMatrix();
		
		glColor3f(1.0, 1.0, 0.960);
		
		glTranslatef(-15.35, 0.43, 9.31);
	
		glScalef(0.03, 0.09, 1.44);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();


// varilla izquierda detras 4

     glPushMatrix();
		
		glColor3f(1.0, 1.0, 0.960);
		
		glTranslatef(-15.35, -9.65, 9.31);
		
		glScalef(0.03, 0.06, 1.44);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();



///**********manija
///------- manija parte cubito delante
//parte izq
glPushMatrix();
		
		glColor3f(0.0f, 0.0f, 0.0f);
	
		glTranslatef(-15.15, 0.43, 9.31);
		
		glScalef(0.03, 0.03, 0.03);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();
//parte der
glPushMatrix();
		
		glColor3f(0.0, 0.0, 0.0);
		
		glTranslatef(-15.15, -0.5, 9.31);
	
		glScalef(0.03, 0.03, 0.03);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();

///------- manija parte cubito detras
//parte der
glPushMatrix();
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		glTranslatef(-15.55, 0.43, 9.31);
	
		glScalef(0.03, 0.03, 0.03);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();
//parte izq
glPushMatrix();
		
		glColor3f(0.0, 0.0, 0.0);
		
		glTranslatef(-15.55, -0.5, 9.31);
	
		glScalef(0.03, 0.03, 0.03);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();


//-------------manija tirar
//--)parte delante
/// manija der delant

glPushMatrix();
		
		glColor3f(0.0, 0.0, 0.0);
	
		glTranslatef(-14.95, -0.5, 8.80);
	
		glScalef(0.02, 0.02, -0.17);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();


/// manija izq delant
glPushMatrix();
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		glTranslatef(-14.95, 0.43, 8.80);
	
		glScalef(0.02, 0.02, -0.17);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();
///--)parte detras

/// manija izq detras
glPushMatrix();
		
		glColor3f(0.0, 0.0, 0.0);
		
		glTranslatef(-15.75, -1.1, 9.31);
		
		glScalef(0.02, -0.17, 0.02);
		glutSolidCube(10);

		glColor3f(0.0, 0.0, 0.0);
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();



///manija der detras
glPushMatrix();
		
		glColor3f(0.0f, 0.0f, 0.0f);
	
		glTranslatef(-15.75, 0.97, 9.31);
		
		
		glScalef(0.02, -0.17, 0.02);
		glutSolidCube(10);

		glColor3f(0.0, 0.0, 0.0);
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();

///**********************************************

///<<<<<<< LUNAS >>>>>>>>>>	

	//!!!!!!!!!!!!!! vidrio 1
		
			glPushMatrix();
		
		glColor3f(0.7450f, 0.8784f, 1.0f);//celeste palido
		
		glTranslatef(-15.1, 14.05, 9.31);
		
		glScalef(0.01, 0.88, 1.44);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();
		
	//!!!!!!!!!!!!! vidrio 2
		
			glPushMatrix();
		
		glColor3f(0.7450f, 0.8784f, 1.0f);//celeste palido
		
		glTranslatef(-15.2, -13.97, 9.31);
		
		glScalef(0.01, 0.88, 1.44);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();
		

	
//!!!!!!!!!!!!!!!!!! vidrio 3
		
			glPushMatrix();
		
		glColor3f(0.7450f, 0.8784f, 1.0f);//celeste palido
		
		glTranslatef(-15.4, 5.05, 9.31);
		
		glScalef(0.01, 0.86, 1.44);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();
		
	//!!!!!!!!!!!!! vidrio 4
		
			glPushMatrix();
		
		glColor3f(0.7450f, 0.8784f, 1.0f);//celeste palido
		
		glTranslatef(-15.4, -5.05, 9.31);
		
		glScalef(0.01, 0.86, 1.44);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();
	
	
	
}

//////////////////////////////////// TRAGALUZ//////////////////////////////////

void Tragaluz(){
	
	
/// varilla inferior general

glPushMatrix();
		
		glColor3f(1.0, 1.0, 0.960);
		
		
		glTranslatef(15.0,0.06,15.5);
	
		glScalef(0.09, 5.00, 0.038);	
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
			
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();
		
/// varilla superior general

glPushMatrix();
		
		glColor3f(1.0, 1.0, 0.960);
	
		
		glTranslatef(15.0,0.06,18.0);
	
		glScalef(0.09, 5.00, 0.038);	
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();
			
///varilla derecha general

glPushMatrix();
		
		glColor3f(1.0, 1.0, 0.960);
	
	
		glTranslatef(15.0,24.52,16.8);
	
		glScalef(0.09, 0.09, 0.22);	
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();		
		
///varilla izquierda general

glPushMatrix();
		
		glColor3f(1.0, 1.0, 0.960);
	
	
		glTranslatef(15.0,-24.52,16.8);
	
		glScalef(0.09, 0.09, 0.22);	
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();		
		
///varilla izq a der 1

glPushMatrix();
		
		glColor3f(1.0, 1.0, 0.960);
	
		
		glTranslatef(15.0,-17.32,16.8);
	
		glScalef(0.09, 0.09, 0.22);	
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();		
		
		
///varilla izq a der 2

glPushMatrix();
		
		glColor3f(1.0, 1.0, 0.960);
	
	
		glTranslatef(15.0,-10.32,16.8);
	
		glScalef(0.09, 0.09, 0.22);	
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();		
		
///varilla izq a der 3

glPushMatrix();
		
		glColor3f(1.0, 1.0, 0.960);
	
		
		glTranslatef(15.0,-3.32,16.8);
	
		glScalef(0.09, 0.09, 0.22);	
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();		
		
///varilla izq a der 4

glPushMatrix();
		
		glColor3f(1.0, 1.0, 0.960);
	
	
		glTranslatef(15.0,4.32,16.8);
	
		glScalef(0.09, 0.09, 0.22);	
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();		
///varilla izq a der 5

glPushMatrix();
		
		glColor3f(1.0, 1.0, 0.960);
	
		
		glTranslatef(15.0,11.52,16.8);
	
		glScalef(0.09, 0.09, 0.22);	
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();			
///varilla izq a der 6

glPushMatrix();
		
		glColor3f(1.0, 1.0, 0.960);
	
		
		glTranslatef(15.0,18.32,16.8);
	
		glScalef(0.09, 0.09, 0.22);	
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();	
	
/// luna

glPushMatrix();
		
		
		glColor3f(0.7450f, 0.8784f, 1.0f);//celeste palido
		
		glTranslatef(15.0,0.32,16.8);
	
		glScalef(0.02, 4.91, 0.22);	
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();	

				
}
//---------------------------------
///////////////////////////////////////////// ENCIMERA /////////////////////////////////////////////
void Encimera ()
{   
    //PRIMERA BASE
	//CARA INFERIOR
    glBegin(GL_QUADS);
    glColor3f( 0.639 , 0.474 , 0.403 );
    glVertex3f(-5, 10, 0);
    glVertex3f(-5, -10, 0);
    glVertex3f(0, -10, 0); 
    glVertex3f(0, 10, 0);
    glEnd();
            
    //CARA DERECHA
    
	glBegin(GL_QUADS);
    glColor3f( 0.639 , 0.474 , 0.403 );
    glVertex3f(-5, -10, 5);
    glVertex3f(-5, -10, 0);
    glVertex3f(0, -10, 0); 
    glVertex3f(0, -10, 5);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-5, -10, 5);
    glVertex3f(-5, -10, 0);
    glVertex3f(0, -10, 0); 
    glVertex3f(0, -10, 5);
    glEnd();
    
    //CARA IZQUIERDA
	glBegin(GL_QUADS);
    glColor3f( 0.639 , 0.474 , 0.403 );
    glVertex3f(-5, 10, 5);
    glVertex3f(-5, 10, 0);
    glVertex3f(0, 10, 0); 
    glVertex3f(0, 10, 5);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-5, 10, 5);
    glVertex3f(-5, 10, 0);
    glVertex3f(0, 10, 0); 
    glVertex3f(0, 10, 5);
    glEnd();
    
    //CARA FRONTAL
	glBegin(GL_QUADS);
    glColor3f( 0.639 , 0.474 , 0.403 );
    glVertex3f(-5, 10, 5);
    glVertex3f(-5, 10, 0);
    glVertex3f(-5, -10, 0); 
    glVertex3f(-5, -10, 5);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-5, 10, 5);
    glVertex3f(-5, 10, 0);
    glVertex3f(-5, -10, 0); 
    glVertex3f(-5, -10, 5);
    glEnd();
    
    //CARA POSTERIOR
	glBegin(GL_QUADS);
    glColor3f( 0.639 , 0.474 , 0.403 );
    glVertex3f(0, -10, 5);
    glVertex3f(0, -10, 0);
    glVertex3f(0, 10, 0); 
    glVertex3f(0, 10, 5);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(0, -10, 5);
    glVertex3f(0, -10, 0);
    glVertex3f(0, 10, 0); 
    glVertex3f(0, 10, 5);
    glEnd();
	    
    //SEGUNDA BASE
    //CARA INFERIOR
	glBegin(GL_QUADS);
    glColor3f( 0.639 , 0.474 , 0.403 );
    glVertex3f(-5, 10, 5);
    glVertex3f(-5, -10, 5);
    glVertex3f(-3, -10, 5); 
    glVertex3f(-3, 10, 5);
    glEnd();
    
    //CARA SUPERIOR
	glBegin(GL_QUADS);
    glColor3f( 0.639 , 0.474 , 0.403 );
    glVertex3f(-5, 10, 7);
    glVertex3f(-5, -10, 7);
    glVertex3f(-3, -10, 7); 
    glVertex3f(-3, 10, 7);
    glEnd();
        
    //CARA FRONTAL
	glBegin(GL_QUADS);
    glColor3f( 0.639 , 0.474 , 0.403 );
    glVertex3f(-5, 10, 7);
    glVertex3f(-5, -10, 7);
    glVertex3f(-5, -10, 5); 
    glVertex3f(-5, 10, 5);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-5, 10, 7);
    glVertex3f(-5, -10, 7);
    glVertex3f(-5, -10, 5); 
    glVertex3f(-5, 10, 5);
    glEnd();
    
    //CARA POSTERIOR
	glBegin(GL_QUADS);
    glColor3f( 0.639 , 0.474 , 0.403 );
    glVertex3f(-3, 10, 7);
    glVertex3f(-3, -10, 7);
    glVertex3f(-3, -10, 5); 
    glVertex3f(-3, 10, 5);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-3, 10, 7);
    glVertex3f(-3, -10, 7);
    glVertex3f(-3, -10, 5); 
    glVertex3f(-3, 10, 5);
    glEnd();
    
    //CARA DERRECHA
	glBegin(GL_QUADS);
    glColor3f( 0.639 , 0.474 , 0.403 );
    glVertex3f(-5, -10, 7);
    glVertex3f(-5, -10, 5);
    glVertex3f(-3, -10, 5); 
    glVertex3f(-3, -10, 7);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-5, -10, 7);
    glVertex3f(-5, -10, 5);
    glVertex3f(-3, -10, 5); 
    glVertex3f(-3, -10, 7);
    glEnd();
    
    //CARA IZQUIERDA
	glBegin(GL_QUADS);
    glColor3f( 0.639 , 0.474 , 0.403 );
    glVertex3f(-3, 10, 7);
    glVertex3f(-3, 10, 5);
    glVertex3f(-5, 10, 5); 
    glVertex3f(-5, 10, 7);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-3, 10, 7);
    glVertex3f(-3, 10, 5);
    glVertex3f(-5, 10, 5); 
    glVertex3f(-5, 10, 7);
    glEnd();
    
    //TERCERA BASE
    //CARA INFERIOR
	glBegin(GL_QUADS);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-6, 10, 7);
    glVertex3f(-6, -10, 7);
    glVertex3f(-3, -10, 7); 
    glVertex3f(-3, 10, 7);
    glEnd();
    
    //CARA SUPERIOR
	glBegin(GL_QUADS);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-6, 10, 7.5);
    glVertex3f(-6, -10, 7.5);
    glVertex3f(-3, -10, 7.5); 
    glVertex3f(-3, 10, 7.5);
    glEnd();
    
    //CARA FRONTAL
	glBegin(GL_QUADS);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-6, 10, 7.5);
    glVertex3f(-6, -10, 7.5);
    glVertex3f(-6, -10, 7); 
    glVertex3f(-6, 10, 7);
    glEnd();
    
    //CARA POSTERIOR
	glBegin(GL_QUADS);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-3, 10, 7.5);
    glVertex3f(-3, -10, 7.5);
    glVertex3f(-3, -10, 7); 
    glVertex3f(-3, 10, 7);
    glEnd();
    
    //CARA DERRECHA
	glBegin(GL_QUADS);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-6, -10, 7.5);
    glVertex3f(-6, -10, 7);
    glVertex3f(-3, -10, 7); 
    glVertex3f(-3, -10, 7.5);
    glEnd();
    
    //CARA IZQUIERDA
	glBegin(GL_QUADS);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-6, 10, 7.5);
    glVertex3f(-6, 10, 7);
    glVertex3f(-3, 10, 7); 
    glVertex3f(-3, 10, 7.5);
    glEnd();
    
    //CUARTA BASE
    //CARA INFERIOR
	glBegin(GL_QUADS);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-3, 10, 5);
    glVertex3f(-3, -10, 5);
    glVertex3f(-2, -10, 5);
    glVertex3f(-2, 10, 5); 
    glEnd();
    
    glBegin(GL_QUADS);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-2, -3, 5);
    glVertex3f(-2, -10, 5);
    glVertex3f(-1, -10, 5);
    glVertex3f(-1, -3, 5); 
    glEnd();

    glBegin(GL_QUADS);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-1, 10, 5);
    glVertex3f(-1, -10, 5);
    glVertex3f(0, -10, 5);
    glVertex3f(0, 10, 5); 
    glEnd();

    glBegin(GL_QUADS);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-2, 10, 5);
    glVertex3f(-2, 3, 5);
    glVertex3f(-1, 3, 5); 
    glVertex3f(-1, 10, 5);
    glEnd();
    
    //CARA SUPERIOR
	glBegin(GL_QUADS);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-3, 10, 5.5);
    glVertex3f(-3, -10, 5.5);
    glVertex3f(-2, -10, 5.5);
    glVertex3f(-2, 10, 5.5); 
    glEnd();
    
    glBegin(GL_QUADS);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-2, -3, 5.5);
    glVertex3f(-2, -10, 5.5);
    glVertex3f(-1, -10, 5.5);
    glVertex3f(-1, -3, 5.5); 
    glEnd();

    glBegin(GL_QUADS);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-1, 10, 5.5);
    glVertex3f(-1, -10, 5.5);
    glVertex3f(0, -10, 5.5);
    glVertex3f(0, 10, 5.5); 
    glEnd();

    glBegin(GL_QUADS);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-2, 10, 5.5);
    glVertex3f(-2, 3, 5.5);
    glVertex3f(-1, 3, 5.5); 
    glVertex3f(-1, 10, 5.5);
    glEnd();
    
    //CARA FRONTAL
	glBegin(GL_QUADS);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-3, 10, 5.5);
    glVertex3f(-3, -10, 5.5);
    glVertex3f(-3, -10, 5); 
    glVertex3f(-3, 10, 5);
    glEnd();
    
    //CARA POSTERIOR
	glBegin(GL_QUADS);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(0, 10, 5.5);
    glVertex3f(0, -10, 5.5);
    glVertex3f(0, -10, 5); 
    glVertex3f(0, 10, 5);
    glEnd();
    
    //CARA DERRECHA
	glBegin(GL_QUADS);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-3, -10, 5.5);
    glVertex3f(-3, -10, 5);
    glVertex3f(0, -10, 5); 
    glVertex3f(0, -10, 5.5);
    glEnd();
    
    //CARA IZQUIERDA
	glBegin(GL_QUADS);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-3, 10, 5.5);
    glVertex3f(-3, 10, 5.5);
    glVertex3f(0, 10, 5); 
    glVertex3f(0, 10, 5.5);
    glEnd();
    
    //LAVADERO
    //CARA INFERIOR
    glBegin(GL_QUADS);
    glColor3f( 0.960 , 0.960 , 0.960 );
    glVertex3f(-2, 3, 5);
    glVertex3f(-2, -3, 5);
    glVertex3f(-1, -3, 5); 
    glVertex3f(-1, 3, 5);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-2, 3, 5);
    glVertex3f(-2, -3, 5);
    glVertex3f(-1, -3, 5); 
    glVertex3f(-1, 3, 5);
    glEnd();
        
    //CARA FRONTAL
	glBegin(GL_QUADS);
    glColor3f( 0.960 , 0.960 , 0.960 );
    glVertex3f(-2, 3, 5);
    glVertex3f(-2, -3, 5);
    glVertex3f(-2, -3, 5.5); 
    glVertex3f(-2, 3, 5.5);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-2, 3, 5);
    glVertex3f(-2, -3, 5);
    glVertex3f(-2, -3, 5.5); 
    glVertex3f(-2, 3, 5.5);
    glEnd();
    
    //CARA POSTERIOR
	glBegin(GL_QUADS);
    glColor3f( 0.960 , 0.960 , 0.960 );
    glVertex3f(-1, 3, 5);
    glVertex3f(-1, -3, 5);
    glVertex3f(-1, -3, 5.5); 
    glVertex3f(-1, 3, 5.5);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-1, 3, 5);
    glVertex3f(-1, -3, 5);
    glVertex3f(-1, -3, 5.5); 
    glVertex3f(-1, 3, 5.5);
    glEnd();
    
    //CARA DERRECHA
	glBegin(GL_QUADS);
    glColor3f( 0.960 , 0.960 , 0.960 );
    glVertex3f(-2, -3, 5.5);
    glVertex3f(-2, -3, 5);
    glVertex3f(-1, -3, 5); 
    glVertex3f(-1, -3, 5.5);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-2, -3, 5.5);
    glVertex3f(-2, -3, 5);
    glVertex3f(-1, -3, 5); 
    glVertex3f(-1, -3, 5.5);
    glEnd();
    
    //CARA IZQUIERDA
	glBegin(GL_QUADS);
    glColor3f( 0.960 , 0.960 , 0.960 );
    glVertex3f(-2, 3, 5.5);
    glVertex3f(-2, 3, 5);
    glVertex3f(-1, 3, 5); 
    glVertex3f(-1, 3, 5.5);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-2, 3, 5.5);
    glVertex3f(-2, 3, 5);
    glVertex3f(-1, 3, 5); 
    glVertex3f(-1, 3, 5.5);
    glEnd();
    
    //CAÑO
    //PRIMERA BASE   
    //CARA SUPERIOR
	glBegin(GL_QUADS);
    glColor3f( 0.588 , 0.576 , 0.572 );
    glVertex3f(-2.6, 0.1, 7.5);
    glVertex3f(-2.6, -0.1, 7.5);
    glVertex3f(-2.4, -0.1, 7.5); 
    glVertex3f(-2.4, 0.1, 7.5);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-2.6, 0.1, 7.5);
    glVertex3f(-2.6, -0.1, 7.5);
    glVertex3f(-2.4, -0.1, 7.5); 
    glVertex3f(-2.4, 0.1, 7.5);
    glEnd();
    
    //CARA FRONTAL
	glBegin(GL_QUADS);
    glColor3f( 0.588 , 0.576 , 0.572 );
    glVertex3f(-2.6, 0.1, 5.5);
    glVertex3f(-2.6, 0.1, 5.5);
    glVertex3f(-2.6, -0.1, 7.5); 
    glVertex3f(-2.6, 0.1, 7.5);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-2.6, 0.1, 5.5);
    glVertex3f(-2.6, 0.1, 5.5);
    glVertex3f(-2.6, -0.1, 7.5); 
    glVertex3f(-2.6, 0.1, 7.5);
    glEnd();
    
    //CARA POSTERIOR
	glBegin(GL_QUADS);
    glColor3f( 0.588 , 0.576 , 0.572 );
    glVertex3f(-2.4, -0.1, 5.5);
    glVertex3f(-2.4, 0.1, 5.5);
    glVertex3f(-2.4, 0.1, 7.5); 
    glVertex3f(-2.4, -0.1, 7.5);
    
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-2.4, -0.1, 5.5);
    glVertex3f(-2.4, 0.1, 5.5);
    glVertex3f(-2.4, 0.1, 7.5); 
    glVertex3f(-2.4, -0.1, 7.5);
    
    //CARA DERRECHA
	glBegin(GL_QUADS);
    glColor3f( 0.588 , 0.576 , 0.572 );
    glVertex3f(-2.6, -0.1, 7.5);
    glVertex3f(-2.6, -0.1, 5.5);
    glVertex3f(-2.4, -0.1, 5.5); 
    glVertex3f(-2.4, -0.1, 7.5);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-2.6, -0.1, 7.5);
    glVertex3f(-2.6, -0.1, 5.5);
    glVertex3f(-2.4, -0.1, 5.5); 
    glVertex3f(-2.4, -0.1, 7.5);
    glEnd();
    
    //CARA IZQUIERDA
	glBegin(GL_QUADS);
    glColor3f( 0.588 , 0.576 , 0.572 );
    glVertex3f(-2.6, 0.1, 7.5);
    glVertex3f(-2.6, 0.1, 5.5);
    glVertex3f(-2.4, 0.1, 5.5); 
    glVertex3f(-2.4, 0.1, 7.5);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-2.6, 0.1, 7.5);
    glVertex3f(-2.6, 0.1, 5.5);
    glVertex3f(-2.4, 0.1, 5.5); 
    glVertex3f(-2.4, 0.1, 7.5);
    glEnd();
    
    //SEGUNDA BASE
    //CARA INFERIOR
	glBegin(GL_QUADS);
    glColor3f( 0.588 , 0.576 , 0.572 );
    glVertex3f(-2.4, -0.1, 7.3);
    glVertex3f(-2.4, 0.1, 7.3);
    glVertex3f(-1.5, -0.1, 7.3); 
    glVertex3f(-1.5, 0.1, 7.3);
    glEnd();
    
    //CARA SUPERIOR
	glBegin(GL_QUADS);
    glColor3f( 0.588 , 0.576 , 0.572 );
    glVertex3f(-2.4, -0.1, 7.5);
    glVertex3f(-2.4, 0.1, 7.5);
    glVertex3f(-1.5, -0.1, 7.5); 
    glVertex3f(-1.5, 0.1, 7.5);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-2.4, -0.1, 7.5);
    glVertex3f(-2.4, 0.1, 7.5);
    glVertex3f(-1.5, -0.1, 7.5); 
    glVertex3f(-1.5, 0.1, 7.5);
    glEnd();
    
    //CARA FRONTAL
	glBegin(GL_QUADS);
    glColor3f( 0.588 , 0.576 , 0.572 );
    glVertex3f(-2.4, 0.1, 7.3);
    glVertex3f(-2.4, -0.1, 7.3);
    glVertex3f(-2.4, 0.1, 7.5); 
    glVertex3f(-2.4, -0.1, 7.5);
    glEnd();
    
    //CARA POSTERIOR
	glBegin(GL_QUADS);
    glColor3f( 0.588 , 0.576 , 0.572 );
    glVertex3f(-1.5, 0.1, 7.3);
    glVertex3f(-1.5, -0.1, 7.3);
    glVertex3f(-1.5, -0.1, 7.5); 
    glVertex3f(-1.5, 0.1, 7.5);
    
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-1.5, 0.1, 7.3);
    glVertex3f(-1.5, -0.1, 7.3);
    glVertex3f(-1.5, -0.1, 7.5); 
    glVertex3f(-1.5, 0.1, 7.5);
    
    //CARA DERRECHA
	glBegin(GL_QUADS);
    glColor3f( 0.588 , 0.576 , 0.572 );
    glVertex3f(-2.4, -0.1, 7.5);
    glVertex3f(-2.4, -0.1, 7.3);
    glVertex3f(-1.5, -0.1, 7.3); 
    glVertex3f(-1.5, -0.1, 7.5);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-2.4, -0.1, 7.5);
    glVertex3f(-2.4, -0.1, 7.3);
    glVertex3f(-1.5, -0.1, 7.3); 
    glVertex3f(-1.5, -0.1, 7.5);
    glEnd();
    
    //CARA IZQUIERDA
	glBegin(GL_QUADS);
    glColor3f( 0.588 , 0.576 , 0.572 );
    glVertex3f(-2.4, 0.1, 7.5);
    glVertex3f(-2.4, 0.1, 7.3);
    glVertex3f(-1.5, 0.1, 7.3); 
    glVertex3f(-1.5, 0.1, 7.5);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-2.4, 0.1, 7.5);
    glVertex3f(-2.4, 0.1, 7.3);
    glVertex3f(-1.5, 0.1, 7.3); 
    glVertex3f(-1.5, 0.1, 7.5);
    glEnd();
    
    //LLAVE DE CAÑO
    //CARA INFERIOR
	glBegin(GL_QUADS);
    glColor3f( 0.588 , 0.576 , 0.572 );
    glVertex3f(-2.4, 0.1, 6);
    glVertex3f(-2.4, -0.4, 6);
    glVertex3f(-2.1, -0.4, 6); 
    glVertex3f(-2.1, 0.1, 6);
    glEnd();
    
    //CARA SUPERIOR
	glBegin(GL_QUADS);
    glColor3f( 0.588 , 0.576 , 0.572 );
    glVertex3f(-2.4, 0.1, 6.2);
    glVertex3f(-2.4, -0.4, 6.2);
    glVertex3f(-2.1, -0.4, 6.2); 
    glVertex3f(-2.1, 0.1, 6.2);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
	glVertex3f(-2.4, 0.1, 6.2);
    glVertex3f(-2.4, -0.4, 6.2);
    glVertex3f(-2.1, -0.4, 6.2); 
    glVertex3f(-2.1, 0.1, 6.2);
    glEnd();
     
    //CARA FRONTAL
	glBegin(GL_QUADS);
    glColor3f( 0.588 , 0.576 , 0.572 );
    glVertex3f(-2.4, 0.1, 6.2);
    glVertex3f(-2.4, -0.4, 6.2);
    glVertex3f(-2.4, -0.4, 6); 
    glVertex3f(-2.4, 0.1, 6);
	glEnd();
	
	glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );    
	glVertex3f(-2.4, 0.1, 6.2);
    glVertex3f(-2.4, -0.4, 6.2);
    glVertex3f(-2.4, -0.4, 6); 
    glVertex3f(-2.4, 0.1, 6);
	glEnd();
	    
    //CARA POSTERIOR
	glBegin(GL_QUADS);
    glColor3f( 0.588 , 0.576 , 0.572 );
    glVertex3f(-2.1, 0.1, 6.2);
    glVertex3f(-2.1, -0.4, 6.2);
    glVertex3f(-2.1, -0.4, 6); 
    glVertex3f(-2.1, 0.1, 6);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-2.1, 0.1, 6.2);
    glVertex3f(-2.1, -0.4, 6.2);
    glVertex3f(-2.1, -0.4, 6); 
    glVertex3f(-2.1, 0.1, 6);
    glEnd();
    
    //CARA DERRECHA
	glBegin(GL_QUADS);
    glColor3f( 0.588 , 0.576 , 0.572 );
    glVertex3f(-2.4, -0.4, 6.2);
    glVertex3f(-2.4, -0.4, 6);
    glVertex3f(-2.1, -0.4, 6); 
    glVertex3f(-2.1, -0.4, 6.2);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-2.4, -0.4, 6.2);
    glVertex3f(-2.4, -0.4, 6);
    glVertex3f(-2.1, -0.4, 6); 
    glVertex3f(-2.1, -0.4, 6.2);
    glEnd();
    
    //CARA IZQUIERDA
	glBegin(GL_QUADS);
    glColor3f( 0.588 , 0.576 , 0.572 );
    glVertex3f(-2.4, 0.1, 6.2);
    glVertex3f(-2.4, 0.1, 6);
    glVertex3f(-2.1, 0.1, 6); 
    glVertex3f(-2.1, 0.1, 6.2);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-2.4, 0.1, 6.2);
    glVertex3f(-2.4, 0.1, 6);
    glVertex3f(-2.1, 0.1, 6); 
    glVertex3f(-2.1, 0.1, 6.2);
    glEnd();
    
    //TABALA PARA PICAR
    glBegin(GL_POLYGON);
    glColor3f( 0.941 , 0.627 , 0.337 );
    glVertex3f(-2, -5, 5.6);
    glVertex3f(-2, -7.5, 5.6);
    glVertex3f(-1, -7.5, 5.6); 
    glVertex3f(-1, -5, 5.6);
    glVertex3f(-1.6, -7.5, 5.6);
    glVertex3f(-1.7, -8, 5.6);
    glVertex3f(-1.3, -8, 5.6); 
    glVertex3f(-1.4, -7.5, 5.6);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glColor3f( 1.0 , 1.0 , 1.0 );
    glVertex3f(-2, -5, 5.6);
    glVertex3f(-2, -7.5, 5.6);
    glVertex3f(-1, -7.5, 5.6); 
    glVertex3f(-1, -5, 5.6);
    glVertex3f(-1.6, -7.5, 5.6);
    glVertex3f(-1.7, -8, 5.6);
    glVertex3f(-1.3, -8, 5.6); 
    glVertex3f(-1.4, -7.5, 5.6);
    glEnd();
    
    //CUCHILLO
    //MANGO
    glBegin(GL_QUADS);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-1.39, -7.14, 5.7);
    glVertex3f(-1.3, -7.08, 5.7);
    glVertex3f(-1.5, -6.7, 5.7); 
    glVertex3f(-1.59, -6.75, 5.7);
    glEnd();
    
    //HOJA
    glBegin(GL_POLYGON);
    glColor3f( 0.858 , 0.858 , 0.858 );
    glVertex3f(-1.59, -6.75, 5.7);
    glVertex3f(-1.45, -6.67, 5.7);
    glVertex3f(-1.61, -6.3, 5.7);
    glVertex3f(-1.8, -6, 5.7); 
    glVertex3f(-1.97, -5.8, 5.7); 
    glVertex3f(-1.81, -6.23, 5.7);
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3f( 0.921 , 0.917 , 0.917 );
    glVertex3f(-1.45, -6.67, 5.7);
    glVertex3f(-1.4, -6.64, 5.7);
    glVertex3f(-1.58, -6.27, 5.7); 
    glVertex3f(-1.78, -5.96, 5.7);
    glVertex3f(-1.97, -5.8, 5.7); 
    glVertex3f(-1.8, -6, 5.7);
    glVertex3f(-1.61, -6.3, 5.7); 
    glEnd();
    
    //TAZA     
    glPushMatrix();
		
	glColor3f(0.929, 0.831, 1.0);
    
	glTranslatef(-1.17,6.25,5.5);
	
	glScalef(0.04, 0.050, 0.140);	
	glutSolidCube(10);
	glColor3f(0.0f, 0.0f, 0.0f);
			
	LineaCubo(2);	
	glEnd ();	
		
	glPopMatrix();
	
	//AZA
	//PARTE SUPERIOR
	glPushMatrix();
		
	glColor3f(0.929, 0.831, 1.0);
    
	glTranslatef(-1.31,6.40,6);
	
	glScalef(0.01, 0.065, 0.015);	
	glutSolidCube(10);
	glColor3f(0.0f, 0.0f, 0.0f);
			
	LineaCubo(2);	
	glEnd ();	
		
	glPopMatrix();
	
	//PARTE INFERIOR
	glPushMatrix();
		
	glColor3f(0.929, 0.831, 1.0);
    
	glTranslatef(-1.31,6.40,5.5);
	
	glScalef(0.01, 0.065, 0.025);	
	glutSolidCube(10);
	glColor3f(0.0f, 0.0f, 0.0f);
			
	LineaCubo(2);	
	glEnd ();	
		
	glPopMatrix();
	
	//PARTE DERECHA
	glPushMatrix();
		
	glColor3f(0.929, 0.831, 1.0);
    
	glTranslatef(-1.31,6.67,5.5);
	
	glScalef(0.01, 0.010, 0.115);	
	glutSolidCube(10);
	glColor3f(0.0f, 0.0f, 0.0f);
			
	LineaCubo(2);	
	glEnd ();	
		
	glPopMatrix();
}

void Candelabro ()
{
	 
    //PRIMER CANDELABRO
    //CARA FRONTAL
    glBegin(GL_QUADS);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(0, -2, 20);
    glVertex3f(0, -2, 18);
    glVertex3f(0, -2.2, 18); 
    glVertex3f(0, -2.2, 20);
    glEnd();
    
    //CARA POSTERIOR
    glBegin(GL_QUADS);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(0.2, -2, 20);
    glVertex3f(0.2, -2, 18);
    glVertex3f(0.2, -2.2, 18); 
    glVertex3f(0.2, -2.2, 20);
    glEnd();
    
    //CARA DERECHA
    glBegin(GL_QUADS);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(0, -2, 20);
    glVertex3f(0, -2, 18);
    glVertex3f(0.2, -2, 18); 
    glVertex3f(0.2, -2, 20);
    glEnd();
    
    //CARA IZQUIERDA
    glBegin(GL_QUADS);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(0, -2.2, 20);
    glVertex3f(0, -2.2, 18);
    glVertex3f(0.2, -2.2, 18); 
    glVertex3f(0.2, -2.2, 20);
    glEnd();
	
	//FOCO	
	//CARA SUPERIOR
    glBegin(GL_QUADS);
    glColor3f( 0.968 , 0.964 , 0.960 );
    glVertex3f(-0.5, -2, 18);
    glVertex3f(-0.5, -2.2, 18);
    glVertex3f(0.5, -2.2, 18); 
    glVertex3f(0.5, -2, 18);
    glEnd();
    
    //CARA INFERIOR
    glBegin(GL_QUADS);
    glColor3f( 0.968 , 0.964 , 0.960 );
    glVertex3f(-0.5, -2, 14);
    glVertex3f(-0.5, -2.2, 14);
    glVertex3f(0.5, -2.2, 14); 
    glVertex3f(0.5, -2, 14);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-0.5, -2, 14);
    glVertex3f(-0.5, -2.2, 14);
    glVertex3f(0.5, -2.2, 14); 
    glVertex3f(0.5, -2, 14);
    glEnd();
    
	//CARA FRONTAL
    glBegin(GL_QUADS);
    glColor3f( 0.968 , 0.964 , 0.960 );
    glVertex3f(-0.5, -2, 18);
    glVertex3f(-0.5, -2, 14);
    glVertex3f(-0.5, -2.2, 14); 
    glVertex3f(-0.5, -2.2, 18);
    glEnd();
    
    //CARA POSTERIOR
    glBegin(GL_QUADS);
    glColor3f( 0.968 , 0.964 , 0.960 );
    glVertex3f(0.5, -2, 18);
    glVertex3f(0.5, -2, 14);
    glVertex3f(0.5, -2.2, 18); 
    glVertex3f(0.5, -2.2, 14);
    glEnd();
    
    //CARA DERECHA
    glBegin(GL_QUADS);
    glColor3f( 0.968 , 0.964 , 0.960 );
    glVertex3f(-0.5, -2, 18);
    glVertex3f(-0.5, -2, 14);
    glVertex3f(0.5, -2, 14); 
    glVertex3f(0.5, -2, 18);
    glEnd();
       
    //CARA IZQUIERDA
    glBegin(GL_QUADS);
    glColor3f( 0.968 , 0.964 , 0.960 );
    glVertex3f(-0.5, -2.2, 18);
    glVertex3f(-0.5, -2.2, 14);
    glVertex3f(0.5, -2.2, 14); 
    glVertex3f(0.5, -2.2, 18);
    glEnd();
    
    //SEGUNDO CANDELABRO
    
    glPushMatrix();
    glTranslatef(0.0f, -5.0f, 0.0f);//TRASLADADO
    //CARA FRONTAL
    glBegin(GL_QUADS);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(0, -2, 20);
    glVertex3f(0, -2, 18);
    glVertex3f(0, -2.2, 18); 
    glVertex3f(0, -2.2, 20);
    glEnd();
    
    //CARA POSTERIOR
    glBegin(GL_QUADS);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(0.2, -2, 20);
    glVertex3f(0.2, -2, 18);
    glVertex3f(0.2, -2.2, 18); 
    glVertex3f(0.2, -2.2, 20);
    glEnd();
    
    //CARA DERECHA
    glBegin(GL_QUADS);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(0, -2, 20);
    glVertex3f(0, -2, 18);
    glVertex3f(0.2, -2, 18); 
    glVertex3f(0.2, -2, 20);
    glEnd();
    
    //CARA IZQUIERDA
    glBegin(GL_QUADS);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(0, -2.2, 20);
    glVertex3f(0, -2.2, 18);
    glVertex3f(0.2, -2.2, 18); 
    glVertex3f(0.2, -2.2, 20);
    glEnd();
	
	//FOCO	
	//CARA SUPERIOR
    glBegin(GL_QUADS);
    glColor3f( 0.968 , 0.964 , 0.960 );
    glVertex3f(-0.5, -2, 18);
    glVertex3f(-0.5, -2.2, 18);
    glVertex3f(0.5, -2.2, 18); 
    glVertex3f(0.5, -2, 18);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-0.5, -2, 18);
    glVertex3f(-0.5, -2.2, 18);
    glVertex3f(0.5, -2.2, 18); 
    glVertex3f(0.5, -2, 18);
    glEnd();
    
    //CARA INFERIOR
    glBegin(GL_QUADS);
    glColor3f( 0.968 , 0.964 , 0.960 );
    glVertex3f(-0.5, -2, 14);
    glVertex3f(-0.5, -2.2, 14);
    glVertex3f(0.5, -2.2, 14); 
    glVertex3f(0.5, -2, 14);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-0.5, -2, 14);
    glVertex3f(-0.5, -2.2, 14);
    glVertex3f(0.5, -2.2, 14); 
    glVertex3f(0.5, -2, 14);
    glEnd();
    
	//CARA FRONTAL
    glBegin(GL_QUADS);
    glColor3f( 0.968 , 0.964 , 0.960 );
    glVertex3f(-0.5, -2, 18);
    glVertex3f(-0.5, -2, 14);
    glVertex3f(-0.5, -2.2, 14); 
    glVertex3f(-0.5, -2.2, 18);
    glEnd();
    
    //CARA POSTERIOR
    glBegin(GL_QUADS);
    glColor3f( 0.968 , 0.964 , 0.960 );
    glVertex3f(0.5, -2, 18);
    glVertex3f(0.5, -2, 14);
    glVertex3f(0.5, -2.2, 18); 
    glVertex3f(0.5, -2.2, 14);
    glEnd();
    
    //CARA DERECHA
    glBegin(GL_QUADS);
    glColor3f( 0.968 , 0.964 , 0.960 );
    glVertex3f(-0.5, -2, 18);
    glVertex3f(-0.5, -2, 14);
    glVertex3f(0.5, -2, 14); 
    glVertex3f(0.5, -2, 18);
    glEnd();
    
    //CARA IZQUIERDA
    glBegin(GL_QUADS);
    glColor3f( 0.968 , 0.964 , 0.960 );
    glVertex3f(-0.5, -2.2, 18);
    glVertex3f(-0.5, -2.2, 14);
    glVertex3f(0.5, -2.2, 14); 
    glVertex3f(0.5, -2.2, 18);
    glEnd();
    glPopMatrix();
    
    //TERCER CANDELABRO
    
    glPushMatrix();
    glTranslatef(0.0f, 10.0f, 0.0f);//TRASLADADO
    //CARA FRONTAL
    glBegin(GL_QUADS);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(0, -2, 20);
    glVertex3f(0, -2, 18);
    glVertex3f(0, -2.2, 18); 
    glVertex3f(0, -2.2, 20);
    glEnd();
    
    //CARA POSTERIOR
    glBegin(GL_QUADS);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(0.2, -2, 20);
    glVertex3f(0.2, -2, 18);
    glVertex3f(0.2, -2.2, 18); 
    glVertex3f(0.2, -2.2, 20);
    glEnd();
    
    //CARA DERECHA
    glBegin(GL_QUADS);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(0, -2, 20);
    glVertex3f(0, -2, 18);
    glVertex3f(0.2, -2, 18); 
    glVertex3f(0.2, -2, 20);
    glEnd();
    
    //CARA IZQUIERDA
    glBegin(GL_QUADS);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(0, -2.2, 20);
    glVertex3f(0, -2.2, 18);
    glVertex3f(0.2, -2.2, 18); 
    glVertex3f(0.2, -2.2, 20);
    glEnd();
	
	//FOCO	
	//CARA SUPERIOR
    glBegin(GL_QUADS);
    glColor3f( 0.968 , 0.964 , 0.960 );
    glVertex3f(-0.5, -2, 18);
    glVertex3f(-0.5, -2.2, 18);
    glVertex3f(0.5, -2.2, 18); 
    glVertex3f(0.5, -2, 18);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-0.5, -2, 18);
    glVertex3f(-0.5, -2.2, 18);
    glVertex3f(0.5, -2.2, 18); 
    glVertex3f(0.5, -2, 18);
    glEnd();
    
    //CARA INFERIOR
    glBegin(GL_QUADS);
    glColor3f( 0.968 , 0.964 , 0.960 );
    glVertex3f(-0.5, -2, 14);
    glVertex3f(-0.5, -2.2, 14);
    glVertex3f(0.5, -2.2, 14); 
    glVertex3f(0.5, -2, 14);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-0.5, -2, 14);
    glVertex3f(-0.5, -2.2, 14);
    glVertex3f(0.5, -2.2, 14); 
    glVertex3f(0.5, -2, 14);
    glEnd();
    
	//CARA FRONTAL
    glBegin(GL_QUADS);
    glColor3f( 0.968 , 0.964 , 0.960 );
    glVertex3f(-0.5, -2, 18);
    glVertex3f(-0.5, -2, 14);
    glVertex3f(-0.5, -2.2, 14); 
    glVertex3f(-0.5, -2.2, 18);
    glEnd();
    
    //CARA POSTERIOR
    glBegin(GL_QUADS);
    glColor3f( 0.968 , 0.964 , 0.960 );
    glVertex3f(0.5, -2, 18);
    glVertex3f(0.5, -2, 14);
    glVertex3f(0.5, -2.2, 18); 
    glVertex3f(0.5, -2.2, 14);
    glEnd();
    
    //CARA DERECHA
    glBegin(GL_QUADS);
    glColor3f( 0.968 , 0.964 , 0.960 );
    glVertex3f(-0.5, -2, 18);
    glVertex3f(-0.5, -2, 14);
    glVertex3f(0.5, -2, 14); 
    glVertex3f(0.5, -2, 18);
    glEnd();
    
    //CARA IZQUIERDA
    glBegin(GL_QUADS);
    glColor3f( 0.968 , 0.964 , 0.960 );
    glVertex3f(-0.5, -2.2, 18);
    glVertex3f(-0.5, -2.2, 14);
    glVertex3f(0.5, -2.2, 14); 
    glVertex3f(0.5, -2.2, 18);
    glEnd();
    glPopMatrix();
    
    //CUARTO CANDELABRO 
    glPushMatrix();
    glTranslatef(0.0f, 8.0f, 0.0f);//TRASLADADO
    //CARA FRONTAL
    glBegin(GL_QUADS);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(0, -2, 20);
    glVertex3f(0, -2, 18);
    glVertex3f(0, -2.2, 18); 
    glVertex3f(0, -2.2, 20);
    glEnd();
    
    //CARA POSTERIOR
    glBegin(GL_QUADS);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(0.2, -2, 20);
    glVertex3f(0.2, -2, 18);
    glVertex3f(0.2, -2.2, 18); 
    glVertex3f(0.2, -2.2, 20);
    glEnd();
    
    //CARA DERECHA
    glBegin(GL_QUADS);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(0, -2, 20);
    glVertex3f(0, -2, 18);
    glVertex3f(0.2, -2, 18); 
    glVertex3f(0.2, -2, 20);
    glEnd();
    
    //CARA IZQUIERDA
    glBegin(GL_QUADS);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(0, -2.2, 20);
    glVertex3f(0, -2.2, 18);
    glVertex3f(0.2, -2.2, 18); 
    glVertex3f(0.2, -2.2, 20);
    glEnd();
	
	//FOCO	
	//CARA SUPERIOR
    glBegin(GL_QUADS);
    glColor3f( 0.968 , 0.964 , 0.960 );
    glVertex3f(-0.5, -2, 18);
    glVertex3f(-0.5, -2.2, 18);
    glVertex3f(0.5, -2.2, 18); 
    glVertex3f(0.5, -2, 18);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-0.5, -2, 18);
    glVertex3f(-0.5, -2.2, 18);
    glVertex3f(0.5, -2.2, 18); 
    glVertex3f(0.5, -2, 18);
    glEnd();
    
    
    //CARA INFERIOR
    glBegin(GL_QUADS);
    glColor3f( 0.968 , 0.964 , 0.960 );
    glVertex3f(-0.5, -2, 14);
    glVertex3f(-0.5, -2.2, 14);
    glVertex3f(0.5, -2.2, 14); 
    glVertex3f(0.5, -2, 14);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-0.5, -2, 14);
    glVertex3f(-0.5, -2.2, 14);
    glVertex3f(0.5, -2.2, 14); 
    glVertex3f(0.5, -2, 14);
    glEnd();
    
	//CARA FRONTAL
    glBegin(GL_QUADS);
    glColor3f( 0.968 , 0.964 , 0.960 );
    glVertex3f(-0.5, -2, 18);
    glVertex3f(-0.5, -2, 14);
    glVertex3f(-0.5, -2.2, 14); 
    glVertex3f(-0.5, -2.2, 18);
    glEnd();
    
    //CARA POSTERIOR
    glBegin(GL_QUADS);
    glColor3f( 0.968 , 0.964 , 0.960 );
    glVertex3f(0.5, -2, 18);
    glVertex3f(0.5, -2, 14);
    glVertex3f(0.5, -2.2, 18); 
    glVertex3f(0.5, -2.2, 14);
    glEnd();
    
    //CARA DERECHA
    glBegin(GL_QUADS);
    glColor3f( 0.968 , 0.964 , 0.960 );
    glVertex3f(-0.5, -2, 18);
    glVertex3f(-0.5, -2, 14);
    glVertex3f(0.5, -2, 14); 
    glVertex3f(0.5, -2, 18);
    glEnd();
    
    //CARA IZQUIERDA
    glBegin(GL_QUADS);
    glColor3f( 0.968 , 0.964 , 0.960 );
    glVertex3f(-0.5, -2.2, 18);
    glVertex3f(-0.5, -2.2, 14);
    glVertex3f(0.5, -2.2, 14); 
    glVertex3f(0.5, -2.2, 18);
    glEnd();
    glPopMatrix();
}

void cocina(){
//LADO TRASERO  DE LA COCINA
glBegin(GL_POLYGON);
glColor3f( 1.0, 1.0, 1.0 ); 
glVertex3f( 14.9, -2, 0.2 );
glVertex3f( 14.9, -2, 4.7);
glVertex3f( 14.9, 2, 4.7);
glVertex3f( 14.9, 2, 0.2 );
glEnd();

//LADO DERECHO DE LA COCINA
glBegin(GL_POLYGON);
glColor3f( 0.62, 0.62, 0.62 ); 
glVertex3f( 14.9, -2, 0 );
glVertex3f( 14.9, -2, 4);
glVertex3f( 6, -2, 4);
glVertex3f( 6, -2,0);
glEnd();

//LADO IZQUIERDO DE LA COCINA
glBegin(GL_POLYGON);
glColor3f( 0.62, 0.62, 0.62); 
glVertex3f( 15, 2, 0 );
glVertex3f( 15, 2, 4);
glVertex3f( 6 ,2, 4);
glVertex3f( 6, 2, 0 );
glEnd();
//LADO FRONTAL  DE LA COCINA
glBegin(GL_POLYGON);
glColor3f( 0.62, 0.62, 0.62); 
glVertex3f( 6, -2, 0.1 );
glVertex3f( 6, 2, 0.1);
glVertex3f( 6, 2, 4);
glVertex3f( 6, -2, 4);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 );
glVertex3f( 6, -2, 0 );
glVertex3f( 6, 2, 0);
glVertex3f( 6, 2, 4);
glVertex3f( 6, -2, 4);
glEnd();


//LADO FRONTAL DEL HORNO DE LA COCINA
glBegin(GL_POLYGON);
glColor3f( 0.45 ,0.45 ,0.45); 
glVertex3f( 5.99, -1.8, 0.7 );
glVertex3f( 5.99, 1.8, 0.7);
glVertex3f( 5.99, 1.8, 3.2);
glVertex3f( 5.99, -1.8, 3.2 );
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 );
glVertex3f( 5.99, -1.8, 0.7 );
glVertex3f( 5.99, 1.8, 0.7);
glVertex3f( 5.99, 1.8, 3.2);
glVertex3f( 5.99, -1.8, 3.2 );
glEnd();

//LADO FRONTAL DEL HORNO 1 DE LA COCINA
glBegin(GL_POLYGON);
glColor3f( 0.50 ,0.50 ,0.50); 
glVertex3f( 5.99, -1.8, 3.6 );
glVertex3f( 5.99, 1.8, 3.6);
glVertex3f( 5.99, 1.8, 3.9);
glVertex3f( 5.99, -1.8, 3.9 );
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 );
glVertex3f( 5.99, -1.8, 3.6 );
glVertex3f( 5.99, 1.8, 3.6);
glVertex3f( 5.99, 1.8, 3.9);
glVertex3f( 5.99, -1.8, 3.9 );
glEnd();
//LADO FRONTAL DEL HORNO 2 DE LA COCINA
glBegin(GL_POLYGON);
glColor3f(0.50 ,0.50 ,0.50); 
glVertex3f( 5.99, -1.8, 3.25 );
glVertex3f( 5.99, 1.8, 3.25);
glVertex3f( 5.99, 1.8, 3.55);
glVertex3f( 5.99, -1.8, 3.55 );
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 );
glVertex3f( 5.99, -1.8, 3.25 );
glVertex3f( 5.99, 1.8, 3.25);
glVertex3f( 5.99, 1.8, 3.55);
glVertex3f( 5.99, -1.8, 3.55 );
glEnd();

//LADO SUPERIOR   DE LA COCINA
glBegin(GL_POLYGON);
glColor3f( 0.64 ,0.64 ,0.64); 
glVertex3f( 14.9, -2, 4 );
glVertex3f( 14.9, 2 , 4 );
glVertex3f( 6, 2 , 4);
glVertex3f( 6, -2 ,  4  );
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 );
glVertex3f( 14.9, -2, 4 );
glVertex3f( 14.9, 2 , 4 );
glVertex3f( 6, 2 , 4);
glVertex3f( 6, -2 ,  4  );
glEnd();


//LADO SUPERIOR HORNILLA   DE LA COCINA
glBegin(GL_POLYGON);
glColor3f( 0.1, 0.1 ,0.1); 
glVertex3f( 14, -1.8, 4.01);
glVertex3f( 14, 1.8 , 4.01 );
glVertex3f( 6.2, 1.8 , 4.01);
glVertex3f( 6.2,- 1.8 , 4.01 );
glEnd();


//manija de cocina
glPushMatrix();
glTranslatef(6,1.5,3.4);
glRotated(90, 1,0,0);
cilindro = gluNewQuadric();
glColor3f(0.6,0.6 ,0.6);
gluQuadricDrawStyle(cilindro,GLU_FILL);
gluCylinder(cilindro,0.1,0.1,3,20,20);
glPopMatrix();


glPushMatrix();
glTranslatef(5.99,1.7,3.7);
glColor3f (0.1,0.1 ,0.1);
glutWireSphere(0.1,40,40);
glPopMatrix();

// ------------1
glPushMatrix();
glTranslatef(5.99,1.3,3.7);
glColor3f (0.6,0.6 ,0.6);
glutWireSphere(0.1,40,40);
glPopMatrix();

// ------------2
glPushMatrix();
glTranslatef(5.99,0.9,3.7);
glColor3f (0.6,0.6 ,0.6);
glutWireSphere(0.1,40,40);
glPopMatrix();

// ------------3
glPushMatrix();
glTranslatef(5.99,0.5,3.7);
glColor3f (0.6,0.6 ,0.6);
glutWireSphere(0.1,40,40);
glPopMatrix();

// ------------4
glPushMatrix();
glTranslatef(5.99,0.1,3.7);
glColor3f (0.6,0.6 ,0.6);
glutWireSphere(0.1,40,40);
glPopMatrix();

// ------------5
glPushMatrix();
glTranslatef(5.99,-0.3,3.7);
glColor3f (0.6,0.6 ,0.6);
glutWireSphere(0.1,40,40);
glPopMatrix();

// ------------6
glPushMatrix();
glTranslatef(5.99,-0.7,3.7);
glColor3f (0.6,0.6 ,0.6);
glutWireSphere(0.1,40,40);
glPopMatrix();

glPopMatrix();	
}

void silla()
{

//---------SILLA 1

glBegin(GL_POLYGON);
glColor3f(  0.1 ,0.1 ,0.1 ); 
glVertex3f( -10, -1, 4.9 );
glVertex3f( -10, 1, 4.9);
glVertex3f( -7, 1, 4.9);
glVertex3f( -7, -1, 4.9);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 );
glVertex3f( -10, -1, 4.9 );
glVertex3f( -10, 1, 4.9);
glVertex3f( -7, 1, 4.9);
glVertex3f( -7, -1, 4.9);
glEnd();
//Piso 1
glBegin(GL_POLYGON);
glColor3f(  0.1 ,0.1 ,0.1  ); 
glVertex3f( -10, -1, 0.2 );
glVertex3f( -10, 1, 0.2);
glVertex3f( -7, 1, 0.2);
glVertex3f( -7, -1, 0.2);
glEnd();
 
glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 );
glVertex3f( -10, -1, 0.2 );
glVertex3f( -10, 1, 0.2);
glVertex3f( -7, 1, 0.2);
glVertex3f( -7, -1, 0.2);
glEnd();
//----2
glBegin(GL_POLYGON);
glColor3f( 0.1 ,0.1 ,0.1 ); 
glVertex3f( -7, 1, 4.9 );
glVertex3f( -7, -1, 4.9);
glVertex3f( -6, -1, 4);
glVertex3f( -6,1, 4);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 );
glVertex3f( -7, 1, 4.9 );
glVertex3f( -7, -1, 4.9);
glVertex3f( -6, -1, 4);
glVertex3f( -6,1, 4);
glEnd();
//----3
glBegin(GL_POLYGON);
glColor3f( 0.1 ,0.1 ,0.1  ); 
glVertex3f( -10, 1, 4.9 );
glVertex3f( -10, -1, 4.9);
glVertex3f( -11, -1, 7.5);
glVertex3f( -11,1, 7.5);
glEnd();
glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 ); 
glVertex3f( -10, 1, 4.9 );
glVertex3f( -10, -1, 4.9);
glVertex3f( -11, -1, 7.5);
glVertex3f( -11,1, 7.5);
glEnd();


glPushMatrix();
glTranslatef(-10.5,1,0);
glPushMatrix();
glTranslatef(2,-1,0);
cilindro = gluNewQuadric();
glColor3f( 0.1 ,0.1 ,0.1 );
gluQuadricDrawStyle(cilindro,GLU_FILL);
gluCylinder(cilindro,0.3,0.3,5,20,20);
glEnd();
glPopMatrix();
glPopMatrix();
//---SILLA2

glBegin(GL_POLYGON);
glColor3f( 0.50 ,0.50 ,0.50 ); 
glVertex3f( -10, 7, 4.9 );
glVertex3f( -10, 4, 4.9);
glVertex3f( -7, 4, 4.9);
glVertex3f( -7, 7, 4.9);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 );
glVertex3f( -10, 7, 4.9 );
glVertex3f( -10, 4, 4.9);
glVertex3f( -7, 4, 4.9);
glVertex3f( -7, 7, 4.9);
glEnd();

//-----1
glBegin(GL_POLYGON);
glColor3f( 0.50 ,0.50 ,0.50 ); 
glVertex3f( -10, 7, 0.2 );
glVertex3f( -10, 4, 0.2);
glVertex3f( -7, 4, 0.2);
glVertex3f( -7, 7, 0.2);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 );
glVertex3f( -10, 7, 0.2 );
glVertex3f( -10, 4, 0.2);
glVertex3f( -7, 4, 0.2);
glVertex3f( -7, 7, 0.2);
glEnd();
//----2
glBegin(GL_POLYGON);
glColor3f(  0.50 ,0.50 ,0.50 ); 
glVertex3f( -7, 4, 4.9 );
glVertex3f( -7, 7, 4.9);
glVertex3f( -6, 7, 4);
glVertex3f( -6,4, 4);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 );
glVertex3f( -7, 4, 4.9 );
glVertex3f( -7, 7, 4.9);
glVertex3f( -6, 7, 4);
glVertex3f( -6,4, 4);
glEnd();
//----3
glBegin(GL_POLYGON);
glColor3f(  0.50 ,0.50 ,0.50 ); 
glVertex3f( -10, 7, 4.9 );
glVertex3f( -10, 4, 4.9);
glVertex3f( -11, 4, 7.5);
glVertex3f( -11,7, 7.5);
glEnd();
glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 ); 
glVertex3f( -10, 7, 4.9 );
glVertex3f( -10, 4, 4.9);
glVertex3f( -11, 4, 7.5);
glVertex3f( -11,7, 7.5);
glEnd();

glPushMatrix();
glTranslatef(-10.5,6,0);
glPushMatrix();
glTranslatef(2,-1,0);
cilindro = gluNewQuadric();
glColor3f( 0.50 ,0.50 ,0.50);
gluQuadricDrawStyle(cilindro,GLU_FILL);
gluCylinder(cilindro,0.3,0.3,5,20,20);
glEnd();
glPopMatrix();
glPopMatrix();


//---SILLA3

glBegin(GL_POLYGON);
glColor3f( 1.0,1.0,1.0); 
glVertex3f( -10, -7, 4.9 );
glVertex3f( -10, -4, 4.9);
glVertex3f( -7, -4, 4.9);
glVertex3f( -7, -7, 4.9);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 );
glVertex3f( -10, -7, 4.9 );
glVertex3f( -10, -4, 4.9);
glVertex3f( -7, -4, 4.9);
glVertex3f( -7, -7, 4.9);
glEnd();

//-----1
glBegin(GL_POLYGON);
glColor3f( 1.0,1.0,1.0); 
glVertex3f( -10, -7, 0.2 );
glVertex3f( -10, -4, 0.2);
glVertex3f( -7, -4, 0.2);
glVertex3f( -7, -7, 0.2);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 );
glVertex3f( -10,- 7, 0.2 );
glVertex3f( -10, -4, 0.2);
glVertex3f( -7, -4, 0.2);
glVertex3f( -7, -7, 0.2);
glEnd();
//----2
glBegin(GL_POLYGON);
glColor3f(  1.0,1.0,1.0 ); 
glVertex3f( -7,- 4, 4.9 );
glVertex3f( -7, -7, 4.9);
glVertex3f( -6, -7, 4);
glVertex3f( -6,-4, 4);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 );
glVertex3f( -7, -4, 4.9 );
glVertex3f( -7, -7, 4.9);
glVertex3f( -6, -7, 4);
glVertex3f( -6,-4, 4);
glEnd();
//----3
glBegin(GL_POLYGON);
glColor3f(  1.0,1.0,1.0 ); 
glVertex3f( -10,- 7, 4.9 );
glVertex3f( -10, -4, 4.9);
glVertex3f( -11, -4, 7.5);
glVertex3f( -11,-7, 7.5);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 ); 
glVertex3f( -10, -7, 4.9 );
glVertex3f( -10, -4, 4.9);
glVertex3f( -11, -4, 7.5);
glVertex3f( -11,-7, 7.5);
glEnd();

glPushMatrix();
glTranslatef(-10.5,-4.5,0);
glPushMatrix();
glTranslatef(2,-1,0);
cilindro = gluNewQuadric();
glColor3f( 1.0,1.0,1.0);
gluQuadricDrawStyle(cilindro,GLU_FILL);
gluCylinder(cilindro,0.3,0.3,5,20,20);
glEnd();
glPopMatrix();

glPopMatrix();

}
	

void Refrigedador(){
	
	//cara derecha del refri
	glBegin(GL_POLYGON	);
	glColor3f(colores[iDibujo][0], colores[iDibujo][1], colores[iDibujo][2]);
	glVertex3f(15, -24.99, 0.1);
    glVertex3f(15, -24.99, 13);
    glVertex3f(8, -24.99, 13); 
    glVertex3f(7.55, -24.99, 11);	
	glVertex3f(7.35, -24.99, 9);
    glVertex3f(7.15, -24.99, 6.6);
    glVertex3f(7.3, -24.99, 4); 
    glVertex3f(7.55, -24.99, 2);
	glVertex3f(8, -24.99, 0);       
    glEnd();
    
    //cara izq del refri
	glBegin(GL_POLYGON	);
	glColor3f(colores[iDibujo][0], colores[iDibujo][1], colores[iDibujo][2]);
	glVertex3f(15, -15, 0.1);
    glVertex3f(15, -15, 13);
    glVertex3f(8, -15, 13); 
    glVertex3f(7.55, -15, 11);	
	glVertex3f(7.35, -15, 9);
    glVertex3f(7.15, -15, 6.6);
    glVertex3f(7.3, -15, 4); 
    glVertex3f(7.55, -15, 2);
	glVertex3f(8, -15, 0);       
    glEnd();
    
    //cara atras del refri
	glBegin(GL_POLYGON	);
	glColor3f(colores[iDibujo][0], colores[iDibujo][1], colores[iDibujo][2]);
	glVertex3f(14.99, -25, 0);
    glVertex3f(14.99, -25, 13);
    glVertex3f(14.99, -15, 13); 
    glVertex3f(14.99, -15, 0);	    
    glEnd();
    
    //cara refri1
    glBegin(GL_POLYGON);
	glColor3f(colores[iDibujo][0], colores[iDibujo][1], colores[iDibujo][2]);
	glVertex3f(8, -15, 13);
    glVertex3f(7.55, -15, 11);
    glVertex3f(7.35, -15, 9); 
    glVertex3f(7.15, -15, 6.6);	
	glVertex3f(7.15, -19.8, 6.6);
    glVertex3f(7.35, -19.8, 9);
    glVertex3f(7.55, -19.8, 11); 
	glVertex3f(8, -19.8, 13);       
    glEnd();
    
    
    //cara refri2
   
    glBegin(GL_POLYGON	);
    glColor3f(colores[iDibujo][0], colores[iDibujo][1], colores[iDibujo][2]);
	glVertex3f(8, -20, 13);
    glVertex3f(7.55, -20, 11);
    glVertex3f(7.35, -20, 9); 
    glVertex3f(7.15, -20, 6.6);	
	glVertex3f(7.15, -25, 6.6);
    glVertex3f(7.35, -25, 9);
    glVertex3f(7.55, -25, 11); 
	glVertex3f(8, -25, 13);       
    glEnd();
    
     //cara refri3
    glBegin(GL_POLYGON	);
	glColor3f(colores[iDibujo][0], colores[iDibujo][1], colores[iDibujo][2]);
	glVertex3f(7.149, -15, 6.4);
    glVertex3f(7.29, -15, 4);
    glVertex3f(7.549, -15, 2); 
    glVertex3f(7.99, -15, 0);	
	glVertex3f(7.99, -19.8, 0);
    glVertex3f(7.549, -19.8, 2); 
	glVertex3f(7.29, -19.8, 4);  
	glVertex3f(7.149, -19.8, 6.4);          
    glEnd();
    
    //cara refri4
    glBegin(GL_POLYGON	);
	glColor3f(colores[iDibujo][0], colores[iDibujo][1], colores[iDibujo][2]);
	glVertex3f(7.149, -20, 6.4);
    glVertex3f(7.29, -20, 4);
    glVertex3f(7.549, -20, 2); 
    glVertex3f(7.99, -20, 0);	
	glVertex3f(7.99, -25, 0);
    glVertex3f(7.549, -25, 2); 
	glVertex3f(7.29, -25, 4);  
	glVertex3f(7.149, -25, 6.4);          
    glEnd();
    
    //piso
    glBegin(GL_POLYGON	);
	glColor3f(colores[iDibujo][0], colores[iDibujo][1], colores[iDibujo][2]);
	glVertex3f(8, -24.99, 0.19);
    glVertex3f(14.99, -25, 0.19);
    glVertex3f(14.99, -15, 0.19); 
    glVertex3f(8, -14.99, 0.19);	    
    glEnd();
    
    //techo
    glBegin(GL_POLYGON	);
	glColor3f(colores[iDibujo][0], colores[iDibujo][1], colores[iDibujo][2]);
	glVertex3f(8, -24.99, 12.99);
    glVertex3f(14.99, -25, 12.99);
    glVertex3f(14.99, -15, 12.99); 
    glVertex3f(8, -14.99, 12.99);	    
    glEnd();
    
    //palanca1
    glBegin(GL_POLYGON	);
	glColor3f( 0 , 0 , 0);
	glVertex3f(7.142, -19.6, 6.8);
    glVertex3f(7.342, -19.6, 9);
    glVertex3f(7.542, -19.6, 11); 
    glVertex3f(7.542, -19.8, 11);	
	glVertex3f(7.342, -19.8, 9);
    glVertex3f(7.142, -19.8, 6.8); 	    
    glEnd();
    
    //palanca2
    glBegin(GL_POLYGON	);
	glColor3f( 0 , 0 , 0);
	glVertex3f(7.142, -20, 6.8);
    glVertex3f(7.342, -20, 9);
    glVertex3f(7.542, -20, 11); 
    glVertex3f(7.542, -20.2, 11);	
	glVertex3f(7.342, -20.2, 9);
    glVertex3f(7.142, -20.2, 6.8); 	    
    glEnd();
    
     //palanca3
    glBegin(GL_POLYGON	);
	glColor3f( 0 , 0 , 0);
	glVertex3f(7.42, -19.6, 2.3);
    glVertex3f(7.32, -19.6, 4);
    glVertex3f(7.12, -19.6, 6.2); 
    glVertex3f(7.12, -19.8, 6.2);	
	glVertex3f(7.22, -19.8, 4);
    glVertex3f(7.42, -19.8, 2.3); 	    
    glEnd();
    
    //palanca4
    glBegin(GL_POLYGON	);
	glColor3f( 0 , 0 , 0);
	glVertex3f(7.42, -20, 2.3);
    glVertex3f(7.32, -20, 4);
    glVertex3f(7.12, -20, 6.2); 
    glVertex3f(7.12, -20.2, 6.2);	
	glVertex3f(7.22, -20.2, 4);
    glVertex3f(7.42, -20.2, 2.3); 	    
    glEnd();
    
    
    //espacioH
    glBegin(GL_POLYGON	);
	glColor3f( 0.337 , 0.337 , 0.337 );
	glVertex3f(7.14, -15, 6.6);
    glVertex3f(7.14, -25, 6.6);
    glVertex3f(7.14, -25, 6.4);	
    glVertex3f(7.14, -15, 6.4); 	    
    glEnd();
    
     //espacioV
    glBegin(GL_POLYGON	);
	glColor3f( 0.332 , 0.337 , 0.337 );
	glVertex3f(7.92, -19.8, 13);
    glVertex3f(7.52, -19.8, 11);
    glVertex3f(7.32, -19.8, 9); 
    glVertex3f(7.12, -19.8, 6.6);	
	glVertex3f(7.12, -19.8, 6.4);
    glVertex3f(7.32, -19.8, 9);
    glVertex3f(7.22, -19.8, 4); 
	glVertex3f(7.92, -19.8, 13); 
	
	glVertex3f(7.52, -19.8, 2);
    glVertex3f(7.92, -19.8, 0);
    glVertex3f(7.92, -20, 0); 
    glVertex3f(7.52, -20, 2);	
	glVertex3f(7.22, -20, 4);
    glVertex3f(7.12, -20, 6.4);
    glVertex3f(7.22, -19.8, 4); 
	glVertex3f(7.12, -20, 6.6); 
	
	glVertex3f(7.32, -20, 9);
    glVertex3f(7.52, -20, 11); 
	glVertex3f(7.9, -20, 13); 
		    
    glEnd();   
    
    //diseñocara refri1
    
    glLineWidth(4);
    glBegin(GL_LINE_LOOP);
	glColor3f( 0 , 0 , 0);
	glVertex3f(7.98, -15, 13);
    glVertex3f(7.548, -15, 11);
    glVertex3f(7.348, -15, 9); 
    glVertex3f(7.148, -15, 6.6);	
	glVertex3f(7.148, -19.8, 6.6);
    glVertex3f(7.348, -19.8, 9);
    glVertex3f(7.548, -19.8, 11); 
	glVertex3f(7.98, -19.8, 13); 
	glEnd();
	
	//diseñocara refri2
	glBegin(GL_LINE_LOOP);
	glColor3f( 0 , 0 , 0);
	glVertex3f(7.98, -20, 13);
    glVertex3f(7.548, -20, 11);
    glVertex3f(7.348, -20, 9); 
    glVertex3f(7.148, -20, 6.6);	
	glVertex3f(7.148, -25, 6.6);
    glVertex3f(7.348, -25, 9);
    glVertex3f(7.548, -25, 11); 
	glVertex3f(7.98, -25, 13);       
    glEnd();
    
   //diseñocara refri3
    glBegin(GL_LINE_LOOP);
	glColor3f( 0 , 0 , 0);
	glVertex3f(7.149, -15, 6.4);
    glVertex3f(7.29, -15, 4);
    glVertex3f(7.549, -15, 2); 
    glVertex3f(7.99, -15, 0);	
	glVertex3f(7.99, -19.8, 0);
    glVertex3f(7.549, -19.8, 2); 
	glVertex3f(7.29, -19.8, 4);  
	glVertex3f(7.149, -19.8, 6.4);          
    glEnd();
    
    //diseñocara refri4
    glBegin(GL_LINE_LOOP);
	glColor3f( 0 , 0 , 0);
	glVertex3f(7.149, -20, 6.4);
    glVertex3f(7.29, -20, 4);
    glVertex3f(7.549, -20, 2); 
    glVertex3f(7.99, -20, 0);	
	glVertex3f(7.99, -25, 0);
    glVertex3f(7.549, -25, 2); 
	glVertex3f(7.29, -25, 4);  
	glVertex3f(7.149, -25, 6.4);          
    glEnd();
       
}

void repisa1(){
	
	//parte frontal
	glBegin(GL_QUADS);
	glColor3f( 0.6, 0.5, 0.3); //marron claro
	glVertex3f(6.5, -2, 0);
    glVertex3f(6.5, -2, 4);
    glVertex3f(6.5, -14.5, 4); 
    glVertex3f(6.5, -14.5, 0); 
    glEnd();
    
    //manija primer cajon
    glBegin(GL_QUADS);
	glColor3f( 1.0, 1.0, 1.0); //blanco
	glVertex3f(6.49, -7, 3.4);
    glVertex3f(6.49, -7, 3.5);
    glVertex3f(6.49, -9, 3.5); 
    glVertex3f(6.49, -9, 3.4); 
    glEnd();
    
    //manija segundo cajon
    glBegin(GL_QUADS);
	glColor3f( 1.0, 1.0, 1.0); //blanco
	glVertex3f(6.49, -7, 2.2);
    glVertex3f(6.49, -7, 2.3);
    glVertex3f(6.49, -9, 2.3); 
    glVertex3f(6.49, -9, 2.2); 
    glEnd();
    
    //manija tercer cajon
    glBegin(GL_QUADS);
	glColor3f( 1.0, 1.0, 1.0); //blanco
	glVertex3f(6.49, -7, 0.90);
    glVertex3f(6.49, -7, 1);
    glVertex3f(6.49, -9, 1); 
    glVertex3f(6.49, -9, 0.90); 
    glEnd();
    
    //lineas frontal lado derecho
    glBegin(GL_QUADS);
	glColor3f( 0.0, 0.0, 0.0); //negro
	glVertex3f(6.5, -2, 0);
    glVertex3f(6.5, -2, 4);
    glVertex3f(6.5, -2.2, 4); 
    glVertex3f(6.5, -2.2, 0); 
    glEnd();
    
    //lineas lado izquierdo
    glBegin(GL_QUADS);
	glColor3f( 0.0, 0.0, 0.0); //negro
	glVertex3f(6.49, -2.01, 0);
    glVertex3f(6.49, -2.01, 4);
    glVertex3f(6.49, -2.14, 4); 
    glVertex3f(6.49, -2.14, 0); 
    glEnd();
    
    //linea primer cajon
    glBegin(GL_QUADS);
	glColor3f( 0.0, 0.0, 0.0); //negro
	glVertex3f(6.49, -2, 2.8);
    glVertex3f(6.49, -2, 2.9);
    glVertex3f(6.49, -14.5, 2.9); 
    glVertex3f(6.49, -14.5, 2.8); 
    glEnd();
    
    //linea segundo cajon
    glBegin(GL_QUADS);
	glColor3f( 0.0, 0.0, 0.0); //negro
	glVertex3f(6.49, -2, 1.5);
    glVertex3f(6.49, -2, 1.6);
    glVertex3f(6.49, -14.5, 1.6); 
    glVertex3f(6.49, -14.5, 1.5); 
    glEnd();
    
    //lineas de la base
    glBegin(GL_QUADS);
	glColor3f( 0.0, 0.0, 0.0); //negro
	glVertex3f(6.49, -2, 0);
    glVertex3f(6.49, -2, 0.2);
    glVertex3f(6.49, -14.5, 0.2); 
    glVertex3f(6.49, -14.5, 0); 
    glEnd();
    
    //parte costado derecho
    glBegin(GL_QUADS);
	glColor3f( 0.6, 0.5, 0.3); //marron claro
	glVertex3f(6.5, -14.5, 0);
    glVertex3f(6.5, -14.5, 4);
    glVertex3f(15, -14.5, 4); 
    glVertex3f(15, -14.5, 0); 
    glEnd();
    
    //lineas lado derecho
    glBegin(GL_QUADS);
	glColor3f( 0.0, 0.0, 0.0); //negro
	glVertex3f(6.49, -14.45, 0);
    glVertex3f(6.49, -14.45, 4);
    glVertex3f(6.49, -14.55, 4); 
    glVertex3f(6.49, -14.55, 0); 
    glEnd();
    
    
    //lineas lado derecho (base)
    glBegin(GL_QUADS);
	glColor3f( 0.0, 0.0, 0.0); //negro
	glVertex3f(6.5, -14.54, 0);
    glVertex3f(6.5, -14.54, 0.15);
    glVertex3f(15, -14.54, 0.15); 
    glVertex3f(15, -14.54, 0); 
    glEnd();
    
    
    //parte costado izquierda
    glBegin(GL_QUADS);
	glColor3f( 0.6, 0.5, 0.3); //marron claro
	glVertex3f(6.5, -2.01, 0);
    glVertex3f(6.5, -2.01, 4);
    glVertex3f(14.5, -2.01, 4); 
    glVertex3f(14.5, -2.01, 0); 
    glEnd();
    
    //parte superior
    glBegin(GL_QUADS);
	glColor3f( 0.0, 0.0 , 0.0 ); //negro
	glVertex3f(6.2, -2, 4);
    glVertex3f(14.5, -2, 4);
    glVertex3f(14.5, -14.5, 4); 
    glVertex3f(6.2, -14.5, 4); 
    glEnd();
    
    //-------------------------TOSTADORA------------------------
    
	//tostadora cara frontal
	glBegin(GL_QUADS);
	glColor3f( 0.7, 0.7, 0.8 ); //plomo
	glVertex3f(11, -9, 4.01);
    glVertex3f(11, -9, 6.01);
    glVertex3f(11, -13, 6.01); 
    glVertex3f(11, -13, 4.01); 
    glEnd();
    
    
    //botones tostadora
    glBegin(GL_QUADS);
	glColor3f( 0.0, 0.0, 0.1); //negro azulado
	glVertex3f(10.99, -9, 4.01);
    glVertex3f(10.99, -9, 4.57);
    glVertex3f(10.99, -13, 4.57); 
    glVertex3f(10.99, -13, 4.01); 
    glEnd();
    
    //boton izq
    glBegin(GL_QUADS);
	glColor3f( 1.0, 1.0, 1.0); //blanco
	glVertex3f(10.98, -9.5, 4.2);
    glVertex3f(10.98, -9.5, 4.3);
    glVertex3f(10.98, -10.5, 4.3); 
    glVertex3f(10.98, -10.5, 4.2); 
    glEnd();
    
    //boton derecho
    glBegin(GL_QUADS);
	glColor3f( 1.0, 1.0, 1.0); //blanco
	glVertex3f(10.98, -11.5, 4.2);
    glVertex3f(10.98, -11.5, 4.3);
    glVertex3f(10.98, -12.5, 4.3); 
    glVertex3f(10.98, -12.5, 4.2); 
    glEnd();
    
    //lineas tostadora lado derecho
    glBegin(GL_QUADS);
	glColor3f( 0.0, 0.0, 0.0 ); //negro
	glVertex3f(10.99, -12.9, 4.01);
    glVertex3f(10.99, -12.9, 6.01);
    glVertex3f(10.99, -13, 6.01); 
    glVertex3f(10.99, -13, 4.01); 
    glEnd();
    
    //lineas tostadora lado izquierdo 
    glBegin(GL_QUADS);
	glColor3f( 0.0, 0.0, 0.0 ); //negro
	glVertex3f(10.99, -9, 4.01);
    glVertex3f(10.99, -9, 6.01);
    glVertex3f(10.99, -9.10, 6.01); 
    glVertex3f(10.99, -9.10, 4.01); 
    glEnd();
    
    //tostadora cara derecha
    glBegin(GL_QUADS);
	glColor3f( 0.7, 0.7, 0.8 ); //plomo
	glVertex3f(11, -13, 4.01);
    glVertex3f(11, -13, 6.01);
    glVertex3f(13, -13, 6.01);
    glVertex3f(13, -13, 4.01);
	glEnd();
	
	//tostadora cara izquierda
	glBegin(GL_QUADS);
	glColor3f( 0.7, 0.7, 0.8 ); //plomo
	glVertex3f(11, -9.01, 4.01);
    glVertex3f(11, -9.01, 6.01);
    glVertex3f(13, -9.01, 6.01);
    glVertex3f(13, -9.01, 4.01);
    glEnd();
	
	//linea derecha lado izquierdo
	glBegin(GL_QUADS);
	glColor3f( 0.0, 0.0, 0.0 ); //negro
	glVertex3f(11, -9, 4.01);
    glVertex3f(11, -9, 6.01);
    glVertex3f(11.09, -9, 6.01);
    glVertex3f(11.09, -9, 4.01);
    glEnd();
    
    //linea izquierda lado izquierdo
	glBegin(GL_QUADS);
	glColor3f( 0.0, 0.0, 0.0 ); //negro
	glVertex3f(13, -9, 4.01);
    glVertex3f(13, -9, 6.01);
    glVertex3f(13.09, -9, 6.01);
    glVertex3f(13.09, -9, 4.01);
    glEnd();
    
	//tostadora parte trasera
	glBegin(GL_QUADS);
	glColor3f( 0.7, 0.7, 0.8 ); //plomo
	glVertex3f(13, -9, 4.01);
    glVertex3f(13, -9, 6.01);
    glVertex3f(13, -13, 6.01); 
    glVertex3f(13, -13, 4.01); 
    glEnd();
    
    //tostadora parte arriba
    glBegin(GL_QUADS);
	glColor3f( 0.0, 0.0, 0.0 ); //plomo
	glVertex3f(11, -9, 6.01);
    glVertex3f(13, -9, 6.01);
    glVertex3f(13, -13, 6.01); 
    glVertex3f(11, -13, 6.01); 
    glEnd();
    
    //lineas para poner pan de la tostadora
    glBegin(GL_QUADS);
	glColor3f( 1.0, 1.0, 1.0 ); //blanco
	glVertex3f(12.2, -9.5, 6.02);
    glVertex3f(12.5, -9.5, 6.02);
    glVertex3f(12.5, -12.5, 6.02); 
    glVertex3f(12.2, -12.5, 6.02); 
    glEnd();
    
    glBegin(GL_QUADS);
	glColor3f( 1.0, 1.0, 1.0 ); //blanco
	glVertex3f(11.4, -9.5, 6.02);
    glVertex3f(11.7, -9.5, 6.02);
    glVertex3f(11.7, -12.5, 6.02); 
    glVertex3f(11.4, -12.5, 6.02); 
    glEnd();
    
    
    //--------------------------TABLA DE PICAR------------------------------
    
    //parte frontal
    glBegin(GL_QUADS);
	glColor3f( 0.9, 0.8 , 0.3 ); //amarillo patito
	glVertex3f(9, -3.5, 4.02);
    glVertex3f(9, -3.5, 4.30);
    glVertex3f(9, -8, 4.30); 
    glVertex3f(9, -8, 4.02); 
    glEnd();
    
    //lineas parte frontal
    glBegin(GL_QUADS);
	glColor3f( 0.9, 0.8 , 0.3 ); //amarillo patito
	glVertex3f(9, -3.5, 4.02);
    glVertex3f(9, -3.5, 4.30);
    glVertex3f(9, -8, 4.30); 
    glVertex3f(9, -8, 4.02); 
    glEnd();
    
    //parte arriba
    glBegin(GL_QUADS);
	glColor3f( 0.9, 0.8 , 0.3 ); //amarillo patito
	glVertex3f(9, -3.5, 4.30);
    glVertex3f(12, -3.5, 4.30);
    glVertex3f(12, -8, 4.30); 
    glVertex3f(9, -8, 4.30); 
    glEnd();
    	
	//parte derecha
    glBegin(GL_QUADS);
	glColor3f( 0.9, 0.8, 0.3 ); //amarillo patito
	glVertex3f(9, -8, 4.02);
    glVertex3f(9, -8, 4.30);
    glVertex3f(12, -8, 4.30);
    glVertex3f(12, -8, 4.02);
    glEnd();
    
    //parte izquierda
    glBegin(GL_QUADS);
	glColor3f( 0.9, 0.8, 0.3 ); //amarillo patito
	glVertex3f(9, -3.5, 4.02);
    glVertex3f(9, -3.5, 4.30);
    glVertex3f(12, -3.5, 4.30);
    glVertex3f(12, -3.5, 4.02);
    glEnd();
    
    //parte atras
    glBegin(GL_QUADS);
	glColor3f( 0.9, 0.8, 0.3 ); //amarillo patito
	glVertex3f(12, -3.5, 4.02);
    glVertex3f(12, -3.5, 4.30);
    glVertex3f(12, -8, 4.30);
    glVertex3f(12, -8, 4.02);
    glEnd();
    
}

void repisa2 (){
	
	//parte frontal
	glBegin(GL_QUADS);
	glColor3f( 0.6, 0.5, 0.3); //marron claro
	glVertex3f(6.5, 14, 0);
    glVertex3f(6.5, 14, 4);
    glVertex3f(6.5, 2, 4); 
    glVertex3f(6.5, 2, 0); 
    glEnd();
    
    //manija primer cajon
    glBegin(GL_QUADS);
	glColor3f( 1.0, 1.0, 1.0); //blanco
	glVertex3f(6.49, 7, 3.4);
    glVertex3f(6.49, 7, 3.5);
    glVertex3f(6.49, 9, 3.5); 
    glVertex3f(6.49, 9, 3.4); 
    glEnd();
    
    //manija segundo cajon
    glBegin(GL_QUADS);
	glColor3f( 1.0, 1.0, 1.0); //blanco
	glVertex3f(6.49, 7, 2.2);
    glVertex3f(6.49, 7, 2.3);
    glVertex3f(6.49, 9, 2.3); 
    glVertex3f(6.49, 9, 2.2); 
    glEnd();
    
    //manija tercer cajon
    glBegin(GL_QUADS);
	glColor3f( 1.0, 1.0, 1.0); //blanco
	glVertex3f(6.49, 7, 0.8);
    glVertex3f(6.49, 7, 0.9);
    glVertex3f(6.49, 9, 0.9); 
    glVertex3f(6.49, 9, 0.8); 
    glEnd();
    
    //lineas de la base
    glBegin(GL_QUADS);
	glColor3f( 0.0, 0.0, 0.0); //negro
	glVertex3f(6.49, 2, 0);
    glVertex3f(6.49, 2, 0.2);
    glVertex3f(6.49, 14, 0.2); 
    glVertex3f(6.49, 14, 0); 
    glEnd();
    
    //lineas frontal lado derecho
    glBegin(GL_QUADS);
	glColor3f( 0.0, 0.0, 0.0); //negro
	glVertex3f(6.47, 2, 0);
    glVertex3f(6.47, 2, 4);
    glVertex3f(6.47, 2.10, 4); 
    glVertex3f(6.47, 2.10, 0); 
    glEnd();
    
    //lineas frontal lado izquierdo
    glBegin(GL_QUADS);
	glColor3f( 0.0, 0.0, 0.0); //negro
	glVertex3f(6.47, 13.90, 0);
    glVertex3f(6.47, 13.90, 4);
    glVertex3f(6.47, 14, 4); 
    glVertex3f(6.47, 14, 0); 
    glEnd();
    
    //lineas primer cajon
    glBegin(GL_QUADS);
	glColor3f( 0.0, 0.0, 0.0); //negro
	glVertex3f(6.4, 14, 2.8);
    glVertex3f(6.4, 14, 2.9);
    glVertex3f(6.4, 2, 2.9); 
    glVertex3f(6.4, 2, 2.8); 
    glEnd();
    
    //lineas segundo cajon
    glBegin(GL_QUADS);
	glColor3f( 0.0, 0.0, 0.0); //negro
	glVertex3f(6.4, 14, 1.5);
    glVertex3f(6.4, 14, 1.6);
    glVertex3f(6.4, 2, 1.6); 
    glVertex3f(6.4, 2, 1.5); 
    glEnd();
    
    //parte costado derecho
    glBegin(GL_QUADS);
	glColor3f( 0.6, 0.5, 0.3); //marron claro
	glVertex3f(6.5, 2, 0);
    glVertex3f(6.5, 2, 4);
    glVertex3f(15, 2.01, 4); 
    glVertex3f(15, 2.01, 0); 
    glEnd();
    
    
    //parte costado izquierda
    glBegin(GL_QUADS);
	glColor3f( 0.6, 0.5, 0.3); //marron claro
	glVertex3f(6.5, 14, 0);
    glVertex3f(6.5, 14, 4);
    glVertex3f(15, 14, 4); 
    glVertex3f(15, 14, 0); 
    glEnd();
    
    //parte superior
    glBegin(GL_QUADS);
	glColor3f( 0.0, 0.0 , 0.0 ); //negro
	glVertex3f(6.2, 14, 4);
    glVertex3f(15, 14, 4);
    glVertex3f(15, 2, 4); 
    glVertex3f(6.2, 2, 4); 
    glEnd();
    
    
    
    
}

void repostero(){
//parte delantera
glBegin(GL_QUADS);
glColor3f( 0.6, 0.5, 0.3);
glVertex3f(6.5, 25, 0);
glVertex3f(6.5, 14, 0);
glVertex3f(6.5, 14, 14); 
glVertex3f(6.5, 25, 14);
glEnd();	

//costado izquierdo
glBegin(GL_QUADS);
glColor3f( 0.6, 0.5, 0.3);
glVertex3f(6.5, 14, 14);
glVertex3f(6.5, 14, 0);
glVertex3f(15, 14, 0); 
glVertex3f(15, 14, 14);
glEnd();	

//parte de encima
glBegin(GL_QUADS);
glColor3f( 0.6, 0.5, 0.3);
glVertex3f(6.5, 25, 14);
glVertex3f(6.5, 14, 14);
glVertex3f(15, 14, 14); 
glVertex3f(15, 25, 14);
glEnd();
//////////////////////////////
//horno
glBegin(GL_QUADS);
glColor3f( 0.294 , 0.290 , 0.282 );
glVertex3f(6.4, 19.5, 5.5);
glVertex3f(6.4, 14, 5.5);
glVertex3f(6.4, 14, 2); 
glVertex3f(6.4, 19.5, 2);
glEnd();

//vidrio
glBegin(GL_QUADS);
glColor3f(0.7450f, 0.8784f, 1.0f);//celeste palido 
glVertex3f(6.3, 18.5, 4.7);
glVertex3f(6.3, 15, 4.7);
glVertex3f(6.3, 15, 2.8); 
glVertex3f(6.3, 18.5, 2.8);
glEnd();

//microondas

glBegin(GL_QUADS);
glColor3f( 0.670 , 0.666 , 0.658 ); 
glVertex3f(6.4, 19.5, 5.5);
glVertex3f(6.4, 14, 5.5);
glVertex3f(6.4, 14, 8); 
glVertex3f(6.4, 19.5, 8);
glEnd();
//vidrio
glBegin(GL_QUADS);
glColor3f(0.7450f, 0.8784f, 1.0f);//celeste palido
glVertex3f(6.3, 18.5, 6);
glVertex3f(6.3, 15, 6);
glVertex3f(6.3, 15, 7.5); 
glVertex3f(6.3, 18.5, 7.5);
glEnd();


//Manijas de cajones
glBegin(GL_QUADS);
glColor3f(1.0f, 1.0f, 1.0f);
glVertex3f(6.4, 17.5, 1.5);
glVertex3f(6.4, 16, 1.5);
glVertex3f(6.4, 16, 1.3); 
glVertex3f(6.4, 17.5, 1.3);
glEnd();

//-------------manijas trasladadas--------------
glPushMatrix();
glTranslatef(0.0f, 0.0f, 9.0f);//TRASLADADO
//Manijas de cajones
glBegin(GL_QUADS);
glColor3f(1.0f, 1.0f, 1.0f);
glVertex3f(6.4, 17.5, 1.5);
glVertex3f(6.4, 16, 1.5);
glVertex3f(6.4, 16, 1.3); 
glVertex3f(6.4, 17.5, 1.3);
glEnd();
glPopMatrix();

glPushMatrix();
glTranslatef(0.0f, 0.0f, 10.0f);//TRASLADADO
//Manijas de cajones
glBegin(GL_QUADS);
glColor3f(1.0f, 1.0f, 1.0f);
glVertex3f(6.4, 17.5, 1.5);
glVertex3f(6.4, 16, 1.5);
glVertex3f(6.4, 16, 1.3); 
glVertex3f(6.4, 17.5, 1.3);
glEnd();
glPopMatrix();

glPushMatrix();
glTranslatef(0.0f, 5.5f, 0.0f);//TRASLADADO
//Manijas de cajones
glBegin(GL_QUADS);
glColor3f(1.0f, 1.0f, 1.0f);
glVertex3f(6.4, 17.5, 1.5);
glVertex3f(6.4, 16, 1.5);
glVertex3f(6.4, 16, 1.3); 
glVertex3f(6.4, 17.5, 1.3);
glEnd();
glPopMatrix();

glPushMatrix();
glTranslatef(0.0f, 5.5, 4.0f);//TRASLADADO
//Manijas de cajones
glBegin(GL_QUADS);
glColor3f(1.0f, 1.0f, 1.0f);
glVertex3f(6.4, 17.5, 1.5);
glVertex3f(6.4, 16, 1.5);
glVertex3f(6.4, 16, 1.3); 
glVertex3f(6.4, 17.5, 1.3);
glEnd();
glPopMatrix();

glPushMatrix();
glTranslatef(0.0f, 5.5f, 9.0f);//TRASLADADO
//Manijas de cajones
glBegin(GL_QUADS);
glColor3f(1.0f, 1.0f, 1.0f);
glVertex3f(6.4, 17.5, 1.5);
glVertex3f(6.4, 16, 1.5);
glVertex3f(6.4, 16, 1.3); 
glVertex3f(6.4, 17.5, 1.3);
glEnd();
glPopMatrix();

glPushMatrix();
glTranslatef(0.0f, 5.5f, 10.0f);//TRASLADADO
//Manijas de cajones
glBegin(GL_QUADS);
glColor3f(1.0f, 1.0f, 1.0f);
glVertex3f(6.4, 17.5, 1.5);
glVertex3f(6.4, 16, 1.5);
glVertex3f(6.4, 16, 1.3); 
glVertex3f(6.4, 17.5, 1.3);
glEnd();
glPopMatrix();

//LINEAS PARA SEPARACION DE CAJONES
glLineWidth(2); 
glBegin(GL_LINES);
glColor3f(0.0f, 0.0f, 0.0f);
glVertex3f(6.5, 19.5, 14);
glVertex3f(6.5, 19.5, 0);

glVertex3f(6.5, 25, 10.84);
glVertex3f(6.5, 14, 10.84);

glVertex3f(6.5, 25, 6.0);
glVertex3f(6.5, 19.5, 6.0);

glVertex3f(6.5, 25, 2.0);
glVertex3f(6.5, 14, 2);

glEnd();

//LINEAS PARA MUEBLE
glLineWidth(2); 
glBegin(GL_LINES);
glColor3f(0.0f, 0.0f, 0.0f);

glVertex3f(6.5, 14, 14);
glVertex3f(6.5, 14, 0);

glVertex3f(6.5, 25, 14);
glVertex3f(6.5, 14, 14);

glVertex3f(6.5, 14, 14);
glVertex3f(15, 14, 14);

glVertex3f(14.9, 14, 14);
glVertex3f(14.9, 14, 0);

glEnd();
}

void estanteArriba(){
 //arriba estante
glBegin(GL_QUADS);
glColor3f( 0.6, 0.5, 0.3);
glVertex3f(15, 13.99, 14);
glVertex3f(11.5, 13.99, 14);
glVertex3f(11.5, -14.99, 14); 
glVertex3f(15, -14.99, 14);
glEnd();

 //abajo estante
glBegin(GL_QUADS);
glColor3f( 0.6, 0.5, 0.3);
glVertex3f(15, 13.99, 11);
glVertex3f(11.5, 13.99, 11);
glVertex3f(11.5, -14.99, 11); 
glVertex3f(15, -14.99, 11);
glEnd();

 //atras estante
glBegin(GL_QUADS);
glColor3f( 0.6, 0.5, 0.3);
glVertex3f(14.99, 13.99, 14);
glVertex3f(14.99, 13.99, 11);
glVertex3f(14.99, -14.99, 11); 
glVertex3f(14.99, -14.99, 14);
glEnd();


 //derecha estante
glBegin(GL_QUADS);
glColor3f( 0.6, 0.5, 0.3);
glVertex3f(14.99, -14.99, 14);
glVertex3f(14.99, -14.99, 11);
glVertex3f(11.49, -14.99, 11); 
glVertex3f(11.49, -14.99, 14);
glEnd();


//separaciones1 estante
glBegin(GL_QUADS);
glColor3f( 0.835 , 0.827 , 0.819 );
glVertex3f(11.49, 13.99, 11);
glVertex3f(11.49, 13.99, 14);
glVertex3f(11.49, 13.49, 14); 
glVertex3f(11.49, 13.49, 11);
glEnd();

//separaciones2 estante
glBegin(GL_QUADS);
glColor3f( 0.835 , 0.827 , 0.819 );
glVertex3f(11.49, 4.89, 11);
glVertex3f(11.49, 4.89, 14);
glVertex3f(11.49, 4.39, 14); 
glVertex3f(11.49, 4.49, 11);
glEnd();

//separaciones3 estante
glBegin(GL_QUADS);
glColor3f( 0.835 , 0.827 , 0.819 );
glVertex3f(11.49, -5.49, 11);
glVertex3f(11.49, -5.49, 14);
glVertex3f(11.49, -5.99, 14); 
glVertex3f(11.49, -5.99, 11);
glEnd();

//separaciones4 estante
glBegin(GL_QUADS);
glColor3f( 0.835 , 0.827 , 0.819 );
glVertex3f(11.49, -14.49, 11);
glVertex3f(11.49, -14.49, 14);
glVertex3f(11.49, -14.99, 14); 
glVertex3f(11.49, -14.99, 11);
glEnd();

//separaciones5 estante
glBegin(GL_QUADS);
glColor3f( 0.835 , 0.827 , 0.819 );
glVertex3f(11.49, 14, 11.5);
glVertex3f(11.49, 14, 11);
glVertex3f(11.49, -15, 11); 
glVertex3f(11.49, -15, 11.5);
glEnd();
//separaciones6 estante
glBegin(GL_QUADS);
glColor3f( 0.835 , 0.827 , 0.819 );
glVertex3f(11.49, 14, 14);
glVertex3f(11.49, 14, 13.5);
glVertex3f(11.49, -15, 13.5); 
glVertex3f(11.49, -15, 14);
glEnd();

//1
glBegin(GL_QUADS);
glColor3f( 0.835 , 0.827 , 0.819 );
glVertex3f(11.49, 4.9, 11);
glVertex3f(11.49, 4.9, 14);
glVertex3f(14.99, 4.9, 14); 
glVertex3f(14.99, 4.9, 11);
glEnd();
//2
glBegin(GL_QUADS);
glColor3f( 0.835 , 0.827 , 0.819 );
glVertex3f(11.49, 4.5, 11);
glVertex3f(11.49, 4.5, 14);
glVertex3f(14.99, 4.5, 14); 
glVertex3f(14.99, 4.5, 11);
glEnd();
//3
glBegin(GL_QUADS);
glColor3f( 0.835 , 0.827 , 0.819 );
glVertex3f(11.49, -5.49, 11);
glVertex3f(11.49, -5.49, 14);
glVertex3f(14.99, -5.49, 14); 
glVertex3f(14.99, -5.49, 11);
glEnd();
//4
glBegin(GL_QUADS);
glColor3f( 0.835 , 0.827 , 0.819 );
glVertex3f(11.49, -5.99, 11);
glVertex3f(11.49, -5.99, 14);
glVertex3f(14.99, -5.99, 14); 
glVertex3f(14.99, -5.99, 11);
glEnd();


//diseño
glLineWidth(3);
glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0, 0.0 );
glVertex3f(11.48, 14, 14);
glVertex3f(11.48, 14, 11);
glVertex3f(11.48, -15, 11); 
glVertex3f(11.48, -15, 14);
glEnd();

//sombreado1
glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0, 0.0 );
glVertex3f(11.48, 13.48, 13.5);
glVertex3f(11.48, 13.48, 11.5);
glVertex3f(11.48, 4.9, 11.5); 
glVertex3f(11.48, 4.9, 13.5); 
glEnd();

//sombreado2
glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0, 0.0 );
glVertex3f(11.48, 4.38, 13.5);
glVertex3f(11.48, 4.38, 11.5);
glVertex3f(11.48, -5.48, 11.5); 
glVertex3f(11.48, -5.48, 13.5); 
glEnd();

//sombreado3
glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0, 0.0 );
glVertex3f(11.48, -5.98, 13.5);
glVertex3f(11.48, -5.98, 11.5);
glVertex3f(11.48, -14.48, 11.5); 
glVertex3f(11.48, -14.48, 13.5); 
glEnd();


//1
glBegin(GL_LINE_LOOP);
glColor3f( 0.835 , 0.827 , 0.819 );
glVertex3f(11.51, 4.9, 11);
glVertex3f(11.51, 4.9, 14);
glVertex3f(14.01, 4.9, 14); 
glVertex3f(14.01, 4.9, 11);
glEnd();
//2
glBegin(GL_LINE_LOOP);
glColor3f( 0.835 , 0.827 , 0.819 );
glVertex3f(11.51, 4.5, 11);
glVertex3f(11.51, 4.5, 14);
glVertex3f(15.01, 4.5, 14); 
glVertex3f(15.01, 4.5, 11);
glEnd();
//3
glBegin(GL_LINE_LOOP);
glColor3f( 0.835 , 0.827 , 0.819 );
glVertex3f(11.51, -5.49, 11);
glVertex3f(11.51, -5.49, 14);
glVertex3f(15.01, -5.49, 14); 
glVertex3f(15.01, -5.49, 11);
glEnd();
//4
glBegin(GL_LINE_LOOP);
glColor3f( 0.835 , 0.827 , 0.819 );
glVertex3f(11.51, -5.99, 11);
glVertex3f(11.51, -5.99, 14);
glVertex3f(15.01, -5.99, 14); 
glVertex3f(15.01, -5.99, 11);
glEnd();


}

void Utensilios ()
{
	//ESPATULA
    glBegin(GL_QUADS);
    glColor3f( 0.858 , 0.858 , 0.858 );
    glVertex3f(14.9, -9, 11);
    glVertex3f(14.9, -9.2 , 11);
    glVertex3f(14.9, -9.2, 8);
    glVertex3f(14.9, -9, 8); 
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(14.9, -9, 11);
    glVertex3f(14.9, -9.2 , 11);
    glVertex3f(14.9, -9.2, 8);
    glVertex3f(14.9, -9, 8); 
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3f( 0.858 , 0.858 , 0.858 );
    glVertex3f(14.9, -9.2, 8);
    glVertex3f(14.9, -9.7, 7.5);
    glVertex3f(14.9, -9.7, 6.5);
    glVertex3f(14.9, -8.5, 6.5);
    glVertex3f(14.9, -8.5, 7.5);
    glVertex3f(14.9, -9, 8);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glColor3f( 0.858 , 0.858 , 0.858 );
    glVertex3f(14.9, -9.2, 8);
    glVertex3f(14.9, -9.7, 7.5);
    glVertex3f(14.9, -9.7, 6.5);
    glVertex3f(14.9, -8.5, 6.5);
    glVertex3f(14.9, -8.5, 7.5);
    glVertex3f(14.9, -9, 8);
    glEnd();
    
    //CUCHARON
    glPushMatrix();
    glTranslatef(0.0f, 3.0f, 0.0f);//TRASLADADO
    
    glBegin(GL_QUADS);
    glColor3f( 0.858 , 0.858 , 0.858 );
    glVertex3f(14.9, -9, 11);
    glVertex3f(14.9, -9.2 , 11);
    glVertex3f(14.9, -9.2, 8);
    glVertex3f(14.9, -9, 8); 
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3f( 0.858 , 0.858 , 0.858 );
    glVertex3f(14.9, -9.2, 8);
    glVertex3f(14.9, -9.6, 7.5);
    glVertex3f(14.9, -9.6, 6.79);
    glVertex3f(14.9, -9.41, 6.36);
    glVertex3f(14.9, -8.79, 6.35);
    glVertex3f(14.9, -8.41, 6.83);
    glVertex3f(14.9, -8.5, 7.5);
    glVertex3f(14.9, -9, 8);
    glEnd();
    glPopMatrix();
}

///////////////////////////// PATIO /////////////////////////////////////

void linea_vereda(){
	//madera donde esta los asientos
	glLineWidth(1.5);
	glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );//negro
    glVertex3f(-50, -31.5, 0.91);
    glVertex3f(-50, -10.5, 0.91);
    glVertex3f(-39, -10.5, 0.91); 
    glVertex3f(-39, -31.5, 0.91);
    glEnd();
    
    glLineWidth(1.5);
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );//negro
    glVertex3f(-50, -31.5, 1.2);
    glVertex3f(-50, -10.5, 1.2);
    glVertex3f(-39, -10.5, 1.2); 
    glVertex3f(-39, -31.5, 1.2);
    glEnd();
    //vereda saleindo de la mampara
    glLineWidth(1.5);
	glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );//negro
    glVertex3f(-15, -25, 0.1);
    glVertex3f(-15, 25, 0.1);
    glVertex3f(-25, 25, 0.1); 
    glVertex3f(-25, -19, 0.1);
    glVertex3f(-40, -19, 0.1);
    glVertex3f(-40, -25, 0.1); 
    glEnd();
    
    glLineWidth(1.5);
	glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );//negro
    glVertex3f(-15, -25, 0.7);
    glVertex3f(-15, 25, 0.7);
    glVertex3f(-25, 25, 0.7); 
    glVertex3f(-25, -19, 0.7);
    glVertex3f(-40, -19, 0.7);
    glVertex3f(-40, -25, 0.7); 
    glEnd();
    //madera pqgada a la pared
    glLineWidth(1.5);
	glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );//negro
    glVertex3f(-50, 25, 0.1);
    glVertex3f(-50, -12,  0.1);
    glVertex3f(-45, -12, 0.1); 
    glVertex3f(-45, 25, 0.1);
    glEnd();
    
    glLineWidth(1.5);
	glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );//negro
    glVertex3f(-50, 25, 0.7);
    glVertex3f(-50, -12,  0.7);
    glVertex3f(-45, -12, 0.7); 
    glVertex3f(-45, 25, 0.7);
    glEnd();
}

void vereda_piscina(){
	//VEREDA AL SALIR POR MAMPARA
	glBegin(GL_QUADS);
	glColor3f( 0.341 , 0.278 , 0.235 );//marron OSCURO
	glVertex3f(-15, 25, 0.1);
    glVertex3f(-15, -25, 0.1);
    glVertex3f(-25, -25,0.1); 
    glVertex3f(-25, 25, 0.1); 
    
    glVertex3f(-25, -25, 0.1);
    glVertex3f(-25, -19, 0.1);
    glVertex3f(-40, -19,0.1); 
    glVertex3f(-40, -25, 0.1);
	
	//cierre de grosor cerca al pasadizo
    glVertex3f(-25, 25, 0.1);
    glVertex3f(-15, 25, 0.1);
    glVertex3f(-15, 25, 0.7); 
    glVertex3f(-25, 25, 0.7);
	 
    //VEREDA CERCA A LA PARED
    glVertex3f(-45, 25, 0.1);
    glVertex3f(-50, 25, 0.1);
    glVertex3f(-50, -12,0.1); 
    glVertex3f(-45, -12, 0.1);
    
    //GROSOR DE LA VEREDA
    
    glVertex3f(-15, 25, 0.7);
    glVertex3f(-15, -25, 0.7);
    glVertex3f(-25, -25,0.7); 
    glVertex3f(-25, 25, 0.7); 
    
    glVertex3f(-25, -25, 0.7);
    glVertex3f(-25, -19, 0.7);
    glVertex3f(-40, -19,0.7); 
    glVertex3f(-40, -25, 0.7);
    
    //GROSOR VEREDA CERCA A LA PARED
    glVertex3f(-45, 25, 0.7);
    glVertex3f(-50, 25, 0.7);
    glVertex3f(-50, -12,0.7); 
    glVertex3f(-45, -12, 0.7);
    
    // COSTADOS
    glVertex3f(-40, -25, 0.1);
    glVertex3f(-15, -25, 0.1);
    glVertex3f(-15, -25, 0.7);
    glVertex3f(-40, -25, 0.7);
    
    glVertex3f(-25, 25, 0.1);
    glVertex3f(-25, -19, 0.1);
    glVertex3f(-25, -19, 0.7);
    glVertex3f(-25, 25, 0.7);
    
    glVertex3f(-25, -19, 0.1);
    glVertex3f(-40, -19,  0.1);
    glVertex3f(-40, -19,  0.7);
    glVertex3f(-25, -19, 0.7);
    
    //COSTADOS VEREDA CERCA A LA PARED
    glVertex3f(-45, 25, 0.1);
    glVertex3f(-45, -12, 0.1);
    glVertex3f(-45, -12, 0.7); 
    glVertex3f(-45, 25, 0.7);
    
    glVertex3f(-45, -12, 0.1);
    glVertex3f(-50, -12, 0.1);
    glVertex3f(-50, -12, 0.7); 
    glVertex3f(-45, -12, 0.7);
    glEnd();
//------------------------------------------------------------------------------------
    //BASE DE CONCRETO PARA ASIENTOS DE PISCINA
    glBegin(GL_QUADS);
	glColor3f( 1.0 , 1.0 , 1.0 );//BLANCO
	glVertex3f(-50, -12, 0.1);
    glVertex3f(-40, -12, 0.1);
    glVertex3f(-40, -30,0.1); 
    glVertex3f(-50, -30, 0.1);
    
    //GROSOR
    glVertex3f(-50, -12, 0.9);
    glVertex3f(-40, -12, 0.9);
    glVertex3f(-40, -30,0.9); 
    glVertex3f(-50, -30, 0.9);
    
    //COSTADOS
    glVertex3f(-40, -12, 0.1);
    glVertex3f(-40, -30, 0.1);
    glVertex3f(-40, -30,0.9); 
    glVertex3f(-40, -12, 0.9);
    
    glVertex3f(-40, -30,0.1);
    glVertex3f(-50, -30,0.1);
    glVertex3f(-50, -30,0.9); 
    glVertex3f(-40, -30,0.9);
    
    glVertex3f(-40, -12,0.1);
    glVertex3f(-50, -12,0.1);
    glVertex3f(-50, -12,0.9); 
    glVertex3f(-40, -12,0.9);
    glEnd();
    
    //MADERA ENCIMA DE CONCRETO PARA LA BASE DE LOS ASIENTOS
    glBegin(GL_QUADS);
	glColor3f( 0.341 , 0.278 , 0.235 );//marron OSCURO
	glVertex3f(-50, -10.5, 0.91);
    glVertex3f(-39, -10.5, 0.91);
    glVertex3f(-39, -31.5, 0.91); 
    glVertex3f(-50, -31.5, 0.91);
    
    //GROSOR
    glVertex3f(-50, -10.5, 1.2);
    glVertex3f(-39, -10.5, 1.2);
    glVertex3f(-39, -31.5, 1.2); 
    glVertex3f(-50, -31.5, 1.2);
    
    //COSTADOS
    glVertex3f(-50, -10.5, 0.91);
    glVertex3f(-39, -10.5, 0.91);
    glVertex3f(-39, -10.5, 1.2); 
    glVertex3f(-50, -10.5, 1.2);
    
    glVertex3f(-39, -10.5, 0.91);
    glVertex3f(-39, -31.5, 0.91);
    glVertex3f(-39, -31.5, 1.2); 
    glVertex3f(-39, -10.5, 1.2);
    
    glVertex3f(-39, -31.5, 0.91);
    glVertex3f(-50, -31.5, 0.91);
    glVertex3f(-50, -31.5, 1.2); 
    glVertex3f(-39, -31.5, 1.2);
    glEnd();
    
    linea_vereda();
    glEnd();
}

void silla1_piscina(){
	//MADERA DEL ASIENTO
	//base de la silla
	glBegin(GL_QUADS);
	glColor3f( 0.541 , 0.372 , 0.188 );//marron maso menos claro
	glVertex3f(-50, -27,1.21);
    glVertex3f(-44, -27,1.21);
    glVertex3f(-44, -22,1.21); 
    glVertex3f(-50, -22,1.21); 
    
    //GROSOR
    glVertex3f(-50, -27,1.6);
    glVertex3f(-44, -27,1.6);
    glVertex3f(-44, -22,1.6); 
    glVertex3f(-50, -22,1.6); 
    
    //COSTADOS
    //BASE DE SILLA
    glVertex3f(-50, -27, 1.21);
    glVertex3f(-44, -27, 1.21);
    glVertex3f(-44, -27, 1.6); 
    glVertex3f(-50, -27, 1.6); 
    
    glVertex3f(-44, -27, 1.21);
    glVertex3f(-44, -22, 1.21);
    glVertex3f(-44, -22, 1.6); 
    glVertex3f(-44, -27, 1.6); 
    
    glVertex3f(-44, -22, 1.21);
    glVertex3f(-50, -22,  1.21);
    glVertex3f(-50, -22,  1.6); 
    glVertex3f(-44, -22, 1.6); 
    glEnd();
    ///---------------------------------------------------------
    //espaldar
    // madera izquierda
    glBegin(GL_QUADS);
	glColor3f( 0.541 , 0.372 , 0.188 );//marron maso menos claro
	glVertex3f(-50, -27, 1.6);
    glVertex3f(-50, -27, 4);
    glVertex3f(-49, -27, 4); 
    glVertex3f(-49, -27, 1.6); 
    
    glVertex3f(-49, -27, 1.6);
    glVertex3f(-49, -27, 4);
    glVertex3f(-49, -26.2, 4); 
    glVertex3f(-49, -26.2, 1.6);
    
    glVertex3f(-49, -26.2, 1.6);
    glVertex3f(-49, -26.2, 4);
    glVertex3f(-50, -26.2, 4); 
    glVertex3f(-50, -26.2, 1.6);
    
    //madera derecha
    glVertex3f(-50, -22.8, 1.6);
    glVertex3f(-49, -22.8, 1.6);
    glVertex3f(-49, -22.8, 4); 
    glVertex3f(-50, -22.8, 4);
    
    glVertex3f(-49, -22.8,  1.6);
    glVertex3f(-49, -22,  1.6);
    glVertex3f(-49, -22,  4); 
    glVertex3f(-49, -22.8,  4);
    
    glVertex3f(-49, -22,  1.6);
    glVertex3f(-50, -22,  1.6);
    glVertex3f(-50, -22,  4); 
    glVertex3f(-49, -22,  4);
    
    //madera centro
    glVertex3f(-49, -26.2, 3);
    glVertex3f(-49, -26.2, 2.5);
    glVertex3f(-49, -22.8, 2.5); 
    glVertex3f(-49, -22.8, 3);
    
    glVertex3f(-49, -26.2, 3);
    glVertex3f(-50, -26.2, 3);
    glVertex3f(-50, -22.8, 3); 
    glVertex3f(-49, -22.8, 3);
    
    glVertex3f(-49, -26.2, 2.5);
    glVertex3f(-49, -26.2, 2.5);
    glVertex3f(-50, -22.8, 2.5); 
    glVertex3f(-49, -22.8, 2.5);
    //tapa encima de la madera
    glVertex3f(-50, -27, 4);
    glVertex3f(-50, -26.2, 4);
    glVertex3f(-49, -26.2, 4); 
    glVertex3f(-49, -27, 4);
    
    glVertex3f(-50, -22.8, 4);
    glVertex3f(-50, -22, 4);
    glVertex3f(-49, -22, 4); 
    glVertex3f(-49, -22.8, 4);
    glEnd();
    
    //soporte de almohadas
    glBegin(GL_QUADS);
    glColor3f( 0.541 , 0.372 , 0.188 );//marron maso menos claro
    glVertex3f(-49.2, -26.2, 4.2);
    glVertex3f(-49.2, -22.8, 4.2);
    glVertex3f(-47, -22.8, 1.61); 
    glVertex3f(-47, -26.2, 1.61);
    
    glVertex3f(-47, -22.8, 1.61); 
    glVertex3f(-47, -26.2, 1.61);
    glVertex3f(-44, -26.2, 1.61); 
    glVertex3f(-44, -22.8, 1.61);
    
    glVertex3f(-44, -26.2, 1.61); 
    glVertex3f(-44, -22.8, 1.61);
    glVertex3f(-42, -22.8, 1.21); 
    glVertex3f(-42, -26.2, 1.21);
    glEnd();
    
    glLineWidth(2); 
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);//NEGRO
	glVertex3f(-49.2, -26.2, 4.2);
    glVertex3f(-49.2, -23, 4.2);
    glVertex3f(-47, -22.8, 1.61); 
    glVertex3f(-44, -22.8, 1.61);
    
    glVertex3f(-42, -22.8, 1.21);
    glVertex3f(-42, -26.2, 1.21);
    glVertex3f(-44, -26.2, 1.61); 
    glVertex3f(-47, -26.2, 1.61);
	glEnd();
	
	
	//ALMOHADAS 1
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);//BLANCO
    glVertex3f(-47, -26, 1.62); 
    glVertex3f(-47, -23, 1.62);
    glVertex3f(-47, -23, 2.0); 
    glVertex3f(-47, -26, 2.0);
    
    glVertex3f(-47, -23, 2.0); 
    glVertex3f(-47, -26, 2.0);
    glVertex3f(-44, -26, 2.0); 
    glVertex3f(-44, -23, 2.0);
    
    glVertex3f(-44, -26, 2.0); 
    glVertex3f(-44, -23, 2.0);
    glVertex3f(-44, -23, 1.62); 
    glVertex3f(-44, -26, 1.62);
    
    glVertex3f(-47, -26, 2.0); 
    glVertex3f(-44, -26, 2.0);
    glVertex3f(-44, -26, 1.62); 
    glVertex3f(-47, -26, 1.62);
    
    glVertex3f(-47, -23, 2.0); 
    glVertex3f(-44, -23, 2.0);
    glVertex3f(-44, -23, 1.62); 
    glVertex3f(-47, -23, 1.62);
    //AMOHADA 2
    glVertex3f(-47.18, -26, 1.9); 
    glVertex3f(-46.9, -26, 2.1);
    glVertex3f(-48.9, -26, 4.55); 
    glVertex3f(-49.25, -26, 4.3);
    
    glVertex3f(-47.18, -23, 1.9); 
    glVertex3f(-46.9, -23, 2.1);
    glVertex3f(-48.9, -23, 4.55); 
    glVertex3f(-49.25, -23, 4.3);
    
    glVertex3f(-48.9, -26, 4.55); 
    glVertex3f(-48.9, -23, 4.55);
    glVertex3f(-46.9, -23, 2.1); 
    glVertex3f(-46.9, -26, 2.1);
    
    glVertex3f(-49.25, -23, 4.3); 
    glVertex3f(-49.25, -26, 4.3);
    glVertex3f(-48.9, -26, 4.55); 
    glVertex3f(-48.9, -23, 4.55);
    
    glVertex3f(-47.18, -23, 1.9); 
    glVertex3f(-46.9, -23, 2.1);
    glVertex3f(-46.9, -26, 2.1); 
    glVertex3f(-47.18, -26, 1.9);
    
    glVertex3f(-47.18, -26, 1.9); 
    glVertex3f(-49.25, -26, 4.3);
    glVertex3f(-49.25, -23, 4.3); 
    glVertex3f(-47.18, -23, 1.9);
 	//ALMOHADAS 3
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);//BLANCO
    glVertex3f(-44, -23, 1.61); 
    glVertex3f(-43.85, -23, 2);
    glVertex3f(-43.85, -26, 2); 
    glVertex3f(-44, -26, 1.61);
    
    glVertex3f(-43.85, -23, 2);
    glVertex3f(-43.85, -26, 2); 
    glVertex3f(-41.80, -26, 1.55) ;
    glVertex3f(-41.80, -23, 1.55);
    
    glVertex3f(-41.80, -26, 1.55) ;
    glVertex3f(-41.80, -23, 1.55);
    glVertex3f(-42, -23, 1.21); 
    glVertex3f(-42, -26, 1.21);
    
    glVertex3f(-44, -26, 1.61); 
    glVertex3f(-43.85, -26, 2);
    glVertex3f(-41.80, -26, 1.55); 
    glVertex3f(-42, -26, 1.21);
    
    glVertex3f(-44, -23, 1.61); 
    glVertex3f(-43.85, -23, 2);
    glVertex3f(-41.80, -23, 1.55); 
    glVertex3f(-42, -23, 1.21);   
    
    glEnd();
	//delineado almohadas
	glLineWidth(1.5); 
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-43.85, -26, 2); 
    glVertex3f(-43.85, -23, 2);
    glVertex3f(-41.80, -23, 1.55); 
    glVertex3f(-41.80, -26, 1.55); 
	glEnd();
	
	glLineWidth(1.5); 
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-44, -26, 2); 
    glVertex3f(-44, -23, 2);
    glVertex3f(-47, -23, 2); 
    glVertex3f(-47, -26, 2); 
	glEnd();
	
	glLineWidth(1.5); 
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-46.9, -26, 2.1); 
    glVertex3f(-46.9, -23, 2.1);
    glVertex3f(-48.9, -23, 4.55); 
    glVertex3f(-48.9, -26, 4.55); 
	glEnd();
	
	// delineado en silla
	glLineWidth(2); 
	glBegin(GL_LINE_LOOP);

	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-50, -27, 1.6);
	glVertex3f(-50, -22, 1.6);
	glVertex3f(-44, -22, 1.6);
	glVertex3f(-44, -27, 1.6);
	glEnd();
	glLineWidth(2); 
	glBegin(GL_LINE_LOOP);
	glVertex3f(-50, -27, 1.21);
	glVertex3f(-50, -22, 1.21);
	glVertex3f(-44, -22, 1.21);
	glVertex3f(-44, -27, 1.21);
	glEnd();
	glLineWidth(2); 
	glBegin(GL_LINE_LOOP);
	glVertex3f(-50, -26.2, 3);
	glVertex3f(-49, -26.2, 3);
	glVertex3f(-49, -22.8, 3);
	glVertex3f(-50, -22.8, 3);
	glEnd();
	glLineWidth(2); 
	glBegin(GL_LINE_LOOP);
	glVertex3f(-50, -27, 4);
	glVertex3f(-49, -27, 4);
	glVertex3f(-49, -26.2, 4);
	glVertex3f(-50, -26.2, 4);
	glEnd();
	glLineWidth(2); 
	glBegin(GL_LINE_LOOP);
	glVertex3f(-50, -22.8, 4);
	glVertex3f(-50, -22, 4);
	glVertex3f(-49, -22, 4);
	glVertex3f(-49, -22.8, 4);
	glEnd();
	glLineWidth(2); 
	glBegin(GL_LINES);
	glVertex3f(-49, -26.2, 4);
	glVertex3f(-49, -26.2, 1.6);
	glVertex3f(-49, -26.2, 1.6);
	glVertex3f(-49, -27, 1.6);
	glVertex3f(-49, -27, 1.6);
	glVertex3f(-49, -27, 4);
	glVertex3f(-49, -22, 4);
	glVertex3f(-49, -22, 1.6);
	glVertex3f(-49, -22, 1.6);
	glVertex3f(-49, -22.8, 1.6);
	glVertex3f(-49, -22.8, 1.6);
	glVertex3f(-49, -22.8, 4);
	
	glVertex3f(-49, -22.8, 1.6);
	glVertex3f(-50, -22.8, 1.6);
	glVertex3f(-49, -26.2, 1.6);
	glVertex3f(-50, -26.2, 1.6);
	glVertex3f(-44, -22, 1.6);
	glVertex3f(-44, -22, 1.21);
	glVertex3f(-44, -27, 1.6);
	glVertex3f(-44, -27, 1.21);
	glVertex3f(-49, -26.2, 2.5);
	glVertex3f(-49, -22.8, 2.5);
	
	glVertex3f(-49, -27, 1.6);
	glVertex3f(-49, -26.2, 1.6);
	glVertex3f(-49, -22.8, 1.6);
	glVertex3f(-49, -22, 1.6);
	
	glEnd();
}

void silla2_piscina(){
glPushMatrix();
glTranslatef(0.0f, 9.0f, 0.0f);//TRASLADADO

silla1_piscina();

glEnd();
glPopMatrix();
glEnd();
}

void piscina(){


	//glColor3f( 0.607 , 0.886 ,  1.0 );//celeste
	//paredes interiores
	glBegin(GL_QUADS);
	glColor3f( 1.0 , 1.0 ,  1.0  );//celeste
	glVertex3f(-45, 25, 0.1);
    glVertex3f(-45, 25, -10);
    glVertex3f(-25, 25, -10); 
    glVertex3f(-25, 25, 0.1); 
    
    glVertex3f(-45, 25, 0.1);
    glVertex3f(-45, 25, -10);
    glVertex3f(-45, -12, -10); 
    glVertex3f(-45, -12, 0.1); 
    
    glVertex3f(-45, -12, 0.1);
    glVertex3f(-40, -12, 0.1);
    glVertex3f(-40, -12, -10); 
    glVertex3f(-45, -12, -10); 
    
    glVertex3f(-40, -12, 0.1);
    glVertex3f(-40, -19, 0.1);
    glVertex3f(-40, -19, -10); 
    glVertex3f(-40, -12, -10); 
    
    glVertex3f(-40, -19, 0.1);
    glVertex3f(-25, -19, 0.1);
    glVertex3f(-25, -19, -10); 
    glVertex3f(-40, -19, -10);
    
    glVertex3f(-25, -19, 0.1);
    glVertex3f(-25, 25, 0.1);
    glVertex3f(-25, 25, -10); 
    glVertex3f(-25, -19, -10);
    glEnd();
    //base
    glBegin(GL_POLYGON);
    glColor3f( 0.0 , 0.0 , 0.0 );//NEGRO
    glVertex3f(-45, 25, -10);
    glVertex3f(-25, 25, -10);
    glVertex3f(-25, -19, -10); 
    glVertex3f(-40, -19, -10);
    glVertex3f(-40, -12, -10);
    glVertex3f(-45, -12, -10);
    glEnd();
    //LINEAS
    glLineWidth(2); 
	glBegin(GL_LINES);
	glVertex3f(-40, -12, 0.1);
    glVertex3f(-40, -12, -10);
    glVertex3f(-40, -19, 0.1); 
    glVertex3f(-40, -19, -10);
    glVertex3f(-25, -19, 0.1);
    glVertex3f(-25, -19, -10);
    
    glVertex3f(-45, -12, 0.1);
    glVertex3f(-45, -12, -10);
    glVertex3f(-45, 25, 0.1); 
    glVertex3f(-45, 25, -10);
    glVertex3f(-25, 25, 0.1);
    glVertex3f(-25, 25, -10);
	glEnd();
	glLineWidth(2); 
	glBegin(GL_LINE_LOOP);
	glVertex3f(-25, 25, -10);
    glVertex3f(-25, -19, -10);
    glVertex3f(-40, -19, -10); 
    glVertex3f(-40, -12, -10);
    glVertex3f(-45, -12, -10);
    glVertex3f(-45, 25, -10);
	glEnd();
	glLineWidth(2); 
	glBegin(GL_LINE_LOOP);
	glVertex3f(-25, 25, 0.1);
    glVertex3f(-25, -19, 0.1);
    glVertex3f(-40, -19, 0.1); 
    glVertex3f(-40, -12, 0.1);
    glVertex3f(-45, -12, 0.1);
    glVertex3f(-45, 25, 0.1);
	glEnd();
	
	//agua transparente
	//probar luego para la transparencia
	//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	//GLfloat mat_diffuse[]={0.121f , 0.788f , 0.823f,0.5f};
	glBegin(GL_POLYGON);
	//glColor4f( 0.121 , 0.788 , 0.823 ,1.0);//CIAN CLARO
	glColor3f( 0.121 , 0.788 , 0.823 );//CIAN CLARO
    
    glVertex3f(-45, 25, 0.1);
    glVertex3f(-25, 25, 0.1);
    glVertex3f(-25, -19, 0.1); 
    glVertex3f(-40, -19, 0.1);
    glVertex3f(-40, -12, 0.1);
    glVertex3f(-45, -12, 0.1);
    glEnd();
  
}

void pasto(){	
	//pasto
    glBegin(GL_POLYGON);
    glColor3f( 0.364 , 0.529 , 0.090 );;//verde
    glVertex3f(55, -25, 0.1);
    glVertex3f(55, -55, 0.1);
    glVertex3f(-50, -55, 0.1); 
    glVertex3f(-50, -30, 0.1);
    glVertex3f(-40, -30, 0.1);
    glVertex3f(-40, -25, 0.1);
    glEnd();	
	//pasos
	glBegin(GL_QUADS);
    glColor3f( 0.423 , 0.474 , 0.505 );//blanco medio oscuro
    glVertex3f(-36, -29, 0.2);
    glVertex3f(-36, -26.5,  0.2);
    glVertex3f(-30, -26.5, 0.2); 
    glVertex3f(-30, -29,  0.2);
    
    glVertex3f(-36, -33,0.2); 
    glVertex3f(-36, -30.5,  0.2);
    glVertex3f(-30, -30.5, 0.2);
    glVertex3f(-30, -33, 0.2);
    //grosor
    glVertex3f(-36, -29, 0.7);
    glVertex3f(-36, -26.5,  0.7);
    glVertex3f(-30, -26.5, 0.7); 
    glVertex3f(-30, -29,  0.7);
    
    glVertex3f(-36, -33,0.7); 
    glVertex3f(-36, -30.5,  0.7);
    glVertex3f(-30, -30.5, 0.7);
    glVertex3f(-30, -33, 0.7);
    
    //lados
    //paso 2
    glVertex3f(-36, -33, 0.2);
    glVertex3f(-30, -33, 0.2);
    glVertex3f(-30, -33, 0.7); 
    glVertex3f(-36, -33, 0.7);
    
    glVertex3f(-36, -30.5, 0.2);
    glVertex3f(-30, -30.5, 0.2);
    glVertex3f(-30, -30.5, 0.7); 
    glVertex3f(-36, -30.5, 0.7);
    
    glVertex3f(-36, -33, 0.2);
    glVertex3f(-36, -30.5, 0.2);
    glVertex3f(-36, -30.5, 0.7); 
    glVertex3f(-36, -33, 0.7);
    
    glVertex3f(-30, -33, 0.2);
    glVertex3f(-30, -30.5, 0.2);
    glVertex3f(-30, -30.5, 0.7); 
    glVertex3f(-30, -33, 0.7);
    //paso 1
    glVertex3f(-36, -29, 0.2);
    glVertex3f(-30, -29, 0.2);
    glVertex3f(-30, -29, 0.7); 
    glVertex3f(-36, -29, 0.7);
    
    glVertex3f(-36, -26.5, 0.2);
    glVertex3f(-30, -26.5, 0.2);
    glVertex3f(-30, -26.5, 0.7); 
    glVertex3f(-36, -26.5, 0.7);
    
    glVertex3f(-36, -29, 0.2);
    glVertex3f(-36, -26.5, 0.2);
    glVertex3f(-36, -26.5, 0.7); 
    glVertex3f(-36, -29, 0.7);
    
    glVertex3f(-30, -29, 0.2);
    glVertex3f(-30, -26.5, 0.2);
    glVertex3f(-30, -26.5, 0.7); 
    glVertex3f(-30, -29, 0.7);
    glEnd();
    //lineas
    glLineWidth(1.0);
	glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );//negro
    glVertex3f(-36, -29, 0.7);
    glVertex3f(-36, -26.5,  0.7);
    glVertex3f(-30, -26.5, 0.7); 
    glVertex3f(-30, -29,  0.7);
    glEnd();
    
    glLineWidth(1.0);
	glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );//negro
    glVertex3f(-36, -33,0.7); 
    glVertex3f(-36, -30.5,  0.7);
    glVertex3f(-30, -30.5, 0.7);
    glVertex3f(-30, -33, 0.7);
    glEnd();
}

void base(){
	//base
	glBegin(GL_QUADS);
    glColor3f( 1.0 , 1.0 , 1.0 );;//blanco
    glVertex3f(-50, -55, 3);
    glVertex3f(-50, -35, 3);
    glVertex3f(-36, -35, 3); 
    glVertex3f(-36, -55, 3);
    
    glVertex3f(-36, -55, 3);
    glVertex3f(-36, -41, 3);
    glVertex3f(-30, -41, 3); 
    glVertex3f(-30, -55, 3); 
    
    glVertex3f(-30, -55, 3);
    glVertex3f(-30, -35, 3);
    glVertex3f(-5, -35, 3); 
    glVertex3f(-5, -55, 3);
    //COSTADOS
    glVertex3f(-5, -55, 0.2);
    glVertex3f(-5, -55, 3.0);
    glVertex3f(-5, -35, 3.0); 
    glVertex3f(-5, -35, 0.2); 
    
    glVertex3f(-5, -35, 0.2);
    glVertex3f(-5, -35,  3.0);
    glVertex3f(-30, -35, 3.0); 
    glVertex3f(-30, -35,  0.2);
    
    glVertex3f(-36, -35,  0.2);
    glVertex3f(-36, -35, 3.0);
    glVertex3f(-50, -35, 3.0); 
    glVertex3f(-50, -35,  0.2);
    glEnd();
    //costado de escalera
    glBegin(GL_POLYGON);
    glColor3f( 1.0 , 1.0 , 1.0 );;//blanco
	glVertex3f(-36, -38, 2.0);
    glVertex3f(-36, -41, 2.0);
    glVertex3f(-36, -41, 3.0); 
    glVertex3f(-36, -35, 3.0);
	glVertex3f(-36, -35, 1.0);
	glVertex3f(-36, -38, 1.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 1.0 , 1.0 , 1.0 );;//blanco
	glVertex3f(-30, -38, 2.0);
    glVertex3f(-30, -41, 2.0);
    glVertex3f(-30, -41, 3.0); 
    glVertex3f(-30, -35, 3.0);
	glVertex3f(-30, -35, 1.0);
	glVertex3f(-30, -38, 1.0);
	glEnd();
	//-------------------------------------------------
	//escalera
	glBegin(GL_QUADS);
	glColor3f( 1.0 , 1.0 , 1.0 );;//blanco
	glVertex3f(-30, -38, 1);
    glVertex3f(-36, -38, 1);
    glVertex3f(-36, -35, 1); 
    glVertex3f(-30, -35, 1);
    
    glVertex3f(-36, -35, 1); 
    glVertex3f(-30, -35, 1);
    glVertex3f(-30, -35, 0.2); 
    glVertex3f(-36, -35, 0.2);
    
    glVertex3f(-30, -38, 1);
    glVertex3f(-36, -38, 1);
    glVertex3f(-36, -38, 2); 
    glVertex3f(-30, -38, 2);
    
    glVertex3f(-36, -38, 2); 
    glVertex3f(-30, -38, 2);
    glVertex3f(-30, -41, 2); 
    glVertex3f(-36, -41, 2);
    
    glVertex3f(-30, -41, 2); 
    glVertex3f(-36, -41, 2);
    glVertex3f(-36, -41, 3); 
    glVertex3f(-30, -41, 3);
    glEnd();
	//GROSOR MADERA EN LOS PASOS
	glBegin(GL_QUADS);
	glColor3f( 0.341 , 0.278 , 0.235 );//marron OSCURO
	//PASO 1
	glVertex3f(-30, -38, 1.3);
    glVertex3f(-36, -38, 1.3);
    glVertex3f(-36, -35, 1.3); 
    glVertex3f(-30, -35, 1.3);
    //PASO 2 
    glVertex3f(-36, -38, 2.3); 
    glVertex3f(-30, -38, 2.3);
    glVertex3f(-30, -41, 2.3); 
    glVertex3f(-36, -41, 2.3);
    
	glEnd();
	
	//COSTADOS
	glBegin(GL_QUADS);
	glColor3f( 0.341 , 0.278 , 0.235 );//marron OSCURO
	//PASO 1
	glVertex3f(-30, -35, 1);
	glVertex3f(-30, -35, 1.3);
	glVertex3f(-36, -35, 1.3);
    glVertex3f(-36, -35, 1);
    //PASO 2 
    glVertex3f(-30, -38, 2);
    glVertex3f(-30, -38, 2.3);
    glVertex3f(-36, -38,  2.3);
    glVertex3f(-36, -38, 2);
    
	glEnd();
	
	//DELINEADO
	//PASO 1
	glLineWidth(1.5);
	glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );//negro
    glVertex3f(-30, -38, 1.3);
    glVertex3f(-36, -38, 1.3);
    glVertex3f(-36, -35, 1.3); 
    glVertex3f(-30, -35, 1.3);
    glEnd();
    //PASO 2
    glLineWidth(1.5);
	glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );//negro
    glVertex3f(-36, -38, 2.3); 
    glVertex3f(-30, -38, 2.3);
    glVertex3f(-30, -41, 2.3); 
    glVertex3f(-36, -41, 2.3);
    glEnd();
     //base de madera todo el piso
    glBegin(GL_QUADS);
	glColor3f( 0.341 , 0.278 , 0.235 );//marron OSCURO
   
    glVertex3f(-50, -55, 3.01);
    glVertex3f(-50, -34, 3.01);
    glVertex3f(-36, -34, 3.01); 
    glVertex3f(-36, -55, 3.01);
    
    glVertex3f(-36, -55, 3.01);
    glVertex3f(-36, -41, 3.01);
    glVertex3f(-30, -41, 3.01); 
    glVertex3f(-30, -55, 3.01); 
    
    glVertex3f(-30, -55, 3.01);
    glVertex3f(-30, -34, 3.01);
    glVertex3f(-4, -34, 3.01); 
    glVertex3f(-4, -55, 3.01);
    //grosor
    glVertex3f(-50, -55, 3.7);
    glVertex3f(-50, -34, 3.7);
    glVertex3f(-36, -34, 3.7); 
    glVertex3f(-36, -55, 3.7);
    
    glVertex3f(-36, -55, 3.7);
    glVertex3f(-36, -41, 3.7);
    glVertex3f(-30, -41, 3.7); 
    glVertex3f(-30, -55, 3.7); 
    
    glVertex3f(-30, -55, 3.7);
    glVertex3f(-30, -34, 3.7);
    glVertex3f(-4, -34, 3.7); //
    glVertex3f(-4, -55, 3.7);//
    //costados
    glVertex3f(-4, -55, 3.01);
    glVertex3f(-4, -34, 3.01);
    glVertex3f(-4, -34, 3.7); 
    glVertex3f(-4, -55, 3.7);
    
    glVertex3f(-4, -34,  3.01);
    glVertex3f(-30, -34, 3.01);
    glVertex3f(-30, -34, 3.7); 
    glVertex3f(-4, -34, 3.7); 
    
    glVertex3f(-36, -34,  3.01);
    glVertex3f(-50, -34,  3.01);
    glVertex3f(-50, -34,  3.7); 
    glVertex3f(-36, -34,  3.7);
    
    //dentro de la escalera
    glVertex3f(-36, -35,  3.01);
    glVertex3f(-36, -41, 3.01);
    glVertex3f(-36, -41, 3.7); 
    glVertex3f(-36, -35, 3.7); 
    
    glVertex3f(-36, -41,   3.01);
    glVertex3f(-30, -41,  3.01);
    glVertex3f(-30, -41,  3.7); 
    glVertex3f(-36, -41,   3.7);
    
    glVertex3f(-30, -41,  3.01);
    glVertex3f(-30, -34,  3.01);
    glVertex3f(-30, -34,  3.7); 
    glVertex3f(-30, -41,  3.7);
    
    glEnd();
    //lineas de base
    glLineWidth(1.5);
	glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );//negro
    glVertex3f(-4, -55, 3.7); 
    glVertex3f(-4, -34, 3.7);
    glVertex3f(-30, -34, 3.7); 
    glVertex3f(-30, -41, 3.7);
    
    glVertex3f(-36, -41,  3.7); 
    glVertex3f(-36, -34, 3.7);
    glVertex3f(-50, -34, 3.7); 
    glVertex3f(-50, -55 ,3.7);
    glEnd();
    
    glLineWidth(1.5);
	glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );//negro
    glVertex3f(-30, -41, 3.01); 
    glVertex3f(-35.98, -41, 3.01);
    glVertex3f(-35.98, -41, 2.3); 
    glVertex3f(-35.98, -38, 2.3);
    
    glVertex3f(-35.98, -38, 1.3); 
    glVertex3f(-35.98, -35, 1.3);
    glVertex3f(-30.02, -35, 1.3); 
    glVertex3f(-30.02, -38, 1.3);
    
    glVertex3f(-30.02, -38, 2.3); 
    glVertex3f(-30.02, -40.98, 2.3);
    
    glEnd();
    
 
    
    glEnd();
}

void techo(){
	glBegin(GL_QUADS);
	//columnas
	//cara delantera
    glColor3f( 0.1 , 0.1 , 0.1 );//negro
    glVertex3f(-5, -35, 18);
    glVertex3f(-7, -35, 18);
    glVertex3f(-7, -35, 3.7); 
    glVertex3f(-5, -35, 3.7);
    //cara trasera
    
    glVertex3f(-5, -37, 18);
    glVertex3f(-7, -37, 18);
    glVertex3f(-7, -37, 3.7); 
    glVertex3f(-5, -37, 3.7);
    //cara derecha
    
    glVertex3f(-7, -35, 18);
    glVertex3f(-7, -37, 18);
    glVertex3f(-7, -37, 3.7); 
    glVertex3f(-7, -35, 3.7);
    //cara izquierda
    
    glVertex3f(-5, -37, 18);
    glVertex3f(-5, -35, 18);
    glVertex3f(-5, -35, 3.7); 
    glVertex3f(-5, -37, 3.7);
    glBegin(GL_QUADS);
    
    //viga costado
    //cara arriba
    glVertex3f(-5, -35, 20);
    glVertex3f(-5, -55, 20);
    glVertex3f(-7, -55, 20); 
    glVertex3f(-7, -35, 20);
    //cara abajo
    
    glVertex3f(-5, -35, 18);
    glVertex3f(-5, -55, 18);
    glVertex3f(-7, -55, 18); 
    glVertex3f(-7, -35, 18);
    //cara derecha
    
    glVertex3f(-7, -35, 20);
    glVertex3f(-7, -55, 20);
    glVertex3f(-7, -55, 18); 
    glVertex3f(-7, -35, 18);
    //cara izquierda
    
    glVertex3f(-5, -55, 20);
    glVertex3f(-5, -55, 18);
    glVertex3f(-5, -35, 18); 
    glVertex3f(-5, -35, 20);
    
    //enfrente
    glVertex3f(-7, -35, 18);
    glVertex3f(-7, -35, 20);
    glVertex3f(-5, -35, 20); 
    glVertex3f(-5, -35, 18);
    
    //viga larga
    //cara arriba
    glVertex3f(-7, -37, 20);
    glVertex3f(-7, -35, 20);
    glVertex3f(-50, -37, 20); 
    glVertex3f(-50, -35, 20);
    //cara abajo
    
    glVertex3f(-7, -37, 18);
    glVertex3f(-7, -35, 18);
    glVertex3f(-50, -35, 18); 
    glVertex3f(-50, -37, 18);
    //cara derecha
    
    glVertex3f(-7, -37, 20);
    glVertex3f(-7, -37, 18);
    glVertex3f(-50, -37, 18); 
    glVertex3f(-50, -37, 20);
    //cara izquierda
    
    glVertex3f(-7, -35, 18);
    glVertex3f(-7, -35, 20);
    glVertex3f(-50, -35, 20); 
    glVertex3f(-50, -35, 18);
    glEnd();
    
    //viga del fondo por la parrilla 
    glPushMatrix();
	glTranslatef(-41, 0.0f, 0.0f);//TRASLADADO
	glBegin(GL_QUADS);
	//viga costado
    //cara arriba
    glVertex3f(-5, -35, 20);
    glVertex3f(-5, -55, 20);
    glVertex3f(-7, -55, 20); 
    glVertex3f(-7, -35, 20);
    //cara abajo
    
    glVertex3f(-5, -35, 18);
    glVertex3f(-5, -55, 18);
    glVertex3f(-7, -55, 18); 
    glVertex3f(-7, -35, 18);
    //cara derecha
    
    glVertex3f(-7, -35, 20);
    glVertex3f(-7, -55, 20);
    glVertex3f(-7, -55, 18); 
    glVertex3f(-7, -35, 18);
    //cara izquierda
    
    glVertex3f(-5, -55, 20);
    glVertex3f(-5, -55, 18);
    glVertex3f(-5, -35, 18); 
    glVertex3f(-5, -35, 20);
    
    //enfrente
    glVertex3f(-7, -35, 18);
    glVertex3f(-7, -35, 20);
    glVertex3f(-5, -35, 20); 
    glVertex3f(-5, -35, 18);
    glEnd();
    glPopMatrix();
    //repeticion de vigas cortas
    
    double a=-7.0;
    for(int i=0;i<4;i++){
	
    glPushMatrix();
	glTranslatef(a, 0.0f, 0.0f);//TRASLADADO
	glBegin(GL_QUADS);
	//viga costado
    //cara arriba
    glVertex3f(-5, -35, 20);
    glVertex3f(-5, -55, 20);
    glVertex3f(-7, -55, 20); 
    glVertex3f(-7, -35, 20);
    //cara abajo
    
    glVertex3f(-5, -35, 18);
    glVertex3f(-5, -55, 18);
    glVertex3f(-7, -55, 18); 
    glVertex3f(-7, -35, 18);
    //cara derecha
    
    glVertex3f(-7, -35, 20);
    glVertex3f(-7, -55, 20);
    glVertex3f(-7, -55, 18); 
    glVertex3f(-7, -35, 18);
    //cara izquierda
    
    glVertex3f(-5, -55, 20);
    glVertex3f(-5, -55, 18);
    glVertex3f(-5, -35, 18); 
    glVertex3f(-5, -35, 20);
    
    //enfrente
    glVertex3f(-7, -35, 18);
    glVertex3f(-7, -35, 20);
    glVertex3f(-5, -35, 20); 
    glVertex3f(-5, -35, 18);
    glEnd();
    glPopMatrix();
    
    a=a-7;
    }
    
	//techo
    glBegin(GL_QUADS);
    glColor3f( 1.0 , 1.0 , 1.0 );//blanco
	//viga costado
    //cara arriba
    glVertex3f(-5, -55, 20.01);
    glVertex3f(-5, -35, 20.01);
    glVertex3f(-36, -35, 20.01);
    glVertex3f(-36, -55, 20.01); 
    
    //cara abajo
    
    glVertex3f(-36, -35, 20.01);
    glVertex3f(-36, -51, 20.01);
    glVertex3f(-45, -51, 20.01); 
    glVertex3f(-45, -35, 20.01);
    //cara derecha
    
    glVertex3f(-45, -35, 20.01);
    glVertex3f(-45, -55, 20.01);
    glVertex3f(-50, -55, 20.01); 
    glVertex3f(-50, -35, 20.01);
    glEnd();
    
    glBegin(GL_QUADS);
    glVertex3f(-4, -33, 20.01);
    glVertex3f(-4, -55, 20.01);
    glVertex3f(-50, -55, 20.01); 
    glVertex3f(-50, -33, 20.01);
    glEnd();
    //LINEAS NEGRO PARED
    
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );//NEGRO
    glVertex3f(-4, -33, 20.01);
    glVertex3f(-4, -55, 20.01);
    glVertex3f(-50, -55, 20.01); 
    glVertex3f(-50, -33, 20.01);
    glEnd();
    
}

void parrilla(){
	
	glBegin(GL_QUADS);
	//cajon izquierdo
	//cara izquierda
    glColor3f( 0.337 , 0.227 , 0.172 );//marron
    glVertex3f(-32, -55, 8);
    glVertex3f(-32, -51, 8);
    glVertex3f(-32, -51, 5); 
    glVertex3f(-32, -55, 5);
    //encima
    glVertex3f(-32, -55, 8);
    glVertex3f(-36, -55, 8);
    glVertex3f(-36, -51, 8); 
    glVertex3f(-32, -51, 8);
    //defrente
    glVertex3f(-32, -51, 8);
    glVertex3f(-32, -51, 5);
    glVertex3f(-36, -51, 5); 
    glVertex3f(-36, -51, 8);
    //abajo
    glVertex3f(-32, -55, 5);
    glVertex3f(-32, -51, 5);
    glVertex3f(-36, -51, 5); 
    glVertex3f(-36, -55, 5);
    //cajon derecho chico
    //encima
    glVertex3f(-45, -55, 8);
    glVertex3f(-50, -55, 8);
    glVertex3f(-50, -51, 8); 
    glVertex3f(-45, -51, 8);
    //defrente
    glVertex3f(-45, -51, 8);
    glVertex3f(-46, -51, 8);
    glVertex3f(-46, -51, 5); 
    glVertex3f(-45, -51, 5);
    //cajon derecho grande
    //encima
    glVertex3f(-46, -51, 8);
    glVertex3f(-50, -51, 8);
    glVertex3f(-50, -35, 8); 
    glVertex3f(-46, -35, 8);
    //defrente
    glVertex3f(-46, -51, 5);
    glVertex3f(-46, -51, 8);
    glVertex3f(-46, -35, 8); 
    glVertex3f(-46, -35, 5);
    //derecha
    glVertex3f(-46, -35, 8);
    glVertex3f(-50, -35, 8);
    glVertex3f(-50, -35, 5); 
    glVertex3f(-46, -35, 5);
    glColor3f( 0.5 , 0.5 , 0.5 );//plomo
    //Parte del parrillero
    //izq
    //izquierdo
    glVertex3f(-36, -55, 8);
    glVertex3f(-36, -55, 9);
    glVertex3f(-36, -51, 9); 
    glVertex3f(-36, -51, 8);
    //encima
    glVertex3f(-36, -55, 9);
    glVertex3f(-36, -51, 9);
    glVertex3f(-37, -51, 9); 
    glVertex3f(-37, -55, 9);
    //drecho
    glVertex3f(-37, -51, 9); 
    glVertex3f(-37, -55, 9);
    glVertex3f(-37, -55, 6); 
    glVertex3f(-37, -51, 6);
    //defrente
    glVertex3f(-37, -51, 6); 
    glVertex3f(-36, -51, 6);
    glVertex3f(-36, -51, 9); 
    glVertex3f(-37, -51, 9);
    //derec
    //drecho
    glVertex3f(-45, -55, 8);
    glVertex3f(-45, -55, 9);
    glVertex3f(-45, -51, 9); 
    glVertex3f(-45, -51, 8);
    //encima
    glVertex3f(-45, -55, 9);
    glVertex3f(-45, -51, 9);
    glVertex3f(-44, -51, 9); 
    glVertex3f(-44, -55, 9);
    //izquierdo
    glVertex3f(-44, -51, 9); 
    glVertex3f(-44, -55, 9);
    glVertex3f(-44, -55, 6); 
    glVertex3f(-44, -51, 6);
    //defrente
    glVertex3f(-44, -51, 6); 
    glVertex3f(-45, -51, 6);
    glVertex3f(-45, -51, 9); 
    glVertex3f(-44, -51, 9);
    //base
    glVertex3f(-36, -55, 6); 
    glVertex3f(-45, -55, 6);
    glVertex3f(-45, -51, 6); 
    glVertex3f(-36, -51, 6);
    
    glVertex3f(-36, -51, 6); 
    glVertex3f(-36, -51, 5);
    glVertex3f(-45, -51, 5); 
    glVertex3f(-45, -51, 6);
    //plancha de freir
    glColor3f( 0.0 , 0.0 , 0.0 );//negro
    glVertex3f(-37, -55, 7.8); 
    glVertex3f(-37, -51, 7.8);
    glVertex3f(-44, -51, 7.8); 
    glVertex3f(-44, -55, 7.8);
    
    glVertex3f(-37, -55, 7.6); 
    glVertex3f(-37, -51, 7.6);
    glVertex3f(-44, -51, 7.6); 
    glVertex3f(-44, -55, 7.6);
    
    glVertex3f(-37, -51, 7.8); 
    glVertex3f(-44, -51, 7.8);
    glVertex3f(-44, -51, 7.6); 
    glVertex3f(-37, -51, 7.6);
    
    //hueco por donde saldra el humo
    glColor3f( 0.5 , 0.5 , 0.5 );//plmo
    //izqu
    glVertex3f(-36, -55, 15); 
    glVertex3f(-36, -51, 15);
    glVertex3f(-36, -51, 20); 
    glVertex3f(-36, -55, 20);
    //dfrente
    glVertex3f(-36, -51, 15);
    glVertex3f(-36, -51, 20); 
    glVertex3f(-45, -51, 20); 
    glVertex3f(-45, -51, 15);
    //derecha
    glVertex3f(-45, -51, 20); 
    glVertex3f(-45, -51, 15);
    glVertex3f(-45, -55, 15); 
    glVertex3f(-45, -55, 20);
    glEnd();
    
    //-----------------------lineas detallado
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0, 0.0 );//NEGRO
    glVertex3f(-12, -52, 8); 
    glVertex3f(-12, -53, 8);
    glVertex3f(-7, -53, 8); 
    glVertex3f(-7, -38, 8);
    
    glVertex3f(-12, -38, 8); 
    glVertex3f(-12, -39, 8);
    glVertex3f(-8, -39, 8); 
    glVertex3f(-8, -52, 8);
    glEnd();
    
    //-------------------------zona por donde sale el humo
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0, 0.0 );//NEGRO
    
    glVertex3f(-36, -51, 20); 
    glVertex3f(-45, -51, 20);
    glVertex3f(-45, -51, 15); 
    glVertex3f(-36, -51, 15);
    
    glEnd();
    //-------------------------mueble derecho a la parrilla
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0, 0.0 );//NEGRO
    
    glVertex3f(-45, -51, 8); 
    glVertex3f(-45, -55, 8);
    glVertex3f(-50, -55, 8); 
    glVertex3f(-50, -35, 8);
    
    glVertex3f(-46, -35, 8); 
    glVertex3f(-46, -51, 8);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0, 0.0 );//NEGRO
    
    glVertex3f(-45, -51, 5); 
    glVertex3f(-45, -55, 5);
    glVertex3f(-50, -55, 5); 
    glVertex3f(-50, -35, 5);
    
    glVertex3f(-46, -35, 5); 
    glVertex3f(-46, -51, 5);
    glEnd();
    
    //-------------------------mueble izquierdo de la parrilla
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0, 0.0 );//NEGRO
    
    glVertex3f(-32, -55, 8); 
    glVertex3f(-36, -55, 8);
    glVertex3f(-36, -51, 8); 
    glVertex3f(-36, -51, 5);
    
    glVertex3f(-32, -51, 5); 
    glVertex3f(-32, -51, 8);
    glVertex3f(-36, -51, 8); 
    glVertex3f(-36, -51, 5);
    glEnd();
    
    //------------------------- parrilla
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0, 0.0 );//NEGRO
    
    glVertex3f(-36, -51, 9); 
    glVertex3f(-36, -55, 9);
    glVertex3f(-37, -55, 9); 
    glVertex3f(-37, -51, 9);
    
    glVertex3f(-37, -51, 6); 
    glVertex3f(-44, -51, 6);
    glVertex3f(-44, -51, 9); 
    glVertex3f(-44, -55, 9);
    
    glVertex3f(-45, -55, 9); 
    glVertex3f(-45, -51, 9);
    glVertex3f(-45, -51, 5); 
    glVertex3f(-36, -51, 5);
    glEnd();
    
    glBegin(GL_LINES);
    glColor3f( 0.0 , 0.0, 0.0 );//NEGRO
    
    glVertex3f(-32, -51, 8); 
    glVertex3f(-36, -51, 8);
    glVertex3f(-32, -55, 8); 
    glVertex3f(-32, -55, 5);
    
    glVertex3f(-36, -51, 9); 
    glVertex3f(-37, -51, 9);
    glVertex3f(-44, -51, 9); 
    glVertex3f(-45, -51, 9);
    
    glVertex3f(-44, -55, 6); 
    glVertex3f(-44, -55, 9);
    glVertex3f(-37, -55, 6); 
    glVertex3f(-37, -55, 9);
    
    glVertex3f(-36, -55, 8); 
    glVertex3f(-36, -55, 9);
    glVertex3f(-36, -51, 9); 
    glVertex3f(-36, -51, 8);
    
    glVertex3f(-45, -55, 9); 
    glVertex3f(-45, -55, 8);
    glVertex3f(-45, -51, 8); 
    glVertex3f(-45, -51, 9);
    
    glVertex3f(-37, -55, 6); 
    glVertex3f(-44, -55, 6);
    
    glVertex3f(-37, -51, 6); 
    glVertex3f(-44, -51, 6);
    glVertex3f(-46, -35, 5); 
    glVertex3f(-46, -35, 8);
    
    glVertex3f(-50, -35, 5); 
    glVertex3f(-50, -35, 8);
    glEnd();
    
    //----------------------CAJONES
    glBegin(GL_QUADS);
    glColor3f( 0.768 , 0.517 , 0.345 );
    glVertex3f(-32.5, -50.98, 7.5); 
    glVertex3f(-35.5, -50.98, 7.5);
    glVertex3f(-35.5, -50.98, 5.5); 
    glVertex3f(-32.5, -50.98, 5.5);
    
    glVertex3f(-45.98, -50.5, 5.5); 
    glVertex3f(-45.98, -50.5, 7.5);
    glVertex3f(-45.98, -44, 7.5); 
    glVertex3f(-45.98, -44, 5.5);
    
    glVertex3f(-45.98, -43, 5.5); 
    glVertex3f(-45.98, -43, 7.5);
    glVertex3f(-45.98, -35.5, 7.5); 
    glVertex3f(-45.98, -35.5, 5.5);
    glEnd();
    //-----------------------LINEAS
    
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0, 0.0 );//NEGRO
    glVertex3f(-32.5, -50.98, 7.5); 
    glVertex3f(-35.5, -50.98, 7.5);
    glVertex3f(-35.5, -50.98, 5.5); 
    glVertex3f(-32.5, -50.98, 5.5);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex3f(-45.98, -50.5, 5.5); 
    glVertex3f(-45.98, -50.5, 7.5);
    glVertex3f(-45.98, -44, 7.5); 
    glVertex3f(-45.98, -44, 5.5);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex3f(-45.98, -43, 5.5); 
    glVertex3f(-45.98, -43, 7.5);
    glVertex3f(-45.98, -35.5, 7.5); 
    glVertex3f(-45.98, -35.5, 5.5);
    glEnd();
    
    glBegin(GL_LINES);
    glColor3f( 0.0 , 0.0, 0.0 );//NEGRO
    glVertex3f(-45.98, -47, 7.5); 
    glVertex3f(-45.98, -47, 5.5);
    glVertex3f(-45.98, -39.5, 7.5); 
    glVertex3f(-45.98, -39.5, 5.5);
    glEnd();
}

void sillon_chico(){
	//------------------------------------sillon chico----------------------------------
    
    glBegin(GL_QUADS);
	//cara izquierda
    glColor3f( 0.415 , 0.415 , 0.415 );;//plmo 
    glVertex3f(-27, -50, 3.7);
    glVertex3f(-27, -50, 8);
    glVertex3f(-22, -50, 8); 
    glVertex3f(-22, -50, 3.7);
    //cara derecha
    glVertex3f(-27, -42, 3.7);
    glVertex3f(-27, -42, 8);
    glVertex3f(-22, -42, 8); 
    glVertex3f(-22, -42, 3.7);
    //cara trasera
    glVertex3f(-27, -50, 3.7);
    glVertex3f(-27, -50, 8);
    glVertex3f(-27, -42, 8); 
    glVertex3f(-27, -42, 3.7);
    //encima
    glVertex3f(-22, -49, 8);
    glVertex3f(-26, -49, 8);
    glVertex3f(-27, -50, 8); 
    glVertex3f(-22, -50, 8);
    
    glVertex3f(-26, -49, 8);
    glVertex3f(-27, -50, 8);
    glVertex3f(-27, -42, 8); 
    glVertex3f(-26, -43, 8);
    
    glVertex3f(-27, -42, 8); 
    glVertex3f(-26, -43, 8);
    glVertex3f(-22, -43, 8); 
    glVertex3f(-22, -42, 8);
    //enfrente
    glVertex3f(-22, -50, 8);
    glVertex3f(-22, -49, 8);
    glVertex3f(-22, -49, 4.5); 
    glVertex3f(-22, -50,  3.7);
    
    glVertex3f(-22, -49, 4.5); 
    glVertex3f(-22, -50,  3.7);
    glVertex3f(-22, -42,  3.7); 
    glVertex3f(-22, -43, 4.5);
    
    glVertex3f(-22, -42,  3.7); 
    glVertex3f(-22, -43, 4.5);
    glVertex3f(-22, -43, 8); 
    glVertex3f(-22, -42, 8);
    //cara izquierda dentro
    glVertex3f(-22, -49, 8); 
    glVertex3f(-26, -49, 8);
    glVertex3f(-26, -49, 4.5); 
    glVertex3f(-22, -49, 4.5);
    //cara derecha dentro
    glVertex3f(-22, -43, 8); 
    glVertex3f(-26, -43, 8);
    glVertex3f(-26, -43, 4.5); 
    glVertex3f(-22, -43, 4.5);
    //----------------cojin grande
    glColor3f( 0.827 , 0.811 , 0.768 );//beige
    //arriba
    glVertex3f(-22, -49, 6); 
    glVertex3f(-26, -49, 6);
    glVertex3f(-26, -43, 6); 
    glVertex3f(-22, -43, 6);
    //enfrente
    glVertex3f(-22, -49, 6); 
    glVertex3f(-22, -49, 4.5);
    glVertex3f(-22, -43, 4.5); 
    glVertex3f(-22, -43, 6);
    //--------------cojin pequeño
    //arriba
    glVertex3f(-25, -49, 9); 
    glVertex3f(-26, -49, 9);
    glVertex3f(-26, -43, 9); 
    glVertex3f(-25, -43, 9);
    //enfrente
    glVertex3f(-25, -49, 9); 
    glVertex3f(-25, -49, 6);
    glVertex3f(-25, -43, 6); 
    glVertex3f(-25, -43, 9);
    //izquierdo
    glVertex3f(-25, -49, 9); 
    glVertex3f(-25, -49, 6);
    glVertex3f(-26, -49, 6); 
    glVertex3f(-26, -49,  9);
    //derecho
    glVertex3f(-25, -43, 6); 
    glVertex3f(-25, -43, 9);
    glVertex3f(-26, -43, 9); 
    glVertex3f(-26, -43, 6);
    //atras
    glVertex3f(-26, -43, 9); 
    glVertex3f(-26, -49, 9);
    glVertex3f(-26, -49, 6); 
    glVertex3f(-26, -43, 6);
    
    
    glEnd();
    //------------------LINEAS PARA DETALLADO
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0, 0.0 );//NEGRO
    glVertex3f(-27, -50, 8); 
    glVertex3f(-27, -42, 8);
    glVertex3f(-22, -42, 8); 
    glVertex3f(-22, -43, 8);
    
    glVertex3f(-26, -43, 8); 
    glVertex3f(-26, -49, 8);
    glVertex3f(-22, -49, 8); 
    glVertex3f(-22, -50, 8);
    
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3f(-22, -49, 8); 
    glVertex3f(-22, -50, 8);
    glVertex3f(-22, -50, 3.7); 
    glVertex3f(-22, -42, 3.7);
    
    glVertex3f(-22, -42, 8); 
    glVertex3f(-22, -43, 8);
    glVertex3f(-22, -43, 4.5); 
    glVertex3f(-22, -49, 4.5);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3f(-22, -49, 6); 
    glVertex3f(-22, -43, 6);
    glVertex3f(-26, -43, 6); 
    glVertex3f(-26, -43, 9);
    
    glVertex3f(-26, -49, 9); 
    glVertex3f(-25, -49, 9);
    glVertex3f(-25, -43, 9); 
    glVertex3f(-25, -43, 6);
    
    glVertex3f(-25, -49, 6); 
    glEnd();
    glBegin(GL_LINES);
    
    glVertex3f(-27, -42, 8); 
    glVertex3f(-27, -42, 3.7);
    glVertex3f(-27, -50, 8); 
    glVertex3f(-27, -50, 3.7);
    
    glVertex3f(-25, -49, 9); 
    glVertex3f(-25, -48.99, 6);
    glVertex3f(-26, -48.97, 6); 
    glVertex3f(-22, -48.97, 6);
    
    glEnd();
}

void muebles(){
	glBegin(GL_QUADS);
	//cajon izquierdo
	//cara izquierda
    glColor3f( 0.415 , 0.415 , 0.415 );;//plmo 
    glVertex3f(-7, -38, 8);
    glVertex3f(-12, -38, 8);
    glVertex3f(-12, -38, 3.7); 
    glVertex3f(-7, -38, 3.7);
    //cara derecha
    
    glVertex3f(-7, -53, 8);
    glVertex3f(-12, -53, 8);
    glVertex3f(-12, -53, 3.7); 
    glVertex3f(-7, -53, 3.7);
    //cara trasera
    
    glVertex3f(-7, -38, 3.7);
    glVertex3f(-7, -38, 8);
    glVertex3f(-7, -53, 8); 
    glVertex3f(-7, -53, 3.7);
    //Parte de encima
    glVertex3f(-7, -38, 8);
    glVertex3f(-8, -39, 8);
    glVertex3f(-8, -52, 8); 
    glVertex3f(-7, -53, 8);
    
    glVertex3f(-7, -38, 8);
    glVertex3f(-8, -39, 8);
    glVertex3f(-12, -39, 8); 
    glVertex3f(-12, -38, 8);
    
    glVertex3f(-8, -52, 8); 
    glVertex3f(-7, -53, 8);
    glVertex3f(-12, -53, 8); 
    glVertex3f(-12, -52, 8);
    //defrente
    glVertex3f(-12, -38, 3.7);
    glVertex3f(-12, -39, 4.5);
    glVertex3f(-12, -39, 8); 
    glVertex3f(-12, -38, 8);
    
    glVertex3f(-12, -38, 3.7);
    glVertex3f(-12, -39, 4.5);
    glVertex3f(-12, -52, 4.5); 
    glVertex3f(-12, -53, 3.7);
    
    glVertex3f(-12, -52, 4.5); 
    glVertex3f(-12, -53, 3.7);
    glVertex3f(-12, -53, 8); 
    glVertex3f(-12, -52, 8);
    //colchones------------------------------
    //arriba
    glColor3f( 0.827 , 0.811 , 0.768 );//beige
    glVertex3f(-8, -39, 9); 
    glVertex3f(-9, -39, 9);
    glVertex3f(-9, -52, 9); 
    glVertex3f(-8, -52, 9);
    //atras
    glVertex3f(-8, -39, 9); 
    glVertex3f(-8, -52, 9);
    glVertex3f(-8, -52, 6); 
    glVertex3f(-8, -39, 6); 
    //enfrente
    glVertex3f(-9, -39, 9); 
    glVertex3f(-9, -52, 9);
    glVertex3f(-9, -52, 6); 
    glVertex3f(-9, -39, 6);
    //------cojin izquierdo-------------
    //cojin arriba
    glVertex3f(-9, -51, 9); 
    glVertex3f(-12, -52, 9);
    glVertex3f(-12, -51, 9); 
    glVertex3f(-9, -51, 9);
    //cojin izquierdo
    glVertex3f(-12, -51, 9); 
    glVertex3f(-9, -51, 9);
    glVertex3f(-9, -51, 6); 
    glVertex3f(-12, -51, 6);
    //cojin derecho
    glVertex3f(-8, -52, 9); 
    glVertex3f(-12, -52, 9);
    glVertex3f(-12, -52, 6); 
    glVertex3f(-8, -52, 6);
    //cojin enfrente
    glVertex3f(-12, -51, 9); 
    glVertex3f(-12, -52, 9);
    glVertex3f(-12, -52, 6); 
    glVertex3f(-12, -51, 6);
    //----------cojin derecho-------------
    //cojin arriba
    glVertex3f(-9, -39, 9); 
    glVertex3f(-12, -39, 9);
    glVertex3f(-12, -40, 9); 
    glVertex3f(-9, -40, 9);
    //cojin izquierdo
    glVertex3f(-8, -39, 9); 
    glVertex3f(-12, -39, 9);
    glVertex3f(-12, -39, 6); 
    glVertex3f(-8, -39, 6);
    //cojin derecho
    glVertex3f(-12, -40, 9); 
    glVertex3f(-9, -40, 9);
    glVertex3f(-9, -40, 6); 
    glVertex3f(-12, -40, 6);
    //cojin enfrente
    glVertex3f(-12, -39, 9); 
    glVertex3f(-12, -40, 9);
    glVertex3f(-12, -40, 6); 
    glVertex3f(-12, -39, 6);
    //cojin base
     
    //cojin encima
    glVertex3f(-8, -39, 6); 
    glVertex3f(-8, -52, 6);
    glVertex3f(-12, -52, 6); 
    glVertex3f(-12, -39, 6);
    //cojin enfrente
    glVertex3f(-12, -52, 6); 
    glVertex3f(-12, -39, 6);
    glVertex3f(-12, -39, 4.5); 
    glVertex3f(-12, -52, 4.5);
    glEnd();
    //----------------linea detallado
	glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0, 0.0 );//NEGRO
    glVertex3f(-12, -52, 8); 
    glVertex3f(-12, -53, 8);
    glVertex3f(-7, -53, 8); 
    glVertex3f(-7, -38, 8);
    
    glVertex3f(-12, -38, 8); 
    glVertex3f(-12, -39, 8);
    glVertex3f(-8, -39, 8); 
    glVertex3f(-8, -52, 8);
    glEnd();
    
    
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0, 0.0 );//NEGRO
    glVertex3f(-12, -52, 8); 
    glVertex3f(-12, -53, 8);
    glVertex3f(-12, -53, 3.7); 
    glVertex3f(-12, -38, 3.7);
    
    glVertex3f(-12, -38, 8); 
    glVertex3f(-12, -39, 8);
    glVertex3f(-12, -39, 4.5); 
    glVertex3f(-12, -52, 4.5);
    glEnd();
    //sillon
    
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0, 0.0 );//NEGRO
    glVertex3f(-12, -39, 9); 
    glVertex3f(-12, -40, 9);
    glVertex3f(-9, -40, 9); 
    glVertex3f(-9, -51, 9);
    
    glVertex3f(-12, -51, 9); 
    glVertex3f(-12, -52, 9);
    glVertex3f(-8, -52, 9); 
    glVertex3f(-8, -39, 9);
    glEnd();
    
    glBegin(GL_LINES);
    glColor3f( 0.0 , 0.0, 0.0 );//NEGRO
    glVertex3f(-7, -38, 8); 
    glVertex3f(-7, -38, 3.7);
    glVertex3f(-8, -52, 8); 
    glVertex3f(-7, -53, 3.7);
    
    glVertex3f(-8, -39, 9); 
    glVertex3f(-8, -39, 6);
    glVertex3f(-12, -39, 9); 
    glVertex3f(-12, -39, 6);
    
    glVertex3f(-8, -52, 9); 
    glVertex3f(-8, -52, 6);
    glVertex3f(-12, -52, 9); 
    glVertex3f(-12, -52, 6);
    
    glVertex3f(-12, -40, 9); 
    glVertex3f(-12, -40, 6);
    glVertex3f(-12, -51, 9); 
    glVertex3f(-12, -51, 6);
    
    glVertex3f(-9, -39, 9); 
    glVertex3f(-9, -40.05, 9);
    glVertex3f(-9, -40.05, 9); 
    glVertex3f(-9, -40.05, 6);
    
    glVertex3f(-9, -52, 9); 
    glVertex3f(-9, -50.95, 9);
    glVertex3f(-9, -50.95, 9); 
    glVertex3f(-9, -50.95, 6);
    glEnd();
    
	glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0, 0.0 );//NEGRO
    glVertex3f(-12, -39, 6); 
    glVertex3f(-8, -39, 6);
    glVertex3f(-8, -52, 6); 
    glVertex3f(-12, -52, 6);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0, 0.0 );//NEGRO
    glVertex3f(-12, -40.05, 6.01); 
    glVertex3f(-9.05, -40.05, 6.01);
    glVertex3f(-9.05, -50.95, 6.01); 
    glVertex3f(-12, -50.95, 6.01);
    glEnd();
 //--------------------------------------
    glPushMatrix();
    glTranslatef(-2.0f, -3.0f, 0.0f);//TRASLADADO
    
    sillon_chico();
    glEnd();
    glPopMatrix();
    glEnd();
    
    
    
    
}

void parede_patio(){
	glBegin(GL_QUADS);
	//cajon izquierdo
	//cara derecha
	glColor3f( 0.819 , 0.756 , 0.694 );//plmo 
    glVertex3f(-50.07, -55.07, 20);
    glVertex3f(-50.07, -55.07, 0);
    glVertex3f(55, -55.07, 0.1); 
    glVertex3f(55, -55.07, 20);
    //cara izquierda
    glVertex3f(-50.07, -55.07, 20);
    glVertex3f(-50.07, -55.07, 0.1);
    glVertex3f(-50.07, 25, 0.1); 
    glVertex3f(-50.07, 25, 20);
    //pared cerca al pasillo
    glVertex3f(-50.07, 25, 0.1);
    glVertex3f(-50.07, 25, 20);
    glVertex3f(-25, 25, 20);
    glVertex3f(-25, 25, 0.1);
	glEnd();
	
	
}

void zona_parrilla(){
	base();
	techo();
	parrilla();
	muebles();
	parede_patio();
}	

/////////////////////////// PUERTA PASILLO ///////////////////

void puertaPasilloSala(){
	
	//puerta central (madera)
	
	glPushMatrix();
		
		//glColor3f(1.0f, 1.4f, 1.0f);
		
		glColor3f( 0.6, 0.5, 0.3);

		glTranslatef(55.05, -17.05, 8.11);

		glScalef(0.04, 0.85, 1.54);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
	glPopMatrix();
	

	//////////////////////////////////////// extremos de puerta //////////////////////////////////
	//*********** lad izq
	glPushMatrix();
	    //glColor3f(1.0, 1.0, 1.0);
		glColor3f(1.0, 0.815, 0.392);
		glTranslatef(55.05, -21.05, 8.11);
		
		//glScalef(0.057, 0.089, 1.59);
		glScalef(0.089, 0.087, 1.59);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();			
	glPopMatrix();
	
	
	
	//********** lad der
	glPushMatrix();
	   // glColor3f(1.0, 1.0, 1.0);
	    glColor3f(1.0, 0.815, 0.392);
	
		glTranslatef(55.05, -13.05, 8.11);
	
		glScalef(0.087, 0.089, 1.59);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();			
	glPopMatrix();
	
	
	
	//*************lad inf
	glPushMatrix();
	
		//glColor3f(1.0, 1.0, 1.0);
		glColor3f(1.0, 0.815, 0.392);
		glTranslatef(55.10, -17.05, 0.21);
	
		
		glScalef(0.10, 0.74, 0.045);
		
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();			
	glPopMatrix();
	
	
	
	//********** lad sup
	
	glPushMatrix();
	    //glColor3f(1.0, 1.0, 1.0);
		glColor3f(1.0, 0.815, 0.392);
	
		glTranslatef(55.10, -17.05, 15.81);
	
		glScalef(0.10, 0.74, 0.045);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();			
	glPopMatrix();
	
	
	//////////////////////////////  manija ///////////////////////////////////////
	
	//////// ---------------dentro ----------
	
	/// cubito
	//parte der
	
    glPushMatrix();
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
			glTranslatef(54.75, -19.85, 8.11);
	
		glScalef(0.04, 0.03, 0.03);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
	
	
	
	//// manija horizontal
	
	glPushMatrix();
	    glColor3f(0.0, 0.0, 0.0);
	
			glTranslatef(54.55, -19.25, 8.11);
	
		//glScalef(0.23, 0.03, 0.03);
		glScalef(0.03, 0.23, 0.03);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();			
	glPopMatrix();

		//////// --------------- afuera ----------
	
	/// cubito
	//parte der
	
    glPushMatrix();
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		glTranslatef(55.24, -19.35, 8.11);
	
		glScalef(0.04, 0.03, 0.03);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
	
	
	
	//// manija vertical
	
	glPushMatrix();
	    glColor3f(0.0, 0.0, 0.0);
	
			glTranslatef(55.45, -19.40, 7.81);
	
		//glScalef(0.23, 0.03, 0.03);
		glScalef(0.03, 0.03, 0.23);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();			
	glPopMatrix();


}

void puertaPasillo(){
		
	//puerta central (madera)
	
	glPushMatrix();
		
		glColor3f(1.0f, 1.4f, 1.0f);
		
		glTranslatef(-0.4, 25.05, 8.11);
		
		glScalef(0.80, 0.04, 1.54);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
	glPopMatrix();
	

	//////////////////////////////////////// extremos de puerta //////////////////////////////////
	//*********** lad izq
	glPushMatrix();
	    glColor3f(1.0, 1.0, 1.0);
	
		glTranslatef(-4.5, 25.05, 8.00);
	
		glScalef(0.057, 0.089, 1.59);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();			
	glPopMatrix();
	
	
	
	//********** lad der
	glPushMatrix();
	    glColor3f(1.0, 1.0, 1.0);
	
		glTranslatef(3.5, 25.05, 8.00);
	
		glScalef(0.057, 0.089, 1.59);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();			
	glPopMatrix();
	
	
	
	//*************lad inf
	glPushMatrix();
	
		glColor3f(1.0, 1.0, 1.0);
	
		glTranslatef(-0.5, 25.05, 0.21);
	
		
		//glScalef(0.13, 0.796, 0.038);
		glScalef(0.74, 0.10, 0.035);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();			
	glPopMatrix();
	
	
	
	//********** lad sup
	
	glPushMatrix();
	    glColor3f(1.0, 1.0, 1.0);
	
		glTranslatef(-0.5, 25.05, 15.71);
	
		glScalef(0.74, 0.10, 0.035);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();			
	glPopMatrix();
	
	
	//////////////////////////////  manija ///////////////////////////////////////
	
	//////// ---------------dentro ----------
	
	/// cubito
	//parte der
	
    glPushMatrix();
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		glTranslatef(2.2, 24.75, 8.00);
	
		glScalef(0.03, 0.05, 0.03);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
	
	
	
	//// manija horizontal
	
	glPushMatrix();
	    glColor3f(0.0, 0.0, 0.0);
	
		glTranslatef(1.65, 24.35, 8.00);
	
		glScalef(0.23, 0.03, 0.03);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();			
	glPopMatrix();

		//////// --------------- afuera ----------
	
	/// cubito
	//parte der
	
    glPushMatrix();
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		glTranslatef(2.2, 25.45, 8.00);
	
		glScalef(0.03, 0.05, 0.03);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
	
	
	
	//// manija vertical
	
	glPushMatrix();
	    glColor3f(0.0, 0.0, 0.0);
	
		glTranslatef(1.99, 25.75, 8.00);
	
		//glScalef(0.23, 0.03, 0.03);
		glScalef(0.03, 0.03, 0.23);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();			
	glPopMatrix();


}

void paredes1(){
	
//------PAREDES Y PISO DE LA SALA----------------
//PISO
glBegin(GL_QUADS);
glColor3f(0.7, 0.5, 0.3);
glVertex3f(15.01, -25, 0.2);
glVertex3f(15.01, 25, 0.2);
glVertex3f(55, 25, 0.2); 
glVertex3f(55, -25, 0.2);
glEnd();


//--PARED DERECHA------

glBegin(GL_QUADS);
glColor3f(0.6, 0.6, 0.5);
glVertex3f(15.01, -25, 0.1);
glVertex3f(15.01, -25, 20);
glVertex3f(55, -25, 20); 
glVertex3f(55, -25, 0.1);
glEnd();

glBegin(GL_QUADS);
glColor3f(0.9, 0.9, 0.5);
glVertex3f(-15.01, -25.4, 0.1);
glVertex3f(-15.01, -25.4, 20);
glVertex3f(55, -25.4, 20); 
glVertex3f(55, -25.4, 0.1);
glEnd();


//--PARED FONDO------

glBegin(GL_QUADS);
glColor3f(0.6, 0.6, 0.5);
glVertex3f(55, -25, 0.1);
glVertex3f(55, -25, 20);
glVertex3f(55, 25, 20); 
glVertex3f(55, 25, 0.1);
glEnd();

//--PARED IZQUIERDA------

glBegin(GL_QUADS);
glColor3f(0.6, 0.6, 0.5);
glVertex3f(15.01, 25, 0.1);
glVertex3f(15.01, 25, 20);
glVertex3f(55, 25, 20); 
glVertex3f(55, 25, 0.1);
glEnd();

//--PARED ALFRENTE------
glBegin(GL_QUADS);
glColor3f(0.6, 0.6, 0.5);
glVertex3f(15.01, -25, 0.1);
glVertex3f(15.01, -25, 20);
glVertex3f(15.01, 25, 20); 
glVertex3f(15.01, 25, 0.1);
glEnd();

//TECHO

glBegin(GL_QUADS);
glColor3f(1.0, 1.0, 1.0); 
glVertex3f(15.01, -25, 20);
glVertex3f(15.01, 25, 20);
glVertex3f(55, 25, 20); 
glVertex3f(55, -25, 20);
glEnd();


}

///////////////////////// PUERTA PRINCIPAL /////////////////
void puertaPrincipal(){
	

	//puerta central (madera)
	
	glPushMatrix();
		
		glColor3f(1.0f, 1.4f, 1.0f);
		
		glTranslatef(30.4, 25.05, 8.11);
		
		glScalef(0.75, 0.04, 1.54);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
	glPopMatrix();
	

	//////////////////////////////////////// extremos de puerta //////////////////////////////////
	//*********** lad izq
	glPushMatrix();
	    glColor3f(1.0, 1.0, 1.0);
	
		glTranslatef(26.5, 25.05, 8.00);
	
		glScalef(0.057, 0.089, 1.59);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();			
	glPopMatrix();
	
	
	
	//********** lad der
	glPushMatrix();
	    glColor3f(1.0, 1.0, 1.0);
	
		glTranslatef(34.5, 25.05, 8.00);
	
		glScalef(0.057, 0.089, 1.59);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();			
	glPopMatrix();
	
	
	
	//*************lad inf
	glPushMatrix();
	
		glColor3f(1.0, 1.0, 1.0);
	
		glTranslatef(30.5, 25.05, 0.21);
	
		glScalef(0.75, 0.10, 0.035);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();			
	glPopMatrix();
	
	
	
	//********** lad sup
	
	glPushMatrix();
	    glColor3f(1.0, 1.0, 1.0);
	
		glTranslatef(30.5, 25.05, 15.71);
	
		glScalef(0.75, 0.10, 0.035);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();			
	glPopMatrix();
	
	
	//////////////////////////////  manija ///////////////////////////////////////
	
	//////// ---------------dentro ----------
	
	/// cubito
	//parte der
	
    glPushMatrix();
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		glTranslatef(33.2, 24.75, 8.00);
	
		glScalef(0.03, 0.05, 0.03);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
	
	
	
	//// manija horizontal
	
	glPushMatrix();
	    glColor3f(0.0, 0.0, 0.0);
	
		glTranslatef(32.65, 24.35, 8.00);
	
		glScalef(0.23, 0.03, 0.03);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();			
	glPopMatrix();

		//////// --------------- afuera ----------
	
	/// cubito
	//parte der
	
    glPushMatrix();
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		glTranslatef(33.2, 25.45, 8.00);
	
		glScalef(0.03, 0.05, 0.03);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
	
	
	
	//// manija vertical
	
	glPushMatrix();
	    glColor3f(0.0, 0.0, 0.0);
	
		glTranslatef(33.19, 25.75, 7.50);
	
		//glScalef(0.23, 0.03, 0.03);
		glScalef(0.03, 0.03, 0.23);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();			
	glPopMatrix();


}

//////////////// CUADRO 1 ////////////////////////
void cuadro1(){
	
	//////////////////>>>>>>>> PORTADA <<<<<<<<<<<
	
	//lienzo del cuadro (blanco)
	
	glPushMatrix();
		
		glColor3f(1.0f, 1.0f, 1.0f);
		
		glTranslatef(40.4, -25.05, 14.51);
		
		glScalef(0.80, 0.03, 0.54);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
	glPopMatrix();
	
	//lienzo del cuadro (morado)
	
	glPushMatrix();
		
		glColor3f(0.850f, 0.772f, 0.878f);
		
		glTranslatef(40.4, -25.05, 14.51);
		
		glScalef(0.70, 0.04, 0.44);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
	glPopMatrix();
	
	
	//////------- bordes
	
		//bordes lado izq
	
	glPushMatrix();
		
		glColor3f(1.0, 0.815, 0.392);
		
		glTranslatef(44.5, -25.05, 14.50);
		
		glScalef(0.03, 0.04, 0.54);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
	glPopMatrix();
	
		//bordes lado der
	
	glPushMatrix();
		
		glColor3f(1.0, 0.815, 0.392);
		
		glTranslatef(36.3, -25.05, 14.50);
		
		glScalef(0.03, 0.04, 0.54);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
	glPopMatrix();
	
		
	
	// bordes lad inf
	
	glPushMatrix();
	
		glColor3f(1.0, 0.815, 0.392);//amarillo
	
		glTranslatef(40.4, -25.05, 11.61);
	
		
	
		glScalef(0.86, 0.04, 0.03);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();			
	glPopMatrix();
	
	
	// bordes lad sup
	
	glPushMatrix();
	    glColor3f(1.0, 0.815, 0.392);
	
		glTranslatef(40.4, -25.05, 17.31);
	
		glScalef(0.86, 0.04, 0.03);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();			
	glPopMatrix();
	
	/////>>>>>>>>>>>> IMAGEN  <<<<<<<<<<<<<<
	
	///hojita
	glPushMatrix();
		
		glColor3f(0.5f, 1.0f, 0.4f);
		
		glTranslatef(39.8, -24.90, 15.57);
		glRotated(45,0,1,0);
		
		glScalef(0.05, 0.04, 0.06);
		
		glutSolidCube(10);
		
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
	glPopMatrix();
	
	///manzanita
	glPushMatrix();
		
		glColor3f(0.839f, 0.321f, 0.301f);
		
		glTranslatef(40.4, -24.90, 14.01);
		
		glScalef(0.20, 0.04, 0.18);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
	glPopMatrix();
	
	///tallito
	glPushMatrix();
		
		glColor4f(0.329f, 0.125f, 0.117f,0.129f);//marron
		
		glTranslatef(40.4, -24.90, 15.50);
		
		glScalef(0.03, 0.02, 0.12);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
	glPopMatrix();
	
	//plato sup
	glPushMatrix();
		
		glColor3f(0.560f, 0.552f, 0.545f);//plomo
		
		glTranslatef(40.4, -24.90, 13.01);
		
		glScalef(0.29, 0.04, 0.016);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
	glPopMatrix();
	//plato inf
		glPushMatrix();
		
		glColor3f(0.560f, 0.552f, 0.545f);//plomo
		
		glTranslatef(40.4, -24.90, 12.80);
		
		glScalef(0.20, 0.04, 0.020);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
	glPopMatrix();
	
	glPopMatrix();
	
}
/////////////////// TV  ///////////////////////

void televisor(){
	
	
	//////////////////>>>>>>>> TV <<<<<<<<<<<
	
	//pared rac del TV (blanco)
	
	glPushMatrix();
		
		glColor3f(1.0f, 1.0f, 1.0f);
		
		glTranslatef(55.00, 7.05, 11.51);
		
		glScalef(0.02, 1.65, 0.89);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
	glPopMatrix();
	
	//centro del tv (negro)
	
	glPushMatrix();
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		
		glTranslatef(55.00, 7.05, 11.51);
		
		glScalef(0.04, 1.05, 0.59);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
	glPopMatrix();
	
	//detras del tv (gris)
	
	glPushMatrix();
		
		glColor3f(0.560f, 0.552f, 0.545f);//plomo
			
		glTranslatef(55.20, 7.05, 11.51);
		
		glScalef(0.02, 1.05, 0.60);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
	glPopMatrix();
	
	
	
	//////------- bordes
	
		//bordes lado der
	
	glPushMatrix();
		
		glColor3f(0.560f, 0.552f, 0.545f);//plomo
		
		glTranslatef(55.00, 1.95, 11.51);
		

		glScalef(0.06, 0.04, 0.59);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
	glPopMatrix();
	
		//bordes lado izq
	
	glPushMatrix();
		
		glColor3f(0.560f, 0.552f, 0.545f);//plomo
		
		glTranslatef(55.00, 12.55, 11.51);
		
		glScalef(0.06, 0.04, 0.59);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
	glPopMatrix();
	
	
	
	// bordes lad inf
	
	glPushMatrix();
	
		glColor3f(0.560f, 0.552f, 0.545f);//plomo
		
		glTranslatef(55.00, 7.35, 8.51);
	
		glScalef(0.04, 1.09, 0.04);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();			
	glPopMatrix();
	
	
	// bordes lad sup
	
	glPushMatrix();
	
		glColor3f(0.560f, 0.552f, 0.545f);//plomo
		
		glTranslatef(55.00, 7.35, 14.51);
	
		glScalef(0.04, 1.09, 0.04);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);
			
		glEnd ();
					
	glPopMatrix();
	
	///boton 
		glPushMatrix();
		
		glColor3f(0.9607f, 0.1803f, 0.0901f);
		
		glTranslatef(54.80, 2.35, 8.41);
		
		glScalef(0.01, 0.01, 0.01);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
	glPopMatrix();
	
}

void mesaTVSala(){
	
	/////////////////// mesa parte inf
		glPushMatrix();
		
		glColor3f(1.0f, 1.0f, 1.0f);
		
		glTranslatef(51.00, 8.47, 1.8);
		
		glScalef(0.7, 3.3, 0.30);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
	glPopMatrix();
	
		/////////////////// mesa parte sup
		glPushMatrix();
		
		glColor3f(1.0f, 1.0f, 1.0f);
		
		glTranslatef(51.00,8.47, 5.7);
		
		glScalef(0.7, 3.3, 0.10);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
	glPopMatrix();
	
		/////////////////// mesa parte izq
		glPushMatrix();
		
		glColor3f(1.0f, 1.0f, 1.0f);
		
		glTranslatef(51.0, 24.51, 4.25);
		
		glScalef(0.7, 0.09, 0.19);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
	glPopMatrix();
	
	/////////////////// mesa parte der
		glPushMatrix();
		
		glColor3f(1.0f, 1.0f, 1.0f);
		
		
		glTranslatef(51.0,-7.57, 4.25);
		
		glScalef(0.7, 0.09, 0.19);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
	glPopMatrix();
	
		/////////////////// mesa parte fondo
		glPushMatrix();
		
		glColor3f(1.0f, 1.0f, 1.0f);
		
		
		glTranslatef(54.30,8.47, 4.3);
		
		glScalef(0.05, 3.2, 0.19);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
	glPopMatrix();
	
	///////////////////OBJETO  //////////////
	
	//>>>>>>>>> bluray <<<<<<<<<<<<<<
	
	/// caja
		glPushMatrix();
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		glTranslatef(51.00,8.17, 3.8);
		
		glScalef(0.3, 0.3, 0.08);
		
		glutSolidCube(10);
		
		glColor3f(1.0f, 1.0f, 1.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
	glPopMatrix();
	
	/// disquera
		glPushMatrix();
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		glTranslatef(49.98,8.37, 3.8);
		
		glScalef(0.10, 0.19, 0.03);
		
		glutSolidCube(10);
		
		glColor3f(1.0f, 1.0f, 1.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
	glPopMatrix();
	
	///boton 
		glPushMatrix();
		
	//	glColor3f(0.9607f, 0.1803f, 0.0901f);//rojo
		glColor3f(0.0117f, 0.4549f, 1.0f);
		
		
		
		glTranslatef(49.50,7.07, 3.8);
		
		glScalef(0.02, 0.03, 0.03);
		
		glutSolidCube(10);
		
		glColor3f(1.0f, 1.0f, 1.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
	glPopMatrix();
	
	//>>>>>>>>>>   CAJONES  <<<<<<<<<<<<<<
	
	//orden de izquierda a derecha
	
	//---------------cajon 1 -----------------
		glPushMatrix();
		
	    glColor3f( 0.7019, 0.4705, 0.1882);
		
		
		glTranslatef(48.80, 20.47, 1.8);

		glScalef(0.3, 0.68, 0.14);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();
		
		//// manija 1
			glPushMatrix();
		
	    glColor3f( 1.0f, 1.0f, 1.0f);
		
	
		glTranslatef(47.20, 20.47, 1.8);

		glScalef(0.02, 0.45, 0.02);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();
		
		
	
	//----------------------cajon 2 -------------------
		glPushMatrix();
		
		glColor3f( 0.7019, 0.4705, 0.1882);
		
		
		glTranslatef(48.80, 12.47, 1.8);

		glScalef(0.3, 0.68, 0.14);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();
		
		
		
		//// manija 2
			glPushMatrix();
		
	    glColor3f( 1.0f, 1.0f, 1.0f);
		
	
		glTranslatef(47.20, 12.47, 1.8);

		glScalef(0.02, 0.45, 0.02);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();
		
		
		
		
		
	//---------------- cajon 3 --------------------
		glPushMatrix();
		
		glColor3f( 0.7019, 0.4705, 0.1882);
		
	
		glTranslatef(48.80, 4.47, 1.8);

		glScalef(0.3, 0.68, 0.14);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();
		
		
		//// manija 3
			glPushMatrix();
		
	    glColor3f( 1.0f, 1.0f, 1.0f);
		
	
		glTranslatef(47.20, 4.47, 1.8);
	

		glScalef(0.02, 0.45, 0.02);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();
		
		
		
	//-------------- cajon 4 ----------------
		glPushMatrix();
		
		
		glColor3f( 0.7019, 0.4705, 0.1882);
		
	
		glTranslatef(48.80, -3.47, 1.8);

		glScalef(0.3, 0.68, 0.14);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();
	
	//// manija 4
			glPushMatrix();
		
	    glColor3f( 1.0f, 1.0f, 1.0f);
		
	
		glTranslatef(47.20, -3.47, 1.8);

		glScalef(0.02, 0.45, 0.02);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();
	
}

void repisa3(){
	
	//lado pared
	glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(20, -24.98, 12.5);
    glVertex3f(20, -24.98, 13);
    glVertex3f(35, -24.98, 13); 
    glVertex3f(35, -24.98, 12.5);
    glEnd();
    
    //base
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(20, -24.98, 12.5);
    glVertex3f(20, -21, 12.5);
    glVertex3f(35, -21, 12.5); 
    glVertex3f(35, -24.98, 12.5);
    glEnd();
    
    //lado encima
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(20, -24.98, 13);
    glVertex3f(20, -21, 13);
    glVertex3f(35, -21, 13); 
    glVertex3f(35, -24.98, 13);
    glEnd();
    
    //lado delantero
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(20, -21, 12.5);
    glVertex3f(20, -21, 13);
    glVertex3f(35, -21, 13); 
    glVertex3f(35, -21, 12.5);
    glEnd();
}

void repisa4(){
	
	//lado pared
	glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(20, -24.98, 8.5);
    glVertex3f(20, -24.98, 9);
    glVertex3f(38, -24.98, 9); 
    glVertex3f(38, -24.98, 8.5);
    glEnd();
    
    //base
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(20, -24.98, 8.5);
    glVertex3f(20, -21, 8.5);
    glVertex3f(38, -21, 8.5); 
    glVertex3f(38, -24.98, 8.5);
    glEnd();
    
    //lado encima
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(20, -24.98, 9);
    glVertex3f(20, -21, 9);
    glVertex3f(38, -21, 9); 
    glVertex3f(38, -24.98, 9);
    glEnd();
    
    //lado delantero
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(20, -21, 8.5);
    glVertex3f(20, -21, 9);
    glVertex3f(38, -21, 9); 
    glVertex3f(38, -21, 8.5);
    glEnd();
    
    //libro1
    //cara atras
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(34, -24, 9.01);
    glVertex3f(34, -24, 11);
    glVertex3f(34.5, -24, 11); 
    glVertex3f(34.5, -24, 9.01);
    glEnd();
    
    //lado derecho
    glBegin(GL_QUADS);
    glColor3f(0.8, 0.0, 0.0);
    glVertex3f(34, -24, 9.01);
    glVertex3f(34, -24, 11);
    glVertex3f(34, -22, 11); 
    glVertex3f(34, -22, 9.01);
    glEnd();
    
    //lado izquierdo
    glBegin(GL_QUADS);
    glColor3f(0.8, 0.0, 0.0);
    glVertex3f(34.5, -24, 9.01);
    glVertex3f(34.5, -24, 11);
    glVertex3f(34.5, -22, 11); 
    glVertex3f(34.5, -22, 9.01);
    glEnd();
    
    //cara adelante
    glBegin(GL_QUADS);
    glColor3f(0.8, 0.0, 0.0);
    glVertex3f(34, -22, 9.01);
    glVertex3f(34, -22, 11);
    glVertex3f(34.5, -22, 11); 
    glVertex3f(34.5, -22, 9.01);
    glEnd();
    
    //cara encima
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(34, -24, 11);
    glVertex3f(34, -22, 11);
    glVertex3f(34.5, -22, 11); 
    glVertex3f(34.5, -24, 11);
    glEnd();
    
    //libro2
    //cara atras
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(34.7, -24, 9.01);
    glVertex3f(34.7, -24, 11);
    glVertex3f(35.2, -24, 11); 
    glVertex3f(35.2, -24, 9.01);
    glEnd();
    
    //lado derecho
    glBegin(GL_QUADS);
    glColor3f(0.6, 1.0, 0.0);
    glVertex3f(34.7, -24, 9.01);
    glVertex3f(34.7, -24, 11);
    glVertex3f(34.7, -22, 11); 
    glVertex3f(34.7, -22, 9.01);
    glEnd();
    
    //lado izquierdo
    glBegin(GL_QUADS);
    glColor3f(0.6, 1.0, 0.0);
    glVertex3f(35.2, -24, 9.01);
    glVertex3f(35.2, -24, 11);
    glVertex3f(35.2, -22, 11); 
    glVertex3f(35.2, -22, 9.01);
    glEnd();
    
    //cara adelante
    glBegin(GL_QUADS);
    glColor3f(0.6, 1.0, 0.0);
    glVertex3f(34.7, -22, 9.01);
    glVertex3f(34.7, -22, 11);
    glVertex3f(35.2, -22, 11); 
    glVertex3f(35.2, -22, 9.01);
    glEnd();
    
    //cara encima
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(34.7, -24, 11);
    glVertex3f(34.7, -22, 11);
    glVertex3f(35.2, -22, 11); 
    glVertex3f(35.2, -24, 11);
    glEnd();
    
    //libro3
    //cara atras
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(35.4, -24, 9.01);
    glVertex3f(35.4, -24, 11);
    glVertex3f(35.9, -24, 11); 
    glVertex3f(35.9, -24, 9.01);
    glEnd();
    
    //lado derecho
    glBegin(GL_QUADS);
    glColor3f(0.4, 0.8, 1.0);
    glVertex3f(35.4, -24, 9.01);
    glVertex3f(35.4, -24, 11);
    glVertex3f(35.4, -22, 11); 
    glVertex3f(35.4, -22, 9.01);
    glEnd();
    
    //lado izquierdo
    glBegin(GL_QUADS);
    glColor3f(0.4, 0.8, 1.0);
    glVertex3f(35.9, -24, 9.01);
    glVertex3f(35.9, -24, 11);
    glVertex3f(35.9, -22, 11); 
    glVertex3f(35.9, -22, 9.01);
    glEnd();
    
    //cara adelante
    glBegin(GL_QUADS);
    glColor3f(0.4, 0.8, 1.0);
    glVertex3f(35.4, -22, 9.01);
    glVertex3f(35.4, -22, 11);
    glVertex3f(35.9, -22, 11); 
    glVertex3f(35.9, -22, 9.01);
    glEnd();
    
    //cara encima
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(35.4, -24, 11);
    glVertex3f(35.4, -22, 11);
    glVertex3f(35.9, -22, 11); 
    glVertex3f(35.9, -24, 11);
    glEnd();
    
    //libro4
    //cara atras
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(33.3, -24, 9.01);
    glVertex3f(33.3, -24, 11);
    glVertex3f(33.8, -24, 11); 
    glVertex3f(33.8, -24, 9.01);
    glEnd();
    
    //lado derecho
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.0, 0.9);
    glVertex3f(33.3, -24, 9.01);
    glVertex3f(33.3, -24, 11);
    glVertex3f(33.3, -22, 11); 
    glVertex3f(33.3, -22, 9.01);
    glEnd();
    
    //lado izquierdo
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.0, 0.9);
    glVertex3f(33.8, -24, 9.01);
    glVertex3f(33.8, -24, 11);
    glVertex3f(33.8, -22, 11); 
    glVertex3f(33.8, -22, 9.01);
    glEnd();
    
    //cara adelante
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.0, 0.9);
    glVertex3f(33.3, -22, 9.01);
    glVertex3f(33.3, -22, 11);
    glVertex3f(33.8, -22, 11); 
    glVertex3f(33.8, -22, 9.01);
    glEnd();
    
    //cara encima
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(33.3, -24, 11);
    glVertex3f(33.3, -22, 11);
    glVertex3f(33.8, -22, 11); 
    glVertex3f(33.8, -24, 11);
    glEnd();
    
    //libro5
    //cara atras
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(32.6, -24, 9.01);
    glVertex3f(32.6, -24, 11);
    glVertex3f(33.1, -24, 11); 
    glVertex3f(33.1, -24, 9.01);
    glEnd();
    
    //lado derecho
    glBegin(GL_QUADS);
    glColor3f(0.6, 0.6, 0.0);
    glVertex3f(32.6, -24, 9.01);
    glVertex3f(32.6, -24, 11);
    glVertex3f(32.6, -22, 11); 
    glVertex3f(32.6, -22, 9.01);
    glEnd();
    
    //lado izquierdo
    glBegin(GL_QUADS);
    glColor3f(0.6, 0.6, 0.0);
    glVertex3f(33.1, -24, 9.01);
    glVertex3f(33.1, -24, 11);
    glVertex3f(33.1, -22, 11); 
    glVertex3f(33.1, -22, 9.01);
    glEnd();
    
    //cara adelante
    glBegin(GL_QUADS);
    glColor3f(0.6, 0.6, 0.0);
    glVertex3f(32.6, -22, 9.01);
    glVertex3f(32.6, -22, 11);
    glVertex3f(33.1, -22, 11); 
    glVertex3f(33.1, -22, 9.01);
    glEnd();
    
    //cara encima
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(32.6, -24, 11);
    glVertex3f(32.6, -22, 11);
    glVertex3f(33.1, -22, 11); 
    glVertex3f(33.1, -24, 11);
    glEnd();
    
    
    //cuadro
    //bordes cuadro
    glBegin(GL_QUADS);
    glColor3f(0.8, 0.8, 0.0);
    glVertex3f(24, -22, 9.01);
    glVertex3f(24, -22, 12);
    glVertex3f(26.5, -22, 12); 
    glVertex3f(26.5, -22, 9.01);
    glEnd();
    
    //fondo blanco cuadro
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(24.2, -21.99, 9.21);
    glVertex3f(24.2, -21.99, 11.8);
    glVertex3f(26.3, -21.99, 11.8); 
    glVertex3f(26.3, -21.99, 9.21);
    glEnd();
    
    
    //sujetador de cuadro
    glBegin(GL_QUADS);
    glColor3f(0.8, 0.8, 0.0);
    glVertex3f(25, -24.02, 9.01);
    glVertex3f(25, -22, 10.7);
    glVertex3f(25.8, -22, 10.7); 
    glVertex3f(25.8, -24.02, 9.01);
    glEnd();
    
    
}

void mueble1(){
	
	//lado de atras mueble
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.4, 0.3);
    glVertex3f(26, -15, 0.2);
    glVertex3f(26, -15, 6);
    glVertex3f(39, -15, 6); 
    glVertex3f(39, -15, 0.2);
    glEnd();
    //bordes negros
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(26.01, -15.01, 0.2);
    glVertex3f(26.01, -15.01, 6);
    glVertex3f(26.05, -15.01, 6); 
    glVertex3f(26.05, -15.01, 0.2);
    glEnd();
    
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(38.96, -15.01, 0.2);
    glVertex3f(38.96, -15.01, 6);
    glVertex3f(39, -15.01, 6); 
    glVertex3f(39, -15.01, 0.2);
    glEnd();
    
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(26, -15.01, 0.2);
    glVertex3f(26, -15.01, 0.24);
    glVertex3f(39, -15.01, 0.24); 
    glVertex3f(39, -15.01, 0.2);
    
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(26, -15.01, 5.96);
    glVertex3f(26, -15.01, 6);
    glVertex3f(39, -15.01, 6); 
    glVertex3f(39, -15.01, 5.96);
    
    //lado derecho
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.4, 0.3);
    glVertex3f(26, -15, 0.2);
    glVertex3f(26, -15, 6);
    glVertex3f(26, -13.5, 6); 
    glVertex3f(26, -13.5, 0.2);
    glEnd();
    
    //linea lado derecho
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(25.99, -15, 0.2);
    glVertex3f(25.99, -15, 6);
    glVertex3f(25.99, -15.04, 6); 
    glVertex3f(25.99, -15.04, 0.2);
    glEnd();
    
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(25.99, -13.5, 0.2);
    glVertex3f(25.99, -13.5, 6);
    glVertex3f(25.99, -13.54, 6); 
    glVertex3f(25.99, -13.54, 0.2);
    glEnd();
    
    //lado izquierdo
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.4, 0.3);
    glVertex3f(39, -15, 0.2);
    glVertex3f(39, -15, 6);
    glVertex3f(39, -13.5, 6); 
    glVertex3f(39, -13.5, 0.2);
    glEnd();
    
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(39.01, -14.96, 0.2);
    glVertex3f(39.01, -14.96, 6);
    glVertex3f(39.01, -15, 6); 
    glVertex3f(39.01, -15, 0.2);
    glEnd();
    
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(39.01, -13.5, 0.2);
    glVertex3f(39.01, -13.5, 6);
    glVertex3f(39.01, -13.54, 6); 
    glVertex3f(39.01, -13.54, 0.2);
    glEnd();
    
    
    
    //lado arriba
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.4, 0.3);
    glVertex3f(26, -15, 6);
    glVertex3f(26, -13.5, 6);
    glVertex3f(39, -13.5, 6); 
    glVertex3f(39, -15, 6);
    glEnd();
    
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(26, -14.96, 6.01);
    glVertex3f(26, -15, 6.01);
    glVertex3f(39, -15, 6.01); 
    glVertex3f(39, -14.96, 6.01);
    glEnd();
    
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(26, -15, 6.01);
    glVertex3f(26, -13.5, 6.01);
    glVertex3f(26.04, -13.5, 6.01); 
    glVertex3f(26.04, -15, 6.01);
    glEnd();
    
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(38.94, -15, 6.01);
    glVertex3f(38.94, -13.5, 6.01);
    glVertex3f(39, -13.5, 6.01); 
    glVertex3f(39, -15, 6.01);
    glEnd();
    
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(26, -13.5, 6.01);
    glVertex3f(26, -13.54, 6.01);
    glVertex3f(39, -13.54, 6.01); 
    glVertex3f(39, -13.5, 6.01);
    glEnd();
    
    //linea encima
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(32.1, -15, 6.01);
    glVertex3f(32.1, -13.5, 6.01);
    glVertex3f(32.2, -13.5, 6.01); 
    glVertex3f(32.2, -15, 6.01);
    glEnd();
    
    //linea continuacion1
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(32.1, -13.49, 0.2);
    glVertex3f(32.1, -13.49, 6);
    glVertex3f(32.2, -13.49, 6); 
    glVertex3f(32.2, -13.49, 0.2);
    glEnd();
    
    //linea lado asiento
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(32.1, -13.5, 3.81);
    glVertex3f(32.1, -9, 3.81);
    glVertex3f(32.2, -9, 3.81); 
    glVertex3f(32.2, -15, 3.81);
    glEnd();
    
    //linea lado de adelante mueble
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(32.1, -8.99, 2.5);
    glVertex3f(32.1, -8.99, 3.8);
    glVertex3f(32.2, -8.99, 3.8); 
    glVertex3f(32.2, -8.99, 2.5);
    glEnd();
    
    //linea lado de cara adelante mueble
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(26, -8.99, 2.4);
    glVertex3f(26, -8.99, 2.5);
    glVertex3f(39, -8.99, 2.5); 
    glVertex3f(39, -8.99, 2.4);
    glEnd();
    
    
    //lado de adelante trasera mueble
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.4, 0.3);
    glVertex3f(26, -13.5, 0.2);
    glVertex3f(26, -13.5, 6);
    glVertex3f(39, -13.5, 6); 
    glVertex3f(39, -13.5, 0.2);
    glEnd();
    
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(26, -13.49, 3.81);
    glVertex3f(26, -13.49, 3.84);
    glVertex3f(39, -13.49, 3.84); 
    glVertex3f(39, -13.49, 3.81);
    glEnd();
    //lado de adelante mueble
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.4, 0.3);
    glVertex3f(26, -9, 0.2);
    glVertex3f(26, -9, 3.8);
    glVertex3f(39, -9, 3.8); 
    glVertex3f(39, -9, 0.2);
    glEnd();
    
    //lado derecho
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.4, 0.3);
    glVertex3f(26, -13.5, 0.2);
    glVertex3f(26, -13.5, 3.8);
    glVertex3f(26, -9, 3.8); 
    glVertex3f(26, -9, 0.2);
    glEnd();
    
    //linea lado derecho 
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(25.99, -13.5, 2.4);
    glVertex3f(25.99, -13.5, 2.5);
    glVertex3f(25.99, -9, 2.5); 
    glVertex3f(25.99, -9, 2.4);
    glEnd();
    
    
    //lado izquierdo
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.4, 0.3);
    glVertex3f(39, -13.5, 0.2);
    glVertex3f(39, -13.5, 3.8);
    glVertex3f(39, -9, 3.8); 
    glVertex3f(39, -9, 0.2);
    glEnd();	
    
    //linea lado derecho 
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(39.01, -13.5, 2.4);
    glVertex3f(39.01, -13.5, 2.5);
    glVertex3f(39.01, -9, 2.5); 
    glVertex3f(39.01, -9, 2.4);
    glEnd();
    
    //lado arriba
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.4, 0.3);
    glVertex3f(26, -13.5, 3.8);
    glVertex3f(26, -9, 3.8);
    glVertex3f(39, -9, 3.8); 
    glVertex3f(39, -15, 3.8);
    glEnd();
    
	
}

void mueble()
{    //ALFOMBRA
	glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f( 0.714, 0.613, 0.415);
    glVertex3f(15.2, -15, 0.3);
    glVertex3f(15.2, 15, 0.3);
    glVertex3f(40, 15, 0.3); 
    glVertex3f(40, -15, 0.3);
    glEnd();
    
    glPopMatrix();
    glPushMatrix();
    glBegin(GL_LINE_LOOP);
   glColor3f(0.1,0.1,0.1);
    glVertex3f(15.2, -15, 0.3);
    glVertex3f(15.2, 15, 0.3);
    glVertex3f(40, 15, 0.3); 
    glVertex3f(40, -15, 0.3);
    glEnd();
    glPopMatrix();
    
    
     //  MUEBLE BASE 1
		glPushMatrix();
		glColor3f( 0.5, 0.4, 0.3);
	    glTranslatef(18.72, 2.95, 1.4); 
		glScalef(0.7,1.405, 0.2);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();
		
		//COJIN 1
		glPushMatrix();
		glColor3f( 0.5, 0.4, 0.3);
	    glTranslatef(19.46,7.77,2.82); 
		glScalef(0.55, 0.44, 0.08);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
		glPopMatrix();
		
			//  COJIN 2
		glPushMatrix();
		glColor3f( 0.5, 0.4, 0.3);
	    glTranslatef(19.46,3.26,2.82); 
		glScalef(0.55, 0.46, 0.08);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
		glPopMatrix();
		
			//  COJIN 3
		glPushMatrix();
		glColor3f( 0.5, 0.4, 0.3);
	    glTranslatef(19.46,-1.55,2.82); 
		glScalef(0.55, 0.50, 0.08);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
		glPopMatrix();
		
	    //  COJIN ESPALDAR 1
		glPushMatrix();
		glColor3f( 0.5, 0.4, 0.3);
	    glTranslatef(16,7.71,4.4); 
		glScalef(0.15, 0.45, 0.4);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
		glPopMatrix();
		//  COJIN ESPALDAR 2
		glPushMatrix();
		glColor3f( 0.5, 0.4, 0.3);
	    glTranslatef(16,7.-3.8,4.4); 
		glScalef(0.15, 0.45, 0.4);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
		glPopMatrix();
		//  COJIN ESPALDAR 3
		glPushMatrix();
		glColor3f( 0.5, 0.4, 0.3);
	    glTranslatef(16,7.-8.5,4.4); 
		glScalef(0.15, 0.49, 0.4);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
		glPopMatrix();
		
}

void mesa()
{//PATA 1
		glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(18,-9,1.2); 
		glScalef(0.02, 0.02, 0.2);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
		glPopMatrix();
		// PATA 2
		glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(21,-9,1.2); 
		glScalef(0.02, 0.02, 0.2);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
		glPopMatrix();
		// PATA 3
		glPushMatrix();
		glColor3f(0.34 ,0.10 ,0);
	    glTranslatef(18,-14,1.2); 
		glScalef(0.02, 0.02, 0.2);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
		glPopMatrix();
		// PATA 4
		glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(21,-14,1.2); 
		glScalef(0.02, 0.02, 0.2);
		glutSolidCube(10);
		glColor3f(0.34 ,0.10 ,0);
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();
		// BORDE 1
		glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(19.5,-9,2.2); 
		glScalef(0.5, 0.1, 0.005);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
		glPopMatrix();
		// BORDE 2
		glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(19.5,-14,2.2); 
		glScalef(0.5, 0.1, 0.005);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
		glPopMatrix();
			// BORDE 3
		glPushMatrix();
		glColor3f(0.34 ,0.10 ,0);
	    glTranslatef(21.6,-11.6,2.2); 
		glScalef(0.08, 0.5, 0.005);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
		glPopMatrix();
			// BORDE 4
		glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(17.4,-11.6,2.2); 
		glScalef(0.08, 0.5, 0.005);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
		glPopMatrix();
		
			// VIDRIO
		glPushMatrix();
		glColor3f( 1.0,1.0,1.0);
	    glTranslatef(19.5,-11.5,2.2); 
		glScalef(0.34, 0.40, 0.005);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
		glPopMatrix();
}

void paredes2 ()
{
	
//------PAREDES Y PISO DEL BAÑO----------------
//PISO
glBegin(GL_QUADS);
glColor3f(0.823, 0.796, 0.839);
glVertex3f(15, 35, 0.1);
glVertex3f(15, 65, 0.1);
glVertex3f(-15, 65, 0.1); 
glVertex3f(-15, 35, 0.1);
glEnd();

//--PARED ALFRENTE------

glBegin(GL_QUADS);
glColor3f(0.501, 0.639, 0.909);
glVertex3f(15, 35, 0.1);
glVertex3f(-15, 35, 0.1);
glVertex3f(-15, 35, 20); 
glVertex3f(15, 35, 20);
glEnd();

//--PARED FONDO------

glBegin(GL_QUADS);
glColor3f(0.501, 0.639, 0.909);
glVertex3f(15, 65, 0.1);
glVertex3f(-15, 65, 0.1);
glVertex3f(-15, 65, 20); 
glVertex3f(15, 65, 20);
glEnd();

//--PARED IZQUIERDA------

glBegin(GL_QUADS);
glColor3f(0.501, 0.639, 0.909);
glVertex3f(15, 35, 0.1);
glVertex3f(15, 65, 0.1);
glVertex3f(15, 65, 20); 
glVertex3f(15, 35, 20);
glEnd();

//--PARED DERECHA------ 
glBegin(GL_QUADS);
glColor3f(0.501, 0.639, 0.909);
glVertex3f(-15, 35, 0.1);
glVertex3f(-15, 65, 0.1);
glVertex3f(-15, 65, 20); 
glVertex3f(-15, 35, 20);
glEnd();

//TECHO

glBegin(GL_QUADS);
glColor3f(0.501, 0.639, 0.909);
glVertex3f(15, 35, 20);
glVertex3f(15, 65, 20);
glVertex3f(-15, 65, 20); 
glVertex3f(-15, 35, 20);
glEnd();

}

void vehiculo ()
{
glPushMatrix();
glTranslatef(posX,posY,posZ);
glRotated(angle,0.0,0.0,a);
glTranslatef(-2,0,0);
//chasis1
glPushMatrix();
glColor3f( 0.788 , 0.796 , 0.807 );
glBegin(GL_POLYGON);
glVertex3f(29.5, -27.5, 12);
glVertex3f(15.5, -27.5, 7);
glVertex3f(15.5, -27.5, 4);
glVertex3f(16, -27.5, 3);
glVertex3f(17, -27.5, 2);
glVertex3f(19, -27.5, 2);
glVertex3f(19.5, -27.5, 3);
glVertex3f(20, -27.5, 3.7);
glVertex3f(21.5, -27.5, 4);
glVertex3f(23, -27.5, 3.7);
glVertex3f(23.5, -27.5, 3);
glVertex3f(24, -27.5, 2);
glVertex3f(33.5, -27.5, 2);
glVertex3f(34, -27.5, 3);
glVertex3f(35, -27.5, 3.7);
glVertex3f(36.3, -27.5, 4);
glVertex3f(37.5, -27.5, 3.7);
glVertex3f(38, -27.5, 3);
glVertex3f(38.5, -27.5, 2);
glVertex3f(40, -27.5, 2.2);
glVertex3f(42, -27.5, 3);
glVertex3f(43.5, -27.5, 4);
glVertex3f(43.5, -27.5, 8);
glEnd();
/*conexion1
glVertex3f(44.5, -30, 4);
glVertex3f(44.5, -37.5, 4);*/
//chasis2
glBegin(GL_POLYGON);
glColor3f( 0.788 , 0.796 , 0.807 );
glVertex3f(29.5, -40, 12);
glVertex3f(43.5, -40, 8);
glVertex3f(43.5, -40, 4);
glVertex3f(42, -40, 3);
glVertex3f(40, -40, 2.2);
glVertex3f(38.5, -40, 2);
glVertex3f(38, -40, 3);
glVertex3f(37.5, -40, 3.7);
glVertex3f(36.3, -40, 4);
glVertex3f(35, -40, 3.7);
glVertex3f(34, -40, 3);
glVertex3f(33.5, -40, 2);
glVertex3f(24, -40, 2);
glVertex3f(23.5, -40, 3);
glVertex3f(23, -40, 3.7);
glVertex3f(21.5, -40, 4);
glVertex3f(20, -40, 3.7);
glVertex3f(19.5, -40, 3);
glVertex3f(19, -40, 2);
glVertex3f(17, -40, 2);
glVertex3f(16, -40, 3);
glVertex3f(15.5, -40, 4);
glVertex3f(15.5, -40, 7);
/*conexion2
glVertex3f(15.2, -37.5, 4);
glVertex3f(15.2, -30, 4);*/

glEnd();
glPopMatrix();

//rueda1
glPushMatrix();
glColor3f( 0 , 0 , 0);
gluQuadricDrawStyle(cilindro,GLU_FILL);
glTranslatef(21.5, -27, 2);
glRotated(90,1.0,0.0,0.0);
gluCylinder(cilindro,2,2,1,20,20);
glEnd();
glPopMatrix();


//circulo1 rueda1
glPushMatrix(); 
glTranslatef(17.5, -28, -2);
glScalef(2, 2, 2);      
glBegin(GL_POLYGON);
glColor3f( 0 , 0 , 0);
for(float i=0;i<10;i+=0.01){
	calx=radio+cos(i);
	calz=radio+sin(i);
	glVertex3f(calx,0,calz);
}
glEnd();
glPopMatrix();

//circulo2 rueda1
glPushMatrix(); 
glTranslatef(17.5, -27, -2);
glScalef(2, 2, 2);      
glBegin(GL_POLYGON);
glColor3f( 0 , 0 , 0);
for(float i=0;i<10;i+=0.01){
	calx=radio+cos(i);
	calz=radio+sin(i);
	glVertex3f(calx,0,calz);
	
}
glEnd();
glPopMatrix(); 


 
//rueda2
glPushMatrix();
glColor3f( 0 , 0 , 0);
gluQuadricDrawStyle(cilindro,GLU_FILL);
glTranslatef(36, -27, 2);
glRotated(90,1.0,0.0,0.0);
gluCylinder(cilindro,2,2,1,20,20);
glEnd();
glPopMatrix();

//circulo1 rueda2
glPushMatrix(); 
glTranslatef(32, -28, -2);
glScalef(2, 2, 2);      
glBegin(GL_POLYGON);
glColor3f( 0 , 0 , 0);
for(float i=0;i<10;i+=0.01){
	calx=radio+cos(i);
	calz=radio+sin(i);
	glVertex3f(calx,0,calz);
}
glEnd();
glPopMatrix();


//circulo2 rueda2
glPushMatrix(); 
glTranslatef(32, -27, -2);
glScalef(2, 2, 2);      
glBegin(GL_POLYGON);
glColor3f( 0 , 0 , 0);
for(float i=0;i<10;i+=0.01){
	calx=radio+cos(i);
	calz=radio+sin(i);
	glVertex3f(calx,0,calz);
	
}
glEnd();
glPopMatrix(); 

//rueda3
glPushMatrix();
glColor3f( 0 , 0 , 0);
gluQuadricDrawStyle(cilindro,GLU_FILL);
glTranslatef(21.5, -39.5, 2);
glRotated(90,1.0,0.0,0.0);
gluCylinder(cilindro,2,2,1,20,20);
glEnd();
glPopMatrix();


//circulo1 rueda3
glPushMatrix(); 
glTranslatef(17.5, -40.5, -2);
glScalef(2, 2, 2);      
glBegin(GL_POLYGON);
glColor3f( 0 , 0 , 0);
for(float i=0;i<10;i+=0.01){
	calx=radio+cos(i);
	calz=radio+sin(i);
	glVertex3f(calx,0,calz);
}
glEnd();
glPopMatrix();

//circulo2 rueda3
glPushMatrix(); 
glTranslatef(17.5, -39.5, -2);
glScalef(2, 2, 2);      
glBegin(GL_POLYGON);
glColor3f( 0 , 0 , 0);
for(float i=0;i<10;i+=0.01){
	calx=radio+cos(i);
	calz=radio+sin(i);
	glVertex3f(calx,0,calz);
	
}
glEnd();
glPopMatrix(); 




//rueda4
glPushMatrix();
glColor3f( 0 , 0 , 0);
gluQuadricDrawStyle(cilindro,GLU_FILL);
glTranslatef(36, -39.5, 2);
glRotated(90,1.0,0.0,0.0);
gluCylinder(cilindro,2,2,1,20,20);
glEnd();
glPopMatrix();

//circulo1 rueda2
glPushMatrix(); 
glTranslatef(32, -40.5, -2);
glScalef(2, 2, 2);      
glBegin(GL_POLYGON);
glColor3f( 0 , 0 , 0);
for(float i=0;i<10;i+=0.01){
	calx=radio+cos(i);
	calz=radio+sin(i);
	glVertex3f(calx,0,calz);
}
glEnd();
glPopMatrix();


//circulo2 rueda2
glPushMatrix(); 
glTranslatef(32, -39.5, -2);
glScalef(2, 2, 2);      
glBegin(GL_POLYGON);
glColor3f( 0 , 0 , 0);
for(float i=0;i<10;i+=0.01){
	calx=radio+cos(i);
	calz=radio+sin(i);
	glVertex3f(calx,0,calz);
	
}
glEnd();
glPopMatrix(); 
//No tocar ni yo se que es,tenia sueño
glBegin(GL_QUADS);
glColor3f( 0.788 , 0.796 , 0.807 );
glVertex3f(15.5, -27.5, 7);
glVertex3f(15.2, -30, 6);
glVertex3f(15.2, -30, 4);
glVertex3f(15.5, -27.5, 4);
glEnd();

glBegin(GL_QUADS);
glColor3f( 0.788 , 0.796 , 0.807 );
glVertex3f(15.2, -38.5, 6);
glVertex3f(15.5, -40, 7);
glVertex3f(15.5, -40, 4);
glVertex3f(15.2, -38.5, 4);
glEnd();

glBegin(GL_QUADS);
glColor3f( 0.788 , 0.796 , 0.807 );
glVertex3f(15.2, -30, 6);
glVertex3f(15.2, -30, 4);
glVertex3f(15.2, -38.5, 4);
glVertex3f(15.2, -38.5, 6);
glEnd();

glBegin(GL_QUADS);
glColor3f( 1, 0, 0 );
glVertex3f(15.5, -27.5, 7);
glVertex3f(15.2, -30, 6);
glVertex3f(15.2, -38.5, 6);
glVertex3f(15.5, -40, 7);
glEnd();

glBegin(GL_QUADS);
glColor3f( 0.788 , 0.796 , 0.807 );
glVertex3f(15.5, -27.5, 7);
glVertex3f(15.5, -40, 7);
glVertex3f(21.6, -40, 9);
glVertex3f(21.6, -27.5, 9);
glEnd();


glBegin(GL_QUADS);
glColor3f( 0.490 , 0.549 , 0.619 );
glVertex3f(29.5, -27.5, 12);
glVertex3f(29.5, -40, 12);
glVertex3f(21.6, -40, 9);
glVertex3f(21.6, -27.5, 9);
glEnd();

glBegin(GL_QUADS);
glColor3f( 0.490 , 0.549 , 0.619 );
glVertex3f(29.5, -27.5, 12);
glVertex3f(29.5, -40, 12);
glVertex3f(36.3, -40, 10);
glVertex3f(36.3, -27.5, 10);
glEnd();

glBegin(GL_QUADS);
glColor3f( 0.788 , 0.796 , 0.807 );
glVertex3f(36.3, -40, 10);
glVertex3f(36.3, -27.5, 10);
glVertex3f(43.5, -27.5, 8);
glVertex3f(43.5, -40, 8);

glEnd();


//parte de atras creo que se llama asi deah

glBegin(GL_QUADS);
glColor3f( 0.788 , 0.796 , 0.807 );
glVertex3f(43.5, -40, 8);
glVertex3f(44.5, -37.5, 8);
glVertex3f(44.5, -30, 8);
glVertex3f(43.5, -27.5, 8);
glEnd();

glBegin(GL_QUADS);
glColor3f( 0.788 , 0.796 , 0.807 );
glVertex3f(43.5, -40, 8);
glVertex3f(44.5, -37.5, 8);
glVertex3f(44.5, -37.5, 4);
glVertex3f(43.5, -40, 4);
glEnd();

glBegin(GL_QUADS);
glColor3f( 0.788 , 0.796 , 0.807 );
glVertex3f(43.5, -27.5, 8);
glVertex3f(43.5, -27.5, 4);
glVertex3f(44.5, -30, 4);
glVertex3f(44.5, -30, 8);
glEnd();

glBegin(GL_QUADS);
glColor3f( 0.788 , 0.796 , 0.807 );
glVertex3f(44.5, -37.5, 8);
glVertex3f(44.5, -37.5, 4);
glVertex3f(44.5, -30, 4);
glVertex3f(44.5, -30, 8);
glEnd();


//parte de abajo
glBegin(GL_POLYGON);
glColor3f( 0, 0 , 0);
glVertex3f(38.5, -27.5, 2);
glVertex3f(40, -27.5, 2.2);
glVertex3f(42, -27.5, 3);
glVertex3f(43.5, -27.5, 4);

glVertex3f(44.5, -30, 4);
glVertex3f(44.5, -37.5, 4);
glVertex3f(43.5, -40, 4);
glVertex3f(42, -40, 3);

glVertex3f(40, -40, 2.2);
glVertex3f(38.5, -40, 2);
glEnd();

//1
glBegin(GL_QUADS);
glColor3f( 0, 0 , 0);
glVertex3f(38.5, -27.5, 2);
glVertex3f(38.5, -40, 2);
glVertex3f(38, -40, 3);
glVertex3f(38, -27.5, 3);

glVertex3f(38, -40, 3);
glVertex3f(38, -27.5, 3);
glVertex3f(37.5, -27.5, 3.7);
glVertex3f(37.5, -40, 3.7);

glVertex3f(37.5, -27.5, 3.7);
glVertex3f(37.5, -40, 3.7);
glVertex3f(36, -40, 4);
glVertex3f(36, -27.5, 4);

glVertex3f(36, -40, 4);
glVertex3f(36, -27.5, 4);
glVertex3f(35, -27.5, 3.7);
glVertex3f(35, -40, 3.7);

glVertex3f(35, -27.5, 3.7);
glVertex3f(35, -40, 3.7);
glVertex3f(34, -40, 3);
glVertex3f(34, -27.5, 3);

glVertex3f(34, -40, 3);
glVertex3f(34, -27.5, 3);
glVertex3f(33.5, -27.5, 2);
glVertex3f(33.5, -40, 2);

//conexion
glVertex3f(33.5, -40, 2);
glVertex3f(33.5, -27.5, 2);
glVertex3f(24, -27.5, 2);
glVertex3f(24, -40, 2);

//2

glVertex3f(24, -27.5, 2);
glVertex3f(24.5, -40, 2);
glVertex3f(23.5, -40, 3);
glVertex3f(23.5, -27.5, 3);

glVertex3f(23.5, -40, 3);
glVertex3f(23.5, -27.5, 3);
glVertex3f(23, -27.5, 3.7);
glVertex3f(23, -40, 3.7);

glVertex3f(23, -27.5, 3.7);
glVertex3f(23, -40, 3.7);
glVertex3f(21.5, -40, 4);
glVertex3f(21.5, -27.5, 4);

glVertex3f(21.5, -40, 4);
glVertex3f(21.5, -27.5, 4);
glVertex3f(20, -27.5, 3.7);
glVertex3f(20, -40, 3.7);

glVertex3f(20, -27.5, 3.7);
glVertex3f(20, -40, 3.7);
glVertex3f(19.5, -40, 3);
glVertex3f(19.5, -27.5, 3);

glVertex3f(19.5, -40, 3);
glVertex3f(19.5, -27.5, 3);
glVertex3f(19, -27.5, 2);
glVertex3f(19, -40, 2);

glVertex3f(19, -27.5, 2);
glVertex3f(19, -40, 2);
glVertex3f(17, -40, 2);
glVertex3f(17, -27.5, 2);

glVertex3f(17, -40, 2);
glVertex3f(17, -27.5, 2);
glVertex3f(16, -27.5, 3);
glVertex3f(16, -40, 3);
glEnd();

glBegin(GL_POLYGON);
glColor3f( 0, 0 , 0);
glVertex3f(16, -27.5, 3);
glVertex3f(16, -40, 3);
glVertex3f(15.5, -40, 4);
glVertex3f(15.2, -38.5, 4);
glVertex3f(15.2, -30, 4);
glVertex3f(15.5, -27.5, 4);
glEnd();
//ventana1
glBegin(GL_QUADS);
glColor3f( 0, 0 , 0);
glVertex3f(33, -27.49, 8);
glVertex3f(33, -27.49, 10);
glVertex3f(29.5, -27.49, 11.9);
glVertex3f(20, -27.49, 7.6);
glEnd();
//ventana2
glBegin(GL_QUADS);
glColor3f( 0, 0 , 0);
glVertex3f(33, -40.01, 8);
glVertex3f(33, -40.01, 10);
glVertex3f(29.5, -40.01, 11.9);
glVertex3f(20, -40.01, 7.6);
glEnd();
glPopMatrix();
}

void paredDerechaFondo() {
	glPushMatrix();
	
	glColor3f(0.63, 0.63, 0.63);
	glTranslatef(-5.21, -1.95, 0.0);
	glScalef(0.04, 0.65, 1.0);
	glutSolidCube(10);
	glColor3f(0.0f, 0.0f, 0.0f);
	LineaCubo(1.5);

	glPopMatrix();
}

void paredIzquierdaFondo() {
	glPushMatrix();
	
	glColor3f(0.63, 0.63, 0.63);
	glTranslatef(0.0, -1.95, -5.21);
	glScalef(1.0, 0.65, 0.04);
	glutSolidCube(10);
	glColor3f(0.0f, 0.0f, 0.0f);
	LineaCubo(1.5);

	glPopMatrix();
}

void PisoCuarto(){
	glPushMatrix();
		glColor3f(0.87f, 0.87f, 0.87f);
		glTranslatef(0.0, -5.0, 0.0);
		glScalef(1.0, 0.04, 1.0);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1.5);
		glEnd();
	glPopMatrix();	
}

void ruedaSilla(float x, float y, float z) {
	glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(x, y, z);
		glutSolidSphere(0.07, 100, 5);
	glPopMatrix();
}

void pataSilla(float x, float y, float z, float ang) {
	glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(x, y, z);
		glRotatef(ang, 0.0, 1.0, 0.0);
		glScalef(1.0, 1.0, -3.1);
		glutSolidCube(0.11);
		glScalef(0.011, 0.011, 0.011);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1.5);			
	glPopMatrix();
}

void ejeSilla() {
	glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(-2.975, -4.81, 1.7);
		glutSolidSphere(0.12, 10, 10);
	glPopMatrix();
}

void paloSilla() {
	glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(-2.975, -4.35, 1.7);
		glScalef(0.1, 0.65, 0.1);
		glutSolidCube(1);
		glScalef(0.1, 0.1, 0.1);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1.5);			
	glPopMatrix();
}

void asiento() {
	glPushMatrix();
		glColor3f(0.84, 0.84, 0.84);
		glTranslatef(-2.975, -4, 1.7);
		glRotatef(40, 0.0, 1.0, 0.0);
		glScalef(3.5, 1.0, 3.5);
		glutSolidCube(0.2);
		glScalef(0.02, 0.02, 0.02);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1.5);			
	glPopMatrix();
}

void respaldar() {
	glPushMatrix();
		glColor3f(0.84, 0.84, 0.84);
		glTranslatef(-2.7, -3.4, 1.45);
		glRotatef(130, 0.0, 1.0, 0.0);
		glScalef(3.5, 6.9, 1.0);
		glutSolidCube(0.2);
		glScalef(0.02, 0.02, 0.02);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1.5);			
	glPopMatrix();
}

void posaBrazos(float x, float y, float z) {
	glPushMatrix();
		glColor3f(0.1, 0.1, 0.1);
		glTranslatef(x, y, z);
		glRotatef(130, 0.0, 1.0, 0.0);
		glScalef(0.2, 0.1, 1.0);
		glutSolidCube(0.5);
		glScalef(0.05, 0.05, 0.05);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1.5);			
	glPopMatrix();
}

void paloPosaBrazos(float x, float y, float z) {
	glPushMatrix();
		glColor3f(0.1, 0.1, 0.1);
		glTranslatef(x, y, z);
		glRotatef(130, 0.0, 1.0, 0.0);
		glRotatef(90, 1.0, 0.0, 0.0);
		glScalef(0.2, 0.1, 1.0);
		glutSolidCube(0.5);
		glScalef(0.05, 0.05, 0.05);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1.5);			
	glPopMatrix();
}
//
void SillaGamer() {
	glPushMatrix();
	
	glScalef(1.8, 1.8, 1.8);
	
		///////////////////////////////////////////////////// RUEDAS SILLA ////////////////////////////////////////////////////////////////////////////////
		ruedaSilla(-3.01, -4.93, 2.1);
		ruedaSilla(-3.3, -4.93, 1.7);
		ruedaSilla(-3.01, -4.93, 1.3);
		ruedaSilla(-2.65, -4.93, 1.49);
		ruedaSilla(-2.65, -4.93, 1.91);
		
		//////////////////////////////////////////////////// EJE DE LA SILLA  //////////////////////////////////////////////////////////////////////////////////
		ejeSilla();
		
		///////////////////////////////////////////////////// PATAS SILLA ///////////////////////////////////////////////////////////////////////////////////
		pataSilla(-3, -4.81, 2, -8);
		pataSilla(-3.2, -4.81, 1.7, 90);
		pataSilla(-3, -4.81, 1.4, 8);
		pataSilla(-2.75, -4.81, 1.53, -60);
		pataSilla(-2.75, -4.81, 1.87, 60);
		
		///////////////////////////////////////////////////// PALO SILLA /////////////////////////////////////////////////////////////////////////////
		paloSilla();
		
		/////////////////////////////////////////////////////// ASIENTO SILLA //////////////////////////////////////////////////////////////////////////
		asiento();
		
		/////////////////////////////////////////////////////// RESPALDAR SILLA ////////////////////////////////////////////////////////////////////////
		respaldar(); 
		
		/////////////////////////////////////////////////////// POSA BRAZOS ///////////////////////////////////////////////////////////////////////////
		posaBrazos(-2.75, -3.5, 1.95);
		posaBrazos(-3.2, -3.5, 1.4);
		paloPosaBrazos(-2.75, -3.75, 1.95);
		paloPosaBrazos(-3.2, -3.75, 1.4);	
		
	glPopMatrix();
}

void Escritorio(){
	glPushMatrix();
	glScalef(0.8, 1.0, 0.7);
	
	///////////////////////////////////////////// MESA ESCRITORIO ////////////////////////////////////////////////////////
	glPushMatrix();
		glColor3f(0.39f, 0.32f, 0.27f);
		glTranslatef(-3.95, -2.75, -2.0);
		glScalef(0.2, 0.01, 0.6);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1.5);		
		glEnd();
	glPopMatrix();	
	
	///////////////////////////////////////////// CAJON 1 ////////////////////////////////////////////////////////
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(-3.8, -3.2, 0.15);
		glScalef(0.18, 0.05, 0.13);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1.5);		
		glEnd();
	glPopMatrix();
		
	///////////////////////////////////////////// CAJON 2 ////////////////////////////////////////////////////////
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(-3.8, -3.8, 0.15);
		glScalef(0.18, 0.05, 0.13);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1.5);		
		glEnd();
	glPopMatrix();
			
	///////////////////////////////////////////// CAJON 3 ////////////////////////////////////////////////////////
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(-3.8, -4.4, 0.15);
		glScalef(0.18, 0.05, 0.13);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1.5);		
		glEnd();
	glPopMatrix();
	
	///////////////////////////////////////////// CAJONES GENERAL ESCRITORIO ////////////////////////////////////////////////////////
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(-3.95, -3.8, 0.15);
		glScalef(0.2, 0.195, 0.15);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1.5);		
		glEnd();
	glPopMatrix();	
	
	///////////////////////////////////////////// PATA ESCRITORIO ////////////////////////////////////////////////////////
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(-3.95, -3.8, -4.88);
		glScalef(0.2, 0.195, 0.01);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1.5);		
		glEnd();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-2.3, 1.0, -6.15);
	glScalef(0.5, 1.1, 1.8);

		//////////////////////////////////////////////////////////////// MONITOR 1 MARCO /////////////////////////////////////////////////////////////////////////////////////
		glPushMatrix();
		
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(-4.81, -2.7, 1.4);
		glScalef(0.01, 0.11, 0.11);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
		
		glPopMatrix();
	
		//////////////////////////////////////////////////////////////// MONITOR 1 /////////////////////////////////////////////////////////////////////////////////////
		glPushMatrix();
		
		glColor3f( 0.529 , 0.807 , 0.921 );
		glTranslatef(-4.8, -2.7, 1.4);
		glScalef(0.01, 0.1, 0.1);
		glutSolidCube(10);
		glColor3f(135, 206, 235);
		LineaCubo(1);	
		glEnd ();	
		
		glPopMatrix();

		//////////////////////////////////////////////////////////////// MONITOR 2 MARCO /////////////////////////////////////////////////////////////////////////////////////
		
		glPushMatrix();
		
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(-4.57, -2.7, 2.5);
		glRotatef(40, 0.0, 1.0, 0.0);
		glScalef(0.009, 0.11, 0.11);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);		
		glEnd();
		
		glPopMatrix();
		
		//////////////////////////////////////////////////////////////// MONITOR 2 /////////////////////////////////////////////////////////////////////////////////////
		
		glPushMatrix();
		
		glColor3f( 0.529 , 0.807 , 0.921 );
		glTranslatef(-4.56, -2.7, 2.5);
		glRotatef(40, 0.0, 1.0, 0.0);
		glScalef(0.01, 0.1, 0.1);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);		
		glEnd ();
		glPopMatrix();
		
		//////////////////////////////////////////////////////////////// RACK 1 /////////////////////////////////////////////////////////////////////////////////////
				
		glPushMatrix();
		
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(-5.1, -2.9, 1.4);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glScalef(0.2, 0.05, 0.05);
		cilindro = gluNewQuadric();
		gluQuadricDrawStyle(cilindro,GLU_FILL);
		gluCylinder(cilindro,1,1,10,20,20);
		
		glPopMatrix();						
		
		//////////////////////////////////////////////////////////////// RACK 2 /////////////////////////////////////////////////////////////////////////////////////
				
		glPushMatrix();
		
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(-4.8, -2.9, 2.5);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glScalef(0.2, 0.05, 0.05);
		cilindro = gluNewQuadric();
		gluQuadricDrawStyle(cilindro,GLU_FILL);
		gluCylinder(cilindro,1,1,10,20,20);	
		
		glPopMatrix();
		
		
		glPopMatrix();
			////////////////////////////////////////////////////////////////////////////// TECLADO //////////////////////////////////////////////////////////////////////////////////////
	
	glPushMatrix();
	
	glColor3f(0.59f, 0.6f, 0.6f);
	glTranslatef(-4.0, -2.63, -3.75);
	glRotatef(90, 0.0, 1.0, 0.0);
	glScalef(0.13, 0.006, 0.05);
	glutSolidCube(10);
	glColor3f(0.0f, 0.0f, 0.0f);
	LineaCubo(1.5);	
	
	glPopMatrix();

		glPushMatrix();
		
		glColor3f(0.08, 0.08, 0.08);
		glTranslatef(-4.98, -1.8, -2.5);
		glScalef(0.002, 0.15, 0.435);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1.5);
		
		glPopMatrix();
	
	////////////////////////////////////////////////////////////////////////////// MOUSE PAD ///////////////////////////////////////////////////////////////////////////////////////
	
	glPushMatrix();
	
	glColor3f(0.5f, 0.49f, 0.48f);
	glTranslatef(-4.0, -2.67, -3.5);
	glRotatef(90, 0.0, 1.0, 0.0);
	glScalef(0.2, 0.001, 0.1);
	glutSolidCube(10);
	glColor3f(0.0f, 0.0f, 0.0f);
	LineaCubo(1.5);	
	
	glPopMatrix();	
	glPopMatrix();
}

void TV(){
	
	///////////////////////////////////////////// TV //////////////////////////////////////////////////////////////////////
	glPushMatrix();
	
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(-4.95, -0.9, 2.4);
		glScalef(0.0078, 0.25, 0.41);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1.5);

	glPopMatrix();
		
	///////////////////////////////////////////// TV DISPLAY //////////////////////////////////////////////////////////////////////
	glPushMatrix();
	
		glColor3f( RED1, GREEN1, BLUE1 );
		glTranslatef(-4.95, -0.9, 1.0);//(-4.95, -0.9, 2.4)
		glScalef(0.008, 0.23, 0.095);//glScalef(0.008, 0.23, 0.39)
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1.5);

	glPopMatrix();

    glPushMatrix();
	
		glColor3f( RED2, GREEN2, BLUE2 );
		glTranslatef(-4.95, -0.9, 1.95);
		glScalef(0.008, 0.23, 0.095);//glScalef(0.008, 0.23, 0.39)
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1.5);

	glPopMatrix();

    glPushMatrix();
	
		glColor3f( RED3, GREEN3, BLUE3 );
		glTranslatef(-4.95, -0.9, 2.9);
		glScalef(0.008, 0.23, 0.095);//glScalef(0.008, 0.23, 0.39)
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1.5);

	glPopMatrix();
    glPushMatrix();
	
		glColor3f( RED4, GREEN4, BLUE4 );
		glTranslatef(-4.95, -0.9, 3.85);
		glScalef(0.008, 0.23, 0.095);//glScalef(0.008, 0.23, 0.39)
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1.5);

	glPopMatrix();
	//ImagenTV();		
	
	///////////////////////////////////////////// TV //////////////////////////////////////////////////////////////////////
	glPushMatrix();
		
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(-4.96, -2.5, 2.4);
		glRotatef(90, 1.0, 0.0, 0.0);
		glScalef(0.01, 0.3, 0.01);//glScalef(0.01, 0.3, 0.01)
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1.5);
	glPopMatrix();
	
}

void Puerta(){
	glPushMatrix();
	glTranslatef(-0.5, 0.9, -6.05);
	glScalef(0.5, 1.1, 1.7);
	
	 	//////////////////////////////////////////////////////////////// puerta/////////////////////////////////////////////////////////////////////////////////////
		glPushMatrix();
		
		glColor3f( 0.364 , 0.223 , 0.082 );;
		glTranslatef(0.90, -3.0, 0.5);
		glScalef(0.5, 0.48, 0.028);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
		
		
		
		glPopMatrix();
		
		//////////////////////////////////////////////////////////////// *puerta/////////////////////////////////////////////////////////////////////////////////////
		glPushMatrix();
		
		glColor3f( 0.364 , 0.223 , 0.082 );
		glTranslatef(0.1, -1.5, 0.5);//moviemiento
		glScalef(0.1, 0.06, 0.028);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(8);	
		glEnd ();	
		
		glPopMatrix();
		
		//////////////////////////////////////////////////////////////// *puerta/////////////////////////////////////////////////////////////////////////////////////
		glPushMatrix();
		
		glColor3f( 0.364 , 0.223 , 0.082 );
		glTranslatef(0.1, -3.0, 0.5);//moviemiento
		glScalef(0.1, 0.09, 0.028);//figura
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(8);	
		glEnd ();	
		
		glPopMatrix();		
		
		//////////////////////////////////////////////////////////////// *puerta/////////////////////////////////////////////////////////////////////////////////////
		glPushMatrix();
		
		glColor3f( 0.364 , 0.223 , 0.082 );
		glTranslatef(0.1, -4.5, 0.5);//moviemiento
		glScalef(0.1, 0.09, 0.028);//figura
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(8);	
		glEnd ();	
		
		glPopMatrix();
		
		//////////////////////////////////////////////////////////////// *puerta/////////////////////////////////////////////////////////////////////////////////////
		glPushMatrix();
		
		glColor3f( 0.364 , 0.223 , 0.082 );
		glTranslatef(1.9, -1.5, 0.5);//moviemiento
		glScalef(0.1, 0.06, 0.028);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(8);	
		glEnd ();	
		
		glPopMatrix();
		
		//////////////////////////////////////////////////////////////// *puerta/////////////////////////////////////////////////////////////////////////////////////
		glPushMatrix();
		
		glColor3f( 0.364 , 0.223 , 0.082 );
		glTranslatef(1.9, -3.0, 0.5);//moviemiento
		glScalef(0.1, 0.09, 0.028);//figura
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(8);	
		glEnd ();	
		
		glPopMatrix();
		
		//////////////////////////////////////////////////////////////// *puerta/////////////////////////////////////////////////////////////////////////////////////
		glPushMatrix();
		
		glColor3f( 0.364 , 0.223 , 0.082 );
		glTranslatef(1.9, -4.5, 0.5);//moviemiento
		glScalef(0.1, 0.09, 0.028);//figura
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(8);	
		glEnd ();	
		
		glPopMatrix();
	
	glPopMatrix();
}

void caLateral()
{
	
	// Propiedades del material

// "Limpiamos" el frame buffer con el color de "Clear", en este color negro
// Aqu? va, verificarlo en el repintado
// Rotacion de 20 grados en torno al eje x
glPushMatrix();
glScalef(0.3,0.3,0.3);
glTranslatef(0.0,-6.3,-0.4);
glRotated(90.0, 0.0, 1.0, 0.0);

glPushMatrix();
glScalef(1.5,0.7,0.03);
glColor4f(0.094f, 0.023f, 0.0f, 1.0f);
glutSolidCube(10);
glPopMatrix();

///////////////////////////////////////////////////////////////////////////////////////////
glPushMatrix();
// BASE //////////////////////////////////////////////////////////////////////////////////
//glScalef(1.5,0.7,0.05);
glColor4f(0.094f, 0.023f, 0.0f, 1.0f);//red
glTranslatef(0,-2.8,-10);
glScalef(1.5,0.15,2);
//glTranslatef();
glutSolidCube(10);
glPopMatrix();
/////////////////////////////////////////////////////////////////////////////////////////////

glPushMatrix();
glColor4f(0.250f, 0.250f, 0.250f,  1.0f);//red
// COLCHON /////////////////////////////////////////////////////////////////////////////////
//glScalef(1.5,0.7,0.05);
//(GL_FRONT, GL_AMBIENT, mat_ambient);
//(GL_FRONT, GL_DIFFUSE, mat_plomo);

glTranslatef(0,-0.5,-10);
glScalef(1.47,0.3,2);
//glTranslatef();
glutSolidCube(10);
glPopMatrix();
////////////////////////////////////////////////////////////////////////////////////////////

glPushMatrix();
glColor4f(0.501f, 0.501f, 0.501f,  1.0f);//red
// CABECERA DERECHA ////////////////////////////////////////////////////////////////////////
glTranslatef(0.5,1,-2.3);
//glTranslatef(0,-0.5,-10);
glScalef(1.3,0.1,0.9);
//glTranslatef();
//glutSolidCube(10);
glRotated(90, 0,1,0);
cilindro = gluNewQuadric();
gluQuadricDrawStyle(cilindro,GLU_FILL);
gluCylinder(cilindro,2,2,5,50,50);
//glTranslatef();
//glutSolidCube(10);
glPopMatrix();
/////////////////////////////////////////////////////////////////////////////////////////////

glPushMatrix();
glColor4f(0.501f, 0.501f, 0.501f,  1.0f);//red
// CABECERA IZQUIERDA ////////////////////////////////////////////////////////////////////////
glTranslatef(-6.9,1,-2.3);
//glTranslatef(0,-0.5,-10);
glScalef(1.3,0.1,0.9);
//glTranslatef();
//glutSolidCube(10);
glRotated(90, 0,1,0);
cilindro = gluNewQuadric();
gluQuadricDrawStyle(cilindro,GLU_FILL);
gluCylinder(cilindro,2,2,5,50,50);
glPopMatrix();
///////////////////////////////////////////////////////////////////////////////////////////////
glPopMatrix();



}

void sofa()
{
	// Propiedades del material

	// "Limpiamos" el frame buffer con el color de "Clear", en este color negro
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Aqu? va, verificarlo en el repintado
	// Rotacion de 20 grados en torno al eje x
	
	glPushMatrix();
	//glTranslatef(-20,1,9);
		glScalef(0.17,0.16,0.15);

		//glRotated(10.0, 0.0, 0.0, 0.0);
		// Rotacion de -30 grados en torno al eje y
		//glRotated(15, 1.0, 1.0, 0.0);
		glTranslatef(-19.0, 2.6,6.0);
		// LATERAL ///////////////////////////////////////////////////////////////
		//Aplicando el setMaterial

		glPushMatrix();
	
			glColor4f(0.376f, 0.376f, 0.376f, 1.0f);//red
			glScalef(1.9,1.3,0.2);
			glutSolidCube(10);
			glColor3f(0.0f, 0.0f, 0.0f);
			LineaCubo(1.5);
		glPopMatrix();
		///////////////////////////////////////////////////////////////////////

		glPushMatrix();
			glColor4f(0.25f, 0.25f, 0.25f, 1.0f);
			// BASE //////////////////////////////////////////////////////////////
			glTranslatef(0,-4.99,7.1);
			glScalef(1.9,0.3,1.2);
			glutSolidCube(10);
			glColor3f(0.0f, 0.0f, 0.0f);
			LineaCubo(1.5);
		glPopMatrix();
		/////////////////////////////////////////////////////////////////////

		//glPopMatrix();
		///////////////////////////////////////////////////////////////////////
		glPushMatrix();
			//(GL_FRONT, GL_DIFFUSE, mat_marron);
			glColor4f(0.25f, 0.25f, 0.25f, 1.0f);
			// BRACERA DERECHA ///////////////////////////////////////////////////////
			glTranslatef(9.9,1,7);
			glScalef(0.09,0.05,1.6);
        glutSolidCube(10);
        glPopMatrix();
        ////////////////////////////////////////////////////////////////////////

        glPushMatrix();
        glColor4f(0.245f, 0.08f, 0.2f, 2.0f);//
        // BRACERA IZQUIERDA /////////////////////////////////////////////////////////
        glTranslatef(-9.9,1,7);
        glScalef(0.09,0.05,1.6);
        glutSolidCube(10);
        glPopMatrix();
        ////////////////////////////////////////////////////////////////////////

        glPushMatrix();
        glColor4f(0.245f, 0.08f, 0.2f, 2.0f);//
        // PATAS delantea IZQUIERDA /////////////////////////////////////////////////////////
        glTranslatef(-9.9,-4.67,12.7);
        glScalef(0.09,1.08,0.06);
        glutSolidCube(10);
        glPopMatrix();
        ////////////////////////////////////////////////////////////////////////

        glPushMatrix();
        glColor4f(0.245f, 0.08f, 0.2f, 2.0f);//
        // PATAS delantera DERECHA /////////////////////////////////////////////////////////
        glTranslatef(9.9,-4.67,12.7);
        glScalef(0.09,1.08,0.06);
        glutSolidCube(10);
        glPopMatrix();
        ////////////////////////////////////////////////////////////////////////

        glPushMatrix();
        glColor4f(0.245f, 0.08f, 0.2f, 2.0f);//
        // PATAS TRASERA IZQUIERDA /////////////////////////////////////////////////////////
        glTranslatef(-9.9,-4.67,0.3);
        glScalef(0.09,1.08,0.06);
        glutSolidCube(10);
        glPopMatrix();
        ////////////////////////////////////////////////////////////////////////

        glPushMatrix();
        glColor4f(0.245f, 0.08f, 0.2f, 2.0f);//
        // PATAS TRASERA DERERCHA /////////////////////////////////////////////////////////
        glTranslatef(9.9,-4.67,0.3);
        glScalef(0.09,1.08,0.06);
        glutSolidCube(10);
        glPopMatrix();
        glPopMatrix();
        ////////////////////////////////////////////////////////////////////////
        //glPopMatrix();
        //glFlush();
}

///////////////////////////////////////// BAÑO ////////////////////////////////////////////
void cal ()
{
	
//------PAREDES Y PISO DEL BAÑO----------------
//PISO
glBegin(GL_QUADS);
glColor3f(0.823, 0.796, 0.839);
glVertex3f(15, 35, 0.1);
glVertex3f(15, 65, 0.1);
glVertex3f(-15, 65, 0.1); 
glVertex3f(-15, 35, 0.1);
glEnd();

//--PARED ALFRENTE------

glBegin(GL_QUADS);
glColor3f(0.501, 0.639, 0.909);
glVertex3f(15, 35, 0.1);
glVertex3f(-15, 35, 0.1);
glVertex3f(-15, 35, 20); 
glVertex3f(15, 35, 20);
glEnd();

//--PARED FONDO------

glBegin(GL_QUADS);
glColor3f(0.501, 0.639, 0.909);
glVertex3f(15, 65, 0.1);
glVertex3f(-15, 65, 0.1);
glVertex3f(-15, 65, 20); 
glVertex3f(15, 65, 20);
glEnd();

//--PARED IZQUIERDA------

glBegin(GL_QUADS);
glColor3f(0.501, 0.639, 0.909);
glVertex3f(15, 35, 0.1);
glVertex3f(15, 65, 0.1);
glVertex3f(15, 65, 20); 
glVertex3f(15, 35, 20);
glEnd();

//--PARED DERECHA------ 
glBegin(GL_QUADS);
glColor3f(0.501, 0.639, 0.909);
glVertex3f(-15, 35, 0.1);
glVertex3f(-15, 65, 0.1);
glVertex3f(-15, 65, 20); 
glVertex3f(-15, 35, 20);
glEnd();

//TECHO

glBegin(GL_QUADS);
glColor3f(0.949, 0.890, 0.839); 
glVertex3f(15, 35, 20);
glVertex3f(15, 65, 20);
glVertex3f(-15, 65, 20); 
glVertex3f(-15, 35, 20);
glEnd();

}

void puertabanio ()
{
//puerta central (madera)
	
	glPushMatrix();
		
		glColor3f(1.0f, 1.4f, 1.0f);
		
		glTranslatef(0, 35, 8.11);
		
		glScalef(0.75, 0.04, 1.54);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
	glPopMatrix();
	

	//////////////////////////////////////// extremos de puerta //////////////////////////////////
	//*********** lad izq
	glPushMatrix();
	    glColor3f(1.0, 1.0, 1.0);
	
		glTranslatef(4, 35, 8.00);
	
		glScalef(0.057, 0.089, 1.59);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();			
	glPopMatrix();
	
	
	//********** lad der
	glPushMatrix();
	    glColor3f(1.0, 1.0, 1.0);
	
		glTranslatef(-4, 35, 8.00);
	
		glScalef(0.057, 0.089, 1.59);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();			
	glPopMatrix();
	
	
	//*************lad inf
	glPushMatrix();
	
		glColor3f(1.0, 1.0, 1.0);
	
		glTranslatef(0, 35, 0.21);
	
		glScalef(0.75, 0.10, 0.035);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();			
	glPopMatrix();
	
	
	
	//********** lad sup
	
	glPushMatrix();
	    glColor3f(1.0, 1.0, 1.0);
	
		glTranslatef(0, 35, 15.71);
	
		glScalef(0.75, 0.10, 0.035);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();			
	glPopMatrix();
	
	
	//////////////////////////////  manija ///////////////////////////////////////
	
	//////// ---------------dentro ----------
	
	/// cubito
	//parte der
	
    glPushMatrix();
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		glTranslatef(2.7, 35.1, 8.00);
	
		glScalef(0.03, 0.05, 0.03);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
	
	//// manija horizontal
	
	glPushMatrix();
	    glColor3f(0.0, 0.0, 0.0);
	
		glTranslatef(2.2, 35.5, 8.00);
	
		glScalef(0.23, 0.03, 0.03);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();			
	glPopMatrix();

		//////// --------------- afuera ----------
	
	/// cubito
	//parte der
	
    glPushMatrix();
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		glTranslatef(2.7, 34.5, 8.00);
	
		glScalef(0.03, 0.05, 0.03);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
	
	//// manija vertical
	
	glPushMatrix();
	    glColor3f(0.0, 0.0, 0.0);
	
		glTranslatef(2.7, 34.3, 7.50);
	
		//glScalef(0.23, 0.03, 0.03);
		glScalef(0.03, 0.03, 0.23);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();			
	glPopMatrix();

}

void ducha()
{
	
//------ PISO DE LA DUCHA---------------

//-- CARA ALFRENTE------

glBegin(GL_QUADS);
glColor3f(1.0, 1.0, 1.0);
glVertex3f(8, 65, 0.2);
glVertex3f(8, 55, 0.2);
glVertex3f(8, 55, 4); 
glVertex3f(8, 65, 4);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 );
glVertex3f(8, 65, 0.2);
glVertex3f(8, 55, 0.2);
glVertex3f(8, 55, 4); 
glVertex3f(8, 65, 4);
glEnd();

//-- CARA FONDO------

glBegin(GL_QUADS);
glColor3f(1.0, 1.0, 1.0);
glVertex3f(14.9, 65, 0.2);
glVertex3f(14.9, 55, 0.2);
glVertex3f(14.9, 55, 4); 
glVertex3f(14.9, 65, 4);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 );
glVertex3f(14.9, 65, 0.2);
glVertex3f(14.9, 55, 0.2);
glVertex3f(14.9, 55, 4); 
glVertex3f(14.9, 65, 4);
glEnd();

//-- CARA IZQUIERDA------

glBegin(GL_QUADS);
glColor3f(1.0, 1.0, 1.0);
glVertex3f(14.9, 64.9, 0.2);
glVertex3f(7.9, 64.9, 0.2);
glVertex3f(7.9, 64.9, 4); 
glVertex3f(14.9, 64.9, 4);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 );
glVertex3f(14.9, 64.9, 0.2);
glVertex3f(7.9, 64.9, 0.2);
glVertex3f(7.9, 64.9, 4); 
glVertex3f(14.9, 64.9, 4);
glEnd();

//-- CARA DERECHA------ 
glBegin(GL_QUADS);
glColor3f(1.0, 1.0, 1.0);
glVertex3f(15, 55, 0.2);
glVertex3f(8, 55, 0.2);
glVertex3f(8, 55, 4); 
glVertex3f(15, 55, 4);
glEnd();	

glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 );
glVertex3f(15, 55, 0.2);
glVertex3f(8, 55, 0.2);
glVertex3f(8, 55, 4); 
glVertex3f(15, 55, 4);
glEnd();

//---------- PARED ----------------
//-- CARA ALFRENTE------

glBegin(GL_QUADS);
glColor3f(0.501, 0.639, 0.909);
glVertex3f(8, 55, 0.2);
glVertex3f(8, 52, 0.2);
glVertex3f(8, 52, 20); 
glVertex3f(8, 55, 20);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 );
glVertex3f(8, 55, 0.2);
glVertex3f(8, 52, 0.2);
glVertex3f(8, 52, 20); 
glVertex3f(8, 55, 20);
glEnd();

//-- CARA FONDO------

glBegin(GL_QUADS);
glColor3f(0.501, 0.639, 0.909);
glVertex3f(14.9, 55, 0.2);
glVertex3f(14.9, 52, 0.2);
glVertex3f(14.9, 52, 20); 
glVertex3f(14.9, 55, 20);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 );
glVertex3f(14.9, 55, 0.2);
glVertex3f(14.9, 52, 0.2);
glVertex3f(14.9, 52, 20); 
glVertex3f(14.9, 55, 20);
glEnd();

//-- CARA IZQUIERDA------

glBegin(GL_QUADS);
glColor3f(0.501, 0.639, 0.909);
glVertex3f(8, 55, 0.2);
glVertex3f(15, 55, 0.2);
glVertex3f(15, 55, 20); 
glVertex3f(8, 55, 20);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 );
glVertex3f(8, 55, 0.2);
glVertex3f(15, 55, 0.2);
glVertex3f(15, 55, 20); 
glVertex3f(8, 55, 20);
glEnd();

//-- CARA DERECHA------ 
glBegin(GL_QUADS);
glColor3f(0.501, 0.639, 0.909);
glVertex3f(8, 52, 0.2);
glVertex3f(15, 52, 0.2);
glVertex3f(15, 52, 20); 
glVertex3f(8, 52, 20);
glEnd();	

glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 );
glVertex3f(8, 52, 0.2);
glVertex3f(15, 52, 0.2);
glVertex3f(15, 52, 20); 
glVertex3f(8, 52, 20);
glEnd();


//------ REGADERA ---------	
	
	/// CUBO VERTICAL
    glPushMatrix();
		
		glColor3f( 0.588 , 0.576 , 0.572 );
		
		glTranslatef(12.5, 63.5, 15.0);
	
		glScalef(0.08, 0.25 , 0.04);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
		/// CUBITO
    glPushMatrix();
		
		glColor3f( 0.588 , 0.576 , 0.572 );
		
		glTranslatef(12.5, 62.39, 14.49);
	
		glScalef(0.08, 0.025 , 0.06);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
	//// CUBO HORIZONTAL
	glPushMatrix();
	    glColor3f( 0.588 , 0.576 , 0.572 );
	
		glTranslatef(12.5, 62, 14);
	
		glScalef(0.25, 0.20, 0.03);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();			
	glPopMatrix();
}

void espejo_y_lavadero()
{
//---------------------- ESPEJO ------------------

//-- MARCO TRASERO------

glBegin(GL_QUADS);
glColor3f(0.0, 0.0, 0.0);
glVertex3f(-5, 64.9, 12);
glVertex3f(3, 64.9, 12);
glVertex3f(3, 64.9, 17); 
glVertex3f(-5, 64.9, 17);
glEnd();

//--- MARCO DELANTERO
glBegin(GL_QUADS);
glColor3f(1.0, 1.0, 1.0);
glVertex3f(-4.7, 64.8, 12.3);
glVertex3f(2.7, 64.8, 12.3);
glVertex3f(2.7, 64.8, 16.7); 
glVertex3f(-4.7, 64.8, 16.7);
glEnd();
	
//--------------------- LAVADERO -----------------------
//-- CARA INFERIOR -----
glBegin(GL_QUADS);
glColor3f(1.0, 1.0, 1.0);
glVertex3f(-4, 64.9, 5);
glVertex3f(-4, 62, 5);
glVertex3f(2, 62, 5); 
glVertex3f(2, 64.9, 5);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 );
glVertex3f(-4, 64.9, 5);
glVertex3f(-4, 62, 5);
glVertex3f(2, 62, 5); 
glVertex3f(2, 64.9, 5);
glEnd();

//-- CARA ALFRENTE------

glBegin(GL_QUADS);
glColor3f(1.0, 1.0, 1.0);
glVertex3f(-4, 64.9, 5);
glVertex3f(2, 64.9, 5);
glVertex3f(3, 64.9, 8); 
glVertex3f(-5, 64.9, 8);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 );
glVertex3f(-4, 64.9, 5);
glVertex3f(2, 64.9, 5);
glVertex3f(3, 64.9, 8); 
glVertex3f(-5, 64.9, 8);
glEnd();

//-- CARA FONDO------

glBegin(GL_QUADS);
glColor3f(1.0, 1.0, 1.0);
glVertex3f(-4, 62, 5);
glVertex3f(2, 62, 5);
glVertex3f(3, 62, 8); 
glVertex3f(-5, 62, 8);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 );
glVertex3f(-4, 62, 5);
glVertex3f(2, 62, 5);
glVertex3f(3, 62, 8); 
glVertex3f(-5, 62, 8);
glEnd();

//-- CARA IZQUIERDA------

glBegin(GL_QUADS);
glColor3f(1.0, 1.0, 1.0);
glVertex3f(-4, 64.9, 5);
glVertex3f(-4, 62, 5);
glVertex3f(-5, 62, 8); 
glVertex3f(-5, 64.9, 8);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 );
glVertex3f(-4, 64.9, 5);
glVertex3f(-4, 62, 5);
glVertex3f(-5, 62, 8); 
glVertex3f(-5, 64.9, 8);
glEnd();

//-- CARA DERECHA------ 
glBegin(GL_QUADS);
glColor3f(1.0, 1.0, 1.0);
glVertex3f(2, 64.9, 5);
glVertex3f(2, 62, 5);
glVertex3f(3, 62, 8); 
glVertex3f(3, 64.9, 8);
glEnd();	

glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 );
glVertex3f(2, 64.9, 5);
glVertex3f(2, 62, 5);
glVertex3f(3, 62, 8); 
glVertex3f(3, 64.9, 8);
glEnd();


//------ LLAVE DEL CAÑO ---------	
	
	/// CUBO VERTICAL
    glPushMatrix();
		
		glColor3f( 0.588 , 0.576 , 0.572 );
		
		glTranslatef(-1, 63.5, 10.0);
	
		glScalef(0.08, 0.25 , 0.04);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
		/// CUBITO
    glPushMatrix();
		
		glColor3f( 0.588 , 0.576 , 0.572 );
		
		glTranslatef(-1, 63.5, 10.5);
	
		glScalef(0.08, 0.020 , 0.06);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
//------ TUBERIA DEL CAÑO ---------	
	
	/// CUBO VERTICAL
    glPushMatrix();
		
		glColor3f( 0.588 , 0.576 , 0.572 );
		
		glTranslatef(-1, 63.5, 3.4);
	
		glScalef(0.08, 0.21 , 0.04);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
		/// CUBITO
    glPushMatrix();
		
		glColor3f( 0.588 , 0.576 , 0.572 );
		
		glTranslatef(-1, 62.6, 4);
	
		glScalef(0.08, 0.020 , 0.16);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
}

void retrete()
{	
//-- CARA SUPERIOR -----
glBegin(GL_QUADS);
glColor3f(1.0, 1.0, 1.0);
glVertex3f(-13.5, 64.9, 8);
glVertex3f(-13.5, 62, 8);
glVertex3f(-8.5, 62, 8); 
glVertex3f(-8.5, 64.9, 8);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 );
glVertex3f(-13.5, 64.9, 8);
glVertex3f(-13.5, 62, 8);
glVertex3f(-8.5, 62, 8); 
glVertex3f(-8.5, 64.9, 8);
glEnd();

//-- CARA ALFRENTE------

glBegin(GL_QUADS);
glColor3f(1.0, 1.0, 1.0);
glVertex3f(-13, 64.9, 5);
glVertex3f(-9, 64.9, 5);
glVertex3f(-8.5, 64.9, 8); 
glVertex3f(-13.5, 64.9, 8);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 );
glVertex3f(-13, 64.9, 5);
glVertex3f(-9, 64.9, 5);
glVertex3f(-8.5, 64.9, 8); 
glVertex3f(-13.5, 64.9, 8);
glEnd();

//-- CARA FONDO------

glBegin(GL_QUADS);
glColor3f(1.0, 1.0, 1.0);
glVertex3f(-13, 62, 5.05);
glVertex3f(-9, 62, 5.05);
glVertex3f(-8.5, 62, 8); 
glVertex3f(-13.5, 62, 8);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 );
glVertex3f(-13, 62, 5.05);
glVertex3f(-9, 62, 5.05);
glVertex3f(-8.5, 62, 8); 
glVertex3f(-13.5, 62, 8);
glEnd();

//-- CARA IZQUIERDA------

glBegin(GL_QUADS);
glColor3f(1.0, 1.0, 1.0);
glVertex3f(-13, 64.9, 5);
glVertex3f(-13, 62, 5);
glVertex3f(-13.5, 62, 8); 
glVertex3f(-13.5, 64.9, 8);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 );
glVertex3f(-13, 64.9, 5);
glVertex3f(-13, 62, 5);
glVertex3f(-13.5, 62, 8); 
glVertex3f(-13.5, 64.9, 8);
glEnd();

//-- CARA DERECHA------ 
glBegin(GL_QUADS);
glColor3f(1.0, 1.0, 1.0);
glVertex3f(-9, 64.9, 5);
glVertex3f(-9, 62, 5);
glVertex3f(-8.5, 62, 8); 
glVertex3f(-8.5, 64.9, 8);
glEnd();	

glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 );
glVertex3f(-9, 64.9, 5);
glVertex3f(-9, 62, 5);
glVertex3f(-8.5, 62, 8); 
glVertex3f(-8.5, 64.9, 8);
glEnd();

// --- TAZA DEL BAÑO ---------
//-- CARA INFERIOR -----
glBegin(GL_QUADS);
glColor3f(1.0, 1.0, 1.0);
glVertex3f(-13, 64.9, 0.2);
glVertex3f(-13, 62, 0.2);
glVertex3f(-9, 62, 0.2); 
glVertex3f(-9, 64.9, 0.2);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 );
glVertex3f(-13, 64.9, 0.2);
glVertex3f(-13, 62, 0.2);
glVertex3f(-9, 62, 0.2); 
glVertex3f(-9, 64.9, 0.2);
glEnd();

//-- CARA ALFRENTE------

glBegin(GL_QUADS);
glColor3f(1.0, 1.0, 1.0);
glVertex3f(-13, 64.9, 0.2);
glVertex3f(-9, 64.9, 0.2);
glVertex3f(-9, 64.9, 5); 
glVertex3f(-13, 64.9, 5);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 );
glVertex3f(-13, 64.9, 0.2);
glVertex3f(-9, 64.9, 0.2);
glVertex3f(-9, 64.9, 5); 
glVertex3f(-13, 64.9, 5);
glEnd();

//-- CARA FONDO------

glBegin(GL_QUADS);
glColor3f(1.0, 1.0, 1.0);
glVertex3f(-13, 62, 0.2);
glVertex3f(-13, 60, 3);
glVertex3f(-9, 60, 3); 
glVertex3f(-13, 62, 0.2);
glEnd();

//-- CARA IZQUIERDA------

glBegin(GL_POLYGON);
glColor3f(1.0, 1.0, 1.0);
glVertex3f(-13, 64.9, 0.2);
glVertex3f(-13, 62, 0.2);
glVertex3f(-13, 60, 3); 
glVertex3f(-13, 62, 5);
glVertex3f(-13, 60, 5);
glVertex3f(-13, 64.9, 5);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 );	
glVertex3f(-13, 64.9, 0.2);
glVertex3f(-13, 62, 0.2);
glVertex3f(-13, 60, 3); 
glVertex3f(-13, 62, 5);
glVertex3f(-13, 60, 5);
glVertex3f(-13, 64.9, 5);
glEnd();

//-- CARA DERECHA------ 
glBegin(GL_POLYGON);
glColor3f(1.0, 1.0, 1.0);
glVertex3f(-9, 64.9, 0.2);
glVertex3f(-9, 62, 0.2);
glVertex3f(-9, 60, 3); 
glVertex3f(-9, 62, 5);
glVertex3f(-9, 60, 5);
glVertex3f(-9, 64.9, 5);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 );	
glVertex3f(-9, 64.9, 0.2);
glVertex3f(-9, 62, 0.2);
glVertex3f(-9, 60, 3); 
glVertex3f(-9, 62, 5);
glVertex3f(-9, 60, 5);
glVertex3f(-9, 64.9, 5);
glEnd();

//---- TAPA DEL BAÑO -----
glBegin(GL_POLYGON);
glColor3f(1.0, 1.0, 1.0);
glVertex3f(-13, 62, 5);
glVertex3f(-13, 60, 5);
glVertex3f(-12.5, 58, 5); 
glVertex3f(-11, 57, 5);
glVertex3f(-9.5, 58, 5);
glVertex3f(-9, 60, 5);
glVertex3f(-9, 62, 5); 
glEnd();	

glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 );
glVertex3f(-13, 62, 5);
glVertex3f(-13, 60, 5);
glVertex3f(-12.5, 58, 5); 
glVertex3f(-11, 57, 5);
glVertex3f(-9.5, 58, 5);
glVertex3f(-9, 60, 5);
glVertex3f(-9, 62, 5); 
glEnd();

// TAPA DEL BAÑO 2 -----------------
glBegin(GL_POLYGON);
glColor3f(1.0, 1.0, 1.0);
glVertex3f(-13, 60, 3);
glVertex3f(-12.5, 58, 3);
glVertex3f(-11, 57, 3);
glVertex3f(-9.5, 58, 3);
glVertex3f(-9, 60, 3);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 );
glVertex3f(-13, 60, 3);
glVertex3f(-12.5, 58, 3);
glVertex3f(-11, 57, 3);
glVertex3f(-9.5, 58, 3);
glVertex3f(-9, 60, 3);
glEnd();

// TAPA DEL BAÑO 3 -----------------
glBegin(GL_QUADS);
glColor3f(1.0, 1.0, 1.0);
glVertex3f(-13, 60, 3);
glVertex3f(-12.5, 58, 3);
glVertex3f(-12.5, 58, 5); 
glVertex3f(-13, 60, 5);
glEnd();

glBegin(GL_QUADS);
glColor3f(1.0, 1.0, 1.0);
glVertex3f(-12.5, 58, 3);
glVertex3f(-11, 57, 3);
glVertex3f(-11, 57, 5);
glVertex3f(-12.5, 58, 5); 
glEnd();

glBegin(GL_QUADS);
glColor3f(1.0, 1.0, 1.0);
glVertex3f(-11, 57, 3);
glVertex3f(-9.5, 58, 3);
glVertex3f(-9.5, 58, 5);
glVertex3f(-11, 57, 5);
glEnd();

glBegin(GL_QUADS);
glColor3f(1.0, 1.0, 1.0);
glVertex3f(-9.5, 58, 3);
glVertex3f(-9, 60, 3);
glVertex3f(-9, 60, 5);
glVertex3f(-9.5, 58, 5);
glEnd();

//PALANCA	
	/// cubito
	 glPushMatrix();
		glColor3f( 0.588 , 0.576 , 0.572 );
		
		glTranslatef(-12.8, 61.85, 7.5);
	
		glScalef(0.03, 0.03, 0.03);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
	
	//// manija horizontal
	
	glPushMatrix();
	    glColor3f( 0.588 , 0.576 , 0.572 );
	
		glTranslatef(-13, 61.65, 7.5);
	
		glScalef(0.07, 0.03, 0.03);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();			
	glPopMatrix();

}

void lavadora()
{
 glPushMatrix();
  glTranslated(-0.1,0,0);
//-- CARA SUPERIOR -----
glBegin(GL_QUADS);
glColor3f(1.0, 1.0, 1.0);
glVertex3f(8, 49, 8);
glVertex3f(8, 42, 8);
glVertex3f(15, 42, 8); 
glVertex3f(15, 49, 8);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 );
glVertex3f(8, 49, 8);
glVertex3f(8, 42, 8);
glVertex3f(15, 42, 8); 
glVertex3f(15, 49, 8);
glEnd();

//-- CARA ALFRENTE------

glBegin(GL_QUADS);
glColor3f(1.0, 1.0, 1.0);
glVertex3f(8, 49, 0.1);
glVertex3f(15, 49, 0.1);
glVertex3f(15, 49, 8); 
glVertex3f(8, 49, 8);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 );
glVertex3f(8, 49, 0.2);
glVertex3f(15, 49, 0.2);
glVertex3f(15, 49, 8); 
glVertex3f(8, 49, 8);
glEnd();

//-- CARA FONDO------

glBegin(GL_QUADS);
glColor3f(1.0, 1.0, 1.0);
glVertex3f(8, 42, 0.2);
glVertex3f(15, 42, 0.2);
glVertex3f(15, 42, 8); 
glVertex3f(8, 42, 8);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 );
glVertex3f(8, 42, 0.2);
glVertex3f(15, 42, 0.2);
glVertex3f(15, 42, 8); 
glVertex3f(8, 42, 8);
glEnd();

//-- CARA IZQUIERDA------

glBegin(GL_QUADS);
glColor3f(1.0, 1.0, 1.0);
glVertex3f(8, 49, 0.2);
glVertex3f(8, 42, 0.2);
glVertex3f(8, 42, 7); 
glVertex3f(8, 49, 7);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 );
glVertex3f(8, 49, 0.2);
glVertex3f(8, 42, 0.2);
glVertex3f(8, 42, 7); 
glVertex3f(8, 49, 7);
glEnd();

// CARA IZQUIERDA 2
glBegin(GL_QUADS);
glColor3f( 0.588 , 0.576 , 0.572 );
glVertex3f(8, 49, 7);
glVertex3f(8, 42, 7);
glVertex3f(8, 42, 8); 
glVertex3f(8, 49, 8);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 );
glVertex3f(8, 49, 7);
glVertex3f(8, 42, 7);
glVertex3f(8, 42, 8); 
glVertex3f(8, 49, 8);
glEnd();

//-- CARA DERECHA------ 
glBegin(GL_QUADS);
glColor3f(1.0, 1.0, 1.0);
glVertex3f(15, 49, 0.2);
glVertex3f(15, 42, 0.2);
glVertex3f(15, 42, 8); 
glVertex3f(15, 49, 8);
glEnd();	

glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 );
glVertex3f(15, 49, 0.2);
glVertex3f(15, 42, 0.2);
glVertex3f(15, 42, 8); 
glVertex3f(15, 49, 8);
glEnd();

//PUERTA
glBegin(GL_POLYGON);
glColor3f(0.0, 0.0, 0.0);
glVertex3f(7.9, 45.19, 5.83);
glVertex3f(7.9, 44.43, 5.51);
glVertex3f(7.9, 43.69, 4.84); 
glVertex3f(7.9, 43.31, 4);
glVertex3f(7.9, 43.29, 3.23);
glVertex3f(7.9, 43.52, 2.42);
glVertex3f(7.9, 44, 1.71); 
glVertex3f(7.9, 44.86, 1.26);
glVertex3f(7.9, 45.83, 1.14);
glVertex3f(7.9, 46.64, 1.38);
glVertex3f(7.9, 47.28, 1.83); 
glVertex3f(7.9, 47.76, 2.5);
glVertex3f(7.9, 48, 3.3);
glVertex3f(7.9, 47.85, 4.22);
glVertex3f(7.9, 47.47, 5); 
glVertex3f(7.9, 46.78, 5.64);
glVertex3f(7.9, 46, 5.86);
glEnd();

glBegin(GL_POLYGON);
glColor3f(1.0, 1.0, 1.0);
glVertex3f(7.8, 45.25, 5.43);
glVertex3f(7.8, 44.59, 5.2);
glVertex3f(7.8, 44, 4.64); 
glVertex3f(7.8, 43.75, 4);
glVertex3f(7.8, 43.74, 3.26);
glVertex3f(7.8, 43.97, 2.6);
glVertex3f(7.8, 44.37, 2.17); 
glVertex3f(7.8, 45, 1.76);
glVertex3f(7.8, 45.77, 1.67);
glVertex3f(7.8, 46.46, 1.87);
glVertex3f(7.8, 46.99, 2.28); 
glVertex3f(7.8, 47.27, 2.74);
glVertex3f(7.8, 47.49, 3.42);
glVertex3f(7.8, 47.44, 4);
glVertex3f(7.8, 47.05, 4.78); 
glVertex3f(7.8, 46.52, 5.22);
glVertex3f(7.8, 45.84, 5.44);
glEnd();

 glPopMatrix();
}

void repisa_y_alfombra()
{
	//------ REPISA 1 ---------	
   glPushMatrix();
		glColor3f( 0.588 , 0.576 , 0.572 );
		
		glTranslatef(11.5, 50.9, 15.0);
	
		glScalef(0.65, 0.25 , 0.04);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
		//------ REPISA 2 ---------	
   glPushMatrix();
		glColor3f( 0.588 , 0.576 , 0.572 );
		
		glTranslatef(11.5, 50.9, 10.0);
	
		glScalef(0.65, 0.25 , 0.04);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
//----------- ALFOMBRA ----------------
glBegin(GL_QUADS);
glColor3f(0.709, 0.941, 0.815);
glVertex3f(2, 52, 0.2);
glVertex3f(-9, 52, 0.2);
glVertex3f(-9, 44, 0.2); 
glVertex3f(2, 44, 0.2);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 );
glVertex3f(2, 52, 0.2);
glVertex3f(-9, 52, 0.2);
glVertex3f(-9, 44, 0.2); 
glVertex3f(2, 44, 0.2);
glEnd();

//RAYA 1
glBegin(GL_QUADS);
glColor3f(0.988, 0.827, 0.713);
glVertex3f(-7, 52, 0.3);
glVertex3f(-6, 52, 0.3);
glVertex3f(-6, 44, 0.3); 
glVertex3f(-7, 44, 0.3);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 );
glVertex3f(-7, 52, 0.3);
glVertex3f(-6, 52, 0.3);
glVertex3f(-6, 44, 0.3); 
glVertex3f(-7, 44, 0.3);
glEnd();

//RAYA 2
glBegin(GL_QUADS);
glColor3f(0.988, 0.827, 0.713);
glVertex3f(0, 52, 0.3);
glVertex3f(-1, 52, 0.3);
glVertex3f(-1, 44, 0.3); 
glVertex3f(0, 44, 0.3);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f( 0.0 , 0.0 , 0.0 );
glVertex3f(0, 52, 0.3);
glVertex3f(-1, 52, 0.3);
glVertex3f(-1, 44, 0.3); 
glVertex3f(0, 44, 0.3);
glEnd();
	
}

void Muebles(){
	glPushMatrix();
		glTranslatef(4.6, -1.85, 2.75);
		glRotatef(00, 0.0, 1.0, 0.0);
		//glScalef(0.7, 0.7, 0.7);
		caLateral();
	glPopMatrix();	
	
	glPushMatrix();
		glTranslatef(6.2, -3.52, -5.7);
		//glScalef(0.7, 0.7, 0.7);
		sofa();
	glPopMatrix();		
}

void Alfombra() {
	glPushMatrix();
		glColor3f(0.13f, 0.13f, 0.13f);
		glTranslatef(2.4, -4.75, -1.9);
		glScalef(0.9, 0.01, 1.1);
		glutSolidCube(5);
		glScalef(0.5, 0.5, 0.5);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1.5);		
		glEnd();
	glPopMatrix();
}

//////////////// CUADRO 2 ////////////////////////

void cuadro2(){
	//////////////////>>>>>>>> PORTADA <<<<<<<<<<<
	
	//lienzo del cuadro (blanco)
	
	glPushMatrix();
		
		glColor3f(1.0f, 1.0f, 1.0f);
	
		glTranslatef(15.4, 8.05, 10.51);
		
		glScalef(0.03, 0.80, 0.54);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
	glPopMatrix();
	
	//lienzo del cuadro (beigge)
	
	glPushMatrix();
		
		glColor3f(1.0f, 0.878f, 0.615f);
		
		
		glTranslatef(15.4, 8.05, 10.51);
		
		
		glScalef(0.04, 0.60, 0.44);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
	glPopMatrix();
	
	
	//////------- bordes
	
		//bordes lado izq
	
	glPushMatrix();
		
		glColor3f(1.0, 0.815, 0.392);
		
	
		glTranslatef(15.4, 12.05, 10.50);
		
		
		glScalef(0.04, 0.04, 0.54);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
	glPopMatrix();
	
		//bordes lado der
	
	glPushMatrix();
		
		glColor3f(1.0, 0.815, 0.392);
		
		//glTranslatef(36.3, -25.05, 14.50);
		glTranslatef(15.4, 4.05, 10.50);
		
		//glScalef(0.03, 0.04, 0.54);
		glScalef(0.04, 0.04, 0.54);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
	glPopMatrix();
	
		
	
	// bordes lad inf
	
	glPushMatrix();
	
		glColor3f(1.0, 0.815, 0.392);//amarillo
	
		//glTranslatef(40.4, -25.05, 11.61);
		glTranslatef(15.4, 8.05, 7.60);
		
	
		//glScalef(0.86, 0.04, 0.03);
		glScalef(0.05, 0.86, 0.03);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();			
	glPopMatrix();
	
	
	// bordes lad sup
	
	glPushMatrix();
	    glColor3f(1.0, 0.815, 0.392);
	
		//glTranslatef(40.4, -25.05, 17.31);
		glTranslatef(15.4, 8.05, 13.40);
		
		//glScalef(0.86, 0.04, 0.03);
		glScalef(0.05, 0.86, 0.03);
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();			
	glPopMatrix();
	
	
	/////>>>>>>>>>>>> IMAGEN  <<<<<<<<<<<<<<
	
	///cubo1
	glPushMatrix();
		
		glColor3f(0.5f, 1.0f, 0.4f); //verde
		
		glTranslatef(15.9, 9.15, 11.51);
		//glRotated(45,0,1,0);
		
		glScalef(0.03, 0.06, 0.07);
		
		glutSolidCube(10);
		
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
	glPopMatrix();
	
	///cubo2
	glPushMatrix();
		
		glColor3f(0.839f, 0.321f, 0.301f);//rojo
		
		
		glTranslatef(15.9, 8.05, 10.01);
		
		glScalef(0.03, 0.10, 0.18);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
	glPopMatrix();
	
	///cubo3
	glPushMatrix();
		
		glColor4f(0.929f, 0.525f, 0.417f,0.129f);//naranja
		
		//glTranslatef(40.4, -24.90, 15.50);
		glTranslatef(15.9,6.05, 10.51);
		
		glScalef(0.04, 0.08, 0.12);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
	glPopMatrix();
	
	//cubo 4
	glPushMatrix();
		
		glColor3f(0.560f, 0.252f, 0.745f);//morado
		
		//glTranslatef(39.8, -24.90, 15.67);
		glTranslatef(15.9, 9.45, 9.51);
		//glRotated(45,0,1,0);
		
		glScalef(0.03, 0.12, 0.04);
		
		glutSolidCube(10);
		
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();		
		
	glPopMatrix();
	
	//plato inf
		glPushMatrix();
		
		glColor3f(0.980f, 0.580f, 0.886f);//rosa
		
		glTranslatef(15.9, 6.45, 11.51);
		
		glScalef(0.03, 0.12, 0.04);
		
		glutSolidCube(10);
		
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();		
		
	glPopMatrix();
	
	
	
	
}

//////////////// CUADRO 3 ////////////////////////

void cuadro3(){
		//////////////////>>>>>>>> PORTADA <<<<<<<<<<<
	
	//lienzo del cuadro (blanco)
	
	glPushMatrix();
		
		glColor3f(1.0f, 1.0f, 1.0f);
	
		glTranslatef(15.4, -12.05, 10.51);
		
		glScalef(0.03, 0.80, 0.54);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
	glPopMatrix();
	
	//lienzo del cuadro (negro)
	
	glPushMatrix();
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		
		glTranslatef(15.4, -12.05, 10.51);
		
		
		glScalef(0.04, 0.60, 0.44);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
	glPopMatrix();
	
	
	//////------- bordes
	
		//bordes lado izq
	
	glPushMatrix();
		
		glColor3f(1.0, 0.815, 0.392);
		
	
		glTranslatef(15.4, -16.05, 10.50);
		
		
		glScalef(0.04, 0.04, 0.54);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
	glPopMatrix();
	
		//bordes lado der
	
	glPushMatrix();
		
		glColor3f(1.0, 0.815, 0.392);
		
		//glTranslatef(36.3, -25.05, 14.50);
		glTranslatef(15.4, -8.05, 10.50);
		
		//glScalef(0.03, 0.04, 0.54);
		glScalef(0.04, 0.04, 0.54);
		
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
	glPopMatrix();
	
		
	
	// bordes lad inf
	
	glPushMatrix();
	
		glColor3f(1.0, 0.815, 0.392);//amarillo
	
		//glTranslatef(40.4, -25.05, 11.61);
		glTranslatef(15.4, -12.05, 7.60);
		
	
		//glScalef(0.86, 0.04, 0.03);
		glScalef(0.05, 0.86, 0.03);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();			
	glPopMatrix();
	
	
	// bordes lad sup
	
	glPushMatrix();
	    glColor3f(1.0, 0.815, 0.392);
	
		//glTranslatef(40.4, -25.05, 17.31);
		glTranslatef(15.4, -12.05, 13.40);
		
		//glScalef(0.86, 0.04, 0.03);
		glScalef(0.05, 0.86, 0.03);
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();			
	glPopMatrix();
	
	
	/////>>>>>>>>>>>> IMAGEN  <<<<<<<<<<<<<<
	
	///llanto 1 
	glPushMatrix();
		
		glColor3f(0.713f, 1.0f, 0.0f); //verde
		
		//glTranslatef(15.9, 9.15, 11.51);
		glTranslatef(15.8, -14.05, 11.40);
		
		glRotated(45,1,0,0);
		
		glScalef(0.03, 0.04, 0.07);
		
		glutSolidCube(10);
		
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
	glPopMatrix();
	
	//llanto 2
	glPushMatrix();
		
		glColor3f(0.713f, 1.0f, 0.0f); //verde
		
		//glTranslatef(15.9, 9.15, 11.51);
		glTranslatef(15.8, -10.05, 11.40);
		
		glRotated(-45,1,0,0);
		
		glScalef(0.03, 0.04, 0.07);
		
		glutSolidCube(10);
		
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
	glPopMatrix();
	
	
	//llanto 3
	glPushMatrix();
		
		glColor3f(1.0f, 0.0823f, 0.7607f); //pink
		
		//glTranslatef(15.9, 9.15, 11.51);
		glTranslatef(15.8, -14.05, 10.40);
		
		glRotated(45,1,0,0);
		
		glScalef(0.03, 0.04, 0.07);
		
		glutSolidCube(10);
		
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
	glPopMatrix();
	
	//llanto 4
	glPushMatrix();
		
		glColor3f(1.0f, 0.0823f, 0.7607f); //pink
		
		//glTranslatef(15.9, 9.15, 11.51);
		glTranslatef(15.8, -9.85, 10.40);
		
		glRotated(-45,1,0,0);
		
		glScalef(0.03, 0.04, 0.07);
		
		glutSolidCube(10);
		
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
	glPopMatrix();
	
	
	//llanto 5
	glPushMatrix();
		
		glColor3f(0.117f, 0.3411f, 0.9019f); //blue
		
		//glTranslatef(15.9, 9.15, 11.51);
		glTranslatef(15.8, -14.05, 9.40);
		
		glRotated(45,1,0,0);
		
		glScalef(0.03, 0.04, 0.07);
		
		glutSolidCube(10);
		
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
	glPopMatrix();
	
	//llanto 6
	glPushMatrix();
		
		glColor3f(0.117f, 0.3411f, 0.9019f); //blue
		
		//glTranslatef(15.9, 9.15, 11.51);
		glTranslatef(15.8, -9.85, 9.40);
		
		glRotated(-45,1,0,0);
		
		glScalef(0.03, 0.04, 0.07);
		
		glutSolidCube(10);
		
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
	glPopMatrix();
	

	///rombo
	glPushMatrix();
		
		glColor3f(0.596f, 0.807f, 1.0f);//celeste
		
		
		glTranslatef(15.9, -11.85, 10.15);
		
		glScalef(0.03, 0.08, 0.13);
		
		glutSolidTorus(10,0.2,4,5);
		
		glEnd ();	
		
	glPopMatrix();
	

	
	
}

/////dibujar pericote/////////////////////
void DibujarPericote(){

    //cuerpo
    glPushMatrix();
        glTranslatef(0.0,-4.83,0.0);
        glColor3f (0.501 , 0.501 , 0.501 );
        glutSolidSphere(0.3,40,40);
    glPopMatrix();
    //cabeza
    glPushMatrix();
        glTranslatef(-0.3,-4.83,0.0);
        glColor3f (0.501 , 0.501 , 0.501 );
        glutSolidSphere(0.2,40,40);
    glPopMatrix();
    //ojo
    glPushMatrix();
        glTranslatef(-0.4,-4.7,0.04);
        glColor3f (0.411 , 0.047 , 0.047);
        glutSolidSphere(0.05,40,40);
    glPopMatrix();
    //ojo
    glPushMatrix();
        glTranslatef(-0.4,-4.7,-0.04);
        glColor3f (0.411 , 0.047 , 0.047);
        glutSolidSphere(0.05,40,40);
    glPopMatrix();
    //oreja
    glPushMatrix();
        glRotatef(90,0,1,0);
        glTranslatef(0.2,-4.64,-0.3);
        glColor3f (0.501 , 0.6 , 0.501 );
        glutSolidTorus(0.05, 0.05, 20, 20);
    glPopMatrix();
    //oreja
    glPushMatrix();
        glRotatef(90,0,1,0);
        glTranslatef(-0.2,-4.64,-0.3);
        glColor3f (0.501 , 0.6 , 0.501 );
        glutSolidTorus(0.05, 0.05, 20, 20);
    glPopMatrix();
    //nariz
    glPushMatrix();
        glTranslatef(-0.5,-4.8,-0.01);
        glColor3f (0 , 0 , 0);
        glutSolidSphere(0.05,40,40);
    glPopMatrix();
    
  
}
//////fin dibujar pericote////////////////

/////dibujar pericote/////////////////////
void DibujarPericote2(){

    //cuerpo
    glPushMatrix();
        glTranslatef(0.0,-4.83,0.0);
        glColor3f (0.501 , 0.501 , 0.501 );
        glutSolidSphere(0.3,40,40);
    glPopMatrix();
    //cabeza
    glPushMatrix();
        glTranslatef(-0.3,-4.83,0.0);
        glColor3f (0.501 , 0.501 , 0.501 );
        glutSolidSphere(0.2,40,40);
    glPopMatrix();
    //ojo
    glPushMatrix();
        glTranslatef(-0.4,-4.7,0.04);
        glColor3f (0.411 , 0.047 , 0.047);
        glutSolidSphere(0.05,40,40);
    glPopMatrix();
    //ojo
    glPushMatrix();
        glTranslatef(-0.4,-4.7,-0.04);
        glColor3f (0.411 , 0.047 , 0.047);
        glutSolidSphere(0.05,40,40);
    glPopMatrix();
    //oreja
    glPushMatrix();
        glRotatef(90,0,1,0);
        glTranslatef(0.2,-4.64,-0.3);
        glColor3f (0.501 , 0.6 , 0.501 );
        glutSolidTorus(0.05, 0.05, 20, 20);
    glPopMatrix();
    //oreja
    glPushMatrix();
        glRotatef(90,0,1,0);
        glTranslatef(-0.2,-4.64,-0.3);
        glColor3f (0.501 , 0.6 , 0.501 );
        glutSolidTorus(0.05, 0.05, 20, 20);
    glPopMatrix();
    //nariz
    glPushMatrix();
        glTranslatef(-0.5,-4.8,-0.01);
        glColor3f (0 , 0 , 0);
        glutSolidSphere(0.05,40,40);
    glPopMatrix();
    
  
}
//////fin dibujar pericote////////////////

 void moverPericote(){
    random = rand()%5;
    if(random == 2){
        RED1 = (double)rand() / (RAND_MAX + 1.0);
        GREEN1 = (double)rand() / (RAND_MAX + 1.0);
        BLUE1 = (double)rand() / (RAND_MAX + 1.0);
        RED2 = (double)rand() / (RAND_MAX + 1.0);
        GREEN2 = (double)rand() / (RAND_MAX + 1.0);
        BLUE2 = (double)rand() / (RAND_MAX + 1.0);
        RED3 = (double)rand() / (RAND_MAX + 1.0);
        GREEN3 = (double)rand() / (RAND_MAX + 1.0);
        BLUE3 = (double)rand() / (RAND_MAX + 1.0);
        RED4 = (double)rand() / (RAND_MAX + 1.0);
        GREEN4 = (double)rand() / (RAND_MAX + 1.0);
        BLUE4 = (double)rand() / (RAND_MAX + 1.0);
    }
    
    
    if(posXPericote > -7.0){

        posXPericote -= 0.02;
    }
    else{
        posXPericote = 6.0;
    }
    
    
 }
 void idleFunc(){
 	idleFunc2 ();
 	mover_PJ();
    moverPericote();
    glutPostRedisplay();
 }



//---------------------CUARTO 2-------------------
void cama(){
	glBegin(GL_QUADS);
	//izuiqerdo
    glColor3f( 0.184 , 0.192 , 0.188 );
    glVertex3f(-50, 44, 3);
    glVertex3f(-36, 44, 3);
    glVertex3f(-36, 44, 0.1);
    glVertex3f(-50, 44, 0.1);
    //derecho
    
    glVertex3f(-50, 56, 3);
    glVertex3f(-36, 56, 3);
    glVertex3f(-36, 56, 0.1);
    glVertex3f(-50, 56, 0.1);
    //enfrente
    
    glVertex3f(-36, 44, 3);
    glVertex3f(-36, 56, 3);
    glVertex3f(-36, 56, 0.1);
    glVertex3f(-36, 44, 0.1);
    
    //cabecera
    glVertex3f(-49, 44, 7);
    glVertex3f(-49, 56, 7);
    glVertex3f(-49, 56, 3);
    glVertex3f(-49, 44, 3);
    
    glVertex3f(-49, 44, 3);
    glVertex3f(-49, 44, 7);
    glVertex3f(-50, 44, 7);
    glVertex3f(-50, 44, 3);
    
    glVertex3f(-49, 44, 7);
    glVertex3f(-50, 44, 7);
    glVertex3f(-50, 56, 7);
    glVertex3f(-49, 56, 7);
    
    glVertex3f(-50, 56, 7);
    glVertex3f(-49, 56, 7);
    glVertex3f(-49, 56, 3);
    glVertex3f(-50, 56, 3);
    
    //colchon
    glColor3f( 0.917 , 0.917 , 0.917 );
    glVertex3f(-49, 44, 3.7);
    glVertex3f(-49, 56, 3.7);
    glVertex3f(-36, 56, 3.7);
    glVertex3f(-36, 44, 3.7);
    
    glVertex3f(-49, 44, 3.7);
    glVertex3f(-36, 44,  3.7);
    glVertex3f(-36, 44,  3.01);
    glVertex3f(-49, 44, 3.01);
    
    glVertex3f(-49, 56,  3.7);
    glVertex3f(-36, 56,  3.7);
    glVertex3f(-36, 56,  3.01);
    glVertex3f(-49, 56,  3.01);
    
    glVertex3f(-36, 44, 3.7);
    glVertex3f(-36, 56,  3.7);
    glVertex3f(-36, 56,  3.01);
    glVertex3f(-36, 44, 3.01);
    
	glEnd();
	//-------------------delineado
	//COLCHON
	glColor3f( 0.0 , 0.0 , 0.0 );
	glBegin(GL_LINE_LOOP);
	glVertex3f(-49, 44, 3.7);
    glVertex3f(-49, 56,  3.7);
    glVertex3f(-36, 56,  3.7);
    glVertex3f(-36, 44, 3.7);
	glEnd();
	//VELERA IZQUIERDA
	glBegin(GL_LINE_LOOP);
	glVertex3f(-49.98, 35, 3.7);
    glVertex3f(-49.98, 44, 3.7);
    glVertex3f(-45, 44, 3.7);
    glVertex3f(-45.02, 35, 3.7);
	glEnd();
	//VELERA DERECHA
	glBegin(GL_LINE_LOOP);
	glVertex3f(-49.98, 56, 3.7);
    glVertex3f(-49.98, 65, 3.7);
    glVertex3f(-44, 64.98, 3.7);
    glVertex3f(-44, 56, 3.7);
	glEnd();
	
	glBegin(GL_LINES);
	glVertex3f(-36, 44, 3);
    glVertex3f(-36, 44, 3.7);
    glVertex3f(-36, 56, 3);
    glVertex3f(-36, 56, 3.7);
    
    glVertex3f(-45, 44, 3.7);
    glVertex3f(-45, 44, 0.1);
    glVertex3f(-44, 56, 3.7);
    glVertex3f(-44, 56, 0.1);
	glEnd();
}

void paredes_cuarto2(){
	//piso
	glBegin(GL_QUADS);
    glColor3f( 0.423 , 0.380 , 0.356 );
    glVertex3f(-15, 65, 0.1);
    glVertex3f(-15, 35, 0.1);
    glVertex3f(-50, 35, 0.1);
    glVertex3f(-50, 65, 0.1);
	
	//pared derecha
	glColor3f( 0.231 , 0.227 , 0.211 );//plomo oscuro
    glVertex3f(-15.01, 65, 0.1);
    glVertex3f(-15.01, 65, 20);
    glVertex3f(-15.01, 35, 20);
    glVertex3f(-15.01, 35, 0.1);
	//pared izquierda
    glVertex3f(-50, 35, 0.1);
    glVertex3f(-50, 35, 20);
    glVertex3f(-50, 65, 20);
    glVertex3f(-50, 65, 0.1);
	//pared trasera
    glVertex3f(-50, 65, 20);
    glVertex3f(-50, 65, 0.1);
    glVertex3f(-15.01, 65, 0.1);
    glVertex3f(-15.01, 65, 20);
	
	//pared delantera
	glVertex3f(-50, 35, 0.1);
    glVertex3f(-50, 35, 20);
    glVertex3f(-30, 35, 20);
    glVertex3f(-30, 35, 0.1);
    
	//puerta
	glColor3f(0.0 , 0.0 ,  0.0);
    glVertex3f(-30, 35, 0.1);
    glVertex3f(-22, 35, 0.1);
    glVertex3f(-22, 35, 15);
    glVertex3f(-30, 35, 15);
	//techo
	glColor3f(1.0 , 1.0 ,  1.0);
    glVertex3f(-50, 65, 20);
    glVertex3f(-15, 65, 20);
    glVertex3f(-15, 35, 20);
    glVertex3f(-50, 35, 20);
	//techo cuarto 1
	//pared cuarto 1
	glVertex3f(15, 66.01, 20);
    glVertex3f(15, 35.01, 20);
    glVertex3f(55, 35.01, 20);
    glVertex3f(55, 66.01, 20);
    glColor3f( 0.737 , 0.752 , 0.749 );//plomo
	//pared cuarto 1
	glVertex3f(15, 66.01, 20);
    glVertex3f(15, 66.01, 0.1);
    glVertex3f(55, 66.01, 0.1);
    glVertex3f(55, 66.01, 20);
    //pared tapar baño
    glVertex3f(15.04, 66.01, 20);
    glVertex3f(15.04, 35.01, 20);
    glVertex3f(15.04, 35.01, 0.1);
    glVertex3f(15.04, 66.01, 0.1);
	glEnd();
	
	
	glBegin(GL_POLYGON);
	glColor3f( 0.231 , 0.227 , 0.211 );//plomo oscuro
	//pared delantera
    glVertex3f(-15.01, 35, 20);
    glVertex3f(-15.01, 35, 0.1);
    glVertex3f(-22, 35, 0.1);
    glVertex3f(-22, 35, 15);
    
    glVertex3f(-30, 35, 15);
    glVertex3f(-30, 35, 20);
    
	glEnd();
	
	glBegin(GL_QUADS);
	glColor3f( 0.717 , 0.721 , 0.729 );
	glVertex3f(-42, 40, 0.15);
    glVertex3f(-30, 40, 0.15);
    glVertex3f(-30, 60, 0.15);
    glVertex3f(-42, 60, 0.15);
	glEnd();
	
	glBegin(GL_LINE_LOOP);
	glColor3f( 0.0 , 0.0 , 0.0 );
	glVertex3f(-42, 40, 0.15);
    glVertex3f(-30, 40, 0.15);
    glVertex3f(-30, 60, 0.15);
    glVertex3f(-42, 60, 0.15);
	glEnd();
	
	
	
}

void veladores(){
	glBegin(GL_QUADS);
	//Izquierda
    glColor3f( 0.737 , 0.752 , 0.749 );
    glVertex3f(-50.02, 35, 3.7);
    glVertex3f(-50, 44, 3.7);
    glVertex3f(-45, 44, 3.7);
    glVertex3f(-45.02, 35, 3.7);
    
    glVertex3f(-45, 44, 3.7);
    glVertex3f(-45.02, 35, 3.7);
    glVertex3f(-45.02, 35, 0.1);
    glVertex3f(-45, 44, 0.1);
    //derecha
    glVertex3f(-50, 56, 3.7);
    glVertex3f(-50, 65, 3.7);
    glVertex3f(-44, 64.98, 3.7);
    glVertex3f(-44, 56, 3.7);
    
    glVertex3f(-44, 64.98, 3.7);
    glVertex3f(-44, 56, 3.7);
    glVertex3f(-44, 56, 0.1);
    glVertex3f(-44, 64.98, 0.1);
    
	glEnd();
	//delineado
	glBegin(GL_LINES);
	//Izquierda
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-45.02, 35, 0.1);
    glVertex3f(-45, 44, 0.1);
    glVertex3f(-44, 56, 0.1);
    glVertex3f(-44, 64.98, 0.1);
    
    glEnd();
}

void PisoCuarto2(){
	glPushMatrix();
		glColor3f(0.87f, 0.87f, 0.87f);
		glTranslatef(0.0, -5.0, 0.0);
		glScalef(1.0, 0.04, 1.0);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1.5);
		glEnd();
	glPopMatrix();	
}

void ruedaSilla2(float x, float y, float z) {
	glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(x, y, z);
		glutSolidSphere(0.07, 100, 5);
	glPopMatrix();
}

void pataSilla2(float x, float y, float z, float ang) {
	glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(x, y, z);
		glRotatef(ang, 0.0, 1.0, 0.0);
		glScalef(1.0, 1.0, -3.1);
		glutSolidCube(0.11);
		glScalef(0.011, 0.011, 0.011);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1.5);			
	glPopMatrix();
}

void ejeSilla2() {
	glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(-2.975, -4.81, 1.7);
		glutSolidSphere(0.12, 10, 10);
	glPopMatrix();
}

void paloSilla2() {
	glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(-2.975, -4.35, 1.7);
		glScalef(0.1, 0.65, 0.1);
		glutSolidCube(1);
		glScalef(0.1, 0.1, 0.1);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1.5);			
	glPopMatrix();
}

void asiento2() {
	glPushMatrix();
		glColor3f(0.84, 0.84, 0.84);
		glTranslatef(-2.975, -4, 1.7);
		glRotatef(40, 0.0, 1.0, 0.0);
		glScalef(3.5, 1.0, 3.5);
		glutSolidCube(0.2);
		glScalef(0.02, 0.02, 0.02);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1.5);			
	glPopMatrix();
}

void respaldar2() {
	glPushMatrix();
		glColor3f(0.84, 0.84, 0.84);
		glTranslatef(-2.7, -3.4, 1.45);
		glRotatef(130, 0.0, 1.0, 0.0);
		glScalef(3.5, 6.9, 1.0);
		glutSolidCube(0.2);
		glScalef(0.02, 0.02, 0.02);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1.5);			
	glPopMatrix();
}

void posaBrazos2(float x, float y, float z) {
	glPushMatrix();
		glColor3f(0.1, 0.1, 0.1);
		glTranslatef(x, y, z);
		glRotatef(130, 0.0, 1.0, 0.0);
		glScalef(0.2, 0.1, 1.0);
		glutSolidCube(0.5);
		glScalef(0.05, 0.05, 0.05);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1.5);			
	glPopMatrix();
}

void paloPosaBrazos2(float x, float y, float z) {
	glPushMatrix();
		glColor3f(0.1, 0.1, 0.1);
		glTranslatef(x, y, z);
		glRotatef(130, 0.0, 1.0, 0.0);
		glRotatef(90, 1.0, 0.0, 0.0);
		glScalef(0.2, 0.1, 1.0);
		glutSolidCube(0.5);
		glScalef(0.05, 0.05, 0.05);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1.5);			
	glPopMatrix();
}

void SillaGamer2() {
	glPushMatrix();
	
	glScalef(1.8, 1.8, 1.8);
	
		///////////////////////////////////////////////////// RUEDAS SILLA ////////////////////////////////////////////////////////////////////////////////
		ruedaSilla(-3.01, -4.93, 2.1);
		ruedaSilla(-3.3, -4.93, 1.7);
		ruedaSilla(-3.01, -4.93, 1.3);
		ruedaSilla(-2.65, -4.93, 1.49);
		ruedaSilla(-2.65, -4.93, 1.91);
		
		//////////////////////////////////////////////////// EJE DE LA SILLA  //////////////////////////////////////////////////////////////////////////////////
		ejeSilla();
		
		///////////////////////////////////////////////////// PATAS SILLA ///////////////////////////////////////////////////////////////////////////////////
		pataSilla(-3, -4.81, 2, -8);
		pataSilla(-3.2, -4.81, 1.7, 90);
		pataSilla(-3, -4.81, 1.4, 8);
		pataSilla(-2.75, -4.81, 1.53, -60);
		pataSilla(-2.75, -4.81, 1.87, 60);
		
		///////////////////////////////////////////////////// PALO SILLA /////////////////////////////////////////////////////////////////////////////
		paloSilla();
		
		/////////////////////////////////////////////////////// ASIENTO SILLA //////////////////////////////////////////////////////////////////////////
		asiento();
		
		/////////////////////////////////////////////////////// RESPALDAR SILLA ////////////////////////////////////////////////////////////////////////
		respaldar(); 
		
		/////////////////////////////////////////////////////// POSA BRAZOS ///////////////////////////////////////////////////////////////////////////
		posaBrazos(-2.75, -3.5, 1.95);
		posaBrazos(-3.2, -3.5, 1.4);
		paloPosaBrazos(-2.75, -3.75, 1.95);
		paloPosaBrazos(-3.2, -3.75, 1.4);	
		
	glPopMatrix();
}

void Escritorio2(){
	glPushMatrix();
	glScalef(0.8, 1.0, 0.7);
	
	///////////////////////////////////////////// MESA ESCRITORIO ////////////////////////////////////////////////////////
	glPushMatrix();
		glColor3f(0.39f, 0.32f, 0.27f);
		glTranslatef(-3.95, -2.75, -2.0);
		glScalef(0.2, 0.01, 0.6);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1.5);		
		glEnd();
	glPopMatrix();	
	
	///////////////////////////////////////////// CAJON 1 ////////////////////////////////////////////////////////
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(-3.8, -3.2, 0.15);
		glScalef(0.18, 0.05, 0.13);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1.5);		
		glEnd();
	glPopMatrix();
		
	///////////////////////////////////////////// CAJON 2 ////////////////////////////////////////////////////////
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(-3.8, -3.8, 0.15);
		glScalef(0.18, 0.05, 0.13);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1.5);		
		glEnd();
	glPopMatrix();
			
	///////////////////////////////////////////// CAJON 3 ////////////////////////////////////////////////////////
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(-3.8, -4.4, 0.15);
		glScalef(0.18, 0.05, 0.13);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1.5);		
		glEnd();
	glPopMatrix();
	
	///////////////////////////////////////////// CAJONES GENERAL ESCRITORIO ////////////////////////////////////////////////////////
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(-3.95, -3.8, 0.15);
		glScalef(0.2, 0.195, 0.15);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1.5);		
		glEnd();
	glPopMatrix();	
	
	///////////////////////////////////////////// PATA ESCRITORIO ////////////////////////////////////////////////////////
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(-3.95, -3.8, -4.88);
		glScalef(0.2, 0.195, 0.01);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1.5);		
		glEnd();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-2.3, 1.0, -6.15);
	glScalef(0.5, 1.1, 1.8);

		//////////////////////////////////////////////////////////////// MONITOR 1 MARCO /////////////////////////////////////////////////////////////////////////////////////
		glPushMatrix();
		
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(-4.81, -2.7, 1.4);
		glScalef(0.01, 0.11, 0.11);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
		
		glPopMatrix();
	
		//////////////////////////////////////////////////////////////// MONITOR 1 /////////////////////////////////////////////////////////////////////////////////////
		glPushMatrix();
		
		glColor3f( 0.529 , 0.807 , 0.921 );
		glTranslatef(-4.8, -2.7, 1.4);
		glScalef(0.01, 0.1, 0.1);
		glutSolidCube(10);
		glColor3f(135, 206, 235);
		LineaCubo(1);	
		glEnd ();	
		
		glPopMatrix();

		//////////////////////////////////////////////////////////////// MONITOR 2 MARCO /////////////////////////////////////////////////////////////////////////////////////
		
		glPushMatrix();
		
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(-4.57, -2.7, 2.5);
		glRotatef(40, 0.0, 1.0, 0.0);
		glScalef(0.009, 0.11, 0.11);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);		
		glEnd();
		
		glPopMatrix();
		
		//////////////////////////////////////////////////////////////// MONITOR 2 /////////////////////////////////////////////////////////////////////////////////////
		
		glPushMatrix();
		
		glColor3f( 0.529 , 0.807 , 0.921 );
		glTranslatef(-4.56, -2.7, 2.5);
		glRotatef(40, 0.0, 1.0, 0.0);
		glScalef(0.01, 0.1, 0.1);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);		
		glEnd ();
		glPopMatrix();
		
		//////////////////////////////////////////////////////////////// RACK 1 /////////////////////////////////////////////////////////////////////////////////////
				
		glPushMatrix();
		
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(-5.1, -2.9, 1.4);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glScalef(0.2, 0.05, 0.05);
		cilindro = gluNewQuadric();
		gluQuadricDrawStyle(cilindro,GLU_FILL);
		gluCylinder(cilindro,1,1,10,20,20);
		
		glPopMatrix();						
		
		//////////////////////////////////////////////////////////////// RACK 2 /////////////////////////////////////////////////////////////////////////////////////
				
		glPushMatrix();
		
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(-4.8, -2.9, 2.5);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glScalef(0.2, 0.05, 0.05);
		cilindro = gluNewQuadric();
		gluQuadricDrawStyle(cilindro,GLU_FILL);
		gluCylinder(cilindro,1,1,10,20,20);	
		
		glPopMatrix();
		
		
		glPopMatrix();
			////////////////////////////////////////////////////////////////////////////// TECLADO //////////////////////////////////////////////////////////////////////////////////////
	
	glPushMatrix();
	
	glColor3f(0.59f, 0.6f, 0.6f);
	glTranslatef(-4.0, -2.63, -3.75);
	glRotatef(90, 0.0, 1.0, 0.0);
	glScalef(0.13, 0.006, 0.05);
	glutSolidCube(10);
	glColor3f(0.0f, 0.0f, 0.0f);
	LineaCubo(1.5);	
	
	glPopMatrix();

		glPushMatrix();
		
		glColor3f(0.08, 0.08, 0.08);
		glTranslatef(-4.98, -1.8, -2.5);
		glScalef(0.002, 0.15, 0.435);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1.5);
		
		glPopMatrix();
	
	////////////////////////////////////////////////////////////////////////////// MOUSE PAD ///////////////////////////////////////////////////////////////////////////////////////
	
	glPushMatrix();
	
	glColor3f(0.5f, 0.49f, 0.48f);
	glTranslatef(-4.0, -2.67, -3.5);
	glRotatef(90, 0.0, 1.0, 0.0);
	glScalef(0.2, 0.001, 0.1);
	glutSolidCube(10);
	glColor3f(0.0f, 0.0f, 0.0f);
	LineaCubo(1.5);	
	
	glPopMatrix();	
	glPopMatrix();
}

void TV2(){
	
	///////////////////////////////////////////// TV //////////////////////////////////////////////////////////////////////
	glPushMatrix();
	
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(-4.95, -0.9, 2.4);
		glScalef(0.0078, 0.25, 0.41);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1.5);

	glPopMatrix();
		
	///////////////////////////////////////////// TV DISPLAY //////////////////////////////////////////////////////////////////////
	glPushMatrix();
	
		glColor3f( RED1, GREEN1, BLUE1 );
		glTranslatef(-4.95, -0.9, 1.0);//(-4.95, -0.9, 2.4)
		glScalef(0.008, 0.23, 0.095);//glScalef(0.008, 0.23, 0.39)
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1.5);

	glPopMatrix();

    glPushMatrix();
	
		glColor3f( RED2, GREEN2, BLUE2 );
		glTranslatef(-4.95, -0.9, 1.95);
		glScalef(0.008, 0.23, 0.095);//glScalef(0.008, 0.23, 0.39)
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1.5);

	glPopMatrix();

    glPushMatrix();
	
		glColor3f( RED3, GREEN3, BLUE3 );
		glTranslatef(-4.95, -0.9, 2.9);
		glScalef(0.008, 0.23, 0.095);//glScalef(0.008, 0.23, 0.39)
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1.5);

	glPopMatrix();
    glPushMatrix();
	
		glColor3f( RED4, GREEN4, BLUE4 );
		glTranslatef(-4.95, -0.9, 3.85);
		glScalef(0.008, 0.23, 0.095);//glScalef(0.008, 0.23, 0.39)
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1.5);

	glPopMatrix();
	//ImagenTV();		
	
	///////////////////////////////////////////// TV //////////////////////////////////////////////////////////////////////
	glPushMatrix();
		
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(-4.96, -2.5, 2.4);
		glRotatef(90, 1.0, 0.0, 0.0);
		glScalef(0.01, 0.3, 0.01);//glScalef(0.01, 0.3, 0.01)
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1.5);
	glPopMatrix();
	
}

void cuarto2(){
	cama();
	veladores();
	paredes_cuarto2();
	glPushMatrix();
	glTranslated(-34,51,15.7);
	glRotated(90,1,0,0);
	glRotated(180,0,-1,0);
	glScaled(3.8,3,3);
    glPushMatrix();
        glRotatef(-45,0,1,0);
        glTranslatef(posXPericote,0.0,0.0);
        DibujarPericote2();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(2.5, 4.0, -5.0);
        SillaGamer2();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-1.0, 0.0, 0.03);
        Escritorio2();
    glPopMatrix();
    glPushMatrix();
        TV2();
    glPopMatrix();
	glPopMatrix();	
	
}

//------------------------PASILLO-------------------------

void pasillo(){
	glBegin(GL_QUADS);
    //pared 1 
    glColor3f( 0.737 , 0.752 , 0.749 );//plomo
    glVertex3f(-50, 35, 0.1);
    glVertex3f(-50, 35, 20);
    glVertex3f(-50, 25, 20);
    glVertex3f(-50, 25, 0.1);
    //pared2-fondo
    
    glVertex3f(55, 35, 0.1);
    glVertex3f(55, 35, 20);
    glVertex3f(55, 25, 20);
    glVertex3f(55, 25, 0.1);
    
    glColor3f( 0.341 , 0.278 , 0.235 );//marron OSCURO
	//piso
    
    glVertex3f(-50, 35, 0.1);
    glVertex3f(-50, 25, 0.1);
    glVertex3f(55, 25, 0.1);
    glVertex3f(55, 35, 0.1);
    
    glColor3f( 1.0 , 1.0 , 1.0 );//blanco
    //techo
    
    glVertex3f(-50, 35, 20);
    glVertex3f(-50, 25, 20);
    glVertex3f(55, 25, 20);
    glVertex3f(55, 35, 20);
    glEnd();
}

void Radio(){
	//caja radio
	glPushMatrix();
	glTranslated(-104,-10,-3.2);
	glBegin(GL_POLYGON);
	glColor3f( 0.658 , 0.403 , 0.294 ); //semi marrron :v
	glVertex3f(54, 9, 5.2);
	glVertex3f(56, 9, 5.2);
	glVertex3f(56, 9, 4);
	glVertex3f(54, 9, 4);
	glEnd();
	//caja trasera radio 
	glBegin(GL_POLYGON);
	glColor3f( 0.658 , 0.403 , 0.294 ); //semi marrron :v
	glVertex3f(54, 9, 5.2);
	glVertex3f(54, 12, 5.2);
	glVertex3f(54, 12, 4);
	glVertex3f(54, 9, 4);
	glEnd();
	//caja der radio 
	glBegin(GL_POLYGON);
	glColor3f( 0.658 , 0.403 , 0.294 ); //semi marrron :v
	glVertex3f(54, 12, 5.2);
	glVertex3f(56, 12, 5.2);
	glVertex3f(56, 12, 4);
	glVertex3f(54, 12, 4);
	glEnd();
	//caja der radio 
	glBegin(GL_POLYGON);
	glColor3f( 0.658 , 0.403 , 0.294 ); //semi marrron :v
	glVertex3f(54, 12, 4);
	glVertex3f(56, 12, 4);
	glVertex3f(56, 9, 4);
	glVertex3f(54, 9, 4);
	glEnd();
	//techo radio
	glBegin(GL_POLYGON);
	glColor3f( 0.658 , 0.403 , 0.294 ); //semi marrron :v
	glVertex3f(54, 9, 5.2);
	glVertex3f(54, 12, 5.2);
	glVertex3f(56, 12, 5.2);
	glVertex3f(56, 9, 5.2);
	glEnd();
	//techo radio
	glBegin(GL_POLYGON);
	glColor3f( 0.572 , 0.450 , 0.329 );; //semi marrron :v
	glVertex3f(56, 9, 5.2);
	glVertex3f(56, 12, 5.2);
	glVertex3f(56, 12, 4.56);
	glVertex3f(56, 9, 4.56);
	glEnd();
	//frente 1 arriba
	glBegin(GL_POLYGON);
	glColor3f( 0.572 , 0.450 , 0.329 ); //semi marrron :v
	glVertex3f(56, 9, 5.2);
	glVertex3f(56, 12, 5.2);
	glVertex3f(56, 12, 4.56);
	glVertex3f(56, 9, 4.56);
	glEnd();
	//frente 2 bajo
	glBegin(GL_POLYGON);
	glColor3f( 0.278 , 0.152 , 0.156 ); //semi marrron :v
	glVertex3f(56, 9, 4.56);
	glVertex3f(56, 12, 4.56);
	glVertex3f(56, 12, 4);
	glVertex3f(56, 9, 4);
	glEnd();
	//linea radio
	glBegin(GL_LINE_LOOP);
	glColor3f( 0.521 , 0.392 , 0.149 ); //semi marrron :v
	glVertex3f(56.1, 10, 4.2);
	glVertex3f(56.1, 11, 4.2);
	glEnd();
	//boton izq
	glBegin(GL_POLYGON);
	glColor3f( 0.674 , 0.666 , 0.670 ); //griss :v
	glVertex3f(56.1, 9.5, 4.31);
	glVertex3f(56.1, 9.7, 4.31);
	glVertex3f(56.1, 9.7, 4.2);
	glVertex3f(56.1, 9.5, 4.2);
	glEnd();
	//boton der
	glBegin(GL_POLYGON);
	glColor3f( 0.674 , 0.666 , 0.670 ); //griss :v
	glVertex3f(56.1, 11.3, 4.31);
	glVertex3f(56.1, 11.5, 4.31);
	glVertex3f(56.1, 11.5, 4.2);
	glVertex3f(56.1, 11.3, 4.2);
	glEnd();
	//antena radio izq
	glBegin(GL_LINE_LOOP);
	glColor3f( 0 , 0 , 0 ); //semi marrron :v
	glVertex3f(55, 9.8, 6.2);
	glVertex3f(55, 10.5, 5.2);
	glEnd();
	//antena radio der
	glBegin(GL_LINE_LOOP);
	glColor3f( 0 , 0 , 0 ); //semi marrron :v
	glVertex3f(55, 10.5, 5.2);
	glVertex3f(55, 11.2, 6.2);
	glEnd();
	glPopMatrix();
	
}

void terraza(){
	
// Base de terraza

glBegin(GL_QUADS);

glColor3f(0.9490f,0.9058f,0.8431f);

glVertex3f(54.5, 25, 20.1);
glVertex3f(54.5, -25, 20.1);
glVertex3f(-15, -25, 20.1);
glVertex3f(-15, 25, 20.1);
glEnd();


// -----  VALLAS PARA BASE Y POSABRAZOS  --------

// valla atras inferior
glPushMatrix();
		
		glColor3f(0.1725, 0.0862, 0.0666);
	
		glTranslatef(19.9,-24.53,20.20);
	
		glScalef(07.0, 0.10, 0.038);
			
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();
		
	
// valla atras superior

//** parte izq
glPushMatrix();
		
		glColor3f(0.1725, 0.0862, 0.0666);
	
		glTranslatef(-6.1,-24.53,28.80);
	
		glScalef(1.8, 0.10, 0.038);
			
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();	
	
// **parte der
glPushMatrix();
		
		glColor3f(0.1725, 0.0862, 0.0666);
	
		glTranslatef(33.9,-24.53,28.80);
	
		glScalef(4.2, 0.10, 0.038);
			
		glutSolidCube(10);
		
		glColor3f(0.0f, 0.0f, 0.0f);
		
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();			
		
// valla delante inferior
glPushMatrix();
		
		glColor3f(0.1725, 0.0862, 0.0666);
	
		glTranslatef(19.9,24.53,20.20);
	
		glScalef(07.0, 0.10, 0.038);
			
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();
		
		
		

// valla izq inferior (piscina)
glPushMatrix();
		
		glColor3f(0.1725, 0.0862, 0.0666);
	
		glTranslatef(-14.8,0.0,20.20);
	
		glScalef(0.10, 5.00, 0.038);
			
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();
		
// valla izq superior (piscina)
glPushMatrix();
		
		glColor3f(0.1725, 0.0862, 0.0666);
	
		glTranslatef(-14.8,0.0,28.80);
	
		glScalef(0.10, 5.00, 0.038);
			
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();		
// valla der inferior (calle)
glPushMatrix();
		
		glColor3f(0.1725, 0.0862, 0.0666);
	
		glTranslatef(54.4,0.0,20.0);
		
		glScalef(0.10, 5.00, 0.038);
			
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();	
// valla der superior (calle)
glPushMatrix();
		
		glColor3f(0.1725, 0.0862, 0.0666);
	
		glTranslatef(54.4,0.0,28.80);
		
		glScalef(0.10, 5.00, 0.038);
			
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();	
		
//   VALLAS PARADAS
// vallas izq paradas (piscina)	
		
		//--var 1
		
		glPushMatrix();
		
		
		glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(-14.8,-24.0,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();
		
		//--var 2
		
		glPushMatrix();
		
		
		glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(-14.8,-21.0,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();
		
		//--var 3
		
		glPushMatrix();
		
		
		glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(-14.8,-18.0,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();
		
		
		//--var 4
		
		glPushMatrix();
		
		glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(-14.8,-15.0,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();

		//-- var  5
		glPushMatrix();
		
		glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(-14.8,-12.0,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();

		//-- var  6
		glPushMatrix();
		
		glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(-14.8,-9.0,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();
		
		//-- var 7
		glPushMatrix();
		
		glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(-14.8,-6.0,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();
		
		//-- var 8
		glPushMatrix();
		
		glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(-14.8,-3.0,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();
		
		//--var 9	
		glPushMatrix();
		
		glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(-14.8,0.0,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();
		
		//--var 10
		glPushMatrix();
		glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(-14.8,3.0,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();		
		glPopMatrix();	
		
		//--var 11
		glPushMatrix();
		glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(-14.8,6.0,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();		
		glPopMatrix();
		
		//--var 12
		glPushMatrix();
		glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(-14.8,9.0,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();		
		glPopMatrix();	
		
		//--var 13
		glPushMatrix();
		glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(-14.8,12.0,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();		
		glPopMatrix();
		
		//--var 14
		glPushMatrix();
		glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(-14.8,15.0,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();		
		glPopMatrix();
		
		//--var 15
		
		glPushMatrix();
		glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(-14.8,18.0,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();		
		glPopMatrix();
		
		//--var 16
		
		glPushMatrix();
		glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(-14.8,21.0,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();		
		glPopMatrix();
		
		//--var 17
		
		glPushMatrix();
	glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(-14.8,24.0,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();		
		glPopMatrix();
		
// vallas der paradas (calle)	
		
		//--var 1
		
		glPushMatrix();
		
		glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(54.4,-24.0,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();
		
		//--var 2
		
		glPushMatrix();
		
		glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(54.4,-21.0,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();
		
		//--var 3
		
		glPushMatrix();
		
		glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(54.4,-18.0,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();
		
		
		//--var 4
		
		glPushMatrix();
		
		glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(54.4,-15.0,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();

		//-- var  5
		glPushMatrix();
		
		glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(54.4,-12.0,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();

		//-- var  6
		glPushMatrix();
		
		glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(54.4,-9.0,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();
		
		//-- var 7
		glPushMatrix();
		
		glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(54.4,-6.0,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();
		
		//-- var 8
		glPushMatrix();
		
		glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(54.4,-3.0,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();
		
		//--var 9	
		glPushMatrix();
		
		glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(54.4,0.0,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();
		
		//--var 10
		glPushMatrix();
		glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(54.4,3.0,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();		
		glPopMatrix();	
		
		//--var 11
		glPushMatrix();
	glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(54.4,6.0,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();		
		glPopMatrix();
		
		//--var 12
		glPushMatrix();
	glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(54.4,9.0,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();		
		glPopMatrix();	
		
		//--var 13
		glPushMatrix();
	glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(54.4,12.0,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();		
		glPopMatrix();
		
		//--var 14
		glPushMatrix();
		glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(54.4,15.0,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();		
		glPopMatrix();
		
		//--var 15
		
		glPushMatrix();
	glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(54.4,18.0,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();		
		glPopMatrix();
		
		//--var 16
		
		glPushMatrix();
	glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(54.4,21.0,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();		
		glPopMatrix();
		
		//--var 17
		
		glPushMatrix();
	glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(54.4,24.0,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();		
		glPopMatrix();
		
	// varillas hacia la escalera
	
	//--var 1
		
		glPushMatrix();
		
	glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(-12.8,-24.5,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();
	
		//--var 2
		
		glPushMatrix();
		
	glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(-9.8,-24.5,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();
	
		//--var 3
		
		glPushMatrix();
		
	glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(-6.8,-24.5,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();	
		
	   //--var 4
	
		
		glPushMatrix();
		
	glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(-3.8,-24.5,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();	
		
		//--var 5
	
		
		glPushMatrix();
		
	glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(-0.8,-24.5,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();
			
		
	// ---> para puerta
		//**lado izq
		
		glPushMatrix();
		
		glColor3f(0.1725, 0.0862, 0.0666);
	
		glTranslatef(2.4,-24.5,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();	
		
		//***lado der
		
		glPushMatrix();
		
		glColor3f(0.1725, 0.0862, 0.0666);
	
		glTranslatef(13.6,-24.5,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();	
		
		//***lado superior
		
		glPushMatrix();
		
		glColor3f(0.1725, 0.0862, 0.0666);
	
		glTranslatef(8.0,-24.5,27.85);
	
		//glScalef(0.06, 0.06, 0.85);
		glScalef(1.10, 0.06, 0.038);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();
		
		//***relleno de puerta
		
		glPushMatrix();
		
		//glColor3f(1.0, 1.0, 1.0);
		glColor3f(0.7372, 0.6431, 0.5333);
	
		glTranslatef(8.0,-24.5,24.15);
	
		//glScalef(0.06, 0.06, 0.85);
		glScalef(1.10, 0.02, 0.70);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();
		
		//cubito(manija) atras
		
		glPushMatrix();
		
		glColor3f(0.0, 0.0, 0.0);
	
		glTranslatef(11.7,-24.8,24.65);
	
		glScalef(0.03, 0.03, 0.03);
		
		glutSolidCube(10);
		glColor3f(1.0f, 1.0f, 1.0f);
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();
		
		//manija (manija) atras
		
		glPushMatrix();
		
		glColor3f(0.0, 0.0, 0.0);
	
		glTranslatef(11.7,-25.1,24.65);
	
		glScalef(0.03, 0.03, 0.03);
		
		glutSolidSphere(11,20,20);
		
		glColor3f(1.0f, 1.0f, 1.0f);
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();
		
		
			//cubito(manija) adelante
		
		glPushMatrix();
		
		glColor3f(0.0, 0.0, 0.0);
	
		glTranslatef(11.7,-24.2,24.65);
	
		glScalef(0.03, 0.03, 0.03);
		
		glutSolidCube(10);
		glColor3f(1.0f, 1.0f, 1.0f);
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();
		
			//manija (manija) adelante
		
		glPushMatrix();
		
		glColor3f(0.0, 0.0, 0.0);
	
		glTranslatef(11.7,-23.9,24.65);
	
		glScalef(0.03, 0.03, 0.03);
		
		glutSolidSphere(11,20,20);
		
		glColor3f(1.0f, 1.0f, 1.0f);
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();
		
		//--var 6
		
		glPushMatrix();
		
		glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(16.6,-24.5,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();
		
		//--var 7
		
		glPushMatrix();
		
	glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(19.6,-24.5,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();
	
		//--var 8
		
		glPushMatrix();
		
	glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(22.6,-24.5,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();	
		
	//--var 9
		
		glPushMatrix();
		
		glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(25.6,-24.5,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();	
		//--var 10
		
		glPushMatrix();
		
		glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(28.6,-24.5,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();	
		
		//--var 11
		
		glPushMatrix();
		
		glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(31.6,-24.5,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();
		
	//--var 12
		
		glPushMatrix();
		
		glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(34.6,-24.5,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();
			
	//--var 13
		
		glPushMatrix();
		
		glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(37.6,-24.5,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();	
		//--var 14
		
		glPushMatrix();
		
		glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(40.6,-24.5,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();
			//--var 15
		
		glPushMatrix();
		
		glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(43.6,-24.5,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();	
		//--var 16
		
		glPushMatrix();
		
		glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(46.6,-24.5,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();
		
	//--var 17
		
		glPushMatrix();
		
		glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(49.6,-24.5,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();	
		
		//--var 18
		
		glPushMatrix();
		
		glColor3f(0.2078, 0.2431, 0.2627);
	
		glTranslatef(52.6,-24.5,24.65);
	
		glScalef(0.06, 0.06, 0.85);
		
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		glPopMatrix();			
}		

void escalera() {
		
	//>>> Peldanios
		
	// p1
	glPushMatrix();
		
		
		glColor3f(0.8862, 0.6196, 0.3843);
	
		glTranslatef(32.0,-47.53,1.80);
	
		//glScalef(0.13, 3.796, 0.038);
		glScalef(0.35, 1.00, 0.068);
			
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();
	
		// p2
	glPushMatrix();
		
		
		glColor3f(0.8862, 0.6196, 0.3843);
	
		glTranslatef(28.0,-47.53,3.80);
	
		//glScalef(0.13, 3.796, 0.038);
		glScalef(0.35, 1.00, 0.068);
			
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();
		
		// p3
	glPushMatrix();
		
		//glColor3f(1.0, 1.0, 0.960);
		glColor3f(0.8862, 0.6196, 0.3843);
	
		glTranslatef(24.0,-47.53,5.80);
	
		glScalef(0.35, 1.00, 0.068);
			
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();
		
			// p4
	glPushMatrix();
		
		//glColor3f(1.0, 1.0, 0.960);
		glColor3f(0.8862, 0.6196, 0.3843);
	
		glTranslatef(20.0,-47.53,7.80);
	
		glScalef(0.35, 1.00, 0.068);
			
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();
		
			// p5
	glPushMatrix();
		
	
		glColor3f(0.8862, 0.6196, 0.3843);
	
		glTranslatef(16.0,-47.53,9.80);
	
		glScalef(0.35, 1.00, 0.068);
			
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();
		
		//  P DESCANSO 
	glPushMatrix();
		
		
		glColor3f(0.8862, 0.6196, 0.3843);
	
		glTranslatef(7.8,-47.53,11.50);
	
		glScalef(1.20, 1.20, 0.10);
			
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();
		
		// p6
	glPushMatrix();
		
		
		glColor3f(0.8862, 0.6196, 0.3843);
	
		glTranslatef(8.0,-39.53,13.80);
	
		glScalef(1.00, 0.35, 0.068);
			
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();
		
		// p7
	glPushMatrix();
		
		glColor3f(0.8862, 0.6196, 0.3843);
	
		glTranslatef(8.0,-35.53,15.80);
	
		glScalef(1.00, 0.35, 0.068);
			
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();
			
		// p8
	glPushMatrix();
		
		glColor3f(0.8862, 0.6196, 0.3843);
	
		glTranslatef(8.0,-31.53,17.80);
	
		glScalef(1.00, 0.35, 0.068);
			
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();	
	
		//p9
		
	glPushMatrix();
		
		glColor3f(0.8862, 0.6196, 0.3843);
	
		glTranslatef(8.0,-27.53,19.80);
	
		glScalef(1.00, 0.55, 0.068);
			
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();	
			
	//>> costados de escalera <<
	
	// lado izq (base)
	 	glPushMatrix();
		
		
		glColor3f(0.2235, 0.1098, 0.0627);
	
		glTranslatef(24.30,-53.00,6.98);
		glRotated(-67,0,1,0);
		
	
		glScalef(0.40, 0.08, 2.40);
			
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();
		
	// lado der (base)
	 	glPushMatrix();
		
		glColor3f(0.2235, 0.1098, 0.0627);
	
		glTranslatef(24.30,-42.00,6.98);
		glRotated(-67,0,1,0);
		
	
		glScalef(0.40, 0.08, 2.40);
			
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();
		
		
		// lado detras(descanso)
	 	glPushMatrix();
		
		glColor3f(0.2235, 0.1098, 0.0627);
	
		glTranslatef(7.8,-53.00,11.78);
		
		glScalef(1.25, 0.08, 0.40);
			
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();
		
		// lado izq(descanso)
	 	glPushMatrix();
		
		glColor3f(0.2235, 0.1098, 0.0627);
	
		glTranslatef(1.8,-47.00,11.78);
		
		glScalef(0.08, 1.20, 0.40);
			
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();
		
		
		
		
		// lado der (puerta)
	 	glPushMatrix();
		
		glColor3f(0.2235, 0.1098, 0.0627);
	
		glTranslatef(13.45,-33.50,16.78);
		glRotated(-60,1,0,0);
		
		glScalef(0.08, 0.40, 1.98);
			
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();
		
		// lado izq (puerta)
	 	glPushMatrix();
		
		glColor3f(0.2235, 0.1098, 0.0627);
	
		glTranslatef(2.45,-33.50,16.78);
		glRotated(-60,1,0,0);
		
		glScalef(0.08, 0.40, 1.98);
			
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
		
		glPopMatrix();
		
}


void cuarto_segundo_piso(){

//PISO
glBegin(GL_QUADS);
glColor3f(0.4, 0.3, 0.0);
glVertex3f(-50, 24.8, 20.12);
glVertex3f(-50, 66.5, 20.12);
glVertex3f(55, 66.5, 20.12); 
glVertex3f(55, 24.8, 20.12);
glEnd();

//--PARED ALFRENTE------

glBegin(GL_QUADS);
glColor3f(1.0, 1.0, 0.9);
glVertex3f(55, 24.8, 20.05);
glVertex3f(55, 24.8, 45.05);
glVertex3f(55, 66.5, 45.05); 
glVertex3f(55, 66.5, 20.05);
glEnd();

glBegin(GL_QUADS);
glColor3f(0.9, 0.9, 0.5);
glVertex3f(55.05, 24.8, 0.01);
glVertex3f(55.05, 24.8, 45.05);
glVertex3f(55.05, 66.5, 45.05); 
glVertex3f(55.05, 66.5, 0.01);
glEnd();

//--PARED FONDO------

glBegin(GL_QUADS);
glColor3f(1.0, 1.0, 0.9);
glVertex3f(-50, 24.8, 20.05);
glVertex3f(-50, 24.8, 45.05);
glVertex3f(-50, 66.5, 45.05); 
glVertex3f(-50, 66.5, 20.05);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f(0.0, 0.0, 0.0);
glVertex3f(-50, 24.82, 20.07);
glVertex3f(-50, 24.82, 45.05);
glVertex3f(-50, 66.47, 45.05); 
glVertex3f(-50, 66.47, 20.07);
glEnd();


glBegin(GL_QUADS);
glColor3f(0.9, 0.9, 0.5);
glVertex3f(-50.12, 24.8, 0.01);
glVertex3f(-50.12, 24.8, 45.05);
glVertex3f(-50.12, 66.5, 45.05); 
glVertex3f(-50.12, 66.5, 0.01);
glEnd();

glBegin(GL_QUADS);
glColor3f(0.9, 0.9, 0.5);
glVertex3f(-50.12, 24.8, 0.01);
glVertex3f(-50.12, 24.8, 20.05);
glVertex3f(-50.12, -55, 20.05); 
glVertex3f(-50.12, -55, 0.01);
glEnd();

//--PARED IZQUIERDA------

glBegin(GL_QUADS);
glColor3f(1.0, 1.0, 0.9);
glVertex3f(-50, 24.8, 20.05);
glVertex3f(-50, 24.8, 45.05);
glVertex3f(55, 24.8, 45.05); 
glVertex3f(55, 24.8, 20.05);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f(0.0, 0.0, 0.0);
glVertex3f(-49.9, 24.81, 20.07);
glVertex3f(-49.9, 24.81, 45.05);
glVertex3f(54.9, 24.81, 45.05); 
glVertex3f(54.9, 24.81, 20.07);
glEnd();


glBegin(GL_QUADS);
glColor3f(0.9, 0.9, 0.5);
glVertex3f(-50.12, -55.1, 0.01);
glVertex3f(-50.12, -55.1, 20.05);
glVertex3f(55, -55.1, 20.05); 
glVertex3f(55, -55.1, 0.01);
glEnd();

//--PARED DERECHA------ 
glBegin(GL_QUADS);
glColor3f(1.0, 1.0, 0.9);
glVertex3f(-50, 66.5, 20.05);
glVertex3f(-50, 66.5, 45.05);
glVertex3f(55, 66.5, 45.05); 
glVertex3f(55, 66.5, 20.05);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f(0.0, 0.0, 0.0);
glVertex3f(-49.9, 66.5, 20.07);
glVertex3f(-49.9, 66.5, 45.05);
glVertex3f(54.9, 66.5, 45.05); 
glVertex3f(54.9, 66.5, 20.07);
glEnd();

glBegin(GL_QUADS);
glColor3f(0.9, 0.9, 0.5);
glVertex3f(-50.12, 66.51, 0.01);
glVertex3f(-50.12, 66.51, 45.05);
glVertex3f(55, 66.51, 45.05); 
glVertex3f(55, 66.51, 0.01);
glEnd();

//TECHO

glBegin(GL_QUADS);
glColor3f(0.1, 0.0, 0.1); 
glVertex3f(-50, 24.8, 45.05);
glVertex3f(-50, 66.5, 45.05);
glVertex3f(55, 66.5, 45.05); 
glVertex3f(55, 24.8, 45.05);
glEnd();

	
}

void mesas(){
	
	//parte fondo
	glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-49.5, 34, 20.12);
    glVertex3f(-49.5, 34, 24);
    glVertex3f(-49.5, 56, 24); 
    glVertex3f(-49.5, 56, 20.12);
    glEnd();
    
    //linea parte fondo
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-49.5, 34, 20.12);
    glVertex3f(-49.5, 34, 24);
    glVertex3f(-49.5, 56, 24); 
    glVertex3f(-49.5, 56, 20.12);
    glEnd();
    
    //parte delantera
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-38.5, 34, 20.12);
    glVertex3f(-38.5, 34, 24);
    glVertex3f(-38.5, 56, 24); 
    glVertex3f(-38.5, 56, 20.12);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-38.49, 40, 20.12);
	glVertex3f(-38.49, 40, 24);
	glVertex3f(-38.49, 40, 24);
    glVertex3f(-38.49, 40, 20.12);
	
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-38.49, 49, 20.12);
	glVertex3f(-38.49, 49, 24);
	glVertex3f(-38.49, 49, 24);
    glVertex3f(-38.49, 49, 20.12);
		
    //linea parte delantera
    glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-38.5, 34, 20.12);
    glVertex3f(-38.5, 34, 24);
    glVertex3f(-38.5, 56, 24); 
    glVertex3f(-38.5, 56, 20.12);
    glEnd();
    
    //lado izquierdo
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-49.5, 34, 20.12);
    glVertex3f(-49.5, 34, 24);
    glVertex3f(-38.5, 34, 24); 
    glVertex3f(-38.5, 34, 20.12);
    glEnd();
    
    //linea lado izquierdo
    glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-49.5, 34, 20.12);
    glVertex3f(-49.5, 34, 24);
    glVertex3f(-38.5, 34, 24); 
    glVertex3f(-38.5, 34, 20.12);
    glEnd();
    
    //lado derecho
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-49.5, 56, 20.12);
    glVertex3f(-49.5, 56, 24);
    glVertex3f(-38.5, 56, 24); 
    glVertex3f(-38.5, 56, 20.12);
    glEnd();
    
    //linea lado derecho
    glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-49.5, 56, 20.12);
    glVertex3f(-49.5, 56, 24);
    glVertex3f(-38.5, 56, 24); 
    glVertex3f(-38.5, 56, 20.12);
    glEnd();
    
    //encima
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-49.5, 34, 24);
    glVertex3f(-49.5, 56, 24);
    glVertex3f(-38.5, 56, 24); 
    glVertex3f(-38.5, 34, 24);
    glEnd();
    
    //linea encima
    glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-49.5, 34, 24);
    glVertex3f(-49.5, 56, 24);
    glVertex3f(-38.5, 56, 24); 
    glVertex3f(-38.5, 34, 24);
    glEnd();
    
    //*********************** DVD ********************
    //base del dvd
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-47, 39, 24.01);
    glVertex3f(-47, 44, 24.01);
    glVertex3f(-42, 44, 24.01); 
    glVertex3f(-42, 39, 24.01);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(-47, 39, 24.01);
    glVertex3f(-47, 44, 24.01);
    glVertex3f(-42, 44, 24.01); 
    glVertex3f(-42, 39, 24.01);
    glEnd();
	
    //encima dvd
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-47, 39, 25.01);
    glVertex3f(-47, 44, 25.01);
    glVertex3f(-42, 44, 25.01); 
    glVertex3f(-42, 39, 25.01);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
	glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-47, 39, 25.01);
    glVertex3f(-47, 44, 25.01);
    glVertex3f(-42, 44, 25.01); 
    glVertex3f(-42, 39, 25.01);
    glEnd();
    
    //fondo dvd 
	glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-47, 39, 24.01);
    glVertex3f(-47, 39, 25.01);
    glVertex3f(-47, 44, 25.01); 
    glVertex3f(-47, 44, 24.01);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(-47, 39, 24.01);
    glVertex3f(-47, 39, 25.01);
    glVertex3f(-47, 44, 25.01); 
    glVertex3f(-47, 44, 24.01);
    glEnd();
    
    //parte delantera dvd
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-42, 39, 24.01);
    glVertex3f(-42, 39, 25.01);
    glVertex3f(-42, 44, 25.01); 
    glVertex3f(-42, 44, 24.01);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(-42, 39, 24.01);
    glVertex3f(-42, 39, 25.01);
    glVertex3f(-42, 44, 25.01); 
    glVertex3f(-42, 44, 24.01);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
	glColor3f(0.9, 0.0, 0.0);
	glVertex3f(-41.99, 39, 24.5);
    glVertex3f(-41.99, 44, 24.5);
    glVertex3f(-41.99, 44, 24.5); 
    glVertex3f(-41.99, 39, 24.5);
    glEnd();
    
    //lado izquierdo dvd
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-47, 39, 24.01);
    glVertex3f(-47, 39, 25.01);
    glVertex3f(-42, 39, 25.01); 
    glVertex3f(-42, 39, 24.01);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(-47, 39, 24.01);
    glVertex3f(-47, 39, 25.01);
    glVertex3f(-42, 39, 25.01); 
    glVertex3f(-42, 39, 24.01);
    glEnd();
	
    //lado derecho dvd
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-47, 44, 24.01);
    glVertex3f(-47, 44, 25.01);
    glVertex3f(-42, 44, 25.01); 
    glVertex3f(-42, 44, 24.01);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(-47, 44, 24.01);
    glVertex3f(-47, 44, 25.01);
    glVertex3f(-42, 44, 25.01); 
    glVertex3f(-42, 44, 24.01);
    glEnd();
	
	//********************** CONTROL REMOTO ***********************
	//base
	glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-47.5, 47, 24.01);
    glVertex3f(-47.5, 48, 24.01);
    glVertex3f(-42, 48, 24.01); 
    glVertex3f(-42, 47, 24.01);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(-47.5, 47, 24.01);
    glVertex3f(-47.5, 48, 24.01);
    glVertex3f(-42, 48, 24.01); 
    glVertex3f(-42, 47, 24.01);
    glEnd();
    
    //encima
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-47.5, 47, 24.50);
    glVertex3f(-47.5, 48, 24.50);
    glVertex3f(-42, 48, 24.50); 
    glVertex3f(-42, 47, 24.50);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(-47.5, 47, 24.50);
    glVertex3f(-47.5, 48, 24.50);
    glVertex3f(-42, 48, 24.50); 
    glVertex3f(-42, 47, 24.50);
    glEnd();
    
    //lado izquierdo control
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-47.5, 47, 24.01);
    glVertex3f(-47.5, 47, 24.50);
    glVertex3f(-42, 47, 24.50); 
    glVertex3f(-42, 47, 24.01);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(-47.5, 47, 24.01);
    glVertex3f(-47.5, 47, 24.50);
    glVertex3f(-42, 47, 24.50); 
    glVertex3f(-42, 47, 24.01);
    glEnd();
	
    //lado derecho control
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-47.5, 48, 24.01);
    glVertex3f(-47.5, 48, 24.50);
    glVertex3f(-42, 48, 24.50); 
    glVertex3f(-42, 48, 24.01);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
	glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-47.5, 48, 24.01);
    glVertex3f(-47.5, 48, 24.50);
    glVertex3f(-42, 48, 24.50); 
    glVertex3f(-42, 48, 24.01);
    glEnd();
    
    
    //********************************** MESA CENTRO ********************************
    //parte fondo
	glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-28, 39, 20.12);
    glVertex3f(-28, 39, 23);
    glVertex3f(-28, 50, 23); 
    glVertex3f(-28, 50, 20.12);
    glEnd();
    
    //linea fondo
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-28, 39, 20.12);
    glVertex3f(-28, 39, 23);
    glVertex3f(-28, 50, 23);
    glVertex3f(-28, 50, 20.12);
	glEnd();
    
    //parte delantera
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-22, 39, 20.12);
    glVertex3f(-22, 39, 23);
    glVertex3f(-22, 50, 23); 
    glVertex3f(-22, 50, 20.12);
    glEnd();
    
    //linea delantera
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-22, 39, 20.12);
    glVertex3f(-22, 39, 23);
    glVertex3f(-22, 50, 23);
    glVertex3f(-22, 50, 20.12);
	glEnd();
    
    //lado izquierdo
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-28, 39, 20.12);
    glVertex3f(-28, 39, 23);
    glVertex3f(-22, 39, 23); 
    glVertex3f(-22, 39, 20.12);
    glEnd();
    
    //linea izquierda
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-28, 39, 20.12);
    glVertex3f(-28, 39, 23);
    glVertex3f(-22, 39, 23);
    glVertex3f(-22, 39, 20.12);
	glEnd();
    
    //lado derecho
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-28, 50, 20.12);
    glVertex3f(-28, 50, 23);
    glVertex3f(-22, 50, 23); 
    glVertex3f(-22, 50, 20.12);
    glEnd();
    
    //linea derecha
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-28, 50, 20.15);
    glVertex3f(-28, 50, 23);
    glVertex3f(-22, 50, 23);
    glVertex3f(-22, 50, 20.15);
	glEnd();
	
    //encima
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-28, 39, 23);
    glVertex3f(-28, 50, 23);
    glVertex3f(-22, 50, 23); 
    glVertex3f(-22, 39, 23);
    glEnd();
    
    //linea encima
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-28, 39, 23);
    glVertex3f(-28, 50, 23);
    glVertex3f(-22, 50, 23);
    glVertex3f(-22, 39, 23);
	glEnd();
    
    //encima2
    glBegin(GL_QUADS);
    glColor3f(0.3, 0.1, 0.0);
    glVertex3f(-27.5, 39.5, 23.01);
    glVertex3f(-27.5, 49.5, 23.01);
    glVertex3f(-22.5, 49.5, 23.01); 
    glVertex3f(-22.5, 39.5, 23.01);
    glEnd();
    
    //linea encima2
    glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-27.5, 39.5, 23.01);
    glVertex3f(-27.5, 49.5, 23.01);
    glVertex3f(-22.5, 49.5, 23.01); 
    glVertex3f(-22.5, 39.5, 23.01);
    glEnd();
    
	
}

void tele2(){
	
	//fondo
	glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-49.5, 34.8, 29.5);
    glVertex3f(-49.5, 34.8, 39);
    glVertex3f(-49.5, 55.5, 39); 
    glVertex3f(-49.5, 55.5, 29.5);
    glEnd();
    
    //lado delantero
	glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-48.5, 34.8, 29.5);
    glVertex3f(-48.5, 34.8, 39);
    glVertex3f(-48.5, 55.5, 39); 
    glVertex3f(-48.5, 55.5, 29.5);
    glEnd();
    
    //lado izquierdo
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-49.5, 34.8, 29.5);
    glVertex3f(-49.5, 34.8, 39);
    glVertex3f(-48.5, 34.8, 39); 
    glVertex3f(-48.5, 34.8, 29.5);
    glEnd();
    
    //lado derecho
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-49.5, 55.5, 29.5);
    glVertex3f(-49.5, 55.5, 39);
    glVertex3f(-48.5, 55.5, 39); 
    glVertex3f(-48.5, 55.5, 29.5);
    glEnd();
    
    //encima
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-49.5, 34.8, 39);
    glVertex3f(-49.5, 55.5, 39);
    glVertex3f(-48.5, 55.5, 39); 
    glVertex3f(-48.5, 34.8, 39);
    glEnd();
    
    //base
	glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-49.5, 34.8, 29.5);
    glVertex3f(-49.5, 55.5, 29.5);
    glVertex3f(-48.5, 55.5, 29.5); 
    glVertex3f(-48.5, 34.8, 29.5);
    glEnd();
    
    //pantalla
    //fondo
	glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-48.49, 35.8, 30.5);
    glVertex3f(-48.49, 35.8, 38);
    glVertex3f(-48.49, 54.5, 38); 
    glVertex3f(-48.49, 54.5, 30.5);
    glEnd();
    
    
    
}

void mueble3(){
	
	//pata 1
	//lado atras
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-11, 40, 20.12);
    glVertex3f(-11, 40, 21.5);
    glVertex3f(-11, 41, 21.5); 
    glVertex3f(-11, 41, 20.12);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-11, 40, 20.12);
    glVertex3f(-11, 40, 21.5);
    glVertex3f(-11, 41, 21.5); 
    glVertex3f(-11, 41, 20.12);
    glEnd();
    
    //lado delante 
	glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-10.5, 40, 20.12);
    glVertex3f(-10.5, 40, 21.5);
    glVertex3f(-10.5, 41, 21.5); 
    glVertex3f(-10.5, 41, 20.12);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-10.5, 40, 20.12);
    glVertex3f(-10.5, 40, 21.5);
    glVertex3f(-10.5, 41, 21.5); 
    glVertex3f(-10.5, 41, 20.12);
    glEnd();
    
    //lado izquierdo
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-11, 40, 20.12);
    glVertex3f(-11, 40, 21.5);
    glVertex3f(-10.5, 40, 21.5); 
    glVertex3f(-10.5, 40, 20.12);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-11, 40, 20.12);
    glVertex3f(-11, 40, 21.5);
    glVertex3f(-10.5, 40, 21.5); 
    glVertex3f(-10.5, 40, 20.12);
    glEnd();
    
    //lado derecho
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-11, 41, 20.12);
    glVertex3f(-11, 41, 21.5);
    glVertex3f(-10.5, 41, 21.5); 
    glVertex3f(-10.5, 41, 20.12);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-11, 41, 20.12);
    glVertex3f(-11, 41, 21.5);
    glVertex3f(-10.5, 41, 21.5); 
    glVertex3f(-10.5, 41, 20.12);
    glEnd();
    
    //pata2
    //lado atras
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-11, 53, 20.12);
    glVertex3f(-11, 53, 21.5);
    glVertex3f(-11, 54, 21.5); 
    glVertex3f(-11, 54, 20.12);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-11, 53, 20.12);
    glVertex3f(-11, 53, 21.5);
    glVertex3f(-11, 54, 21.5); 
    glVertex3f(-11, 54, 20.12);
    glEnd();
    
    //lado delante 
	glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-10.5, 53, 20.12);
    glVertex3f(-10.5, 53, 21.5);
    glVertex3f(-10.5, 54, 21.5); 
    glVertex3f(-10.5, 54, 20.12);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-10.5, 53, 20.12);
    glVertex3f(-10.5, 53, 21.5);
    glVertex3f(-10.5, 54, 21.5); 
    glVertex3f(-10.5, 54, 20.12);
    glEnd();
    
    //lado izquierdo
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-11, 53, 20.12);
    glVertex3f(-11, 53, 21.5);
    glVertex3f(-10.5, 53, 21.5); 
    glVertex3f(-10.5, 53, 20.12);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-11, 53, 20.12);
    glVertex3f(-11, 53, 21.5);
    glVertex3f(-10.5, 53, 21.5); 
    glVertex3f(-10.5, 53, 20.12);
    glEnd();
    
    //lado derecho
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-11, 54, 20.12);
    glVertex3f(-11, 54, 21.5);
    glVertex3f(-10.5, 54, 21.5); 
    glVertex3f(-10.5, 54, 20.12);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-11, 54, 20.12);
    glVertex3f(-11, 54, 21.5);
    glVertex3f(-10.5, 54, 21.5); 
    glVertex3f(-10.5, 54, 20.12);
    glEnd();
    
    //pata3
    //lado atras
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-1, 53, 20.12);
    glVertex3f(-1, 53, 21.5);
    glVertex3f(-1, 54, 21.5); 
    glVertex3f(-1, 54, 20.12);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-1, 53, 20.12);
    glVertex3f(-1, 53, 21.5);
    glVertex3f(-1, 54, 21.5); 
    glVertex3f(-1, 54, 20.12);
    glEnd();
    
    //lado delante 
	glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(0, 53, 20.12);
    glVertex3f(0, 53, 21.5);
    glVertex3f(0, 54, 21.5); 
    glVertex3f(0, 54, 20.12);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
    glVertex3f(0, 53, 20.12);
    glVertex3f(0, 53, 21.5);
    glVertex3f(0, 54, 21.5); 
    glVertex3f(0, 54, 20.12);
    glEnd();
    
    //lado izquierdo
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-1, 53, 20.12);
    glVertex3f(-1, 53, 21.5);
    glVertex3f(0, 53, 21.5); 
    glVertex3f(0, 53, 20.12);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-1, 53, 20.12);
    glVertex3f(-1, 53, 21.5);
    glVertex3f(0, 53, 21.5); 
    glVertex3f(0, 53, 20.12);
    glEnd();
    
    //lado derecho
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-1, 54, 20.12);
    glVertex3f(-1, 54, 21.5);
    glVertex3f(0, 54, 21.5); 
    glVertex3f(0, 54, 20.12);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-1, 54, 20.12);
    glVertex3f(-1, 54, 21.5);
    glVertex3f(0, 54, 21.5); 
    glVertex3f(0, 54, 20.12);
    glEnd();
    
    //pata4
	//lado atras
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-1, 40, 20.12);
    glVertex3f(-1, 40, 21.5);
    glVertex3f(-1, 41, 21.5); 
    glVertex3f(-1, 41, 20.12);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-1, 40, 20.12);
    glVertex3f(-1, 40, 21.5);
    glVertex3f(-1, 41, 21.5); 
    glVertex3f(-1, 41, 20.12);
    glEnd();
    
    //lado delante 
	glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(0, 40, 20.12);
    glVertex3f(0, 40, 21.5);
    glVertex3f(0, 41, 21.5); 
    glVertex3f(0, 41, 20.12);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
    glVertex3f(0, 40, 20.12);
    glVertex3f(0, 40, 21.5);
    glVertex3f(0, 41, 21.5); 
    glVertex3f(0, 41, 20.12);
    glEnd();
    
    //lado izquierdo
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-1, 40, 20.12);
    glVertex3f(-1, 40, 21.5);
    glVertex3f(0, 40, 21.5); 
    glVertex3f(0, 40, 20.12);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-1, 40, 20.12);
    glVertex3f(-1, 40, 21.5);
    glVertex3f(0, 40, 21.5); 
    glVertex3f(0, 40, 20.12);
    glEnd();
    
    //lado derecho
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-1, 41, 20.12);
    glVertex3f(-1, 41, 21.5);
    glVertex3f(0, 41, 21.5); 
    glVertex3f(0, 41, 20.12);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-1, 41, 20.12);
    glVertex3f(-1, 41, 21.5);
    glVertex3f(0, 41, 21.5); 
    glVertex3f(0, 41, 20.12);
    glEnd();
    
    //base
    glBegin(GL_QUADS);
    glColor3f(0.3, 0.2, 0.1);
    glVertex3f(-11, 39, 21.5);
    glVertex3f(-11, 55, 21.5);
    glVertex3f(0, 55, 21.5); 
    glVertex3f(0, 39, 21.5);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-11, 39, 21.5);
    glVertex3f(-11, 55, 21.5);
    glVertex3f(0, 55, 21.5); 
    glVertex3f(0, 39, 21.5);
    glEnd();
    
    //espaldar lado adelante
    glBegin(GL_QUADS);
    glColor3f(0.3, 0.2, 0.1);
    glVertex3f(0, 39, 21.5);
    glVertex3f(0, 39, 28.5);
    glVertex3f(0, 55, 28.5); 
    glVertex3f(0, 55, 21.5);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(0, 39, 21.5);
    glVertex3f(0, 39, 28.5);
    glVertex3f(0, 55, 28.5); 
    glVertex3f(0, 55, 21.5);
    glEnd();
    
    //espaldar atras
    glBegin(GL_QUADS);
    glColor3f(0.3, 0.2, 0.1);
    glVertex3f(-2.5, 39, 21.5);
    glVertex3f(-2.5, 39, 28.5);
    glVertex3f(-2.5, 55, 28.5); 
    glVertex3f(-2.5, 55, 21.5);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-2.5, 39, 21.5);
    glVertex3f(-2.5, 39, 28.5);
    glVertex3f(-2.5, 55, 28.5); 
    glVertex3f(-2.5, 55, 21.5);
    glEnd();
    
    //lado encima
    glBegin(GL_QUADS);
    glColor3f(0.3, 0.2, 0.1);
    glVertex3f(-2.5, 39, 28.5);
    glVertex3f(-2.5, 55, 28.5);
    glVertex3f(0, 55, 28.5); 
    glVertex3f(0, 39, 28.5);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-2.5, 39, 28.5);
    glVertex3f(-2.5, 55, 28.5);
    glVertex3f(0, 55, 28.5); 
    glVertex3f(0, 39, 28.5);
    glEnd();
	
    //lado del asiento
    glBegin(GL_QUADS);
    glColor3f(0.3, 0.2, 0.1);
    glVertex3f(-11, 41, 23.5);
    glVertex3f(-11, 53, 23.5);
    glVertex3f(-2.5, 53, 23.5); 
    glVertex3f(-2.5, 41, 23.5);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-11, 41, 23.52);
    glVertex3f(-11, 53, 23.52);
    glVertex3f(-2.6, 53, 23.52); 
    glVertex3f(-2.6, 41, 23.52);
    glEnd();
    
    //cara izquierda1
    glBegin(GL_QUADS);
    glColor3f(0.3, 0.2, 0.1);
    glVertex3f(-11, 39, 21.5);
    glVertex3f(-11, 39, 25);
    glVertex3f(0, 39, 25); 
    glVertex3f(0, 39, 21.5);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
	glColor3f(0.3, 0.2, 0.1);
    glVertex3f(-11, 39, 21.5);
    glVertex3f(-11, 39, 25);
    glVertex3f(0, 39, 25); 
    glVertex3f(0, 39, 21.5);
    glEnd();
    
    //cara izquierda2
    glBegin(GL_QUADS);
    glColor3f(0.3, 0.2, 0.1);
    glVertex3f(-11, 41, 21.5);
    glVertex3f(-11, 41, 25);
    glVertex3f(0, 41, 25); 
    glVertex3f(0, 41, 21.5);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-11, 41, 21.5);
    glVertex3f(-11, 41, 25);
    glVertex3f(-2.7, 41, 25); 
    glVertex3f(-2.7, 41, 21.5);
    glEnd();
    
    //cara izquierda encima
    glBegin(GL_QUADS);
    glColor3f(0.3, 0.2, 0.1);
    glVertex3f(-11, 39, 25);
    glVertex3f(-11, 41, 25);
    glVertex3f(0, 41, 25); 
    glVertex3f(0, 39, 25);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-11, 39, 25.02);
    glVertex3f(-11, 41, 25.02);
    glVertex3f(-2.6, 41, 25.02); 
    glVertex3f(-2.6, 39, 25.02);
    glEnd();
    
    //cara atras izquierda
    glBegin(GL_QUADS);
    glColor3f(0.3, 0.2, 0.1);
    glVertex3f(-11, 39, 21.5);
    glVertex3f(-11, 39, 25);
    glVertex3f(-11, 41, 25); 
    glVertex3f(-11, 41, 21.5);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-11, 39, 21.5);
    glVertex3f(-11, 39, 25);
    glVertex3f(-11, 41, 25); 
    glVertex3f(-11, 41, 21.5);
    glEnd();
    
    //cara derecha1
    glBegin(GL_QUADS);
    glColor3f(0.3, 0.2, 0.1);
    glVertex3f(-11, 55, 21.5);
    glVertex3f(-11, 55, 25);
    glVertex3f(0, 55, 25); 
    glVertex3f(0, 55, 21.5);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-11, 55, 21.5);
    glVertex3f(-11, 55, 25);
    glVertex3f(0, 55, 25); 
    glVertex3f(0, 55, 21.5);
    glEnd();
	
    //cara derecha2
    glBegin(GL_QUADS);
    glColor3f(0.3, 0.2, 0.1);
    glVertex3f(-11, 53, 21.5);
    glVertex3f(-11, 53, 25);
    glVertex3f(0, 53, 25); 
    glVertex3f(0, 53, 21.5);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-11, 53, 21.5);
    glVertex3f(-11, 53, 25);
    glVertex3f(-2.7, 53, 25); 
    glVertex3f(-2.7, 53, 21.5);
    glEnd();
    
    //cara derecha encima
    glBegin(GL_QUADS);
    glColor3f(0.3, 0.2, 0.1);
    glVertex3f(-11, 53, 25);
    glVertex3f(-11, 55, 25);
    glVertex3f(0, 55, 25); 
    glVertex3f(0, 53, 25);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-11, 53, 25);
    glVertex3f(-11, 55, 25);
    glVertex3f(-2.6, 55, 25); 
    glVertex3f(-2.6, 53, 25);
    glEnd();
    
    //cara atras derecha
    glBegin(GL_QUADS);
    glColor3f(0.3, 0.2, 0.1);
    glVertex3f(-11, 53, 21.5);
    glVertex3f(-11, 53, 25);
    glVertex3f(-11, 55, 25); 
    glVertex3f(-11, 55, 21.5);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-11, 53, 21.5);
    glVertex3f(-11, 53, 25);
    glVertex3f(-11, 55, 25); 
    glVertex3f(-11, 55, 21.5);
    glEnd();
    
    //cara atras asiento
    glBegin(GL_QUADS);
    glColor3f(0.3, 0.2, 0.1);
    glVertex3f(-11, 41, 21.5);
    glVertex3f(-11, 41, 23.5);
    glVertex3f(-11, 53, 23.5); 
    glVertex3f(-11, 53, 21.5);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-11, 41, 21.5);
    glVertex3f(-11, 41, 23.5);
    glVertex3f(-11, 53, 23.5); 
    glVertex3f(-11, 53, 21.5);
    glEnd();
    
}

void espejo2do(){
	
	//espejo
glBegin(GL_QUADS);
glColor3f(0.8, 0.8, 0.8);
glVertex3f(-26, 66.49, 30);
glVertex3f(-26, 66.49, 40);
glVertex3f(-1, 66.49, 40); 
glVertex3f(-1, 66.49, 30);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f(0.0, 0.0, 0.0);
glVertex3f(-26, 66.49, 30);
glVertex3f(-26, 66.49, 40);
glVertex3f(-1, 66.49, 40); 
glVertex3f(-1, 66.49, 30);
glEnd();

//vidrio del espejo
glBegin(GL_QUADS);
glColor3f(0.8, 1.0, 1.0);
glVertex3f(-25, 66.48, 31);
glVertex3f(-25, 66.48, 39);
glVertex3f(-2, 66.48, 39); 
glVertex3f(-2, 66.48, 31);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f(0.0, 0.0, 0.0);
glVertex3f(-25, 66.48, 31);
glVertex3f(-25, 66.48, 39);
glVertex3f(-2, 66.48, 39); 
glVertex3f(-2, 66.48, 31);
glEnd();


//********************* CUADRO *************************
glBegin(GL_QUADS);
glColor3f(0.8, 0.0, 0.0);
glVertex3f(-28, 24.83, 30);
glVertex3f(-28, 24.83, 40);
glVertex3f(-18, 24.83, 40); 
glVertex3f(-18, 24.83, 30);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f(0.0, 0.0, 0.0);
glVertex3f(-28, 24.85, 30);
glVertex3f(-28, 24.85, 40);
glVertex3f(-18, 24.85, 40); 
glVertex3f(-18, 24.85, 30);
glEnd();

//fondo blanco del cuadro
glBegin(GL_QUADS);
glColor3f(1.0, 1.0, 1.0);
glVertex3f(-27, 24.84, 31);
glVertex3f(-27, 24.84, 39);
glVertex3f(-19, 24.84, 39); 
glVertex3f(-19, 24.84, 31);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f(0.0, 0.0, 0.0);
glVertex3f(-27, 24.85, 31);
glVertex3f(-27, 24.85, 39);
glVertex3f(-19, 24.85, 39); 
glVertex3f(-19, 24.85, 31);
glEnd();

glBegin(GL_QUADS);
glColor3f(0.6, 0.1, 1.0);
glVertex3f(-25, 24.85, 33);
glVertex3f(-25, 24.85, 37);
glVertex3f(-21, 24.85, 37); 
glVertex3f(-21, 24.85, 33);
glEnd();

glBegin(GL_LINE_LOOP);
glColor3f(0.0, 0.0, 0.0);
glVertex3f(-25, 24.85, 33);
glVertex3f(-25, 24.85, 37);
glVertex3f(-21, 24.85, 37); 
glVertex3f(-21, 24.85, 33);
glEnd();

	
}

void escritorio3() {
	
///////////////////////////////////////////// MESA ESCRITORIO ////////////////////////////////////////////////////////
/// REPISA 1
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(42, 66, 24);
		glScalef(2.5, 0.03, 0.8);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(42, 64, 28);
		glScalef(2.5, 0.5, 0.02);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();

/// REPISA 2	
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(54, 54, 24);
		glScalef(0.03, 2.5, 0.8);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();	
	
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(52.5, 54, 28);
		glScalef(0.5, 2.5, 0.02);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
//////////////////////////// PATAS DEL ESCRITORIO ////////////////////////////77	
// PATA 1	
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(29.5, 64, 24);
		glScalef(0.02, 0.5, 0.8);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(33.5, 64, 24);
		glScalef(0.02, 0.5, 0.8);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
////// PATA 2	
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(52.5, 45.5, 24);
		glScalef(0.5, 0.02, 0.8);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
    glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(52.5, 41.5, 24);
		glScalef(0.5, 0.02, 0.8);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();	
	
//////////////////////////////// CAJONES ////////////////////////////////////	
/// CAJÓN 1	
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(31.5, 61.5, 21.5);
		glScalef(0.4, 0.02, 0.3);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
/// CAJÓN 2		
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(31.5, 61.5, 24);
		glScalef(0.4, 0.02, 0.3);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
/// CAJÓN 3	
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(31.5, 61.5, 26.5);
		glScalef(0.4, 0.02, 0.3);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
/// CAJÓN 4
    glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(50, 43.5, 21.5);
		glScalef(0.02, 0.4, 0.3);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
/// CAJÓN 5
    glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(50, 43.5, 24);
		glScalef(0.02, 0.4, 0.3);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
/// CAJÓN 6		
    glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(50, 43.5, 26.5);
		glScalef(0.02, 0.4, 0.3);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();	
}

void PC(){
	
//// TECLADO 1	
	glPushMatrix();
		glColor3f(0.59f, 0.6f, 0.6f);
		glTranslatef(42, 63, 28.5);
		glScalef(0.4, 0.2, 0.03);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
//// TECLADO 2	
	glPushMatrix();
		glColor3f(0.59f, 0.6f, 0.6f);
		glTranslatef(51, 54, 28.3);
		glScalef(0.2, 0.4, 0.03);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();	
	
//MONITOR 1
    //// BASE 
    glPushMatrix();
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(42, 66, 28.3);
		glScalef(0.3, 0.07, 0.02);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	//// PALO DE BASE
	glPushMatrix();
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(42, 66, 29);
		glScalef(0.03, 0.03, 0.2);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
//PANTALLA	
	glPushMatrix();
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(41.7, 66, 32.5);
		glScalef(0.7, 0.04, 0.5);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
	glPushMatrix();
		glColor3f(0.8, 0.88, 0.94);
		glTranslatef(41.7, 65.7, 32.5);
		glScalef(0.6, 0.01, 0.4);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();	

/// MONITOR 2
    //// BASE 
    glPushMatrix();
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(54, 54, 28.3);
		glScalef(0.07, 0.3, 0.02);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	//// PALO DE BASE
	glPushMatrix();
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(54, 54, 29);
		glScalef(0.03, 0.03, 0.2);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
//PANTALLA	
	glPushMatrix();
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(54, 54, 32.5);
		glScalef(0.04, 0.7, 0.5);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
	glPushMatrix();
		glColor3f(0.8, 0.88, 0.94);
		glTranslatef(53.7, 54, 32.5);
		glScalef(0.01, 0.6, 0.4);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();		
 
 /// CPU
  	glPushMatrix();
		glColor3f(0.924f, 0.913f, 0.933f);
		glTranslatef(50, 64, 30.7);
		glScalef(0.3, 0.4, 0.5);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
  	
}

void librero(){
	
  	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(12, 64, 28);
		glScalef(1, 0.3, 1.5);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();	
	
//PUERTA 1
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(10, 62.5, 28);
		glScalef(0.5, 0.03, 1.2);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();
// PUERTA 2			
	glPopMatrix();
		glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(14, 62.5, 28);
		glScalef(0.5, 0.02, 1.2);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
///MANIJA 1
    glPushMatrix();
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(13.5, 62.3, 29);
		glScalef(0.03, 0.03, 0.2);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();	

///MANIJA 2
    glPushMatrix();
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(11.5, 62.3, 29);
		glScalef(0.03, 0.03, 0.2);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();		
}

void libros(){
	///LIBRO 1
	glPushMatrix();
		glColor3f(0.929f, 0.196f, 0.462f);
		glTranslatef(36, 65, 29);
		glScalef(0.07, 0.1, 0.2);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
	///LIBRO 2
	glPushMatrix();
		glColor3f(0.266f, 0.196f, 0.929f);
		glTranslatef(35.3, 65, 29);
		glScalef(0.07, 0.1, 0.2);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
	///LIBRO 3
	glPushMatrix();
		glColor3f(0.878f, 0.968f, 0.203f);
		glTranslatef(34.6, 65, 29);
		glScalef(0.07, 0.1, 0.2);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();	
	
	///LIBRO 4
	glPushMatrix();
		glColor3f(0.929f, 0.196f, 0.462f);
		glTranslatef(54, 45, 29);
		glScalef(0.1, 0.07, 0.2);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
	///LIBRO 5
	glPushMatrix();
		glColor3f(0.266f, 0.196f, 0.929f);
		glTranslatef(54, 44.3, 29);
		glScalef(0.1, 0.07, 0.2);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
	///LIBRO 6
	glPushMatrix();
		glColor3f(0.878f, 0.968f, 0.203f);
		glTranslatef(54, 43.6, 29);
		glScalef(0.1, 0.07, 0.2);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();	
}

void mampara2(){
	///lUNA 1
	glPushMatrix();
		glColor3f(0.831f, 0.937f, 1.0f);
		glTranslatef(18, 25, 32);
		glScalef(5, 0.02, 2);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
	///lUNA 2
	glPushMatrix();
		glColor3f(0.831f, 0.937f, 1.0f);
		glTranslatef(18, 24, 32);
		glScalef(5, 0.02, 2);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();	
	
	//MARCO 1
	glPushMatrix();
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(18, 25.5, 22);
		glScalef(5, 0.04, 0.05);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
	//MARCO 2
	glPushMatrix();
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(18, 25.5, 42);
		glScalef(5, 0.04, 0.05);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();	
	
	//MARCO 3
	glPushMatrix();
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(18, 23.5, 22);
		glScalef(5, 0.04, 0.05);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
	//MARCO 3
	glPushMatrix();
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(18, 23.5, 42);
		glScalef(5, 0.04, 0.05);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
	//VARILLA 1
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(-7, 23.5, 32);
		glScalef(0.07, 0.05, 2);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();	
	
	//VARILLA 2
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(5, 23.5, 32);
		glScalef(0.07, 0.05, 2);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
	//VARILLA 3
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(17, 23.5, 32);
		glScalef(0.07, 0.05, 2);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
	//VARILLA 4
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(18, 23.5, 32);
		glScalef(0.07, 0.05, 2);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
	//VARILLA 5
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(30, 23.5, 32);
		glScalef(0.07, 0.05, 2);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
	//VARILLA 6
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(43, 23.5, 32);
		glScalef(0.07, 0.05, 2);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
	//VARILLA 7
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(-7, 25.5, 32);
		glScalef(0.07, 0.05, 2);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();	
	
	//VARILLA 8
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(5, 25.5, 32);
		glScalef(0.07, 0.05, 2);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
	//VARILLA 9
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(17, 25.5, 32);
		glScalef(0.07, 0.05, 2);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
	//VARILLA 10
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(18, 25.5, 32);
		glScalef(0.07, 0.05, 2);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
	//VARILLA 11
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(30, 25.5, 32);
		glScalef(0.07, 0.05, 2);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
	//VARILLA 12
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(43, 25.5, 32);
		glScalef(0.07, 0.05, 2);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
	//MANIJA 1
	glPushMatrix();
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(17, 26, 32);
		glScalef(0.05, 0.05, 0.2);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
	//MANIJA 1
	glPushMatrix();
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(18, 26, 32);
		glScalef(0.05, 0.05, 0.2);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
	
	//MANIJA 3
	glPushMatrix();
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(17, 23, 32);
		glScalef(0.05, 0.05, 0.2);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
	//MANIJA 4
	glPushMatrix();
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(18, 23, 32);
		glScalef(0.05, 0.05, 0.2);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
}	

void cuarto1(){


	glPushMatrix();
	glTranslated(34.1,51,15.7);
	glRotated(90,1,0,0);
	glRotated(180,0,-1,0);
	glScaled(3.8,3,3);
	glPushMatrix();
		Alfombra();
		PisoCuarto();
		paredDerechaFondo();
		paredIzquierdaFondo();
		Puerta();
		Muebles();
	glPopMatrix();
    glPushMatrix();
        glRotatef(-45,0,1,0);
        glTranslatef(posXPericote,0.0,0.0);
        DibujarPericote();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(2.5, 4.0, -5.0);
        SillaGamer();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-1.0, 0.0, 0.03);
        Escritorio();
    glPopMatrix();
    glPushMatrix();
        TV();
    glPopMatrix();
	glPopMatrix();	

}

//////////////////////////////////////////---casa 1 cerrado



void murosPartRightPark1(){
	//1 muro park 
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (37.42f, 67.49f, 0.50f);
	    glVertex3f (37.42f, 62.60f, 0.50f);
	    glVertex3f (37.56f, 62.60f, 0.50f);
	    glVertex3f (37.56f, 67.49f, 0.50f);   
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (37.56f, 62.74f, 0.50f);
		glVertex3f (37.56f, 62.60f, 0.50f);
		glVertex3f (39.71f, 62.60f, 0.50f);
	    glVertex3f (39.71f, 62.74f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (37.42f, 67.49f, 0.50f);
	    glVertex3f (37.42f, 67.49f, 0.40f);
	    glVertex3f (37.42f, 67.46f, 0.38f);
	    glVertex3f (37.42f, 62.60f, 0.38f);
	    glVertex3f (37.42f, 62.60f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (37.42f, 62.60f, 0.50f);
	    glVertex3f (37.42f, 62.60f, 0.38f);
	    glVertex3f (39.71f, 62.60f, 0.38f);
	    glVertex3f (39.71f, 62.60f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (37.56f, 62.74f, 0.50f);
	    glVertex3f (37.56f, 62.74f, 0.26f);
	    glVertex3f (37.56f, 67.49f, 0.26f);
	    glVertex3f (37.56f, 67.49f, 0.50f);
   glEnd();
	glPopMatrix();
	//
		glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (39.71f, 62.74f, 0.50f);
	    glVertex3f (39.71f, 62.74f, 0.26f);
	    glVertex3f (37.56f, 62.74f, 0.26f);
	    glVertex3f (37.56f, 62.74f, 0.50f);
   glEnd();
	glPopMatrix();
	
	//pasto 
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.42f, 0.6f, 0.3f, 1.0f);
	    glVertex3f (37.56f, 67.49f, 0.26f);
	    glVertex3f (37.56f, 62.74f, 0.26f);
	    glVertex3f (39.71f, 62.74f, 0.26f);
	    glVertex3f (39.71f, 67.49f, 0.26f);
   glEnd();
	glPopMatrix();
	
	//EXTRA DELINEATION
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	glColor4f (0.0f, 0.0f, 0.0f, 0.0f);
	    glVertex3f (37.42f, 67.49f, 0.50f);
	    glVertex3f (37.42f, 62.60f, 0.50f);
	    glVertex3f (39.71f, 62.60f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	glColor4f (0.0f, 0.0f, 0.0f, 0.0f);
	    glVertex3f (39.71f, 62.74f, 0.50f);
	    glVertex3f (37.56f, 62.74f, 0.50f);
	    glVertex3f (37.56f, 67.49f, 0.50f);
   glEnd();
	glPopMatrix();	
}

void murosPartRightPark2(){
		//2 muro park 
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (41.85f, 55.62f, 0.50f);
	    glVertex3f (41.40f, 57.36f, 0.50f);
	    glVertex3f (41.64f, 57.45f, 0.50f);
	    glVertex3f (42.04f, 55.90f, 0.50f);
	    glVertex3f (42.04f, 55.64f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (40.51f, 58.92f, 0.50f);
	    glVertex3f (41.40f, 57.36f, 0.50f);
	    glVertex3f (41.64f, 57.45f, 0.50f);
	    glVertex3f (40.89f, 58.77f, 0.50f);
	    glVertex3f (40.76f, 59.0f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (40.76f, 59.0f, 0.50f);
	    glVertex3f (44.14f, 60.04f, 0.50f);
	    glVertex3f (44.24f, 59.81f, 0.50f);
	    glVertex3f (40.89f, 58.77f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (42.04f, 55.90f, 0.50f);
	    glVertex3f (45.35f, 56.33f, 0.50f);
	    glVertex3f (45.38f, 56.08f, 0.50f);
	    glVertex3f (42.04f, 55.64f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (44.24f, 59.81f, 0.50f);
	    glVertex3f (45.20f, 57.50f, 0.50f);
	    glVertex3f (44.95f, 57.43f, 0.50f);
	    glVertex3f (44.0f, 59.73f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (45.20f, 57.50f, 0.50f);
	    glVertex3f (44.95f, 57.43f, 0.50f);
	    glVertex3f (45.10f, 56.30f, 0.50f);
	    glVertex3f (45.35f, 56.33f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (40.51f, 58.92f, 0.50f);
	    glVertex3f (40.51f, 58.92f, 0.38f);
	    glVertex3f (41.40f, 57.36f, 0.38f);
	    glVertex3f (41.40f, 57.36f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (41.40f, 57.36f, 0.38f);
	    glVertex3f (41.85f, 55.62f, 0.38f);
	    glVertex3f (41.85f, 55.62f, 0.50f);
	    glVertex3f (41.40f, 57.36f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (41.85f, 55.62f, 0.50f);
	    glVertex3f (41.85f, 55.62f, 0.38f);
	    glVertex3f (45.38f, 56.08f, 0.38f);
	    glVertex3f (45.38f, 56.08f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (45.38f, 56.08f, 0.50f);
	    glVertex3f (45.38f, 56.08f, 0.38f);
	    glVertex3f (45.20f, 57.50f, 0.38f);
	    glVertex3f (45.20f, 57.50f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (45.20f, 57.50f, 0.50f);
	    glVertex3f (45.20f, 57.50f, 0.38f);
	    glVertex3f (44.14f, 60.04f, 0.38f);
	    glVertex3f (44.14f, 60.04f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (44.14f, 60.04f, 0.50f);
	    glVertex3f (44.14f, 60.04f, 0.38f);
	    glVertex3f (40.51f, 58.92f, 0.38f);  
	    glVertex3f (40.51f, 58.92f, 0.50f);  
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (40.89f, 58.77f, 0.50f);
	    glVertex3f (40.89f, 58.77f, 0.26f);
	    glVertex3f (44.0f, 59.73f, 0.26f);  
	    glVertex3f (44.0f, 59.73f, 0.50f);  
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (44.0f, 59.73f, 0.50f);
	    glVertex3f (44.95f, 57.43f, 0.50f);
	    glVertex3f (44.95f, 57.43f, 0.26f);  
	    glVertex3f (44.0f, 59.73f, 0.26f);  
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (44.95f, 57.43f, 0.50f);
	     glVertex3f (45.10f, 56.30f, 0.50f);
	     glVertex3f (45.10f, 56.30f, 0.26f);
	     glVertex3f (44.95f, 57.43f, 0.26f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (45.10f, 56.30f, 0.50f);
	     glVertex3f (42.04f, 55.90f, 0.50f);
	     glVertex3f (42.04f, 55.90f, 0.26f);
	     glVertex3f (45.10f, 56.30f, 0.26f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (42.04f, 55.90f, 0.50f);
	     glVertex3f (41.64f, 57.45f, 0.50f);
	     glVertex3f (41.64f, 57.45f, 0.26f);
	     glVertex3f (42.04f, 55.90f, 0.26f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (41.64f, 57.45f, 0.50f);
	    glVertex3f (41.64f, 57.45f, 0.26f);
	    glVertex3f (40.89f, 58.77f, 0.26f);
	    glVertex3f (40.89f, 58.77f, 0.50f);
   glEnd();
	glPopMatrix();
	
		//pasto 
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.42f, 0.6f, 0.3f, 1.0f);
	    glVertex3f (42.04f, 55.90f, 0.26f);
	    glVertex3f (41.64f, 57.45f, 0.26f);
	    glVertex3f (44.95f, 57.43f, 0.26f);
	    glVertex3f (45.10f, 56.30f, 0.26f);
	  glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.42f, 0.6f, 0.3f, 1.0f);
	    glVertex3f (41.64f, 57.45f, 0.26f);
	    glVertex3f (40.89f, 58.77f, 0.26f);
	    glVertex3f (44.0f, 59.73f, 0.26f);
	    glVertex3f (44.95f, 57.43f, 0.26f);
	  glEnd();
	glPopMatrix();
	
	//EXTRA DELINEATION
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glColor4f (0.0f, 0.0f, 0.0f, 0.0f);
	    glVertex3f (40.51f, 58.92f, 0.50f);
	    glVertex3f (41.40f, 57.36f, 0.50f);
	    glVertex3f (41.85f, 55.62f, 0.50f);
	    glVertex3f (45.38f, 56.08f, 0.50f);
	    glVertex3f (45.20f, 57.50f, 0.50f);
	    glVertex3f (44.14f, 60.04f, 0.50f);  
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glColor4f (0.0f, 0.0f, 0.0f, 0.0f);
	    glVertex3f (40.89f, 58.77f, 0.50f);
	    glVertex3f (44.0f, 59.73f, 0.50f); 
	    glVertex3f (44.0f, 59.73f, 0.50f);
	    glVertex3f (44.95f, 57.43f, 0.50f);
	     glVertex3f (45.10f, 56.30f, 0.50f);
	     glVertex3f (42.04f, 55.90f, 0.50f);
	    glVertex3f (41.64f, 57.45f, 0.50f);
	    glVertex3f (40.89f, 58.77f, 0.50f);
   glEnd();
	glPopMatrix();
	
	
	
	
	
	
}

void murosPartRightPark3(){
	//2 wall park - right
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (48.61f, 60.04f, 0.50f);
	    glVertex3f (48.71f, 59.79f, 0.50f);
	    glVertex3f (56.22f, 59.79f, 0.50f);
	    glVertex3f (56.22f, 60.04f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (48.61f, 60.04f, 0.50f);
	    glVertex3f (48.33f, 60.04f, 0.50f);
	    glVertex3f (49.39f, 57.50f, 0.50f);
	    glVertex3f (49.63f, 57.77f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (49.39f, 57.50f, 0.50f);
	    glVertex3f (49.63f, 57.77f, 0.50f);
	    glVertex3f (49.99f, 54.73f, 0.50f);
	    glVertex3f (49.75f, 54.77f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (49.75f, 54.77f, 0.50f);
	    glVertex3f (49.71f, 54.47f, 0.50f);
	    glVertex3f (49.99f, 54.47f, 0.50f);
	    glVertex3f (49.99f, 54.73f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (49.99f, 54.73f, 0.50f);
	    glVertex3f (49.99f, 54.47f, 0.50f);
	    glVertex3f (56.22f, 54.47f, 0.50f);
	    glVertex3f (56.22f, 54.73f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (56.22f, 54.47f, 0.50f);
	    glVertex3f (56.47f, 54.47f, 0.50f);
	    glVertex3f (56.47f, 60.04f, 0.50f);
	    glVertex3f (56.22f, 60.04f, 0.50f);
   glEnd();
	glPopMatrix();
	//wall sideways
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (48.33f, 60.04f, 0.50f);
	    glVertex3f (48.33f, 60.04f, 0.38f);
	    glVertex3f (49.39f, 57.50f, 0.38f);
	    glVertex3f (49.39f, 57.50f, 0.50f);
   glEnd();
	glPopMatrix();
	//
glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (49.39f, 57.50f, 0.50f);
	    glVertex3f (49.39f, 57.50f, 0.38f);
	    glVertex3f (49.75f, 54.77f, 0.38f);
	    glVertex3f (49.75f, 54.77f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (49.75f, 54.77f, 0.50f);
	    glVertex3f (49.75f, 54.77f, 0.38f);
	    glVertex3f (49.71f, 54.47f, 0.38f);
	    glVertex3f (49.71f, 54.47f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (49.71f, 54.47f, 0.50f);
	    glVertex3f (49.71f, 54.47f, 0.38f);
	    glVertex3f (56.47f, 54.47f, 0.38f);
	    glVertex3f (56.47f, 54.47f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (56.47f, 54.47f, 0.50f);
	    glVertex3f (56.47f, 54.47f, 0.38f);
	    glVertex3f (56.47f, 60.04f, 0.38f);
	    glVertex3f (56.47f, 60.04f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (56.47f, 60.04f, 0.50f);
	    glVertex3f (56.47f, 60.04f, 0.38f);
	    glVertex3f (48.33f, 60.04f, 0.38f);
	    glVertex3f (48.33f, 60.04f, 0.50f);
   glEnd();
	glPopMatrix();
	
	//wall INSIDE
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (48.71f, 59.79f, 0.50f);
	    glVertex3f (48.71f, 59.79f, 0.26f);
	    glVertex3f (56.22f, 59.79f, 0.26f);
	    glVertex3f (56.22f, 59.79f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (56.22f, 59.79f, 0.50f);
	    glVertex3f (56.22f, 59.79f, 0.26f);
	    glVertex3f (56.22f, 54.73f, 0.26f);
	    glVertex3f (56.22f, 54.73f, 0.50f);
   glEnd();
	glPopMatrix();
	//
    glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (56.22f, 54.73f, 0.50f);
	    glVertex3f (56.22f, 54.73f, 0.26f);
	    glVertex3f (49.99f, 54.73f, 0.26f);
	    glVertex3f (49.99f, 54.73f, 0.50f);
   glEnd();
	glPopMatrix();
	//
  glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (49.99f, 54.73f, 0.50f);
	    glVertex3f (49.99f, 54.73f, 0.26f);
	    glVertex3f (49.63f, 57.57f, 0.26f);
	    glVertex3f (49.63f, 57.57f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (49.63f, 57.57f, 0.50f);
	    glVertex3f (49.63f, 57.57f, 0.26f);
	    glVertex3f (48.71f, 59.79f, 0.26f);
	    glVertex3f (48.71f, 59.79f, 0.50f);
   glEnd();
	glPopMatrix();
	
	//GRASS 
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.42f, 0.6f, 0.3f, 1.0f);
	    glVertex3f (49.63f, 57.57f, 0.26f);
	    glVertex3f (49.99f, 54.73f, 0.26f);
	    glVertex3f (56.22f, 54.73f, 0.26f);
	    glVertex3f (56.22f, 59.79f, 0.26f);
	    glVertex3f (52.30f, 59.79f, 0.26f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glColor4f (0.42f, 0.6f, 0.3f, 1.0f);
	    glVertex3f (48.71f, 59.79f, 0.26f);
	    glVertex3f (49.63f, 57.57f, 0.26f);
	    glVertex3f (52.30f, 59.79f, 0.26f);
   glEnd();
	glPopMatrix();
	
	//DELINEATION WALL INTERIOR
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glColor4f (0.0f, 0.0f, 0.0f, 0.0f);
	    glVertex3f (56.22f, 54.73f, 0.50f);
	    glVertex3f (56.22f, 59.79f, 0.50f);
	    glVertex3f (48.71f, 59.79f, 0.50f);
		glVertex3f (49.63f, 57.57f, 0.50f);
		glVertex3f (50.0f, 54.77f, 0.50f); 
		glVertex3f (49.99f, 54.73f, 0.50f); 
   glEnd();
	glPopMatrix();
	//DELINEATION WALL EXTERIOR
		glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glColor4f (0.0f, 0.0f, 0.0f, 0.0f);
	    glVertex3f (48.33f, 60.04f, 0.50f);
		glVertex3f (49.39f, 57.50f, 0.50f);
		glVertex3f (49.75f, 54.77f, 0.50f);
		glVertex3f (49.71f, 54.47f, 0.50f);
		glVertex3f (56.47f, 54.47f, 0.50f);
		glVertex3f (56.47f, 60.04f, 0.50f);
   glEnd();
	glPopMatrix();
}

void murosPartRightPark4(){
		//3 wall park 
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (40.65f, 50.38f, 0.50f);
	    glVertex3f (40.45f, 50.53f, 0.50f);
	    glVertex3f (39.16f, 49.27f, 0.50f);
	    glVertex3f (39.32f, 49.07f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (41.59f, 51.99f, 0.50f);
	    glVertex3f (41.36f, 52.08f, 0.50f);
	    glVertex3f (40.45f, 50.53f, 0.50f);
	    glVertex3f (40.65f, 50.38f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (41.59f, 51.99f, 0.50f);
	    glVertex3f (41.46f, 51.77f, 0.50f);
	    glVertex3f (44.55f, 50.49f, 0.50f);
		glVertex3f (44.65f, 50.72f, 0.50f);  
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (43.92f, 49.63f, 0.50f);
	    glVertex3f (44.14f, 49.50f, 0.50f);
	    glVertex3f (44.55f, 50.49f, 0.50f);
		glVertex3f (44.32f, 50.59f, 0.50f);  
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (42.29f, 47.50f, 0.50f);
	    glVertex3f (42.47f, 47.32f, 0.50f);
	    glVertex3f (44.14f, 49.50f, 0.50f);
		glVertex3f (43.92f, 49.63f, 0.50f);  
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (41.38f, 46.80f, 0.50f);
	    glVertex3f (41.53f, 46.60f, 0.50f);
	    glVertex3f (42.47f, 47.32f, 0.50f);
		glVertex3f (42.29f, 47.50f, 0.50f);  
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (39.32f, 49.07f, 0.50f);
	    glVertex3f (39.50f, 49.25f, 0.50f);
	    glVertex3f (41.53f, 46.60f, 0.50f);
		glVertex3f (41.33f, 46.45f, 0.50f);  
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (39.16f, 49.27f, 0.50f);
	    glVertex3f (39.16f, 49.27f, 0.38f);
	    glVertex3f (41.33f, 46.45f, 0.38f);
		glVertex3f (41.33f, 46.45f, 0.50f);  
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (41.33f, 46.45f, 0.50f);
	    glVertex3f (41.33f, 46.45f, 0.38f);
	    glVertex3f (42.47f, 47.32f, 0.38f);
		glVertex3f (42.47f, 47.32f, 0.50f);  
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (42.47f, 47.32f, 0.50f);
	    glVertex3f (42.47f, 47.32f, 0.38f);
	    glVertex3f (44.14f, 49.50f, 0.38f);
		glVertex3f (44.14f, 49.50f, 0.50f); 
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (44.14f, 49.50f, 0.50f);
	    glVertex3f (44.14f, 49.50f, 0.38f);
	    glVertex3f (44.65f, 50.72f, 0.38f);
		glVertex3f (44.65f, 50.72f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (44.65f, 50.72f, 0.50f);
	    glVertex3f (44.65f, 50.72f, 0.38f);
	    glVertex3f (41.36f, 52.08f, 0.38f);
		glVertex3f (41.36f, 52.08f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (41.36f, 52.08f, 0.50f);
	    glVertex3f (41.36f, 52.08f, 0.38f);
	    glVertex3f (40.45f, 50.53f, 0.38f);
		glVertex3f (40.45f, 50.53f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (40.45f, 50.53f, 0.50f);
	    glVertex3f (40.45f, 50.53f, 0.38f);
	    glVertex3f (39.16f, 49.27f, 0.38f);
		glVertex3f (39.16f, 49.27f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (41.38f, 46.80f, 0.50f);
	    glVertex3f (41.38f, 46.80f, 0.26f);
	    glVertex3f (39.50f, 49.25f, 0.26f);
		glVertex3f (39.50f, 49.25f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (39.50f, 49.25f, 0.50f);
	    glVertex3f (39.50f, 49.25f, 0.26f);
	    glVertex3f (40.65f, 50.38f, 0.26f);
		glVertex3f (41.46f, 51.77f, 0.26f);
		glVertex3f (41.46f, 51.77f, 0.50f);
		glVertex3f (40.65f, 50.38f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (41.46f, 51.77f, 0.50f);
	    glVertex3f (41.46f, 51.77f, 0.26f);
	    glVertex3f (44.32f, 50.59f, 0.26f);
		glVertex3f (44.32f, 50.59f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (44.32f, 50.59f, 0.50f);
	    glVertex3f (44.32f, 50.59f, 0.26f);
	    glVertex3f (43.92f, 49.63f, 0.26f);
		glVertex3f (43.92f, 49.63f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (43.92f, 49.63f, 0.50f);
	    glVertex3f (43.92f, 49.63f, 0.26f);
	    glVertex3f (42.29f, 47.50f, 0.26f);
	    glVertex3f (42.29f, 47.50f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (42.29f, 47.50f, 0.50f);
	    glVertex3f (42.29f, 47.50f, 0.26f);
	    glVertex3f (41.38f, 46.80f, 0.26f);
	    glVertex3f (41.38f, 46.80f, 0.50f);
   glEnd();
	glPopMatrix();
	
	//DELINEATION WALL
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glColor4f (0.0f, 0.0f, 0.0f, 0.0f);
	    glVertex3f (41.33f, 46.45f, 0.50f);
	    glVertex3f (42.47f, 47.32f, 0.50f);
	    glVertex3f (44.14f, 49.50f, 0.50f);
	    glVertex3f (44.65f, 50.72f, 0.50f);  
	    glVertex3f (41.36f, 52.08f, 0.50f);
	    glVertex3f (40.45f, 50.53f, 0.50f);
	    glVertex3f (39.16f, 49.27f, 0.50f);    
   glEnd();
	glPopMatrix();
	//INTERIOR WALL
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glColor4f (0.0f, 0.0f, 0.0f, 0.0f);
	     glVertex3f (41.38f, 46.80f, 0.50f);
		 glVertex3f (39.50f, 49.25f, 0.50f);  
		 glVertex3f (39.50f, 49.25f, 0.50f);
		 glVertex3f (40.65f, 50.38f, 0.50f);
		 glVertex3f (41.46f, 51.77f, 0.50f); 
		 glVertex3f (44.32f, 50.59f, 0.50f);
		 glVertex3f (43.92f, 49.63f, 0.50f);
		 glVertex3f (42.29f, 47.50f, 0.50f);
   glEnd();
	glPopMatrix();
	
	//GRASS
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.42f, 0.6f, 0.3f, 1.0f);
	    glVertex3f (41.46f, 51.77f, 0.26f);
	    glVertex3f (40.65f, 50.38f, 0.26f);
	    glVertex3f (43.92f, 49.63f, 0.26f);
		glVertex3f (44.32f, 50.59f, 0.26f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glColor4f (0.42f, 0.6f, 0.3f, 1.0f);
	    glVertex3f (42.29f, 47.50f, 0.26f);
	    glVertex3f (43.92f, 49.63f, 0.26f);
	    glVertex3f (40.65f, 50.38f, 0.26f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.42f, 0.6f, 0.3f, 1.0f);
	    glVertex3f (41.38f, 46.80f, 0.26f);
	    glVertex3f (42.29f, 47.50f, 0.26f);
	    glVertex3f (40.65f, 50.38f, 0.26f);
		glVertex3f (39.50f, 49.25f, 0.26f);
   glEnd();
	glPopMatrix();
}

void murosPartRightPark5(){
	//3 wall park - right
	//wall elevated
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (45.52f, 46.45f, 0.50f);
	    glVertex3f (46.27f, 47.02f, 0.50f);
	    glVertex3f (46.27f, 46.45f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (46.27f, 46.70f, 0.50f);
	    glVertex3f (46.27f, 46.45f, 0.50f);
	    glVertex3f (56.47f, 46.45f, 0.50f);
	    glVertex3f (56.47f, 46.70f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (56.22f, 46.70f, 0.50f);
	    glVertex3f (56.47f, 46.70f, 0.50f);
	    glVertex3f (56.47f, 50.89f, 0.50f);
	    glVertex3f (56.22f, 50.89f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (56.22f, 50.63f, 0.50f);
	    glVertex3f (56.22f, 50.89f, 0.50f);
	    glVertex3f (49.08f, 50.89f, 0.50f);
	    glVertex3f (49.08f, 50.63f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (49.08f, 50.63f, 0.50f);
	    glVertex3f (49.08f, 50.89f, 0.50f);
	    glVertex3f (48.91f, 50.89f, 0.50f);
	    glVertex3f (48.33f, 49.50f, 0.50f);
	    glVertex3f (48.55f, 49.37f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (48.55f, 49.37f, 0.50f);
	    glVertex3f (48.33f, 49.50f, 0.50f);
	    glVertex3f (46.66f, 47.32f, 0.50f);
	    glVertex3f (46.84f, 47.14f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (46.84f, 47.14f, 0.50f);
	    glVertex3f (46.66f, 47.32f, 0.50f);
	    glVertex3f (46.27f, 47.02f, 0.50f);
	    glVertex3f (46.27f, 46.70f, 0.50f);
   glEnd();
	glPopMatrix();
	// wall of side 
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (45.52f, 46.45f, 0.50f);
	    glVertex3f (45.52f, 46.45f, 0.38f);
	    glVertex3f (56.47f, 46.45f, 0.38f);
	    glVertex3f (56.47f, 46.45f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (56.47f, 46.45f, 0.50f);
	    glVertex3f (56.47f, 46.45f, 0.38f);
	    glVertex3f (56.47f, 50.89f, 0.38f);
	    glVertex3f (56.47f, 50.89f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (56.47f, 50.89f, 0.50f);
	    glVertex3f (56.47f, 50.89f, 0.38f);
	    glVertex3f (48.91f, 50.89f, 0.38f);
	    glVertex3f (48.91f, 50.89f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (48.91f, 50.89f, 0.50f);
	    glVertex3f (48.91f, 50.89f, 0.38f);
	    glVertex3f (48.33f, 49.50f, 0.38f);
	    glVertex3f (48.33f, 49.50f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (48.33f, 49.50f, 0.50f);
	    glVertex3f (48.33f, 49.50f, 0.38f);
	    glVertex3f (46.66f, 47.32f, 0.38f);
	    glVertex3f (46.66f, 47.32f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (46.66f, 47.32f, 0.50f);
	    glVertex3f (46.66f, 47.32f, 0.38f);
	    glVertex3f (45.52f, 46.45f, 0.38f);
	    glVertex3f (45.52f, 46.45f, 0.50f);
   glEnd();
	glPopMatrix();
	//wall of side - inside
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (56.22f, 50.63f, 0.50f);
	    glVertex3f (56.22f, 50.63f, 0.26f);
	    glVertex3f (56.22f, 46.70f, 0.26f);
	    glVertex3f (56.22f, 46.70f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (56.22f, 46.70f, 0.50f);
	    glVertex3f (56.22f, 46.70f, 0.26f);
	    glVertex3f (46.27f, 46.70f, 0.26f);
	    glVertex3f (46.27f, 46.70f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (46.27f, 46.70f, 0.50f);
	    glVertex3f (46.27f, 46.70f, 0.26f);
	    glVertex3f (46.84f, 47.14f, 0.26f);
	    glVertex3f (46.84f, 47.14f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (46.84f, 47.14f, 0.50f);
	    glVertex3f (46.84f, 47.14f, 0.26f);
	    glVertex3f (48.55f, 49.37f, 0.26f);
	    glVertex3f (48.55f, 49.37f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (48.55f, 49.37f, 0.50f);
	    glVertex3f (48.55f, 49.37f, 0.26f);
	    glVertex3f (49.08f, 50.63f, 0.26f);
	    glVertex3f (49.08f, 50.63f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (49.08f, 50.63f, 0.50f);
	    glVertex3f (49.08f, 50.63f, 0.26f);
	    glVertex3f (56.22f, 50.63f, 0.26f);
	    glVertex3f (56.22f, 50.63f, 0.50f);
   glEnd();
	glPopMatrix();
	
	//GRASS
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.42f, 0.6f, 0.3f, 1.0f);
	    glVertex3f (56.22f, 46.70f, 0.26f);
	    glVertex3f (56.22f, 50.63f, 0.26f);
	    glVertex3f (49.08f, 50.63f, 0.26f);
	    glVertex3f (48.55f, 49.37f, 0.26f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.42f, 0.6f, 0.3f, 1.0f);
	    glVertex3f (48.55f, 49.37f, 0.26f);
	    glVertex3f (56.22f, 46.70f, 0.26f);
	    glVertex3f (47.05f, 46.70f, 0.26f);
	    glVertex3f (46.84f, 47.14f, 0.26f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glColor4f (0.42f, 0.6f, 0.3f, 1.0f);
	    glVertex3f (46.84f, 47.14f, 0.26f);
	    glVertex3f (47.05f, 46.70f, 0.26f);
	    glVertex3f (46.27f, 46.70f, 0.26f);
   glEnd();
	glPopMatrix();
	
	//delineation outer
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glColor4f (0.0f, 0.0f, 0.0f, 0.0f);
	    glVertex3f (56.47f, 50.89f, 0.50f);
		glVertex3f (48.91f, 50.89f, 0.50f);
		glVertex3f (48.33f, 49.50f, 0.50f);  
		glVertex3f (46.66f, 47.32f, 0.50f);
		glVertex3f (45.52f, 46.45f, 0.50f); 
		glVertex3f (56.47f, 46.45f, 0.50f);   
   glEnd();
	glPopMatrix();
	//delineation inside 
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glColor4f (0.0f, 0.0f, 0.0f, 0.0f);
	    glVertex3f (56.22f, 50.63f, 0.50f);
		glVertex3f (49.08f, 50.63f, 0.50f); 
		glVertex3f (48.55f, 49.37f, 0.50f);
		glVertex3f (46.84f, 47.14f, 0.50f);
		glVertex3f (46.27f, 46.70f, 0.50f);
		glVertex3f (56.22f, 46.70f, 0.50f);     
   glEnd();
	glPopMatrix();
}

void muroCentralParque(){
	//part elevada
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (33.57f, 52.28f, 0.50f);
	    glVertex3f (33.68f, 52.45f, 0.50f);
	    glVertex3f (33.12f, 52.88f, 0.50f);
	    glVertex3f (32.70f, 53.43f, 0.50f);
	    glVertex3f (32.52f, 53.33f, 0.50f);
		glVertex3f (32.98f, 52.74f, 0.50f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
		glVertex3f (32.52f, 53.33f, 0.50f);
		glVertex3f (32.70f, 53.43f, 0.50f);
		glVertex3f (32.43f, 54.08f, 0.50f);
		glVertex3f (32.23f, 54.03f, 0.50f);
		glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
		glVertex3f (32.23f, 54.03f, 0.50f);
		glVertex3f (32.43f, 54.08f, 0.50f);
		glVertex3f (32.34f, 54.77f, 0.50f);
		glVertex3f (32.43f, 55.46f, 0.50f);
		glVertex3f (32.23f, 55.52f, 0.50f);
		glVertex3f (32.13f, 54.77f, 0.50f);
		glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
		glVertex3f (32.23f, 55.52f, 0.50f);
		glVertex3f (32.43f, 55.46f, 0.50f);
		glVertex3f (32.70f, 56.11f, 0.50f);
		glVertex3f (33.12f, 56.66f, 0.50f);
		glVertex3f (32.98f, 56.81f, 0.50f);
		glVertex3f (32.52f, 56.21f, 0.50f);
		glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
		glVertex3f (32.98f, 56.81f, 0.50f);
		glVertex3f (33.12f, 56.66f, 0.50f);
		glVertex3f (33.68f, 57.09f, 0.50f);
		glVertex3f (34.32f, 57.36f, 0.50f);
		glVertex3f (34.27f, 57.55f, 0.50f);
		glVertex3f (33.57f, 57.27f, 0.50f);
		glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
		glVertex3f (34.27f, 57.55f, 0.50f);
		glVertex3f (34.32f, 57.36f, 0.50f);
		glVertex3f (35.01f, 57.45f, 0.50f);
		glVertex3f (35.71f, 57.36f, 0.50f);
		glVertex3f (35.76f, 57.55f, 0.50f);
		glVertex3f (35.01f, 57.65f, 0.50f);
		glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (35.76f, 57.55f, 0.50f);
		glVertex3f (35.71f, 57.36f, 0.50f);
		glVertex3f (36.35f, 57.09f, 0.50f);
		glVertex3f (36.91f, 56.66f, 0.50f);
		glVertex3f (37.05f, 56.81f, 0.50f);
		glVertex3f (36.45f, 57.27f, 0.50f);
		glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (37.05f, 56.81f, 0.50f);
	    glVertex3f (36.91f, 56.66f, 0.50f);
	    glVertex3f (37.33f, 56.11f, 0.50f);
	    glVertex3f (37.60f, 55.46f, 0.50f);
	    glVertex3f (37.80f, 55.52f, 0.50f);
	    glVertex3f (37.51f, 56.21f, 0.50f);
		glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (37.80f, 55.52f, 0.50f);
	    glVertex3f (37.60f, 55.46f, 0.50f);
	    glVertex3f (37.69f, 54.77f, 0.50f);
	    glVertex3f (37.60f, 54.08f, 0.50f);
	    glVertex3f (37.80f, 54.03f, 0.50f);
	    glVertex3f (37.89f, 54.77f, 0.50f);
		glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (37.80f, 54.03f, 0.50f);
	    glVertex3f (37.60f, 54.08f, 0.50f);
	    glVertex3f (37.33f, 53.43f, 0.50f);
	    glVertex3f (36.91f, 52.88f, 0.50f);
	    glVertex3f (37.05f, 52.74f, 0.50f);
	    glVertex3f (37.51f, 53.33f, 0.50f);
		glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (37.05f, 52.74f, 0.50f);
	    glVertex3f (36.91f, 52.88f, 0.50f);
	    glVertex3f (36.35f, 52.45f, 0.50f);
	    glVertex3f (35.71f, 52.19f, 0.50f);
	    glVertex3f (35.76f, 51.99f, 0.50f);
	    glVertex3f (36.45f, 52.28f, 0.50f);
		glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (35.76f, 51.99f, 0.50f);
	    glVertex3f (35.71f, 52.19f, 0.50f);
	    glVertex3f (35.01f, 52.09f, 0.50f);
	    glVertex3f (34.32f, 52.19f, 0.50f);
	    glVertex3f (34.27f, 51.99f, 0.50f);
	    glVertex3f (35.01f, 51.89f, 0.50f);
		glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (34.27f, 51.99f, 0.50f);
	     glVertex3f (34.32f, 52.19f, 0.50f);
	      glVertex3f (33.68f, 52.45f, 0.50f);
	     glVertex3f (33.57f, 52.28f, 0.50f);
	   	glEnd();
	glPopMatrix();
	//lados muros
		glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (32.52f, 53.33f, 0.50f);
	    glVertex3f (32.52f, 53.33f, 0.38f);
	    glVertex3f (32.98f, 52.74f, 0.38f);
	    glVertex3f (33.57f, 52.28f, 0.38f);
	    glVertex3f (33.57f, 52.28f, 0.50f);
	    glVertex3f (32.98f, 52.74f, 0.50f);
	   	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (33.57f, 52.28f, 0.50f);
	    glVertex3f (33.57f, 52.28f, 0.38f);
	    glVertex3f (34.27f, 51.99f, 0.38f);
	    glVertex3f (35.01f, 51.89f, 0.38f);
	    glVertex3f (35.01f, 51.89f, 0.50f);
	    glVertex3f (34.27f, 51.99f, 0.50f);
	   	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (35.01f, 51.89f, 0.50f);
	    glVertex3f (35.01f, 51.89f, 0.38f);
	    glVertex3f (35.76f, 51.99f, 0.38f);
	    glVertex3f (36.45f, 52.28f, 0.38f);
	    glVertex3f (36.45f, 52.28f, 0.50f);
	    glVertex3f (35.76f, 51.99f, 0.50f);
	   	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (36.45f, 52.28f, 0.50f);
	    glVertex3f (36.45f, 52.28f, 0.38f);
	    glVertex3f (37.05f, 52.74f, 0.38f);
	    glVertex3f (37.51f, 53.33f, 0.38f);
	    glVertex3f (37.51f, 53.33f, 0.50f);
	    glVertex3f (37.05f, 52.74f, 0.50f);
	   	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (37.51f, 53.33f, 0.50f);
	    glVertex3f (37.51f, 53.33f, 0.38f);
	    glVertex3f (37.80f, 54.03f, 0.38f);
	    glVertex3f (37.89f, 54.77f, 0.38f);
	    glVertex3f (37.89f, 54.77f, 0.50f);
	    glVertex3f (37.80f, 54.03f, 0.50f);
	   	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (37.89f, 54.77f, 0.50f);
	    glVertex3f (37.89f, 54.77f, 0.38f);
	    glVertex3f (37.80f, 55.52f, 0.38f);
	    glVertex3f (37.51f, 56.21f, 0.38f);
	    glVertex3f (37.51f, 56.21f, 0.50f);
	    glVertex3f (37.80f, 55.52f, 0.50f);
	   	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (37.51f, 56.21f, 0.50f);
	    glVertex3f (37.51f, 56.21f, 0.38f);
	    glVertex3f (37.05f, 56.81f, 0.38f);
	    glVertex3f (36.45f, 57.27f, 0.38f);
	    glVertex3f (36.45f, 57.27f, 0.50f);
	    glVertex3f (37.05f, 56.81f, 0.50f);
	   	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (36.45f, 57.27f, 0.50f);
	    glVertex3f (36.45f, 57.27f, 0.38f);
	    glVertex3f (35.76f, 57.55f, 0.38f);
	    glVertex3f (35.01f, 57.65f, 0.38f);
	    glVertex3f (35.01f, 57.65f, 0.50f);
	    glVertex3f (35.76f, 57.55f, 0.50f);
	   	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (35.01f, 57.65f, 0.50f);
	    glVertex3f (35.01f, 57.65f, 0.38f);
	    glVertex3f (34.27f, 57.55f, 0.38f);
	    glVertex3f (33.57f, 57.27f, 0.38f);
	    glVertex3f (33.57f, 57.27f, 0.50f);
	    glVertex3f (34.27f, 57.55f, 0.50f);
	   	glEnd();
	glPopMatrix();
	//
		glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (33.57f, 57.27f, 0.50f);
	    glVertex3f (33.57f, 57.27f, 0.38f);
	    glVertex3f (32.98f, 56.81f, 0.38f);
	    glVertex3f (32.52f, 56.21f, 0.38f);
	    glVertex3f (32.52f, 56.21f, 0.50f);
	    glVertex3f (32.98f, 56.81f, 0.50f);
	   	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (32.52f, 56.21f, 0.50f);
	    glVertex3f (32.52f, 56.21f, 0.38f);
	    glVertex3f (32.23f, 55.52f, 0.38f);
	    glVertex3f (32.13f, 54.77f, 0.38f);
	    glVertex3f (32.13f, 54.77f, 0.50f);
	    glVertex3f (32.23f, 55.52f, 0.50f);
	   	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (32.13f, 54.77f, 0.50f);
	    glVertex3f (32.13f, 54.77f, 0.38f);
	    glVertex3f (32.23f, 54.03f, 0.38f);
	    glVertex3f (32.52f, 53.33f, 0.38f);
	    glVertex3f (32.52f, 53.33f, 0.50f);
	    glVertex3f (32.23f, 54.03f, 0.50f);
	   	glEnd();
	glPopMatrix();
	//WALL INSIDE
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (35.01f, 57.45f, 0.50f);
	    glVertex3f (35.01f, 57.45f, 0.26f);
	    glVertex3f (35.71f, 57.36f, 0.26f);
	    glVertex3f (35.71f, 57.36f, 0.50f);
	   	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (35.71f, 57.36f, 0.50f);
	    glVertex3f (35.71f, 57.36f, 0.26f);
	    glVertex3f (36.35f, 57.09f, 0.26f);
	    glVertex3f (36.35f, 57.09f, 0.50f);
	   	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (36.35f, 57.09f, 0.50f);
	    glVertex3f (36.35f, 57.09f, 0.26f);
	    glVertex3f (36.91f, 56.66f, 0.26f);
	    glVertex3f (36.91f, 56.66f, 0.50f);
	   	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (36.91f, 56.66f, 0.50f);
	    glVertex3f (36.91f, 56.66f, 0.26f);
	    glVertex3f (37.33f, 56.11f, 0.26f);
	    glVertex3f (37.33f, 56.11f, 0.50f);
	   	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (37.33f, 56.11f, 0.50f);
	    glVertex3f (37.33f, 56.11f, 0.26f);
	    glVertex3f (37.60f, 55.46f, 0.26f);
	    glVertex3f (37.60f, 55.46f, 0.50f);
	   	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (37.60f, 55.46f, 0.50f);
	    glVertex3f (37.60f, 55.46f, 0.26f);
	    glVertex3f (37.69f, 54.77f, 0.26f);
	    glVertex3f (37.69f, 54.77f, 0.50f);
	   	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (37.69f, 54.77f, 0.50f);
	    glVertex3f (37.69f, 54.77f, 0.26f);
	    glVertex3f (37.60f, 54.08f, 0.26f);
	    glVertex3f (37.60f, 54.08f, 0.50f);
	   	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (37.60f, 54.08f, 0.50f);
	    glVertex3f (37.60f, 54.08f, 0.26f);
	    glVertex3f (37.33f, 53.43f, 0.26f);
	    glVertex3f (37.33f, 53.43f, 0.50f);
	   	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (37.33f, 53.43f, 0.50f);
	    glVertex3f (37.33f, 53.43f, 0.26f);
	    glVertex3f (36.91f, 52.88f, 0.26f);
	    glVertex3f (36.91f, 52.88f, 0.50f);
	   	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (36.91f, 52.88f, 0.50f);
	    glVertex3f (36.91f, 52.88f, 0.26f);
	    glVertex3f (36.35f, 52.45f, 0.26f);
	    glVertex3f (36.35f, 52.45f, 0.50f);
	   	glEnd();
	glPopMatrix();
	//
		glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (36.35f, 52.45f, 0.50f);
	    glVertex3f (36.35f, 52.45f, 0.26f);
	    glVertex3f (35.71f, 52.19f, 0.26f);
	    glVertex3f (35.71f, 52.19f, 0.50f);
	   	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (35.71f, 52.19f, 0.50f);
	    glVertex3f (35.71f, 52.19f, 0.26f);
	    glVertex3f (35.01f, 52.09f, 0.26f);
	    glVertex3f (35.01f, 52.09f, 0.50f);
	   	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (35.01f, 52.09f, 0.50f);
	    glVertex3f (35.01f, 52.09f, 0.26f);
	    glVertex3f (34.32f, 52.19f, 0.26f);
	    glVertex3f (34.32f, 52.19f, 0.50f);
	   	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (34.32f, 52.19f, 0.50f);
	    glVertex3f (34.32f, 52.19f, 0.26f);
	    glVertex3f (33.68f, 52.45f, 0.26f);
	    glVertex3f (33.68f, 52.45f, 0.50f);
	   	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (33.68f, 52.45f, 0.50f);
	    glVertex3f (33.68f, 52.45f, 0.26f);
	    glVertex3f (33.12f, 52.88f, 0.26f);
	    glVertex3f (33.12f, 52.88f, 0.50f);
	   	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (33.12f, 52.88f, 0.50f);
	    glVertex3f (33.12f, 52.88f, 0.26f);
	    glVertex3f (32.70f, 53.43f, 0.26f);
	    glVertex3f (32.70f, 53.43f, 0.50f);
	   	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (32.70f, 53.43f, 0.50f);
	    glVertex3f (32.70f, 53.43f, 0.26f);
	    glVertex3f (32.43f, 54.08f, 0.26f);
	    glVertex3f (32.43f, 54.08f, 0.50f);
	   	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (32.43f, 54.08f, 0.50f);
	    glVertex3f (32.43f, 54.08f, 0.26f);
	    glVertex3f (32.34f, 54.77f, 0.26f);
	    glVertex3f (32.34f, 54.77f, 0.50f);
	   	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (32.34f, 54.77f, 0.50f);
	    glVertex3f (32.34f, 54.77f, 0.26f);
	    glVertex3f (32.43f, 55.46f, 0.26f);
	    glVertex3f (32.43f, 55.46f, 0.50f);
	   	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (32.43f, 55.46f, 0.50f);
	    glVertex3f (32.43f, 55.46f, 0.26f);
	    glVertex3f (32.70f, 56.11f, 0.26f);
	    glVertex3f (32.70f, 56.11f, 0.50f);
	   	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (32.70f, 56.11f, 0.50f);
	    glVertex3f (32.70f, 56.11f, 0.26f);
	    glVertex3f (33.12f, 56.66f, 0.26f);
	    glVertex3f (33.12f, 56.66f, 0.50f);
	   	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (33.12f, 56.66f, 0.50f);
	    glVertex3f (33.12f, 56.66f, 0.26f);
	    glVertex3f (33.68f, 57.09f, 0.26f);
	    glVertex3f (33.68f, 57.09f, 0.50f);
	   	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (33.68f, 57.09f, 0.50f);
	    glVertex3f (33.68f, 57.09f, 0.26f);
	    glVertex3f (34.32f, 57.36f, 0.26f);
	    glVertex3f (34.32f, 57.36f, 0.50f);
	   	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (34.32f, 57.36f, 0.50f);
	    glVertex3f (34.32f, 57.36f, 0.26f);
	    glVertex3f (35.01f, 57.45f, 0.26f);
	    glVertex3f (35.01f, 57.45f, 0.50f);
	   	glEnd();
	glPopMatrix();
	
	//EXTRE DELINEATION MUROS - exteriores 
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glColor4f (0.0f, 0.0f, 0.0f, 0.0f);
	    glVertex3f (32.52f, 53.33f, 0.50f);
	    glVertex3f (32.98f, 52.74f, 0.50f);
	    glVertex3f (33.57f, 52.28f, 0.50f);
	    glVertex3f (34.27f, 51.99f, 0.50f);
	    glVertex3f (35.01f, 51.89f, 0.50f);
	    glVertex3f (35.76f, 51.99f, 0.50f);
	    glVertex3f (36.45f, 52.28f, 0.50f);
	    glVertex3f (37.05f, 52.74f, 0.50f);
	    glVertex3f (37.51f, 53.33f, 0.50f);
	    glVertex3f (37.80f, 54.03f, 0.50f);
	    glVertex3f (37.89f, 54.77f, 0.50f);
	    glVertex3f (37.80f, 55.52f, 0.50f);
	    glVertex3f (37.51f, 56.21f, 0.50f);
	    glVertex3f (37.05f, 56.81f, 0.50f);
	    glVertex3f (36.45f, 57.27f, 0.50f);
	    glVertex3f (35.76f, 57.55f, 0.50f);
	    glVertex3f (35.01f, 57.65f, 0.50f);
	    glVertex3f (34.27f, 57.55f, 0.50f);
	    glVertex3f (33.57f, 57.27f, 0.50f);
	    glVertex3f (32.98f, 56.81f, 0.50f);
	    glVertex3f (32.52f, 56.21f, 0.50f);
	    glVertex3f (32.23f, 55.52f, 0.50f);
	    glVertex3f (32.13f, 54.77f, 0.50f);
	    glVertex3f (32.23f, 54.03f, 0.50f);
	   	glEnd();
	glPopMatrix();
	
	////pasto central
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.42f, 0.6f, 0.3f, 1.0f);
	    glVertex3f (32.70f, 53.43f, 0.26f);
	    glVertex3f (32.43f, 54.08f, 0.26f);
	    glVertex3f (32.34f, 54.77f, 0.26f);
	    glVertex3f (32.43f, 55.46f, 0.26f);
	    glVertex3f (32.70f, 56.11f, 0.26f);
	    glVertex3f (33.12f, 56.66f, 0.26f);
	    glVertex3f (33.68f, 57.09f, 0.26f);
	    glVertex3f (34.32f, 57.36f, 0.26f);
	    glVertex3f (35.01f, 57.45f, 0.26f);
	    glVertex3f (35.71f, 57.36f, 0.26f);
	    glVertex3f (36.35f, 57.09f, 0.26f);
	    glVertex3f (36.91f, 56.66f, 0.26f);
	    glVertex3f (37.33f, 56.11f, 0.26f);
	    glVertex3f (37.60f, 55.46f, 0.26f);
	    glVertex3f (37.69f, 54.77f, 0.26f);
	    glVertex3f (37.60f, 54.08f, 0.26f);
	    glVertex3f (37.33f, 53.43f, 0.26f);
	    glVertex3f (36.91f, 52.88f, 0.26f);
	    glVertex3f (36.35f, 52.45f, 0.26f);
	    glVertex3f (35.71f, 52.19f, 0.26f);
	    glVertex3f (35.01f, 52.09f, 0.26f);
	    glVertex3f (34.32f, 52.19f, 0.26f);
	    glVertex3f (33.68f, 52.45f, 0.26f);
	    glVertex3f (33.12f, 52.88f, 0.26f);
	  glEnd();
	glPopMatrix();
	
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (30.58f, 62.74f, 0.50f);
	    glVertex3f (30.58f, 62.60f, 0.50f);
	    glVertex3f (32.98f, 62.60f, 0.50f);
	    glVertex3f (32.98f, 62.74f, 0.50f);
		glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.5f, 0.27f, 0.24f, 1.0f);
	    glVertex3f (30.58f, 62.60f, 0.50f);
	    glVertex3f (30.58f, 62.60f, 0.38f);
	    glVertex3f (32.98f, 62.60f, 0.38f);
	    glVertex3f (32.98f, 62.60f, 0.50f);
		glEnd();
	glPopMatrix();
	
	//delineation central
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glColor4f (0.0f, 0.0f, 0.0f, 0.0f);
	    glVertex3f (32.70f, 53.43f, 0.50f);
	    glVertex3f (32.43f, 54.08f, 0.50f);
	    glVertex3f (32.34f, 54.77f, 0.50f);
	    glVertex3f (32.43f, 55.46f, 0.50f);
	    glVertex3f (32.70f, 56.11f, 0.50f);
	    glVertex3f (33.12f, 56.66f, 0.50f);
	    glVertex3f (33.68f, 57.09f, 0.50f);
	    glVertex3f (34.32f, 57.36f, 0.50f);
	    glVertex3f (35.01f, 57.45f, 0.50f);
	    glVertex3f (35.71f, 57.36f, 0.50f);
	    glVertex3f (36.35f, 57.09f, 0.50f);
	    glVertex3f (36.91f, 56.66f, 0.50f);
	    glVertex3f (37.33f, 56.11f, 0.50f);
	    glVertex3f (37.60f, 55.46f, 0.50f);
	    glVertex3f (37.69f, 54.77f, 0.50f);
	    glVertex3f (37.60f, 54.08f, 0.50f);
	    glVertex3f (37.33f, 53.43f, 0.50f);
	    glVertex3f (36.91f, 52.88f, 0.50f);
	    glVertex3f (36.35f, 52.45f, 0.50f);
	    glVertex3f (35.71f, 52.19f, 0.50f);
	    glVertex3f (35.01f, 52.09f, 0.50f);
	    glVertex3f (34.32f, 52.19f, 0.50f);
	    glVertex3f (33.68f, 52.45f, 0.50f);
	    glVertex3f (33.12f, 52.88f, 0.50f);
	  glEnd();
	glPopMatrix();
	
}

void estacionation(){
	//UP
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f (0.3f, 0.3f, 0.3f);
	    glVertex3f (61.44f, 40.32f, 0.05f); 
		glVertex3f (73.86f, 40.32f, 0.05f);
		glVertex3f (73.86f, 111.08f, 0.05f);   
		glVertex3f (61.44f, 111.08f, 0.05f); 
	glEnd();
	glPopMatrix();
	//DELINEATION 
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glColor3f (0.0f, 0.0f, 0.0f);
	    glVertex3f (61.44f, 40.32f, 0.05f); 
		glVertex3f (73.86f, 40.32f, 0.05f);
		glVertex3f (73.86f, 111.08f, 0.05f);   
		glVertex3f (61.44f, 111.08f, 0.05f); 
	glEnd();
	glPopMatrix();
	//SIDE-ON
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f (0.3f, 0.3f, 0.3f);
	    glVertex3f (61.44f, 111.08f, 0.05f); 
		glVertex3f (61.44f, 111.08f, 0.0f);
		glVertex3f (73.86f, 111.08f, 0.0f);   
		glVertex3f (73.86f, 111.08f, 0.05f); 
	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f (0.3f, 0.3f, 0.3f);
	    glVertex3f (73.86f, 111.08f, 0.05f); 
		glVertex3f (73.86f, 111.08f, 0.0f);
		glVertex3f (73.86f, 40.32f, 0.0f);   
		glVertex3f (73.86f, 40.32f, 0.05f); 
	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f (0.3f, 0.3f, 0.3f);
	    glVertex3f (73.86f, 40.32f, 0.05f);  
		glVertex3f (73.86f, 40.32f, 0.0f);
		glVertex3f (61.44f, 40.32f, 0.0f);   
		glVertex3f (61.44f, 40.32f, 0.05f); 
	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f (0.3f, 0.3f, 0.3f);
	    glVertex3f (61.44f, 111.08f, 0.05f);  
		glVertex3f (61.44f, 111.08f, 0.0f);
		glVertex3f (61.44f, 104.75f, 0.0f);   
		glVertex3f (61.44f, 104.75f, 0.05f); 
	glEnd();
	glPopMatrix();
	//RAMPA
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f (0.3f, 0.3f, 0.3f);
	    glVertex3f (73.86f, 45.90f, 0.05f); 
		glVertex3f (77.12f, 45.90f, 0.0f);
		glVertex3f (77.12f, 52.41f, 0.0f);   
		glVertex3f (73.86f, 52.41f, 0.05f); 
	glEnd();
	glPopMatrix();
	//RAMP - RIGHT 
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glColor3f (0.3f, 0.3f, 0.3f);
	    glVertex3f (73.86f, 52.41f, 0.05f);  
		glVertex3f (73.86f, 52.41f, 0.0f);
		glVertex3f (77.12f, 52.41f, 0.0f);  
	glEnd();
	glPopMatrix();
	//DELINEATION
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glColor3f (0.0f, 0.0f, 0.0f);
	    glVertex3f (73.86f, 52.41f, 0.05f);  
		glVertex3f (73.86f, 52.41f, 0.0f);
		glVertex3f (77.12f, 52.41f, 0.0f);  
	glEnd();
	glPopMatrix();
	//RAMP - LEFT 
		glPushMatrix();
	glBegin(GL_TRIANGLES);
	glColor3f (0.3f, 0.3f, 0.3f);
	    glVertex3f (77.12f, 45.90f, 0.0f);  
		glVertex3f (73.86f, 45.90f, 0.05f);
		glVertex3f (73.86f, 45.90f, 0.0f);  
	glEnd();
	glPopMatrix();
	//DELINEATION
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glColor3f (0.0f, 0.0f, 0.0f);
	    glVertex3f (77.12f, 45.90f, 0.0f);  
		glVertex3f (73.86f, 45.90f, 0.05f);
		glVertex3f (73.86f, 45.90f, 0.0f);  
	glEnd();
	glPopMatrix();
	//vereda ploma 
    glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.62f, 0.62f, 0.62f, 1.0f);
	    glVertex3f (61.44f, 40.58f, 0.20f); 
		glVertex3f (66.77f, 40.58f, 0.20f);
		glVertex3f (66.96f, 40.61f, 0.20f);   
		glVertex3f (67.16f, 40.69f, 0.20f);
		glVertex3f (67.34f, 40.82f, 0.20f);
		glVertex3f (67.51f, 41.0f, 0.20f);
		glVertex3f (67.67f, 41.22f, 0.20f);
		glVertex3f (67.81f, 41.48f, 0.20f);
		glVertex3f (67.92f, 41.78f, 0.20f);
		glVertex3f (68.02f, 42.11f, 0.20f); 
		glVertex3f (68.09f, 42.46f, 0.20f); 
		glVertex3f (68.13f, 42.83f, 0.20f); 
		glVertex3f (68.14f, 43.20f, 0.20f);
		glVertex3f (68.14f, 43.78f, 0.20f);
		glVertex3f (68.13f, 43.99f, 0.20f);
		glVertex3f (68.11f, 44.19f, 0.20f);
		glVertex3f (68.07f, 44.39f, 0.20f);
		glVertex3f (68.02f, 44.57f, 0.20f);
		glVertex3f (67.96f, 44.74f, 0.20f);
		glVertex3f (67.88f, 44.88f, 0.20f);
		glVertex3f (67.79f, 45.01f, 0.20f);
		glVertex3f (67.70f, 45.11f, 0.20f);
		glVertex3f (67.59f, 45.18f, 0.20f);
		glVertex3f (67.49f, 45.23f, 0.20f);
		glVertex3f (67.38f, 45.24f, 0.20f);
		glVertex3f (61.44f, 45.24f, 0.20f); 
	glEnd();
	glPopMatrix();
	//DELINEATION
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	glColor4f (0.0f, 0.0f, 0.0f, 0.0f);
	    glVertex3f (61.44f, 40.58f, 0.20f); 
		glVertex3f (66.77f, 40.58f, 0.20f);
		glVertex3f (66.96f, 40.61f, 0.20f);   
		glVertex3f (67.16f, 40.69f, 0.20f);
		glVertex3f (67.34f, 40.82f, 0.20f);
		glVertex3f (67.51f, 41.0f, 0.20f);
		glVertex3f (67.67f, 41.22f, 0.20f);
		glVertex3f (67.81f, 41.48f, 0.20f);
		glVertex3f (67.92f, 41.78f, 0.20f);
		glVertex3f (68.02f, 42.11f, 0.20f); 
		glVertex3f (68.09f, 42.46f, 0.20f); 
		glVertex3f (68.13f, 42.83f, 0.20f); 
		glVertex3f (68.14f, 43.20f, 0.20f);
		glVertex3f (68.14f, 43.78f, 0.20f);
		glVertex3f (68.13f, 43.99f, 0.20f);
		glVertex3f (68.11f, 44.19f, 0.20f);
		glVertex3f (68.07f, 44.39f, 0.20f);
		glVertex3f (68.02f, 44.57f, 0.20f);
		glVertex3f (67.96f, 44.74f, 0.20f);
		glVertex3f (67.88f, 44.88f, 0.20f);
		glVertex3f (67.79f, 45.01f, 0.20f);
		glVertex3f (67.70f, 45.11f, 0.20f);
		glVertex3f (67.59f, 45.18f, 0.20f);
		glVertex3f (67.49f, 45.23f, 0.20f);
		glVertex3f (67.38f, 45.24f, 0.20f);
		glVertex3f (62.65f, 45.24f, 0.20f); 
	glEnd();
	glPopMatrix();
	//
		glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.62f, 0.62f, 0.62f, 1.0f);
	    glVertex3f (61.44f, 45.24f, 0.20f); 
		glVertex3f (62.65f, 45.24f, 0.20f);
		glVertex3f (62.65f, 106.42f, 0.20f);   
		glVertex3f (61.44f, 106.42f, 0.20f); 
	glEnd();
	glPopMatrix();
	
	
	
	
	
	//YELLOW LINES
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (1.0f, 1.0f, 0.0f, 1.0f);
	    glVertex3f (61.44f, 40.58f, 0.20f); 
		glVertex3f (61.44f, 40.29f, 0.20f);
		glVertex3f (66.77f, 40.29f, 0.20f);   
		glVertex3f (66.77f, 40.58f, 0.20f); 
	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (1.0f, 1.0f, 0.0f, 1.0f);
	    glVertex3f (66.77f, 40.58f, 0.20f);  
		glVertex3f (66.77f, 40.29f, 0.20f); 
		glVertex3f (66.99f, 40.32f, 0.20f);   
		glVertex3f (66.96f, 40.61f, 0.20f); 
	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (1.0f, 1.0f, 0.0f, 1.0f);
	    glVertex3f (66.96f, 40.61f, 0.20f);  
		glVertex3f (66.99f, 40.32f, 0.20f); 
		glVertex3f (67.20f, 40.41f, 0.20f);   
		glVertex3f (67.16f, 40.69f, 0.20f); 
	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (1.0f, 1.0f, 0.0f, 1.0f);
	    glVertex3f (67.16f, 40.69f, 0.20f);  
		glVertex3f (67.20f, 40.41f, 0.20f); 
		glVertex3f (67.40f, 40.55f, 0.20f);   
		glVertex3f (67.34f, 40.82f, 0.20f); 
	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (1.0f, 1.0f, 0.0f, 1.0f);
	    glVertex3f (67.34f, 40.82f, 0.20f);  
		glVertex3f (67.40f, 40.55f, 0.20f); 
		glVertex3f (67.59f, 40.75f, 0.20f);   
		glVertex3f (67.51f, 41.0f, 0.20f); 
	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (1.0f, 1.0f, 0.0f, 1.0f);
	    glVertex3f (67.51f, 41.0f, 0.20f);  
		glVertex3f (67.59f, 40.75f, 0.20f); 
		glVertex3f (67.77f, 41.0f, 0.20f);   
		glVertex3f (67.67f, 41.22f, 0.20f); 
	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (1.0f, 1.0f, 0.0f, 1.0f);
	    glVertex3f (67.67f, 41.22f, 0.20f);   
		glVertex3f (67.77f, 41.0f, 0.20f); 
		glVertex3f (67.92f, 41.29f, 0.20f);   
		glVertex3f (67.81f, 41.48f, 0.20f); 
	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (1.0f, 1.0f, 0.0f, 1.0f);
	    glVertex3f (67.81f, 41.48f, 0.20f);    
		glVertex3f (67.92f, 41.29f, 0.20f); 
		glVertex3f (68.05f, 41.63f, 0.20f);   
		glVertex3f (67.92f, 41.78f, 0.20f); 
	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (1.0f, 1.0f, 0.0f, 1.0f);
	    glVertex3f (67.92f, 41.78f, 0.20f);    
		glVertex3f (68.05f, 41.63f, 0.20f);  
		glVertex3f (68.16f, 41.99f, 0.20f);   
		glVertex3f (68.02f, 42.11f, 0.20f); 
	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (1.0f, 1.0f, 0.0f, 1.0f);
	    glVertex3f (68.02f, 42.11f, 0.20f);    
		glVertex3f (68.16f, 41.99f, 0.20f);  
		glVertex3f (68.23f, 42.38f, 0.20f);   
		glVertex3f (68.09f, 42.46f, 0.20f); 
	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (1.0f, 1.0f, 0.0f, 1.0f);
	    glVertex3f (68.09f, 42.46f, 0.20f);   
		glVertex3f (68.23f, 42.38f, 0.20f);  
		glVertex3f (68.28f, 42.79f, 0.20f);   
		glVertex3f (68.13f, 42.83f, 0.20f); 
	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (1.0f, 1.0f, 0.0f, 1.0f);
	    glVertex3f (68.13f, 42.83f, 0.20f);   
		glVertex3f (68.28f, 42.79f, 0.20f);   
		glVertex3f (68.29f, 43.20f, 0.20f);   
		glVertex3f (68.14f, 43.20f, 0.20f); 
	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (1.0f, 1.0f, 0.0f, 1.0f);
	    glVertex3f (68.14f, 43.20f, 0.20f);    
		glVertex3f (68.29f, 43.20f, 0.20f);    
		glVertex3f (68.29f, 43.78f, 0.20f);   
		glVertex3f (68.14f, 43.78f, 0.20f); 
	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (1.0f, 1.0f, 0.0f, 1.0f);
	    glVertex3f (68.14f, 43.78f, 0.20f);     
		glVertex3f (68.29f, 43.78f, 0.20f);    
		glVertex3f (68.28f, 44.03f, 0.20f);   
		glVertex3f (68.13f, 43.99f, 0.20f); 
	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (1.0f, 1.0f, 0.0f, 1.0f);
	    glVertex3f (68.13f, 43.99f, 0.20f);     
		glVertex3f (68.28f, 44.03f, 0.20f);    
		glVertex3f (68.26f, 44.28f, 0.20f);   
		glVertex3f (68.11f, 44.19f, 0.20f); 
	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (1.0f, 1.0f, 0.0f, 1.0f);
	    glVertex3f (68.11f, 44.19f, 0.20f);      
		glVertex3f (68.26f, 44.28f, 0.20f);    
		glVertex3f (68.21f, 44.51f, 0.20f);   
		glVertex3f (68.07f, 44.39f, 0.20f); 
	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (1.0f, 1.0f, 0.0f, 1.0f);
	    glVertex3f (68.07f, 44.39f, 0.20f);      
		glVertex3f (68.21f, 44.51f, 0.20f);    
		glVertex3f (68.15f, 44.73f, 0.20f);   
		glVertex3f (68.02f, 44.57f, 0.20f); 
	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (1.0f, 1.0f, 0.0f, 1.0f);
	    glVertex3f (68.02f, 44.57f, 0.20f);       
		glVertex3f (68.15f, 44.73f, 0.20f);     
		glVertex3f (67.98f, 45.11f, 0.20f);   
		glVertex3f (67.88f, 44.88f, 0.20f); 
	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (1.0f, 1.0f, 0.0f, 1.0f);
	    glVertex3f (67.88f, 44.88f, 0.20f);        
		glVertex3f (67.98f, 45.11f, 0.20f);     
		glVertex3f (67.76f, 45.37f, 0.20f);   
		glVertex3f (67.70f, 45.11f, 0.20f); 
	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (1.0f, 1.0f, 0.0f, 1.0f);
	    glVertex3f (67.70f, 45.11f, 0.20f);        
		glVertex3f (67.76f, 45.37f, 0.20f);     
		glVertex3f (67.64f, 45.46f, 0.20f);   
		glVertex3f (67.59f, 45.18f, 0.20f); 
	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (1.0f, 1.0f, 0.0f, 1.0f);
	    glVertex3f (67.59f, 45.18f, 0.20f);       
		glVertex3f (67.64f, 45.46f, 0.20f);      
		glVertex3f (67.51f, 45.51f, 0.20f);   
		glVertex3f (67.49f, 45.23f, 0.20f); 
	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (1.0f, 1.0f, 0.0f, 1.0f);
	    glVertex3f (67.49f, 45.23f, 0.20f);        
		glVertex3f (67.51f, 45.51f, 0.20f);      
		glVertex3f (67.38f, 45.53f, 0.20f);   
		glVertex3f (67.38f, 45.24f, 0.20f); 
	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (1.0f, 1.0f, 0.0f, 1.0f);
	    glVertex3f (67.38f, 45.24f, 0.20f);         
		glVertex3f (67.38f, 45.53f, 0.20f);      
		glVertex3f (62.65f, 45.53f, 0.20f);   
		glVertex3f (62.65f, 45.24f, 0.20f); 
	glEnd();
	glPopMatrix();
	//
		glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (1.0f, 1.0f, 0.0f, 1.0f);
	    glVertex3f (62.65f, 45.53f, 0.20f);         
		glVertex3f (62.81f, 45.53f, 0.20f);      
		glVertex3f (62.81f, 106.13f, 0.20f);   
		glVertex3f (62.65f, 106.13f, 0.20f); 
	glEnd();
	glPopMatrix();
	//GRASS
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.29f, 0.43f, 0.2f, 1.0f);
	    glVertex3f (73.86f, 52.41f, 0.0f); 
	    glVertex3f (77.12f, 52.41f, 0.0f); 
	    glVertex3f (77.12f, 111.08f, 0.0f);
		glVertex3f (73.86f, 111.08f, 0.0f);  
	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.29f, 0.43f, 0.2f, 1.0f);
	    glVertex3f (73.86f, 40.32f, 0.0f); 
	    glVertex3f (77.12f, 40.32f, 0.0f); 
	    glVertex3f (77.12f, 45.90f, 0.0f);
		glVertex3f (73.86f, 45.90f, 0.0f);  
	glEnd();
	glPopMatrix();
}

void paloCurviado(){
	glPushMatrix();
	glTranslatef(1.8f, 0.0f, 0.0f);
	//palo curviado 
	// de lado 
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	     glVertex3f (52.36f, 54.32f, 0.38f);
	     glVertex3f (52.36f, 54.28f, 0.38f);
	     glVertex3f (52.36f, 54.28f, 0.85f);
	     glVertex3f (52.36f, 54.32f, 0.85f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	     glVertex3f (52.36f, 54.32f, 0.85f);
	     glVertex3f (52.36f, 54.28f, 0.85f);
	     glVertex3f (52.36f, 54.27f, 0.88f);
	     glVertex3f (52.36f, 54.25f, 0.92f);
	     glVertex3f (52.36f, 54.28f, 0.94f);
	     glVertex3f (52.36f, 54.31f, 0.90f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	    glVertex3f (52.36f, 54.28f, 0.94f);
	    glVertex3f (52.36f, 54.25f, 0.92f);
	     glVertex3f (52.36f, 54.23f, 0.94f);
	     glVertex3f (52.36f, 54.19f, 0.95f);
	     glVertex3f (52.36f, 54.20f, 0.99f);
	     glVertex3f (52.36f, 54.25f, 0.97f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	    glVertex3f (52.36f, 54.20f, 0.99f);
	    glVertex3f (52.36f, 54.19f, 0.95f);
	     glVertex3f (52.36f, 53.87f, 0.95f);
	     glVertex3f (52.36f, 53.86f, 0.99f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	    glVertex3f (52.36f, 53.86f, 0.99f);
	    glVertex3f (52.36f, 53.87f, 0.95f);
	     glVertex3f (52.36f, 53.83f, 0.94f);
	     glVertex3f (52.36f, 53.80f, 0.91f);
	     glVertex3f (52.36f, 53.77f, 0.93f);
	     glVertex3f (52.36f, 53.81f, 0.97f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	    glVertex3f (52.36f, 53.77f, 0.93f);
	    glVertex3f (52.36f, 53.80f, 0.91f);
	     glVertex3f (52.36f, 53.78f, 0.87f);
	     glVertex3f (52.36f, 53.77f, 0.83f);
	     glVertex3f (52.36f, 53.73f, 0.83f);
	     glVertex3f (52.36f, 53.74f, 0.89f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	    glVertex3f (52.36f, 53.77f, 0.83f);
	    glVertex3f (52.36f, 53.77f, 0.38f);
	     glVertex3f (52.36f, 53.73f, 0.38f);
	     glVertex3f (52.36f, 53.73f, 0.83f);
   glEnd();
	glPopMatrix();
	
	//de frente
		glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	    glVertex3f (52.40f, 54.32f, 0.85f);
	    glVertex3f (52.40f, 54.32f, 0.38f);
	     glVertex3f (52.36f, 54.32f, 0.38f);
	     glVertex3f (52.36f, 54.32f, 0.85f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	    glVertex3f (52.40f, 54.28f, 0.94f);
	    glVertex3f (52.40f, 54.31f, 0.90f);
	     glVertex3f (52.40f, 54.32f, 0.85f);
	     glVertex3f (52.36f, 54.32f, 0.85f);
	     glVertex3f (52.36f, 54.31f, 0.90f);
	     glVertex3f (52.36f, 54.28f, 0.94f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	    glVertex3f (52.40f, 54.20f, 0.99f);
	    glVertex3f (52.40f, 54.25f, 0.97f);
	     glVertex3f (52.40f, 54.28f, 0.94f);
	     glVertex3f (52.36f, 54.28f, 0.94f);
	     glVertex3f (52.36f, 54.25f, 0.97f);
	     glVertex3f (52.36f, 54.20f, 0.99f);
   glEnd();
	glPopMatrix();
		glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	    glVertex3f (52.40f, 54.20f, 0.99f);
	    glVertex3f (52.36f, 54.20f, 0.99f);
	     glVertex3f (52.36f, 53.86f, 0.99f);
	     glVertex3f (52.40f, 53.86f, 0.99f);
   glEnd();
	glPopMatrix();
		glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	    glVertex3f (52.36f, 53.86f, 0.99f);
	    glVertex3f (52.36f, 53.81f, 0.97f);
	     glVertex3f (52.36f, 53.77f, 0.93f);
	     glVertex3f (52.40f, 53.77f, 0.93f);
	     glVertex3f (52.40f, 53.81f, 0.97f);
	     glVertex3f (52.40f, 53.86f, 0.99f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	    glVertex3f (52.36f, 53.77f, 0.93f);
	    glVertex3f (52.36f, 53.74f, 0.89f);
	     glVertex3f (52.36f, 53.73f, 0.83f);
	     glVertex3f (52.40f, 53.73f, 0.83f);
	     glVertex3f (52.40f, 53.74f, 0.89f);
	     glVertex3f (52.40f, 53.77f, 0.93f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	    glVertex3f (52.36f, 53.73f, 0.83f);
	    glVertex3f (52.36f, 53.73f, 0.38f);
	     glVertex3f (52.40f, 53.73f, 0.38f);
	     glVertex3f (52.40f, 53.73f, 0.83f);
   glEnd();
	glPopMatrix();
	
	glPopMatrix();
	
	//tranlate del lado del banco
	glPushMatrix();
	glTranslatef(1.7f, 0.0f, 0.0f);
	//HERE - //cara del lado izquierdo 
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	    glVertex3f (52.46f, 54.38f, 1.30f);
	    glVertex3f (52.41f, 54.38f, 1.30f);
	    glVertex3f (52.41f, 54.35f, 1.30f);
	    glVertex3f (52.46f, 54.35f, 1.30f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	     glVertex3f (52.46f, 54.35f, 1.30f);
	     glVertex3f (52.41f, 54.35f, 1.30f);
	     glVertex3f (52.41f, 54.33f, 1.29f);
	     glVertex3f (52.46f, 54.33f, 1.29f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	     glVertex3f (52.46f, 54.33f, 1.29f);
	     glVertex3f (52.41f, 54.33f, 1.29f);
	     glVertex3f (52.41f, 54.31f, 1.26f);
	     glVertex3f (52.46f, 54.31f, 1.26f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	     glVertex3f (52.46f, 54.31f, 1.26f);
	     glVertex3f (52.41f, 54.31f, 1.26f);
	     glVertex3f (52.41f, 54.22f, 0.89f);
	     glVertex3f (52.46f, 54.22f, 0.89f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	     glVertex3f (52.46f, 54.22f, 0.89f);
	     glVertex3f (52.41f, 54.22f, 0.89f);
	     glVertex3f (52.41f, 54.18f, 0.85f);
	     glVertex3f (52.46f, 54.18f, 0.85f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	     glVertex3f (52.46f, 54.18f, 0.85f);
	     glVertex3f (52.41f, 54.18f, 0.85f);
	     glVertex3f (52.41f, 54.13f, 0.82f);
	     glVertex3f (52.46f, 54.13f, 0.82f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	     glVertex3f (52.46f, 54.13f, 0.82f);
	     glVertex3f (52.41f, 54.13f, 0.82f);
	     glVertex3f (52.41f, 54.07f, 0.81f);
	     glVertex3f (52.46f, 54.07f, 0.81f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	     glVertex3f (52.46f, 54.07f, 0.81f);
	     glVertex3f (52.41f, 54.07f, 0.81f);
	     glVertex3f (52.41f, 53.78f, 0.81f);
	     glVertex3f (52.46f, 53.78f, 0.81f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	     glVertex3f (52.46f, 53.78f, 0.81f);
	     glVertex3f (52.41f, 53.78f, 0.81f);
	     glVertex3f (52.41f, 53.74f, 0.79f);
	     glVertex3f (52.46f, 53.74f, 0.79f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	     glVertex3f (52.46f, 53.74f, 0.79f);
	     glVertex3f (52.41f, 53.74f, 0.79f);
	     glVertex3f (52.41f, 53.71f, 0.76f);
	     glVertex3f (52.41f, 53.70f, 0.71f);
	     glVertex3f (52.46f, 53.70f, 0.71f);
	     glVertex3f (52.46f, 53.71f, 0.76f);
   glEnd();
	glPopMatrix();
	
	//costado de la parte izquierda
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	    glVertex3f (52.41f, 54.38f, 1.30f);
	    glVertex3f (52.41f, 54.38f, 1.28f);
	    glVertex3f (52.41f, 54.36f, 1.28f);
	    glVertex3f (52.41f, 54.35f, 1.30f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	    glVertex3f (52.41f, 54.35f, 1.30f);
	    glVertex3f (52.41f, 54.36f, 1.28f);
	    glVertex3f (52.41f, 54.34f, 1.27f);
	    glVertex3f (52.41f, 54.33f, 1.29f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	    glVertex3f (52.41f, 54.33f, 1.29f);
	    glVertex3f (52.41f, 54.34f, 1.27f);
	    glVertex3f (52.41f, 54.33f, 1.25f);
	    glVertex3f (52.41f, 54.31f, 1.26f);
   glEnd();
	glPopMatrix();	
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	    glVertex3f (52.41f, 54.31f, 1.26f);
	    glVertex3f (52.41f, 54.33f, 1.25f);
	    glVertex3f (52.41f, 54.24f, 0.88f);
	    glVertex3f (52.41f, 54.22f, 0.89f);
   glEnd();
	glPopMatrix();	
	//
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	    glVertex3f (52.41f, 54.22f, 0.89f);
	    glVertex3f (52.41f, 54.24f, 0.88f);
	    glVertex3f (52.41f, 54.19f, 0.83f);
	    glVertex3f (52.41f, 54.14f, 0.80f);
	    glVertex3f (52.41f, 54.13f, 0.82f);
	    glVertex3f (52.41f, 54.18f, 0.85f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	    glVertex3f (52.41f, 54.13f, 0.82f);
	    glVertex3f (52.41f, 54.14f, 0.80f);
	    glVertex3f (52.41f, 54.08f, 0.79f);
	    glVertex3f (52.41f, 53.78f, 0.79f);
	    glVertex3f (52.41f, 53.78f, 0.81f);
	    glVertex3f (52.41f, 54.07f, 0.81f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	    glVertex3f (52.41f, 53.78f, 0.81f);
	    glVertex3f (52.41f, 53.78f, 0.79f);
	    glVertex3f (52.41f, 53.75f, 0.78f);
	    glVertex3f (52.41f, 53.73f, 0.75f);
	    glVertex3f (52.41f, 53.71f, 0.76f);
	    glVertex3f (52.41f, 53.74f, 0.79f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	    glVertex3f (52.41f, 53.71f, 0.76f);
	    glVertex3f (52.41f, 53.73f, 0.75f);
	    glVertex3f (52.41f, 53.72f, 0.71f);
	    glVertex3f (52.41f, 53.70f, 0.71f);
   glEnd();
	glPopMatrix();
	
	glPopMatrix();
}

void banca(){
	//1.1
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	    glVertex3f (52.46f, 54.35f, 1.30f);
	    glVertex3f (52.46f, 54.33f, 1.29f);
	    glVertex3f (54.11f, 54.33f, 1.29f);
	    glVertex3f (54.11f, 54.35f, 1.30f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	    glVertex3f (52.46f, 54.38f, 1.30f);
	    glVertex3f (52.46f, 54.35f, 1.30f);
	    glVertex3f (54.11f, 54.35f, 1.30f);
	    glVertex3f (54.11f, 54.38f, 1.30f);
   glEnd();
	glPopMatrix();
	//HERE - //cara del lado izquierdo 
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	    glVertex3f (52.46f, 54.38f, 1.30f);
	    glVertex3f (52.41f, 54.38f, 1.30f);
	    glVertex3f (52.41f, 54.35f, 1.30f);
	    glVertex3f (52.46f, 54.35f, 1.30f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	     glVertex3f (52.46f, 54.35f, 1.30f);
	     glVertex3f (52.41f, 54.35f, 1.30f);
	     glVertex3f (52.41f, 54.33f, 1.29f);
	     glVertex3f (52.46f, 54.33f, 1.29f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	     glVertex3f (52.46f, 54.33f, 1.29f);
	     glVertex3f (52.41f, 54.33f, 1.29f);
	     glVertex3f (52.41f, 54.31f, 1.26f);
	     glVertex3f (52.46f, 54.31f, 1.26f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	     glVertex3f (52.46f, 54.31f, 1.26f);
	     glVertex3f (52.41f, 54.31f, 1.26f);
	     glVertex3f (52.41f, 54.22f, 0.89f);
	     glVertex3f (52.46f, 54.22f, 0.89f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	     glVertex3f (52.46f, 54.22f, 0.89f);
	     glVertex3f (52.41f, 54.22f, 0.89f);
	     glVertex3f (52.41f, 54.18f, 0.85f);
	     glVertex3f (52.46f, 54.18f, 0.85f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	     glVertex3f (52.46f, 54.18f, 0.85f);
	     glVertex3f (52.41f, 54.18f, 0.85f);
	     glVertex3f (52.41f, 54.13f, 0.82f);
	     glVertex3f (52.46f, 54.13f, 0.82f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	     glVertex3f (52.46f, 54.13f, 0.82f);
	     glVertex3f (52.41f, 54.13f, 0.82f);
	     glVertex3f (52.41f, 54.07f, 0.81f);
	     glVertex3f (52.46f, 54.07f, 0.81f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	     glVertex3f (52.46f, 54.07f, 0.81f);
	     glVertex3f (52.41f, 54.07f, 0.81f);
	     glVertex3f (52.41f, 53.78f, 0.81f);
	     glVertex3f (52.46f, 53.78f, 0.81f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	     glVertex3f (52.46f, 53.78f, 0.81f);
	     glVertex3f (52.41f, 53.78f, 0.81f);
	     glVertex3f (52.41f, 53.74f, 0.79f);
	     glVertex3f (52.46f, 53.74f, 0.79f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	     glVertex3f (52.46f, 53.74f, 0.79f);
	     glVertex3f (52.41f, 53.74f, 0.79f);
	     glVertex3f (52.41f, 53.71f, 0.76f);
	     glVertex3f (52.41f, 53.70f, 0.71f);
	     glVertex3f (52.46f, 53.70f, 0.71f);
	     glVertex3f (52.46f, 53.71f, 0.76f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	     glVertex3f (52.46f, 53.71f, 0.76f);
	     glVertex3f (52.46f, 53.70f, 0.71f);
	     glVertex3f (54.11f, 53.70f, 0.71f);
	     glVertex3f (54.11f, 53.71f, 0.76f);
   glEnd();
	glPopMatrix();
	//banca part - white 
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.85f, 0.88f, 0.84f, 1.0f);
	     glVertex3f (52.46f, 54.33f, 1.29f);
	     glVertex3f (52.46f, 54.31f, 1.26f);
	     glVertex3f (54.11f, 54.31f, 1.26f);
	     glVertex3f (54.11f, 54.33f, 1.29f);                   
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.85f, 0.88f, 0.84f, 1.0f);
	     glVertex3f (52.46f, 54.31f, 1.26f);
	     glVertex3f (52.46f, 54.22f, 0.89f);
	     glVertex3f (54.11f, 54.22f, 0.89f);
	     glVertex3f (54.11f, 54.31f, 1.26f);                   
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.85f, 0.88f, 0.84f, 1.0f);
	     glVertex3f (52.46f, 54.22f, 0.89f);
	     glVertex3f (52.46f, 54.18f, 0.85f);
	     glVertex3f (52.46f, 54.13f, 0.82f);
	     glVertex3f (54.11f, 54.13f, 0.82f); 
		 glVertex3f (54.11f, 54.18f, 0.85f);
		 glVertex3f (54.11f, 54.22f, 0.89f);                  
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.85f, 0.88f, 0.84f, 1.0f);
	     glVertex3f (52.46f, 54.13f, 0.82f);
	     glVertex3f (52.46f, 54.07f, 0.81f);
	     glVertex3f (52.46f, 53.78f, 0.81f);
	     glVertex3f (54.11f, 53.78f, 0.81f); 
		 glVertex3f (54.11f, 54.07f, 0.81f);
		 glVertex3f (54.11f, 54.13f, 0.82f);                  
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.85f, 0.88f, 0.84f, 1.0f);
	     glVertex3f (52.46f, 53.78f, 0.81f);
	     glVertex3f (52.46f, 53.74f, 0.79f); 
		 glVertex3f (52.46f, 53.71f, 0.76f);
		 glVertex3f (54.11f, 53.71f, 0.76f); 
		 glVertex3f (54.11f, 53.74f, 0.79f);
		 glVertex3f (54.11f, 53.78f, 0.81f);                 
   glEnd();
	glPopMatrix();
	
	//costado de la parte izquierda
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	    glVertex3f (52.41f, 54.38f, 1.30f);
	    glVertex3f (52.41f, 54.38f, 1.28f);
	    glVertex3f (52.41f, 54.36f, 1.28f);
	    glVertex3f (52.41f, 54.35f, 1.30f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	    glVertex3f (52.41f, 54.35f, 1.30f);
	    glVertex3f (52.41f, 54.36f, 1.28f);
	    glVertex3f (52.41f, 54.34f, 1.27f);
	    glVertex3f (52.41f, 54.33f, 1.29f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	    glVertex3f (52.41f, 54.33f, 1.29f);
	    glVertex3f (52.41f, 54.34f, 1.27f);
	    glVertex3f (52.41f, 54.33f, 1.25f);
	    glVertex3f (52.41f, 54.31f, 1.26f);
   glEnd();
	glPopMatrix();	
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	    glVertex3f (52.41f, 54.31f, 1.26f);
	    glVertex3f (52.41f, 54.33f, 1.25f);
	    glVertex3f (52.41f, 54.24f, 0.88f);
	    glVertex3f (52.41f, 54.22f, 0.89f);
   glEnd();
	glPopMatrix();	
	//
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	    glVertex3f (52.41f, 54.22f, 0.89f);
	    glVertex3f (52.41f, 54.24f, 0.88f);
	    glVertex3f (52.41f, 54.19f, 0.83f);
	    glVertex3f (52.41f, 54.14f, 0.80f);
	    glVertex3f (52.41f, 54.13f, 0.82f);
	    glVertex3f (52.41f, 54.18f, 0.85f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	    glVertex3f (52.41f, 54.13f, 0.82f);
	    glVertex3f (52.41f, 54.14f, 0.80f);
	    glVertex3f (52.41f, 54.08f, 0.79f);
	    glVertex3f (52.41f, 53.78f, 0.79f);
	    glVertex3f (52.41f, 53.78f, 0.81f);
	    glVertex3f (52.41f, 54.07f, 0.81f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	    glVertex3f (52.41f, 53.78f, 0.81f);
	    glVertex3f (52.41f, 53.78f, 0.79f);
	    glVertex3f (52.41f, 53.75f, 0.78f);
	    glVertex3f (52.41f, 53.73f, 0.75f);
	    glVertex3f (52.41f, 53.71f, 0.76f);
	    glVertex3f (52.41f, 53.74f, 0.79f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	    glVertex3f (52.41f, 53.71f, 0.76f);
	    glVertex3f (52.41f, 53.73f, 0.75f);
	    glVertex3f (52.41f, 53.72f, 0.71f);
	    glVertex3f (52.41f, 53.70f, 0.71f);
   glEnd();
	glPopMatrix();
	//palo curviado 
	// de lado 
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	     glVertex3f (52.36f, 54.32f, 0.38f);
	     glVertex3f (52.36f, 54.28f, 0.38f);
	     glVertex3f (52.36f, 54.28f, 0.85f);
	     glVertex3f (52.36f, 54.32f, 0.85f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	     glVertex3f (52.36f, 54.32f, 0.85f);
	     glVertex3f (52.36f, 54.28f, 0.85f);
	     glVertex3f (52.36f, 54.27f, 0.88f);
	     glVertex3f (52.36f, 54.25f, 0.92f);
	     glVertex3f (52.36f, 54.28f, 0.94f);
	     glVertex3f (52.36f, 54.31f, 0.90f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	    glVertex3f (52.36f, 54.28f, 0.94f);
	    glVertex3f (52.36f, 54.25f, 0.92f);
	     glVertex3f (52.36f, 54.23f, 0.94f);
	     glVertex3f (52.36f, 54.19f, 0.95f);
	     glVertex3f (52.36f, 54.20f, 0.99f);
	     glVertex3f (52.36f, 54.25f, 0.97f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	    glVertex3f (52.36f, 54.20f, 0.99f);
	    glVertex3f (52.36f, 54.19f, 0.95f);
	     glVertex3f (52.36f, 53.87f, 0.95f);
	     glVertex3f (52.36f, 53.86f, 0.99f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	    glVertex3f (52.36f, 53.86f, 0.99f);
	    glVertex3f (52.36f, 53.87f, 0.95f);
	     glVertex3f (52.36f, 53.83f, 0.94f);
	     glVertex3f (52.36f, 53.80f, 0.91f);
	     glVertex3f (52.36f, 53.77f, 0.93f);
	     glVertex3f (52.36f, 53.81f, 0.97f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	    glVertex3f (52.36f, 53.77f, 0.93f);
	    glVertex3f (52.36f, 53.80f, 0.91f);
	     glVertex3f (52.36f, 53.78f, 0.87f);
	     glVertex3f (52.36f, 53.77f, 0.83f);
	     glVertex3f (52.36f, 53.73f, 0.83f);
	     glVertex3f (52.36f, 53.74f, 0.89f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	    glVertex3f (52.36f, 53.77f, 0.83f);
	    glVertex3f (52.36f, 53.77f, 0.38f);
	     glVertex3f (52.36f, 53.73f, 0.38f);
	     glVertex3f (52.36f, 53.73f, 0.83f);
   glEnd();
	glPopMatrix();
	
	//de frente
		glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	    glVertex3f (52.40f, 54.32f, 0.85f);
	    glVertex3f (52.40f, 54.32f, 0.38f);
	     glVertex3f (52.36f, 54.32f, 0.38f);
	     glVertex3f (52.36f, 54.32f, 0.85f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	    glVertex3f (52.40f, 54.28f, 0.94f);
	    glVertex3f (52.40f, 54.31f, 0.90f);
	     glVertex3f (52.40f, 54.32f, 0.85f);
	     glVertex3f (52.36f, 54.32f, 0.85f);
	     glVertex3f (52.36f, 54.31f, 0.90f);
	     glVertex3f (52.36f, 54.28f, 0.94f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	    glVertex3f (52.40f, 54.20f, 0.99f);
	    glVertex3f (52.40f, 54.25f, 0.97f);
	     glVertex3f (52.40f, 54.28f, 0.94f);
	     glVertex3f (52.36f, 54.28f, 0.94f);
	     glVertex3f (52.36f, 54.25f, 0.97f);
	     glVertex3f (52.36f, 54.20f, 0.99f);
   glEnd();
	glPopMatrix();
		glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	    glVertex3f (52.40f, 54.20f, 0.99f);
	    glVertex3f (52.36f, 54.20f, 0.99f);
	     glVertex3f (52.36f, 53.86f, 0.99f);
	     glVertex3f (52.40f, 53.86f, 0.99f);
   glEnd();
	glPopMatrix();
		glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	    glVertex3f (52.36f, 53.86f, 0.99f);
	    glVertex3f (52.36f, 53.81f, 0.97f);
	     glVertex3f (52.36f, 53.77f, 0.93f);
	     glVertex3f (52.40f, 53.77f, 0.93f);
	     glVertex3f (52.40f, 53.81f, 0.97f);
	     glVertex3f (52.40f, 53.86f, 0.99f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	    glVertex3f (52.36f, 53.77f, 0.93f);
	    glVertex3f (52.36f, 53.74f, 0.89f);
	     glVertex3f (52.36f, 53.73f, 0.83f);
	     glVertex3f (52.40f, 53.73f, 0.83f);
	     glVertex3f (52.40f, 53.74f, 0.89f);
	     glVertex3f (52.40f, 53.77f, 0.93f);
   glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.51f, 0.24f, 0.0f, 1.0f);
	    glVertex3f (52.36f, 53.73f, 0.83f);
	    glVertex3f (52.36f, 53.73f, 0.38f);
	     glVertex3f (52.40f, 53.73f, 0.38f);
	     glVertex3f (52.40f, 53.73f, 0.83f);
   glEnd();
	glPopMatrix();
	
	//DELINEATION 
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	glColor4f (0.0f, 0.0f, 0.0f, 0.0f);
	    glVertex3f (52.41f, 54.38f, 1.30f);
	    glVertex3f (52.41f, 54.35f, 1.30f);
	    glVertex3f (52.41f, 54.33f, 1.29f);
	    glVertex3f (52.41f, 54.31f, 1.26f);
	    glVertex3f (52.41f, 54.22f, 0.89f);
	    glVertex3f (52.41f, 54.18f, 0.85f);
	    glVertex3f (52.41f, 54.13f, 0.82f);
	    glVertex3f (52.41f, 54.07f, 0.81f);
	    glVertex3f (52.41f, 53.78f, 0.81f);
	    glVertex3f (52.41f, 53.74f, 0.79f);
	    glVertex3f (52.41f, 53.71f, 0.76f);
	    glVertex3f (52.41f, 53.70f, 0.71f);
   glEnd();
	glPopMatrix();
	
	
	paloCurviado();
	
	
	
	
}

void asientos(){
	//asientos - Lina
	//espaldar superior
	glPushMatrix();
	glBegin(GL_POLYGON);
		glColor4f(0.05f,0.07f,0.95f,1.8f);
	    glVertex3f (25.4f, 94.0f, 0.9f);    
	    glVertex3f (25.4f, 94.8f, 0.9f); 
	    glVertex3f (25.5f, 94.8f, 0.9f); 
	    glVertex3f (25.5f, 94.0f, 0.9f); 
		glEnd();
	glPopMatrix();
	
	//espaldar delante
	glPushMatrix();
	glBegin(GL_POLYGON);
		glColor4f(0.05f,0.07f,0.95f,1.8f);
	    glVertex3f (25.4f, 94.0f, 0.9f);    
	    glVertex3f (25.4f, 94.8f, 0.9f);
	    glVertex3f (25.4f, 94.8f, 0.8f);
	    glVertex3f (25.4f, 94.0f, 0.8f); 
		glEnd();
	glPopMatrix();
	
	//espaldar derecha
	glPushMatrix();
	glBegin(GL_POLYGON);
		glColor4f(0.05f,0.07f,0.95f,1.8f);
	    glVertex3f (25.4f, 94.0f, 0.8f);    
	    glVertex3f (25.4f, 94.0f, 0.9f); 
	    glVertex3f (25.5f, 94.0f, 0.9f); 
	    glVertex3f (25.5f, 94.0f, 0.8f); 
		glEnd();
	glPopMatrix();
	
	//espaldar izquierda
	glPushMatrix();
	glBegin(GL_POLYGON);
		glColor4f(0.05f,0.07f,0.95f,1.8f);
	    glVertex3f (25.4f, 94.8f, 0.8f);    
	    glVertex3f (25.4f, 94.8f, 0.9f); 
	    glVertex3f (25.5f, 94.8f, 0.9f); 
	    glVertex3f (25.5f, 94.8f, 0.8f); 
		glEnd();
	glPopMatrix();
	
	//espaldar atras
	glPushMatrix();
	glBegin(GL_POLYGON);
		glColor4f(0.0f,0.0f,0.0f,1.0f);
 		glVertex3f (25.5f, 94.8f, 0.9f); 
	    glVertex3f (25.5f, 94.0f, 0.9f);
	    glVertex3f (25.5f, 94.0f, 0.8f); 
	    glVertex3f (25.5f, 94.8f, 0.8f);
		glEnd();
	glPopMatrix();
	
	//tubo-negro
	//bajo
	glPushMatrix();
	glBegin(GL_POLYGON);
		glColor4f(0.0f,0.0f,0.0f,1.0f);
 		glVertex3f (25.5f, 94.5f, 0.85f); 
	    glVertex3f (25.5f, 94.4f, 0.85f);
	    glVertex3f (25.5f, 94.4f, 0.7f); 
	    glVertex3f (25.5f, 94.5f, 0.7f);
		glEnd();
	glPopMatrix();
	
	//superior
	glPushMatrix();
	glBegin(GL_POLYGON);
		glColor4f(0.0f,0.0f,0.0f,1.0f);
 		glVertex3f (25.55f, 94.5f, 0.85f); 
	    glVertex3f (25.55f, 94.4f, 0.85f);
	    glVertex3f (25.55f, 94.4f, 0.7f); 
	    glVertex3f (25.55f, 94.5f, 0.7f);
		glEnd();
	glPopMatrix();
	
	//arriba
	glPushMatrix();
	glBegin(GL_POLYGON);
		glColor4f(0.0f,0.0f,0.0f,1.0f);
	    glVertex3f (25.5f, 94.4f, 0.85f);    
	    glVertex3f (25.5f, 94.5f, 0.85f); 
	    glVertex3f (25.55f, 94.5f, 0.85f); 
	    glVertex3f (25.55f, 94.4f, 0.85f); 
		glEnd();
	glPopMatrix();
	
	//abajo
	glPushMatrix();
	glBegin(GL_POLYGON);
		glColor4f(0.0f,0.0f,0.0f,1.0f);
	    glVertex3f (25.5f, 94.4f, 0.7f);    
	    glVertex3f (25.5f, 94.5f, 0.7f); 
	    glVertex3f (25.55f, 94.5f, 0.7f); 
	    glVertex3f (25.55f, 94.4f, 0.7f); 
		glEnd();
	glPopMatrix();
	
	//izquierda
	glPushMatrix();
	glBegin(GL_POLYGON);
		glColor4f(0.0f,0.0f,0.0f,1.0f);
	    glVertex3f (25.5f, 94.4f, 0.7f);    
	    glVertex3f (25.5f, 94.4f, 0.85f); 
	    glVertex3f (25.55f, 94.4f, 0.85f); 
	    glVertex3f (25.55f, 94.4f, 0.7f); 
		glEnd();
	glPopMatrix();
	
	//derecha
	glPushMatrix();
	glBegin(GL_POLYGON);
		glColor4f(0.0f,0.0f,0.0f,1.0f);
	    glVertex3f (25.5f, 94.5f, 0.7f);
	    glVertex3f (25.5f, 94.5f, 0.85f); 
	    glVertex3f (25.55f, 94.5f, 0.85f); 
	    glVertex3f (25.55f, 94.5f, 0.7f); 
		glEnd();
	glPopMatrix();
	
	//asiento 
	//superior
	glPushMatrix();
	glBegin(GL_POLYGON);
		glColor4f(0.01f,0.019f,0.56f,1.0f);
	    glVertex3f (24.85f, 93.9f, 0.7f);    
	    glVertex3f (24.85f, 94.9f, 0.7f); 
	    glVertex3f (25.55f, 94.9f, 0.7f); 
	    glVertex3f (25.55f, 93.9f, 0.7f); 
		glEnd();
	glPopMatrix();
	
	//inferior
	glPushMatrix();
	glBegin(GL_POLYGON);
		glColor4f(0.01f,0.019f,0.56f,1.0f);
	    glVertex3f (24.85f, 93.9f, 0.65f);    
	    glVertex3f (24.85f, 94.9f, 0.65f); 
	    glVertex3f (25.55f, 94.9f, 0.65f); 
	    glVertex3f (25.55f, 93.9f, 0.65f); 
		glEnd();
	glPopMatrix();
	
	//arriba
	glPushMatrix();
	glBegin(GL_POLYGON);
		glColor4f(0.01f,0.019f,0.56f,1.0f);
	    glVertex3f (24.85f, 94.9f, 0.65f);    
	    glVertex3f (24.85f, 94.9f, 0.7f); 
	    glVertex3f (25.55f, 94.9f, 0.7f); 
	    glVertex3f (25.55f, 94.9f, 0.65f); 
		glEnd();
	glPopMatrix();
	
	//abajo
	glPushMatrix();
	glBegin(GL_POLYGON);
		glColor4f(0.01f,0.019f,0.56f,1.0f);
	    glVertex3f (24.85f, 93.9f, 0.65f);    
	    glVertex3f (24.85f, 93.9f, 0.7f); 
	    glVertex3f (25.55f, 93.9f, 0.7f); 
	    glVertex3f (25.55f, 93.9f, 0.65f); 
		glEnd();
	glPopMatrix();
}

void faro(){
//cubo de abajo 
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.14f, 0.14f, 0.14f, 1.0f);
	    glVertex3f (34.79f, 54.55f, 0.83f);
	    glVertex3f (34.79f, 54.55f, 0.27f);
	    glVertex3f (35.24f, 54.55f, 0.27f);
	    glVertex3f (35.24f, 54.55f, 0.83f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.14f, 0.14f, 0.14f, 1.0f);
	    glVertex3f (35.24f, 54.55f, 0.83f);
	    glVertex3f (35.24f, 54.55f, 0.27f);
	    glVertex3f (35.24f, 55.01f, 0.27f);
	    glVertex3f (35.24f, 55.01f, 0.83f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.14f, 0.14f, 0.14f, 1.0f);
	    glVertex3f (35.24f, 55.01f, 0.83f);
	    glVertex3f (35.24f, 55.01f, 0.27f);
	    glVertex3f (34.79f, 55.01f, 0.27f);
	    glVertex3f (34.79f, 55.01f, 0.83f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.14f, 0.14f, 0.14f, 1.0f);
	    glVertex3f (34.79f, 55.01f, 0.83f);
	    glVertex3f (34.79f, 55.01f, 0.27f);
	    glVertex3f (34.79f, 54.55f, 0.27f);
	    glVertex3f (34.79f, 54.55f, 0.83f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.14f, 0.14f, 0.14f, 1.0f);
	    glVertex3f (34.79f, 54.55f, 0.83f);
	    glVertex3f (35.24f, 54.55f, 0.83f);
	    glVertex3f (35.24f, 55.01f, 0.83f);
	    glVertex3f (34.79f, 55.01f, 0.83f);
   glEnd();
	glPopMatrix();
	//DELINEATION on
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glColor4f (0.0f, 0.0f, 0.0f, 0.0f);
	    glVertex3f (34.79f, 54.55f, 0.83f);
	    glVertex3f (35.24f, 54.55f, 0.83f);
	    glVertex3f (35.24f, 55.01f, 0.83f);
	    glVertex3f (34.79f, 55.01f, 0.83f);
   glEnd();
	glPopMatrix();
	
	//palo
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.14f, 0.14f, 0.14f, 1.0f);
	    glVertex3f (35.09f, 54.86f, 0.83f);
	    glVertex3f (34.94f, 54.86f, 0.83f);
	    glVertex3f (34.94f, 54.86f, 7.54f);
	    glVertex3f (35.09f, 54.86f, 7.54f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.14f, 0.14f, 0.14f, 1.0f);
	    glVertex3f (36.16f, 54.86f, 7.38f);
	    glVertex3f (33.87f, 54.86f, 7.38f);
	    glVertex3f (33.87f, 54.86f, 7.54f);
	    glVertex3f (36.16f, 54.86f, 7.54f);
   glEnd();
	glPopMatrix();
	//DELINEATION
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glColor4f (0.0f, 0.0f, 0.0f, 0.0f);
	    glVertex3f (36.16f, 54.86f, 7.38f);
	    glVertex3f (33.87f, 54.86f, 7.38f);
	    glVertex3f (33.87f, 54.86f, 7.54f);
	    glVertex3f (36.16f, 54.86f, 7.54f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.14f, 0.14f, 0.14f, 1.0f);
	    glVertex3f (36.16f, 54.86f, 7.54f);
	    glVertex3f (33.87f, 54.86f, 7.54f);
	    glVertex3f (33.87f, 54.71f, 7.54f);
	    glVertex3f (36.16f, 54.71f, 7.54f);
   glEnd();
	glPopMatrix();
	//DELINEATION
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glColor4f (0.0f, 0.0f, 0.0f, 0.0f);
	    glVertex3f (36.16f, 54.86f, 7.54f);
	    glVertex3f (33.87f, 54.86f, 7.54f);
	    glVertex3f (33.87f, 54.71f, 7.54f);
	    glVertex3f (36.16f, 54.71f, 7.54f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.14f, 0.14f, 0.14f, 1.0f);
	    glVertex3f (36.16f, 54.71f, 7.38f);
	    glVertex3f (36.16f, 54.86f, 7.38f);
	    glVertex3f (36.16f, 54.86f, 7.54f);
	    glVertex3f (36.16f, 54.71f, 7.54f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.14f, 0.14f, 0.14f, 1.0f);
	    glVertex3f (33.87f, 54.86f, 7.38f);
	    glVertex3f (33.87f, 54.71f, 7.38f);
	    glVertex3f (33.87f, 54.71f, 7.54f);
	    glVertex3f (33.87f, 54.86f, 7.54f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.14f, 0.14f, 0.14f, 1.0f);
	    glVertex3f (33.87f, 54.71f, 7.38f);
	    glVertex3f (33.87f, 54.71f, 7.54f);
	    glVertex3f (36.16f, 54.71f, 7.54f);
	    glVertex3f (36.16f, 54.71f, 7.38f);
   glEnd();
	glPopMatrix();
	//DELINEATION
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glColor4f (0.0f, 0.0f, 0.0f, 0.0f);
	    glVertex3f (33.87f, 54.71f, 7.38f);
	    glVertex3f (33.87f, 54.71f, 7.54f);
	    glVertex3f (36.16f, 54.71f, 7.54f);
	    glVertex3f (36.16f, 54.71f, 7.38f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.14f, 0.14f, 0.14f, 1.0f);
	    glVertex3f (34.94f, 54.71f, 7.54f);
	    glVertex3f (35.09f, 54.71f, 7.54f);
	    glVertex3f (35.09f, 54.71f, 0.83f);
	    glVertex3f (34.94f, 54.71f, 0.83f);
   glEnd();
	glPopMatrix();
	//side right 
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.14f, 0.14f, 0.14f, 1.0f);
	    glVertex3f (34.94f, 54.86f, 0.83f);
	    glVertex3f (34.94f, 54.71f, 0.83f);
	    glVertex3f (34.94f, 54.71f, 7.38f);
	    glVertex3f (34.94f, 54.86f, 7.38f);
   glEnd();
	glPopMatrix();
	//DELINEATION
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glColor4f (0.0f, 0.0f, 0.0f, 0.0f);
	    glVertex3f (34.94f, 54.86f, 0.83f);
	    glVertex3f (34.94f, 54.71f, 0.83f);
	    glVertex3f (34.94f, 54.71f, 7.38f);
	    glVertex3f (34.94f, 54.86f, 7.38f);
   glEnd();
	glPopMatrix();
	//side left  
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.14f, 0.14f, 0.14f, 1.0f);
	    glVertex3f (35.09f, 54.71f, 7.38f);
	    glVertex3f (35.09f, 54.86f, 7.38f);
	    glVertex3f (35.09f, 54.86f, 0.83f);
	    glVertex3f (35.09f, 54.71f, 0.83f);
   glEnd();
	glPopMatrix();
	//DELINEATION
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glColor4f (0.0f, 0.0f, 0.0f, 0.0f);
	    glVertex3f (35.09f, 54.71f, 7.38f);
	    glVertex3f (35.09f, 54.86f, 7.38f);
	    glVertex3f (35.09f, 54.86f, 0.83f);
	    glVertex3f (35.09f, 54.71f, 0.83f);
   glEnd();
	glPopMatrix();
	
	//ILUMINATION LEFT 
		glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.14f, 0.14f, 0.14f, 1.0f);
	    glVertex3f (33.57f, 54.48f, 7.38f);
	    glVertex3f (33.57f, 54.48f, 7.0f);
	    glVertex3f (34.18f, 54.48f, 7.0f);
	    glVertex3f (34.18f, 54.48f, 7.38f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.14f, 0.14f, 0.14f, 1.0f);
	    glVertex3f (33.57f, 55.09f, 7.38f);
	    glVertex3f (33.57f, 55.09f, 7.0f);
	    glVertex3f (33.57f, 54.48f, 7.0f);
	    glVertex3f (33.57f, 54.48f, 7.38f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.14f, 0.14f, 0.14f, 1.0f);
	    glVertex3f (34.18f, 55.09f, 7.38f);
	    glVertex3f (34.18f, 55.09f, 7.0f);
	    glVertex3f (33.57f, 55.09f, 7.0f);
	    glVertex3f (33.57f, 55.09f, 7.38f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.14f, 0.14f, 0.14f, 1.0f);
	    glVertex3f (34.18f, 54.48f, 7.38f);
	    glVertex3f (34.18f, 54.48f, 7.0f);
	    glVertex3f (34.18f, 55.09f, 7.0f);
	    glVertex3f (34.18f, 55.09f, 7.38f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.14f, 0.14f, 0.14f, 1.0f);
	    glVertex3f (34.18f, 54.48f, 7.38f);
	    glVertex3f (33.57f, 54.48f, 7.38f);
	    glVertex3f (33.57f, 55.09f, 7.38f);
	    glVertex3f (34.18f, 55.09f, 7.38f);
   glEnd();
	glPopMatrix();
	//DELINEATION
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glColor4f (0.0f, 0.0f, 0.0f, 0.0f);
	    glVertex3f (34.18f, 54.48f, 7.38f);
	    glVertex3f (33.57f, 54.48f, 7.38f);
	    glVertex3f (33.57f, 55.09f, 7.38f);
	    glVertex3f (34.18f, 55.09f, 7.38f);
   glEnd();
	glPopMatrix();
	//ILUMINATION RIGHT 
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.14f, 0.14f, 0.14f, 1.0f);
	    glVertex3f (35.85f, 54.48f, 7.38f);
	    glVertex3f (35.85f, 54.48f, 7.00f);
	    glVertex3f (36.46f, 54.48f, 7.00f);
	    glVertex3f (36.46f, 54.48f, 7.38f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.14f, 0.14f, 0.14f, 1.0f);
	    glVertex3f (36.46f, 54.48f, 7.38f);
	    glVertex3f (36.46f, 54.48f, 7.00f);
	    glVertex3f (36.46f, 55.09f, 7.00f);
	    glVertex3f (36.46f, 55.09f, 7.38f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.14f, 0.14f, 0.14f, 1.0f);
	    glVertex3f (36.46f, 55.09f, 7.38f);
	    glVertex3f (36.46f, 55.09f, 7.00f);
	    glVertex3f (35.85f, 55.09f, 7.00f);
	    glVertex3f (35.85f, 55.09f, 7.38f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.14f, 0.14f, 0.14f, 1.0f);
	    glVertex3f (35.85f, 55.09f, 7.38f);
	    glVertex3f (35.85f, 54.48f, 7.38f);
	    glVertex3f (36.46f, 54.48f, 7.38f);
	    glVertex3f (36.46f, 55.09f, 7.38f);
   glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.14f, 0.14f, 0.14f, 1.0f);
	    glVertex3f (35.85f, 55.09f, 7.38f);
	    glVertex3f (35.85f, 55.09f, 7.00f);
	    glVertex3f (35.85f, 54.48f, 7.00f);
	    glVertex3f (35.85f, 54.48f, 7.38f);
   glEnd();
	glPopMatrix();
	
	//deliniation 
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glColor4f (0.0f, 0.0f, 0.0f, 0.0f);
	    glVertex3f (35.85f, 55.09f, 7.38f);
	    glVertex3f (35.85f, 54.48f, 7.38f);
	    glVertex3f (36.46f, 54.48f, 7.38f);
	    glVertex3f (36.46f, 55.09f, 7.38f);
   glEnd();
	glPopMatrix();
}

void translateDeFaros(){
	 //translate de faros
   glPushMatrix();
	glTranslatef(16.3f, -1.0f, 0.0f);
	faro();
	glPopMatrix();
	//
	glPushMatrix();
	glTranslatef(16.0f, -9.0f, 0.0f);
	faro();
	glPopMatrix();
	//
	glPushMatrix();
	glTranslatef(-16.0f, -9.0f, 0.0f);
	faro();
	glPopMatrix();
	//
	glPushMatrix();
	glTranslatef(-16.3f, -1.0f, 0.0f);
	faro();
	glPopMatrix();
}

void translateDeBancas(){
	glPushMatrix();
	glTranslatef(0.0f, -8.3f, 0.0f);
	banca();
	glPopMatrix();
	//
	glPushMatrix();
	glTranslatef(-4.0f, -8.3f, 0.0f);
	banca();
	glPopMatrix();
	//
	glPushMatrix();
	glTranslatef(-32.5f, -8.5f, 0.0f);
	banca();
	glPopMatrix();
	//
	glPushMatrix();
	glTranslatef(-36.0f, -8.5f, 0.0f);
	banca();
	glPopMatrix();
	//
	glPushMatrix();
	glTranslatef(-36.0f, -0.5f, 0.0f);
	banca();
	glPopMatrix();
}

void wall(){
	glPushMatrix();
	glBegin(GL_QUADS);
	//glColor4f (0.78f, 0.76f, 0.75f, 1.0f);
	glColor4f (0.9f, 0.9f, 0.9f, 1.0f);
	    glVertex3f (0.0f, 20.05f, 0.38f); 
		glVertex3f (0.0f, 20.05f, 0.0f);
		glVertex3f (18.11f, 20.05f, 0.0f);   
		glVertex3f (18.11f, 20.05f, 0.38f);
	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.9f, 0.9f, 0.9f, 1.0f);
	    glVertex3f (19.29f, 19.82f, 0.38f); 
		glVertex3f (19.29f, 19.82f, 0.0f);
		glVertex3f (18.11f, 20.05f, 0.0f);   
		glVertex3f (18.11f, 20.05f, 0.38f); 
	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.9f, 0.9f, 0.9f, 1.0f);
	    glVertex3f (20.38f, 19.31f, 0.38f); 
		glVertex3f (20.38f, 19.31f, 0.0f);
		glVertex3f (19.29f, 19.82f, 0.0f);   
		glVertex3f (19.29f, 19.82f, 0.38f); 
	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.9f, 0.9f, 0.9f, 1.0f);
	    glVertex3f (21.30f, 18.54f, 0.38f); 
		glVertex3f (21.30f, 18.54f, 0.0f);
		glVertex3f (20.38f, 19.31f, 0.0f);   
		glVertex3f (20.38f, 19.31f, 0.38f); 
	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.9f, 0.9f, 0.9f, 1.0f);
	    glVertex3f (22.01f, 17.57f, 0.38f); 
		glVertex3f (22.01f, 17.57f, 0.0f);
		glVertex3f (21.30f, 18.54f, 0.0f);   
		glVertex3f (21.30f, 18.54f, 0.38f); 
	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.9f, 0.9f, 0.9f, 1.0f);
	    glVertex3f (22.45f, 16.46f, 0.38f); 
		glVertex3f (22.45f, 16.46f, 0.0f);
		glVertex3f (22.01f, 17.57f, 0.0f);   
		glVertex3f (22.01f, 17.57f, 0.38f); 
	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.9f, 0.9f, 0.9f, 1.0f);
	    glVertex3f (22.60f, 15.27f, 0.38f); 
		glVertex3f (22.60f, 15.27f, 0.0f);
		glVertex3f (22.45f, 16.46f, 0.0f);   
		glVertex3f (22.45f, 16.46f, 0.38f); 
	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.9f, 0.9f, 0.9f, 1.0f);
	    glVertex3f (22.45f, 14.08f, 0.38f); 
		glVertex3f (22.45f, 14.08f, 0.0f);
		glVertex3f (22.60f, 15.27f, 0.0f);   
		glVertex3f (22.60f, 15.27f, 0.38f); 
	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.9f, 0.9f, 0.9f, 1.0f);
	    glVertex3f (22.01f, 12.96f, 0.38f); 
		glVertex3f (22.01f, 12.96f, 0.0f);
		glVertex3f (22.45f, 14.08f, 0.0f);   
		glVertex3f (22.45f, 14.08f, 0.38f);  
	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.9f, 0.9f, 0.9f, 1.0f);
	    glVertex3f (21.30f, 11.99f, 0.38f); 
		glVertex3f (21.30f, 11.99f, 0.0f);
		glVertex3f (22.01f, 12.96f, 0.0f);   
		glVertex3f (22.01f, 12.96f, 0.38f);  
	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.9f, 0.9f, 0.9f, 1.0f);
	    glVertex3f (20.38f, 11.23f, 0.38f); 
		glVertex3f (20.38f, 11.23f, 0.0f);
		glVertex3f (21.30f, 11.99f, 0.0f);   
		glVertex3f (21.30f, 11.99f, 0.38f);  
	glEnd();
	glPopMatrix();
	//
		glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.9f, 0.9f, 0.9f, 1.0f);
	    glVertex3f (19.29f, 10.72f, 0.38f); 
		glVertex3f (19.29f, 10.72f, 0.0f);
		glVertex3f (20.38f, 11.23f, 0.0f);   
		glVertex3f (20.38f, 11.23f, 0.38f);  
	glEnd();
	glPopMatrix();
	//
		glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.9f, 0.9f, 0.9f, 1.0f);
	    glVertex3f (18.11f, 10.49f, 0.38f); 
		glVertex3f (18.11f, 10.49f, 0.0f);
		glVertex3f (19.29f, 10.72f, 0.0f);   
		glVertex3f (19.29f, 10.72f, 0.38f);  
	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.9f, 0.9f, 0.9f, 1.0f);
	    glVertex3f (18.11f, 10.49f, 0.38f); 
		glVertex3f (18.11f, 10.49f, 0.0f);
		glVertex3f (0.0f, 10.49f, 0.0f);   
		glVertex3f (0.0f, 10.49f, 0.38f);  
	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.9f, 0.9f, 0.9f, 1.0f);
	    glVertex3f (0.0f, 20.05f, 0.38f); 
		glVertex3f (18.11f, 20.05f, 0.38f); 
		glVertex3f (19.29f, 19.82f, 0.38f); 
		glVertex3f (20.38f, 19.31f, 0.38f); 
		glVertex3f (21.30f, 18.54f, 0.38f); 
		glVertex3f (22.01f, 17.57f, 0.38f); 
		glVertex3f (22.45f, 16.46f, 0.38f); 
		glVertex3f (22.60f, 15.27f, 0.38f); 
		glVertex3f (22.45f, 14.08f, 0.38f); 
		glVertex3f (22.01f, 12.96f, 0.38f); 
		glVertex3f (21.30f, 11.99f, 0.38f); 
		glVertex3f (20.38f, 11.23f, 0.38f); 
		glVertex3f (19.29f, 10.72f, 0.38f); 
		glVertex3f (18.11f, 10.49f, 0.38f); 
		glVertex3f (0.0f, 10.49f, 0.38f); 
	glEnd();
	glPopMatrix();
		//DELINEATION
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glColor4f (0.0f, 0.0f, 0.0f, 0.0f);
	    glVertex3f (0.0f, 20.05f, 0.38f); 
		glVertex3f (18.11f, 20.05f, 0.38f); 
		glVertex3f (19.29f, 19.82f, 0.38f); 
		glVertex3f (20.38f, 19.31f, 0.38f); 
		glVertex3f (21.30f, 18.54f, 0.38f); 
		glVertex3f (22.01f, 17.57f, 0.38f); 
		glVertex3f (22.45f, 16.46f, 0.38f); 
		glVertex3f (22.60f, 15.27f, 0.38f); 
		glVertex3f (22.45f, 14.08f, 0.38f); 
		glVertex3f (22.01f, 12.96f, 0.38f); 
		glVertex3f (21.30f, 11.99f, 0.38f); 
		glVertex3f (20.38f, 11.23f, 0.38f); 
		glVertex3f (19.29f, 10.72f, 0.38f); 
		glVertex3f (18.11f, 10.49f, 0.38f); 
		glVertex3f (0.0f, 10.49f, 0.38f); 
	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.9f, 0.9f, 0.9f, 1.0f);
	    glVertex3f (0.0f, 20.05f, 0.38f); 
		glVertex3f (0.0f, 20.05f, 0.0f); 
		glVertex3f (0.0f, 10.49f, 0.0f);   
		glVertex3f (0.0f, 10.49f, 0.49f);  
	glEnd();
	glPopMatrix();
	//DELINEATION
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	glColor4f (0.0f, 0.0f, 0.0f, 0.0f);
	    glVertex3f (0.0f, 20.05f, 0.38f); 
		glVertex3f (0.0f, 20.05f, 0.0f); 
		glVertex3f (0.0f, 10.49f, 0.0f);   
		glVertex3f (0.0f, 10.49f, 0.49f);  
	glEnd();
	glPopMatrix();
	//GRASS
		glPushMatrix();
	glBegin(GL_POLYGON);
	glColor4f (0.29f, 0.43f, 0.2f, 1.0f);
	    glVertex3f (0.0f, 18.95f, 0.63f); 
		glVertex3f (11.66f, 18.95f, 0.63f);
		glVertex3f (12.60f, 18.77f, 0.63f); 
		glVertex3f (13.44f, 18.38f, 0.63f);   
		glVertex3f (14.15f, 17.79f, 0.63f);
		glVertex3f (14.69f, 17.04f, 0.63f);
		glVertex3f (15.03f, 16.18f, 0.63f);
		glVertex3f (15.15f, 15.27f, 0.63f);
		glVertex3f (15.03f, 14.35f, 0.63f);
		glVertex3f (14.69f, 13.49f, 0.63f);
		glVertex3f (14.15f, 12.75f, 0.63f);
		glVertex3f (13.44f, 12.16f, 0.63f);
		glVertex3f (12.60f, 11.77f, 0.63f);
		glVertex3f (11.66f, 11.59f, 0.63f);
		glVertex3f (0.0f, 11.59f, 0.63f);	  
	glEnd();
	glPopMatrix();
	//PIEDRA WALL
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.66f, 0.64f, 0.5f, 1.0f);
	    glVertex3f (11.71f, 19.46f, 1.57f); 
		glVertex3f (11.71f, 19.46f, 0.38f); 
		glVertex3f (0.0f, 19.46f, 0.38f);   
		glVertex3f (0.0f, 19.46f, 1.57f);  
	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.66f, 0.64f, 0.5f, 1.0f);
	    glVertex3f (12.76f, 19.26f, 1.57f); 
	    glVertex3f (12.76f, 19.26f, 0.38f);  
	    glVertex3f (11.71f, 19.46f, 0.38f);
	    glVertex3f (11.71f, 19.46f, 1.57f);   
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.66f, 0.64f, 0.5f, 1.0f);
	    glVertex3f (13.71f, 18.81f, 1.57f); 
	    glVertex3f (13.71f, 18.81f, 0.38f);  
	    glVertex3f (12.76f, 19.26f, 0.38f);
	    glVertex3f (12.76f, 19.26f, 1.57f);   
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.66f, 0.64f, 0.5f, 1.0f);
	    glVertex3f (14.52f, 18.14f, 1.57f); 
	    glVertex3f (14.52f, 18.14f, 0.38f);  
	    glVertex3f (13.71f, 18.81f, 0.38f);
	    glVertex3f (13.71f, 18.81f, 1.57f);   
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.66f, 0.64f, 0.5f, 1.0f);
	    glVertex3f (15.14f, 17.29f, 1.57f); 
	    glVertex3f (15.14f, 17.29f, 0.38f);  
	    glVertex3f (14.52f, 18.14f, 0.38f);
	    glVertex3f (14.52f, 18.14f, 1.57f);   
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.66f, 0.64f, 0.5f, 1.0f);
	    glVertex3f (15.52f, 16.31f, 1.57f); 
	    glVertex3f (15.52f, 16.31f, 0.38f);  
	    glVertex3f (15.14f, 17.29f, 0.38f);
	    glVertex3f (15.14f, 17.29f, 1.57f);   
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.66f, 0.64f, 0.5f, 1.0f);
	    glVertex3f (15.66f, 15.27f, 1.57f); 
	    glVertex3f (15.66f, 15.27f, 0.38f);  
	    glVertex3f (15.52f, 16.31f, 0.38f);
	    glVertex3f (15.52f, 16.31f, 1.57f);   
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.66f, 0.64f, 0.5f, 1.0f);
	    glVertex3f (15.52f, 14.23f, 1.57f); 
	    glVertex3f (15.52f, 14.23f, 0.38f);  
	    glVertex3f (15.66f, 15.27f, 0.38f);
	    glVertex3f (15.66f, 15.27f, 1.57f);   
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.66f, 0.64f, 0.5f, 1.0f);
	    glVertex3f (15.14f, 13.25f, 1.57f); 
	    glVertex3f (15.14f, 13.25f, 0.38f);  
	    glVertex3f (15.52f, 14.23f, 0.38f);
	    glVertex3f (15.52f, 14.23f, 1.57f);   
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.66f, 0.64f, 0.5f, 1.0f);
	    glVertex3f (14.52f, 12.40f, 1.57f); 
	    glVertex3f (14.52f, 12.40f, 0.38f);  
	    glVertex3f (15.14f, 13.25f, 0.38f);
	    glVertex3f (15.14f, 13.25f, 1.57f);   
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.66f, 0.64f, 0.5f, 1.0f);
	    glVertex3f (13.71f, 11.73f, 1.57f); 
	    glVertex3f (13.71f, 11.73f, 0.38f);  
	    glVertex3f (14.52f, 12.40f, 0.38f);
	    glVertex3f (14.52f, 12.40f, 1.57f);   
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.66f, 0.64f, 0.5f, 1.0f);
	    glVertex3f (12.76f, 11.28f, 1.57f); 
	    glVertex3f (12.76f, 11.28f, 0.38f);  
	    glVertex3f (13.71f, 11.73f, 0.38f);
	    glVertex3f (13.71f, 11.73f, 1.57f);   
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.66f, 0.64f, 0.5f, 1.0f);
	    glVertex3f (11.71f, 11.08f, 1.57f); 
	    glVertex3f (11.71f, 11.08f, 0.38f);  
	    glVertex3f (12.76f, 11.28f, 0.38f);
	    glVertex3f (12.76f, 11.28f, 1.57f);   
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.66f, 0.64f, 0.5f, 1.0f);
	    glVertex3f (0.0f, 11.08f, 1.57f); 
	    glVertex3f (0.0f, 11.08f, 0.38f);  
	    glVertex3f (11.71f, 11.08f, 0.38f);
	    glVertex3f (11.71f, 11.08f, 1.57f);   
	glEnd();
	glPopMatrix();
	//PART OF UP 
	 glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.66f, 0.64f, 0.5f, 1.0f);
	    glVertex3f (0.0f, 11.59f, 1.57f); 
	    glVertex3f (0.0f, 11.08f, 1.57f);  
	    glVertex3f (11.71f, 11.08f, 1.57f);
	    glVertex3f (11.66f, 11.59f, 1.57f);   
	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.66f, 0.64f, 0.5f, 1.0f);
	    glVertex3f (11.66f, 11.59f, 1.57f); 
	    glVertex3f (11.71f, 11.08f, 1.57f);  
	    glVertex3f (12.76f, 11.28f, 1.57f);
	    glVertex3f (12.60f, 11.77f, 1.57f);   
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.66f, 0.64f, 0.5f, 1.0f);
	    glVertex3f (12.60f, 11.77f, 1.57f);  
	    glVertex3f (12.76f, 11.28f, 1.57f);  
	    glVertex3f (13.71f, 11.73f, 1.57f);
	    glVertex3f (13.44f, 12.16f, 1.57f);   
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.66f, 0.64f, 0.5f, 1.0f);
	    glVertex3f (13.44f, 12.16f, 1.57f);  
	    glVertex3f (13.71f, 11.73f, 1.57f);  
	    glVertex3f (14.52f, 12.40f, 1.57f);
	    glVertex3f (14.15f, 12.75f, 1.57f);   
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.66f, 0.64f, 0.5f, 1.0f);
	    glVertex3f (14.15f, 12.75f, 1.57f);   
	    glVertex3f (14.52f, 12.40f, 1.57f);  
	    glVertex3f (15.14f, 13.25f, 1.57f);
	    glVertex3f (14.69f, 13.49f, 1.57f);   
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.66f, 0.64f, 0.5f, 1.0f);
	    glVertex3f (14.69f, 13.49f, 1.57f);    
	    glVertex3f (15.14f, 13.25f, 1.57f);  
	    glVertex3f (15.52f, 14.23f, 1.57f);
	    glVertex3f (15.03f, 14.35f, 1.57f);   
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.66f, 0.64f, 0.5f, 1.0f);
	    glVertex3f (15.03f, 14.35f, 1.57f);    
	    glVertex3f (15.52f, 14.23f, 1.57f);  
	    glVertex3f (15.66f, 15.27f, 1.57f);
	    glVertex3f (15.15f, 15.27f, 1.57f);   
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.66f, 0.64f, 0.5f, 1.0f);
	    glVertex3f (15.15f, 15.27f, 1.57f);     
	    glVertex3f (15.66f, 15.27f, 1.57f); 
	    glVertex3f (15.52f, 16.31f, 1.57f);
	    glVertex3f (15.03f, 16.18f, 1.57f);   
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.66f, 0.64f, 0.5f, 1.0f);
	    glVertex3f (15.03f, 16.18f, 1.57f);    
	    glVertex3f (15.52f, 16.31f, 1.57f); 
	    glVertex3f (15.14f, 17.29f, 1.57f);
	    glVertex3f (14.69f, 17.04f, 1.57f);   
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.66f, 0.64f, 0.5f, 1.0f);
	    glVertex3f (14.69f, 17.04f, 1.57f);     
	    glVertex3f (15.14f, 17.29f, 1.57f);
	    glVertex3f (14.52f, 18.14f, 1.57f);
	    glVertex3f (14.15f, 17.79f, 1.57f);   
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.66f, 0.64f, 0.5f, 1.0f);
	    glVertex3f (14.15f, 17.79f, 1.57f);     
	    glVertex3f (14.52f, 18.14f, 1.57f);
	    glVertex3f (13.71f, 18.81f, 1.57f);
	    glVertex3f (13.44f, 18.38f, 1.57f);   
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.66f, 0.64f, 0.5f, 1.0f);
	    glVertex3f (13.44f, 18.38f, 1.57f);      
	    glVertex3f (13.71f, 18.81f, 1.57f);
	    glVertex3f (12.76f, 19.26f, 1.57f);
	    glVertex3f (12.60f, 18.77f, 1.57f);   
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.66f, 0.64f, 0.5f, 1.0f);
	    glVertex3f (12.60f, 18.77f, 1.57f);     
	    glVertex3f (12.76f, 19.26f, 1.57f);
	    glVertex3f (11.71f, 19.46f, 1.57f);
	    glVertex3f (11.66f, 18.95f, 1.57f);   
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.66f, 0.64f, 0.5f, 1.0f);
	    glVertex3f (11.66f, 18.95f, 1.57f);     
	    glVertex3f (11.71f, 19.46f, 1.57f);
	    glVertex3f (0.0f, 19.46f, 1.57f);
	    glVertex3f (0.0f, 18.95f, 1.57f);   
	glEnd();
	glPopMatrix();
	//DELINEATION
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	glColor4f (0.0f, 0.0f, 0.0f, 0.0f);
	    glVertex3f (0.0f, 19.46f, 1.57f);     
	    glVertex3f (11.71f, 19.46f, 1.57f);
	    glVertex3f (12.76f, 19.26f, 1.57f);
	    glVertex3f (13.71f, 18.81f, 1.57f);
		glVertex3f (14.52f, 18.14f, 1.57f);
		glVertex3f (15.14f, 17.29f, 1.57f);
		glVertex3f (15.52f, 16.31f, 1.57f); 
		glVertex3f (15.66f, 15.27f, 1.57f); 
		glVertex3f (15.52f, 14.23f, 1.57f); 
		glVertex3f (15.14f, 13.25f, 1.57f);  
		glVertex3f (14.52f, 12.40f, 1.57f); 
		glVertex3f (13.71f, 11.73f, 1.57f);
		glVertex3f (12.76f, 11.28f, 1.57f);  
		glVertex3f (11.71f, 11.08f, 1.57f);  
		glVertex3f (0.0f, 11.08f, 1.57f);     
	glEnd();
	glPopMatrix();
	//PART OF INSIDE 
	 glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.66f, 0.64f, 0.5f, 1.0f);
	    glVertex3f (0.0f, 18.95f, 1.57f); 
	    glVertex3f (0.0f, 18.95f, 0.63f);  
	    glVertex3f (11.66f, 18.95f, 0.63f);
	    glVertex3f (11.66f, 18.95f, 1.57f);   
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.66f, 0.64f, 0.5f, 1.0f);
	    glVertex3f (11.66f, 18.95f, 1.57f); 
	    glVertex3f (11.66f, 18.95f, 0.63f);  
	    glVertex3f (12.60f, 18.77f, 0.63f);
	    glVertex3f (12.60f, 18.77f, 1.57f);   
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.66f, 0.64f, 0.5f, 1.0f);
	    glVertex3f (12.60f, 18.77f, 1.57f);   
	    glVertex3f (12.60f, 18.77f, 0.63f); 
	    glVertex3f (13.44f, 18.38f, 0.63f);
	    glVertex3f (13.44f, 18.38f, 1.57f);   
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.66f, 0.64f, 0.5f, 1.0f);
	    glVertex3f (13.44f, 18.38f, 1.57f);    
	    glVertex3f (13.44f, 18.38f, 0.63f);
	    glVertex3f (14.15f, 17.79f, 0.63f);
	    glVertex3f (14.15f, 17.79f, 1.57f);   
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.66f, 0.64f, 0.5f, 1.0f);
	    glVertex3f (14.15f, 17.79f, 1.57f);    
	    glVertex3f (14.15f, 17.79f, 0.63f);
	    glVertex3f (14.69f, 17.04f, 0.63f);
	    glVertex3f (14.69f, 17.04f, 1.57f);   
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.66f, 0.64f, 0.5f, 1.0f);
	    glVertex3f (14.69f, 17.04f, 1.57f);    
	    glVertex3f (14.69f, 17.04f, 0.63f);
	    glVertex3f (15.03f, 16.18f, 0.63f);
	    glVertex3f (15.03f, 16.18f, 1.57f);   
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.66f, 0.64f, 0.5f, 1.0f);
	    glVertex3f (15.03f, 16.18f, 1.57f);    
	    glVertex3f (15.03f, 16.18f, 0.63f);
	    glVertex3f (15.15f, 15.27f, 0.63f);
	    glVertex3f (15.15f, 15.27f, 1.57f);   
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.66f, 0.64f, 0.5f, 1.0f);
	    glVertex3f (15.15f, 15.27f, 1.57f);    
	    glVertex3f (15.15f, 15.27f, 0.63f);
	    glVertex3f (15.03f, 14.35f, 0.63f);
	    glVertex3f (15.03f, 14.35f, 1.57f);   
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.66f, 0.64f, 0.5f, 1.0f);
	    glVertex3f (15.03f, 14.35f, 1.57f);    
	    glVertex3f (15.03f, 14.35f, 0.63f);
	    glVertex3f (14.69f, 13.49f, 0.63f);
	    glVertex3f (14.69f, 13.49f, 1.57f);   
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.66f, 0.64f, 0.5f, 1.0f);
	    glVertex3f (14.69f, 13.49f, 1.57f);    
	    glVertex3f (14.69f, 13.49f, 0.63f);
	    glVertex3f (14.15f, 12.75f, 0.63f);
	    glVertex3f (14.15f, 12.75f, 1.57f);   
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.66f, 0.64f, 0.5f, 1.0f);
	    glVertex3f (14.15f, 12.75f, 1.57f);     
	    glVertex3f (14.15f, 12.75f, 0.63f);
	    glVertex3f (13.44f, 12.16f, 0.63f);
	    glVertex3f (13.44f, 12.16f, 1.57f);   
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.66f, 0.64f, 0.5f, 1.0f);
	    glVertex3f (13.44f, 12.16f, 1.57f);     
	    glVertex3f (13.44f, 12.16f, 0.63f);
	    glVertex3f (12.60f, 11.77f, 0.63f);
	    glVertex3f (12.60f, 11.77f, 1.57f);   
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.66f, 0.64f, 0.5f, 1.0f);
	    glVertex3f (12.60f, 11.77f, 1.57f);      
	    glVertex3f (12.60f, 11.77f, 0.63f);
	    glVertex3f (11.66f, 11.59f, 0.63f);
	    glVertex3f (11.66f, 11.59f, 1.57f);   
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.66f, 0.64f, 0.5f, 1.0f);
	    glVertex3f (11.66f, 11.59f, 1.57f);       
	    glVertex3f (11.66f, 11.59f, 0.63f);
	    glVertex3f (0.0f, 11.59f, 0.63f);
	    glVertex3f (0.0f, 11.59f, 1.57f);   
	glEnd();
	glPopMatrix();
	//DELINEATION
		glPushMatrix();
	glBegin(GL_LINE_STRIP);
	glColor4f (0.0f, 0.0f, 0.0f, 0.0f);
	    glVertex3f (0.0f, 11.59f, 1.57f); 
		glVertex3f (11.66f, 11.59f, 1.57f); 
		glVertex3f (12.60f, 11.77f, 1.57f);
		glVertex3f (13.44f, 12.16f, 1.57f); 
		glVertex3f (14.15f, 12.75f, 1.57f); 
		glVertex3f (14.69f, 13.49f, 1.57f); 
		glVertex3f (15.03f, 14.35f, 1.57f); 
		glVertex3f (15.15f, 15.27f, 1.57f); 
		glVertex3f (15.03f, 16.18f, 1.57f); 
	    glVertex3f (14.69f, 17.04f, 1.57f); 
		glVertex3f (14.15f, 17.79f, 1.57f); 
		glVertex3f (13.44f, 18.38f, 1.57f);  
		glVertex3f (12.60f, 18.77f, 1.57f); 
		glVertex3f (11.66f, 18.95f, 1.57f); 
		glVertex3f (0.0f, 18.95f, 1.57f);    
	glEnd();
	glPopMatrix();
}

void downWall(){
		glPushMatrix();
	glBegin(GL_QUADS);
	//glColor4f (0.78f, 0.76f, 0.75f, 1.0f);
	glColor4f (0.9f, 0.9f, 0.9f, 1.0f);
	    glVertex3f (68.97f, -9.22f, 0.49f); 
		glVertex3f (68.97f, -9.22f, 0.0f); 
		glVertex3f (0.0f, -9.22f, 0.0f);   
		glVertex3f (0.0f, -9.22f, 0.49f);  
	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.9f, 0.9f, 0.9f, 1.0f);
	    glVertex3f (0.0f, -9.22f, 0.49f); 
		glVertex3f (0.0f, -9.22f, 0.0f); 
		glVertex3f (0.0f, -22.19f, 0.0f);   
		glVertex3f (0.0f, -22.19f, 0.49f);  
	glEnd();
	glPopMatrix();
	//DELINEATION
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	glColor4f (0.0f, 0.0f, 0.0f, 0.0f);
	    glVertex3f (0.0f, -9.22f, 0.49f); 
		glVertex3f (0.0f, -9.22f, 0.0f); 
		glVertex3f (0.0f, -22.19f, 0.0f);   
		glVertex3f (0.0f, -22.19f, 0.49f);  
	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.9f, 0.9f, 0.9f, 1.0f);
	    glVertex3f (68.97f, -9.22f, 0.49f); 
		glVertex3f (68.97f, -22.19f, 0.49f); 
		glVertex3f (0.0f, -22.19f, 0.49f);   
		glVertex3f (0.0f, -9.22f, 0.49f);  
	glEnd();
	glPopMatrix();
	//DELINEATION
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glColor4f (0.0f, 0.0f, 0.0f, 0.0f);
	    glVertex3f (68.97f, -9.22f, 0.49f); 
		glVertex3f (68.97f, -22.19f, 0.49f); 
		glVertex3f (0.0f, -22.19f, 0.49f);   
		glVertex3f (0.0f, -9.22f, 0.49f);  
	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.9f, 0.9f, 0.9f, 1.0f);
	    glVertex3f (0.0f, -22.19f, 0.49f); 
		glVertex3f (0.0f, -22.19f, 0.0f); 
		glVertex3f (68.97f, -22.19f, 0.0f);   
		glVertex3f (68.97f, -22.19f, 0.49f);  
	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.9f, 0.9f, 0.9f, 1.0f);
	    glVertex3f (68.97f, -22.19f, 0.49f); 
		glVertex3f (68.97f, -22.19f, 0.0f); 
		glVertex3f (68.97f, -9.22f, 0.0f);   
		glVertex3f (68.97f, -9.22f, 0.49f);  
	glEnd();
	glPopMatrix();
	//DELINEATION
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	glColor4f (0.0f, 0.0f, 0.0f, 0.0f);
	    glVertex3f (68.97f, -22.19f, 0.49f); 
		glVertex3f (68.97f, -22.19f, 0.0f); 
		glVertex3f (68.97f, -9.22f, 0.0f);   
		glVertex3f (68.97f, -9.22f, 0.49f);  
	glEnd();
	glPopMatrix();
}

void road(){
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.8f, 0.8f, 0.8f, 1.0f);
	    glVertex3f (0.0f, 40.14f, 0.0f); 
		glVertex3f (0.0f, -9.22f, 0.0f);
		glVertex3f (68.97f, -9.22f, 0.0f);   
		glVertex3f (68.97f, 40.14f, 0.0f);
	glEnd();
	glPopMatrix();
}

void whiteLines(){
	//left 
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (1.0f, 1.0f, 1.0f, 1.0f);
	    glVertex3f (21.46f, 38.83f, 0.0f); 
		glVertex3f (21.46f, 38.19f, 0.0f);
		glVertex3f (15.01f, 38.19f, 0.0f);   
		glVertex3f (15.01f, 38.83f, 0.0f);
	glEnd();
	glPopMatrix();
	//left-down 
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (1.0f, 1.0f, 1.0f, 1.0f);
	    glVertex3f (15.01f, 9.24f, 0.0f); 
		glVertex3f (15.01f, 8.60f, 0.0f);
		glVertex3f (21.46f, 8.60f, 0.0f);   
		glVertex3f (21.46f, 9.24f, 0.0f);
	glEnd();
	glPopMatrix();
	//right 
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (1.0f, 1.0f, 1.0f, 1.0f);
	    glVertex3f (48.57f, 38.80f, 0.0f); 
		glVertex3f (48.57f, 38.16f, 0.0f);
		glVertex3f (55.02f, 38.16f, 0.0f);   
		glVertex3f (55.02f, 38.80f, 0.0f);
	glEnd();
	glPopMatrix();
	//right-down 
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (1.0f, 1.0f, 1.0f, 1.0f);
	    glVertex3f (48.57f, 9.24f, 0.0f); 
		glVertex3f (48.57f, 8.60f, 0.0f);
		glVertex3f (55.02f, 8.60f, 0.0f);   
		glVertex3f (55.02f, 9.24f, 0.0f);
	glEnd();
	glPopMatrix();
   //delineation 
  glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glColor4f (0.0f, 0.0f, 0.0f, 0.0f);
	    glVertex3f (21.46f, 38.83f, 0.0f); 
		glVertex3f (21.46f, 38.19f, 0.0f);
		glVertex3f (15.01f, 38.19f, 0.0f);   
		glVertex3f (15.01f, 38.83f, 0.0f);
	glEnd();
	glPopMatrix();
	//
		glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glColor4f (0.0f, 0.0f, 0.0f, 0.0f);
	    glVertex3f (15.01f, 9.24f, 0.0f); 
		glVertex3f (15.01f, 8.60f, 0.0f);
		glVertex3f (21.46f, 8.60f, 0.0f);   
		glVertex3f (21.46f, 9.24f, 0.0f);
	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glColor4f (0.0f, 0.0f, 0.0f, 0.0f);
	    glVertex3f (48.57f, 38.80f, 0.0f); 
		glVertex3f (48.57f, 38.16f, 0.0f);
		glVertex3f (55.02f, 38.16f, 0.0f);   
		glVertex3f (55.02f, 38.80f, 0.0f);
	glEnd();
	glPopMatrix();
	//
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glColor4f (0.0f, 0.0f, 0.0f, 0.0f);
	    glVertex3f (48.57f, 9.24f, 0.0f); 
		glVertex3f (48.57f, 8.60f, 0.0f);
		glVertex3f (55.02f, 8.60f, 0.0f);   
		glVertex3f (55.02f, 9.24f, 0.0f);
	glEnd();
	glPopMatrix();
}

void linesTranslate(){
	//translate de lineas
	//second line
   glPushMatrix();
	glTranslatef(0.0f, -1.5f, 0.0f);
	whiteLines();
	glPopMatrix();
	//third line
	glPushMatrix();
	glTranslatef(0.0f, -3.0f, 0.0f);
	whiteLines();
	glPopMatrix();
	//quarter line
	glPushMatrix();
	glTranslatef(0.0f, -4.5f, 0.0f);
	whiteLines();
	glPopMatrix();
	//fifth line
	glPushMatrix();
	glTranslatef(0.0f, -6.0f, 0.0f);
	whiteLines();
	glPopMatrix();
	//6st line
	glPushMatrix();
	glTranslatef(0.0f, -7.5f, 0.0f);
	whiteLines();
	glPopMatrix();
	//7 line
	glPushMatrix();
	glTranslatef(0.0f, -9.0f, 0.0f);
	whiteLines();
	glPopMatrix();
	//8 line
	glPushMatrix();
	glTranslatef(0.0f, -10.5f, 0.0f);
	whiteLines();
	glPopMatrix();
	//9 line
	glPushMatrix();
	glTranslatef(0.0f, -12.0f, 0.0f);
	whiteLines();
	glPopMatrix();
	//10 line
	glPushMatrix();
	glTranslatef(0.0f, -13.5f, 0.0f);
	whiteLines();
	glPopMatrix();
	//11 line
	glPushMatrix();
	glTranslatef(0.0f, -15.0f, 0.0f);
	whiteLines();
	glPopMatrix();
	//12 line
	glPushMatrix();
	glTranslatef(0.0f, -16.5f, 0.0f);
	whiteLines();
	glPopMatrix();
	
	//YELLOW LINES - UP LEFT 
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.96f, 0.81f, 0.0f, 1.0f);
	    glVertex3f (3.74f, 30.06f, 0.0f); 
		glVertex3f (3.74f, 29.43f, 0.0f);
		glVertex3f (11.33f, 29.43f, 0.0f);   
		glVertex3f (11.33f, 30.06f, 0.0f);
	glEnd();
	glPopMatrix();
	//DELINEATION
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glColor4f (0.0f, 0.0f, 0.0f, 0.0f);
	    glVertex3f (3.74f, 30.06f, 0.0f); 
		glVertex3f (3.74f, 29.43f, 0.0f);
		glVertex3f (11.33f, 29.43f, 0.0f);   
		glVertex3f (11.33f, 30.06f, 0.0f);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	//YELLOW LINES - UP RIGHT 
	glPushMatrix();
	glTranslatef(54.5f, 0.0f, 0.0f);
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.96f, 0.81f, 0.0f, 1.0f);
	    glVertex3f (3.74f, 30.06f, 0.0f); 
		glVertex3f (3.74f, 29.43f, 0.0f);
		glVertex3f (11.33f, 29.43f, 0.0f);   
		glVertex3f (11.33f, 30.06f, 0.0f);
	glEnd();
	glPopMatrix();
	//DELINEATION
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glColor4f (0.0f, 0.0f, 0.0f, 0.0f);
	    glVertex3f (3.74f, 30.06f, 0.0f); 
		glVertex3f (3.74f, 29.43f, 0.0f);
		glVertex3f (11.33f, 29.43f, 0.0f);   
		glVertex3f (11.33f, 30.06f, 0.0f);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	//YELLOW LINES - DOWN LEFT 
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.96f, 0.81f, 0.0f, 1.0f);
	    glVertex3f (3.74f, 0.31f, 0.0f); 
		glVertex3f (3.74f, -0.32f, 0.0f);
		glVertex3f (11.33f, -0.32f, 0.0f);   
		glVertex3f (11.33f, 0.31f, 0.0f);
	glEnd();
	glPopMatrix();
	//DELINEATION
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glColor4f (0.0f, 0.0f, 0.0f, 0.0f);
	    glVertex3f (3.74f, 0.31f, 0.0f); 
		glVertex3f (3.74f, -0.32f, 0.0f);
		glVertex3f (11.33f, -0.32f, 0.0f);   
		glVertex3f (11.33f, 0.31f, 0.0f);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	//YELLOW LINES - DOWN right
	glPushMatrix();
	glTranslatef(54.5f, 0.0f, 0.0f);
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor4f (0.96f, 0.81f, 0.0f, 1.0f);
	    glVertex3f (3.74f, 0.31f, 0.0f); 
		glVertex3f (3.74f, -0.32f, 0.0f);
		glVertex3f (11.33f, -0.32f, 0.0f);   
		glVertex3f (11.33f, 0.31f, 0.0f);
	glEnd();
	glPopMatrix();
	//DELINEATION
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glColor4f (0.0f, 0.0f, 0.0f, 0.0f);
	    glVertex3f (3.74f, 0.31f, 0.0f); 
		glVertex3f (3.74f, -0.32f, 0.0f);
		glVertex3f (11.33f, -0.32f, 0.0f);   
		glVertex3f (11.33f, 0.31f, 0.0f);
	glEnd();
	glPopMatrix();
	glPopMatrix();
}


//------------------------------------------------------------------------------------------------------------------------------------------------
//=========================================CASA 2==========================================================
void cochera(){
	//pared blanca
	glBegin(GL_QUADS);

    glColor3f( 1.0 , 1.0 ,1.0 );//blanco
    glVertex3f(60, 76, 20);
    glVertex3f(36, 76, 20);
    glVertex3f(36, 76, 0.1);
    glVertex3f(60, 76, 0.1);
    
    glVertex3f(60, 70, 20);
    glVertex3f(36, 70, 20);
    glVertex3f(36, 70, 0.1);
    glVertex3f(60, 70, 0.1);
    
    glVertex3f(60, 70, 0.1);
    glVertex3f(60, 76, 0.1);
    glVertex3f(60, 76, 20);
    glVertex3f(60, 70, 20);
    
    glVertex3f(36, 70, 0.1);
    glVertex3f(36, 76, 0.1);
    glVertex3f(36, 76, 20);
    glVertex3f(36, 70, 20);
    
    glVertex3f(60, 70, 20);
    glVertex3f(60, 76, 20);
    glVertex3f(36, 76, 20);
    glVertex3f(36, 70, 20);
    //================================COLUMNAS CHICAS
    glColor3f( 0.066 , 0.054 , 0.137 );
    glVertex3f(58, 74, 20);
    glVertex3f(58, 74, 25);
    glVertex3f(56, 74, 25);
    glVertex3f(56, 74, 20);
    
    glVertex3f(58, 74, 20);
    glVertex3f(58, 74, 25);
    glVertex3f(58, 72, 25);
    glVertex3f(58, 72, 20);
    
    glVertex3f(58, 72, 20);
    glVertex3f(58, 72, 25);
    glVertex3f(56, 72, 25);
    glVertex3f(56, 72, 20);
    
    glVertex3f(56, 74, 20);
    glVertex3f(56, 74, 25);
    glVertex3f(56, 72, 25);
    glVertex3f(56, 72, 20);
    
    glVertex3f(58, 72, 25);
    glVertex3f(56, 72, 25);
    glVertex3f(56, 74, 25);
    glVertex3f(58, 74, 25);
    //2
    glVertex3f(40, 74, 20);
    glVertex3f(40, 74, 25);
    glVertex3f(38, 74, 25);
    glVertex3f(38, 74, 20);
    
    glVertex3f(40, 74, 20);
    glVertex3f(40, 74, 25);
    glVertex3f(40, 72, 25);
    glVertex3f(40, 72, 20);
    
    glVertex3f(40, 72, 20);
    glVertex3f(40, 72, 25);
    glVertex3f(38, 72, 25);
    glVertex3f(38, 72, 20);
    
    glVertex3f(38, 74, 20);
    glVertex3f(38, 74, 25);
    glVertex3f(38, 72, 25);
    glVertex3f(38, 72, 20);
    
    glVertex3f(40, 72, 25);
    glVertex3f(38, 72, 25);
    glVertex3f(38, 74, 25);
    glVertex3f(40, 74, 25);
    
    //===================================VIGAS
    //delantera
    glVertex3f(58, 74, 25);
    glVertex3f(58, 74, 23);
    glVertex3f(58, 122, 23);
    glVertex3f(58, 122, 25);
    
    glVertex3f(58, 74, 25);
    glVertex3f(56, 74, 25);
    glVertex3f(56, 122, 25);
    glVertex3f(58, 122, 25);
    
    glVertex3f(58, 74, 23);
    glVertex3f(56, 74, 23);
    glVertex3f(56, 122, 23);
    glVertex3f(58, 122, 23);
    
    glVertex3f(56, 74, 25);
    glVertex3f(56, 74, 23);
    glVertex3f(56, 122, 23);
    glVertex3f(56, 122, 25);
    //trasera
    glVertex3f(40, 74, 25);
    glVertex3f(40, 74, 23);
    glVertex3f(40, 120, 23);
    glVertex3f(40, 120, 25);
    
    glVertex3f(40, 74, 25);
    glVertex3f(38, 74, 25);
    glVertex3f(38, 122, 25);
    glVertex3f(40, 122, 25);
    
    glVertex3f(40, 74, 23);
    glVertex3f(38, 74, 23);
    glVertex3f(38, 122, 23);
    glVertex3f(40, 122, 23);
    
    glVertex3f(38, 74, 25);
    glVertex3f(38, 74, 23);
    glVertex3f(38, 120, 23);
    glVertex3f(38, 120, 25);
    //costado der
    glVertex3f(58, 122, 25);
    glVertex3f(38, 122, 25);
    glVertex3f(38, 120, 25);
    glVertex3f(58, 120, 25);
    
    glVertex3f(58, 122, 23);
    glVertex3f(38, 122, 23);
    glVertex3f(38, 120, 23);
    glVertex3f(58, 120, 23);
    
    glVertex3f(58, 122, 25);
    glVertex3f(38, 122, 25);
    glVertex3f(38, 122, 23);
    glVertex3f(58, 122, 23);
    
    glVertex3f(58, 120, 25);
    glVertex3f(38, 120, 25);
    glVertex3f(38, 120, 23);
    glVertex3f(58, 120, 23);
    //costado iz
    glVertex3f(58, 74, 25);
    glVertex3f(38, 74, 25);
    glVertex3f(38, 72, 25);
    glVertex3f(58, 72, 25);
    
    glVertex3f(58, 74, 23);
    glVertex3f(38, 74, 23);
    glVertex3f(38, 72, 23);
    glVertex3f(58, 72, 23);
    
    glVertex3f(58, 74, 25);
    glVertex3f(38, 74, 25);
    glVertex3f(38, 74, 23);
    glVertex3f(58, 74, 23);
    
    glVertex3f(58, 72, 25);
    glVertex3f(38, 72, 25);
    glVertex3f(38, 72, 23);
    glVertex3f(58, 72, 23);
    
    //=====================================COLUMNAS
    glVertex3f(58, 122, 0.1);
    glVertex3f(58, 122, 23);
    glVertex3f(56, 122, 23);
    glVertex3f(56, 122, 0.1);
    
    glVertex3f(58, 120, 0.1);
    glVertex3f(58, 120, 23);
    glVertex3f(56, 120, 23);
    glVertex3f(56, 120, 0.1);
    
    glVertex3f(58, 122, 0.1);
    glVertex3f(58, 122, 23);
    glVertex3f(58, 120, 23);
    glVertex3f(58, 120, 0.1);
    
    glVertex3f(56, 122, 0.1);
    glVertex3f(56, 122, 23);
    glVertex3f(56, 120, 23);
    glVertex3f(56, 120, 0.1);
    
    //ATRAS
    glVertex3f(40, 122, 0.1);
    glVertex3f(40, 122, 23);
    glVertex3f(38, 122, 23);
    glVertex3f(38, 122, 0.1);
    
    glVertex3f(40, 120, 0.1);
    glVertex3f(40, 120, 23);
    glVertex3f(38, 120, 23);
    glVertex3f(38, 120, 0.1);
    
    glVertex3f(40, 122, 0.1);
    glVertex3f(40, 122, 23);
    glVertex3f(40, 120, 23);
    glVertex3f(40, 120, 0.1);
    
    glVertex3f(38, 122, 0.1);
    glVertex3f(38, 122, 23);
    glVertex3f(38, 120, 23);
    glVertex3f(38, 120, 0.1);
    //====================================TECHO COCHERA
    glColor3f( 0.733 , 0.650 , 0.545 );
    glVertex3f(56, 74, 25);
    glVertex3f(56, 120, 25);
    glVertex3f(40, 120, 25);
    glVertex3f(40, 74, 25);
    
    glVertex3f(56, 74, 23);
    glVertex3f(56, 120, 23);
    glVertex3f(40, 120, 23);
    glVertex3f(40, 74, 23);
    //-------------------------techo entrada
    
    
    glVertex3f(28, 96, 25);
    glVertex3f(38, 96, 25);
    glVertex3f(38, 96, 23);
    glVertex3f(28, 96, 23);
    //==========================================PISO
    glColor3f( 0.780 , 0.635 , 0.458 );//blanco
    glVertex3f(64, 76, 0.3);
    glVertex3f(64, 122, 0.3);
    glVertex3f(33, 122, 0.3);
    glVertex3f(33, 76, 0.3);
    
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f( 0.733 , 0.650 , 0.545 );
	glVertex3f(38, 122, 23);
    glVertex3f(24, 122, 23);
    glVertex3f(24, 106, 23);
    glVertex3f(28, 106, 23);
    glVertex3f(28, 96, 23);
    glVertex3f(38, 96, 23);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f( 0.733 , 0.650 , 0.545 );
	glVertex3f(38, 122, 25);
    glVertex3f(24, 122, 25);
    glVertex3f(24, 106, 25);
    glVertex3f(28, 106,  25);
    glVertex3f(28, 96, 25);
    glVertex3f(38, 96, 25);
	glEnd();
}
void cuartoa(){
	//===================================paredes 
	glBegin(GL_QUADS);
	glColor3f( 0.227 , 0.231 , 0.309 );
	glVertex3f(28, 106, 0.2);
    glVertex3f(28, 106, 40);
    glVertex3f(28, 76, 40);
    glVertex3f(28, 76, 0.2);
    
    glVertex3f(28, 76, 40);
    glVertex3f(28, 76, 0.2);
    glVertex3f(-10, 76, 0.2);
    glVertex3f(-10, 76, 40);
    
    glVertex3f(-10, 106, 0.2);
    glVertex3f(-10, 106, 40);
    glVertex3f(-10, 76, 40);
    glVertex3f(-10, 76, 0.2);
    
    glVertex3f(28, 76, 40);
    glVertex3f(28, 106, 40);
    glVertex3f(-10, 106, 40);
    glVertex3f(-10, 76, 40);
	glEnd();
	
	glBegin(GL_QUADS);
	glColor3f( 0.227 , 0.231 , 0.309 );
	glVertex3f(28, 106, 40);
    glVertex3f(18, 106, 40);
    glVertex3f(18, 106, 0.2);
    glVertex3f(28, 106, 0.2);

	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f( 0.227 , 0.231 , 0.309 );
	glVertex3f(0, 106, 35);
    glVertex3f(18, 106, 35);
    glVertex3f(18, 106, 40);
    glVertex3f(-10, 106, 40);
    glVertex3f(-10, 106, 0.2);
    glVertex3f(0, 106, 0.2);
	glEnd();

}
void cuartob(){
	glBegin(GL_QUADS);
	
    glColor3f( 0.454 , 0.454 , 0.501 );//plomo
    glVertex3f(24, 172, 30);
    glVertex3f(24, 172, 35);
    glVertex3f(0, 172, 35);
    glVertex3f(0, 172, 30);
    
    glColor3f( 1.0 , 1.0 ,1.0 );//blanco
	glVertex3f(24, 122, 30);
    glVertex3f(24, 122, 35);
    glVertex3f(24, 172, 35);
    glVertex3f(24, 172, 30);
    
    glVertex3f(0, 172, 30);
    glVertex3f(0, 172, 35);
    glVertex3f(0, 106, 35);
    glVertex3f(0, 106, 30);
    
    glVertex3f(0, 106, 35);
    glVertex3f(24, 106, 35);
    glVertex3f(24, 172, 35);
    glVertex3f(0, 172, 35);
    
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f( 1.0 , 1.0 ,1.0 );//blanco
	glVertex3f(24, 116, 18);
    glVertex3f(24, 116, 0.2);
    glVertex3f(24, 122, 0.2);
    glVertex3f(24, 122, 35);
    glVertex3f(24, 106, 35);
    glVertex3f(24, 106, 18);
	glEnd();
}
void cuartoc(){
	glBegin(GL_QUADS);
	//------------------------pared
	//costado puerta principal
	glColor3f( 0.454 , 0.454 , 0.501 );//plomo
	glVertex3f(38, 122, 30);
    glVertex3f(38, 122, 0.2);
    glVertex3f(24, 122, 0.2);
    glVertex3f(24, 122, 30);
    //costado
    glColor3f( 0.454 , 0.454 , 0.501 );//plomo
	glVertex3f(-15, 172, 30);
    glVertex3f(-15, 172, 0.2);
    glVertex3f(38, 172, 0.2);
    glVertex3f(38, 172, 30);
    
    glColor3f( 0.454 , 0.454 , 0.501 );//plomo
    glVertex3f(0, 122, 30);
    glVertex3f(0, 122, 0.2);
    glVertex3f(-15, 122, 0.2);
    glVertex3f(-15, 122, 30);
    glColor3f( 1.0 , 1.0 ,1.0 );//blanco
    glVertex3f(-15, 172, 0.1);
    glVertex3f(-15, 172, 30);
    glVertex3f(-15, 122, 30);
    glVertex3f(-15, 122, 0.1);
    //------------------------techo
    glVertex3f(38, 122, 30);
    glVertex3f(24, 122, 30);
    glVertex3f(24, 172, 30);
    glVertex3f(38, 172, 30);
    
    glVertex3f(0, 122, 30);
    glVertex3f(-15, 122, 30);
    glVertex3f(-15, 172, 30);
    glVertex3f(0, 172, 30);
    
    //-------------------------puerta
    glColor3f( 0.690 , 0.298 ,  0.0  );
    glVertex3f(24, 106, 0.2);
    glVertex3f(24, 106, 18);
    glVertex3f(24, 116, 18);
    glVertex3f(24, 116, 0.2);
    
    //-------------------------ventana
    glColor3f( 0.607 , 0.886 ,  1.0 );//celeste
    glVertex3f(38, 136, 5);
    glVertex3f(38, 136, 22);
    glVertex3f(38, 163, 22);
    glVertex3f(38, 163, 5);
    
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3f( 1.0 , 1.0 ,1.0 );//blanco
    //-----------------------pared alfrente
    glVertex3f(38, 136, 5);
    glVertex3f(38, 172, 5);
    glVertex3f(38, 172, 0.2);
    glVertex3f(38, 122, 0.2);
    glVertex3f(38, 122, 30);
    glVertex3f(38, 136, 30);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 1.0 , 1.0 ,1.0 );//blanco
    //-----------------------pared alfrente
    glVertex3f(38, 163, 22);
    glVertex3f(38, 163, 5);
    glVertex3f(38, 172, 5);
    glVertex3f(38, 172, 30);
    glVertex3f(38, 136, 30);
    glVertex3f(38, 136, 22);
	glEnd();
	
}
void pasto2(){
	glBegin(GL_POLYGON);
	//===========================PASTO ENTRADA A LA CASA
	glColor3f( 0.247 , 0.305 , 0.152 );
	glVertex3f(28, 106,  0.3);
    glVertex3f(28, 76,  0.3);
    glVertex3f(33, 76, 0.3);
    glVertex3f(33, 122,   0.3);
    glVertex3f(24, 122,   0.3);
    glVertex3f(24, 106,    0.3);
    glEnd();
    glBegin(GL_POLYGON);
	////costado de casa
	glColor3f( 0.247 , 0.305 , 0.152 );
	glVertex3f(36, 70, 0.1);
    glVertex3f(60, 70, 0.1);
    glVertex3f(60, 67, 0.1);
    glVertex3f(-10, 67, 0.1);
    glVertex3f(-10, 76, 0.1);
    glVertex3f(36, 76, 0.1);
    glEnd();
    glBegin(GL_QUADS);
    //ventana pasto
    
    
	glVertex3f(64, 122, 0.3);
    glVertex3f(64, 185, 0.3);
    glVertex3f(38, 185,  0.3);
    glVertex3f(38, 122,  0.3);
    
    
    ////costado de casa
    glVertex3f(60, 76, 0.1);
    glVertex3f(64, 76, 0.1);
    glVertex3f(64, 67, 0.1);
    glVertex3f(60, 67, 0.1);
    glEnd();
}
void pisocasa(){
	glBegin(GL_QUADS);
	glColor3f( 0.733 , 0.619 , 0.494 );
	glVertex3f(38, 122, 0.2);
    glVertex3f(38, 172, 0.2);
    glVertex3f(-15, 172, 0.2);
    glVertex3f(-15, 122, 0.2);
    
    glVertex3f(28, 76, 0.2);
    glVertex3f(28, 106, 0.2);
    glVertex3f(-10, 106,  0.2);
    glVertex3f(-10, 76, 0.2);
    
    glVertex3f(24, 106,  0.2);
    glVertex3f(24, 122, 0.2);
    glVertex3f(-10, 122,  0.2);
    glVertex3f(-10, 106,  0.2);
    
	glEnd();
}
void zona_descanso(){
	//lineas zona descanso escalera
	glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-15, 165, 30);
    glVertex3f(-15, 158, 30);
    glVertex3f(-24, 158, 30);
    glVertex3f(-24, 165, 30);
    glEnd();
	glBegin(GL_QUADS);
	//paso zona de descanso 2do piso
	glColor3f( 0.313 , 0.203 , 0.192 );
	
	glVertex3f(-15, 165, 30);
    glVertex3f(-15, 158, 30);
    glVertex3f(-24, 158, 30);
    glVertex3f(-24, 165, 30);
    //pared marron grande
	glColor3f( 0.780 , 0.490 , 0.250 );
	glVertex3f(-50, 172, 0.1);
    glVertex3f(-15, 172, 0.1);
    glVertex3f(-15, 172, 40);
    glVertex3f(-50, 172, 40);
    
    glVertex3f(-50, 165, -2);
    glVertex3f(-15, 165, -2);
    glVertex3f(-15, 165, 40);
    glVertex3f(-50, 165, 40);
    
    glVertex3f(-50, 172, 0.1);
    glVertex3f(-50, 165, 0.1);
    glVertex3f(-50, 165, 40);
    glVertex3f(-50, 172, 40);
    
    glVertex3f(-15.2, 172, 0.1);
    glVertex3f(-15.2, 165, 0.1);
    glVertex3f(-15.2, 165, 40);
    glVertex3f(-15.2, 172, 40);
    
    glColor3f( 1.0 , 1.0 , 1.0 );
    //pared parte dentro
    glVertex3f(-15, 165, -2);
    glVertex3f(-15, 122,-2);
    glVertex3f(-15, 122, 0.1);
    glVertex3f(-15, 165, 0.1);
    
    glVertex3f(-15, 122, 0.1);
    glVertex3f(-15, 122, -2);
    glVertex3f(-42, 122, -2);
    glVertex3f(-42, 122, 0.1);
    //piso
    glColor3f( 0.807 , 0.556 , 0.317 );
    glVertex3f(-50, 165, -2);
    glVertex3f(-15, 165, -2);
    glVertex3f(-15, 122, -2);
    glVertex3f(-50, 122, -2);
    //escalera
    glColor3f( 0.341 , 0.278 , 0.235 );//marron OSCURO
    glVertex3f(-42, 126, 0.2);
    glVertex3f(-42, 122, 0.2);
    glVertex3f(-50, 122, 0.2);
    glVertex3f(-50, 126, 0.2);
    
    glVertex3f(-42, 126, 0.2);
    glVertex3f(-50, 126, 0.2);
    glVertex3f(-50, 126, -1);
    glVertex3f(-42, 126, -1);
    
    glVertex3f(-50, 126, -1);
    glVertex3f(-42, 126, -1);
    glVertex3f(-42, 130, -1);
    glVertex3f(-50, 130, -1);
    
    glVertex3f(-42, 130, -1);
    glVertex3f(-50, 130, -1);
    glVertex3f(-50, 130, -2);
    glVertex3f(-42, 130, -2);
    
	glEnd();
}
void escalera_patio(){
	glBegin(GL_QUADS);
	glColor3f( 0.313 , 0.203 , 0.192 );
	glVertex3f(-24, 122, 0.7);
    glVertex3f(-15, 122, 0.7);
    glVertex3f(-15, 118, 0.7);
    glVertex3f(-24, 118, 0.7);
    
    glVertex3f(-24, 122, 1.1);
    glVertex3f(-15, 122, 1.1);
    glVertex3f(-15, 118, 1.1);
    glVertex3f(-24, 118, 1.1);
    
    glVertex3f(-15, 122, 0.7);
    glVertex3f(-15, 122, 1.1);
    glVertex3f(-24, 122, 1.1);
    glVertex3f(-24, 122, 0.7);
    
    glVertex3f(-15, 118, 0.7);
    glVertex3f(-15, 118, 1.1);
    glVertex3f(-24, 118, 1.1);
    glVertex3f(-24, 118, 0.7);
    
    glVertex3f(-24, 122,  0.7);
    glVertex3f(-24, 122,  1.1);
    glVertex3f(-24, 118,  1.1);
    glVertex3f(-24, 118,  0.7);
	glEnd();
	glLineWidth(2);
    //mesa de centro
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-24, 122, 1.1);
    glVertex3f(-15.1, 122, 1.1);
    glVertex3f(-15.1, 118, 1.1);
    glVertex3f(-24, 118, 1.1);
    glEnd();
}
void piso_piscina2(){
	//piso general abajo
	glBegin(GL_POLYGON);
	glColor3f( 0.341 , 0.278 , 0.235 );//marron OSCURO
	glVertex3f(-20, 106, 0.2);
    glVertex3f(-20, 67, 0.2);
    glVertex3f(-10, 67, 0.2);
    glVertex3f(-10, 122, 0.2);
    glVertex3f(-50, 122, 0.2);
    glVertex3f(-50, 106,  0.2);
	glEnd();
	//piso general encima
	glBegin(GL_POLYGON);
	glColor3f( 0.341 , 0.278 , 0.235 );//marron OSCURO
	glVertex3f(-20, 106, 0.7);
    glVertex3f(-20, 67, 0.7);
    glVertex3f(-10, 67, 0.7);
    glVertex3f(-10, 122, 0.7);
    glVertex3f(-50, 122, 0.7);
    glVertex3f(-50, 106,  0.7);
	glEnd();
	//costados
	glBegin(GL_QUADS);
	glColor3f( 0.341 , 0.278 , 0.235 );//marron OSCURO
	//entrada
	glVertex3f(-10, 122, 0.2);
    glVertex3f(-10, 106,  0.2);
    glVertex3f(-10, 106,  0.7);
    glVertex3f(-10, 122, 0.7);
    
    glVertex3f(-15, 122,  0.2);
    glVertex3f(-50, 122,   0.2);
    glVertex3f(-50, 122,   0.7);
    glVertex3f(-15, 122, 0.7);
    
    glVertex3f(-10, 67,  0.2);
    glVertex3f(-20, 67,   0.2);
    glVertex3f(-20, 67,   0.7);
    glVertex3f(-10, 67, 0.7);
    
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f( 0.341 , 0.278 , 0.235 );//marron OSCURO
	glVertex3f(-20, 106, 0.2);
    glVertex3f(-20, 67,  0.2);
    glVertex3f(-20, 67,  0.7);
    glVertex3f(-20, 106, 0.7);
    glVertex3f(-50, 106, 0.7);
    glVertex3f(-50, 106,  0.2);
	glEnd();
}
void piscina2(){
	glBegin(GL_QUADS);
	//agua
	glColor3f( 0.121 , 0.788 , 0.823 );//CIAN CLARO
	glVertex3f(-20, 67, 0.2);
    glVertex3f(-50, 67, 0.2);
    glVertex3f(-50, 106, 0.2);
    glVertex3f(-20, 106, 0.2);
    //fondo
    glColor3f( 0.0 , 0.0 ,  0.0 );//cnegro
    glVertex3f(-20, 67, -10.0);
    glVertex3f(-50, 67, -10.0);
    glVertex3f(-50, 106, -10.0);
    glVertex3f(-20, 106, -10.0);
    //paredes
    glColor3f( 1.0 , 1.0 ,  1.0 );//blanco
    glVertex3f(-20, 106, 0.2);
    glVertex3f(-20, 67, 0.2);
    glVertex3f(-20, 67, -10);
    glVertex3f(-20, 106, -10);
    
    glVertex3f(-20, 67, 0.2);
    glVertex3f(-50, 67, 0.2);
    glVertex3f(-50, 67, -10);
    glVertex3f(-20, 67, -10);
    
    glVertex3f(-50, 67,  0.2);
    glVertex3f(-50, 106,  0.2);
    glVertex3f(-50, 106,  -10);
    glVertex3f(-50, 67,  -10);
    
    glVertex3f(-50, 106,  0.2);
    glVertex3f(-20, 106, 0.2);
    glVertex3f(-20, 106, -10);
    glVertex3f(-50, 106,  -10);
    piso_piscina2();
    
	glEnd();
}
void mueble2(){
	//mueble 1 chico
	glBegin(GL_QUADS);
	glColor3f( 0.545 , 0.541 , 0.564 );
	glVertex3f(-26, 135, 1);
    glVertex3f(-42, 135, 1);
    glVertex3f(-42, 135, -2);
    glVertex3f(-26, 135, -2);
    
    glVertex3f(-26, 135, 1);
    glVertex3f(-42, 135, 1);
    glVertex3f(-42, 126, 1);
    glVertex3f(-26, 126, 1);
    
    glVertex3f(-42, 126, 1);
    glVertex3f(-26, 126, 1);
    glVertex3f(-26, 126, 5);
    glVertex3f(-42, 126, 5);
    
    glVertex3f(-26, 126, 5);
    glVertex3f(-42, 126, 5);
    glVertex3f(-42, 122, 5);
    glVertex3f(-26, 122, 5);
    
    glVertex3f(-42, 122, 5);
    glVertex3f(-26, 122, 5);
    glVertex3f(-26, 122, 0.1);
    glVertex3f(-42, 122, 0.1);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f( 0.545 , 0.541 , 0.564 );
	glVertex3f(-42, 126, 1);
    glVertex3f(-42, 126, 5);
    glVertex3f(-42, 122, 5);
    glVertex3f(-42, 122, -2);
    glVertex3f(-42, 135, -2);
    glVertex3f(-42, 135, 1);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f( 0.545 , 0.541 , 0.564 );
	glVertex3f(-26, 126, 1);
    glVertex3f(-26, 126, 5);
    glVertex3f(-26, 122, 5);
    glVertex3f(-26, 122, -2);
    glVertex3f(-26, 135, -2);
    glVertex3f(-26, 135, 1);
	glEnd();
	//mueble 2 grande
	glBegin(GL_POLYGON);
	glColor3f( 0.545 , 0.541 , 0.564 );
	glVertex3f(-17, 135, 1);
    glVertex3f(-17, 135, 5);
    glVertex3f(-15, 135, 5);
    glVertex3f(-15, 135, -2);
    glVertex3f(-25, 135, -2);
    glVertex3f(-25, 135, 1);
	glEnd();
	
	glBegin(GL_QUADS);
	glColor3f( 0.545 , 0.541 , 0.564 );
	glVertex3f(-25, 165, 1);
    glVertex3f(-25, 135, 1);
    glVertex3f(-25, 135, -2);
    glVertex3f(-25, 165, -2);
    
    glVertex3f(-25, 165, 1);
    glVertex3f(-25, 135, 1);
    glVertex3f(-17, 135, 1);
    glVertex3f(-17, 165, 1);
    
    glVertex3f(-17, 135, 1);
    glVertex3f(-17, 165, 1);
    glVertex3f(-17, 165, 5);
    glVertex3f(-17, 135, 5);
    
    glVertex3f(-17, 165, 5);
    glVertex3f(-17, 135, 5);
    glVertex3f(-15, 135, 5);
    glVertex3f(-15, 165, 5);
	glEnd();
	
	//mesa de centro
	glBegin(GL_QUADS);
	glColor3f( 0.545 , 0.541 , 0.564 );
	glVertex3f(-40, 158, 1);
    glVertex3f(-40, 144, 1);
    glVertex3f(-40, 144, -2);
    glVertex3f(-40, 158, -2);
    
    glVertex3f(-34, 158, 1);
    glVertex3f(-34, 144, 1);
    glVertex3f(-34, 144, -2);
    glVertex3f(-34, 158, -2);
    
    glVertex3f(-40, 158, -2);
    glVertex3f(-40, 158, 1);
    glVertex3f(-34, 158, 1);
    glVertex3f(-34, 158, -2);
    
    glVertex3f(-40, 144, -2);
    glVertex3f(-40, 144, 1);
    glVertex3f(-34, 144, 1);
    glVertex3f(-34, 144, -2);
    
    glVertex3f(-40, 158, 1);
    glVertex3f(-40, 144, 1);
    glVertex3f(-34, 144, 1);
    glVertex3f(-34, 158, 1);
	glEnd();
	glBegin(GL_QUADS);
	//========================GROSOR COJINES
	glColor3f( 0.756 , 0.698 , 0.588 );
	glVertex3f(-26, 135, 1.8);
    glVertex3f(-42, 135, 1.8);
    glVertex3f(-42, 126, 1.8);
    glVertex3f(-26, 126, 1.8);
    
    glVertex3f(-42, 135, 1);
    glVertex3f(-42, 126, 1);
    glVertex3f(-42, 126, 1.8);
    glVertex3f(-42, 135, 1.8);
    
    glVertex3f(-26, 135, 1);
    glVertex3f(-26, 126, 1);
    glVertex3f(-26, 126, 1.8);
    glVertex3f(-26, 135, 1.8);
    
    glVertex3f(-26, 135, 1);
    glVertex3f(-42, 135, 1);
    glVertex3f(-42, 135, 1.8);
    glVertex3f(-26, 135, 1.8);
    //vertical
    glVertex3f(-26, 128, 1.8);
    glVertex3f(-26, 128, 5.8);
    glVertex3f(-42, 128, 5.8);
    glVertex3f(-42, 128, 1.8);
    
    glVertex3f(-42, 128, 5.8);
    glVertex3f(-42, 126, 5.8);
    glVertex3f(-42, 126, 1.8);
    glVertex3f(-42, 128, 1.8);
    
    glVertex3f(-26, 128, 5.8);
    glVertex3f(-26, 126, 5.8);
    glVertex3f(-26, 126, 1.8);
    glVertex3f(-26, 128, 1.8);
    
    glVertex3f(-42, 126, 5.8);
    glVertex3f(-26, 126, 5.8);
    glVertex3f(-26, 126, 5);
    glVertex3f(-42, 126, 5);
    
     glVertex3f(-42, 126, 5.8);
    glVertex3f(-42, 128, 5.8);
    glVertex3f(-26, 128, 5.8);
    glVertex3f(-26, 126, 5.8);
    //----------mueble grande
    glVertex3f(-25, 165, 1);
    glVertex3f(-25, 135,  1);
    glVertex3f(-25, 135,  1.8);
    glVertex3f(-25, 165, 1.8);
    
    glVertex3f(-25, 135, 1);
    glVertex3f(-17, 135,  1);
    glVertex3f(-17, 135,  1.8);
    glVertex3f(-25, 135, 1.8);
    
    glVertex3f(-17, 135, 1.8);
    glVertex3f(-25, 135,  1.8);
    glVertex3f(-25, 165,  1.8);
    glVertex3f(-17, 165, 1.8);
    
    //vertical
    glVertex3f(-19, 135, 1.8);
    glVertex3f(-19, 165,  1.8);
    glVertex3f(-19, 165,   5.8);
    glVertex3f(-19, 135,  5.8);
    
    glVertex3f(-19, 135,  1.8);
    glVertex3f(-17, 135,  1.8);
    glVertex3f(-17, 135,   5.8);
    glVertex3f(-19, 135,   5.8);
    
    glVertex3f(-19, 165, 5.8);
    glVertex3f(-17, 165, 5.8);
    glVertex3f(-17, 135, 5.8);
    glVertex3f(-19, 135, 5.8);
    
    glVertex3f(-17, 135, 5.8);
    glVertex3f(-17, 165, 5.8);
    glVertex3f(-17, 165, 5);
    glVertex3f(-17, 135, 5);
	glEnd();
	//-----------------MUEBLE TV
	glBegin(GL_QUADS);
	glColor3f( 0.756 , 0.698 , 0.588 );
	glVertex3f(-44, 165, 4);
    glVertex3f(-30, 165, 4);
    glVertex3f(-30, 162, 4);
    glVertex3f(-44, 162, 4);
    
    glVertex3f(-44, 165, 4);
    glVertex3f(-44, 162, 4);
    glVertex3f(-44, 162, 2);
    glVertex3f(-44, 165, 2);
    
    glVertex3f(-30, 165, 4);
    glVertex3f(-30, 162, 4);
    glVertex3f(-30, 162, 2);
    glVertex3f(-30, 165, 2);
    
    glVertex3f(-44, 162, 4);
    glVertex3f(-30, 162, 4);
    glVertex3f(-30, 162, 2);
    glVertex3f(-44, 162, 2);
	glEnd();
	//------------------------TV
	glBegin(GL_QUADS);
	glColor3f( 0.0 , 0.0 , 0.0 );
	glVertex3f(-44, 164, 16);
    glVertex3f(-30, 164, 16);
    glVertex3f(-30, 164, 8);
    glVertex3f(-44, 164, 8);
    
    glVertex3f(-44, 164, 16);
    glVertex3f(-44, 164, 8);
    glVertex3f(-44, 165, 8);
    glVertex3f(-44, 165, 16);
    
    glVertex3f(-30, 164, 16);
    glVertex3f(-30, 164, 8);
    glVertex3f(-30, 165, 8);
    glVertex3f(-30, 165, 16);
    
    glVertex3f(-44, 164, 16);
    glVertex3f(-30, 164, 16);
    glVertex3f(-30, 165, 16);
    glVertex3f(-44, 165, 16);
    
    glVertex3f(-44, 164, 8);
    glVertex3f(-30, 164, 8);
    glVertex3f(-30, 165, 8);
    glVertex3f(-44, 165, 8);
    glEnd();
}
void paredes_contorno(){
	glBegin(GL_QUADS);
	glColor3f( 0.850 , 0.850 , 0.843 );
	glVertex3f(-50, 67, -2);
    glVertex3f(-50, 67, 25);
    glVertex3f(-50, 165, 25);
    glVertex3f(-50, 165, -2);
    
    glVertex3f(-50, 67, 0.1);
    glVertex3f(-50, 67, 25);
    glVertex3f(55, 67, 25);
    glVertex3f(55, 67, 0.1);
	glEnd();
}
void lineas_casa2(){
	//-----------------------lineas detallado
	//sala descanso patio
    glLineWidth(2);
    //mesa de centro
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-34, 158, 1);
    glVertex3f(-34, 144, 1);
    glVertex3f(-40, 144, 1);
    glVertex3f(-40, 158, 1);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex3f(-26, 135, 1.8);
    glVertex3f(-26, 128.1, 1.8);
    glVertex3f(-42, 128.1, 1.8);
    glVertex3f(-42, 135, 1.8);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex3f(-26, 128, 5.8);
    glVertex3f(-26, 126, 5.8);
    glVertex3f(-42, 126, 5.8);
    glVertex3f(-42, 128, 5.8);
    glEnd();
    //techo
    glBegin(GL_LINE_LOOP);
    glVertex3f(0, 172, 35);
    glVertex3f(0, 106, 35);
    glVertex3f(24, 106, 35);
    glVertex3f(24, 172, 35);
    glEnd();
    //escalera
    glBegin(GL_LINE_LOOP);
    glVertex3f(-42, 130, -1);
    glVertex3f(-42, 126, -1);
    glVertex3f(-50, 126, -1);
    glVertex3f(-50, 130, -1);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex3f(-42, 126, 0.1);
    glVertex3f(-42, 122, 0.1);
    glVertex3f(-50, 122, 0.1);
    glVertex3f(-50, 126, 0.1);
    glEnd();
    //sillon grande
    glBegin(GL_LINE_LOOP);
    glVertex3f(-42, 126, 5);
    glVertex3f(-26, 126, 5);
    glVertex3f(-26, 122, 5);
    glVertex3f(-42, 122, 5);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex3f(-25, 165, 1.8);
    glVertex3f(-19.1, 165,  1.8);
    glVertex3f(-19.1, 135, 1.8);
    glVertex3f(-25, 135, 1.8);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex3f(-19, 165, 5.8);
    glVertex3f(-17, 165, 5.8);
    glVertex3f(-17, 135, 5.8);
    glVertex3f(-19, 135, 5.8);
    glEnd();
    
    
    glBegin(GL_LINES);
    glVertex3f(-19, 165, 5.8);
    glVertex3f(-19, 165, 1.8);
    glVertex3f(-19, 135,  5.8);
    glVertex3f(-19, 135, 1.8);
    
    glVertex3f(-26, 128,  5.8);
    glVertex3f(-26, 128,  1.8);
    glVertex3f(-42, 128,   5.8);
    glVertex3f(-42, 128,  1.8);
    
    glVertex3f(-26, 122, 5);
    glVertex3f(-26, 122, 0.1);
    glVertex3f(-42, 122, 0.1);
    glVertex3f(-42, 122, 5);
    glEnd();
    //----------piso vereda
    glBegin(GL_LINE_LOOP);
    glVertex3f(-20, 106, 0.7);
    glVertex3f(-20, 67, 0.7);
    glVertex3f(-10, 67, 0.7);
    glVertex3f(-10, 122, 0.7);
    glVertex3f(-50, 122, 0.7);
    glVertex3f(-50, 106, 0.7);
    glEnd();
    //=========================muro marron
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-15.1, 165, -2);
    glVertex3f(-50, 165, -2);
    glVertex3f(-50, 165, 40);
    glVertex3f(-15.1, 165, 40);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-50, 165, 40);
    glVertex3f(-15, 165, 40);
    glVertex3f(-15, 172, 40);
    glVertex3f(-50, 172, 40);
    glEnd();
    //===================CUARTO A
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(28, 76, 40);
    glVertex3f(-10, 76, 40);
    glVertex3f(-10, 106, 40);
    glVertex3f(28, 106, 40);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(28, 76, 40);
    glVertex3f(28, 106, 40);
    glVertex3f(28, 106, 0.1);
    glVertex3f(28, 76, 0.1);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-10, 76, 40);
    glVertex3f(-10, 106, 40);
    glVertex3f(-10, 106, 0.1);
    glVertex3f(-10, 76, 0.1);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(18, 106, 35);
    glVertex3f(0, 106, 35);
    glVertex3f(0, 106, 0.1);
    glVertex3f(-10, 106, 0.1);
    
    glVertex3f(-10, 106, 40);
    glVertex3f(28, 106, 40);
    glVertex3f(28, 106, 0.1);
    glVertex3f(18, 106, 0.1);
    glEnd();
    //=========================CUARTO C
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(24, 106, 35);
    glVertex3f(24, 172, 35);
    glVertex3f(24, 172, 30);
    glVertex3f(38, 172, 30);
    
    glVertex3f(38, 172, 0.1);
    glVertex3f(38, 122, 0.1);
    glVertex3f(38, 122, 30);
    glVertex3f(24, 122, 30);
    
    glVertex3f(24, 122, 0.1);
    glVertex3f(24, 106, 0.1);
    glEnd();
    //puerta
     glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(24, 106.1, 0.2);
    glVertex3f(24, 106.1, 18);
    glVertex3f(24, 116.1, 18);
    glVertex3f(24, 116.1, 0.2);
    glEnd();
    //piso cochera
     glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(33, 76, 0.1);
    glVertex3f(33, 122, 0.1);
    glVertex3f(64, 122, 0.1);
    glVertex3f(64, 76, 0.1);
    glEnd();
    //muro de cochera
     glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(36, 76, 20);
    glVertex3f(60, 76, 20);
    glVertex3f(60, 70, 20);
    glVertex3f(36, 70, 20);
    glEnd();
    //mueble tx
    glBegin(GL_LINE_LOOP);
    glVertex3f(-44, 165, 4);
    glVertex3f(-30, 165, 4);
    glVertex3f(-30, 162, 4);
    glVertex3f(-44, 162, 4);
    glEnd();
    //ventana
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(38, 136, 5);
    glVertex3f(38, 136, 22);
    glVertex3f(38, 163, 22);
    glVertex3f(38, 163, 5);
    glEnd();
    //otros
    glBegin(GL_LINES);
    glVertex3f(38, 122, 0.1);
    glVertex3f(38, 122, 30);
    glVertex3f(24, 122, 35);
    glVertex3f(24, 122, 0.1);
    
    glVertex3f(38, 122, 30);
    glVertex3f(38, 172, 30);
    glVertex3f(60, 76, 20);
    glVertex3f(60, 76, 0.1);
    
    glVertex3f(60, 70, 20);
    glVertex3f(60, 70, 0.1);
    glVertex3f(36, 76, 20);
    glVertex3f(36, 76, 0.1);
    
    glVertex3f(-44, 162, 4);
    glVertex3f(-44, 162, 2);
    glVertex3f(-30, 162, 4);
    glVertex3f(-30, 162, 2);
    glVertex3f(-44, 162, 2);
    glVertex3f(-30, 162, 2);
    
    glVertex3f(-40, 144, 1);
    glVertex3f(-40, 144, -2);
    glVertex3f(-34, 144, 1);
    glVertex3f(-34, 144, -2);
    
    glVertex3f(-40, 158, 1);
    glVertex3f(-40, 158, -2);
    glVertex3f(-34, 158, 1);
    glVertex3f(-34, 158, -2);
    
    glVertex3f(-8, 145, 0.1);
    glVertex3f(-8, 145, 9);
    glVertex3f(-8, 155, 0.1);
    glVertex3f(-8, 155, 9);
    
    glVertex3f(-8, 165, 0.1);
    glVertex3f(-8, 165,9);
    
    glVertex3f(-8, 145, 19);
    glVertex3f(-8, 145, 24);
    glVertex3f(-8, 155, 19);
    glVertex3f(-8, 155, 24);
    
    glVertex3f(-8, 165, 19);
    glVertex3f(-8, 165,24);
    glVertex3f(-8, 128, 0.1);
    glVertex3f(-8, 128, 19);
    
    glVertex3f(-8, 122, 19);
    glVertex3f(-8, 135, 19);
    glVertex3f(-8, 135, 19);
    glVertex3f(-8, 135, 0.1);
    
    glVertex3f(0, 172, 30);
    glVertex3f(0, 122, 30);
    glVertex3f(24, 172, 30);
    glVertex3f(24, 122, 30);
    
    glVertex3f(6, 145, 0.1);
    glVertex3f(6, 145, 9);
    glVertex3f(0, 145, 0.1);
    glVertex3f(0, 145, 9);
     glEnd();
     //COCINA
     glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(6, 145, 9);
    glVertex3f(0, 145, 9);
    glVertex3f(0, 172, 9);
    glVertex3f(6, 172, 9);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-10, 148,  9);
    glVertex3f(-14.9, 148, 9);
    glVertex3f(-14.9, 135, 9);
    glVertex3f(-8, 135, 9);
    
    glVertex3f(-8, 172,  9);
    glVertex3f(-14.9, 172,  9);
    glVertex3f(-14.9, 160, 9);
    glVertex3f(-10, 160,  9);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-8, 135, 24);
    glVertex3f(-8, 172, 24);
    glVertex3f(-8, 172, 19);
    glVertex3f(-8, 135, 19);
    glEnd();
    //mesa
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(30, 140, 8);
    glVertex3f(15, 140, 8);
    glVertex3f(15, 166, 8);
    glVertex3f(30, 166, 8);
    glEnd();
}
void pata_mesa(){
	//================================PATAS
	glBegin(GL_QUADS);
	glColor3f( 0.850 , 0.850 , 0.843 );
	glVertex3f(15, 166, 0.1);
    glVertex3f(15, 166, 7);
    glVertex3f(16, 166, 7);
    glVertex3f(16, 166, 0.1);
    
    glVertex3f(15, 165, 0.1);
    glVertex3f(15, 165, 7);
    glVertex3f(16, 165, 7);
    glVertex3f(16, 165, 0.1);
    
    glVertex3f(16, 166,  0.1);
    glVertex3f(16, 166, 7);
    glVertex3f(16, 165, 7);
    glVertex3f(16, 165,  0.1);
    
    glVertex3f(15, 166,  0.1);
    glVertex3f(15, 166, 7);
    glVertex3f(15, 165, 7);
    glVertex3f(15, 165,  0.1);
	glEnd();
	
	
}
void sala(){
	//================================MESAAA
	glBegin(GL_QUADS);
	glColor3f( 0.850 , 0.850 , 0.843 );
	glVertex3f(30, 166, 8);
    glVertex3f(30, 140, 8);
    glVertex3f(15, 140, 8);
    glVertex3f(15, 166, 8);
    
    glVertex3f(30, 166, 7);
    glVertex3f(30, 140, 7);
    glVertex3f(15, 140, 7);
    glVertex3f(15, 166, 7);
    
    glVertex3f(30, 166, 8);
    glVertex3f(15, 166, 8);
    glVertex3f(15, 166, 7);
    glVertex3f(30, 166, 7);
    
    glVertex3f(30, 140, 8);
    glVertex3f(15, 140, 8);
    glVertex3f(15, 140, 7);
    glVertex3f(30, 140, 7);
    
    glVertex3f(30, 166, 8);
    glVertex3f(30, 140, 8);
    glVertex3f(30, 140, 7);
    glVertex3f(30, 166, 7);
    
    glVertex3f(15, 166, 8);
    glVertex3f(15, 140, 8);
    glVertex3f(15, 140, 7);
    glVertex3f(15, 166, 7);
	glEnd();
	
	pata_mesa();
	glPushMatrix();
	glTranslatef(14.0f, 0.0f, 0.0f);//TRASLADADO
	pata_mesa();
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.0f, -25.0f, 0.0f);//TRASLADADO
	pata_mesa();
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(14.0f, -25.0f, 0.0f);//TRASLADADO
	pata_mesa();
	glEnd();
	glPopMatrix();
}
void cocina2(){
	glBegin(GL_QUADS);
	glColor3f( 0.537 , 0.435 , 0.360 );
	glVertex3f(6, 145, 9);
    glVertex3f(6, 172, 9);
    glVertex3f(6, 172, 0.1);
    glVertex3f(6, 145, 0.1);
    
    glVertex3f(0, 145, 9);
    glVertex3f(0, 172, 9);
    glVertex3f(0, 172, 0.1);
    glVertex3f(0, 145, 0.1);
    
    glVertex3f(6, 145, 9);
    glVertex3f(0, 145, 9);
    glVertex3f(0, 145, 0.1);
    glVertex3f(6, 145, 0.1);
    
    
    glVertex3f(6, 145, 9);
    glVertex3f(0, 145, 9);
    glVertex3f(0, 172, 9);
    glVertex3f(6, 172, 9);
    //zona lavadero
    glVertex3f(-8, 135, 9);
    glVertex3f(-8, 172, 9);
    glVertex3f(-8, 172, 0.1);
    glVertex3f(-8, 135, 0.1);
    
    glVertex3f(-15, 160, 9);
    glVertex3f(-15, 172, 9);
    glVertex3f(-8, 172, 9);
    glVertex3f(-8, 160, 9);
    //cajones arriba
    glColor3f( 0.886 , 0.862 , 0.850 );
    glVertex3f(-8, 135, 19);
    glVertex3f(-8, 172, 19);
    glVertex3f(-8, 172, 24);
    glVertex3f(-8, 135, 24);
    
    glVertex3f(-8, 172, 24);
    glVertex3f(-8, 135, 24);
    glVertex3f(-15, 135, 24);
    glVertex3f(-15, 172, 24);
    
    glVertex3f(-8, 172, 19);
    glVertex3f(-8, 135, 19);
    glVertex3f(-15, 135, 19);
    glVertex3f(-15, 172, 19);
    
    glVertex3f(-8, 135, 24);
    glVertex3f(-15, 135, 24);
    glVertex3f(-15, 135, 19);
    glVertex3f(-8, 135, 19);
    //refrigerador
    glColor3f( 0.266 , 0.278 , 0.274 );
    glVertex3f(-8, 122, 19);
    glVertex3f(-8, 135, 19);
    glVertex3f(-8, 135, 0.1);
    glVertex3f(-8, 122, 0.1);
    
    glVertex3f(-8, 135, 19);
    glVertex3f(-15, 135, 19);
    glVertex3f(-15, 135, 0.1);
    glVertex3f(-8, 135, 0.1);
    
    glVertex3f(-8, 135, 19);
    glVertex3f(-15, 135, 19);
    glVertex3f(-15, 122, 19);
    glVertex3f(-8, 122, 19);
    //LAVADERO
    glColor3f( 0.470 , 0.513 , 0.576 );
    glVertex3f(-10, 148, 9);
    glVertex3f(-15, 148, 9);
    glVertex3f(-15, 148 ,7);
    glVertex3f(-10, 148, 7);
    
    glVertex3f(-10, 160, 9);
    glVertex3f(-15, 160, 9);
    glVertex3f(-15, 160, 7);
    glVertex3f(-10, 160, 7);
    
    glVertex3f(-10, 148, 9);
    glVertex3f(-10, 160,  9);
    glVertex3f(-10, 160,  7);
    glVertex3f(-10, 148, 7);
    
    glVertex3f(-15, 148, 7);
    glVertex3f(-15, 160, 7);
    glVertex3f(-10, 160, 7);
    glVertex3f(-10, 148, 7);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f( 0.537 , 0.435 , 0.360 );
	glVertex3f(-10, 148, 9);
    glVertex3f(-15, 148, 9);
    glVertex3f(-15, 135, 9);
    glVertex3f(-8, 135, 9);
    
    glVertex3f(-8, 160, 9);
    glVertex3f(-10, 160, 9);
    glVertex3f(-10, 148, 9);
	glEnd();
}
void oficina(){
	glBegin(GL_POLYGON);
	glColor3f( 0.741 , 0.490 , 0.050 );
	glVertex3f(0, 86, 8);
    glVertex3f(0, 103, 8);
    glVertex3f(-10, 103, 8);
    glVertex3f(-10, 76, 8);
    
    glVertex3f(9, 76, 8);
    glVertex3f(9, 86, 8);
	glEnd();
	
	glBegin(GL_POLYGON);
	
	glVertex3f(0, 86, 8);
    glVertex3f(0, 103, 8);
    glVertex3f(0, 103, 0.1);
    glVertex3f(0, 86, 0.1);
    
    glVertex3f(9, 86, 0.1);
    glVertex3f(9, 86, 8);
	glEnd();
	
	glBegin(GL_QUADS);
	
	glVertex3f(9, 86, 0.1);
    glVertex3f(9, 86, 8);
    glVertex3f(9, 76, 8);
    glVertex3f(9, 76, 0.1);
    
    glVertex3f(0, 103, 8);
    glVertex3f(-10, 103, 8);
    glVertex3f(-10, 103, 0.1);
    glVertex3f(0, 103, 0.1);
	glEnd();
	
	glBegin(GL_LINE_LOOP);
	glColor3f( 0.0 , 0.0 , 0.0 );
	glVertex3f(0, 86, 8);
    glVertex3f(0, 103, 8);
    glVertex3f(0, 103, 0.1);
    glVertex3f(0, 86, 0.1);
    
    glVertex3f(9, 86, 0.1);
    glVertex3f(9, 86, 8);
	glEnd();
	
	glBegin(GL_LINE_LOOP);
	
	glVertex3f(0, 86, 8);
    glVertex3f(0, 103, 8);
    glVertex3f(-10, 103, 8);
    glVertex3f(-10, 76, 8);
    
    glVertex3f(9, 76, 8);
    glVertex3f(9, 86, 8);
	glEnd();
}

//---------------------------2do piso
void baranda(){
	glBegin(GL_QUADS);
	glColor3f( 0.121 , 0.788 , 0.823 );//CIAN CLARO
	glVertex3f(-15, 172, 35);
    glVertex3f(0, 172, 35);
    glVertex3f(0, 172, 30);
    glVertex3f(-15, 172, 30);
    
    glVertex3f(-15, 158, 30);
    glVertex3f(-15, 158, 35);
    glVertex3f(-15, 122, 35);
    glVertex3f(-15, 122, 30);
    
    glVertex3f(-15, 122, 35);
    glVertex3f(-15, 122, 30);
    glVertex3f(0, 122, 30);
    glVertex3f(0, 122, 35);
    glEnd();
    //lineas
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-15, 122, 34.9);
    glVertex3f(0, 122, 35);
    glVertex3f(0, 122, 30.1);
    glVertex3f(-15, 122, 30.1);
    glVertex3f(-15, 158, 30.1);
    glVertex3f(-15, 158, 34.9);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3f( 0.0 , 0.0 , 0.0 );
    glVertex3f(-15, 172, 34.9);
    glVertex3f(-15, 172, 30.1);
    glVertex3f(0, 172, 30.1);
    glVertex3f(0, 172, 34.9);
    glEnd();
}

void segundopiso(){
	baranda();
}

void casa2(){
	
cochera();
pasto2();
cuartoa();
cuartob();
cuartoc();
pisocasa();
zona_descanso();
escalera_patio();
double y=2.0;
double z=2.0;
for(int i=0;i<12;i++){
glPushMatrix();
glTranslatef(0.0f, y, z);//TRASLADADO
escalera_patio();
y=y+3;
z=z+2.45;
glEnd();
glPopMatrix();
}
piscina2();
mueble2();
paredes_contorno();
lineas_casa2();
segundopiso();
sala();
cocina2();
oficina();
}

//=========================================================================================================

void TerrazaObjetos()
{ 
		//OBJETOS DE TERRAZA 
		// MUEBLE
	//PATA 1
	glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(-1,12,25.2); 
		glScalef(0.1, 0.1,1);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
		glPopMatrix();
	//PATA 2	
	glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(-10,12,25.2); 
		glScalef(0.1, 0.1, 1);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	//PATA 3
	glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(-10,-7,25.2); 
		glScalef(0.1, 0.1, 1);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	
	//PATA 4
	glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(-1,-7,25.2); 
		glScalef(0.1, 0.1, 1);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	//BASE
	
	glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(-5.5,2.5,24); 
		glScalef(1, 2, 0.1);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	//-------------------------
	glPushMatrix();
		glColor3f( 1.0,1.0,1.0);
	    glTranslatef(-5,2.5,25.3); 
		glScalef(0.9, 1.8, 0.15);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	
	
	//-----------------------------------------------------------
	glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(-10,2.5,25); 
		glScalef(0.1,2, 0.05);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	
	glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(-10,2.5,26); 
		glScalef(0.1,2, 0.05);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	
	glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(-10,2.5,27); 
		glScalef(0.1,2, 0.05);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	
	glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(-10,2.5,28); 
		glScalef(0.1,2, 0.05);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	
	glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(-10,2.5,29); 
		glScalef(0.1,2, 0.05);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	
	glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(-10,2.5,30); 
		glScalef(0.1,2, 0.05);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	//---------------------------------------------
	glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(-5.5,-7,26); 
		glScalef(1, 0.1, 0.05);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	
	glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(-5.5,-7,27); 
		glScalef(1, 0.1, 0.05);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	
	glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(-5.5,-7,28); 
		glScalef(1, 0.1, 0.05);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	
	glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(-5.5,-7,29); 
		glScalef(1, 0.1, 0.05);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	
	glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(-5.5,-7,30); 
		glScalef(1, 0.1, 0.05);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	//-------------------------------------------------------------
	
	glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(-5.5,12,26); 
		glScalef(1, 0.1, 0.05);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	
	glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(-5.5,12,27); 
		glScalef(1, 0.1, 0.05);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	
	glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(-5.5,12,28); 
		glScalef(1, 0.1, 0.05);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	
	glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(-5.5,12,29); 
		glScalef(1, 0.1, 0.05);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	
	glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(-5.5,12,30); 
		glScalef(1, 0.1, 0.05);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	//-----------------------2---------------------------
	//---P1
	glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(45,12,25.2); 
		glScalef(0.1, 0.1,1);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	//---P2
	glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(35,12,25.2); 
		glScalef(0.1, 0.1,1);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	//---P3
	glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(35,-7,25.2); 
		glScalef(0.1, 0.1,1);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
		//---P4
	glPopMatrix();
		glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(45,-7,25.2); 
		glScalef(0.1, 0.1,1);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	
	//BASE
	
	glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(40,2.5,24); 
		glScalef(1.1, 2, 0.1);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	//-------------------------
	glPushMatrix();
		glColor3f( 1.0,1.0,1.0);
	    glTranslatef(40,2.5,25.3); 
		glScalef(1.1, 1.8, 0.15);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	
	//------------------------------------------------------
		
	glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(45,2.5,26); 
		glScalef(0.1, 2, 0.05);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	
	glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(45,2.5,27); 
		glScalef(0.1, 2, 0.05);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	
	glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(45,2.5,28); 
		glScalef(0.1, 2, 0.05);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	
	glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(45,2.5,29); 
		glScalef(0.1, 2, 0.05);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	
	glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(45,2.5,30); 
		glScalef(0.1, 2, 0.05);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	
	//--------------------------------------
	glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(40,12,26); 
		glScalef(1.1, 0.1, 0.05);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();

glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(40,12,27); 
		glScalef(1.1, 0.1, 0.05);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	
	glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(40,12,28); 
		glScalef(1.1, 0.1, 0.05);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	
	glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(40,12,29); 
		glScalef(1.1, 0.1, 0.05);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	
	glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(40,12,30); 
		glScalef(1.1, 0.1, 0.05);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();	
	//-----------------------------------------------
	glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(40,-7,26); 
		glScalef(1.1, 0.1, 0.05);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	
	glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(40,-7,27); 
		glScalef(1.1, 0.1, 0.05);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	
	glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(40,-7,28); 
		glScalef(1.1, 0.1, 0.05);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	
	glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(40,-7,29); 
		glScalef(1.1, 0.1, 0.05);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	
	glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(40,-7,30); 
		glScalef(1.1, 0.1, 0.05);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	
//------------------------SOMBRILLA
	
	glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(35,-15,20.5); 
		glScalef(0.75, 0.75, 0.05);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	

	glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(35,-16,30.3); 
		glScalef(0.1, 0.1,2);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	
	
	glPushMatrix();
	glRotated(-45, 1,0,1.5);
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(42.7,-6,37);
		glScalef(0.1, 0.1,2);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	
		
	glPushMatrix();
	
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(35,-6,50);
		glScalef(2,2,0.07);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	


	
	//----------------------MESA
	glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(15,-5,22); 
		glScalef(1, 0.1, 0.05);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	//-----
	glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(15,-5,25.5); 
		glScalef(1, 0.1, 0.05);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	
	glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(15,10,25.5); 
		glScalef(1, 0.1, 0.05);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	
	glPushMatrix();
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(15,10,22); 
		glScalef(1, 0.1, 0.05);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
		//----P1
	glPushMatrix();
	    
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(10.5,10,23); 
		glScalef(0.1,0.1,0.55);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f,0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	//-----P2
	glPushMatrix();
	    glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(19.5,10,23); 
		glScalef(0.1,0.1,0.55);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	
	//----P3
	glPushMatrix();
	    
		glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(10.5,-5,23); 
		glScalef(0.1,0.1,0.55);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	//-----P4
	glPushMatrix();
	    glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(19.5,-5,23); 
		glScalef(0.1,0.1,0.55);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	//----------------------

	glPushMatrix();
	    glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(19.5,3,25.5); 
		glScalef(0.1,1.50,0.05);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	
	glPushMatrix();
	    glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(17,3,25.5); 
		glScalef(0.1,1.50,0.05);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	glPushMatrix();
	    glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(15,3,25.5); 
		glScalef(0.1,1.50,0.05);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	
	glPushMatrix();
	    glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(13,3,25.5); 
		glScalef(0.1,1.50,0.05);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	
	glPushMatrix();
	    glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(10.5,3,25.5); 
		glScalef(0.1,1.50,0.05);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	
	//-----------------PLANTAS
	
	glPushMatrix();
	   	glColor3f(0.714, 0.613, 0.415);
	    glTranslatef(-5,-15,23); 
		glScalef(0.5,0.5,0.55);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	
	glPushMatrix();
	    glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(-5,-15,27); 
		glScalef(0.1,0.1,0.75);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	
	glPushMatrix();
	    glColor3f( 0.714, 0.613, 0.415);
	    glTranslatef(45,-15,23); 
		glScalef(0.5,0.5,0.55);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	
		glPushMatrix();
	    glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(45,-15,27); 
		glScalef(0.1,0.1,0.75);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
		glPushMatrix();
	    glColor3f( 0.714, 0.613, 0.415);
	    glTranslatef(40,20,23); 
		glScalef(0.5,0.5,0.55);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	
	glPushMatrix();
	    glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(40,20,27); 
		glScalef(0.1,0.1,0.75);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
/*
  //-------------------------Re
  	glPushMatrix();
	    glColor3f( 0.34 ,0.10 ,0);
	    glTranslatef(15,23,25.2); 
		glScalef(2.5,0.3,1);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	//----Puerta Rep
	glPushMatrix();
	    glColor3f( 0.714, 0.613, 0.415);
	    glTranslatef(8,21.5,25.2); 
		glScalef(1,0.005,0.85);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	
	glPushMatrix();

		glColor3f(1.0,1.0,1.0);
        glTranslatef(17,21.5,26);
	    glScalef(0.03, 0.03, 0.03);
		glutSolidCube(10);
		glColor3f(0.1,0.1,0.1);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
	
	//----Puerta Rep
	glPushMatrix();
	    glColor3f( 0.714, 0.613, 0.415);
	    glTranslatef(20.5,21.5,25.2); 
		glScalef(1.1,0.005,0.85);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1);	
		glEnd ();	
	glPopMatrix();
	
	
	glPushMatrix();

		glColor3f(1.0,1.0,1.0);
        glTranslatef(11,21.5,26);
	    glScalef(0.03, 0.03, 0.03);
		glutSolidCube(10);
		glColor3f(0.1,0.1,0.1);
		LineaCubo(2);	
		glEnd ();	
	glPopMatrix();
	
	
//-----------------------Radio

glPushMatrix();
     glTranslatef(65,5 ,25 ); 
    Radio();
glPopMatrix();


//_______________TV
glPushMatrix();
	
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(14,23,35);
		glScalef(1,0.1,0.5);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1.5);

	glPopMatrix();
	
	///////////////////////////////////////////// TV DISPLAY //////////////////////////////////////////////////////////////////////
	glPushMatrix();
	
		glColor3f( RED1, GREEN1, BLUE1 );
		glTranslatef(10,22.5,35);
		glScalef(0.2, 0.005, 0.5);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1.5);

	glPopMatrix();

    glPushMatrix();
	
		glColor3f( RED2, GREEN2, BLUE2 );
		glTranslatef(12,22.5,35);
		glScalef(0.2, 0.005, 0.5);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1.5);

	glPopMatrix();

    glPushMatrix();
	
		glColor3f( RED3, GREEN3, BLUE3 );
		glTranslatef(14,22.5,35);
		glScalef(0.2, 0.005, 0.5);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1.5);

	glPopMatrix();
    glPushMatrix();
	
		glColor3f( RED4, GREEN4, BLUE4 );
		glTranslatef(16,22.5,35);
		glScalef(0.2, 0.005, 0.5);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1.5);

	glPopMatrix();
	
	glPushMatrix();
	
		glColor3f( RED1, GREEN1, BLUE1 );
		glTranslatef(18,22.5,35);
		glScalef(0.2, 0.005, 0.5);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1.5);

	glPopMatrix();
	//ImagenTV();		
	
	///////////////////////////////////////////// TV //////////////////////////////////////////////////////////////////////
	glPushMatrix();
		
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(14,22.5,31);
		glRotatef(90, 1.0, 0.0, 0.0);
		glScalef(1, 0.01, 0.04);
		glutSolidCube(10);
		glColor3f(0.0f, 0.0f, 0.0f);
		LineaCubo(1.5);
	glPopMatrix();*/


}


void casanueva1_pt1(){
//cocina
	paredes();
	espejo_y_puerta();
	Mampara();
	Tragaluz();
	Encimera();
    Candelabro();
	Refrigedador();
	repisa1();
	repisa2();
	cocina();
	silla();

	
}
void casanueva1_pt2(){
	repostero();
	estanteArriba();
	Utensilios ();
	//auto
    vehiculo();
    //patio
    vereda_piscina();
	silla1_piscina();
	silla2_piscina();
	piscina();
	pasto();
	zona_parrilla();
	//sala
	paredes1();
	mesaTVSala();
	televisor();
	cuadro1();
	

}
void casanueva1_pt3(){
	
	puertaPasilloSala();
	puertaPrincipal();
	repisa3();
	repisa4();
	mueble();
	mesa();
	mueble1();
	paredes2();


}
void casanueva1_pt4(){
	glPushMatrix();
	glTranslated(34.1,51,15.7);
	glRotated(90,1,0,0);
	glRotated(180,0,-1,0);
	glScaled(3.8,3,3);
	glPushMatrix();
		Alfombra();
		PisoCuarto();
		paredDerechaFondo();
		paredIzquierdaFondo();
		Puerta();
		Muebles();
	glPopMatrix();
    glPushMatrix();
        glRotatef(-45,0,1,0);
        glTranslatef(posXPericote,0.0,0.0);
        DibujarPericote();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(2.5, 4.0, -5.0);
        SillaGamer();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-1.0, 0.0, 0.03);
        Escritorio();
    glPopMatrix();
    glPushMatrix();
        TV();
    glPopMatrix();
	glPopMatrix();	
}
void casanueva1_pt5(){

cal();
puertabanio();
ducha();
espejo_y_lavadero();
retrete();
lavadora();
cuadro2();
cuadro3();
cuarto2();
pasillo();
Radio();
pared();
repisa_y_alfombra();
//cuarto segundo piso
escalera();
terraza();
cuarto_segundo_piso();
mesas();
tele2();
mueble2();
espejo2do();
escritorio3();
PC();
librero();
libros();
mampara2();
mueble3();
TerrazaObjetos();
}

void casaJara(){
	
	
	glPushMatrix();
	//------PAREDES Y PISO DE LA SALA----------------
//PISO
	glBegin(GL_POLYGON);
    glColor3f( 0.631 , 0.639 , 0.619);
    glVertex3f(15.0,-20.0 ,0.0);
    glVertex3f(0.0, -20.0, 0.0);
    glVertex3f(0.0, 20.0 ,0.0);
    glVertex3f(15.0, 20.0, 0.0);
	glEnd();

	glBegin(GL_LINE_STRIP);
    glColor3f(0.0 , 0.0 , 0.0);
    glVertex3f(15,-20,6);
    glVertex3f(3,-20,6);
	glEnd();

	glBegin(GL_LINE_STRIP);
    glColor3f(0.0 , 0.0 , 0.0);
    glVertex3f(15,-20,9.5);
    glVertex3f(3,-20,9.5);
	glEnd();
	
	glBegin(GL_LINE_STRIP);
    glColor3f(0.0 , 0.0 , 0.0);
    glVertex3f(15,-20,13);
    glVertex3f(3,-20,13);
	glEnd();
	
	glBegin(GL_LINE_STRIP);
    glColor3f(0.0 , 0.0 , 0.0);
    glVertex3f(15,-20,16.5);
    glVertex3f(3,-20,16.5);
	glEnd();
	
	glBegin(GL_LINE_STRIP);
    glColor3f(0.0 , 0.0 , 0.0);
    glVertex3f(15,-20,20);
    glVertex3f(3,-20,20);
	glEnd();
	
	glBegin(GL_LINE_STRIP);
    glColor3f(0.0 , 0.0 , 0.0);
    glVertex3f(14.99,-20,6);
    glVertex3f(14.99,-20,20);
	glEnd();
	
	glBegin(GL_LINE_STRIP);
    glColor3f(0.0 , 0.0 , 0.0);
    glVertex3f(3,-20,6);
    glVertex3f(3,-20,20);
	glEnd();
	
	glBegin(GL_LINE_STRIP);
    glColor3f(0.0 , 0.0 , 0.0);
    glVertex3f(6,-20,6);
    glVertex3f(6,-20,20);
	glEnd();
	
	glBegin(GL_LINE_STRIP);
    glColor3f(0.0 , 0.0 , 0.0);
    glVertex3f(9,-20,6);
    glVertex3f(9,-20,20);
	glEnd();
	
	glBegin(GL_LINE_STRIP);
    glColor3f(0.0 , 0.0 , 0.0);
    glVertex3f(12,-20,6);
    glVertex3f(12,-20,20);
	glEnd();
	
	
	
	glBegin(GL_LINE_STRIP);
    glColor3f(0.0 , 0.0 , 0.0);
    glVertex3f(-16.0, -34.0 , 0.01);
    glVertex3f(-14.0, -34.0, 0.01);
    glVertex3f(-14.0, -37.0 , 0.01);
    glVertex3f(-16.0, -37.0, 0.01);
    glVertex3f(-16.0, -34.0 , 0.01);
	glEnd();

	//Paredes
	
	glBegin(GL_POLYGON);
    glColor3f(0.745 , 0.729 , 0.717);
    glVertex3f(15.001,20.0 ,0.0);
    glVertex3f(15.001,-20.0 ,0.0);
    glVertex3f(15.001,-20.0 ,23.0);
    glVertex3f(15.001,20.0, 23.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.745 , 0.729 , 0.717);
    glVertex3f(15.02,20.0 ,0.0);
    glVertex3f(15.02,-20.0 ,0.0);
    glVertex3f(15.02,-20.0 ,23.0);
    glVertex3f(15.02,20.0, 23.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.745 , 0.729 , 0.717);
    glVertex3f(15.0,20.0 ,23.0);
    glVertex3f(0.0,20.0 ,23.0);
    glVertex3f(0.0,-20.0 ,23.0);
    glVertex3f(15.0,-20.0, 23.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.745 , 0.729 , 0.717);
    glVertex3f(15.0,-20.0 ,23.0);
    glVertex3f(15.0,-20.0 ,20.0);
    glVertex3f(0.0, -20.0 ,20.0);
    glVertex3f(0.0, -20.0, 23.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.745 , 0.729 , 0.717);
    glVertex3f(15.0,-20.0 ,6.0);
    glVertex3f(15.0,-20.0 ,0.0);
    glVertex3f(0.0, -20.0 ,0.0);
    glVertex3f(0.0, -20.0, 6.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.745 , 0.729 , 0.717);
    glVertex3f(3.0,-20.0 ,6.0);
    glVertex3f(3.0,-20.0 ,20.0);
    glVertex3f(0.0, -20.0 ,20.0);
    glVertex3f(0.0, -20.0, 6.0);
	glEnd();
	
	
	glBegin(GL_POLYGON);
    glColor3f(0.745 , 0.729 , 0.717);
    glVertex3f(0.0, -20.0, 23.0);
    glVertex3f(0.0,-20.0 ,0.0);
    glVertex3f(0.0, -10.0 ,0.0);
    glVertex3f(0.0, -10.0, 23.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.745 , 0.729 , 0.717);
    glVertex3f(0.0, -10.0, 23.0);
    glVertex3f(0.0,-10.0 ,7.0);
    glVertex3f(0.0, -6.0 ,7.0);
    glVertex3f(0.0, -6.0, 23.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.745 , 0.729 , 0.717);
    glVertex3f(0.0, -6.65, 23.0);
    glVertex3f(0.0,-6.65 ,0.0);
    glVertex3f(0.0, -3.0 ,0.0);
    glVertex3f(0.0, -3.0, 23.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.745 , 0.729 , 0.717);
    glVertex3f(0.0, -3.0, 4.0);
    glVertex3f(0.0,-3.0 ,0.0);
    glVertex3f(0.0, 0.0 ,0.0);
    glVertex3f(0.0, 0.0, 4.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.745 , 0.729 , 0.717);
    glVertex3f(0.0, -3.0, 23.0);
    glVertex3f(0.0,-3.0 ,20.0);
    glVertex3f(0.0, 0.0 ,20.0);
    glVertex3f(0.0, 0.0, 23.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.745 , 0.729 , 0.717);
    glVertex3f(0.0, 0.0 ,23.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 20.0 ,0.0);
    glVertex3f(0.0, 20.0, 23.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.721 , 0.741 , 0.725);
    glVertex3f(0.0, 20.0 ,12.0);
    glVertex3f(15.0, 20.0, 12.0);
    glVertex3f(15.0, 26.0 ,12.0);
    glVertex3f(0.0, 26.0, 12.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.721 , 0.741 , 0.725);
    glVertex3f(0.0, 20.0 ,15.0);
    glVertex3f(0.0, 20.0, 12.0);
    glVertex3f(0.0, 26.0 ,12.0);
    glVertex3f(0.0, 26.0, 15.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.721 , 0.741 , 0.725);
    glVertex3f(15.0, 20.0 ,15.0);
    glVertex3f(15.0, 20.0, 12.0);
    glVertex3f(15.0, 26.0 ,12.0);
    glVertex3f(15.0, 26.0, 15.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.721 , 0.741 , 0.725);
    glVertex3f(0.0, 26.0 ,15.0);
    glVertex3f(0.0, 26.0, 12.0);
    glVertex3f(15.0, 26.0 ,12.0);
    glVertex3f(15.0, 26.0, 15.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.745 , 0.729 , 0.717);
    glVertex3f(0.0, 20.0 ,23.0);
    glVertex3f(0.0, 20.0, 12.0);
    glVertex3f(0.4, 20.0 ,12.0);
    glVertex3f(0.4, 20.0, 23.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.745 , 0.729 , 0.717);
    glVertex3f(0.4, 20.0 ,23.0);
    glVertex3f(0.4, 20.0, 21.0);
    glVertex3f(15.0, 20.0 ,21.0);
    glVertex3f(15.0, 20.0, 23.0);
	glEnd();
	//Pared de la cocina
	glBegin(GL_POLYGON);
    glColor3f(0.745 , 0.729 , 0.717);
    glVertex3f(0.0, 20.0 ,10.8);
    glVertex3f(0.0, 20.0, 0.0);
    glVertex3f(11.0, 20.0 ,0.0);
    glVertex3f(11.0, 20.0, 10.8);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.745 , 0.729 , 0.717);
    glVertex3f(11.0, 20.0 ,10.8);
    glVertex3f(11.0, 20.0, 7.0);
    glVertex3f(15.0, 20.0 ,7.0);
    glVertex3f(15.0, 20.0, 10.8);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.745 , 0.729 , 0.717);
    glVertex3f(15.0, 20.0 ,12.0);
    glVertex3f(15.0, 20.0, 10.0);
    glVertex3f(15.0, 26.0 ,10.0);
    glVertex3f(15.0, 26.0, 12.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.745 , 0.729 , 0.717);
    glVertex3f(0.0, 20.0 ,12.0);
    glVertex3f(0.0, 20.0, 10.0);
    glVertex3f(0.0, 26.0 ,10.0);
    glVertex3f(0.0, 26.0, 12.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.745 , 0.729 , 0.717);
    glVertex3f(15.0, 26.0 ,12.0);
    glVertex3f(15.0, 26.0, 10.0);
    glVertex3f(0.0, 26.0 ,10.0);
    glVertex3f(0.0, 26.0, 12.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.745 , 0.729 , 0.717);
    glVertex3f(15.0, 20.0 ,10.0);
    glVertex3f(0.0, 20.0, 10.0);
    glVertex3f(0.0, 26.0 ,10.0);
    glVertex3f(15.0, 26.0, 10.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 0.737 ,  0.0  ,  0.0);
    glVertex3f(15.0, 20.0 ,10.0);
    glVertex3f(15.0, 20.0, 0.0);
    glVertex3f(15.0, 26.0 ,0.0);
    glVertex3f(15.0, 26.0, 10.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 0.737 ,  0.0  ,  0.0);
    glVertex3f(0.0, 20.0 ,10.0);
    glVertex3f(0.0, 20.0, 0.0);
    glVertex3f(0.0, 26.0 ,0.0);
    glVertex3f(0.0, 26.0, 10.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 0.737 ,  0.0  ,  0.0);
    glVertex3f(0.0, 26.0 ,10.0);
    glVertex3f(0.0, 26.0, 0.0);
    glVertex3f(15.0, 26.0 ,0.0);
    glVertex3f(15.0, 26.0, 10.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 0.360 , 0.345 , 0.349);
    glVertex3f(0.0, 26.0 ,0.0);
    glVertex3f(15.0, 26.0, 0.0);
    glVertex3f(15.0, 20.0 ,0.0);
    glVertex3f(0.0, 20.0, 0.0);
	glEnd();
	
	
	//PISO DEL SEGUNDO PISO
	glBegin(GL_POLYGON);
    glColor3f(0.850 , 0.780 , 0.6);
    glVertex3f(0.0, 1.70 ,12.0);
    glVertex3f(15.0, 1.70, 12.0);
    glVertex3f(15.0, 20.0 ,12.0);
    glVertex3f(0.0, 20.0, 12.0);
	glEnd();
	
	//BASE DEL SEGUNDO PISO
	glBegin(GL_POLYGON);
	
    glColor3f(0.745 , 0.725 , 0.709);
    glVertex3f(0.0, 2.0 ,10.8);
    glVertex3f(15.0, 2.0, 10.8);
    glVertex3f(15.0, 20.0 ,10.8);
    glVertex3f(0.0, 20.0, 10.8);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.745 , 0.725 , 0.709);
    glVertex3f(0.0, 2.0 ,12.0);
    glVertex3f(0.0, 2.0, 10.8);
    glVertex3f(15.0, 2.0 ,10.8);
    glVertex3f(15.0, 2.0, 12.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.745 , 0.725 , 0.709);
    glVertex3f(0.0, 20.0 ,12.0);
    glVertex3f(0.0, 20.0, 10.8);
    glVertex3f(15.0, 20.0 ,10.8);
    glVertex3f(15.0, 20.0, 12.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.745 , 0.725 , 0.709);
    glVertex3f(15.0, 2.0 ,12.0);
    glVertex3f(15.0, 2.0, 10.8);
    glVertex3f(15.0, 20.0 ,10.8);
    glVertex3f(15.0, 20.0, 12.0);
	glEnd();
	
	
	//Columna1
	glBegin(GL_POLYGON);
    glColor3f(0.109 , 0.094 , 0.090);
    glVertex3f(1.0, 2.0 ,10.8);
    glVertex3f(1.0, 2.0, 0.0);
    glVertex3f(1.0, 3.0 ,0.0);
    glVertex3f(1.0, 3.0, 10.8);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.109 , 0.094 , 0.090);
    glVertex3f(0.0, 2.0 ,10.8);
    glVertex3f(0.0, 2.0, 0.0);
    glVertex3f(1.0, 2.0 ,0.0);
    glVertex3f(1.0, 2.0, 10.8);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.109 , 0.094 , 0.090);
    glVertex3f(1.0, 3.0 ,10.8);
    glVertex3f(1.0, 3.0, 0.0);
    glVertex3f(0.0, 3.0 ,0.0);
    glVertex3f(0.0, 3.0, 10.8);
	glEnd();
	
	
	//Columna2
	
	glBegin(GL_POLYGON);
    glColor3f(0.109 , 0.094 , 0.090);
    glVertex3f(15.0, 3.0 ,10.8);
    glVertex3f(15.0, 3.0, 0.0);
    glVertex3f(14.0, 3.0 ,0.0);
    glVertex3f(14.0, 3.0, 10.8);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.109 , 0.094 , 0.090);
    glVertex3f(14.0, 3.0 ,10.8);
    glVertex3f(14.0, 3.0, 0.0);
    glVertex3f(14.0, 2.0 ,0.0);
    glVertex3f(14.0, 2.0, 10.8);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.109 , 0.094 , 0.090);
    glVertex3f(14.0, 2.0 ,10.8);
    glVertex3f(14.0, 2.0, 0.0);
    glVertex3f(15.0, 2.0 ,0.0);
    glVertex3f(15.0, 2.0, 10.8);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.109 , 0.094 , 0.090);
    glVertex3f(0.0, 20.0 ,0.0);
    glVertex3f(0.0, -20.0, 0.0);
    glVertex3f(-20.0, -20.0 ,0.0);
    glVertex3f(-20.0, 20.0, 0.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.745 , 0.729 , 0.717);
    glVertex3f(-5.0, -10.0 ,12.0);
    glVertex3f(-5.0, -20.0, 12.0);
    glVertex3f(-5.0, -20.0 , 0.0);
    glVertex3f(-5.0, -10.0, 0.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.745 , 0.729 , 0.717);
    glVertex3f(-5.0, -10.0 ,12.0);
    glVertex3f(-5.0, -6.0, 12.0);
    glVertex3f(-5.0, -6.0 , 8.0);
    glVertex3f(-5.0, -10.0, 8.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.745 , 0.729 , 0.717);
    glVertex3f(-5.0, 0.0 ,12.0);
    glVertex3f(-5.0, -6.0, 12.0);
    glVertex3f(-5.0, -6.0 , 0.0);
    glVertex3f(-5.0, 0.0, 0.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.745 , 0.729 , 0.717);
    glVertex3f(-20.0, -20.0 ,12.0);
    glVertex3f(-20.0, 0.0, 12.0);
    glVertex3f(-20.0, 0.0 , 0.0);
    glVertex3f(-20.0, -20.0, 0.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.745 , 0.729 , 0.717);
    glVertex3f(-20.0, 0.0 ,0.0);
    glVertex3f(-20.0, 0.0, 12.0);
    glVertex3f(-5.0, 0.0 , 12.0);
    glVertex3f(-5.0, 0.0, 0.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.745 , 0.729 , 0.717);
    glVertex3f(-20.0, -20.0 , 12.0);
    glVertex3f(-5.0, -20.0, 12.0);
    glVertex3f(-5.0, 0.0 , 12.0);
    glVertex3f(-20.0, 0.0, 12.0);
	glEnd();
	
	glBegin(GL_LINE_STRIP);
    glColor3f(0.0 , 0.0 , 0.0);
    glVertex3f(-20.0, -19.99 ,11.99);
    glVertex3f(-20.0, -0.01, 11.99);
	glEnd();
	
	glBegin(GL_LINE_STRIP);
    glColor3f(0.0 , 0.0 , 0.0);
    glVertex3f(-20.0, -0.01 ,11.99);
    glVertex3f(-5.0, -0.01, 11.99);
	glEnd();
	
	glBegin(GL_LINE_STRIP);
    glColor3f(0.0 , 0.0 , 0.0);
    glVertex3f(-5.0, -0.01 ,11.99);
    glVertex3f(-5.0, -19.99, 11.99);
	glEnd();
	
	glBegin(GL_LINE_STRIP);
    glColor3f(0.0 , 0.0 , 0.0);
    glVertex3f(-5.0, -19.99 ,11.99);
    glVertex3f(-20.0, -19.99, 11.99);
	glEnd();
	
	glBegin(GL_LINE_STRIP);
    glColor3f(0.0 , 0.0 , 0.0);
    glVertex3f(-5.0, -0.01 ,11.99);
    glVertex3f(-5.0, -0.01 ,0.0);
	glEnd();
	
	glBegin(GL_LINE_STRIP);
    glColor3f(0.0 , 0.0 , 0.0);
    glVertex3f(-20.0, -0.01 ,11.99);
    glVertex3f(-20.0, -0.01 ,0.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.745 , 0.729 , 0.717);
    glVertex3f(-5.0, -20.0 , 0.0);
    glVertex3f(-5.0, -40.0, 0.0);
    glVertex3f(0.0, -40.0 , 0.0);
    glVertex3f(0.0, -20.0, 0.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.509 , 0.768 , 0.250);
    glVertex3f(-20.0, -20.0 , 0.0);
    glVertex3f(-20.0, -40.0, 0.0);
    glVertex3f(-5.0, -40.0 , 0.0);
    glVertex3f(-5.0, -20.0, 0.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.509 , 0.768 , 0.250);
    glVertex3f(-19.9, -40.0 , -0.01);
    glVertex3f(-19.9, 40.0, -0.01);
    glVertex3f(-22.0, 40.0 , -0.01);
    glVertex3f(-22.0, -40.0, -0.01);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.509 , 0.768 , 0.250);
    glVertex3f(15.0, -40.0 , 0.0);
    glVertex3f(0.0, -40.0, 0.0);
    glVertex3f(0.0, -20.0 , 0.0);
    glVertex3f(15.0, -20.0, 0.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.509 , 0.768 , 0.250);
    glVertex3f(-20.0, 40.0 , -0.01);
    glVertex3f(15.0, 40.0, -0.01);
    glVertex3f(15.0, 20.0 , -0.01);
    glVertex3f(-20.0, 20.0, -0.01);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.509 , 0.768 , 0.250);
    glVertex3f(15.0, -40.0 , 0.0);
    glVertex3f(0.0, -40.0, 0.0);
    glVertex3f(0.0, -20.0 , 0.0);
    glVertex3f(15.0, -20.0, 0.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.988 , 0.901 , 0.501);
    glVertex3f(-20.0, 40.0 , 0.0);
    glVertex3f(15.0, 40.0, 0.0);
    glVertex3f(15.0, 120.0 , 0.0);
    glVertex3f(-20.0, 120.0, 0.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.988 , 0.901 , 0.501);
    glVertex3f(-19.9, 40.0 , -0.01);
    glVertex3f(-22.0, 40.0, -0.01);
    glVertex3f(-22.0, 135.0 , -0.01);
    glVertex3f(-19.9, 135.0, -0.01);
	glEnd();
	
	
	glBegin(GL_POLYGON);
    glColor3f(0.988 , 0.901 , 0.501);
    glVertex3f(-20.0, 120.0 , 0.0);
    glVertex3f(15.0, 120.0, 0.0);
    glVertex3f(15.0, 150.0 , -0.01);
    glVertex3f(-20.0, 150.0, -0.01);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.019 , 0.831 , 0.956);
    glVertex3f(15.0, 135.0 , 0.0);
    glVertex3f(-20.0, 135.0, 0.0);
    glVertex3f(-20.0, 200.0 , 0.0);
    glVertex3f(15.0, 200.0, 0.0);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.019 , 0.831 , 0.956);
    glVertex3f(-19.9, 135.0 , -0.01);
    glVertex3f(-22.0, 135.0, -0.01);
    glVertex3f(-22.0, 200.0 , -0.01);
    glVertex3f(-19.9, 200.0, -0.01);
	glEnd();
	
	glBegin(GL_LINE_STRIP);
    glColor3f(0.0 , 0.0 , 0.0);
    glVertex3f(0.0, -24.0 ,0.01);
    glVertex3f(-5.0, -24.0 ,0.01);
	glEnd();
	
	glBegin(GL_LINE_STRIP);
    glColor3f(0.0 , 0.0 , 0.0);
    glVertex3f(0.0, -28.0 ,0.01);
    glVertex3f(-5.0, -28.0 ,0.01);
	glEnd();
	
	glBegin(GL_LINE_STRIP);
    glColor3f(0.0 , 0.0 , 0.0);
    glVertex3f(0.0, -32.0 ,0.01);
    glVertex3f(-5.0, -32.0 ,0.01);
	glEnd();
	
	glBegin(GL_LINE_STRIP);
    glColor3f(0.0 , 0.0 , 0.0);
    glVertex3f(0.0, -36.0 ,0.01);
    glVertex3f(-5.0, -36.0 ,0.01);
	glEnd();
	
	glBegin(GL_LINE_STRIP);
    glColor3f(0.0 , 0.0 , 0.0);
    glVertex3f(0.0, -40.0 ,0.01);
    glVertex3f(-5.0, -40.0 ,0.01);
	glEnd();
	
	glBegin(GL_LINE_STRIP);
    glColor3f(0.0 , 0.0 , 0.0);
    glVertex3f(-5.0, -20.0 ,0.01);
    glVertex3f(0.0, -20.0 ,0.01);
    glVertex3f(0.0, -40.0 ,0.01);
    glVertex3f(-5.0, -40.0 ,0.01);
    glVertex3f(-5.0, -20.0 ,0.01);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.745 , 0.729 , 0.717);
    glVertex3f(-16.0, -23.0 , 0.01);
    glVertex3f(-14.0, -23.0, 0.01);
    glVertex3f(-14.0, -25.0 , 0.01);
    glVertex3f(-16.0, -25.0, 0.01);
	glEnd();
	
	glBegin(GL_LINE_STRIP);
    glColor3f(0.0 , 0.0 , 0.0);
    glVertex3f(-16.0, -23.0 , 0.01);
    glVertex3f(-14.0, -23.0, 0.01);
    glVertex3f(-14.0, -25.0 , 0.01);
    glVertex3f(-16.0, -25.0, 0.01);
    glVertex3f(-16.0, -23.0 , 0.01);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.745 , 0.729 , 0.717);
    glVertex3f(-9.0, -23.0 , 0.01);
    glVertex3f(-11.0, -23.0, 0.01);
    glVertex3f(-11.0, -25.0 , 0.01);
    glVertex3f(-9.0, -25.0, 0.01);
	glEnd();
	
	glBegin(GL_LINE_STRIP);
    glColor3f(0.0 , 0.0 , 0.0);
    glVertex3f(-9.0, -23.0 , 0.01);
    glVertex3f(-11.0, -23.0, 0.01);
    glVertex3f(-11.0, -25.0 , 0.01);
    glVertex3f(-9.0, -25.0, 0.01);
    glVertex3f(-9.0, -23.0 , 0.01);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.745 , 0.729 , 0.717);
    glVertex3f(-16.0, -28.0 , 0.01);
    glVertex3f(-14.0, -28.0, 0.01);
    glVertex3f(-14.0, -31.0 , 0.01);
    glVertex3f(-16.0, -31.0, 0.01);
	glEnd();
	
	glBegin(GL_LINE_STRIP);
    glColor3f(0.0 , 0.0 , 0.0);
    glVertex3f(-16.0, -28.0 , 0.01);
    glVertex3f(-14.0, -28.0, 0.01);
    glVertex3f(-14.0, -31.0 , 0.01);
    glVertex3f(-16.0, -31.0, 0.01);
    glVertex3f(-16.0, -28.0 , 0.01);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.745 , 0.729 , 0.717);
    glVertex3f(-9.0, -28.0 , 0.01);
    glVertex3f(-11.0, -28.0, 0.01);
    glVertex3f(-11.0, -31.0 , 0.01);
    glVertex3f(-9.0, -31.0, 0.01);
	glEnd();
	
	glBegin(GL_LINE_STRIP);
    glColor3f(0.0 , 0.0 , 0.0);
    glVertex3f(-9.0, -28.0 , 0.01);
    glVertex3f(-11.0, -28.0, 0.01);
    glVertex3f(-11.0, -31.0 , 0.01);
    glVertex3f(-9.0, -31.0, 0.01);
    glVertex3f(-9.0, -28.0 , 0.01);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.745 , 0.729 , 0.717);
    glVertex3f(-16.0, -34.0 , 0.01);
    glVertex3f(-14.0, -34.0, 0.01);
    glVertex3f(-14.0, -37.0 , 0.01);
    glVertex3f(-16.0, -37.0, 0.01);
	glEnd();
	
	glBegin(GL_LINE_STRIP);
    glColor3f(0.0 , 0.0 , 0.0);
    glVertex3f(-16.0, -34.0 , 0.01);
    glVertex3f(-14.0, -34.0, 0.01);
    glVertex3f(-14.0, -37.0 , 0.01);
    glVertex3f(-16.0, -37.0, 0.01);
    glVertex3f(-16.0, -34.0 , 0.01);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.745 , 0.729 , 0.717);
    glVertex3f(-9.0, -34.0 , 0.01);
    glVertex3f(-11.0, -34.0, 0.01);
    glVertex3f(-11.0, -37.0 , 0.01);
    glVertex3f(-9.0, -37.0, 0.01);
	glEnd();
	
	glBegin(GL_LINE_STRIP);
    glColor3f(0.0 , 0.0 , 0.0);
    glVertex3f(-9.0, -34.0 , 0.01);
    glVertex3f(-11.0, -34.0, 0.01);
    glVertex3f(-11.0, -37.0 , 0.01);
    glVertex3f(-9.0, -37.0, 0.01);
    glVertex3f(-9.0, -34.0 , 0.01);
	glEnd();
	
	glBegin(GL_LINE_STRIP);
    glColor3f(0.0 , 0.0 , 0.0);
    glVertex3f(1.0, -11.5 ,2.601);
    glVertex3f(1.0, -12.0, 2.601);
    glVertex3f(4.0, -12.0 ,2.601);
    glVertex3f(4.0, -11.5, 2.601);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.745 , 0.729 , 0.717);
    glVertex3f(-20.0, -20.0, 0.0);
    glVertex3f(-20.0, -20.0 , 12.0);
    glVertex3f(-18.5, -20.0, 12.0);
    glVertex3f(-18.5, -20.0, 0.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.745 , 0.729 , 0.717);
    glVertex3f(-5.0, -20.0, 0.0);
    glVertex3f(-5.0, -20.0 , 12.0);
    glVertex3f(-6.5, -20.0, 12.0);
    glVertex3f(-6.5, -20.0, 0.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.745 , 0.729 , 0.717);
    glVertex3f(-18.5, -20.0, 10.0);
	glVertex3f(-18.5, -20.0, 12.0);
    glVertex3f(-6.5, -20.0, 12.0);
    glVertex3f(-6.5, -20.0, 10.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.462 , 0.282 , 0.180);
    glVertex3f(-18.5, -20.0, 10.0);
	glVertex3f(-18.5, -20.0, 0.0);
    glVertex3f(-6.5, -20.0, 0.0);
    glVertex3f(-6.5, -20.0, 10.0);
	glEnd();
	
	//Lineas para notar bordes
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(15.0,-19.99 ,0.01);
    glVertex3f(0.0, -19.99, 0.01);
	glEnd();
	
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0.01,20.0 ,0.01);
    glVertex3f(0.01, -20.0, 0.01);
	glEnd();
	
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(15.0,19.99 ,0.01);
    glVertex3f(0.0, 19.99, 0.01);
	glEnd();
	
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(14.99,-20.0 ,0.01);
    glVertex3f(14.99, 20.0, 0.01);
	glEnd();
	
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE);
	glVertex3f(0.01,-19.99 ,0.00);
    glVertex3f(0.01, -19.99, 23.0);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(15.0,1.999 ,10.79);
    glVertex3f(0.0, 1.999, 10.79);
	glEnd();
	
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(15.0,1.99 ,11.99);
    glVertex3f(0.0, 1.99, 11.99);
	glEnd();
	
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0.0,1.99 ,11.999);
    glVertex3f(0.0, 1.99,10.799);
	glEnd();
	
	glBegin(GL_LINE_STRIP);
    glColor3f(0.0 , 0.0 , 0.0);
    glVertex3f(1.0, -14.0 ,1.151);
    glVertex3f(4.0, -14.0, 1.151);
    glVertex3f(4.0, -12.0 ,1.151);
    glVertex3f(1.0, -12.0, 1.151);
	glEnd();
	
	glBegin(GL_LINE_STRIP);
    glColor3f(0.0 , 0.0 , 0.0);
    glVertex3f(1.0, -11.5 ,2.601);
    glVertex3f(1.0, -12.0, 2.601);
    glVertex3f(4.0, -12.0 ,2.601);
    glVertex3f(4.0, -11.5, 2.601);
	glEnd();
	
	glBegin(GL_LINE_STRIP);
    glColor3f(0.0 , 0.0 , 0.0);
    glVertex3f(1.0, -11.5 ,2.6);
    glVertex3f(4.0, -11.5, 2.6);
	glEnd();
	
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
    glVertex3f(4.0, -12.0 , 2.6);
    glVertex3f(4.0, -12.0, 1.15);
	glEnd();
	
	
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(0.5, -18.5 ,2.61);
    glVertex3f(1.0, -18.5, 2.61);
    glVertex3f(1.0, -11.5, 2.61);
    glVertex3f(0.5, -11.5 ,2.6);
	glEnd();
	
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(0.01, 20.0 ,12.01);
    glVertex3f(14.99, 20.0, 12.01);
    glVertex3f(14.99, 25.98, 12.01);
    glVertex3f(0.01, 25.98 ,12.01);
    glVertex3f(0.01, 20.0 ,12.01);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(0.01, 25.99 ,12.0);
    glVertex3f(0.01, 25.99 ,16.0);
	glEnd();
	
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(14.99, 25.98 ,12.0);
    glVertex3f(14.99, 25.98 ,16.0);
	glEnd();
	glPopMatrix();
}

void vereda(){
	glBegin(GL_POLYGON);
    glColor3f(0.745 , 0.729 , 0.717);
    glVertex3f(-20.0, -44.0 , 0.0);
    glVertex3f(15.0, -44.0, 0.0);
    glVertex3f(15.0, -40.0 , 0.0);
    glVertex3f(-20.0, -40.0, 0.0);
	glEnd();
	
	glBegin(GL_LINES);
    glColor3f(0.0 , 0.0 , 0.0);
    glVertex3f(15.0, -40.0 , 0.0);
    glVertex3f(-20.0, -40.0, 0.0);
	glEnd();
	
	glBegin(GL_LINES);
	glVertex3f(-20.0, -44.0 , 0.0);
    glVertex3f(15.0, -44.0, 0.0);
	glEnd();
}

void PT(){
	glBegin(GL_POLYGON);
	glColor3f(0.545 , 0.368 , 0.231);
    glVertex3f(-6.1, 40.0 , 0.0);
    glVertex3f(-10.1, 40.0, 0.0);
    glVertex3f(-10.1, 40.0 , 4.0);
    glVertex3f(-8.1, 40.0, 5.0);
    glVertex3f(-6.1, 40.0 , 4.0);
	glEnd();
	
	glBegin(GL_LINE_STRIP);
    glColor3f(0.0 , 0.0 , 0.0);
    glVertex3f(-6.1, 40.0 , 0.0);
    glVertex3f(-10.1, 40.0, 0.0);
    glVertex3f(-10.1, 40.0 , 4.0);
    glVertex3f(-8.1, 40.0, 5.0);
    glVertex3f(-6.1, 40.0 , 4.0);
    glVertex3f(-6.1, 40.0 , 0.0);
	glEnd();
}


void muebleJara(){
	
	//SILLON DE 3
	glBegin(GL_POLYGON);
    glColor3f(0.866f , 0.639f , 0.250f);
    glVertex3f(1.0, -14.0 ,0.01);
    glVertex3f(4.0, -14.0, 0.01);
    glVertex3f(4.0, -12.0 ,0.01);
    glVertex3f(1.0, -12.0, 0.01);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.866f , 0.639f , 0.250f);
    glVertex3f(1.0, -14.0 ,1.15);
    glVertex3f(4.0, -14.0, 1.15);
    glVertex3f(4.0, -12.0 ,1.15);
    glVertex3f(1.0, -12.0, 1.15);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.866f , 0.639f , 0.250f);
    glVertex3f(1.0, -14.0 ,1.15);
    glVertex3f(1.0, -14.0, 0.0);
    glVertex3f(1.0, -12.0 ,0.0);
    glVertex3f(1.0, -12.0, 1.15);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.866f , 0.639f , 0.250f);
    glVertex3f(4.0, -14.0 ,1.15);
    glVertex3f(4.0, -14.0, 0.0);
    glVertex3f(4.0, -12.0 ,0.0);
    glVertex3f(4.0, -12.0, 1.15);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.866f , 0.639f , 0.250f);
    glVertex3f(1.0, -14.0 ,1.15);
    glVertex3f(1.0, -14.0, 0.0);
    glVertex3f(4.0, -14.0 ,0.0);
    glVertex3f(4.0, -14.0, 1.15);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.866f , 0.639f , 0.250f);
    glVertex3f(1.0, -12.0 ,2.6);
    glVertex3f(1.0, -12.0, 0.0);
    glVertex3f(4.0, -12.0 ,0.0);
    glVertex3f(4.0, -12.0, 2.6);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.866f , 0.639f , 0.250f);
    glVertex3f(1.0, -11.5 ,2.6);
    glVertex3f(1.0, -11.5, 0.0);
    glVertex3f(4.0, -11.5 ,0.0);
    glVertex3f(4.0, -11.5, 2.6);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.866f , 0.639f , 0.250f);
    glVertex3f(1.0, -12.0 ,2.6);
    glVertex3f(1.0, -12.0, 0.0);
    glVertex3f(1.0, -11.5 ,0.0);
    glVertex3f(1.0, -11.5, 2.6);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.866f , 0.639f , 0.250f);
    glVertex3f(1.0, -11.5 ,2.6);
    glVertex3f(1.0, -12.0, 2.6);
    glVertex3f(4.0, -12.0 ,2.6);
    glVertex3f(4.0, -11.5, 2.6);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.866f , 0.639f , 0.250f);
    glVertex3f(4.0, -11.5 ,2.6);
    glVertex3f(4.0, -11.5, 0.0);
    glVertex3f(4.0, -12.0, 0.0);
    glVertex3f(4.0, -12.0 ,2.6);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.866f , 0.639f , 0.250f);
    glVertex3f(0.5, -18.5 ,2.6);
    glVertex3f(0.5, -18.5, 0.0);
    glVertex3f(0.5, -11.5, 0.0);
    glVertex3f(0.5, -11.5 ,2.6);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.866f , 0.639f , 0.250f);
    glVertex3f(0.5, -18.5 ,2.6);
    glVertex3f(1.0, -18.5, 2.6);
    glVertex3f(1.0, -11.5, 2.6);
    glVertex3f(0.5, -11.5 ,2.6);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.866f , 0.639f , 0.250f);
    glVertex3f(0.5, -18.5 ,0.0);
    glVertex3f(1.0, -18.5, 0.0);
    glVertex3f(1.0, -18.5, 2.6);
    glVertex3f(0.5, -18.5 ,2.6);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f( 0.866 , 0.639 , 0.250 );
    glColor3f(0.866f , 0.639f , 0.250f);
    glVertex3f(0.5, -18.5 ,0.0);
    glVertex3f(1.0, -18.5, 0.0);
    glVertex3f(1.0, -18.5, 2.6);
    glVertex3f(0.5, -18.5 ,2.6);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f( 0.866 , 0.639 , 0.250 );
    glColor3f(0.866f , 0.639f , 0.250f);
    glVertex3f(0.5, -11.5 ,0.0);
    glVertex3f(0.5, -11.5, 2.6);
    glVertex3f(1.0, -11.5, 2.6);
    glVertex3f(1.0, -11.5 ,0.0);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f( 0.866 , 0.639 , 0.250 );
    glColor3f(0.866f , 0.639f , 0.250f);
    glVertex3f(1.0, -18.5, 2.6);
    glVertex3f(1.0, -18.5, 0.0);
    glVertex3f(1.0, -11.5, 0.0);
    glVertex3f(1.0, -11.5 ,2.6);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f( 0.866 , 0.639 , 0.250 );
    glColor3f(0.866f , 0.639f , 0.250f);
    glVertex3f(1.0, -18.5, 2.6);
    glVertex3f(1.0, -18.5, 0.0);
    glVertex3f(4.0, -18.5, 0.0);
    glVertex3f(4.0, -18.5 ,2.6);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f( 0.866 , 0.639 , 0.250 );
    glColor3f(0.866f , 0.639f , 0.250f);
    glVertex3f(1.0, -18.0, 2.6);
    glVertex3f(1.0, -18.0, 0.0);
    glVertex3f(4.0, -18.0, 0.0);
    glVertex3f(4.0, -18.0 ,2.6);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f( 0.866 , 0.639 , 0.250 );
    glColor3f(0.866f , 0.639f , 0.250f);
    glVertex3f(4.0, -18.5, 2.6);
    glVertex3f(4.0, -18.5, 0.0);
    glVertex3f(4.0, -18.0, 0.0);
    glVertex3f(4.0, -18.0 ,2.6);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f( 0.866 , 0.639 , 0.250 );
    glColor3f(0.866f , 0.639f , 0.250f);
    glVertex3f(4.0, -18.0, 1.15);
    glVertex3f(4.0, -18.0, 0.0);
    glVertex3f(4.0, -16.0, 0.0);
    glVertex3f(4.0, -16.0 ,1.15);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f( 0.866 , 0.639 , 0.250 );
    glColor3f(0.866f , 0.639f , 0.250f);
    glVertex3f(1.0, -18.0, 1.15);
    glVertex3f(4.0, -18.0, 1.15);
    glVertex3f(4.0, -16.0, 1.15);
    glVertex3f(1.0, -16.0 ,1.15);
	glEnd();
	
	glBegin(GL_POLYGON);
   	glColor3f(0.866f , 0.639f , 0.250f);
    glVertex3f(1.0, -16.0, 1.15);
    glVertex3f(4.0, -16.0, 1.15);
    glVertex3f(4.0, -14.0, 1.15);
    glVertex3f(1.0, -14.0 ,1.15);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.866f , 0.639f , 0.250f);
    glVertex3f(4.0, -16.0, 1.15);
    glVertex3f(4.0, -16.0, 0.0);
    glVertex3f(4.0, -14.0, 0.0);
    glVertex3f(4.0, -14.0 ,1.15);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.866f , 0.639f , 0.250f);
    glVertex3f(4.0, -18.5, 2.6);
    glVertex3f(1.0, -18.5, 2.6);
    glVertex3f(1.0, -18.0, 2.6);
    glVertex3f(4.0, -18.0 ,2.6);
	glEnd();
	
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(1.0, -16.0, 1.151);
    glVertex3f(4.0, -16.0, 1.151);
    glVertex3f(4.0, -14.0, 1.151);
    glVertex3f(1.0, -14.0 ,1.151);
	glVertex3f(1.0, -16.0, 1.151);   
	glEnd();
	
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(1.0, -18.0, 1.151);
    glVertex3f(4.0, -18.0, 1.151);
    glVertex3f(4.0, -16.0, 1.151);
    glVertex3f(1.0, -16.0 ,1.151);
    glVertex3f(1.0, -18.0, 1.151);
	glEnd();
	
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(1.0, -11.5 ,2.6);
    glVertex3f(1.0, -12.0, 2.6);
    glVertex3f(4.0, -12.0 ,2.6);
    glVertex3f(4.0, -11.5, 2.6);
    glVertex3f(1.0, -11.5 ,2.6);
	glEnd();
	
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(4.0, -18.5, 2.6);
    glVertex3f(1.0, -18.5, 2.6);
    glVertex3f(1.0, -18.0, 2.6);
    glVertex3f(4.0, -18.0 ,2.6);
    glVertex3f(4.0, -18.5, 2.6);
	glEnd();
	
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(4.0, -18.0, 2.6);
    glVertex3f(4.0, -18.0, 1.15);
	glEnd();
	
}


void CamaJ(){
	
	glTranslatef(0.0f, 2.0f, 0.0f);//TRASLADADO
	
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0 , 0.0 ,  0.0);
    glVertex3f(2.5, 5.0, 13.51);
    glVertex3f(2.5, 15.0, 13.51);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.043 , 0.023 ,  0.0);
    glVertex3f(0.0, 5.0, 12.5);
    glVertex3f(10.0, 5.0, 12.5);
    glVertex3f(10.0, 15.0, 12.5);
    glVertex3f(0.0, 15.0 ,12.5);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.043 , 0.023 ,  0.0);
    glVertex3f(10.0, 5.0, 12.5);
    glVertex3f(10.0, 5.0, 12.0);
    glVertex3f(0.0, 5.0, 12.0);
    glVertex3f(0.0, 5.0 ,12.5);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.043 , 0.023 ,  0.0);
    glVertex3f(10.0, 15.0, 12.5);
    glVertex3f(10.0, 15.0, 12.0);
    glVertex3f(0.0, 15.0, 12.0);
    glVertex3f(0.0, 15.0 ,12.5);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.043 , 0.023 ,  0.0);
    glVertex3f(10.0, 5.0, 12.5);
    glVertex3f(10.0, 5.0, 12.0);
    glVertex3f(10.0, 15.0, 12.0);
    glVertex3f(10.0, 15.0 ,12.5);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.043 , 0.023 ,  0.0);
    glVertex3f(0.2, 5.0, 16.0);
    glVertex3f(0.2, 5.0, 12.5);
    glVertex3f(0.2, 15.0, 12.5);
    glVertex3f(0.2, 15.0 ,16.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.043 , 0.023 ,  0.0);
    glVertex3f(0.0, 5.0, 16.0);
    glVertex3f(0.0, 5.0, 12.5);
    glVertex3f(0.2, 5.0, 12.5);
    glVertex3f(0.2, 5.0 ,16.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.043 , 0.023 ,  0.0);
    glVertex3f(0.0, 15.0, 16.0);
    glVertex3f(0.0, 15.0, 12.5);
    glVertex3f(0.2, 15.0, 12.5);
    glVertex3f(0.2, 15.0 ,16.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.043 , 0.023 ,  0.0);
    glVertex3f(0.0, 5.0, 16.0);
    glVertex3f(0.0, 15.0, 16.0);
    glVertex3f(0.2, 15.0, 16.0);
    glVertex3f(0.2, 5.0 ,16.0);
	glEnd();
	
	//Cama

	glBegin(GL_POLYGON);
    glColor3f(0.917 , 0.901 , 0.858);
    glVertex3f(0.2, 5.1, 13.5);
    glVertex3f(10.0, 5.1, 13.5);
    glVertex3f(10.0, 14.9, 13.5);
    glVertex3f(0.2, 14.9,13.5);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.917 , 0.901 , 0.858);
    glVertex3f(10.0, 5.1, 13.5);
    glVertex3f(10.0, 5.1, 12.5);
    glVertex3f(0.2, 5.1, 12.5);
    glVertex3f(0.2, 5.1,13.5);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.917 , 0.901 , 0.858);
    glVertex3f(10.0, 14.9, 13.5);
    glVertex3f(10.0, 14.9, 12.5);
    glVertex3f(0.2, 14.9, 12.5);
    glVertex3f(0.2, 14.9, 13.5);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(0.917 , 0.901 , 0.858);
    glVertex3f(10.0, 5.1, 13.5);
    glVertex3f(10.0, 5.1, 12.5);
    glVertex3f(10.0, 14.9, 12.5);
    glVertex3f(10.0, 14.9, 13.5);
	glEnd();
}

void Cocinaa(){
	
	glBegin(GL_POLYGON);
    glColor3f( 0.066 , 0.047 , 0.035);
    glVertex3f(3.0, 17.0, 3.5);
    glVertex3f(3.0, 17.0, 0.0);
    glVertex3f(3.0, 20.0, 0.0);
    glVertex3f(3.0, 20.0 ,3.5);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 0.066 , 0.047 , 0.035);
    glVertex3f(0.0, 17.0, 3.5);
    glVertex3f(3.0, 17.0, 3.5);
    glVertex3f(3.0, 20.0, 3.5);
    glVertex3f(0.0, 20.0 ,3.5);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 0.247 , 0.227 , 0.215);
    glVertex3f(0.0, 17.0, 1.0);
    glVertex3f(0.0, 17.0, 0.0);
    glVertex3f(3.0, 17.0, 0.0);
    glVertex3f(3.0, 17.0 ,1.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 0.066 , 0.047 , 0.035);
    glVertex3f(0.01, 17.0, 3.5);
    glVertex3f(0.01, 17.0, 0.0);
    glVertex3f(0.01, 20.0, 0.0);
    glVertex3f(0.01, 20.0 ,3.5);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 0.066 , 0.047 , 0.035);
    glVertex3f(0.0, 20.0, 3.1);
    glVertex3f(0.0, 17.0, 3.1);
    glVertex3f(3.0, 17.0, 3.1);
    glVertex3f(3.0, 20.0 ,3.1);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 0.066 , 0.047 , 0.035);
    glVertex3f(0.0, 19.99, 3.5);
    glVertex3f(0.0, 19.99, 0.0);
    glVertex3f(3.0, 19.99, 0.0);
    glVertex3f(3.0, 19.99 ,3.5);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 0.247 , 0.227 , 0.215);
    glVertex3f(0.0, 20.0, 1.0);
    glVertex3f(0.0, 17.0, 1.0);
    glVertex3f(3.0, 17.0, 1.0);
    glVertex3f(3.0, 20.0 ,1.0);
	glEnd();
	
	
	glBegin(GL_POLYGON);
    glColor3f( 1.0 , 1.0 , 1.0);
    glVertex3f(0.0, 17.0, 3.1);
    glVertex3f(0.0, 17.0, 1.0);
    glVertex3f(0.5, 17.0, 1.0);
    glVertex3f(0.5, 17.0 ,3.1);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 1.0 , 1.0 , 1.0);
    glVertex3f(2.5, 17.0, 3.1);
    glVertex3f(2.5, 17.0, 1.0);
    glVertex3f(3.0, 17.0, 1.0);
    glVertex3f(3.0, 17.0 ,3.1);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 1.0 , 1.0 , 1.0);
    glVertex3f(0.5, 17.0, 1.4);
    glVertex3f(0.5, 17.0, 1.0);
    glVertex3f(3.0, 17.0, 1.0);
    glVertex3f(3.0, 17.0 ,1.4);
	glEnd();

	glBegin(GL_POLYGON);
    glColor3f( 0.0 , 0.0 , 0.0);
    glVertex3f(0.0, 17.0, 3.5);
    glVertex3f(0.0, 17.0, 3.1);
    glVertex3f(3.0, 17.0, 3.1);
    glVertex3f(3.0, 17.0 ,3.5);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 1.0 , 1.0 , 1.0);
    glVertex3f(0.5, 17.0, 3.1);
    glVertex3f(0.5, 17.0, 2.7);
    glVertex3f(2.5, 17.0, 2.7);
    glVertex3f(2.5, 17.0 ,3.1);
	glEnd();
	
	glPushMatrix();
	glRotated(-90, 1,0,0);
	glTranslatef(0.5,-0.6,16.7);
	cilindro = gluNewQuadric();
	glColor3f(0.145 , 0.129 , 0.125);
	gluQuadricDrawStyle(cilindro,GLU_FILL);
	gluCylinder(cilindro,0.04,0.04,0.3,40,20);
	glPopMatrix();
	
	glPushMatrix();
	glRotated(-90, 1,0,0);
	glTranslatef(2.4,-0.6,16.7);
	cilindro = gluNewQuadric();
	glColor3f(0.145 , 0.129 , 0.125);
	gluQuadricDrawStyle(cilindro,GLU_FILL);
	gluCylinder(cilindro,0.04,0.04,0.3,40,20);
	glPopMatrix();
	
	glPushMatrix();
	glRotated(-90, 1,0,0);
	glTranslatef(2.4,-2.9,16.7);
	cilindro = gluNewQuadric();
	glColor3f(0.145 , 0.129 , 0.125);
	gluQuadricDrawStyle(cilindro,GLU_FILL);
	gluCylinder(cilindro,0.04,0.04,0.3,40,20);
	glPopMatrix();
	
	glPushMatrix();
	glRotated(-90, 1,0,0);
	glTranslatef(0.5,-2.9,16.7);
	cilindro = gluNewQuadric();
	glColor3f(0.145 , 0.129 , 0.125);
	gluQuadricDrawStyle(cilindro,GLU_FILL);
	gluCylinder(cilindro,0.04,0.04,0.3,40,20);
	glPopMatrix();
	
	glPushMatrix();
	glRotated(-90, 1,0,0);
	glTranslatef(0.4,-3.3,16.88);
	cilindro = gluNewQuadric();
	glColor3f( 0.525 , 0.525 , 0.517);
	gluQuadricDrawStyle(cilindro,GLU_FILL);
	gluCylinder(cilindro,0.08,0.08,0.132,40,20);
	glPopMatrix();
	
		glPushMatrix();
	glRotated(-90, 1,0,0);
	glTranslatef(0.9,-3.3,16.88);
	cilindro = gluNewQuadric();
	glColor3f( 0.525 , 0.525 , 0.517);
	gluQuadricDrawStyle(cilindro,GLU_FILL);
	gluCylinder(cilindro,0.08,0.08,0.132,40,20);
	glPopMatrix();
	
	glPushMatrix();
	glRotated(-90, 1,0,0);
	glTranslatef(1.45,-3.3,16.88);
	cilindro = gluNewQuadric();
	glColor3f( 0.525 , 0.525 , 0.517);
	gluQuadricDrawStyle(cilindro,GLU_FILL);
	gluCylinder(cilindro,0.08,0.08,0.132,40,20);
	glPopMatrix();
	
	glPushMatrix();
	glRotated(-90, 1,0,0);
	glTranslatef(2.5,-3.3,16.88);
	cilindro = gluNewQuadric();
	glColor3f( 0.525 , 0.525 , 0.517);
	gluQuadricDrawStyle(cilindro,GLU_FILL);
	gluCylinder(cilindro,0.08,0.08,0.132,40,20);
	glPopMatrix();
	
	glPushMatrix();
	glRotated(-90, 1,0,0);
	glTranslatef(2.0,-3.3,16.88);
	cilindro = gluNewQuadric();
	glColor3f( 0.525 , 0.525 , 0.517);
	gluQuadricDrawStyle(cilindro,GLU_FILL);
	gluCylinder(cilindro,0.08,0.08,0.132,40,20);
	glPopMatrix();
	
	glPushMatrix();
	glRotated(0, 1,0,0);
	glTranslatef(0.69,17.8,3.50);
	cilindro = gluNewQuadric();
	glColor3f( 0.525 , 0.525 , 0.517);
	gluQuadricDrawStyle(cilindro,GLU_FILL);
	gluCylinder(cilindro,0.32,0.15,0.052,40,20);
	glPopMatrix();
	
	glPushMatrix();
	glRotated(0, 1,0,0);
	glTranslatef(2.19,17.8,3.50);
	cilindro = gluNewQuadric();
	glColor3f( 0.525 , 0.525 , 0.517);
	gluQuadricDrawStyle(cilindro,GLU_FILL);
	gluCylinder(cilindro,0.32,0.15,0.052,40,20);
	glPopMatrix();
	
	glPushMatrix();
	glRotated(0, 1,0,0);
	glTranslatef(0.69,19.2,3.50);
	cilindro = gluNewQuadric();
	glColor3f( 0.525 , 0.525 , 0.517);
	gluQuadricDrawStyle(cilindro,GLU_FILL);
	gluCylinder(cilindro,0.32,0.15,0.052,40,20);
	glPopMatrix();
	
	glPushMatrix();
	glRotated(0, 1,0,0);
	glTranslatef(2.19,19.2,3.50);
	cilindro = gluNewQuadric();
	glColor3f( 0.525 , 0.525 , 0.517);
	gluQuadricDrawStyle(cilindro,GLU_FILL);
	gluCylinder(cilindro,0.32,0.15,0.052,40,20);
	glPopMatrix();
	
	
	glPushMatrix();
	cilindro = gluNewQuadric();
	glColor3f( 0.525 , 0.525 , 0.517);
	gluQuadricDrawStyle(cilindro,GLU_FILL);
	glTranslatef(0.4,16.75,2.91);
	glRotated(90.0, 0.0,1.0,0.0);
	gluCylinder(cilindro,0.08,0.08,2.20,40,20);
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	cilindro = gluNewQuadric();
	glColor3f( 0.525 , 0.525 , 0.517);
	gluQuadricDrawStyle(cilindro,GLU_FILL);
	glTranslatef(0.4,16.75,0.6);
	glRotated(90.0, 0.0,1.0,0.0);
	gluCylinder(cilindro,0.08,0.08,2.20,40,20);
	glEnd();
	glPopMatrix();
	
}

void LavaderoJ(){
	glBegin(GL_POLYGON);
    glColor3f( 0.168 , 0.070 , 0.054);
    glVertex3f(3.0, 17.0, 6.5);
    glVertex3f(3.0, 20.0, 6.5);
    glVertex3f(8.0, 20.0, 6.5);
    glVertex3f(8.0, 17.0 ,6.5);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(  0.168 , 0.070 , 0.054);
    glVertex3f(3.0, 17.0, 8.5);
    glVertex3f(3.0, 20.0, 8.5);
    glVertex3f(8.0, 20.0, 8.5);
    glVertex3f(8.0, 17.0 ,8.5);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(  0.168 , 0.070 , 0.054);
    glVertex3f(3.0, 19.99, 8.5);
    glVertex3f(3.0, 19.99, 6.5);
    glVertex3f(8.0, 19.99, 6.5);
    glVertex3f(8.0, 19.99 ,8.5);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(  0.168 , 0.070 , 0.054);
    glVertex3f(3.0, 20.0, 8.5);
    glVertex3f(3.0, 20.0, 6.5);
    glVertex3f(3.0, 17.0, 6.5);
    glVertex3f(3.0, 17.0 ,8.5);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f(  0.168 , 0.070 , 0.054);
    glVertex3f(8.0, 20.0, 8.5);
    glVertex3f(8.0, 20.0, 6.5);
    glVertex3f(8.0, 17.0, 6.5);
    glVertex3f(8.0, 17.0 ,8.5);
	glEnd();
	
	
	glBegin(GL_POLYGON);
    glColor3f( 0.066 , 0.047 , 0.035);
    glVertex3f(3.0, 17.0, 0.01);
    glVertex3f(3.0, 20.0, 0.01);
    glVertex3f(8.0, 20.0, 0.01);
    glVertex3f(8.0, 17.0 ,0.01);
	glEnd();
	
	glBegin(GL_LINE_STRIP);
    glColor3f( 1.0 , 1.0 , 1.0);
    glVertex3f(3.0, 17.0, 3.6);
    glVertex3f(3.0, 20.0, 3.6);
    glVertex3f(8.0, 20.0, 3.6);
    glVertex3f(8.0, 17.0 ,3.6);
    glVertex3f(3.0, 17.0, 3.6);
	glEnd();
	
	glBegin(GL_LINE_STRIP);
    glColor3f( 1.0 , 1.0 , 1.0);
    glVertex3f(3.3, 17.4, 3.6);
    glVertex3f(3.3, 19.6, 3.6);
    glVertex3f(6.3, 19.6, 3.6);
    glVertex3f(6.3, 17.4 ,3.6);
    glVertex3f(3.3, 17.4, 3.6);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 0.317 , 0.317 , 0.317);
    glVertex3f(3.0, 17.0, 3.6);
    glVertex3f(3.0, 20.0, 3.6);
    glVertex3f(3.3, 20.0, 3.6);
    glVertex3f(3.3, 17.0 ,3.6);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 0.317 , 0.317 , 0.317);
    glVertex3f(6.3, 17.0, 3.6);
    glVertex3f(6.3, 20.0, 3.6);
    glVertex3f(8.0, 20.0, 3.6);
    glVertex3f(8.0, 17.0 ,3.6);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 0.317 , 0.317 , 0.317);
    glVertex3f(3.3, 20.0, 3.6);
    glVertex3f(3.3, 19.6, 3.6);
    glVertex3f(6.3, 19.6, 3.6);
    glVertex3f(6.3, 20.0 ,3.6);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 0.317 , 0.317 , 0.317);
    glVertex3f(3.3, 17.0, 3.6);
    glVertex3f(3.3, 17.4, 3.6);
    glVertex3f(6.3, 17.4, 3.6);
    glVertex3f(6.3, 17.0 ,3.6);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 0.345 , 0.152 , 0.125);
    glVertex3f(3.01, 17.0, 3.6);
    glVertex3f(3.01, 17.0, 0.0);
    glVertex3f(3.01, 20.0, 0.0);
    glVertex3f(3.01, 20.0 ,3.6);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 0.345 , 0.152 , 0.125);
    glVertex3f(8.0, 17.0, 3.6);
    glVertex3f(8.0, 17.0, 0.0);
    glVertex3f(8.01, 20.0, 0.0);
    glVertex3f(8.01, 20.0 ,3.6);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 0.345 , 0.152 , 0.125);
    glVertex3f(3.0, 19.99, 3.6);
    glVertex3f(3.0, 19.99, 0.0);
    glVertex3f(8.0, 19.99, 0.0);
    glVertex3f(8.0, 19.99 ,3.6);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 0.345 , 0.152 , 0.125);
    glVertex3f(3.0, 19.99, 3.6);
    glVertex3f(3.0, 19.99, 0.0);
    glVertex3f(8.0, 19.99, 0.0);
    glVertex3f(8.0, 19.99 ,3.6);
	glEnd();
	
	glBegin(GL_LINE_STRIP);
    glColor3f( 1.0 , 1.0 , 1.0);
    glVertex3f(3.3, 17.4, 2.7);
    glVertex3f(3.3, 19.6, 2.7);
    glVertex3f(6.3, 19.6, 2.7);
    glVertex3f(6.3, 17.4 ,2.7);
    glVertex3f(3.3, 17.4, 2.7);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 0.317 , 0.317 , 0.317);
    glVertex3f(3.3, 17.4, 2.7);
    glVertex3f(3.3, 19.6, 2.7);
    glVertex3f(6.3, 19.6, 2.7);
    glVertex3f(6.3, 17.4 ,2.7);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 0.317 , 0.317 , 0.317);
    glVertex3f(3.3, 19.6, 3.6);
    glVertex3f(3.3, 19.6, 2.7);
    glVertex3f(6.3, 19.6, 2.7);
    glVertex3f(6.3, 19.6 ,3.6);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 0.317 , 0.317 , 0.317);
    glVertex3f(3.3, 17.4, 3.6);
    glVertex3f(3.3, 17.4, 2.7);
    glVertex3f(6.3, 17.4, 2.7);
    glVertex3f(6.3, 17.4 ,3.6);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 0.317 , 0.317 , 0.317);
    glVertex3f(3.3, 19.6, 3.6);
    glVertex3f(3.3, 19.6, 2.7);
    glVertex3f(3.3, 17.4, 2.7);
    glVertex3f(3.3, 17.4 ,3.6);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 0.317 , 0.317 , 0.317);
    glVertex3f(6.3, 19.6, 3.6);
    glVertex3f(6.3, 19.6, 2.7);
    glVertex3f(6.3, 17.4, 2.7);
    glVertex3f(6.3, 17.4 ,3.6);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 0.345 , 0.152 , 0.125);
    glVertex3f(3.0, 17.0, 3.6);
    glVertex3f(3.0, 17.0, 0.0);
    glVertex3f(8.0, 17.0, 0.0);
    glVertex3f(8.0, 17.0 ,3.6);
	glEnd();

	
}

void R(){
	glBegin(GL_POLYGON);
    glColor3f( 0.525 , 0.525 , 0.517);
    glVertex3f(8.0, 17.0, 0.01);
    glVertex3f(11.0, 17.0, 0.01);
    glVertex3f(11.0, 20.0, 0.01);
    glVertex3f(8.0, 20.0 ,0.01);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 0.525 , 0.525 , 0.517);
    glVertex3f(8.0, 17.0, 7.0);
    glVertex3f(11.0, 17.0, 7.0);
    glVertex3f(11.0, 20.0, 7.0);
    glVertex3f(8.0, 20.0 ,7.0);
	glEnd();

	glBegin(GL_POLYGON);
    glColor3f( 0.525 , 0.525 , 0.517);
    glVertex3f(8.01, 17.0, 7.0);
    glVertex3f(8.01, 17.0, 0.0);
    glVertex3f(8.01, 20.0, 0.0);
    glVertex3f(8.01, 20.0 ,7.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 0.525 , 0.525 , 0.517);
    glVertex3f(11.0, 17.0, 7.0);
    glVertex3f(11.0, 17.0, 0.0);
    glVertex3f(11.0, 20.0, 0.0);
    glVertex3f(11.0, 20.0 ,7.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 0.525 , 0.525 , 0.517);
    glVertex3f(8.0, 19.99, 7.0);
    glVertex3f(8.0, 19.99, 0.0);
    glVertex3f(11.0, 19.99, 0.0);
    glVertex3f(11.0, 19.99 ,7.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 0.325 , 0.321 , 0.305);
    glVertex3f(8.0, 17.0, 2.0);
    glVertex3f(8.0, 17.0, 0.0);
    glVertex3f(11.0, 17.0, 0.0);
    glVertex3f(11.0, 17.0 ,2.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 1.0 , 1.0 , 1.0);
    glVertex3f(9.0, 16.99, 1.7);
    glVertex3f(9.0, 16.99, 1.4);
    glVertex3f(10.0, 16.99, 1.4);
    glVertex3f(10.0, 16.99 ,1.7);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 0.325 , 0.321 , 0.305);
    glVertex3f(8.0, 17.0, 7.0);
    glVertex3f(8.0, 17.0, 2.0);
    glVertex3f(11.0, 17.0, 2.0);
    glVertex3f(11.0, 17.0 ,7.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 1.0 , 1.0 , 1.0);
    glVertex3f(8.2, 16.99, 5.5);
    glVertex3f(8.2, 16.99, 3.8);
    glVertex3f(8.5, 16.99, 3.8);
    glVertex3f(8.5, 16.99 ,5.5);
	glEnd();
	
	glBegin(GL_LINES);
    glColor3f( 1.0 , 1.0 , 1.0);
    glVertex3f(8.0, 16.99, 2.0);
    glVertex3f(11.0, 16.99, 2.0);
	glEnd();
}

void MesaCocina(){
	
	glBegin(GL_POLYGON);
    glColor3f(0.831f , 0.811f , 0.698f);
    glVertex3f(0.0, 7.0, 3.0);
    glVertex3f(10.0, 7.0, 3.0);
    glVertex3f(10.0, 12.0, 3.0);
    glVertex3f(0.0, 12.0 ,3.0);
	glEnd();
	
	glBegin(GL_LINE_STRIP);
    glColor3f( 1.0 , 1.0 , 1.0);
    glVertex3f(0.0, 7.0, 3.0);
    glVertex3f(10.0, 7.0, 3.0);
    glVertex3f(10.0, 12.0, 3.0);
    glVertex3f(0.0, 12.0 ,3.0);
    glVertex3f(0.0, 7.0, 3.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 1.0 , 1.0 , 1.0);
    glVertex3f(0.0, 7.0, 3.0);
    glVertex3f(10.0, 7.0, 3.0);
    glVertex3f(10.0, 12.0, 3.0);
    glVertex3f(0.0, 12.0 ,3.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 1.0 , 1.0 , 1.0);
    glVertex3f(1.0, 8.0, 0.01);
    glVertex3f(1.5, 8.0, 0.01);
    glVertex3f(1.5, 8.5, 0.01);
    glVertex3f(1.0, 8.5 ,0.01);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 0.474 , 0.282 , 0.227);
    glVertex3f(1.0, 8.0, 2.99);
    glVertex3f(1.0, 8.0, 0.0);
    glVertex3f(1.0, 8.5, 0.0);
    glVertex3f(1.0, 8.5 ,2.99);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 0.474 , 0.282 , 0.227);
    glVertex3f(1.5, 8.0, 2.99);
    glVertex3f(1.5, 8.0, 0.0);
    glVertex3f(1.5, 8.5, 0.0);
    glVertex3f(1.5, 8.5 ,2.99);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 0.474 , 0.282 , 0.227);
    glVertex3f(1.0, 8.0, 2.99);
    glVertex3f(1.0, 8.0, 0.0);
    glVertex3f(1.5, 8.0, 0.0);
    glVertex3f(1.5, 8.0 ,2.99);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 0.474 , 0.282 , 0.227);
    glVertex3f(1.0, 8.5, 2.99);
    glVertex3f(1.0, 8.5, 0.0);
    glVertex3f(1.5, 8.5, 0.0);
    glVertex3f(1.5, 8.5 ,2.99);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 1.0 , 1.0 , 1.0);
    glVertex3f(1.0, 11.0, 0.01);
    glVertex3f(1.5, 11.0, 0.01);
    glVertex3f(1.5, 11.5, 0.01);
    glVertex3f(1.0, 11.5 ,0.01);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 0.474 , 0.282 , 0.227);
    glVertex3f(1.0, 11.0, 2.99);
    glVertex3f(1.0, 11.0, 0.0);
    glVertex3f(1.0, 11.5, 0.0);
    glVertex3f(1.0, 11.5 ,2.99);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 0.474 , 0.282 , 0.227);
    glVertex3f(1.5, 11.0, 2.99);
    glVertex3f(1.5, 11.0, 0.0);
    glVertex3f(1.5, 11.5, 0.0);
    glVertex3f(1.5, 11.5 ,2.99);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 0.474 , 0.282 , 0.227);
    glVertex3f(1.0, 11.0, 2.99);
    glVertex3f(1.0, 11.0, 0.0);
    glVertex3f(1.5, 11.0, 0.0);
    glVertex3f(1.5, 11.0 ,2.99);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 0.474 , 0.282 , 0.227);
    glVertex3f(1.0, 11.5, 2.99);
    glVertex3f(1.0, 11.5, 0.0);
    glVertex3f(1.5, 11.5, 0.0);
    glVertex3f(1.5, 11.5 ,2.99);
	glEnd();

	glBegin(GL_POLYGON);
    glColor3f( 1.0 , 1.0 , 1.0);
    glVertex3f(9.0, 8.0, 0.01);
    glVertex3f(9.5, 8.0, 0.01);
    glVertex3f(9.5, 8.5, 0.01);
    glVertex3f(9.0, 8.5 ,0.01);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 0.474 , 0.282 , 0.227);
    glVertex3f(9.0, 8.0, 2.99);
    glVertex3f(9.0, 8.0, 0.0);
    glVertex3f(9.0, 8.5, 0.0);
    glVertex3f(9.0, 8.5 ,2.99);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 0.474 , 0.282 , 0.227);
    glVertex3f(9.5, 8.0, 2.99);
    glVertex3f(9.5, 8.0, 0.0);
    glVertex3f(9.5, 8.5, 0.0);
    glVertex3f(9.5, 8.5 ,2.99);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 0.474 , 0.282 , 0.227);
    glVertex3f(9.0, 8.0, 2.99);
    glVertex3f(9.0, 8.0, 0.0);
    glVertex3f(9.5, 8.0, 0.0);
    glVertex3f(9.5, 8.0 ,2.99);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 0.474 , 0.282 , 0.227);
    glVertex3f(9.0, 8.5, 2.99);
    glVertex3f(9.0, 8.5, 0.0);
    glVertex3f(9.5, 8.5, 0.0);
    glVertex3f(9.5, 8.5 ,2.99);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 9.0 , 1.0 , 1.0);
    glVertex3f(9.0, 11.0, 0.01);
    glVertex3f(9.5, 11.0, 0.01);
    glVertex3f(9.5, 11.5, 0.01);
    glVertex3f(9.0, 11.5 ,0.01);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 0.474 , 0.282 , 0.227);
    glVertex3f(9.0, 11.0, 2.99);
    glVertex3f(9.0, 11.0, 0.0);
    glVertex3f(9.0, 11.5, 0.0);
    glVertex3f(9.0, 11.5 ,2.99);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 0.474 , 0.282 , 0.227);
    glVertex3f(9.5, 11.0, 2.99);
    glVertex3f(9.5, 11.0, 0.0);
    glVertex3f(9.5, 11.5, 0.0);
    glVertex3f(9.5, 11.5 ,2.99);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 0.474 , 0.282 , 0.227);
    glVertex3f(9.0, 11.0, 2.99);
    glVertex3f(9.0, 11.0, 0.0);
    glVertex3f(9.5, 11.0, 0.0);
    glVertex3f(9.5, 11.0 ,2.99);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 0.474 , 0.282 , 0.227);
    glVertex3f(9.0, 11.5, 2.99);
    glVertex3f(9.0, 11.5, 0.0);
    glVertex3f(9.5, 11.5, 0.0);
    glVertex3f(9.5, 11.5 ,2.99);
	glEnd();
}

void escalerasJ(){
	
	glBegin(GL_POLYGON);
    glColor3f( 1.0 , 1.0 , 1.0);
    glVertex3f(15.0, 2.0, 11.0);
    glVertex3f(15.0, 1.0, 11.0);
    glVertex3f(10.0, 1.0, 11.0);
    glVertex3f(10.0, 2.0 ,11.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 1.0 , 1.0 , 1.0);
    glVertex3f(15.0, 1.0, 11.0);
    glVertex3f(15.0, 1.0, 10.0);
    glVertex3f(10.0, 1.0, 10.0);
    glVertex3f(10.0, 1.0, 11.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 1.0 , 1.0 , 1.0);
    glVertex3f(15.0, 1.0, 10.0);
    glVertex3f(15.0, 0.0, 10.0);
    glVertex3f(10.0, 0.0, 10.0);
    glVertex3f(10.0, 1.0 ,10.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 1.0 , 1.0 , 1.0);
    glVertex3f(15.0, 0.0, 10.0);
    glVertex3f(15.0, 0.0, 9.0);
    glVertex3f(10.0, 0.0, 9.0);
    glVertex3f(10.0, 0.0, 10.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 1.0 , 1.0 , 1.0);
    glVertex3f(15.0, 0.0, 9.0);
    glVertex3f(15.0, -1.0, 9.0);
    glVertex3f(10.0, -1.0, 9.0);
    glVertex3f(10.0, 0.0 , 9.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 1.0 , 1.0 , 1.0);
    glVertex3f(15.0, -1.0, 9.0);
    glVertex3f(15.0, -1.0, 8.0);
    glVertex3f(10.0, -1.0, 8.0);
    glVertex3f(10.0, -1.0 , 9.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 1.0 , 1.0 , 1.0);
    glVertex3f(15.0, -1.0, 8.0);
    glVertex3f(15.0, -2.0, 8.0);
    glVertex3f(10.0, -2.0, 8.0);
    glVertex3f(10.0, -1.0 , 8.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 1.0 , 1.0 , 1.0);
    glVertex3f(15.0, -2.0, 8.0);
    glVertex3f(15.0, -2.0, 7.0);
    glVertex3f(10.0, -2.0, 7.0);
    glVertex3f(10.0, -2.0 , 8.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 1.0 , 1.0 , 1.0);
    glVertex3f(15.0, -2.0, 7.0);
    glVertex3f(15.0, -3.0, 7.0);
    glVertex3f(10.0, -3.0, 7.0);
    glVertex3f(10.0, -2.0, 7.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 1.0 , 1.0 , 1.0);
    glVertex3f(15.0, -3.0, 7.0);
    glVertex3f(15.0, -3.0, 6.0);
    glVertex3f(10.0, -3.0, 6.0);
    glVertex3f(10.0, -3.0 ,7.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 1.0 , 1.0 , 1.0);
    glVertex3f(15.0, -3.0, 6.0);
    glVertex3f(15.0, -4.0, 6.0);
    glVertex3f(10.0, -4.0, 6.0);
    glVertex3f(10.0, -3.0, 6.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 1.0 , 1.0 , 1.0);
    glVertex3f(15.0, -4.0, 6.0);
    glVertex3f(15.0, -4.0, 5.0);
    glVertex3f(10.0, -4.0, 5.0);
    glVertex3f(10.0, -4.0, 6.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 1.0 , 1.0 , 1.0);
    glVertex3f(15.0, -4.0, 5.0);
    glVertex3f(15.0, -5.0, 5.0);
    glVertex3f(10.0, -5.0, 5.0);
    glVertex3f(10.0, -4.0, 5.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 1.0 , 1.0 , 1.0);
    glVertex3f(15.0, -5.0, 5.0);
    glVertex3f(15.0, -5.0, 4.0);
    glVertex3f(10.0, -5.0, 4.0);
    glVertex3f(10.0, -5.0, 5.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 1.0 , 1.0 , 1.0);
    glVertex3f(15.0, -5.0, 4.0);
    glVertex3f(15.0, -6.0, 4.0);
    glVertex3f(10.0, -6.0, 4.0);
    glVertex3f(10.0, -5.0, 4.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 1.0 , 1.0 , 1.0);
    glVertex3f(15.0, -6.0, 4.0);
    glVertex3f(15.0, -6.0, 3.0);
    glVertex3f(10.0, -6.0, 3.0);
    glVertex3f(10.0, -6.0, 4.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 1.0 , 1.0 , 1.0);
    glVertex3f(15.0, -6.0, 3.0);
    glVertex3f(15.0, -7.0, 3.0);
    glVertex3f(10.0, -7.0, 3.0);
    glVertex3f(10.0, -6.0, 3.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 1.0 , 1.0 , 1.0);
    glVertex3f(15.0, -7.0, 3.0);
    glVertex3f(15.0, -7.0, 2.0);
    glVertex3f(10.0, -7.0, 2.0);
    glVertex3f(10.0, -7.0, 3.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 1.0 , 1.0 , 1.0);
    glVertex3f(15.0, -7.0, 2.0);
    glVertex3f(15.0, -8.0, 2.0);
    glVertex3f(10.0, -8.0, 2.0);
    glVertex3f(10.0, -7.0, 2.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 1.0 , 1.0 , 1.0);
    glVertex3f(15.0, -8.0, 2.0);
    glVertex3f(15.0, -8.0, 1.0);
    glVertex3f(10.0, -8.0, 1.0);
    glVertex3f(10.0, -8.0, 2.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 1.0 , 1.0 , 1.0);
    glVertex3f(15.0, -8.0, 1.0);
    glVertex3f(15.0, -9.0, 1.0);
    glVertex3f(10.0, -9.0, 1.0);
    glVertex3f(10.0, -8.0, 1.0);
	glEnd();
	
	glBegin(GL_POLYGON);
    glColor3f( 1.0 , 1.0 , 1.0);
    glVertex3f(15.0, -9.0, 1.0);
    glVertex3f(15.0, -9.0, 0.0);
    glVertex3f(10.0, -9.0, 0.0);
    glVertex3f(10.0, -9.0, 1.0);
	glEnd();
	
	
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	glColor3f( 0.0 , 0.0 , 0.0);
	glVertex3f(15.0, 2.0, 11.0);
    glVertex3f(15.0, 1.0, 11.0);
    glVertex3f(10.0, 1.0, 11.0);
    glVertex3f(10.0, 2.0 ,11.0);
    glVertex3f(15.0, 2.0, 11.0);
	glEnd();
	glPopMatrix();
	
	
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	glColor3f( 0.0 , 0.0 , 0.0);
    glVertex3f(15.0, 1.0, 11.0);
    glVertex3f(15.0, 1.0, 10.0);
    glVertex3f(10.0, 1.0, 10.0);
    glVertex3f(10.0, 1.0, 11.0);
    glVertex3f(15.0, 1.0, 11.0);
	glEnd();
	glPopMatrix();
	
	
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	glColor3f( 0.0 , 0.0 , 0.0);
    glVertex3f(15.0, 1.0, 10.0);
    glVertex3f(15.0, 0.0, 10.0);
    glVertex3f(10.0, 0.0, 10.0);
    glVertex3f(10.0, 1.0 ,10.0);
	glEnd();
	glPopMatrix();
	
	
	glPushMatrix();	
	glBegin(GL_LINE_STRIP);
	glColor3f( 0.0 , 0.0 , 0.0);
    glVertex3f(15.0, 0.0, 10.0);
    glVertex3f(15.0, 0.0, 9.0);
    glVertex3f(10.0, 0.0, 9.0);
    glVertex3f(10.0, 0.0, 10.0);
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	glColor3f( 0.0 , 0.0 , 0.0);
    glVertex3f(15.0, 0.0, 9.0);
    glVertex3f(15.0, -1.0, 9.0);
    glVertex3f(10.0, -1.0, 9.0);
    glVertex3f(10.0, 0.0 , 9.0);
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	glColor3f( 0.0 , 0.0 , 0.0);
    glVertex3f(15.0, -1.0, 9.0);
    glVertex3f(15.0, -1.0, 8.0);
    glVertex3f(10.0, -1.0, 8.0);
    glVertex3f(10.0, -1.0 , 9.0);
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	glColor3f( 0.0 , 0.0 , 0.0);
    glVertex3f(15.0, -1.0, 8.0);
    glVertex3f(15.0, -2.0, 8.0);
    glVertex3f(10.0, -2.0, 8.0);
    glVertex3f(10.0, -1.0 , 8.0);
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	glColor3f( 0.0 , 0.0 , 0.0);
    glVertex3f(15.0, -2.0, 8.0);
    glVertex3f(15.0, -2.0, 7.0);
    glVertex3f(10.0, -2.0, 7.0);
    glVertex3f(10.0, -2.0 , 8.0);
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	glColor3f( 0.0 , 0.0 , 0.0);
    glVertex3f(15.0, -2.0, 7.0);
    glVertex3f(15.0, -3.0, 7.0);
    glVertex3f(10.0, -3.0, 7.0);
    glVertex3f(10.0, -2.0, 7.0);
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	glColor3f( 0.0 , 0.0 , 0.0);
    glVertex3f(15.0, -3.0, 7.0);
    glVertex3f(15.0, -3.0, 6.0);
    glVertex3f(10.0, -3.0, 6.0);
    glVertex3f(10.0, -3.0 ,7.0);
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	glColor3f( 0.0 , 0.0 , 0.0);
    glVertex3f(15.0, -3.0, 6.0);
    glVertex3f(15.0, -4.0, 6.0);
    glVertex3f(10.0, -4.0, 6.0);
    glVertex3f(10.0, -3.0, 6.0);
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	glColor3f( 0.0 , 0.0 , 0.0);
    glVertex3f(15.0, -4.0, 6.0);
    glVertex3f(15.0, -4.0, 5.0);
    glVertex3f(10.0, -4.0, 5.0);
    glVertex3f(10.0, -4.0, 6.0);
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	glColor3f( 0.0 , 0.0 , 0.0);
    glVertex3f(15.0, -4.0, 5.0);
    glVertex3f(15.0, -5.0, 5.0);
    glVertex3f(10.0, -5.0, 5.0);
    glVertex3f(10.0, -4.0, 5.0);
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	glColor3f( 0.0 , 0.0 , 0.0);
    glVertex3f(15.0, -5.0, 5.0);
    glVertex3f(15.0, -5.0, 4.0);
    glVertex3f(10.0, -5.0, 4.0);
    glVertex3f(10.0, -5.0, 5.0);
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	glColor3f( 0.0 , 0.0 , 0.0);
    glVertex3f(15.0, -5.0, 4.0);
    glVertex3f(15.0, -6.0, 4.0);
    glVertex3f(10.0, -6.0, 4.0);
    glVertex3f(10.0, -5.0, 4.0);
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	glColor3f( 0.0 , 0.0 , 0.0);
    glVertex3f(15.0, -6.0, 4.0);
    glVertex3f(15.0, -6.0, 3.0);
    glVertex3f(10.0, -6.0, 3.0);
    glVertex3f(10.0, -6.0, 4.0);
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	glColor3f( 0.0 , 0.0 , 0.0);
    glVertex3f(15.0, -6.0, 3.0);
    glVertex3f(15.0, -7.0, 3.0);
    glVertex3f(10.0, -7.0, 3.0);
    glVertex3f(10.0, -6.0, 3.0);
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	glColor3f( 0.0 , 0.0 , 0.0);
    glVertex3f(15.0, -7.0, 3.0);
    glVertex3f(15.0, -7.0, 2.0);
    glVertex3f(10.0, -7.0, 2.0);
    glVertex3f(10.0, -7.0, 3.0);
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	glColor3f( 0.0 , 0.0 , 0.0);
    glVertex3f(15.0, -7.0, 2.0);
    glVertex3f(15.0, -8.0, 2.0);
    glVertex3f(10.0, -8.0, 2.0);
    glVertex3f(10.0, -7.0, 2.0);
	glEnd();
	glPopMatrix();
	
	
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	glColor3f( 0.0 , 0.0 , 0.0);
    glVertex3f(15.0, -8.0, 2.0);
    glVertex3f(15.0, -8.0, 1.0);
    glVertex3f(10.0, -8.0, 1.0);
    glVertex3f(10.0, -8.0, 2.0);
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	glColor3f( 0.0 , 0.0 , 0.0);
    glVertex3f(15.0, -8.0, 1.0);
    glVertex3f(15.0, -9.0, 1.0);
    glVertex3f(10.0, -9.0, 1.0);
    glVertex3f(10.0, -8.0, 1.0);
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	glColor3f( 0.0 , 0.0 , 0.0);
    glVertex3f(15.0, -9.0, 1.0);
    glVertex3f(15.0, -9.0, 0.0);
    glVertex3f(10.0, -9.0, 0.0);
    glVertex3f(10.0, -9.0, 1.0);
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glLineWidth(4);
	glBegin(GL_LINE_STRIP);
    glColor3f(0.0 , 0.0 , 0.0);
    glVertex3f(10.0, -8.0, 1.0);
    glVertex3f(10.0, -8.0, 6.0);
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	glLineWidth(4);
    glColor3f(0.0 , 0.0 , 0.0);
    glVertex3f(10.0, -5.0, 4.0);
    glVertex3f(10.0, -5.0, 9.0);
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	glLineWidth(4);
    glColor3f(0.0 , 0.0 , 0.0);
    glVertex3f(10.0, -2.0, 7.0);
    glVertex3f(10.0, -2.0, 12.0);
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	glLineWidth(4);
    glColor3f(0.0 , 0.0 , 0.0);
    glVertex3f(10.0, 1.0, 10.0);
    glVertex3f(10.0, 1.0, 15.0);
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	glLineWidth(4);
    glColor3f(0.0 , 0.0 , 0.0);
    glVertex3f(10.0, -8.8, 5.2);
    glVertex3f(10.0, 1.8, 15.8);
	glEnd();
	glPopMatrix();
}

void puertaJ(){
	glPushMatrix();
	glBegin(GL_POLYGON);
    glColor3f( 1.0 , 1.0 , 1.0);
    glVertex3f(0.0, -6.65, 7.0);
    glVertex3f(0.0, -6.65, 0.0);
    glVertex3f(0.0, -10.0, 0.0);
    glVertex3f(0.0, -10.0 ,7.0);
    glEnd();
    glPopMatrix();
}

void MechaNoche(){
		//MUEBLE
	//pata mueble :v
	//
	glPushMatrix();
	glTranslatef(-17.0f, -403.5f, 24.01f);
	
	glRotated(90, 0,0,1);//TRASLADADO
	
	glBegin(GL_POLYGON);
	glColor3f( 0.874 , 0.494 , 0.274 );
	glVertex3f(58, 8, 0.6);
	glVertex3f(58, 8.4, 0.6);
	glVertex3f(58, 8.4, 0);
	glVertex3f(58, 8, 0);
	//
	glEnd();
	//pata mueble :v
	//
	glBegin(GL_POLYGON);
	glColor3f( 0.874 , 0.494 , 0.274 );
	glVertex3f(58, 8.4, 0);
	glVertex3f(58, 8.4, 0.6);
	glVertex3f(58, 8.7, 0.6);
	glVertex3f(58, 8.7, 0.3);
	glVertex3f(58, 8.4, 0);
	//
	glEnd();
	//pata mueble :v
	//
	glBegin(GL_POLYGON);
	glColor3f( 0.874 , 0.494 , 0.274 );
	glVertex3f(58, 8.7, 0.6);
	glVertex3f(58, 17.3, 0.6);
	glVertex3f(58, 17.3, 0.3);
	glVertex3f(58, 8.7, 0.3);
	//
	glEnd();
	//pata mueble :v
	//
	glBegin(GL_POLYGON);
	glColor3f( 0.874 , 0.494 , 0.274 );
	glVertex3f(58, 17.6, 0.6);
	glVertex3f(58, 18, 0.6);
	glVertex3f(58, 18, 0);
	glVertex3f(58, 17.6, 0);
	//
	glEnd();
	//pata mueble :v
	//
	glBegin(GL_POLYGON);
	glColor3f( 0.874 , 0.494 , 0.274 );
	glVertex3f(58, 17.3, 0.6);
	glVertex3f(58, 17.6, 0.6);
	glVertex3f(58, 17.6, 0);
	glVertex3f(58, 17.3, 0.3);
	//
	glEnd();
	//pata mueble :v
	//
	glBegin(GL_POLYGON);
	glColor3f( 0.874 , 0.494 , 0.274 );
	glVertex3f(58, 8, 4);
	glVertex3f(58, 8.4, 3.7);
	glVertex3f(58, 8.4, 0);
	glVertex3f(58, 8, 0);
	//
	glEnd();
	//pata mueble :v
	//
	glBegin(GL_POLYGON);
	glColor3f( 0.874 , 0.494 , 0.274 );
	glVertex3f(58, 8, 4);
	glVertex3f(58, 18, 4);
	glVertex3f(58, 17.6, 3.7);
	glVertex3f(58, 8.4, 3.7);
	//
	glEnd();
	//pata mueble :v
	//
	glBegin(GL_POLYGON);
	glColor3f( 0.874 , 0.494 , 0.274 );
	glVertex3f(58, 17.6, 3.7);
	glVertex3f(58, 18, 4);
	glVertex3f(58, 18, 0);
	glVertex3f(58, 17.6, 0);
	//
	glEnd();
	//pata mueble :v
	//
	glBegin(GL_POLYGON);
	glColor3f( 0.874 , 0.494 , 0.274 );
	glVertex3f(58, 12.5, 3.7);
	glVertex3f(58, 12.8, 3.7);
	glVertex3f(58, 12.8, 0.6);
	glVertex3f(58, 12.5, 0.6);
	//
	glEnd();
	//pata mueble :v
	//
	glBegin(GL_POLYGON);
	glColor3f( 0.874 , 0.494 , 0.274 );
	glVertex3f(58, 12.8, 2.2);
	glVertex3f(58, 17.6, 2.2);
	glVertex3f(58, 17.6, 1.95);
	glVertex3f(58, 12.8, 1.95);
	//
	glEnd();
	//pata mueble :v
	//
	glBegin(GL_POLYGON);
	glColor3f( 0.874 , 0.494 , 0.274 );
	glVertex3f(52, 18, 0.6);
	glVertex3f(52, 17.6, 0.6);
	glVertex3f(52, 17.6, 0);
	glVertex3f(52, 18, 0);
	//
	glEnd();
	//pata mueble :v
	//
	glBegin(GL_POLYGON);
	glColor3f( 0.874 , 0.494 , 0.274 );
	glVertex3f(52, 17.6, 0.6);
	glVertex3f(52, 17.3, 0.6);
	glVertex3f(52, 17.3, 0.3);
	glVertex3f(52, 17.6, 0);
	//
	glEnd();
	//pata mueble :v
	//
	glBegin(GL_POLYGON);
	glColor3f( 0.874 , 0.494 , 0.274 );
	glVertex3f(52, 17.3, 0.6);
	glVertex3f(52, 8.7, 0.6);
	glVertex3f(52, 8.7, 0.3);
	glVertex3f(52, 17.3, 0.3);
	//
	glEnd();
	//pata mueble :v
	//
	glBegin(GL_POLYGON);
	glColor3f( 0.874 , 0.494 , 0.274 );
	glVertex3f(52, 8.7, 0.6);
	glVertex3f(52, 8.4, 0.6);
	glVertex3f(52, 8.4, 0);
	glVertex3f(52, 8.7, 0.3);
	//
	glEnd();
	//pata mueble :v
	//
	glBegin(GL_POLYGON);
	glColor3f( 0.874 , 0.494 , 0.274 );
	glVertex3f(52, 8.4, 0.6);
	glVertex3f(52, 8, 0.6);
	glVertex3f(52, 8, 0);
	glVertex3f(52, 8.4, 0);
	//
	glEnd();
	//pata mueble :v
	//
	glBegin(GL_POLYGON);
	glColor3f( 0.874 , 0.494 , 0.274 );
	glVertex3f(52, 8.4, 3.7);
	glVertex3f(52, 8, 4);
	glVertex3f(52, 8, 0);
	glVertex3f(52, 8.4, 0);
	//
	glEnd();
	//pata mueble :v
	//
	glBegin(GL_POLYGON);
	glColor3f( 0.874 , 0.494 , 0.274 );
	glVertex3f(52, 17.6, 2.2);
	glVertex3f(52, 12.8, 2.2);
	glVertex3f(52, 12.8, 1.95);
	glVertex3f(52, 17.6, 1.95);
	//
	glEnd();
	//pata mueble :v
	//
	glBegin(GL_POLYGON);
	glColor3f( 0.874 , 0.494 , 0.274 );
	glVertex3f(52, 18, 4);
	glVertex3f(52, 17.6, 3.7);
	glVertex3f(52, 17.6, 0);
	glVertex3f(52, 18, 0);
	//
	glEnd();
	//pata mueble :v
	//
	glBegin(GL_POLYGON);
	glColor3f( 0.874 , 0.494 , 0.274 );
	glVertex3f(52, 18, 4);
	glVertex3f(52, 8, 4);
	glVertex3f(52, 8.4, 3.7);
	glVertex3f(52, 17.6, 3.7);
	//
	glEnd();
	//pata mueble :v
	//
	glBegin(GL_POLYGON);
	glColor3f( 0.874 , 0.494 , 0.274 );
	glVertex3f(52, 12.8, 3.7);
	glVertex3f(52, 12.5, 3.7);
	glVertex3f(52, 8.4, 3.7);
	glVertex3f(52, 17.6, 3.7);
	//
	glEnd();
	//pata mueble :v
	//
	glBegin(GL_POLYGON);
	glColor3f( 0.874 , 0.494 , 0.274 );
	glVertex3f(52, 12.8, 3.7);
	glVertex3f(52, 12.5, 3.7);
	glVertex3f(52, 12.5, 0.6);
	glVertex3f(52, 12.8, 0.6);
	//
	glEnd();
	//pata mueble :v
	//
	glBegin(GL_POLYGON);
	glColor3f( 0.874 , 0.494 , 0.274 );
	glVertex3f(52, 12.8, 3.7);
	glVertex3f(52, 12.5, 3.7);
	glVertex3f(52, 12.5, 0.6);
	glVertex3f(52, 12.8, 0.6);
	//
	glEnd();
	//pata mueble :v
	//
	glBegin(GL_POLYGON);
	glColor3f( 0.874 , 0.494 , 0.274 );
	glVertex3f(52, 8, 4);
	glVertex3f(58, 8, 4);
	glVertex3f(58, 8, 0);
	glVertex3f(52, 8, 0);
	//
	glEnd();
	//pata mueble :v
	//
	glBegin(GL_POLYGON);
	glColor3f( 0.874 , 0.494 , 0.274 );//naranja
	glVertex3f(58, 18, 4);
	glVertex3f(52, 18, 4);
	glVertex3f(52, 18, 0);
	glVertex3f(58, 18, 0);
	//
	glEnd();
	//pata mueble :v
	//
	glBegin(GL_POLYGON);
	glColor3f( 0.509 , 0.290 , 0.160 );//naranja oscuro
	glVertex3f(52, 12.5, 3.7);
	glVertex3f(58, 12.5, 3.7);
	glVertex3f(58, 12.5, 0.6);
	glVertex3f(52, 12.5, 0.6);
	//
	glEnd();
	//pata mueble :v
	//
	glBegin(GL_POLYGON);
	glColor3f( 0.705 , 0.4, 0.219 );//naranja medio
	glVertex3f(58, 8, 0.6);
	glVertex3f(52, 8, 0.6);
	glVertex3f(52, 12.5, 0.6);
	glVertex3f(58, 12.5, 0.6);
	//
	glEnd();
	//pata mueble :v
	//
	glBegin(GL_POLYGON);
	glColor3f( 0.705 , 0.4, 0.219 );//naranja medio
	glVertex3f(58, 18, 4);
	glVertex3f(58, 8, 4);
	glVertex3f(52, 8, 4);
	glVertex3f(52, 18, 4);
	//
	glEnd();
	//pata mueble :v
	//
	glBegin(GL_POLYGON);
	glColor3f( 0.705 , 0.4, 0.219 );//naranja medio
	glVertex3f(58, 17.6, 2.2);
	glVertex3f(58, 12.8, 2.2);
	glVertex3f(52, 12.8, 2.2);
	glVertex3f(52, 17.6, 2.2);
	//
	glEnd();
	//pata mueble :v
	//
	glBegin(GL_POLYGON);
	glColor3f( 0.705 , 0.4, 0.219 );//naranja medio
	glVertex3f(58, 12.5, 0.6);
	glVertex3f(52, 12.5, 0.6);
	glVertex3f(52, 18, 0.6);
	glVertex3f(58, 18, 0.6);
	//
	glEnd();
	//pata mueble :v
	//
	glBegin(GL_POLYGON);
	glColor3f( 0.705 , 0.4, 0.219 );//naranja medio
	glVertex3f(52, 17.6, 4);
	glVertex3f(58, 17.6, 4);
	glVertex3f(58, 17.6, 2.2);
	glVertex3f(52, 17.6, 2.2);
	//
	glEnd();
	//pata mueble :v
	//
	glBegin(GL_POLYGON);
	glColor3f( 0.705 , 0.4, 0.219 );//naranja medio
	glVertex3f(52, 17.6, 1.95);
	glVertex3f(58, 17.6, 1.95);
	glVertex3f(58, 17.6, 0.6);
	glVertex3f(52, 17.6, 0.6);
	//
	glEnd();			
	//pata mueble :v
	//
	glBegin(GL_POLYGON);
	glColor3f( 0.705 , 0.4, 0.219 );//naranja medio
	glVertex3f(58, 12.8, 0.6);
	glVertex3f(58, 12.8, 4);
	glVertex3f(52, 12.8, 4);
	glVertex3f(52, 12.8, 0.6);	
	//
	glEnd();
	glPopMatrix();
}

void TVJ(){
	glPushMatrix();
	
	glTranslatef(84.0f, -290.5f, 5.9f);
	glRotatef(90.0, 0.0,0.0,180.0);
	glScalef(0.8f, 0.8f, 0.8f);
 	
	//------------------------TV
	glBegin(GL_QUADS);
	glColor3f( 0.0 , 0.0 , 0.0 );
	glVertex3f(-44, 164, 16);
    glVertex3f(-30, 164, 16);
    glVertex3f(-30, 164, 8);
    glVertex3f(-44, 164, 8);
    
    glVertex3f(-44, 164, 16);
    glVertex3f(-44, 164, 8);
    glVertex3f(-44, 165, 8);
    glVertex3f(-44, 165, 16);
    
    glVertex3f(-30, 164, 16);
    glVertex3f(-30, 164, 8);
    glVertex3f(-30, 165, 8);
    glVertex3f(-30, 165, 16);
    
    glVertex3f(-44, 164, 16);
    glVertex3f(-30, 164, 16);
    glVertex3f(-30, 165, 16);
    glVertex3f(-44, 165, 16);
    
    glVertex3f(-44, 164, 8);
    glVertex3f(-30, 164, 8);
    glVertex3f(-30, 165, 8);
    glVertex3f(-44, 165, 8);
    glEnd();
    glPopMatrix();
}


void basesombrilla(){
	glBegin(GL_QUADS);
	glColor3f( 0.184 , 0.168 , 0.164 );//marron oscuro
	//base
	glVertex3f(-60, 4, 0);
    glVertex3f(-63, 4, 0);
    glVertex3f(-63, 1, 0);
    glVertex3f(-60, 1, 0);
    //grosor
    glVertex3f(-60, 4, 0.5);
    glVertex3f(-63, 4, 0.5);
    glVertex3f(-63, 1, 0.5);
    glVertex3f(-60, 1, 0.5);
    //costados
    glVertex3f(-63, 4, 0.5);
    glVertex3f(-63, 4, 0);
    glVertex3f(-63, 1, 0);
    glVertex3f(-63, 1, 0.5);
    
    glVertex3f(-60, 4, 0.5);
    glVertex3f(-60, 4, 0);
    glVertex3f(-60, 1, 0);
    glVertex3f(-60, 1, 0.5);
    
    glVertex3f(-63, 1, 0.5);
    glVertex3f(-60, 1, 0.5);
    glVertex3f(-60, 1, 0);
    glVertex3f(-63, 1, 0);
    
    glEnd();
    //costados
    glBegin(GL_POLYGON);
    
    glVertex3f(-62, 2.5, 4);
    glVertex3f(-62, 0, 9);
    glVertex3f(-62, -1, 9);
    glVertex3f(-62, 1.5, 4);
    
    glVertex3f(-62, 1.5, 0.5);
    glVertex3f(-62, 2.5, 0.5);
    
    glEnd();
    
    glBegin(GL_POLYGON);
    
    glVertex3f(-61, 2.5, 4);
    glVertex3f(-61, 0, 9);
    glVertex3f(-61, -1, 9);
    glVertex3f(-61, 1.5, 4);
    
    glVertex3f(-61, 1.5, 0.5);
    glVertex3f(-61, 2.5, 0.5);
    
    glEnd();
    
    //ADELANTE Y ATRAS
    glBegin(GL_POLYGON);
    
    glVertex3f(-61, 2.5, 4);
    glVertex3f(-61, 0, 9);
    glVertex3f(-62, 0, 9);
    glVertex3f(-62, 2.5, 4);
    
    glVertex3f(-62, 2.5, 0.5);
    glVertex3f(-61, 2.5, 0.5);
    
    glEnd();
    
    glBegin(GL_POLYGON);
    
    glVertex3f(-62, 1.5, 4);
    glVertex3f(-62, -1, 9);
    glVertex3f(-61, -1, 9);
    glVertex3f(-61, 1.5, 4);
    
    glVertex3f(-61, 1.5, 0.5);
    glVertex3f(-62, 1.5, 0.5);
    
    glEnd();
    
    //MADERA DIAGONAL
    glBegin(GL_QUADS);
    //costados
	glVertex3f(-62, -0.6, 7);
    glVertex3f(-62, -1, 8);
    glVertex3f(-62, 7, 11);
    glVertex3f(-62, 7.6, 10);
    
    glVertex3f(-61, -0.6, 7);
    glVertex3f(-61, -1, 8);
    glVertex3f(-61, 7, 11);
    glVertex3f(-61, 7.6, 10);
    //abajo arriba
    glVertex3f(-62, -1, 8);
    glVertex3f(-61, -1, 8);
    glVertex3f(-61, 7, 11);
    glVertex3f(-62, 7, 11);
    
    
    
    //TAPAS
    
    glVertex3f(-61, 7.6, 10);
    glVertex3f(-61, 7, 11);
    glVertex3f(-62, 7, 11);
    glVertex3f(-62, 7.6, 10);
    
    glVertex3f(-62, -0.6, 7);
    glVertex3f(-62, -1, 8);
    glVertex3f(-61, -1, 8);
    glVertex3f(-61, -0.6, 7);
    
    glVertex3f(-61, 0, 9);
    glVertex3f(-61, -1, 9);
    glVertex3f(-62, -1, 9);
    glVertex3f(-62, 0, 9);
    glEnd();
}

void carpa(){
	
	glBegin(GL_TRIANGLES);
	glColor3f( 1.0 , 1.0 , 1.0 );//BLANCO	
	glVertex3f(-61.5, 7.6, 10);
    glVertex3f(-66, 12.3, 7.5);
    glVertex3f(-66, 2, 7.5);
    glEnd();
    
    glBegin(GL_TRIANGLES);
	glColor3f( 0.886 , 0.156 , 0.098 );	//ROJO
	glVertex3f(-61.5, 7.6, 10);
    glVertex3f(-66, 12.3, 7.5);
    glVertex3f(-57, 12.3, 7.5);
    glEnd();
    
    glBegin(GL_TRIANGLES);
	glColor3f( 1.0 , 1.0 , 1.0 );//BLANCO	
	glVertex3f(-61.5, 7.6, 10);
    glVertex3f(-57, 12.3, 7.5);
    glVertex3f(-57, 2, 7.5);
    glEnd();
    
    glBegin(GL_TRIANGLES);
	glColor3f( 0.886 , 0.156 , 0.098 );//ROJO
	glVertex3f(-61.5, 7.6, 10);
    glVertex3f(-57, 2, 7.5);
    glVertex3f(-66, 2, 7.5);
    glEnd();
    
    glBegin(GL_QUADS);
	glColor3f( 0.886 , 0.156 , 0.098 );//ROJO
	glVertex3f(-57, 12.3, 7.5);
    glVertex3f(-66, 12.3, 7.5);
    glVertex3f(-66, 12.3, 7);
    glVertex3f(-57, 12.3, 7);
    
    glVertex3f(-57, 2, 7.5);
    glVertex3f(-66, 2, 7.5);
    glVertex3f(-66, 2, 7);
    glVertex3f(-57, 2, 7);
    
    glColor3f( 1.0 , 1.0 , 1.0 );//BLANCO
    
    glVertex3f(-66, 12.3, 7.5);
    glVertex3f(-66, 2, 7.5);
    glVertex3f(-66, 2, 7);
    glVertex3f(-66, 12.3, 7);
    
    glVertex3f(-57, 12.3, 7.5);
    glVertex3f(-57, 2, 7.5);
    glVertex3f(-57, 2, 7);
    glVertex3f(-57, 12.3, 7);
    
    glEnd();
    
}

void lineas(){
	
	glLineWidth(2);
    glColor3f( 0.0 , 0.0 , 0.0 );
    //base
    glBegin(GL_LINE_LOOP);
    
    glVertex3f(-62, 2.5, 4);
    glVertex3f(-62, 0.75, 7.5);
    glVertex3f(-62, 7.6, 10);
    glVertex3f(-62, 7, 11);
    
    glVertex3f(-62, 0.26, 8.45);
    glVertex3f(-62, 0, 9);
    glVertex3f(-62, -1, 9);
    glVertex3f(-62, -0.6, 8.2);
    
    glVertex3f(-62, -1, 8);
    glVertex3f(-62, -0.6, 7);
    glVertex3f(-62, -0.1, 7.2);
    glVertex3f(-62, 1.5, 4);
    
    glVertex3f(-62, 1.5, 0.5);
    glVertex3f(-62, 2.5, 0.5);
    
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    
    glVertex3f(-61, 2.5, 4);
    glVertex3f(-61, 0.75, 7.5);
    glVertex3f(-61, 7.6, 10);
    glVertex3f(-61, 7, 11);
    
    glVertex3f(-61, 0.26, 8.45);
    glVertex3f(-61, 0, 9);
    glVertex3f(-61, -1, 9);
    glVertex3f(-61, -0.6, 8.2);
    
    glVertex3f(-61, -1, 8);
    glVertex3f(-61, -0.6, 7);
    glVertex3f(-61, -0.1, 7.2);
    glVertex3f(-61, 1.5, 4);
    
    glVertex3f(-61, 1.5, 0.5);
    glVertex3f(-61, 2.5, 0.5);
    
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    
    glVertex3f(-60, 4, 0.5);
    glVertex3f(-60, 1, 0.5);
    glVertex3f(-63, 1, 0.5);
    glVertex3f(-63, 4, 0.5);
    
    glEnd();
    //carpa
    glBegin(GL_LINE_LOOP);
    
    glVertex3f(-66, 12.3, 7.5);
    glVertex3f(-57, 12.3, 7.5);
    glVertex3f(-57, 2, 7.5);
    glVertex3f(-66, 2, 7.5);
    
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    
    glVertex3f(-66, 12.3, 7);
    glVertex3f(-57, 12.3, 7);
    glVertex3f(-57, 2, 7);
    glVertex3f(-66, 2, 7);
    
    glEnd();
    
    glBegin(GL_LINES);
    
    glVertex3f(-61.5, 7.6, 10);
    glVertex3f(-61.5, 7.6, 7.5);
    glVertex3f(-61.5, 7.6, 7.5);
    glVertex3f(-66, 2, 7.5);
    glVertex3f(-61.5, 7.6, 7.5);
    glVertex3f(-66, 12.3, 7.5);
    glVertex3f(-61.5, 7.6, 7.5);
    glVertex3f(-57, 12.3, 7.5);
    glVertex3f(-61.5, 7.6, 7.5);
    glVertex3f(-57, 2, 7.5);
    
    glVertex3f(-57, 12.3, 7.5);
    glVertex3f(-61.5, 7.6, 10);
    glVertex3f(-57, 2, 7.5);
    glVertex3f(-61.5, 7.6, 10);
    glVertex3f(-66, 2, 7.5);
    glVertex3f(-61.5, 7.6, 10);
    glVertex3f(-66, 12.3, 7.5);
    glVertex3f(-61.5, 7.6, 10);
    
    glVertex3f(-62, -1, 8);
    glVertex3f(-61, -1, 8);
    glVertex3f(-62, 7, 11);
    glVertex3f(-61, 7, 11);
    
    glEnd();
}

void sombrilla(){
	
	basesombrilla();
	carpa();
	lineas();
}





void Figuras1(){
	
	glPushMatrix();
	glTranslatef(-45.0f, -336.0f, 0.01f);
	glRotatef(180.0, 0.0,0.0,180.0);
	glScalef(0.7f, 0.7f, 0.9f);
	retrete();
	espejo_y_lavadero();
	glPopMatrix();
	
	glPushMatrix();
	TVJ();
	MechaNoche();
	glPopMatrix();
}

void Figuras2(){
	glPushMatrix();
	glTranslatef(-15.0f, -560.5f, 0.01f);
	glRotated(270.0, 0.0,0.0,270.0);
	silla1_piscina();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-102.0f, -510.5f, 0.01f);
	glRotatef(180.0, 0.0,0.0,180.0);
	sombrilla();
	glPopMatrix();
	
}

void casaJ(){
	glPushMatrix();
	glTranslatef(-20.0f, -342.5f, 0.01f);
 	glRotatef(180.0, 0.0,0.0,180.0);
 	glScalef(1.9f, 1.5f, 2.0f);
	casaJara();
	vereda();
	PT();
	muebleJara();
	Cocinaa();
	LavaderoJ();
	R();
	MesaCocina();
	escalerasJ();
	puertaJ();
	CamaJ();
	glPopMatrix();
} 

void copias(){
	glPushMatrix();
	casaJ();
	Figuras1();
	Figuras2();
	glPopMatrix();
}

void copias1(){
	glPushMatrix();
	glTranslatef(80.0f, 0.0f, 0.01f);
	copias();
	glPopMatrix();
}

void copias2(){
    glPushMatrix();
    glTranslatef(140.0f, 0.0f, 0.01f);
    copias();
    glPopMatrix();
}

void copias4(){
    glPushMatrix();
    glTranslatef(280.0f, 0.0f, 0.01f);
    copias();
    glPopMatrix();
}

void copias5(){
    glPushMatrix();
    glTranslatef(350.0f, 0.0f, 0.01f);
    copias();
    glPopMatrix();
}

void copias6(){
    glPushMatrix();
    glTranslatef(420.0f, 0.0f, 0.01f);
    copias();
    glPopMatrix();
}

void pistaCalle(){
	
	glBegin(GL_QUADS);
	glColor3f( 0.105 , 0.105 , 0.105);//negro
	glVertex3f(-300, -277, 0.02);
    glVertex3f(-300, -239, 0.02);
    glVertex3f(420, -239, 0.02);
    glVertex3f(420, -277, 0.02);
	
	glBegin(GL_QUADS);
	glColor3f( 1.0 , 1.0 , 0.0);//amarillo
	glVertex3f(-250, -260, 0.05);
    glVertex3f(-250, -256, 0.05);
    glVertex3f(-200, -256, 0.05);
    glVertex3f(-200, -260, 0.05);
    
    glBegin(GL_QUADS);
	glColor3f( 1.0 , 1.0 , 0.0);//amarillo
	glVertex3f(-160, -260, 0.05);
    glVertex3f(-160, -256, 0.05);
    glVertex3f(-110, -256, 0.05);
    glVertex3f(-110, -260, 0.05);
    
    glBegin(GL_QUADS);
	glColor3f( 1.0 , 1.0 , 0.0);//amarillo
	glVertex3f(-70, -260, 0.05);
    glVertex3f(-70, -256, 0.05);
    glVertex3f(-20, -256, 0.05);
    glVertex3f(-20, -260, 0.05);
    
    glBegin(GL_QUADS);
	glColor3f( 1.0 , 1.0 , 0.0);//amarillo
	glVertex3f(20, -260, 0.05);
    glVertex3f(20, -256, 0.05);
    glVertex3f(70, -256, 0.05);
    glVertex3f(70, -260, 0.05);
    
    glBegin(GL_QUADS);
	glColor3f( 1.0 , 1.0 , 0.0);//amarillo
	glVertex3f(110, -260, 0.05);
    glVertex3f(110, -256, 0.05);
    glVertex3f(160, -256, 0.05);
    glVertex3f(160, -260, 0.05);
    
    glBegin(GL_QUADS);
	glColor3f( 1.0 , 1.0 , 0.0);//amarillo
	glVertex3f(200, -260, 0.05);
    glVertex3f(200, -256, 0.05);
    glVertex3f(250, -256, 0.05);
    glVertex3f(250, -260, 0.05);
    
    glBegin(GL_QUADS);
	glColor3f( 1.0 , 1.0 , 0.0);//amarillo
	glVertex3f(290, -260, 0.05);
    glVertex3f(290, -256, 0.05);
    glVertex3f(340, -256, 0.05);
    glVertex3f(340, -260, 0.05);

	
	glBegin(GL_QUADS);
	glColor3f( 0.105, 0.105, 0.105);//negro
	glVertex3f(-70, -239, 0.02);
    glVertex3f(-120, -239, 0.02);
    glVertex3f(-120, 280, 0.02);
    glVertex3f(-70, 280, 0.02);
    
    glBegin(GL_QUADS);
    glColor3f( 1.0 , 1.0 , 0.0);//amarillo	
    glVertex3f(-92, -230, 0.05);
    glVertex3f(-98, -230, 0.05);
    glVertex3f(-98, -200, 0.05);
    glVertex3f(-92, -200, 0.05);
    
    glBegin(GL_QUADS);
    glColor3f( 1.0 , 1.0 , 0.0);//amarillo	
    glVertex3f(-92, -230, 0.05);
    glVertex3f(-98, -230, 0.05);
    glVertex3f(-98, -180, 0.05);
    glVertex3f(-92, -180, 0.05);
    
    glBegin(GL_QUADS);
    glColor3f( 1.0 , 1.0 , 0.0);//amarillo	
    glVertex3f(-92, -140, 0.05);
    glVertex3f(-98, -140, 0.05);
    glVertex3f(-98, -90, 0.05);
    glVertex3f(-92, -90, 0.05);
    
    glBegin(GL_QUADS);
    glColor3f( 1.0 , 1.0 , 0.0);//amarillo	
    glVertex3f(-92, -50, 0.05);
    glVertex3f(-98, -50, 0.05);
    glVertex3f(-98, 1, 0.05);
    glVertex3f(-92, 1, 0.05);
    
    glBegin(GL_QUADS);
    glColor3f( 1.0 , 1.0 , 0.0);//amarillo	
    glVertex3f(-92, 40, 0.05);
    glVertex3f(-98, 40, 0.05);
    glVertex3f(-98, 90, 0.05);
    glVertex3f(-92, 90, 0.05);
    
    glBegin(GL_QUADS);
    glColor3f( 1.0 , 1.0 , 0.0);//amarillo	
    glVertex3f(-92, 130, 0.05);
    glVertex3f(-98, 130, 0.05);
    glVertex3f(-98, 180, 0.05);
    glVertex3f(-92, 180, 0.05);
    
    glBegin(GL_QUADS);
    glColor3f( 1.0 , 1.0 , 0.0);//amarillo	
    glVertex3f(-92, 220, 0.05);
    glVertex3f(-98, 220, 0.05);
    glVertex3f(-98, 270, 0.05);
    glVertex3f(-92, 270, 0.05);
    
	
}

void Nube()
{//----------------------NUBE1-----------------
glPushMatrix();
     glTranslatef(-205,15,155);
     glColor3f (1.0,1.0,1.0);
     glutSolidSphere(20,40,40);
glPopMatrix();
	
glPushMatrix();
     glTranslatef(-185,15,155);
     glColor3f (1.0,1.0,1.0);
     glutSolidSphere(20,40,40);
glPopMatrix();	

glPushMatrix();
     glTranslatef(-150,15,155);
     glColor3f (1.0,1.0,1.0);
     glutSolidSphere(20,40,40);
glPopMatrix();

//----------------------NUBE2-----------------
glPushMatrix();
     glTranslatef(35,15,155);
     glColor3f (1.0,1.0,1.0);
     glutSolidSphere(20,40,40);
glPopMatrix();
	
glPushMatrix();
     glTranslatef(10,15,155);
     glColor3f (1.0,1.0,1.0);
     glutSolidSphere(20,40,40);
glPopMatrix();	

glPushMatrix();
     glTranslatef(-10,15,155);
     glColor3f (1.0,1.0,1.0);
     glutSolidSphere(20,40,40);
glPopMatrix();

//----------------------NUBE 3-----------------
glPushMatrix();
     glTranslatef(185,15,155);
     glColor3f (1.0,1.0,1.0);
     glutSolidSphere(20,40,40);
glPopMatrix();
	
glPushMatrix();
     glTranslatef(155,15,155);
     glColor3f (1.0,1.0,1.0);
     glutSolidSphere(20,40,40);
glPopMatrix();	

glPushMatrix();
     glTranslatef(135,15,155);
     glColor3f (1.0,1.0,1.0);
     glutSolidSphere(20,40,40);
glPopMatrix();

//----------------------NUBE 4-----------------
glPushMatrix();
     glTranslatef(395,15,155);
     glColor3f (1.0,1.0,1.0);
     glutSolidSphere(20,40,40);
glPopMatrix();
	
glPushMatrix();
     glTranslatef(355,15,155);
     glColor3f (1.0,1.0,1.0);
     glutSolidSphere(20,40,40);
glPopMatrix();	

glPushMatrix();
     glTranslatef(325,15,155);
     glColor3f (1.0,1.0,1.0);
     glutSolidSphere(20,40,40);
glPopMatrix();


}
//-------------------SOl -LUNA
void SolLuna()
{
//-----------SOL.---------------
glPushMatrix();
     glTranslatef(325,15,325);
     glColor3f (1.1,1.1,0.0);
     glutSolidSphere(40,20,20);
glPopMatrix();
//----------------------Tranlado de Nube---------
glPushMatrix();
     glTranslatef(65,-20 ,45 ); 
    Nube();
glPopMatrix();
//----------------------Tranlado de Nube---------
glPushMatrix();
     glTranslatef(65,45 ,-20 ); 
    Nube();
glPopMatrix();

//-----------------------------LUNA---------------
glPushMatrix();
     glTranslatef(-325,15,325);
     glColor3f (0.62, 0.62, 0.62);
     glutSolidSphere(40,20,20);
glPopMatrix();
//--------------------------

}
//=========================================================================================================


void cuerpo(){
	//cuerpo
	glPushMatrix();
glTranslatef(0,0,7.5);	
cilindro = gluNewQuadric();
glColor3f( 0.082 , 0.698 , 0.698 );
gluQuadricDrawStyle(cilindro,GLU_FILL);
gluCylinder(cilindro,2.5,2.5,7,100,100);
glPopMatrix();
}

void Pierna_derecha1(){
//pierna derecha1
	glPushMatrix();
glTranslatef(1.65,0,4);	
cilindro = gluNewQuadric();
glColor3f( 0.050 , 0.950 , 0.950 );
gluQuadricDrawStyle(cilindro,GLU_FILL);
gluCylinder(cilindro,1,1,3.5,100,100);
glPopMatrix();
}
void Pierna_derecha2(){
//pierna derecha2
	glPushMatrix();
glTranslatef(1.65,0,0.2);	
cilindro = gluNewQuadric();
glColor3f( 0.050 , 0.950 , 0.950 );
gluQuadricDrawStyle(cilindro,GLU_FILL);
gluCylinder(cilindro,1,1,3.5,100,100);
glPopMatrix();
}
void pierna_izquierda1(){
//pierna izquierda1
	glPushMatrix();
glTranslatef(-1.65,0,4);	
cilindro = gluNewQuadric();
glColor3f( 0.050 , 0.950 , 0.950 );
gluQuadricDrawStyle(cilindro,GLU_FILL);
gluCylinder(cilindro,1,1,3.5,100,100);
glPopMatrix();
}
void pierna_izquierda2(){
//pierna izquierda2
	glPushMatrix();
glTranslatef(-1.65,0,0.2);	
cilindro = gluNewQuadric();
glColor3f( 0.050 , 0.950 , 0.950 );
gluQuadricDrawStyle(cilindro,GLU_FILL);
gluCylinder(cilindro,1,1,3.5,100,100);
glPopMatrix();

}
void brazo_izquierda1(){
//brazo  izquierda1
	glPushMatrix();
glTranslatef(-4,0,10.5);	
cilindro = gluNewQuadric();
glColor3f( 0.082 , 0.698 , 0.698 );
gluQuadricDrawStyle(cilindro,GLU_FILL);
gluCylinder(cilindro,1,1,3,100,100);
glPopMatrix();
}
void brazo_izquierda2(){
//pierna izquierda2
	glPushMatrix();
glTranslatef(-4,0,7.3);	
cilindro = gluNewQuadric();
glColor3f( 0.509 , 0.063 , 0.063 );
gluQuadricDrawStyle(cilindro,GLU_FILL);
gluCylinder(cilindro,1,1,3,100,100);
glPopMatrix();
}

void brazo_derecha1(){
//brazo  derecha1
	glPushMatrix();
glTranslatef(4,0,10.5);	
cilindro = gluNewQuadric();
glColor3f( 0.082 , 0.698 , 0.698 );
gluQuadricDrawStyle(cilindro,GLU_FILL);
gluCylinder(cilindro,1,1,3,100,100);
glPopMatrix();
}

void brazo_derecha2(){
//brazo  derecha2
	glPushMatrix();
glTranslatef(4,0,7.3);	
cilindro = gluNewQuadric();
glColor3f( 0.509 , 0.063 , 0.063 );
gluQuadricDrawStyle(cilindro,GLU_FILL);
gluCylinder(cilindro,1,1,3,100,100);
glPopMatrix();
}

void zapato_derecho(){
	//zapato
glPushMatrix();
	glColor3f( 0.168 ,  0.0  ,  0.0  );
	glTranslatef(1.6, -0.5, 0);
	glScalef(0.15, -0.25, 0.1);
	glutSolidCube(10);
	glColor3f(0.0f, 0.0f, 0.0f);
	LineaCubo(1);	
	glEnd ();	
	glPopMatrix();
}

void zapato_izquierdo(){
	//zapato
glPushMatrix();
	glColor3f( 0.168 ,  0.0  ,  0.0  );
	glTranslatef(-1.6, -0.5, 0);
	glScalef(0.15, -0.25, 0.1);
	glutSolidCube(10);
	glColor3f(0.0f, 0.0f, 0.0f);
	LineaCubo(1);	
	glEnd ();	
	glPopMatrix();
}


void cabeza(){
	//cabeza
glPushMatrix();
glTranslatef(0,0,17);
glColor3f( 0.509 , 0.063 , 0.063 );
glutSolidSphere(2.5,40,40);
glPopMatrix();
}


void PJ(){
glPushMatrix();
glTranslatef(67,160,1);
glScalef(0.6,0.6,0.6);
glTranslatef(0,posYPJ,0);
cuerpo();
glPushMatrix();
glTranslatef(0,PY,0);
glRotatef(PA,1.0,0,0);
Pierna_derecha1();
Pierna_derecha2();
zapato_derecho();
glPopMatrix();
glPushMatrix();
glTranslatef(0,-PY,0);
glRotatef(-PA,1.0,0,0);
pierna_izquierda1();
pierna_izquierda2();
zapato_izquierdo();
glPopMatrix();
brazo_izquierda1();
brazo_izquierda2();
brazo_derecha1();
brazo_derecha2();
cabeza();


glPopMatrix();
}


void display() {
glClearColor(colores[iFondo][0], colores[iFondo][1], colores[iFondo][2], 1.0f);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpiar el búfer de color
glMatrixMode(GL_MODELVIEW); // Para operar Model-View matrix 
glLoadIdentity();

glRotated(girax,1.0,0.0,0.0);
glRotated(giray,0.0,1.0,0.0);
glRotated(giraz,0.0,0.0,1.0);

gluLookAt(rx ,ry , rz, /* cam-pos (0,0,20) */
px, py, pz, /* ver a */
tx, ty, tz);
 
glBegin(GL_QUADS);
glColor4f (0.29f, 0.43f, 0.2f, 1.0f);
glVertex3f(-320, -320, -2.1);
glVertex3f(-320,320, -2.1);
glVertex3f(320,320, -2.1);
glVertex3f(320,-320, -2.1);
glEnd();





//-------------DIBUJO--------------

	
  //cocina
	paredes();
	espejo_y_puerta();
	Mampara();
	Tragaluz();
	Encimera();
    Candelabro();
	Refrigedador();
	repisa1();
	repisa2();
	cocina();
	silla();
	repostero();
	estanteArriba();
	Utensilios ();
	//auto
    vehiculo ();
    //patio
    vereda_piscina();
	silla1_piscina();
	silla2_piscina();
	piscina();
	pasto();
	zona_parrilla();
	//sala
	paredes1();
	mesaTVSala();
	televisor();
	cuadro1();
	puertaPasilloSala();
	puertaPrincipal();
	repisa3();
	repisa4();
	mueble();
	mesa();
	mueble1();
	paredes2();
	glPushMatrix();
	glTranslated(34.1,51,15.7);
	glRotated(90,1,0,0);
	glRotated(180,0,-1,0);
	glScaled(3.8,3,3);
	glPushMatrix();
		Alfombra();
		PisoCuarto();
		paredDerechaFondo();
		paredIzquierdaFondo();
		Puerta();
		Muebles();
	glPopMatrix();
    glPushMatrix();
        glRotatef(-45,0,1,0);
        glTranslatef(posXPericote,0.0,0.0);
        DibujarPericote();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(2.5, 4.0, -5.0);
        SillaGamer();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-1.0, 0.0, 0.03);
        Escritorio();
    glPopMatrix();
    glPushMatrix();
        TV();
    glPopMatrix();
	glPopMatrix();	
	
		cal ();
puertabanio ();
ducha();
espejo_y_lavadero();
retrete();
lavadora();
cuadro2();
cuadro3();
cuarto2();
pasillo();
Radio();
pared();
repisa_y_alfombra();
//cuarto segundo piso
escalera();
terraza();
cuarto_segundo_piso();
mesas();
tele2();
mueble2();
espejo2do();
escritorio3();
PC();
librero();
libros();
mampara2();
Nube();
SolLuna();
glPushMatrix();
glTranslatef(-100.0f,250.0f, 0.0f);
glRotated(90,0.0,0.0,-1.0);
glScalef(6.0f, 6.0f, 6.0f);
 muroCentralParque();
    murosPartRightPark1();
    murosPartRightPark2();
    murosPartRightPark3();
    murosPartRightPark4();
    murosPartRightPark5();
    
    glPushMatrix();
	glTranslatef(70.4f, 130.1f, 0.2f);
 	glRotatef(180.0, 0.0,0.0,180.0);
	murosPartRightPark1();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(70.3f, 107.1f, 0.0f);
 	glRotatef(180.0, 0.0,0.0,180.0);
	murosPartRightPark2();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(70.3f, 107.1f, 0.0f);
 	glRotatef(180.0, 0.0,0.0,180.0);
	murosPartRightPark3();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(70.3f, 107.1f, 0.0f);
 	glRotatef(180.0, 0.0,0.0,180.0);
	murosPartRightPark4();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(70.3f, 107.1f, 0.0f);
 	glRotatef(180.0, 0.0,0.0,180.0);
	murosPartRightPark5();
	glPopMatrix();
	  faro();
    banca();
    paloCurviado();
    translateDeFaros(); 
    translateDeBancas();
	glPopMatrix();
	
glPushMatrix();
glTranslatef(-242.2f,-165.0f, -0.1f);
glScalef(5.0f, 3.0f, 3.0f);
estacionation();
glPopMatrix();
glPushMatrix();
glTranslatef(-242.2f,-360.0f, 0.5f);
glScalef(5.0f, 3.0f, 3.0f);
estacionation();
glPopMatrix();

glPushMatrix();
glTranslatef(142.0f, -210.0f, 0.0f);
glScalef(3.0f, 3.0f, 3.0f);
	whiteLines();
	linesTranslate();
	wall();
	//TRANSLATE OF WALL
	glPushMatrix();
	glTranslatef(68.97f, 30.5f, 0.0f);
 	glRotatef(180.0, 0.0,0.0,180.0);
	wall();
	glPopMatrix();
	//
	downWall();
	//estacionation();
	road();
glPopMatrix();

casanueva1_pt1();
casanueva1_pt2();
casanueva1_pt3();
casanueva1_pt4();
casanueva1_pt5();
glPopMatrix();
    glPushMatrix();
    copias();
    copias1();
    copias2();
    copias4();
    copias5();
    copias6();
    glPopMatrix();
pistaCalle();
Nube();
SolLuna();
casa2();
mueble3();
TerrazaObjetos();
PJ();
glPushMatrix();
glTranslatef(-200.0f,0.0f,0.0f);
casa2();
glPopMatrix();

//---------------------------------
///casa 1

glPushMatrix();
glTranslatef(-200.0f,-30.0f,0.0f);
casanueva1_pt1();

glPopMatrix();
//---------------------------------
glPushMatrix();
glTranslatef(-200.0f,-30.0f,0.0f);

casanueva1_pt2();
glPopMatrix();

//---------------------------------
glPushMatrix();
glTranslatef(-200.0f,-30.0f,0.0f);

casanueva1_pt3();
glPopMatrix();
//---------------------------------
//---------------------------------
glPushMatrix();
glTranslatef(-200.0f,-30.0f,0.0f);

casanueva1_pt4();
glPopMatrix();
//---------------------------------
glPushMatrix();
glTranslatef(-200.0f,-30.0f,0.0f);

casanueva1_pt5();
glPopMatrix();
          
//------------------------------------------		  		        
glFlush (); // Renderizar ahora
glutSwapBuffers ();
glutPostRedisplay();
}
  
//CamaraMovimiento


void flechas(int key,int x,int y)
{
switch(key)
{
case GLUT_KEY_LEFT:
giray=(giray-15)%360;
break;
case GLUT_KEY_RIGHT:
giray=(giray+15)%360;
break;
case GLUT_KEY_UP:
girax=(girax-15)%360;
break;
case GLUT_KEY_DOWN:
girax=(girax+15)%360;
default:
break;
}
glutPostRedisplay();
}


void teclado (unsigned char key,int x, int y)
{
switch(key)
{
	
case 'a':
case 'A':
//PlaySound("facha.wav", NULL, SND_ASYNC|SND_FILENAME);
rx=rx-0.5;
px=px-0.5;

break;
case 'd':
case 'D':
rx=rx+0.5;
px=px+0.5;
break;
case 'w': //Movimientos de camara
case 'W':
ry=ry+0.5;
py=py+0.5;
break;
case 'S':
case 's':
ry=ry-0.5;
py=py-0.5;
break;
 
case '+':
rz=rz+0.5;
pz=pz+0.5;
break;

case '-':
rz=rz-0.5;
pz=pz-0.5;
break;

case 'Q': //Movimientos de camara
case 'q':
giraz=(giraz-15)%360;

break;
case 'E':
case 'e':
giraz=(giraz+15)%360;

break;
case 27:
exit(0);
break;
default:
break;

}
glutPostRedisplay();
}


void manejarTeclado(unsigned char key, int x, int y){
    teclado(key,x,y);
    glutPostRedisplay(); 
	  
}

void manejarFlechas(int key, int x, int y){
    flechas(key,x,y);
    glutPostRedisplay();    
}


int main(int argc,char** argv)
{
// init GLUT and create window
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
glutInitWindowPosition(0,0);
glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
glutCreateWindow("Silla plano cartesiano beto");
//initGL();
// register callbacks
glutDisplayFunc(display);


glutSpecialFunc( manejarFlechas);
glutKeyboardFunc( manejarTeclado);
glutReshapeFunc(reshape);

//glutMouseWheelFunc(mouseWheel);
// OpenGL init
glEnable(GL_DEPTH_TEST);
// enter GLUT event processing cycle
creacionMenu();
glutMainLoop();
return 15;

}


