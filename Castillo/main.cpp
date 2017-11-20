//Semestre 2017 - 2
//************************************************************//
//************************************************************//
//************** Alumno (s): *********************************//
//*************	Desiderio González Ricardo Abraham		******//
//*************Gutiérrez Bénitez David Fernando			******//
//************************************************************//
//************************************************************//

#include "texture.h"
#include "figuras.h"
#include "Camera.h"
#include "Windows.h"
#include "cmodel/CModel.h"
#include "stdlib.h"
void monitoCT(GLuint textura);

///ARCHIVO/////
FILE *ap;
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
	float angBrazoDerEmpalado;
	float angBrazoIzqEmpalado;
	float angPiernaDerEmpalado;
	float angPiernaIzqEmpalado;

	float angBrazoDerEmpaladoInc;
	float angBrazoIzqEmpaladoInc;
	float angPiernaDerEmpaladoInc;
	float angPiernaIzqEmpaladoInc;

}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex=4;			//introducir datos
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
bool recorrido = false;
bool organo =true;


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
//GUILLOTINA
float despGuillotina, despCabezaGuillotinaZ, despCabezaGuillotinaY, guillotinaPausa;
//EMPALADO
float angBrazoDerEmpalado, angBrazoIzqEmpalado;
float angPiernaDerEmpalado, angPiernaIzqEmpalado;
//MOMIA
float angPiernaDerMomia, angPiernaIzqMomia, giroMomia;
float MomiaZ=-5.0, MomiaX;

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

//GUILLOTINA
bool estado1Guillotina = true;
bool estado2Guillotina = false;
bool estado3Guillotina = false;
bool estado4Guillotina = false;
bool estado5Guillotina = false;

/////MOMIA 
//pies
bool estado1Pmomia = true;
bool estado2Pmomia = false;
//desplazamiento
bool estado1Momia = true;
bool estado2Momia = false;
bool estado3Momia = false;
bool estado4Momia = false;
bool estado5Momia = false;
bool estado6Momia = false;


////temp
bool playfantasma = false;
bool playGuillotina = false;
bool playMomia = false;

////////////////////////TEXTURAS/////////////////////////
//Exterior
CTexture text1; //cielo1
CTexture textGrass;
CTexture textMar;

///CAMINO PIEDRA
CTexture textPiedra;

//Casa
CTexture textPuerta_Casa;
CTexture textWall;
CTexture textPisoCasa;
CTexture textTechoCasa;
//Interior casa
CTexture textSilla;
CTexture textComedor;
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
CTexture textPelo;
CTexture textpiel;
CTexture textCarnePodrida;
CTexture textVenda;

///CASTILLO
CTexture textBarrote;
CTexture entrada;
CTexture puerta;
CTexture pasto;
CTexture textPiso; 
CTexture textTecho;
CTexture textMarble;
CTexture entrada2;
CTexture sangre2;
CTexture vieja;
CTexture sangre;
CTexture metal;
CTexture tierra;


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
CFiguras fig5;
////EXTERIOR/////
CFiguras pasto_islas;
CFiguras mar;
CFiguras camino;
//Monito
CFiguras fig7;



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

	KeyFrame[FrameIndex].angBrazoDerEmpalado = angBrazoDerEmpalado;
	KeyFrame[FrameIndex].angBrazoIzqEmpalado = angBrazoIzqEmpalado;
	KeyFrame[FrameIndex].angPiernaDerEmpalado = angPiernaDerEmpalado;
	KeyFrame[FrameIndex].angPiernaIzqEmpalado = angPiernaIzqEmpalado;
	printf("frameindex %d\n",FrameIndex);			


	FrameIndex++;
}

void resetElements( void )
{

	angBrazoDerEmpalado = KeyFrame[0].angBrazoDerEmpalado;
	angBrazoIzqEmpalado = KeyFrame[0].angBrazoIzqEmpalado;
	angPiernaDerEmpalado = KeyFrame[0].angPiernaDerEmpalado;
	angPiernaIzqEmpalado = KeyFrame[0].angPiernaIzqEmpalado;


}

void interpolation ( void )
{
	KeyFrame[playIndex].angBrazoDerEmpaladoInc = (KeyFrame[playIndex + 1].angBrazoDerEmpalado - KeyFrame[playIndex].angBrazoDerEmpalado) / i_max_steps;
	KeyFrame[playIndex].angBrazoIzqEmpaladoInc = (KeyFrame[playIndex + 1].angBrazoIzqEmpalado - KeyFrame[playIndex].angBrazoIzqEmpalado) / i_max_steps;
	KeyFrame[playIndex].angPiernaDerEmpaladoInc= (KeyFrame[playIndex + 1].angPiernaDerEmpalado - KeyFrame[playIndex].angPiernaDerEmpalado) / i_max_steps;
	KeyFrame[playIndex].angPiernaIzqEmpaladoInc = (KeyFrame[playIndex + 1].angPiernaIzqEmpalado - KeyFrame[playIndex].angPiernaIzqEmpalado) / i_max_steps;

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

void dibujaContornoCasa() {
	//Paredes y piso de la casa
	glPushMatrix();
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1);
		glRotatef(-90, 0,1,0);
		if (terror==false)	
			paredescasa.skybox_casa(26, 30, 30, textWall.GLindex, textPisoCasa.GLindex, textPuerta_Casa.GLindex, textTechoCasa.GLindex, 1.0f, 8.0f, 3.0f, trasladoPuerta);
		else 
			paredescasa.skybox_casa(26, 30, 30, textWall.GLindex, textPisoCasa.GLindex, textPuerta_Casa.GLindex, textTechoCasa.GLindex, 1.0f, 1.0f, 1.0f, trasladoPuerta);
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
				tablaMesa.prisma (1.0, 1.0, 1.0, textComedor.GLindex);
			//patas
			glPopMatrix();
			glPushMatrix();
				glTranslatef(4, -2.5, 2);
				glScalef( .5, 4.5,.5);
				pata1Mesa.prisma (1.0, 1.0, 1.0, textComedor.GLindex);
				glTranslatef(0, 0, -8);
				pata2Mesa.prisma (1.0, 1.0, 1.0, textComedor.GLindex);
				glTranslatef(-16, 0, 0);
				pata3Mesa.prisma (1.0, 1.0, 1.0, textComedor.GLindex);
				glTranslatef(0, 0, 8);
				pata4Mesa.prisma (1.0, 1.0, 1.0, textComedor.GLindex);
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
		hojasNavidad.cono(30.0, 10.0, 50, textHojasNavidad.GLindex, 3.0);
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

	textComedor.LoadBMP("casa/madera_comedor_terror.bmp");
	textComedor.BuildGLTexture();
	textComedor.ReleaseImage();

	textPisoCasa.LoadBMP("casa/piso_terror.bmp");
	textPisoCasa.BuildGLTexture();
	textPisoCasa.ReleaseImage();

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
	PlaySound(TEXT("sonidos/terror.wav"), NULL, SND_ASYNC);
}

void PlayBach() {
	PlaySound(TEXT("sonidos/terror2.wav"), NULL, SND_ASYNC | SND_ASYNC);
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

	if (objCamera.mPos.x>54 && terror == true && organo == true) {
		organo = false;
		PlayBach();
	}

	switch (simkey) {
	case 'w':   //Movimientos de camara
		objCamera.Move_Camera(CAMERASPEED + 0.3);
		break;
	case 'q':
		objCamera.Move_Camera(CAMERASPEED + 0.6);
		break;

	case 's':
	case 'S':
		objCamera.Move_Camera(-(CAMERASPEED + 0.3));
		break;

	case 'a':
	case 'A':
		objCamera.Strafe_Camera(-(CAMERASPEED + 0.3));
		break;

	case 'd':
	case 'D':
		objCamera.Strafe_Camera(CAMERASPEED + 0.3);
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
			PlayMozart();
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

	case 'g':
	case 'G':
		playGuillotina = true;
		break;

	case 'm':
	case 'M':
		playMomia = true;
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
		objCamera.UpDown_Camera(CAMERASPEED*2 );
		break;

	case '6':
		objCamera.UpDown_Camera(-CAMERASPEED*2 );
		break;

	case 'e':        // Cuando Esc es presionado...
		exit(0);   // Salimos del programa
		break;
	default:        // Cualquier otra
		break;
	}

}

