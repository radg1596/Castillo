//Semestre 2017 - 2
//************************************************************//
//************************************************************//
//************** Alumno (s): *********************************//
//*************	Desiderio Gonzalez Ricardo Abraham		******//
//*************Gutierrez Benitez David Fernando			******//
//************************************************************//
//************************************************************//

#include "texture.h"
#include "figuras.h"
#include "Camera.h"
#include "Windows.h"
#include "cmodel/CModel.h"
#include "stdlib.h"

///ARCHIVO/////
FILE *ap,*escribir;
////RECORRIDO////
char c;

///////Contadores////////
float i = 0, j = 0;

//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////


//NEW// Keyframes
//Variables de dibujo y manipulacion

#define MAX_FRAMES 5
int i_max_steps = 90;
int i_curr_steps = 0;

typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float incX;		//Variable para IncrementoX
	float incY;		//Variable para IncrementoY
	float incZ;		//Variable para IncrementoZ
	float viewX;
	float viewY;
	float viewZ;
	float IncviewX;
	float IncviewY;
	float incviewZ;
}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex=0;			//introducir datos
bool play=false;
int playIndex=0;


//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////

int w = 500, h = 500;
int frame=0,time,timebase=0;
char s[30];

CCamera objCamera;	//Create objet Camera

GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 

int font=(int)GLUT_BITMAP_HELVETICA_18;

//////////////////////ILUMINACION

