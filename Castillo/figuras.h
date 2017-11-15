//#include <windows.h>  //Solo para Windows
//#include <GL/gl.h>     // The GL Header File
//#include <stdio.h>

//#include <math.h>
#include "Main.h"


class CFiguras
{
	public:

	float text_der;
	float text_izq;

	void esfera(GLfloat radio, int meridianos, int paralelos, GLuint text); //Func�on creacion esfera
	void cilindro(float radio, float altura, int resolucion, GLuint text);	//Func�on creacion cilindro
	void cono(float altura, float radio, int resolucion, GLuint text, float repeticion_de_textura);		//Func�on creacion cono
	void prisma_anun (GLuint text, GLuint text2);							//Func�on creacion movimiento
	void prisma (float altura, float largo, float profundidad, GLuint text);//Func�on creacion prisma
	void prisma_tablero(float altura, float largo, float profundidad, GLuint text, float repeticion_text);
	void prisma2 (GLuint text, GLuint text2);
	void skybox(float altura, float largo, float profundidad, GLuint text, float repeticion);	//Funcion creacion cielo
	void skybox_cielo(float largo, float altura, float profundidad, GLuint text_lados, GLuint text_piso, GLuint text_superior, float r);
	void skybox_sin_tapa(float largo, float altura, float profundidad, GLuint text, float r);
	void skybox_casa(float altura, float largo, float profundidad, GLuint text_paredes, GLuint text_piso, GLuint text_puerta, GLuint text_techo, float repeticion_paredes, float repeticion_piso, float repeticion_techo, float angPuertaCasa);

	//void torus(GLfloat radioM, GLfloat radiom, int meridianos, int paralelos, GLuint text );
	void torus(GLfloat radioM, GLfloat radiom, int meridianos, int paralelos);

};