void prisma(GLuint textura1, GLuint textura2)  //Funcion creacion prisma
{

	GLfloat vertice[8][3] = {
		{ 0.5 ,-0.5, 0.5 },    //Coordenadas VÃ©rtice 0 V0
		{ -0.5 ,-0.5, 0.5 },    //Coordenadas VÃ©rtice 1 V1
		{ -0.5 ,-0.5, -0.5 },    //Coordenadas VÃ©rtice 2 V2
		{ 0.5 ,-0.5, -0.5 },    //Coordenadas VÃ©rtice 3 V3
		{ 0.5 ,0.5, 0.5 },    //Coordenadas VÃ©rtice 4 V4
		{ 0.5 ,0.5, -0.5 },    //Coordenadas VÃ©rtice 5 V5
		{ -0.5 ,0.5, -0.5 },    //Coordenadas VÃ©rtice 6 V6
		{ -0.5 ,0.5, 0.5 },    //Coordenadas VÃ©rtice 7 V7
	};


	glBindTexture(GL_TEXTURE_2D, textura1);   // choose the texture to use.
	glBegin(GL_POLYGON);	//top
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0, 0.0f); glVertex3fv(vertice[6]);
	glTexCoord2f(6.0, 0.0f); glVertex3fv(vertice[5]);
	glTexCoord2f(6.0, 6.0f); glVertex3fv(vertice[4]);
	glTexCoord2f(0.0f, 6.0f); glVertex3fv(vertice[7]);
	glEnd();

	glBegin(GL_POLYGON);	//Right
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[3]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[5]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[4]);
	glEnd();

	glBegin(GL_POLYGON);	//Back
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[6]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[5]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[3]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON);  //Left
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[6]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[7]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[1]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON);  //Bottom
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[0]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[1]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[2]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[3]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textura2);   // choose the texture to use.
	glBegin(GL_POLYGON);  //front
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertice[0]);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertice[1]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertice[7]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertice[4]);
	glEnd();
}

void momia(GLuint textura) //se modifico
{
	//glNewList(1, GL_COMPILE);
	glPushMatrix();//Pecho
	glScalef(0.5, 0.5, 0.5);
	fig7.prisma(2.0, 2.0, 1, textura);

	glPushMatrix();//Cuello
	glTranslatef(0, 1.0, 0.0);
	fig7.cilindro(0.25, 0.25, 15, textura);
	glPushMatrix();//Cabeza
	glTranslatef(0, 1.0, 0);
	fig7.esfera(0.75, 15, 15, textura);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix(); //Brazo derecho--> //se modifico
	glTranslatef(1.25, 0.65, 0);
	fig7.esfera(0.5, 12, 12, textura);
	glPushMatrix();
	glTranslatef(0.25, 0, 0);
	glRotatef(-90 + 0, 0, 1, 0);  //agregado
	glTranslatef(0.75, 0, 0);
	fig7.prisma(0.7, 1.5, 0.7, textura);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix(); //Brazo izquierdo <-- //se modifico
	glTranslatef(-1.25, 0.65, 0);
	fig7.esfera(0.5, 12, 12, textura);
	glPushMatrix();
	glTranslatef(-0.25, 0, 0);
	glRotatef(90, 0, 1, 0);
	//glRotatef(25, 0, 0, 1);
	//glRotatef(25 + 0, 0, 1, 0);  //agregado
	glTranslatef(-0.75, 0, 0);
	fig7.prisma(0.7, 1.5, 0.7, textura);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();//Cintura
	glTranslatef(0, -1.5, 0);
	fig7.prisma(1, 2, 1, textura);

	glPushMatrix(); //Pie Derecho -->
	glTranslatef(0.75, -0.5, 0);
	glRotatef(-15+angPiernaDerMomia, 1, 0, 0);
	glTranslatef(0, -0.5, 0);
	fig7.prisma(1.0, 0.5, 1, textura);

	glPushMatrix();
	glTranslatef(0, -0.5, 0);
	glRotatef(15 + 0, 1, 0, 0);
	glTranslatef(0, -0.75, 0);
	fig7.prisma(1.5, 0.5, 1, textura);

	glPushMatrix();
	glTranslatef(0, -0.75, 0.3);
	fig7.prisma(0.2, 1.2, 1.5, textura);
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();


	glPushMatrix(); //Pie Izquierdo -->
	glTranslatef(-0.75, -0.5, 0);
	glRotatef(-5+angPiernaIzqMomia, 1, 0, 0);
	glTranslatef(0, -0.5, 0);
	fig7.prisma(1.0, 0.5, 1, textura);

	glPushMatrix();
	glTranslatef(0, -0.5, 0);
	glRotatef(15 + 0, 1, 0, 0);
	glTranslatef(0, -0.75, 0);
	fig7.prisma(1.5, 0.5, 1, textura);

	glPushMatrix();
	glTranslatef(0, -0.75, 0.3);
	fig7.prisma(0.2, 1.2, 1.5, textura);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();


	glPopMatrix();


	glColor3f(1, 1, 1);
	glPopMatrix();

}

void monitoGuillotina(GLuint textura) //se modifico
{
	//glNewList(1, GL_COMPILE);
	glPushMatrix();//Pecho
	glScalef(0.5, 0.5, 0.5);
	fig7.prisma(2.0, 2.0, 1, textura);

	glPushMatrix();//Cuello
	glTranslatef(0, 1.0, 0.0);
	fig7.cilindro(0.25, 0.25, 15, textura);
	glPushMatrix();//Cabeza
	glTranslatef(0, 1.0+despCabezaGuillotinaY, 0+despCabezaGuillotinaZ);
	fig7.esfera(0.75, 15, 15, textura);
	glPopMatrix();
	glPopMatrix();

	

	glPushMatrix();//Cintura
	glTranslatef(0, -1.5, 0);
	fig7.prisma(1, 2, 1, textura);

	glPushMatrix(); //Pie Derecho -->
	glTranslatef(0.75, -0.5, 0);
	glRotatef(-15, 1, 0, 0);
	glTranslatef(0, -0.5, 0);
	fig7.prisma(1.0, 0.5, 1, textura);

	glPushMatrix();
	glTranslatef(0, -0.5, 0);
	glRotatef(15 + 0, 1, 0, 0);
	glTranslatef(0, -0.75, 0);
	fig7.prisma(1.5, 0.5, 1, textura);

	glPushMatrix();
	glTranslatef(0, -0.75, 0.3);
	fig7.prisma(0.2, 1.2, 1.5, textura);
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();


	glPushMatrix(); //Pie Izquierdo -->
	glTranslatef(-0.75, -0.5, 0);
	glRotatef(-5, 1, 0, 0);
	glTranslatef(0, -0.5, 0);
	fig7.prisma(1.0, 0.5, 1, textura);

	glPushMatrix();
	glTranslatef(0, -0.5, 0);
	glRotatef(15 + 0, 1, 0, 0);
	glTranslatef(0, -0.75, 0);
	fig7.prisma(1.5, 0.5, 1, textura);

	glPushMatrix();
	glTranslatef(0, -0.75, 0.3);
	fig7.prisma(0.2, 1.2, 1.5, textura);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();


	glPopMatrix();


	glColor3f(1, 1, 1);
	glPopMatrix();

}

