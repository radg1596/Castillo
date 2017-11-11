//Semestre 2017 - 2
//************************************************************//
//************************************************************//
//************** Alumno (s): *********************************//
//*************											******//
//*************											******//
//************************************************************//
//************************************************************//

#include "texture.h"
#include "figuras.h"
#include "Camera.h"

#include "cmodel/CModel.h"

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

///TEXTURAS///////

CTexture text1; //cielo1


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
CTexture textGrass;
CTexture textAlmohada;
CTexture textColcha;
CTexture textMaderaBuro;
CTexture textMaderaCama;

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
CFiguras cono;
CFiguras cubo;

//Exterior
CFiguras pasto;

//END NEW//////////////////////////////////////////

/////////////Figuras del entorno///////////////////
CFiguras fig1; //Skybox
//////////Figuras de las paredes de la casa//////////////////////// 
CFiguras paredescasa;
CFiguras paredf; //pared frontal 

void saveFrame ( void )
{
	
	printf("frameindex %d\n",FrameIndex);			
			
	FrameIndex++;
}

void resetElements( void )
{


}

void interpolation ( void )
{
	

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
		paredescasa.skybox_casa(26, 30, 30, textWall.GLindex, textPiso.GLindex, textPuerta_Casa.GLindex, textTechoCasa.GLindex, 1.0f, 8.0f, 3.0f);
		glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	//Techo de la casa
	glPushMatrix();
		glTranslatef(0, 16.5, 0);
		cubo.prisma_tablero(4, 35, 35, textTechoCasa.GLindex, 3.0 );
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
//END CASA////////////////////////////////////

			
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

    
    text1.LoadBMP("texturas/cielo1.bmp");
	text1.BuildGLTexture();
	text1.ReleaseImage();

	//NEW////////////////////////////////////////////
	textPuerta_Casa.LoadBMP("casa/door_3.bmp");
	textPuerta_Casa.BuildGLTexture();
	textPuerta_Casa.ReleaseImage();

	textWall.LoadBMP("casa/pared_vieja.bmp");
	textWall.BuildGLTexture();
	textWall.ReleaseImage();

	textSilla.LoadBMP("casa/madera.bmp");
	textSilla.BuildGLTexture();
	textSilla.ReleaseImage();

	textMarble.LoadBMP("casa/marble_2.bmp");
	textMarble.BuildGLTexture();
	textMarble.ReleaseImage();

	textPiso.LoadBMP("casa/floor-parquet.bmp");
	textPiso.BuildGLTexture();
	textPiso.ReleaseImage();

	textTechoCasa.LoadBMP("casa/tejado.bmp");
	textTechoCasa.BuildGLTexture();
	textTechoCasa.ReleaseImage();
	
	textCuadro1.LoadBMP("casa/zamoxdxd.bmp");
	textCuadro1.BuildGLTexture();
	textCuadro1.ReleaseImage();

	textGrass.LoadTGA("texturas/pasto.tga");
	textGrass.BuildGLTexture();
	textGrass.ReleaseImage();
	
	//*****ROSE******
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

	//END NEW//////////////////////////////

	objCamera.Position_Camera(-6, 6.0f,-5, -6, 6.0f,0, 0, 1, 0); //Posision inicial de la camara

	//NEW Iniciar variables de KeyFrames
	for(int i=0; i<MAX_FRAMES; i++)
	{
		KeyFrame[i].posX =0;
		KeyFrame[i].posY =0;
		KeyFrame[i].posZ =0;
		KeyFrame[i].incX =0;
		KeyFrame[i].incY =0;
		KeyFrame[i].incZ =0;
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
					glTranslatef(0,800,0);
					fig1.skybox(1600.0, 1600.0, 1600.0,text1.GLindex,1.0);
				glEnable(GL_LIGHTING);
			glPopMatrix();		

			///////PASTO////////////
			glPushMatrix();
				glDisable(GL_LIGHTING);
					pasto.prisma_tablero(0.1, 100, 100, textGrass.GLindex, 20.0);
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
				glPopMatrix();
				//¨****Interior casa*****
				glPushMatrix();
					glScalef(1.0, 0.5, 1.0);
					glTranslatef(-2.3, -12, 0.2);
					//glRotatef(180, 0, 1, 0);
					glDisable(GL_LIGHTING);
					glScalef(0.3, 0.3, 0.3);
			
					glPushMatrix();
						//****cuadros***			
						cuadro();
						//****COMEDOR***
						glPushMatrix();
							glTranslatef(-20,0,25);
							glScalef(1.3,1.3,1.3);
							comedor();
						glPopMatrix();

						//*****ROSE*****
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

					glPopMatrix();

				glEnable(GL_LIGHTING);
				glPopMatrix();
			
			glPopMatrix();// De interior casa

			glColor3f(1.0,1.0,1.0);

		glPopMatrix();// De casa entera

	glPopMatrix(); //Pop final

	glutSwapBuffers ( );

}

void animacion()
{
	//Movimiento del monito
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


			i_curr_steps++;
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
	
	glFrustum (-0.1, 0.1,-0.1, 0.1, 0.1, 3500.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{
	//printf("%.2f \n", objCamera.mPos.x);
	//printf("%.2f \n", objCamera.mPos.y);
	//printf("%.2f \n", objCamera.mPos.z);
	switch ( key ) {
		case 'w':   //Movimientos de camara
		case 'W':
				objCamera.Move_Camera(CAMERASPEED + 0.2);
			break;

		case 's':
		case 'S':
			objCamera.Move_Camera(-(CAMERASPEED+0.2));
			break;

		case 'a':
		case 'A':
			objCamera.Strafe_Camera(-(CAMERASPEED+0.4));
			break;

		case 'd':
		case 'D':
			objCamera.Strafe_Camera( CAMERASPEED+0.4 );
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

		case 'y':						
		case 'Y':
			textPuerta_Casa.LoadTGA("texturas/vacio.tga");
			textPuerta_Casa.BuildGLTexture();
			textPuerta_Casa.ReleaseImage();
			break;

		case 'g':						
		case 'G':
			break;

		case 'h':						
		case 'H':
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
		objCamera.UpDown_Camera(CAMERASPEED);
		break;

	case GLUT_KEY_PAGE_DOWN:
		if (objCamera.mPos.y>3)
			objCamera.UpDown_Camera(-CAMERASPEED);
		break;

    case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		g_lookupdown -= 1.0f;
		break;

    case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		g_lookupdown += 1.0f;
		break;

	case GLUT_KEY_LEFT:
		objCamera.Rotate_View(-CAMERASPEED);
		break;

	case GLUT_KEY_RIGHT:
		objCamera.Rotate_View( CAMERASPEED);
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
  int submenu;
  glutInit            (&argc, argv); // Inicializamos OpenGL
  glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
  glutInitWindowSize  (500, 500);	// Tamaño de la Ventana
  glutInitWindowPosition (0, 0);	//Posicion de la Ventana
  glutCreateWindow    ("Proyecto Final"); // Nombre de la Ventana
  //glutFullScreen     ( );         // Full Screen
  InitGL ();						// Parametros iniciales de la aplicacion
  glutDisplayFunc     ( display );  //Indicamos a Glut función de dibujo
  glutReshapeFunc     ( reshape );	//Indicamos a Glut función en caso de cambio de tamano
  glutKeyboardFunc    ( keyboard );	//Indicamos a Glut función de manejo de teclado
  glutSpecialFunc     ( arrow_keys );	//Otras
  glutIdleFunc		  ( animacion );

  submenu = glutCreateMenu	  ( menuKeyFrame );
  glutAddMenuEntry	  ("Guardar KeyFrame", 0);
  glutAddMenuEntry	  ("Reproducir Animacion", 1);
  glutCreateMenu	  ( menu );
  glutAddSubMenu	  ("Animacion Monito", submenu);
 
  glutAttachMenu	  (GLUT_RIGHT_BUTTON);


  glutMainLoop        ( );          // 

  return 0;
}