//GLfloat Diffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat Diffuse[]= { 0.5f, 0.5f, 0.5f, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[]= { 0.0f, 7.0f, -5.0f, 0.0f };			// Light Position
GLfloat Position2[]= { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position

GLfloat m_dif1[] = { 0.0f, 0.2f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec1[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb1[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s1[] = {18};

GLfloat m_dif2[] = { 0.8f, 0.2f, 0.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec2[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb2[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s2[] = {22};

//////DESICIONES IMPORTANTES/////////
bool terror = false;
bool puertaAbierta=false;


////////////VARIABLES DE ROTACION Y TRASLADO////////////////////
//******CASA*******
float trasladoPuerta = 0.0;
float angNubes;
float angFuego = 0;
float angArboles = 0;
//FANTASMAS/////
float fantasma1X = 0, fantasma1Y = 0, fantasma1Z = 0;
float fantasma2X = 0, fantasma2Y = 0, fantasma2Z = 0;
float fantasma3X = 0, fantasma3Y = 0, fantasma3Z = 0;
float fantasma4X = 0, fantasma4Y = 0, fantasma4Z = 0;
float angFantasma, angFantasma2, angFantasma3, angFantasma4;


///////////////VARIABLES DE MAQUINAS DE ESTADO////////////
bool estado0Arboles = true;
bool estado1Arboles = false;
//Fantasmas
bool estado1Fantasma1=true;
bool estado2Fantasma1=false;
bool estado3Fantasma1=false;
bool estado4Fantasma1=false;
bool estado5Fantasma1=false;
bool estado6Fantasma1 = false;

bool estado1Fantasma2 = true;
bool estado2Fantasma2 = false;
bool estado3Fantasma2 = false;
bool estado4Fantasma2 = false;
bool estado5Fantasma2 = false;

bool estado1Fantasma3 = true;
bool estado2Fantasma3 = false;
bool estado3Fantasma3 = false;
bool estado4Fantasma3 = false;

bool estado1Fantasma4 = true;
bool estado2Fantasma4 = false;
bool estado3Fantasma4 = false;
bool estado4Fantasma4 = false;

////temp
bool playfantasma = false;

///TEXTURAS///////
//Exterior
CTexture text1; //cielo1
CTexture textGrass;
CTexture textMar;

///CAMINO PIEDRA
CTexture textPiedra;


//NEW///////////////////////////7
//Casa
CTexture textPuerta_Casa;
CTexture textWall;
CTexture textPiso;
CTexture textTechoCasa;
//Interior casa
CTexture textSilla;
CTexture textMarble;
CTexture textCuadro1;
CTexture textAlmohada;
CTexture textColcha;
CTexture textMaderaBuro;
CTexture textMaderaCama;
CTexture textChimenea;
CTexture textSChimenea;
CTexture textFuego;

//Navidad
CTexture textTroncoNavidad;
CTexture textHojasNavidad;
CTexture textRegalo;
CTexture textRegaloFront;
CTexture textEsfera1;
CTexture textEsfera2;
CTexture textEsfera3;
CTexture textEsfera4; CTexture textEsfera5;

//Arboles Casa
CTexture textTree;
CTexture textTreeN;
CTexture textTreeN2;
CTexture textTreeV;
CTexture textTree0;
CTexture textTree1;

/////PERSONAJES///////
CTexture textFantasma;


/////////////CFiguras interior de la casa/////////////////
CFiguras tablaMesa;
CFiguras pata1Mesa;
CFiguras pata2Mesa;
CFiguras pata3Mesa;
CFiguras pata4Mesa;
CFiguras asientoSilla;
CFiguras respaldoSilla1;
CFiguras respaldoSilla2;
CFiguras respaldoSilla3;
CFiguras respaldoSilla4;
CFiguras cama;
CFiguras buro;
CFiguras chimenea;
//****Navidad***
CFiguras hojasNavidad;
CFiguras troncoNavidad;
CFiguras regalo;
CFiguras esfera1;
CFiguras esfera2;
CFiguras esfera3;
CFiguras esfera4;
CFiguras esfera5;
///OTRAS//////
CFiguras cubo;
////EXTERIOR/////
CFiguras pasto;
CFiguras mar;
CFiguras camino;




///////////////////FIGURAS EN 3D///////////////////
CModel  fantasma; 

//END NEW//////////////////////////////////////////

/////////////Figuras del entorno///////////////////
CFiguras fig1; //Skybox
//////////Figuras de las paredes de la casa//////////////////////// 
CFiguras paredescasa;
CFiguras paredf; //pared frontal 

void saveFrame ( void )
{
	KeyFrame[FrameIndex].posX = objCamera.mPos.x;
	KeyFrame[FrameIndex].posY = objCamera.mPos.y;
	KeyFrame[FrameIndex].posZ = objCamera.mPos.z;

	KeyFrame[FrameIndex].viewX = objCamera.mView.x;
	KeyFrame[FrameIndex].viewY = objCamera.mView.y;
	KeyFrame[FrameIndex].viewZ = objCamera.mView.z;

	printf("frameindex %d\n",FrameIndex);			


	FrameIndex++;
}

void resetElements( void )
{

	objCamera.mPos.x = KeyFrame[0].posX;
	objCamera.mPos.y = KeyFrame[0].posY;
	objCamera.mPos.z = KeyFrame[0].posZ;

	objCamera.mView.x = KeyFrame[0].viewX;
	objCamera.mView.y = KeyFrame[0].viewY;
	objCamera.mView.z = KeyFrame[0].viewZ;

}

void interpolation ( void )
{
	KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;
	KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
	KeyFrame[playIndex].incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;

	KeyFrame[playIndex].IncviewX = (KeyFrame[playIndex + 1].viewX - KeyFrame[playIndex].viewX) / i_max_steps;
	KeyFrame[playIndex].IncviewY = (KeyFrame[playIndex + 1].viewY - KeyFrame[playIndex].viewY) / i_max_steps;
	KeyFrame[playIndex].incviewZ = (KeyFrame[playIndex + 1].viewZ - KeyFrame[playIndex].viewZ) / i_max_steps;
}


///****PlanosCruzados////////
void planos_cruzados(GLuint text)
{
	glPushMatrix();
	//glDisable(GL_LIGHTING);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glBindTexture(GL_TEXTURE_2D, text);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();

	glPopMatrix();

	glPushMatrix();
	glRotatef(45, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-45, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glDisable(GL_ALPHA_TEST);
	//glEnable(GL_LIGHTING);

	glPopMatrix();
}

//NEW CASA//////////////////////////////////////
void DibujaCasa ( void ){

}

void dibujaContornoCasa() {
	//Paredes y piso de la casa
	glPushMatrix();
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1);
		glRotatef(-90, 0,1,0);
		if (terror==false)	
			paredescasa.skybox_casa(26, 30, 30, textWall.GLindex, textPiso.GLindex, textPuerta_Casa.GLindex, textTechoCasa.GLindex, 1.0f, 8.0f, 3.0f, trasladoPuerta);
		else 
			paredescasa.skybox_casa(26, 30, 30, textWall.GLindex, textPiso.GLindex, textPuerta_Casa.GLindex, textTechoCasa.GLindex, 1.0f, 1.0f, 1.0f, trasladoPuerta);
		glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	//Techo de la casa
	glPushMatrix();
		glTranslatef(0, 16.5, 0);
		if (terror == false)
			cubo.prisma_tablero(4, 35, 35, textTechoCasa.GLindex, 3.0);
		else 
			cubo.prisma_tablero(4, 35, 35, textTechoCasa.GLindex, 8.0 );
	glPopMatrix();
 }


void mesa(GLfloat xMadera, GLfloat yMadera, GLfloat zMadera, GLfloat xPosMesa, GLfloat yPosMesa, GLfloat zPosMesa){
	//mesa	
		//tabla
		glPushMatrix();
			glScalef(xMadera, yMadera, zMadera);
			glTranslatef(xPosMesa, yPosMesa, zPosMesa);
			glPushMatrix();
				glScalef(10,.5,5);
				tablaMesa.prisma (1.0, 1.0, 1.0, textMarble.GLindex);
			//patas
			glPopMatrix();
			glPushMatrix();
				glTranslatef(4, -2.5, 2);
				glScalef( .5, 4.5,.5);
				pata1Mesa.prisma (1.0, 1.0, 1.0, textMarble.GLindex);
				glTranslatef(0, 0, -8);
				pata2Mesa.prisma (1.0, 1.0, 1.0, textMarble.GLindex);
				glTranslatef(-16, 0, 0);
				pata3Mesa.prisma (1.0, 1.0, 1.0, textMarble.GLindex);
				glTranslatef(0, 0, 8);
				pata4Mesa.prisma (1.0, 1.0, 1.0, textMarble.GLindex);
			glPopMatrix();
		glPopMatrix();

		return;
}

void silla(GLfloat xMadera, GLfloat yMadera, GLfloat zMadera, GLfloat xPosSilla, GLfloat yPosSilla, GLfloat zPosSilla){
	float numBarrotes = -2.9;
	glPushMatrix();
		//posicion y tamaño
		glScalef(xMadera, yMadera, zMadera);
		glTranslatef(xPosSilla, yPosSilla, zPosSilla);
		//figura
		glPushMatrix();
			glScalef(3,.5,3);
			asientoSilla.prisma (1.0, 1.0, 1.0, textSilla.GLindex);//1
		glPopMatrix();
		glPushMatrix();
			glTranslatef(1.35, -3.25,-1.35);
			glScalef( .3,6,.3);
			pata1Mesa.prisma (1.0, 1.0, 1.0, textSilla.GLindex);
			glTranslatef(-9.0, 0, 0);
			pata2Mesa.prisma (1.0, 1.0, 1.0, textSilla.GLindex);
			glTranslatef(0, 0, 9);
			pata3Mesa.prisma (1.0, 1.0, 1.0, textSilla.GLindex);
			glTranslatef(9, 0, 0);
			pata4Mesa.prisma (1.0, 1.0, 1.0, textSilla.GLindex);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(1.45, 4.25, -1.45);
			glScalef( 0.1,8.0,0.1);
			respaldoSilla1.prisma(1.0,1.0,1.0, textSilla.GLindex);
			for(int numBar = 1; numBar <= 10; numBar++){
				glTranslatef(numBarrotes,0,0);
				respaldoSilla1.prisma(1.0,1.0,1.0, textSilla.GLindex);
			}
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0,1,-1.45);
			glScalef( 2.3,0.1,0.1);
			respaldoSilla1.prisma(1.0,1.0,1.0, textSilla.GLindex);
			//
			for(int numBar = 1; numBar <= 30; numBar++){
				glTranslatef(0,2,0);
				respaldoSilla1.prisma(1.0,1.0,1.0, textSilla.GLindex);
			}
			glTranslatef(0,12,0);
			glScalef( 1.5,1,1);
			respaldoSilla1.prisma(1.0,1.0,1.0, textSilla.GLindex);
		glPopMatrix();
	glPopMatrix();

	return;
}

void comedor(void){
	glPushMatrix();
			mesa(2,2,2,0,1,0);
	glPopMatrix();
	//SILLAS
	glPushMatrix();
		glTranslatef(0,0,-0.5);
		glRotatef(25, 0,1,0);
		glTranslatef(2,0,-0.5);
		silla(1,1,1,5,-1,-4.5);
		glPopMatrix();
		glPushMatrix();
			silla(1,1,1,-5,-1,-4.5);
		glPopMatrix();
		glPushMatrix();
			silla(1,1,1,0,-1,-4.5);
		glPopMatrix();
		//giramos con respecto Z
		glScalef(1,1,-1);
		glPushMatrix();				
		glPushMatrix();
			silla(1,1,1,5,-1,-4.5);
		glPopMatrix();
		glPushMatrix();
			silla(1,1,1,-5,-1,-4.5);
		glPopMatrix();
		glPushMatrix();
			silla(1,1,1,0,-1,-4.5);
		glPopMatrix();
	glPopMatrix();
		return;
}


void cuadro(void){
	glPushMatrix();
		glScalef(1,1,-1);
		glTranslatef(-19,30,-42);
		glRotatef(90, 0, 0, 1);
		cubo.prisma(24,40,.2, textCuadro1.GLindex);
		glTranslatef(0,0,-.05);
	glPopMatrix();
	return;
}

//****ROSE****
void dibujaCama (GLfloat xMadera, GLfloat yMadera, GLfloat zMadera, GLfloat xPosCama, GLfloat yPosCama, GLfloat zPosCama)
{			
			glPushMatrix(); 
			glScalef(xMadera, yMadera, zMadera); //posicion y tamaño 
			glTranslatef(xPosCama, yPosCama, zPosCama); //figura 

			//dibujamos la cabecera
			glPushMatrix(); 
				glTranslatef(9.0,1.5,0.5);
				glScalef(18.0,3.0,1.0);  //Tamaño de cabecera
				cama.prisma(1.0,1.0,1.0, textMaderaCama.GLindex);
			glPopMatrix();

			glPushMatrix(); 
				glTranslatef(0.5,6.0,0.5);
				glScalef(1.0,6.0,1.0);  
				cama.prisma(1.0,1.0,1.0, textMaderaCama.GLindex);
			glPopMatrix();

			glPushMatrix(); 
				glTranslatef(4.0,6.0,0.5);
				glScalef(4.0,6.0,1.0);  
				cama.prisma(1.0,1.0,1.0, textMaderaCama.GLindex);
			glPopMatrix();

			glPushMatrix(); 
				glTranslatef(9.0,6.0,0.5);
				glScalef(4.0,6.0,1.0);  
				cama.prisma(1.0,1.0,1.0, textMaderaCama.GLindex);
			glPopMatrix();

			glPushMatrix(); 
				glTranslatef(14.0,6.0,0.5);
				glScalef(4.0,6.0,1.0);  
				cama.prisma(1.0,1.0,1.0, textMaderaCama.GLindex);
			glPopMatrix();

			glPushMatrix(); 
				glTranslatef(17.5,6.0,0.5);
				glScalef(1.0,6.0,1.0);  
				cama.prisma(1.0,1.0,1.0, textMaderaCama.GLindex);
			glPopMatrix();

			glPushMatrix(); 
				glTranslatef(9.0,9.5,0.5);
				glScalef(18.0,1.0,1.0);  
				cama.prisma(1.0,1.0,1.0, textMaderaCama.GLindex);
			glPopMatrix();

			glPushMatrix(); 
				glTranslatef(0.5,5.0,0.5);
				glScalef(1.0,10.0,1.0);
				cama.prisma(1.0,1.0,1.0, textMaderaCama.GLindex);
			glPopMatrix();


			//dibujamos la base de la cama
			glPushMatrix(); 
				glTranslatef(0.5,1.0,11.0);
				glScalef(1.0,2.0,22.0);
				cama.prisma(1.0,1.0,1.0, textMaderaCama.GLindex);
			glPopMatrix();

			glPushMatrix(); 
				glTranslatef(17.5,1.0,11.0);
				glScalef(1.0,2.0,22.0);
				cama.prisma(1.0,1.0,1.0, textMaderaCama.GLindex);
			glPopMatrix();

			//colchon
			glPushMatrix(); 
				glTranslatef(9.0,3.5,11.0);
				glScalef(18.0,3.0,20.0);
				cama.prisma(1.0,1.0,1.0, textColcha.GLindex);
			glPopMatrix();

			//almohada izquierda
			glPushMatrix(); 
				glTranslatef(4.0,5.5,3.0);
				glScalef(8.0,1.0,4.0);
				cama.prisma(1.0,1.0,1.0, textAlmohada.GLindex);
			glPopMatrix();

			//almohada derecha
			glPushMatrix(); 
				glTranslatef(14.0,5.5,3.0);
				glScalef(8.0,1.0,4.0);
				cama.prisma(1.0,1.0,1.0, textAlmohada.GLindex);
			glPopMatrix();


			//enfrente
			glPushMatrix(); 
				glTranslatef(9.0,6.5,21.5);
				glScalef(16.0,1.0,1.0);
				cama.prisma(1.0,1.0,1.0, textMaderaCama.GLindex);
			glPopMatrix();

			glPushMatrix(); 
				glTranslatef(9.0,2.5,21.5);
				glScalef(16.0,5.0,1.0);
				cama.prisma(1.0,1.0,1.0, textMaderaCama.GLindex);
			glPopMatrix();

			glPushMatrix(); 
				glTranslatef(0.5,4.0,21.5);
				glScalef(1.0,8.0,1.0);
				cama.prisma(1.0,1.0,1.0, textMaderaCama.GLindex);
			glPopMatrix();

			glPushMatrix(); 
				glTranslatef(17.5,4.0,21.5);
				glScalef(1.0,8.0,1.0);
				cama.prisma(1.0,1.0,1.0, textMaderaCama.GLindex);
			glPopMatrix();


			//patas
			glPushMatrix(); 
				glTranslatef(0.5,-1.0,21.5);
				glScalef(1.0,2.0,1.0);
				cama.prisma(1.0,1.0,1.0, textMaderaCama.GLindex);
			glPopMatrix();

			glPushMatrix(); 
				glTranslatef(17.5,-1.0,21.5);
				glScalef(1.0,2.0,1.0);
				cama.prisma(1.0,1.0,1.0, textMaderaCama.GLindex);
			glPopMatrix();

			glPushMatrix(); 
				glTranslatef(17.5,-1.0,0.5);
				glScalef(1.0,2.0,1.0);
				cama.prisma(1.0,1.0,1.0, textMaderaCama.GLindex);
			glPopMatrix();

			glPushMatrix(); 
				glTranslatef(0.5,-1.0,0.5);
				glScalef(1.0,2.0,1.0);
				cama.prisma(1.0,1.0,1.0, textMaderaCama.GLindex);
			glPopMatrix();
			glPopMatrix();
}


void dibujaBuro(GLfloat xMadera, GLfloat yMadera, GLfloat zMadera, GLfloat xPosBuro, GLfloat yPosBuro, GLfloat zPosBuro)
{
		glPushMatrix();		
			glScalef(xMadera, yMadera, zMadera); 
			glTranslatef(xPosBuro, yPosBuro, zPosBuro); //figura 
			//contorno
			glPushMatrix();
				glTranslatef(1.5,5.5,1.5);
				glScalef(1.0,11.0,1.0);
				buro.prisma(1.0,1.0,1.0, textMaderaBuro.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(1.5,5.5,8.5);
				glScalef(1.0,11.0,1.0);
				buro.prisma(1.0,1.0,1.0, textMaderaBuro.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(14.5,5.5,1.5);
				glScalef(1.0,11.0,1.0);
				buro.prisma(1.0,1.0,1.0, textMaderaBuro.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(14.5,5.5,8.5);
				glScalef(1.0,11.0,1.0);
				buro.prisma(1.0,1.0,1.0, textMaderaBuro.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(8.0,10.5,8.5);
				glScalef(12.0,1.0,1.0);
				buro.prisma(1.0,1.0,1.0, textMaderaBuro.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(1.5,10.5,5.0);
				glScalef(1.0,1.0,6.0);
				buro.prisma(1.0,1.0,1.0, textMaderaBuro.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(14.5,10.5,5.0);
				glScalef(1.0,1.0,6.0);
				buro.prisma(1.0,1.0,1.0, textMaderaBuro.GLindex);
			glPopMatrix();


			glPushMatrix();
				glTranslatef(8.0,6.5,8.5);
				glScalef(12.0,1.0,1.0);
				buro.prisma(1.0,1.0,1.0, textMaderaBuro.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(1.5,6.5,5.0);
				glScalef(1.0,1.0,6.0);
				buro.prisma(1.0,1.0,1.0, textMaderaBuro.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(14.5,6.5,5.0);
				glScalef(1.0,1.0,6.0);
				buro.prisma(1.0,1.0,1.0, textMaderaBuro.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(8.0,2.5,1.5);
				glScalef(12.0,1.0,1.0);
				buro.prisma(1.0,1.0,1.0, textMaderaBuro.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(8.0,2.5,8.5);
				glScalef(12.0,1.0,1.0);
				buro.prisma(1.0,1.0,1.0, textMaderaBuro.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(1.5,2.5,5.0);
				glScalef(1.0,1.0,6.0);
				buro.prisma(1.0,1.0,1.0, textMaderaBuro.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(14.5,2.5,5.0);
				glScalef(1.0,1.0,6.0);
				buro.prisma(1.0,1.0,1.0, textMaderaBuro.GLindex);
			glPopMatrix();

			//rellenos
			glPushMatrix();
				glTranslatef(13.5,6.5,5.0);
				glScalef(1.0,7.0,6.0);
				buro.prisma(1.0,1.0,1.0, textMaderaBuro.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(2.5,6.5,5.0);
				glScalef(1.0,7.0,6.0);
				buro.prisma(1.0,1.0,1.0, textMaderaBuro.GLindex);
			glPopMatrix();

			//pared atras
			glPushMatrix();
				glTranslatef(8.0,6.5,1.5);
				glScalef(12.0,9.0,1.0);
				buro.prisma(1.0,1.0,1.0, textMaderaBuro.GLindex);
			glPopMatrix();


			//base arriba
			glPushMatrix();
				glTranslatef(8.0,11.5,5.0);
				glScalef(16.0,1.0,10.0);
				buro.prisma(1.0,1.0,1.0, textMaderaBuro.GLindex);
			glPopMatrix();


			//cajones
			glPushMatrix();
				glTranslatef(8.0,8.5,9.25);
				glScalef(12.0,3.0,0.5);
				buro.prisma(1.0,1.0,1.0, textMaderaBuro.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(8.0,4.5,9.25);
				glScalef(12.0,3.0,0.5);
				buro.prisma(1.0,1.0,1.0, textMaderaBuro.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(8.0,8.5,9.75);
				glScalef(2.0,1.0,0.5);
				buro.prisma(1.0,1.0,1.0, textMaderaBuro.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(8.0,4.5,9.75);
				glScalef(2.0,1.0,0.5);
				buro.prisma(1.0,1.0,1.0, textMaderaBuro.GLindex);
			glPopMatrix();
		glPopMatrix();
}

void esferas_navidad() {
	//1
	glPushMatrix();
		glColor3f(0.0, 0.0, 1.0);
		glTranslatef(16, 15, -15);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1);
		esfera1.esfera(1, 10, 10, textEsfera1.GLindex);
		glDisable(GL_ALPHA_TEST);
	glPopMatrix();
	//2
	glPushMatrix();
		glColor3f(1.0, 1.0, 0.0);
		glTranslatef(20, 19, -9);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1);
		esfera2.esfera(1, 10, 10, textEsfera2.GLindex);
		glDisable(GL_ALPHA_TEST);
	glPopMatrix();
	//3
	glPushMatrix();
		glColor3f(1.0, 0.0, 1.0);
		glTranslatef(20, 19, -21);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1);
		esfera3.esfera(1, 10, 10, textEsfera3.GLindex);
		glDisable(GL_ALPHA_TEST);
	glPopMatrix();
	//4
	glPushMatrix();
		glColor3f(1.0, 0.5, 0.0);
		glTranslatef(21, 30, -15);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1);
		esfera4.esfera(1, 10, 10, textEsfera4.GLindex);
		glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	//5
	glPushMatrix();
		glColor3f(0.5, 1.0, 0.5);
		glTranslatef(22, 26, -10);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1);
		esfera5.esfera(1, 10, 10, textEsfera5.GLindex);
		glDisable(GL_ALPHA_TEST);
	glPopMatrix();
}

void navidad() {

	if (terror == false) {
		glPushMatrix();//Tronco
		glTranslatef(25, -10, -15);
		troncoNavidad.cilindro(2.0, 20.0, 10, textTroncoNavidad.GLindex);
		glPopMatrix();

		glPushMatrix();//Hojas
		glTranslatef(25, 10, -15);
		hojasNavidad.cono(30.0, 10.0, 1500, textHojasNavidad.GLindex, 3.0);
		glPopMatrix();

		glPushMatrix();//Regalo
		glTranslatef(15, -8, -15);
		glScalef(10, 7, 7);
		regalo.prisma2(textRegaloFront.GLindex, textRegalo.GLindex);
		glPopMatrix();

		glPushMatrix();//Esferas
		esferas_navidad();
		glPopMatrix();

	}
}

void texturas_casa_terror() {

	text1.LoadBMP("texturas/cielo1.bmp");
	text1.BuildGLTexture();
	text1.ReleaseImage();

	textPuerta_Casa.LoadBMP("casa/puerta.bmp");
	textPuerta_Casa.BuildGLTexture();
	textPuerta_Casa.ReleaseImage();

	textWall.LoadBMP("casa/pared_vieja.bmp");
	textWall.BuildGLTexture();
	textWall.ReleaseImage();

	textSilla.LoadBMP("casa/madera_comedor_terror.bmp");
	textSilla.BuildGLTexture();
	textSilla.ReleaseImage();

	textMarble.LoadBMP("casa/madera_comedor_terror.bmp");
	textMarble.BuildGLTexture();
	textMarble.ReleaseImage();

	textPiso.LoadBMP("casa/piso_terror.bmp");
	textPiso.BuildGLTexture();
	textPiso.ReleaseImage();

	textTechoCasa.LoadBMP("casa/tejado_terror.bmp");
	textTechoCasa.BuildGLTexture();
	textTechoCasa.ReleaseImage();

	textCuadro1.LoadBMP("casa/cuadro_terror.bmp");
	textCuadro1.BuildGLTexture();
	textCuadro1.ReleaseImage();

	textGrass.LoadBMP("texturas/pasto.bmp");
	textGrass.BuildGLTexture();
	textGrass.ReleaseImage();

	textAlmohada.LoadBMP("casa/almohada.bmp");
	textAlmohada.BuildGLTexture();
	textAlmohada.ReleaseImage();

	textColcha.LoadBMP("casa/colcha.bmp");
	textColcha.BuildGLTexture();
	textColcha.ReleaseImage();

	textMaderaBuro.LoadBMP("casa/buro_terror.bmp");
	textMaderaBuro.BuildGLTexture();
	textMaderaBuro.ReleaseImage();

	textMaderaCama.LoadBMP("casa/cama_terror.bmp");
	textMaderaCama.BuildGLTexture();
	textMaderaCama.ReleaseImage();

	textChimenea.LoadBMP("casa/buro_terror.bmp");
	textChimenea.BuildGLTexture();
	textChimenea.ReleaseImage();

	textSChimenea.LoadBMP("casa/buro_terror.bmp");
	textSChimenea.BuildGLTexture();
	textSChimenea.ReleaseImage();

	textFuego.LoadTGA("casa/Fuego.tga");
	textFuego.BuildGLTexture();
	textFuego.ReleaseImage();

	///////***ARBOLES FUERA DE CASA, CERCA///////
	textTree.LoadTGA("texturas/treeSeco.tga");
	textTree.BuildGLTexture();
	textTree.ReleaseImage();

	textTreeN.LoadTGA("texturas/treeSeco.tga");
	textTreeN.BuildGLTexture();
	textTreeN.ReleaseImage();

	textTreeN2.LoadTGA("texturas/treeSeco.tga");
	textTreeN2.BuildGLTexture();
	textTreeN2.ReleaseImage();

	textTreeV.LoadTGA("texturas/treeSeco.tga");
	textTreeV.BuildGLTexture();
	textTreeV.ReleaseImage();

	textTree0.LoadTGA("texturas/treeSeco.tga");
	textTree0.BuildGLTexture();
	textTree0.ReleaseImage();

	textTree1.LoadTGA("texturas/treeSeco.tga");
	textTree1.BuildGLTexture();
	textTree1.ReleaseImage();

}

void DibujaChimenea() {

	glPushMatrix();//Caja
		glTranslatef(20, 3, 32);
		glRotatef(180, 0, 1, 0);
		chimenea.skybox_sin_tapa(20, 25, 20, textChimenea.GLindex, 1);
	glPopMatrix();

	glPushMatrix();//Subida a techo
		glTranslatef(20, 51, 35);
		glRotatef(90, 0, 0, 1);
		chimenea.prisma(10, 72, 10, textMaderaBuro.GLindex);
	glPopMatrix();

	glPushMatrix();//Fuego
		glTranslatef(20, -10, 30);
		glRotatef(angFuego, 0, 1, 0);
		planos_cruzados(textFuego.GLindex);
	glPopMatrix();
}
//END CASA////////////////////////////////////

void DibujaArbolesCasa() {
	
	glDisable(GL_LIGHTING);

	glPushMatrix();//1
		glTranslatef(30, -1, 25);
		glRotatef(angArboles, 0, 1, 0);
		planos_cruzados(textTree.GLindex);
	glPopMatrix();

	glPushMatrix();//2
		glTranslatef(30, 0, -25);
		glRotatef(angArboles, 0, 1, 0);
		planos_cruzados(textTreeN.GLindex);
	glPopMatrix();

	glPushMatrix();//3
		glTranslatef(-30, -1, 25);
		glRotatef(angArboles, 0, 1, 0);
		planos_cruzados(textTreeN2.GLindex);
	glPopMatrix();

	glPushMatrix();//4
		glTranslatef(-30, 0, -25);
		glRotatef(angArboles, 0, 1, 0);
		planos_cruzados(textTreeV.GLindex);
	glPopMatrix();

	glPushMatrix();//5
		glTranslatef(0, 0, 30);
		glRotatef(angArboles, 0, 1, 0);
		planos_cruzados(textTree0.GLindex);
	glPopMatrix();

	glPushMatrix();//6
		glTranslatef(0, 0, -25);
		glRotatef(angArboles, 0, 1, 0);
		planos_cruzados(textTree1.GLindex);
	glPopMatrix();

	glEnable(GL_LIGHTING);
}

/////////FUNCIONES DE SONIDO/////////////
void PlayAire() {
	PlaySound(TEXT("sonidos/aire.wav"), NULL, SND_LOOP | SND_ASYNC);
}

void PlayMozart() {
	PlaySound(TEXT("sonidos/terror.wav"), NULL, SND_LOOP | SND_ASYNC);
}


///////SND_ASYNC hilo que reproduce una vez
////////SND_LOOP | SND_ASYNC reproduce en bucle y si hay otro sonido se detiene

void texturaAleatoriaArbol(float i, float j) {

	if (i > 4 && j > 3) {
		planos_cruzados(textTree.GLindex);
	}

	if (i > 4 && j < 3) {
		planos_cruzados(textTreeV.GLindex);
	}

	if (i < 4 && j > 3) {
		planos_cruzados(textTreeN.GLindex);
	}

	if (i < 4 && j < 3) {
		glPushMatrix();
			glTranslatef(0, -1, 0);
			planos_cruzados(textTreeN2.GLindex);
		glPopMatrix();
	}

}

void DibujaBosque() {
	glScalef(1, 2, 1);
	glPushMatrix(); //Parte A
		for (i = 0; i < 9; i++) {
			for (j = 0; j < 7; j++) {
				glPushMatrix();
					glTranslatef(i * 30, 0, j*-20);
					glRotatef(angArboles, 0, 1, 0);
					texturaAleatoriaArbol(i, j);
				glPopMatrix();
			}
	}
	glPopMatrix();

	glPushMatrix(); //Parte B
		glTranslatef(0, 0, 45);
		for (i = 0; i < 9; i++) {
			for (j = 0; j < 7; j++) {
				glPushMatrix();
					glTranslatef(i * 30, 0, j*+20);
					glRotatef(angArboles, 0, 1, 0);
					texturaAleatoriaArbol(i, j);
				glPopMatrix();
			}
		}
	glPopMatrix();
}

void DibujaFantasma() {
	glDisable(GL_COLOR_MATERIAL);

	glPushMatrix();//Cuerpo
		glScalef(0.005, 0.005, 0.006);
		fantasma.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix();//Cara
		glTranslatef(0, 0.5, 3.6);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1);
		cubo.prisma(2.5, 2.5, 0.0001, textFantasma.GLindex);
		glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	glEnable(GL_COLOR_MATERIAL);
}


void keyboardSimulado(char simkey)  // Create Keyboard Function
{
	switch (simkey) {
	case 'w':   //Movimientos de camara
		objCamera.Move_Camera(CAMERASPEED + 0.2);
		break;
	case 'W':
		objCamera.Move_Camera(CAMERASPEED + 0.6);
		break;

	case 's':
	case 'S':
		objCamera.Move_Camera(-(CAMERASPEED + 0.2));
		break;

	case 'a':
	case 'A':
		objCamera.Strafe_Camera(-(CAMERASPEED + 0.4));
		break;

	case 'd':
	case 'D':
		objCamera.Strafe_Camera(CAMERASPEED + 0.4);
		break;

	case 'k':		//
	case 'K':
		if (FrameIndex<MAX_FRAMES)
		{
			saveFrame();
		}
		break;

	case 'l':
	case 'L':
		if (play == false && (FrameIndex>1))
		{

			resetElements();
			//First Interpolation				
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
		}
		break;

	case 'z':
	case 'Z':
		//Interaccion regalo
		if (objCamera.mPos.z > -7 && objCamera.mPos.z < -1 && objCamera.mPos.x>0 && objCamera.mPos.x<6)
		{
			texturas_casa_terror();
			terror = true;
			PlaySound(NULL, NULL, 0);
			//PlayMozart();
		}
		//Interaccion puerta
		if (objCamera.mPos.z >3 && objCamera.mPos.z < 14 && objCamera.mPos.x>10 && objCamera.mPos.x < 19) {
			if (puertaAbierta == true) {
				if (trasladoPuerta > 0.0)
					trasladoPuerta -= 1.0;
				else
					puertaAbierta = false;
			}
			else {
				if (trasladoPuerta < 4.0)
					trasladoPuerta += 1.0;
				else
					puertaAbierta = true;
			}
		}
		break;

	case 'x':
	case 'X':
		playfantasma = !playfantasma;
		break;

	case 'c':
	case 'C':
		break;

	case 'j':
	case 'J':
		break;

	case 'b':
		break;

	case 'B':
		break;

	case 'p':
		break;

	case 'P':
		break;

	case '1':
		g_lookupdown -= 1.0f;	
		break;

	case '2':
		objCamera.Rotate_View(-CAMERASPEED);
		break;

	case '3':
		objCamera.Rotate_View(CAMERASPEED);
		break;

	case '4':
		g_lookupdown += 1.0f;
		break;

	case '5':
		objCamera.UpDown_Camera(CAMERASPEED * 10);
		break;

	case '6':
		objCamera.UpDown_Camera(-CAMERASPEED * 10);
		break;

	case 27:        // Cuando Esc es presionado...
		exit(0);   // Salimos del programa
		break;
	default:        // Cualquier otra
		break;
	}

}

void InitGL ( GLvoid )     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	glShadeModel (GL_SMOOTH);

	glLightfv(GL_LIGHT1, GL_POSITION, Position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	//////EXTERIOR//////////

	textGrass.LoadBMP("texturas/pasto.bmp");

	textGrass.BuildGLTexture();
	textGrass.ReleaseImage();
    
    text1.LoadBMP("texturas/cielo.bmp");
	text1.BuildGLTexture();
	text1.ReleaseImage();

	textMar.LoadTGA("texturas/mar.tga");
	textMar.BuildGLTexture();
	textMar.ReleaseImage();

	textPiedra.LoadTGA("texturas/piedra.tga");
	textPiedra.BuildGLTexture();
	textPiedra.ReleaseImage();

	//Texturas casa////////////////////////////////////////////
	textPuerta_Casa.LoadBMP("casa/door_3_4_puerta.bmp");
	textPuerta_Casa.BuildGLTexture();
	textPuerta_Casa.ReleaseImage();

	textWall.LoadBMP("casa/pared_normal.bmp");
	textWall.BuildGLTexture();
	textWall.ReleaseImage();

	textSilla.LoadBMP("casa/madera.bmp");
	textSilla.BuildGLTexture();
	textSilla.ReleaseImage();

	textMarble.LoadBMP("casa/madera.bmp");
	textMarble.BuildGLTexture();
	textMarble.ReleaseImage();

	textPiso.LoadBMP("casa/floor-parquet.bmp");
	textPiso.BuildGLTexture();
	textPiso.ReleaseImage();

	textTechoCasa.LoadBMP("casa/tejado.bmp");
	textTechoCasa.BuildGLTexture();
	textTechoCasa.ReleaseImage();
	
	textCuadro1.LoadBMP("casa/cuadro.bmp");
	textCuadro1.BuildGLTexture();
	textCuadro1.ReleaseImage();
	
	textAlmohada.LoadBMP("casa/almohada.bmp");
	textAlmohada.BuildGLTexture();
	textAlmohada.ReleaseImage();

	textColcha.LoadBMP("casa/colcha.bmp");
	textColcha.BuildGLTexture();
	textColcha.ReleaseImage();

	textMaderaBuro.LoadBMP("casa/buro.bmp");
	textMaderaBuro.BuildGLTexture();
	textMaderaBuro.ReleaseImage();

	textMaderaCama.LoadBMP("casa/maderaCama.bmp");
	textMaderaCama.BuildGLTexture();
	textMaderaCama.ReleaseImage();

	textChimenea.LoadBMP("casa/brickwall.bmp");
	textChimenea.BuildGLTexture();
	textChimenea.ReleaseImage();

	textSChimenea.LoadBMP("casa/madera3.bmp");
	textSChimenea.BuildGLTexture();
	textSChimenea.ReleaseImage();
	
	textFuego.LoadTGA("casa/Fuego.tga");
	textFuego.BuildGLTexture();
	textFuego.ReleaseImage();
	

	//***Navidad***
	textTroncoNavidad.LoadBMP("casa/tronco_navidad.bmp");
	textTroncoNavidad.BuildGLTexture();
	textTroncoNavidad.ReleaseImage();

	textHojasNavidad.LoadBMP("casa/grass_2.bmp");
	textHojasNavidad.BuildGLTexture();
	textHojasNavidad.ReleaseImage();

	textRegalo.LoadBMP("casa/regalo.bmp");
	textRegalo.BuildGLTexture();
	textRegalo.ReleaseImage();

	textRegaloFront.LoadBMP("casa/regaloFront.bmp");
	textRegaloFront.BuildGLTexture();
	textRegaloFront.ReleaseImage();

	textEsfera1.LoadTGA("casa/papel.tga");
	textEsfera1.BuildGLTexture();
	textEsfera1.ReleaseImage();

	textEsfera2.LoadTGA("casa/papel2.tga");
	textEsfera2.BuildGLTexture();
	textEsfera2.ReleaseImage();

	textEsfera3.LoadTGA("casa/papel3.tga");
	textEsfera3.BuildGLTexture();
	textEsfera3.ReleaseImage();

	textEsfera4.LoadTGA("casa/papel4.tga");
	textEsfera4.BuildGLTexture();
	textEsfera4.ReleaseImage();

	textEsfera5.LoadTGA("casa/papel5.tga");
	textEsfera5.BuildGLTexture();
	textEsfera5.ReleaseImage();

///////***ARBOLES FUERA DE CASA, CERCA///////

	textTree.LoadTGA("texturas/tree.tga");
	textTree.BuildGLTexture();
	textTree.ReleaseImage();

	textTreeN.LoadTGA("texturas/treeN.tga");
	textTreeN.BuildGLTexture();
	textTreeN.ReleaseImage();

	textTreeN2.LoadTGA("texturas/treeN2.tga");
	textTreeN2.BuildGLTexture();
	textTreeN2.ReleaseImage();

	textTreeV.LoadTGA("texturas/treeV.tga");
	textTreeV.BuildGLTexture();
	textTreeV.ReleaseImage();

	textTree0.LoadTGA("texturas/tree0.tga");
	textTree0.BuildGLTexture();
	textTree0.ReleaseImage();

	textTree1.LoadTGA("texturas/tree1.tga");
	textTree1.BuildGLTexture();
	textTree1.ReleaseImage();


	///////PERSONAJES///////////
	textFantasma.LoadTGA("texturas/fantasma.tga"); 
	textFantasma.BuildGLTexture();
	textFantasma.ReleaseImage();

	//END NEW//////////////////////////////

	///////Modelos 3ds/////////
	fantasma._3dsLoad("modelos/fantasma.3ds");


	objCamera.Position_Camera(-6+250, 4.0f,-5, -6+250, 4.0f,0, 0, 1, 0); //Posision inicial de la camara

	//NEW Iniciar variables de KeyFrames
	for(int i=0; i<MAX_FRAMES; i++)
	{
		KeyFrame[i].posX =0;
		KeyFrame[i].posY =0;
		KeyFrame[i].posZ =0;
		KeyFrame[i].incX =0;
		KeyFrame[i].incY =0;
		KeyFrame[i].incZ =0;

		KeyFrame[i].viewX = 0;
		KeyFrame[i].viewY = 0;
		KeyFrame[i].viewZ = 0;
		KeyFrame[i].IncviewX = 0;
		KeyFrame[i].IncviewY = 0;
		KeyFrame[i].incviewZ = 0;
	}
	//NEW//////////////////NEW//////////////////NEW///////////

}

void pintaTexto(float x, float y, float z, void *font,char *string)
{
  
  char *c;     //Almacena los caracteres a escribir
  glRasterPos3f(x, y, z);	//Posicion apartir del centro de la ventana
  //glWindowPos2i(150,100);
  for (c=string; *c != '\0'; c++) //Condicion de fin de cadena
  {
    glutBitmapCharacter(font, *c); //imprime
  }
}


void display ( void )   // Creamos la funcion donde se dibuja
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	glPushMatrix(); //Push inicial
	
	glRotatef(g_lookupdown,1.0f,0,0);

		gluLookAt(	objCamera.mPos.x,  objCamera.mPos.y,  objCamera.mPos.z,	
					objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,	
					objCamera.mUp.x,   objCamera.mUp.y,   objCamera.mUp.z);
	

		glPushMatrix();		

			glPushMatrix(); //Creamos cielo
				glDisable(GL_LIGHTING);
					glTranslatef(0,2999.5,0);
					glRotatef(angNubes, 0, 1, 0);
					fig1.skybox_cielo(2500.0, 6000.0, 2500.0,text1.GLindex, textMar.GLindex, text1.GLindex, 1.0);
				glEnable(GL_LIGHTING);
			glPopMatrix();	

			///////PASTO_ISLAS////////////
			glPushMatrix();
				glDisable(GL_LIGHTING);

				//glTranslatef(0, 0, 0);
				pasto.prisma_tablero(0.1, 80, 80, textGrass.GLindex, 50.0);
				glTranslatef(190, 0, 10);
				pasto.prisma_tablero(0.1, 280, 300, textGrass.GLindex, 50.0);

				glEnable(GL_LIGHTING);
			glPopMatrix();

			/////////FANTASMAS////////////
			if (terror == true) {
				playfantasma = true;
				glPushMatrix();
					glDisable(GL_LIGHTING);
					glTranslatef(160, 10, 10);

					glPushMatrix(); //Fantasma 1
						glTranslatef(fantasma1X, fantasma1Y, fantasma1Z);
						glRotatef(90 + angFantasma, 0, 1, 0);
						DibujaFantasma();
					glPopMatrix();

					glTranslated(15, 0, 0);
					glPushMatrix();//Fantasma 2
						glTranslatef(fantasma2X, fantasma2Y, fantasma2Z);
						glRotatef(angFantasma2, 0, 1, 0);
						DibujaFantasma();
					glPopMatrix();

					glTranslated(0, 0, -80);
					glPushMatrix();//Fantasma 3
						glTranslatef(fantasma3X, fantasma3Y, fantasma3Z);
						glRotatef(angFantasma3, 0, 1, 0);
						DibujaFantasma();
					glPopMatrix();

					glTranslated(-105, 0, -60);
					glPushMatrix();//Fantasma 4
						glTranslatef(fantasma4X, fantasma4Y, fantasma4Z);
						glRotatef(angFantasma4, 0, 1, 0);
						DibujaFantasma();
					glPopMatrix();

					glEnable(GL_LIGHTING);
				glPopMatrix();
			}
			////////ARBOLES CASA-COLINDANTES
			glPushMatrix();
				DibujaArbolesCasa();
			glPopMatrix();

			////////BOSQUE///////
			glPushMatrix();
				glDisable(GL_LIGHTING);
				glTranslatef(55, -1, -10);
				DibujaBosque();
				glEnable(GL_LIGHTING);
			glPopMatrix();

			//////CAMINO//////////
			glPushMatrix();
				glDisable(GL_LIGHTING);
				glTranslatef(165, 0.2, 10);
				camino.prisma_tablero(0.1, 300, 10, textPiedra.GLindex, 10.0);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			//CASA///////////////////
			glPushMatrix(); //Casa completa
				glTranslatef(0, 7.7, 0);
				//*****Paredes, Piso y Techo *****
				glPushMatrix();
					glDisable(GL_LIGHTING);
					glScalef(1.0, 0.5, 1.0);
					dibujaContornoCasa();
					glEnable(GL_LIGHTING);
				glPopMatrix();
				//¨****Interior casa*****
				glPushMatrix();
					glScalef(1.0, 0.5, 1.0);
					glTranslatef(-2.3, -12, 0.2);
					glDisable(GL_LIGHTING);
					glScalef(0.3, 0.3, 0.3);
			
					glPushMatrix();
						//******Cuadro****			
						cuadro();
						//******Chimenea****
						glPushMatrix();
							
							glTranslatef(-10, 0, 0);
							DibujaChimenea();

						glPopMatrix();  //De chimenea
						//****COMEDOR***
						glPushMatrix();
							glTranslatef(-20,0,25);
							glScalef(1.3,1.3,1.3);
							comedor();
						glPopMatrix();

						//*****CAMA Y BURO*****
						glPushMatrix(); 
							glPushMatrix();
								glTranslatef(0,0,-0.5); 
								glRotatef(90, 0,1,0); 
								glTranslatef(2,-0.5,-0.5);
								dibujaCama(1.1,1.1,1.1,14.0,-5.5,-37.0); 
							glPopMatrix();
							glPushMatrix();
								glRotatef(90, 0,1,0); 
								dibujaBuro(1,1,1,-2,-9.5,-42.0); 
							glPopMatrix();
						glPopMatrix();

						////***Navidad, arbol y regalos
						glPushMatrix();
							glTranslatef(10, 0, 0);
							navidad();
						glPopMatrix(); //De navidad

					glPopMatrix();//Del interior de la casa (muebles)

				glEnable(GL_LIGHTING);
				glPopMatrix();//Del interior de la casa (para trasladar)
			
			glPopMatrix();// De casa entera

			glColor3f(1.0,1.0,1.0);

		glPopMatrix(); //Del ambiente

	glPopMatrix(); //Pop final

	glutSwapBuffers ( );

}

void animacion()
{
	/////Recorrido
	//fprintf(escribir, "c"); //Silencio del teclado
	//c = fgetc(ap);
	//if (c != -1) {
	//	keyboardSimulado(c);
	//}

	///////*******NUBES*********////////////
	if (terror == false) {
		angNubes += 0.01;
	}
		

	//////*********FUEGO******//////////////
	angFuego += 45.0;
	
	////////******ARBOLES******//////////////
	if (estado0Arboles && terror==false) {
		if (angArboles<10.0)
			angArboles += 6.0;
		else {
			estado0Arboles = false;
			estado1Arboles = true;
		}
	}

	if (estado1Arboles && terror==false) {
		if (angArboles>0.0)
			angArboles -= 6.0;
		else {
			estado1Arboles = false;
			estado0Arboles = true;
		}
	}

	//Movimiento recorrido virtual

	if(play)
	{		
		
		if(	i_curr_steps >= i_max_steps) //end of animation between frames?
		{			
			playIndex++;		
			if(playIndex>FrameIndex-2)	//end of total animation?
			{
				printf("termina anim\n");
				playIndex=0;
				play=false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
				//Interpolation
				interpolation();

			}
		}
		else
		{
			//Draw animation
			objCamera.mPos.x += KeyFrame[playIndex].incX;
			objCamera.mPos.y += KeyFrame[playIndex].incY;
			objCamera.mPos.z += KeyFrame[playIndex].incZ;

			objCamera.mView.x += KeyFrame[playIndex].viewX;
			objCamera.mView.y += KeyFrame[playIndex].viewY;
			objCamera.mView.z += KeyFrame[playIndex].viewZ;

			i_curr_steps++;
		}
		
	}

	/////FANTASMA 1//////////
	if (playfantasma)
	{
		if (estado1Fantasma1) //estado 1
		{
			fantasma1X ++;
			if(fantasma1X>155)
			{
				estado1Fantasma1 = false;
				estado2Fantasma1 = true;
			}
		}
	
		if (estado2Fantasma1) //estado 2
		{
			angFantasma = 90;
			fantasma1Z--;
			if(fantasma1Z<= -125)
			{
				estado2Fantasma1 = false;
				estado3Fantasma1 = true;
			}
		}

		if (estado3Fantasma1) //estado 3
		{
			angFantasma = 190;
			fantasma1X = fantasma1X - 2 * 0.62;
			fantasma1Z = fantasma1Z + 2 * 0.25;
			fantasma1Y = fantasma1Y + 0.62;
			if (fantasma1X < 30) 
			{
				estado3Fantasma1 = false;
				estado4Fantasma1 = true;
			}
		}

		if (estado4Fantasma1) //estado 4
		{
			fantasma1X = fantasma1X - 2 * 0.62;
			fantasma1Z = fantasma1Z + 2 * 0.25;
			if (fantasma1X < -40 )
			{
				estado4Fantasma1 = false;
				estado5Fantasma1 = true;
			}
		}

		if (estado5Fantasma1) //estado 5
		{
			fantasma1X = fantasma1X -  0.70;
			fantasma1Z = fantasma1Z + 2 * 0.223;
			fantasma1Y = fantasma1Y - 0.62;
			if (fantasma1Y <= -3.0)
			{
				estado5Fantasma1 = false;
				estado6Fantasma1 = true;
			}
		}

		if (estado6Fantasma1) //estado 6 
		{
			angFantasma = 0;
			fantasma1X++;
			if (fantasma1X > 0)
			{
				estado6Fantasma1 = false;
				estado1Fantasma1 = true;
			}
		}

	}

	////FANTASMA 2

	if (playfantasma)
	{
		if (estado1Fantasma2) //estado 1
		{
			angFantasma2 = 0;
			fantasma2Z ++;
			if(fantasma2Z>86)
			{
				estado1Fantasma2 = false;
				estado2Fantasma2 = true;
			}
		}

		if (estado2Fantasma2) //estado 2
		{
			angFantasma2 = 90;
			fantasma2X++;
			if(fantasma2X> 130)
			{
				estado2Fantasma2 = false;
				estado3Fantasma2 = true;
			}
		}

		if (estado3Fantasma2) //estado 3
		{
			angFantasma2 = 270;
			fantasma2X --;
			if (fantasma2X <= -130) 
			{
				estado3Fantasma2 = false;
				estado4Fantasma2 = true;
			}
		}

		if (estado4Fantasma2) //estado 4
		{
			angFantasma2 = 90;
			fantasma2X ++;
			if (fantasma2X >= 0 )
			{
				estado4Fantasma2 = false;
				estado5Fantasma2 = true;
			}
		}

		if (estado5Fantasma2) //estado 5
		{
			angFantasma2 = 180;
			fantasma2Z --;
			if (fantasma2Z <= 0)
			{
				estado5Fantasma2 = false;
				estado1Fantasma2 = true;
			}
		}

	}

//////FANTASMA 3
	if (playfantasma)
	{
		if (estado1Fantasma3) //estado 1
		{
			angFantasma3 = 270;
			fantasma3X--;
			if (fantasma3X<-130)
			{
				estado1Fantasma3 = false;
				estado2Fantasma3 = true;
			}
		}

		if (estado2Fantasma3) //estado 2
		{
			angFantasma3 = 0;
			fantasma3Z++;
			if (fantasma3Z> 80)
			{
				estado2Fantasma3 = false;
				estado3Fantasma3 = true;
			}
		}

		if (estado3Fantasma3) //estado 3
		{
			angFantasma3 = 90;
			fantasma3X++;
			if (fantasma3X >= 0)
			{
				estado3Fantasma3 = false;
				estado4Fantasma3 = true;
			}
		}

		if (estado4Fantasma3) //estado 4
		{
			angFantasma3 = 180;
			fantasma3Z--;
			if (fantasma3Z <= 0)
			{
				estado4Fantasma3 = false;
				estado1Fantasma3 = true;
			}
		}

	}

	//////FANTASMA 4
	if (playfantasma)
	{
		if (estado1Fantasma4) //estado 1
		{
			angFantasma4 = 0;
			fantasma4Z++;
			if (fantasma4Z>275)
			{
				estado1Fantasma4 = false;
				estado2Fantasma4 = true;
			}
		}

		if (estado2Fantasma4) //estado 2
		{
			angFantasma4 = 90;
			fantasma4X++;
			if (fantasma4X> 240)
			{
				estado2Fantasma4 = false;
				estado3Fantasma4 = true;
			}
		}

		if (estado3Fantasma4) //estado 3
		{
			angFantasma4 = 180;
			fantasma4Z--;
			if (fantasma4Z <= 10)
			{
				estado3Fantasma4 = false;
				estado4Fantasma4 = true;
			}
		}

		if (estado4Fantasma4) //estado 4
		{
			angFantasma4 = 270;
			fantasma4X--;
			if (fantasma4X <= 0)
			{
				estado4Fantasma4 = false;
				estado1Fantasma4 = true;
			}
		}

	}

	glutPostRedisplay();
}

void reshape ( int width , int height )   // Creamos funcion Reshape
{
  if (height==0)										// Prevenir division entre cero
	{
		height=1;
	}

	glViewport(0,0,width,height);	

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista
	
	glFrustum (-0.1, 0.1,-0.1, 0.1, 0.1, 6200.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{
	printf("%.2f \n", objCamera.mPos.x);
	printf("%.2f \n", objCamera.mPos.y);
	printf("%.2f \n", objCamera.mPos.z);
	switch ( key ) {
		case 'w':   //Movimientos de camara
				objCamera.Move_Camera(CAMERASPEED + 0.2);
				fprintf(escribir, "w");
			break;
		case 'W':
				objCamera.Move_Camera(CAMERASPEED + 0.6);
			break;

		case 's':
		case 'S':
			objCamera.Move_Camera(-(CAMERASPEED+0.2));
			fprintf(escribir, "s");
			break;

		case 'a':
		case 'A':
			objCamera.Strafe_Camera(-(CAMERASPEED+0.4));
			fprintf(escribir, "a");
			break;

		case 'd':
		case 'D':
			objCamera.Strafe_Camera( CAMERASPEED+0.4 );
			fprintf(escribir, "d");
			break;

		case 'k':		//
		case 'K':
			if(FrameIndex<MAX_FRAMES)
			{
				saveFrame();
			}
			break;

		case 'l':						
		case 'L':
			if(play==false && (FrameIndex>1))
			{

				resetElements();
				//First Interpolation				
				interpolation();

				play=true;
				playIndex=0;
				i_curr_steps = 0;
			}
			else
			{
				play=false;
			}
			break;

		case 'z':						
		case 'Z':
			//Interaccion regalo
			fprintf(escribir, "z");
			if (objCamera.mPos.z > -7 && objCamera.mPos.z < -1 && objCamera.mPos.x>0 && objCamera.mPos.x<6)
			{
				texturas_casa_terror();
				terror = true;
				PlaySound(NULL, NULL, 0);
				//PlayMozart();
			}
			//Interaccion puerta
			if (objCamera.mPos.z >3 && objCamera.mPos.z < 14 && objCamera.mPos.x>10 && objCamera.mPos.x < 19) {
				if (puertaAbierta == true) {
					if (trasladoPuerta > 0.0)
						trasladoPuerta -= 1.0;
					else
						puertaAbierta = false;
				}
				else {
					if (trasladoPuerta < 4.0)
						trasladoPuerta += 1.0;
					else
						puertaAbierta = true;
				}
			}
			break;

		case 'x':						
		case 'X':
			fprintf(escribir, "x");
			playfantasma = !playfantasma;
			break;

		case 'c':						
		case 'C':
			fprintf(escribir, "c");
			break;

		case 'j':						
		case 'J':
			break;

		case 'b':						
			break;

		case 'B':						
			break;

		case 'p':						
			break;

		case 'P':						
			break;

		case 27:        // Cuando Esc es presionado...
			exit ( 0 );   // Salimos del programa
			break;        
		default:        // Cualquier otra
			break;
  }

  glutPostRedisplay();
}


void arrow_keys ( int a_keys, int x, int y )  // Funcion para manejo de teclas especiales (arrow keys)
{
  switch ( a_keys ) {
	case GLUT_KEY_PAGE_UP:
		objCamera.UpDown_Camera(CAMERASPEED*10);
		fprintf(escribir, "5");
		break;

	case GLUT_KEY_PAGE_DOWN:
		//if (objCamera.mPos.y>3)
			objCamera.UpDown_Camera(-CAMERASPEED*10);
			fprintf(escribir, "6");
		break;

    case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		g_lookupdown -= 1.0f;
		fprintf(escribir, "1");
		break;

    case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		g_lookupdown += 1.0f;
		fprintf(escribir, "2");
		break;

	case GLUT_KEY_LEFT:
		objCamera.Rotate_View(-CAMERASPEED);
		fprintf(escribir, "2");
		break;

	case GLUT_KEY_RIGHT:
		objCamera.Rotate_View( CAMERASPEED);
		fprintf(escribir, "3");
		break;

    default:
		break;
  }
  glutPostRedisplay();
}

void menuKeyFrame( int id)
{
	switch (id)
	{
		case 0:	//Save KeyFrame
			if(FrameIndex<MAX_FRAMES)
			{
				saveFrame();
			}
			break;

		case 1:	//Play animation
			if(play==false && FrameIndex >1)
			{

				resetElements();
				//First Interpolation
				interpolation();

				play=true;
				playIndex=0;
				i_curr_steps = 0;
			}
			else
			{
				play=false;
			}
			break;


	}
}


void menu( int id)
{
	
}



int main ( int argc, char** argv )   // Main Function
{
  //Archivo
  ap = fopen("recorrido.txt", "r+");
  escribir = fopen("escribir.txt", "w+");
  int submenu;
  glutInit            (&argc, argv); // Inicializamos OpenGL
  glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
  glutInitWindowSize  (500, 500);	// Tamaño de la Ventana
  glutInitWindowPosition (0, 0);	//Posicion de la Ventana
  glutCreateWindow    ("Proyecto Final"); // Nombre de la Ventana
 // glutFullScreen     ( );         // Full Screen
  InitGL ();						// Parametros iniciales de la aplicacion
  glutDisplayFunc     ( display );  //Indicamos a Glut función de dibujo
  glutReshapeFunc     ( reshape );	//Indicamos a Glut función en caso de cambio de tamano
  glutKeyboardFunc    ( keyboard );	//Indicamos a Glut función de manejo de teclado
  glutSpecialFunc     ( arrow_keys );	//Otras
  glutIdleFunc		  ( animacion );

  ////////Sonido////////
 PlayAire();

  submenu = glutCreateMenu	  ( menuKeyFrame );
  glutAddMenuEntry	  ("Guardar KeyFrame", 0);
  glutAddMenuEntry	  ("Reproducir Animacion", 1);
  glutCreateMenu	  ( menu );
  glutAddSubMenu	  ("Animacion Monito", submenu);
 
  glutAttachMenu	  (GLUT_RIGHT_BUTTON);

  glutMainLoop        ( );          // 

  return 0;
}