void monitoEmpalado(GLuint textura) //se modifico
{
	//glNewList(1, GL_COMPILE);
	glPushMatrix();//Pecho
	glScalef(0.5, 0.5, 0.5);
	fig7.prisma(2.0, 2.0, 1, textura);

	glPushMatrix();//Cuello
	glTranslatef(0, 1.0, 0.0);
	fig7.cilindro(0.25, 0.25, 15, textura);
	glPushMatrix();//Cabeza
	glTranslatef(0, 1.0, 0);
	fig7.esfera(0.75, 15, 15, textura);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix(); //Brazo derecho--> //se modifico
	glTranslatef(1.25, 0.65, 0);
	fig7.esfera(0.5, 12, 12, textura);
	glPushMatrix();
	glTranslatef(0.25, 0, 0);
	glRotatef(-45+angBrazoDerEmpalado + 0, 0, 1, 0);  //agregado
	glTranslatef(0.75, 0, 0);
	fig7.prisma(0.7, 1.5, 0.7, textura);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix(); //Brazo izquierdo <-- //se modifico
	glTranslatef(-1.25, 0.65, 0);
	fig7.esfera(0.5, 12, 12, textura);
	glPushMatrix();
	glTranslatef(-0.25, 0, 0);
	glRotatef(45, 0, 1, 0);
	//glRotatef(25, 0, 0, 1);
	glRotatef(25 + angBrazoIzqEmpalado, 0, 0, 1);  //agregado
	glTranslatef(-0.75, 0, 0);
	fig7.prisma(0.7, 1.5, 0.7, textura);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();//Cintura
	glTranslatef(0, -1.5, 0);
	fig7.prisma(1, 2, 1, textura);

	glPushMatrix(); //Pie Derecho -->
	glTranslatef(0.75, -0.5, 0);
	glRotatef(-15, 1, 0, 0);
	glTranslatef(0, -0.5, 0);
	fig7.prisma(1.0, 0.5, 1, textura);

	glPushMatrix();
	glTranslatef(0, -0.5, 0);
	glRotatef(15 + angPiernaDerEmpalado, 1, 0, 0);
	glTranslatef(0, -0.75, 0);
	fig7.prisma(1.5, 0.5, 1, textura);

	glPushMatrix();
	glTranslatef(0, -0.75, 0.3);
	fig7.prisma(0.2, 1.2, 1.5, textura);
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();


	glPushMatrix(); //Pie Izquierdo -->
	glTranslatef(-0.75, -0.5, 0);
	glRotatef(-5, 1, 0, 0);
	glTranslatef(0, -0.5, 0);
	fig7.prisma(1.0, 0.5, 1, textura);

	glPushMatrix();
	glTranslatef(0, -0.5, 0);
	glRotatef(15 + angPiernaIzqEmpalado, 1, 0, 0);
	glTranslatef(0, -0.75, 0);
	fig7.prisma(1.5, 0.5, 1, textura);

	glPushMatrix();
	glTranslatef(0, -0.75, 0.3);
	fig7.prisma(0.2, 1.2, 1.5, textura);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();


	glPopMatrix();


	glColor3f(1, 1, 1);
	glPopMatrix();

}

void castillo()
{
	glDisable(GL_LIGHTING);
	glPushMatrix();
		//castillo			
		glPushMatrix();
			glTranslatef(0, 12.5, 0);
			glPushMatrix();
				glEnable(GL_ALPHA_TEST);
				glAlphaFunc(GL_GREATER, 0.1);
				glScalef(60.0, 35.0, 60.0);
				prisma(textBarrote.GLindex, entrada.GLindex);
				glDisable(GL_ALPHA_TEST);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0.0, 12.5, 0.0);
				glEnable(GL_ALPHA_TEST);
				glAlphaFunc(GL_GREATER, 0.1);
				fig1.skybox(59.0, 34.0, 59.0, textBarrote.GLindex, entrada.GLindex);
				glDisable(GL_ALPHA_TEST);
			glPopMatrix();

			////puertas
			glPushMatrix();
				glTranslatef(-5.3, 1.0, 29.75);
				glScalef(11.5, 12.0, 1.0);
				prisma(puerta.GLindex, puerta.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(6.0, 1.0, 29.75);
				glScalef(11.5, 12.0, 1.0);
				prisma(puerta.GLindex, puerta.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-4.5, 34.0, 22.5);
				glScalef(8.5, 7.0, 1.0);
				prisma(puerta.GLindex, puerta.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(4.25, 34.0, 22.5);
				glScalef(9.0, 7.0, 1.0);
				prisma(puerta.GLindex, puerta.GLindex);
			glPopMatrix();

			//pasto
			glPushMatrix();
				glTranslatef(0.0, -6.0, 30.0);
				//glScalef(290.0, 0.01, 250.0);
				cubo.prisma_tablero(0.01, 290.0, 250.0, textGrass.GLindex, 40.0);
			glPopMatrix();

			//techo
			glPushMatrix();
				glTranslatef(0.0, 29.5, 0.0);
				glScalef(60.0, 0.5, 60.0);
				prisma(textBarrote.GLindex, textBarrote.GLindex);
			glPopMatrix();

			//piso
			glPushMatrix();
				glTranslatef(0.0, -4.5, 0.0);
				glScalef(60.0, 0.5, 60.0);
				prisma(textBarrote.GLindex, textBarrote.GLindex);
			glPopMatrix();

			//Escalera
			glPushMatrix();
				glTranslatef(20.0, -3.5, 77.5);
				glScalef(10.0, 4.0, 5.0);
				prisma(textBarrote.GLindex, textBarrote.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(20.0, -0.5, 72.5);
				glScalef(10.0, 4.0, 5.0);
				prisma(textBarrote.GLindex, textBarrote.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(20.0, 2.5, 67.5);
				glScalef(10.0, 4.0, 5.0);
				prisma(textBarrote.GLindex, textBarrote.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(20.0, 5.5, 62.5);
				glScalef(10.0, 4.0, 5.0);
				prisma(textBarrote.GLindex, textBarrote.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(20.0, 8.5, 57.5);
				glScalef(10.0, 4.0, 5.0);
				prisma(textBarrote.GLindex, textBarrote.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(20.0, 11.5, 52.5);
				glScalef(10.0, 4.0, 5.0);
				prisma(textBarrote.GLindex, textBarrote.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(20.0, 14.5, 47.5);
				glScalef(10.0, 4.0, 5.0);
				prisma(textBarrote.GLindex, textBarrote.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(20.0, 17.5, 42.5);
				glScalef(10.0, 4.0, 5.0);
				prisma(textBarrote.GLindex, textBarrote.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(20.0, 20.5, 37.5);
				glScalef(10.0, 4.0, 5.0);
				prisma(textBarrote.GLindex, textBarrote.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(20.0, 23.5, 32.5);
				glScalef(10.0, 4.0, 5.0);
				prisma(textBarrote.GLindex, textBarrote.GLindex);
			glPopMatrix();

			//columnas
			glPushMatrix();
				glTranslatef(-40, -5, 30);
				fig1.cilindro(10, 50, 40, textBarrote.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(40, -5, 30);
				fig1.cilindro(10, 50, 40, textBarrote.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-40, -5, -30);
				fig1.cilindro(10, 80, 40, textBarrote.GLindex);
				glTranslatef(0.0, 80.0, 0.0);
				fig1.cono(20, 15, 40, textBarrote.GLindex,1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(40, -5, -30);
				fig1.cilindro(10, 80, 100, textBarrote.GLindex);
				glTranslatef(0.0, 80.0, 0.0);
				fig1.cono(20, 15, 40, textBarrote.GLindex, 1.0);
			glPopMatrix();

			//puntas
			glPushMatrix();
				glTranslatef(0, 31.5, 29.5);
				glScalef(5.0, 3.0, 1.0);
				prisma(textBarrote.GLindex, textBarrote.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(7, 31.5, 29.5);
				glScalef(5.0, 3.0, 1.0);
				prisma(textBarrote.GLindex, textBarrote.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-7, 31.5, 29.5);
				glScalef(5.0, 3.0, 1.0);
				prisma(textBarrote.GLindex, textBarrote.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-14, 31.5, 29.5);
				glScalef(5.0, 3.0, 1.0);
				prisma(textBarrote.GLindex, textBarrote.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(14, 31.5, 29.5);
				glScalef(5.0, 3.0, 1.0);
				prisma(textBarrote.GLindex, textBarrote.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-21, 31.5, 29.5);
				glScalef(5.0, 3.0, 1.0);
				prisma(textBarrote.GLindex, textBarrote.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-28, 31.5, 29.5);
				glScalef(5.0, 3.0, 1.0);
				prisma(textBarrote.GLindex, textBarrote.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(28, 31.5, 29.5);
				glScalef(5.0, 3.0, 1.0);
				prisma(textBarrote.GLindex, textBarrote.GLindex);
			glPopMatrix();
			//Monito guillotina
			glPushMatrix();
				glTranslatef(-13.0, -0.7, 8.7);
				glRotatef(5, 1.0, 0.0, 0.0);
				glRotatef(-90, 1.0, 0.0, 0.0);
				glScalef(2.0, 2.0, 1.15);
				monitoGuillotina(textpiel.GLindex);
			glPopMatrix();

			//Monito cama
			glPushMatrix();
				glTranslatef(13.0, 0.7, 9.5);
				glRotatef(270, 1, 0, 0);
				glScalef(2.0, 2.0, 1.15);
				monitoCT(textCarnePodrida.GLindex);
			glPopMatrix();
			
			//Empalado
			glPushMatrix();
				glTranslatef(14.0, 8.0, -14.0);
				glRotatef(-30, 1.0, 0.0, 0.0);
				glScalef(2.0, 2.0, 2.0);
				monitoEmpalado(textPelo.GLindex);
			glPopMatrix();
			
			
			//machete
			glPushMatrix();
				glTranslatef(0.0, 0.25, 0.0);
				glRotatef(45.0, 0.0, 1.0, 0.0);
				glRotatef(180.0, 1.0, 0.0, 0.0);
				glRotatef(180.0, 0.0, 1.0, 0.0);
				glScalef(1.0, 0.1, 1.0);
				prisma(metal.GLindex, metal.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-0.4, 0.25, 1.0);
				glRotatef(45.0, 0.0, 1.0, 0.0);
				glRotatef(180.0, 1.0, 0.0, 0.0);
				glScalef(1.0, 0.1, 0.1);
				prisma(textMarble.GLindex, textMarble.GLindex);
			glPopMatrix();
		
			////instrumento1
			glPushMatrix();

				glTranslatef(-16.0, -1.0, -16.0);

				glPushMatrix();
					glTranslatef(0.0, 4.0, 0.0);
					glRotatef(90, 1.0, 0.0, 0.0);
					glRotatef(90, 1.0, 0.0, 0.0);
					glScalef(0.6, 8.0, 0.6);
					prisma(textMarble.GLindex, textMarble.GLindex);
				glPopMatrix();

				glPushMatrix();
				glTranslatef(0.0, 4.0, 0.0);
				glRotatef(90, 1.0, 0.0, 0.0);
				fig1.torus(5.0, 4.0, 20, 20);
				glPopMatrix();

				glPushMatrix(); //rueda

					glPushMatrix();
						glTranslatef(0.0, 5.0, 0.0);
						glRotatef(90, 0.0, 0.0, 1.0);
						glScalef(0.6, 8.0, 0.6);
						prisma(textMarble.GLindex, textMarble.GLindex);
					glPopMatrix();

					glPushMatrix();
						glTranslatef(0.0, 5.0, 0.0);
						glRotatef(45, 0.0, 0.0, 1.0);
						glScalef(0.6, 8.0, 0.6);
						prisma(textMarble.GLindex, textMarble.GLindex);
					glPopMatrix();

					glPushMatrix();
						glTranslatef(0.0, 5.0, 0.0);
						glRotatef(-45, 0.0, 0.0, 1.0);
						glScalef(0.6, 8.0, 0.6);
						prisma(textMarble.GLindex, textMarble.GLindex);
					glPopMatrix();

				glPopMatrix();
			
				glPushMatrix();
					glTranslatef(0.0, 1.0, 0.5);
					glScalef(1.0, 8.0, 0.5);
					prisma(textMarble.GLindex, textMarble.GLindex);
				glPopMatrix();
		
				glPushMatrix();
					glTranslatef(0.0, 1.0, -0.5);
					glScalef(1.0, 8.0, 0.5);
					prisma(textMarble.GLindex, textMarble.GLindex);
				glPopMatrix();

			glPopMatrix();

			//instrumento2
			glPushMatrix();
				glTranslatef(14.0, 0.0, -14.0);
				glScalef(1.0, 8.0, 1.0);
				prisma(textMarble.GLindex, textMarble.GLindex);
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(14.0, 4.0, -14.0);
				fig1.cono(5.0, 1.0, 10.0, 10.0, 1.0);
			glPopMatrix();

			//guillotina
			glPushMatrix();
				glTranslatef(-13.0, -2.0, 12.0);
				glRotatef(180, 1.0, 0.0, 0.0);
				glScalef(5.0, 1.0, 8.0);
				prisma(textMarble.GLindex, textMarble.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-13.0, -2.0, 8.0);
				glScalef(5.0, 2.0, 0.5);
				prisma(textMarble.GLindex, textMarble.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-13.0, -3.0, 16.0);
				glScalef(5.0, 3.0, 0.5);
				prisma(textMarble.GLindex, textMarble.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-11.0, 2.0, 8.0);
				glScalef(1.0, 14.0, 1.0);
				prisma(textMarble.GLindex, textMarble.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-15.0, 2.0, 8.0);
				glScalef(1.0, 14.0, 1.0);
				prisma(textMarble.GLindex, textMarble.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-13.0, 8.0 + despGuillotina, 7.5);
				glScalef(5.0, 2.0, 0.1);
				prisma(metal.GLindex, metal.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-13.0, -4.25, 7.0);
				fig1.cilindro(1.5, 0.1, 100, textMarble.GLindex);
				glTranslatef(0.0, 0.2, 0.0);
				glScalef(1.0, 5.0, 1.0);
				fig1.torus(1.5, 1.3, 10.0, 10.0);
			glPopMatrix();

			////cama de tortura
			glPushMatrix();
				glTranslatef(13.0, 0.0, 10.0);
				glRotatef(180, 1.0, 0.0, 0.0);
				glScalef(6.0, 1.0, 12.0);
				prisma(textMarble.GLindex, textMarble.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(10.5, -3.0, 4.5);
				glScalef(1.0, 5.0, 1.0);
				prisma(textMarble.GLindex, textMarble.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(15.5, -3.0, 4.5);
				glScalef(1.0, 5.0, 1.0);
				prisma(textMarble.GLindex, textMarble.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(10.5, -3.0, 15.5);
				glScalef(1.0, 5.0, 1.0);
				prisma(textMarble.GLindex, textMarble.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(15.5, -3.0, 15.5);
				glScalef(1.0, 5.0, 1.0);
				prisma(textMarble.GLindex, textMarble.GLindex);
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(16.5, 0.0, 16.0);
				glRotatef(90.0, 0.0, 0.0, 1.0);
				fig1.cilindro(1.0, 7.0, 40.0, textMarble.GLindex);
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(16.5, 0.0, 4.0);
				glRotatef(90.0, 0.0, 0.0, 1.0);
				fig1.cilindro(1.0, 7.0, 40.0, textMarble.GLindex);
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(9.5, 0.0, 16.0);
				glRotatef(45.0, 1.0, 0.0, 0.0);
				glScalef(0.3, 5.0, 0.3);
				prisma(textMarble.GLindex, textMarble.GLindex);
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(9.5, 0.0, 4.0);
				glRotatef(135.0, 1.0, 0.0, 0.0);
				glScalef(0.3, 5.0, 0.3);
				prisma(textMarble.GLindex, textMarble.GLindex);
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(9.5, 0.0, 16.0);
				glRotatef(135.0, 1.0, 0.0, 0.0);
				glScalef(0.3, 5.0, 0.3);
				prisma(textMarble.GLindex, textMarble.GLindex);
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(9.5, 0.0, 4.0);
				glRotatef(45.0, 1.0, 0.0, 0.0);
				glScalef(0.3, 5.0, 0.3);
				prisma(textMarble.GLindex, textMarble.GLindex);
			glPopMatrix();
			
			////sangre
			glPushMatrix();
				glTranslatef(16.0, -4.3, -13.0);
				glRotatef(180, 1.0, 0.0, 0.0);
				glEnable(GL_ALPHA_TEST);
				glAlphaFunc(GL_GREATER, 0.1);
				glScalef(7.0, 0.2, 7.0);
				prisma(sangre.GLindex, sangre.GLindex);
				glDisable(GL_ALPHA_TEST);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-16.0, -4.3, -16.0);
				glRotatef(180, 1.0, 0.0, 0.0);
				glEnable(GL_ALPHA_TEST);
				glAlphaFunc(GL_GREATER, 0.1);
				glScalef(10.0, 0.2, 10.0);
				prisma(sangre.GLindex, sangre.GLindex);
				glDisable(GL_ALPHA_TEST);
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(0.0, 6.0, -29.5);
				glRotatef(-90, 1.0, 0.0, 0.0);
				glRotatef(180, 0.0, 1.0, 0.0);
				glEnable(GL_ALPHA_TEST);
				glAlphaFunc(GL_GREATER, 0.1);
				glScalef(30.0, 0.2, 30.0);
				prisma(sangre2.GLindex, sangre2.GLindex);
				glDisable(GL_ALPHA_TEST);
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(0.0, 0.16, 0.0);
				glRotatef(180, 1.0, 0.0, 0.0);
				glEnable(GL_ALPHA_TEST);
				glAlphaFunc(GL_GREATER, 0.1);
				glScalef(4.0, 0.2, 4.0);
				prisma(sangre.GLindex, sangre.GLindex);
				glDisable(GL_ALPHA_TEST);
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(-13.0, -4.2, 7.0);
				glRotatef(180, 1.0, 0.0, 0.0);
				glEnable(GL_ALPHA_TEST);
				glAlphaFunc(GL_GREATER, 0.1);
				glScalef(4.0, 0.2, 4.0);
				prisma(sangre.GLindex, sangre.GLindex);
				glDisable(GL_ALPHA_TEST);
			glPopMatrix();

			//piso 2
			glPushMatrix();
				glTranslatef(0.0, 40.3, 0.0);
				glEnable(GL_ALPHA_TEST);
				glAlphaFunc(GL_GREATER, 0.1);
				glScalef(45.0, 20.0, 45.0);
				prisma(textBarrote.GLindex, entrada.GLindex);
				glEnable(GL_ALPHA_TEST);
			glPopMatrix();

			//muralla
			glPushMatrix();
				glTranslatef(-60.0, 15.0, 80.0);
				glScalef(60.0, 40.0, 2.0);
				prisma(textBarrote.GLindex, textBarrote.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(60.0, 15.0, 80.0);
				glScalef(60.0, 40.0, 2.0);
				prisma(textBarrote.GLindex, textBarrote.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0.0, 15.0, -75.0);
				glScalef(182.0, 40.0, 2.0);
				prisma(textBarrote.GLindex, textBarrote.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(90.0, 15.0, 0.0);
				glScalef(2.0, 40.0, 150.0);
				prisma(textBarrote.GLindex, textBarrote.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-90.0, 15.0, 0.0);
				glScalef(2.0, 40.0, 150.0);
				prisma(textBarrote.GLindex, textBarrote.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-95, -5, 80);
				fig1.cilindro(10, 70, 200, textBarrote.GLindex);
				fig1.cono(20, 50, 40, textBarrote.GLindex, 1.0);
				glTranslatef(0.0, 70.0, 0.0);
				fig1.cono(20, 15, 40, textBarrote.GLindex, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(95, -5, 80);
				fig1.cilindro(10, 70, 200, textBarrote.GLindex);
				fig1.cono(20, 50, 40, textBarrote.GLindex, 1.0);
				glTranslatef(0.0, 70.0, 0.0);
				fig1.cono(20, 15, 40, textBarrote.GLindex, 1.0);
			glPopMatrix();

		glPopMatrix();


	glPopMatrix();//pop de arquitectura del castillo

	///Segundo piso
	glPushMatrix();
		mesa(1.0, 1.0, 1.0, 0.0, 12.5, 0.0);
		glRotatef(30, 0.0, 1.0, 0.0);
		silla(0.6, 0.5, 0.6, 0.0, 23.0, -5.0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0, 12.5, 0);

		glPushMatrix();
			glPushMatrix();
				glRotatef(180, 0, 1, 0);
				dibujaCama(0.5, 0.5, 0.5, 15.0, 63.0, -35.0);
			glPopMatrix();

			dibujaCama(0.5, 0.5, 0.5, -10.0, 63.0, -43);
			dibujaCama(0.5, 0.5, 0.5, 15.0, 63.0, -43);

			///Momia
			glPushMatrix();
				glTranslatef(0+MomiaX, 37.5, 0+MomiaZ);
				glScalef(2.0, 3.0, 2.0);
				glRotatef(giroMomia, 0, 1, 0);
				momia(textVenda.GLindex);
				if (playMomia == true) {
					glTranslatef(0, 0, 0);
					glScalef(0.1, 0.1, 0.1);
					glRotatef(angFuego, 0, 1, 0);
					planos_cruzados(textFuego.GLindex);
				}
			glPopMatrix();
			
			if (playMomia == true) {
				glPushMatrix();//fuego

					glPushMatrix();//1
						glTranslatef(0, 29.5, 0);
						glRotatef(angFuego, 0, 1, 0);
						glScalef(0.4, 0.4, 0.4);
						planos_cruzados(textFuego.GLindex);
					glPopMatrix();

					glPushMatrix();//2
						glTranslatef(10, 33.0, -16);
						glRotatef(angFuego, 0, 1, 0);
						glScalef(0.4, 0.4, 0.4);
						planos_cruzados(textFuego.GLindex);
					glPopMatrix();

					glPushMatrix();//3
						glTranslatef(-10, 29.5, -10);
						glRotatef(angFuego, 0, 1, 0);
						glScalef(0.4, 0.4, 0.4);
						planos_cruzados(textFuego.GLindex);
					glPopMatrix();

					glPushMatrix();//4
						glTranslatef(-12, 33.0, 14);
						glRotatef(angFuego, 0, 1, 0);
						glScalef(0.4, 0.4, 0.4);
						planos_cruzados(textFuego.GLindex);
					glPopMatrix();

					glPushMatrix();//5
						glTranslatef(10, 29.5, 10);
						glRotatef(angFuego, 0, 1, 0);
						glScalef(0.4, 0.4, 0.4);
						planos_cruzados(textFuego.GLindex);
					glPopMatrix();
				
				glPopMatrix();
			}

		glPopMatrix();
	glPopMatrix();//De muebles del segundo piso

	glEnable(GL_LIGHTING);
}

void castillo_ruinas()
{
	glDisable(GL_LIGHTING);

	glPushMatrix();
		//castillo
		glPushMatrix();

			glTranslatef(0, 12.5, 0);
			glPushMatrix();
				glEnable(GL_ALPHA_TEST);
				glAlphaFunc(GL_GREATER, 0.1);
				glScalef(60.0, 35.0, 60.0);
				prisma(vieja.GLindex, entrada2.GLindex);
				glDisable(GL_ALPHA_TEST);
			glPopMatrix();
	
			glPushMatrix();
				glTranslatef(0.0, 12.5, 0.0);
				glEnable(GL_ALPHA_TEST);
				glAlphaFunc(GL_GREATER, 0.1);
				fig1.skybox(59.0, 34.0, 59.0, vieja.GLindex, entrada2.GLindex);
				glDisable(GL_ALPHA_TEST);
			glPopMatrix();
		
			//tierra
			glPushMatrix();
				glTranslatef(0.0, -6.0, 30.0);
				glScalef(280.0, 0.5, 230.0);
				prisma(tierra.GLindex, tierra.GLindex);
			glPopMatrix();
		
			//techo
			glPushMatrix();
				glTranslatef(0.0, 29.5, 0.0);
				glScalef(60.0, 0.5, 60.0);
				prisma(vieja.GLindex, vieja.GLindex);
			glPopMatrix();
		
			//piso
			glPushMatrix();
				glTranslatef(0.0, -4.5, 0.0);
				glScalef(60.0, 0.5, 60.0);
				prisma(vieja.GLindex, vieja.GLindex);
			glPopMatrix();
		
			//Escalera
			glPushMatrix();
				glTranslatef(20.0, -3.5, 77.5);
				glScalef(10.0, 4.0, 5.0);
				prisma(vieja.GLindex, vieja.GLindex);
			glPopMatrix();
		
			glPushMatrix();
				glTranslatef(20.0, -0.5, 72.5);
				glScalef(10.0, 4.0, 5.0);
				prisma(vieja.GLindex, vieja.GLindex);
			glPopMatrix();
		
			glPushMatrix();
				glTranslatef(20.0, 8.5, 57.5);
				glScalef(10.0, 4.0, 5.0);
				prisma(vieja.GLindex, vieja.GLindex);
			glPopMatrix();
		
			glPushMatrix();
				glTranslatef(20.0, 11.5, 52.5);
				glScalef(10.0, 4.0, 5.0);
				prisma(vieja.GLindex, vieja.GLindex);
			glPopMatrix();
		
			glPushMatrix();
				glTranslatef(20.0, 14.5, 47.5);
				glScalef(10.0, 4.0, 5.0);
				prisma(vieja.GLindex, vieja.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(20.0, 17.5, 42.5);
				glScalef(10.0, 4.0, 5.0);
				prisma(vieja.GLindex, vieja.GLindex);
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(20.0, 20.5, 37.5);
				glScalef(10.0, 4.0, 5.0);
				prisma(vieja.GLindex, vieja.GLindex);
			glPopMatrix();
		
			glPushMatrix();
				glTranslatef(20.0, 23.5, 32.5);
				glScalef(10.0, 4.0, 5.0);
				prisma(vieja.GLindex, vieja.GLindex);
			glPopMatrix();
		
			//columnas
			glPushMatrix();
				glTranslatef(-40, -5, 30);
				fig1.cilindro(10, 50, 40, vieja.GLindex);
			glPopMatrix();
		
			glPushMatrix();
				glTranslatef(40, -5, 30);
				fig1.cilindro(10, 50, 40, vieja.GLindex);
			glPopMatrix();
		
			glPushMatrix();
				glTranslatef(-40, -5, -30);
				fig1.cilindro(10, 80, 100, vieja.GLindex);
				glTranslatef(0.0, 80.0, 0.0);
				fig1.cono(20, 15, 40, textBarrote.GLindex, 1.0);
			glPopMatrix();
		
			//puntas
			glPushMatrix();
				glTranslatef(0, 31.5, 29.5);
				glScalef(5.0, 3.0, 1.0);
				prisma(vieja.GLindex, vieja.GLindex);
			glPopMatrix();
		
			glPushMatrix();
				glTranslatef(-14, 31.5, 29.5);
				glScalef(5.0, 3.0, 1.0);
				prisma(vieja.GLindex, vieja.GLindex);
			glPopMatrix();
		
			glPushMatrix();
				glTranslatef(14, 31.5, 29.5);
				glScalef(5.0, 3.0, 1.0);
				prisma(vieja.GLindex, vieja.GLindex);
			glPopMatrix();
		
			glPushMatrix();
				glTranslatef(-21, 31.5, 29.5);
				glScalef(5.0, 3.0, 1.0);
				prisma(vieja.GLindex, vieja.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-28, 31.5, 29.5);
				glScalef(5.0, 3.0, 1.0);
				prisma(vieja.GLindex, vieja.GLindex);
			glPopMatrix();
		
			//piso 2
			glPushMatrix();
				glTranslatef(0.0, 40.3, 0.0);
				glEnable(GL_ALPHA_TEST);
				glAlphaFunc(GL_GREATER, 0.1);
				glScalef(45.0, 20.0, 45.0);
				prisma(vieja.GLindex, entrada2.GLindex);
				glEnable(GL_ALPHA_TEST);
			glPopMatrix();
		
			//muralla
			glPushMatrix();
				glTranslatef(60.0, 15.0, 80.0);
				glScalef(60.0, 40.0, 2.0);
				prisma(vieja.GLindex, vieja.GLindex);
			glPopMatrix();
		
			glPushMatrix();
				glTranslatef(0.0, 15.0, -75.0);
				glScalef(182.0, 40.0, 2.0);
				prisma(vieja.GLindex, vieja.GLindex);
			glPopMatrix();
		
			glPushMatrix();
				glTranslatef(90.0, 15.0, 0.0);
				glScalef(2.0, 40.0, 150.0);
				prisma(vieja.GLindex, vieja.GLindex);
			glPopMatrix();
		
			glPushMatrix();
				glTranslatef(-90.0, 15.0, 0.0);
				glScalef(2.0, 40.0, 150.0);
				prisma(vieja.GLindex, vieja.GLindex);
			glPopMatrix();
		
			glPushMatrix();
				glTranslatef(-95, -5, 80);
				fig1.cilindro(10, 70, 40, vieja.GLindex);
			glPopMatrix();
		
			glPushMatrix();
				glTranslatef(95, -5, 80);
				fig1.cilindro(10, 70, 40, vieja.GLindex);
			glPopMatrix();

		glPopMatrix();
	glPopMatrix();

	glEnable(GL_LIGHTING);
}


void monitoCT(GLuint textura) //se modifico
{
	//glNewList(1, GL_COMPILE);
	glPushMatrix();//Pecho
		glScalef(0.5, 0.5, 0.5);
		fig7.prisma(2.0, 2.0, 1, textura);

		glPushMatrix();//Cuello
			glTranslatef(0, 1.0, 0.0);
			fig7.cilindro(0.25, 0.25, 15, textura);
				glPushMatrix();//Cabeza
				glTranslatef(0.0, 0.8, 0.0);
				fig7.esfera(0.75, 15, 15, textura);
				glPopMatrix();
		glPopMatrix();

		glPushMatrix(); //Brazo derecho--> //se modifico
			glTranslatef(1.25, 0.65, 0);
			fig7.esfera(0.5, 12, 12, textura);
			glPushMatrix();
				glTranslatef(0.25, 0, 0);
				glRotatef(-45 +0, 0, 1, 0);  //agregado
				glTranslatef(0.75, 0, 0);
				fig7.prisma(0.7, 1.5, 0.7, textura);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix(); //Brazo izquierdo <-- //se modifico
			glTranslatef(-1.25, 0.65, 0);
			fig7.esfera(0.5, 12, 12, textura);
			glPushMatrix();
				glTranslatef(-0.25, 0, 0);
				glRotatef(45, 0, 1, 0);
				//glRotatef(25, 0, 0, 1);
				glRotatef(25 + 0, 0, 1, 0);  //agregado
				glTranslatef(-0.75, 0, 0);
				fig7.prisma(0.7, 1.5, 0.7, textura);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();//Cintura
			glTranslatef(0, +-1.5, 0);
			fig7.prisma(1, 2, 1, textura);

			glPushMatrix(); //Pie Derecho -->
					glTranslatef(0.75, -0.5, 0);
					glRotatef(-15, 1, 0, 0);
					glTranslatef(0, -0.5, 0);
					fig7.prisma(1.0, 0.5, 1, textura);

					glPushMatrix();
					glTranslatef(0, -0.5, 0);
						glRotatef(15 + 0, 1, 0, 0);
						glTranslatef(0, -0.75, 0);
						fig7.prisma(1.5, 0.5, 1, textura);

						glPushMatrix();
						glTranslatef(0, -0.75, 0.3);
						fig7.prisma(0.2, 1.2, 1.5, textura);
					glPopMatrix();
			glPopMatrix();
		
		glPopMatrix();


		glPushMatrix(); //Pie Izquierdo -->
			glTranslatef(-0.75, -0.5, 0);
			glRotatef(-5, 1, 0, 0);
			glTranslatef(0, -0.5, 0);
			fig7.prisma(1.0, 0.5, 1, textura);

			glPushMatrix();
				glTranslatef(0, -0.5, 0);
				glRotatef(15 + 0, 1, 0, 0);
				glTranslatef(0, -0.75, 0);
				fig7.prisma(1.5, 0.5, 1, textura);

				glPushMatrix();
					glTranslatef(0, -0.75, 0.3);
					fig7.prisma(0.2, 1.2, 1.5, textura);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();


		glPopMatrix();


		glColor3f(1, 1, 1);
	glPopMatrix();

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

	textComedor.LoadBMP("casa/madera.bmp");
	textComedor.BuildGLTexture();
	textComedor.ReleaseImage();

	textPisoCasa.LoadBMP("casa/floor-parquet.bmp");
	textPisoCasa.BuildGLTexture();
	textPisoCasa.ReleaseImage();

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

	//CASTILLO TEXTURAS//////////////////////////////
	textBarrote.LoadBMP("casa/brickwall.bmp");
	textBarrote.BuildGLTexture();
	textBarrote.ReleaseImage();

	entrada.LoadTGA("texturas/entrada.tga");
	entrada.BuildGLTexture();
	entrada.ReleaseImage();

	puerta.LoadTGA("texturas/puerta.tga");
	puerta.BuildGLTexture();
	puerta.ReleaseImage();

	pasto.LoadTGA("texturas/pasto.tga");
	pasto.BuildGLTexture();
	pasto.ReleaseImage();

	textPiso.LoadBMP("casa/floor-parquet.bmp");
	textPiso.BuildGLTexture();
	textPiso.ReleaseImage();

	textTecho.LoadBMP("casa/brick_3.bmp");
	textTecho.BuildGLTexture();
	textTecho.ReleaseImage();

	tierra.LoadTGA("texturas/tierra.tga");
	tierra.BuildGLTexture();
	tierra.ReleaseImage();

	entrada2.LoadTGA("texturas/entrada2.tga");
	entrada2.BuildGLTexture();
	entrada2.ReleaseImage();

	vieja.LoadTGA("texturas/vieja.tga");
	vieja.BuildGLTexture();
	vieja.ReleaseImage();

	/////DENTRO CASTILLO/////
	metal.LoadTGA("texturas/metalLimpio.tga");
	metal.BuildGLTexture();
	metal.ReleaseImage();

	sangre.LoadTGA("texturas/sangre.tga");
	sangre.BuildGLTexture();
	sangre.ReleaseImage();

	sangre2.LoadTGA("texturas/sangre2.tga");
	sangre2.BuildGLTexture();
	sangre2.ReleaseImage();

	textMarble.LoadBMP("casa/marble_2.bmp");
	textMarble.BuildGLTexture();
	textMarble.ReleaseImage();

	//****TEXTURAS PERSONAJES///
	textCarnePodrida.LoadBMP("texturas/podrido.bmp");
	textCarnePodrida.BuildGLTexture();
	textCarnePodrida.ReleaseImage();

	textPelo.LoadBMP("texturas/pelo.bmp");
	textPelo.BuildGLTexture();
	textPelo.ReleaseImage();

	textpiel.LoadBMP("texturas/piel.bmp");
	textpiel.BuildGLTexture();
	textpiel.ReleaseImage();

	textVenda.LoadTGA("texturas/venda.tga");
	textVenda.BuildGLTexture();
	textVenda.ReleaseImage();


	///////Modelos 3ds/////////
	fantasma._3dsLoad("modelos/fantasma.3ds");


	objCamera.Position_Camera(-6+250, 4.0f,-5, -6+250, 4.0f,0, 0, 1, 0); //Posision inicial de la camara

	//NEW Iniciar variables de KeyFrames
	for(int i=0; i<MAX_FRAMES; i++)
	{
		KeyFrame[i].angBrazoDerEmpalado =0;
		KeyFrame[i].angBrazoIzqEmpalado =0;
		KeyFrame[i].angPiernaDerEmpalado =0;
		KeyFrame[i].angPiernaIzqEmpalado =0;
		KeyFrame[i].angBrazoDerEmpaladoInc =0;
		KeyFrame[i].angBrazoIzqEmpaladoInc =0;
		KeyFrame[i].angPiernaDerEmpaladoInc= 0;
		KeyFrame[i].angPiernaIzqEmpaladoInc = 0;
	}
	//NEW//////////////////NEW//////////////////NEW///////////

	//////ANIMACION DE MONITO EMPALADO////////
	//frame 1
	KeyFrame[0].angBrazoDerEmpalado = 0;
	KeyFrame[0].angBrazoIzqEmpalado = 0;
	KeyFrame[0].angPiernaDerEmpalado = 0;
	KeyFrame[0].angPiernaIzqEmpalado = 0;

	KeyFrame[1].angBrazoDerEmpalado = 30;
	KeyFrame[1].angBrazoIzqEmpalado = -108;
	KeyFrame[1].angPiernaDerEmpalado = -21;
	KeyFrame[1].angPiernaIzqEmpalado = 0;

	KeyFrame[2].angBrazoDerEmpalado = 62;
	KeyFrame[2].angBrazoIzqEmpalado = 9;
	KeyFrame[2].angPiernaDerEmpalado = 12;
	KeyFrame[2].angPiernaIzqEmpalado = -25;

	KeyFrame[3].angBrazoDerEmpalado = -42;
	KeyFrame[3].angBrazoIzqEmpalado = -51;
	KeyFrame[3].angPiernaDerEmpalado = 24;
	KeyFrame[3].angPiernaIzqEmpalado = 26;


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
					glTranslatef(200,1999.5,0);
					glRotatef(angNubes, 0, 1, 0);
					fig1.skybox_cielo(2000.0, 4000.0, 2000.0,text1.GLindex, textMar.GLindex, text1.GLindex, 1.0);
				glEnable(GL_LIGHTING);
			glPopMatrix();	

			/////PASTO_ISLAS////////////
			glPushMatrix();
				glDisable(GL_LIGHTING);
				//glTranslatef(0, 0, 0);
				pasto_islas.prisma_tablero(0.1, 80, 80, textGrass.GLindex, 10.0);
				glTranslatef(190, 0, 10);
				pasto_islas.prisma_tablero(0.1, 280, 300, textGrass.GLindex, 30.0);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			//////////CASTILLO/////////
			if (terror == true) {
				glPushMatrix();
					glTranslatef(490, -6.9, 10);
					//glTranslatef(210, 0, 30);
					glRotatef(270, 0, 1, 0);
					castillo();
				glPopMatrix();
			}

			//////////CASTILLO RUINAS/////////

			if (terror == false) {
				glPushMatrix();
					glTranslatef(490, -6.9, 10);
					//glTranslatef(190, 0, 10);
					glRotatef(270, 0, 1, 0);
					castillo_ruinas();
				glPopMatrix();
			}

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

			//////BOSQUE///////

				glPushMatrix();
					glDisable(GL_LIGHTING);
					glTranslatef(55, -1, -10);
					DibujaBosque();
					glEnable(GL_LIGHTING);
				glPopMatrix();

			//////CAMINO//////////
			glPushMatrix();
				glDisable(GL_LIGHTING);
				glTranslatef(245, 0.2, 10);
				camino.prisma_tablero(0.1, 460, 10, textPiedra.GLindex, 5.0);
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
	///
	//fprintf(escribir, "c");//silencio del teclado
	if (recorrido == true) {
		
		c = fgetc(ap);
		if (c != -1) {
			keyboardSimulado(c);
		}
	}

	///////*******NUBES*********////////////
	if (terror == false) {
		angNubes += 0.03;
		if (angNubes >= 360)
		{
			angNubes = 0;
		}
	}
		

	//////*********FUEGO******//////////////
	angFuego += 45.0;
	
	////////******ARBOLES******//////////////
	if (estado0Arboles && terror==false) {
		if (angArboles<10.0)
			angArboles += 8.0;
		else {
			estado0Arboles = false;
			estado1Arboles = true;
		}
	}

	if (estado1Arboles && terror==false) {
		if (angArboles>0.0)
			angArboles -= 8.0;
		else {
			estado1Arboles = false;
			estado0Arboles = true;
		}
	}

	//Movimiento monito empalado

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
			angBrazoDerEmpalado += KeyFrame[playIndex].angBrazoDerEmpaladoInc;
			angBrazoIzqEmpalado += KeyFrame[playIndex].angBrazoIzqEmpaladoInc;
			angPiernaDerEmpalado+= KeyFrame[playIndex].angPiernaDerEmpaladoInc;
			angPiernaIzqEmpalado += KeyFrame[playIndex].angPiernaIzqEmpaladoInc;


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

	////GUILLOTINA
	if (playGuillotina)
	{
		if (estado1Guillotina) //estado 1
		{
			despGuillotina -=0.1;
			if (despGuillotina<-6.5)
			{
				estado1Guillotina = false;
				estado2Guillotina = true;
			}
		}

		if (estado2Guillotina) //estado 2
		{
			guillotinaPausa += 0.1;
			if (guillotinaPausa> 3)
			{
				estado2Guillotina = false;
				estado3Guillotina = true;
			}
		}

		if (estado3Guillotina) //estado 3
		{
			despGuillotina += 0.1;
			if (despGuillotina >= 0)
			{
				estado3Guillotina = false;
				estado4Guillotina = true;
			}
		}

		if (estado4Guillotina) //estado 4
		{
			despGuillotina -= 0.3;
			if (despGuillotina<-8)
			{
				metal.LoadTGA("texturas/metal.tga");
				metal.BuildGLTexture();
				metal.ReleaseImage();
				estado4Guillotina = false;
				estado5Guillotina = true;
			}
		}

		if (estado5Guillotina) //estado 5
		{
			despCabezaGuillotinaZ -= 0.3;
			despCabezaGuillotinaY = -0.1*0.1;
			if (despCabezaGuillotinaZ<-5)
			{
				estado5Guillotina = false;
			}
		}
	}

//////MOMIA
	//piernas
	if (playMomia)
	{
		if (estado1Pmomia) //estado 1
		{
			angPiernaDerMomia += 5.0;
			angPiernaIzqMomia -= 5.0;
			if (angPiernaDerMomia>35)
			{
				estado1Pmomia = false;
				estado2Pmomia = true;
			}
		}

		if (estado2Pmomia) //estado 2
		{
			angPiernaDerMomia -= 5.0;
			angPiernaIzqMomia += 5.0;
			if (angPiernaDerMomia< -35)
			{
				estado2Pmomia = false;
				estado1Pmomia = true;
			}
		}

	}
	///DESP MOMIA

	if (playMomia)
	{
		if (estado1Momia) //estado 1
		{
			MomiaZ += 0.1;
			MomiaX = sqrt((5 * 5) - MomiaZ*MomiaZ);

			if (MomiaZ>=-1.80)
			{
				giroMomia -= 20;
				estado1Momia = false;
				estado2Momia = true;
			}
		}

		if (estado2Momia) //estado 2
		{
			MomiaZ += 0.1;
			MomiaX = sqrt((5 * 5) - MomiaZ*MomiaZ);

			if (MomiaZ >= 3.70)
			{
				giroMomia -= 50;
				estado2Momia = false;
				estado3Momia = true;
			}
		}

		if (estado3Momia) //estado 3
		{
			MomiaZ += 0.1;
			MomiaX = sqrt((5 * 5) - MomiaZ*MomiaZ);

			if (MomiaZ >= 4.99)
			{
				giroMomia -= 50;
				estado3Momia = false;
				estado4Momia = true;
			}
		}

		if (estado4Momia) //estado 4
		{
			giroMomia -= 1.0;
			MomiaZ -= 0.1;
			MomiaX = -sqrt((5 * 5) - MomiaZ*MomiaZ);

			if (MomiaZ <= -0.8)
			{
				giroMomia -= 50;
				estado4Momia = false;
				estado5Momia = true;
			}
		}

		if (estado5Momia) //estado 5
		{
			giroMomia -= 1.0;
			MomiaZ -= 0.1;
			MomiaX = -sqrt((5 * 5) - MomiaZ*MomiaZ);

			if (MomiaZ <= -2.99)
			{
				giroMomia -= 30;
				estado5Momia = false;
				estado6Momia = true;
			}
		}

		if (estado6Momia) //estado 5
		{
			giroMomia -= 1.0;
			MomiaZ -= 0.1;
			MomiaX = -sqrt((5 * 5) - MomiaZ*MomiaZ);

			if (MomiaZ <= -4.99)
			{
				giroMomia = 0;
				estado6Momia = false;
				estado1Momia = true;
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
	//printf("%.2f \n", objCamera.mPos.x);
	//printf("%.2f \n", objCamera.mPos.y);
	//printf("%.2f \n", objCamera.mPos.x);
	//printf("%.2f \n", MomiaZ);
	//printf("%.2f \n", giroMomia);
	if (objCamera.mPos.x>54 && terror==true && organo==true) {
		organo = false;
		PlayBach();
	}

	switch ( key ) {
		case 'w':   //Movimientos de camara
				objCamera.Move_Camera(CAMERASPEED + 0.3);
				//fprintf(escribir, "w");
			break;
		case 'q':
				objCamera.Move_Camera(CAMERASPEED + 0.6);
			break;

		case 's':
		case 'S':
			objCamera.Move_Camera(-(CAMERASPEED+0.3));
			//fprintf(escribir, "s");
			break;

		case 'a':
		case 'A':
			objCamera.Strafe_Camera(-(CAMERASPEED+0.3));
			//fprintf(escribir, "a");
			break;

		case 'd':
		case 'D':
			objCamera.Strafe_Camera( CAMERASPEED+0.3 );
			////fprintf(escribir, "d");
			break;

		//case 'k':		//
		//case 'K':
		//	if(FrameIndex<MAX_FRAMES)
		//	{
		//		saveFrame();
		//	}
		//	break;

		case 'l':						
		case 'L':
			//fprintf(escribir, "l");
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
			//fprintf(escribir, "z");
			if (objCamera.mPos.z > -7 && objCamera.mPos.z < -1 && objCamera.mPos.x>0 && objCamera.mPos.x<6)
			{
				texturas_casa_terror();
				terror = true;
				PlaySound(NULL, NULL, 0);
				PlayMozart();
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

		case 'm':						
		case 'M':
			playMomia = !playMomia;
			//fprintf(escribir, "m");
			break;

		case 'c':						
		case 'C':
			//fprintf(escribir, "c");
			break;

		case 'r':
		case 'R':
			if (recorrido==false)
				objCamera.Position_Camera(-6 + 250, 4.0f, -5, -6 + 250, 4.0f, 0, 0, 1, 0);
			recorrido = true;
			break;

		case 'g':
		case 'G':
			playGuillotina = !playGuillotina;
			//fprintf(escribir, "g");
			break;

		case 27:        // Cuando Esc es presionado...
			//fprintf(escribir, "e");
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
		if (objCamera.mPos.y<500)
		objCamera.UpDown_Camera(CAMERASPEED*2);
		//fprintf(escribir, "5");
		break;

	case GLUT_KEY_PAGE_DOWN:
		if (objCamera.mPos.y>3)
			objCamera.UpDown_Camera(-CAMERASPEED*2);
			//fprintf(escribir, "6");
		break;

    case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		g_lookupdown -= 1.0f;
		//fprintf(escribir, "1");
		break;

    case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		g_lookupdown += 1.0f;
		//fprintf(escribir, "2");
		break;

	case GLUT_KEY_LEFT:
		objCamera.Rotate_View(-CAMERASPEED);
		//fprintf(escribir, "2");
		break;

	case GLUT_KEY_RIGHT:
		objCamera.Rotate_View( CAMERASPEED);
		//fprintf(escribir, "3");
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
 // escribir = fopen("escribir.txt", "w+");
  int submenu;
  glutInit            (&argc, argv); // Inicializamos OpenGL
  glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
  glutInitWindowSize  (500, 500);	// Tamaño de la Ventana
  glutInitWindowPosition (0, 0);	//Posicion de la Ventana
  glutCreateWindow    ("Proyecto Final"); // Nombre de la Ventana
  glutFullScreen     ( );         // Full Screen
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
  fclose(ap);

  return 0;
}