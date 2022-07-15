/*
================================================================================================================================
	Departamento Eng. Informatica - FCTUC
	Computacao Grafica - 2021/22
	Inês Martins Marçal 2019215917
	Projeto Comando
================================================================================================================================ */
/* Nota: Para compilar é necessario efetuar os seguintes comandos no terminal:
		1º --->   g++ -o ProjetoNitendo ProjetoNitendo.cpp -lglut -lGLU -lGL -lm
		2º --->   ./ProjetoNitendo.
================================================================================================================================ */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "RgbImage.h"


//Definir cores
#define BLUE     0.0, 0.0, 1.0, 1.0
#define LIGHTBLUE 167/255.f, 206/255.f, 206/255.f, 1.0
#define RED		 1.0, 0.0, 0.0, 1.0
#define YELLOW	 1.0, 1.0, 0.0, 1.0
#define GREEN    0.0, 1.0, 0.0, 1.0
#define WHITE    1.0, 1.0, 1.0, 1.0
#define BLACK    0.0, 0.0, 0.0, 1.0
#define PI		 3.14159

//===================================================== Variaveis e constantes ==================================================

GLfloat inc = 0.020;
GLfloat inc_r = 2.5;
GLfloat centrox = 0;
GLfloat rotacaoDireita = 0;
GLfloat rotacaoDireita2 = 0;
GLfloat rotacaoEsquerda = 0;
GLfloat rotacaoEsquerda2 = 0;
GLfloat r, g, b;
GLuint   texture[9];
RgbImage imag;


GLboolean flags[17] = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
GLfloat pos[16] = { 0.24, 0.24, 0.24, 0.24, 0.24, 0.24, 0.24, 0.24, 0.24, 0.24, 0.24, 0.24, 0.24, 0.24, 0.24, 0.24 };
GLboolean flagCor[1] = { false };

//---------------------------------------------------- Materiais
GLfloat intensidadeDia = 1.0;
GLfloat luzGlobalCorAmb[4] = { intensidadeDia, intensidadeDia, intensidadeDia, 1.0 };
GLfloat value[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat difusa[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat especular[4] = { 0.0f, 0.0f, 0.0f, 1.0f };


//---------------------------------------------------- Foco
GLfloat Pos1[] = { 0, 4, 0, 1 };   // Foco 1

bool 		Focos =  0 ;		//.. Dois Focos ligados ou desligados
GLfloat		aberturaFoco = 6;		//.. angulo inicial do foco
GLfloat		anguloINC = 1.0;		//.. incremento
GLfloat		anguloMIN = 1.0;		//.. minimo
GLfloat		anguloMAX = 34.0;		//.. maximo


//---------------------------------------------------- Luz pontual no TETO
GLint   ligaTeto = 1;		 //:::   'T'  
GLfloat intensidadeT = 0.3;  //:::   'I'  
GLfloat   luzR = 1;		 	 //:::   'R'  
GLfloat   luzG = 1;			 //:::   'G'  
GLfloat   luzB = 1;			 //:::   'B'  
GLfloat localPos[4] = { 0.0, 4.0, 0.0, 1.0 };
GLfloat localCorAmb[4] = { 0, 0, 0, 0.0 };
GLfloat localCorDif[4] = { luzR, luzG, luzB, 1.0 };
GLfloat localCorEsp[4] = { luzR, luzG, luzB, 1.0 };


//---------------------------------------------------- Mesh
GLint	  dim = 10;   //numero divisoes da grelha
int				i, j;
float			med_dim = (float)dim / 2;
GLint malha = 0;

//--------------------------------------------------- Coeficiente de especularidade
GLfloat ks = 0.25;

//------------------------------------------------------ Vertices ---------------------------------------------------------------
GLfloat tam = 0.8;
static GLfloat vertices[] = {
	//x=tam (Esquerda)
		-tam,  -tam,  tam,	// 0 
		-tam,   tam,  tam,	// 1 
		-tam,   tam, -tam,	// 2 
		-tam,  -tam, -tam,	// 3 
	//Direita
		 tam,  -tam,  tam,	// 4 
		 tam,   tam,  tam,	// 5 
		 tam,   tam, -tam,	// 6 
		 tam,  -tam, -tam,	// 7 
	// Cima
		-tam,  tam,  tam,	// 8 
		-tam,  tam, -tam,	// 9 
		 tam,  tam, -tam,	// 10 
		 tam,  tam,  tam,	// 11
	// Baixo
		-tam,  -tam,  tam,	// 0 // 12 
		 -tam,  -tam,  -tam,	// 3 // 13 
		 tam,  -tam, -tam,	// 7 // 14
		tam,  -tam, tam,	// 4 // 15
	// Tras_1
		-tam,  -tam, -tam,	// 3 // 16 
		 -tam,   tam, -tam,	// 2 // 17 
		 tam,   tam, -tam,	// 6 // 18 
		tam,  -tam, -tam,	// 7 // 19
	// Frente_1
		-tam,  -tam,  tam,	// 0 // 20 
		-tam,   tam,  tam,	// 1 // 21 
		 tam,   tam,  tam,	// 5 // 22 
		tam,  -tam,  tam,	// 4 // 23

};

static GLfloat vertices2[] = {
	//x=tam Esquerda
		-tam,  -tam,  tam,	// 0 
		-tam,   tam,  tam,	// 1 
		-tam,   tam, -tam,	// 2 
		-tam,  -tam, -tam,	// 3 
	//Direita
		 tam,  -tam,  GLfloat(tam - 0.10),	// 4 
		 tam,   tam,  GLfloat(tam - 0.10),	// 5 
		 tam,   tam, GLfloat(-tam + 0.10),	// 6 
		 tam,  -tam, GLfloat(-tam + 0.10),	// 7 
	// Cima
		-tam,  tam,  tam,	// 8 
		-tam,  tam, -tam,	// 9 
		 tam,  tam, GLfloat(-tam + 0.10),	// 10 
		 tam,  tam,  GLfloat(tam - 0.10),	// 11
	// Baixo
		-tam,  -tam,  tam,	// 0 // 12 
		 -tam,  -tam,  -tam,	// 3 // 13 
		 tam,  -tam, GLfloat(-tam + 0.10),	// 7 // 14
		tam,  -tam, GLfloat(tam - 0.10),	// 4 // 15
	// Tras_1
		-tam,  -tam, -tam,	// 3 // 16 
		-tam,   tam, -tam,	// 2 // 17 
		 tam,   tam, GLfloat(-tam + 0.10),	// 6 // 18 
		tam,  -tam, GLfloat(-tam + 0.10),	// 7 // 19
	// Frente_1
		-tam,  -tam,  tam,	// 0 // 20 
		-tam,   tam,  tam,	// 1 // 21 
		tam,   tam,  GLfloat(tam - 0.10),	// 5 // 22 
		tam,  -tam,  GLfloat(tam - 0.10),	// 4 // 23

};

static GLfloat normais[] = {
		// x=tam (Esquerda)
		-1.0,  0.0,  0.0,
		-1.0,  0.0,  0.0,
		-1.0,  0.0,  0.0,
		-1.0,  0.0,  0.0,
		// x=tam (Direita)
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		// y=tam (Cima)
		0.0,  1.0,  0.0,
		0.0,  1.0,  0.0,
		0.0,  1.0,  0.0,
		0.0,  1.0,  0.0,

		// y=tam (Baixo)
		0.0,  -1.0,  0.0,
		0.0,  -1.0,  0.0,
		0.0,  -1.0,  0.0,
		0.0,  -1.0,  0.0,

		// y=tam (Tras_1)
		0.0,  0.0,  1.0,
		0.0,  0.0,  1.0,
		0.0,  0.0,  1.0,
		0.0,  0.0,  1.0,

		// y=tam (Frente_1)
		0.0,  0.0,  -1.0,
		0.0,  0.0,  -1.0,
		0.0,  0.0,  -1.0,
		0.0,  0.0,  -1.0,
};

static GLfloat normais2[] = {
		// x=tam (Esquerda)
		-1.0,  0.0,  0.0,
		-1.0,  0.0,  0.0,
		-1.0,  0.0,  0.0,
		-1.0,  0.0,  0.0,
		// x=tam (Direita)
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		// y=tam (Cima)
		0.0,  1.0,  0.0,
		0.0,  1.0,  0.0,
		0.0,  1.0,  0.0,
		0.0,  1.0,  0.0,

		// y=tam (Baixo)
		0.0,  -1.0,  0.0,
		0.0,  -1.0,  0.0,
		0.0,  -1.0,  0.0,
		0.0,  -1.0,  0.0,

		// y=tam (Tras_1)
		-0.16 / sqrt(6.5792), 0.0, 2.56 / sqrt(6.5792),
		-0.16 / sqrt(6.5792), 0.0, 2.56 / sqrt(6.5792),
		-0.16 / sqrt(6.5792), 0.0, 2.56 / sqrt(6.5792),
		-0.16 / sqrt(6.5792), 0.0, 2.56 / sqrt(6.5792),

		// y=tam (Frente_1)
		0.16 / sqrt(6.5792), 0.0, -2.56 / sqrt(6.5792),
		0.16 / sqrt(6.5792), 0.0, -2.56 / sqrt(6.5792),
		0.16 / sqrt(6.5792), 0.0, -2.56 / sqrt(6.5792),
		0.16 / sqrt(6.5792), 0.0, -2.56 / sqrt(6.5792),
};
//-------------------------------------------------- Cores-------------------------------------------------------

//Cinzento
static GLfloat cor[] = {

		79 / 255.f,  85 / 255.f, 85 / 255.f,
		79 / 255.f,  85 / 255.f, 85 / 255.f,
		79 / 255.f,  85 / 255.f, 85 / 255.f,
		79 / 255.f,  85 / 255.f, 85 / 255.f,

		79 / 255.f,  85 / 255.f, 85 / 255.f,
		79 / 255.f,  85 / 255.f, 85 / 255.f,
		79 / 255.f,  85 / 255.f, 85 / 255.f,
		79 / 255.f,  85 / 255.f, 85 / 255.f,

		79 / 255.f,  85 / 255.f, 85 / 255.f,
		79 / 255.f,  85 / 255.f, 85 / 255.f,
		79 / 255.f,  85 / 255.f, 85 / 255.f,
		79 / 255.f,  85 / 255.f, 85 / 255.f,

		79 / 255.f,  85 / 255.f, 85 / 255.f,
		79 / 255.f,  85 / 255.f, 85 / 255.f,
		79 / 255.f,  85 / 255.f, 85 / 255.f,
		79 / 255.f,  85 / 255.f, 85 / 255.f,

		79 / 255.f,  85 / 255.f, 85 / 255.f,
		79 / 255.f,  85 / 255.f, 85 / 255.f,
		79 / 255.f,  85 / 255.f, 85 / 255.f,
		79 / 255.f,  85 / 255.f, 85 / 255.f,

		79 / 255.f,  85 / 255.f, 85 / 255.f,
		79 / 255.f,  85 / 255.f, 85 / 255.f,
		79 / 255.f,  85 / 255.f, 85 / 255.f,
		79 / 255.f,  85 / 255.f, 85 / 255.f,


};

//Vermelho
static GLfloat cor2[] = {

		239 / 255.f,  46 / 255.f, 46 / 255.f,
		239 / 255.f,  46 / 255.f, 46 / 255.f,
		239 / 255.f,  46 / 255.f, 46 / 255.f,
		239 / 255.f,  46 / 255.f, 46 / 255.f,

		239 / 255.f,  46 / 255.f, 46 / 255.f,
		239 / 255.f,  46 / 255.f, 46 / 255.f,
		239 / 255.f,  46 / 255.f, 46 / 255.f,
		239 / 255.f,  46 / 255.f, 46 / 255.f,

		239 / 255.f,  46 / 255.f, 46 / 255.f,
		239 / 255.f,  46 / 255.f, 46 / 255.f,
		239 / 255.f,  46 / 255.f, 46 / 255.f,
		239 / 255.f,  46 / 255.f, 46 / 255.f,

		239 / 255.f,  46 / 255.f, 46 / 255.f,
		239 / 255.f,  46 / 255.f, 46 / 255.f,
		239 / 255.f,  46 / 255.f, 46 / 255.f,
		239 / 255.f,  46 / 255.f, 46 / 255.f,

		239 / 255.f,  46 / 255.f, 46 / 255.f,
		239 / 255.f,  46 / 255.f, 46 / 255.f,
		239 / 255.f,  46 / 255.f, 46 / 255.f,
		239 / 255.f,  46 / 255.f, 46 / 255.f,

		239 / 255.f,  46 / 255.f, 46 / 255.f,
		239 / 255.f,  46 / 255.f, 46 / 255.f,
		239 / 255.f,  46 / 255.f, 46 / 255.f,
		239 / 255.f,  46 / 255.f, 46 / 255.f,


};

//Azul
static GLfloat cor3[] = {

		  46 / 255.f,  162 / 255.f, 239 / 255.f,
		  46 / 255.f,  162 / 255.f, 239 / 255.f,
		  46 / 255.f,  162 / 255.f, 239 / 255.f,
		  46 / 255.f,  162 / 255.f, 239 / 255.f,

		  46 / 255.f,  162 / 255.f, 239 / 255.f,
		  46 / 255.f,  162 / 255.f, 239 / 255.f,
		  46 / 255.f,  162 / 255.f, 239 / 255.f,
		  46 / 255.f,  162 / 255.f, 239 / 255.f,

		  46 / 255.f,  162 / 255.f, 239 / 255.f,
		  46 / 255.f,  162 / 255.f, 239 / 255.f,
		  46 / 255.f,  162 / 255.f, 239 / 255.f,
		  46 / 255.f,  162 / 255.f, 239 / 255.f,

		  46 / 255.f,  162 / 255.f, 239 / 255.f,
		  46 / 255.f,  162 / 255.f, 239 / 255.f,
		  46 / 255.f,  162 / 255.f, 239 / 255.f,
		  46 / 255.f,  162 / 255.f, 239 / 255.f,

		  46 / 255.f,  162 / 255.f, 239 / 255.f,
		  46 / 255.f,  162 / 255.f, 239 / 255.f,
		  46 / 255.f,  162 / 255.f, 239 / 255.f,
		  46 / 255.f,  162 / 255.f, 239 / 255.f,

		  46 / 255.f,  162 / 255.f, 239 / 255.f,
		  46 / 255.f,  162 / 255.f, 239 / 255.f,
		  46 / 255.f,  162 / 255.f, 239 / 255.f,
		  46 / 255.f,  162 / 255.f, 239 / 255.f,


};

//Preto
static GLfloat cor4[] = {

		0.0,  0.0, 0.0,
		0.0,  0.0, 0.0,
		0.0,  0.0, 0.0,
		0.0,  0.0, 0.0,

		0.0,  0.0, 0.0,
		0.0,  0.0, 0.0,
		0.0,  0.0, 0.0,
		0.0,  0.0, 0.0,

		0.0,  0.0, 0.0,
		0.0,  0.0, 0.0,
		0.0,  0.0, 0.0,
		0.0,  0.0, 0.0,

		0.0,  0.0, 0.0,
		0.0,  0.0, 0.0,
		0.0,  0.0, 0.0,
		0.0,  0.0, 0.0,

		0.0,  0.0, 0.0,
		0.0,  0.0, 0.0,
		0.0,  0.0, 0.0,
		0.0,  0.0, 0.0,

		0.0,  0.0, 0.0,
		0.0,  0.0, 0.0,
		0.0,  0.0, 0.0,
		0.0,  0.0, 0.0,


};

//Preto
static GLfloat cor6[] = {

		0.0,  0.0, 0.0,
		0.0,  0.0, 0.0,
		0.0,  0.0, 0.0,
		0.0,  0.0, 0.0,

		0.0,  0.0, 0.0,
		0.0,  0.0, 0.0,
		0.0,  0.0, 0.0,
		0.0,  0.0, 0.0,

		243 / 255.f,  243 / 255.f, 154 / 255.f,
		243 / 255.f,  243 / 255.f, 154 / 255.f,
		243 / 255.f,  243 / 255.f, 154 / 255.f,
		243 / 255.f,  243 / 255.f, 154 / 255.f,

		0.0,  0.0, 0.0,
		0.0,  0.0, 0.0,
		0.0,  0.0, 0.0,
		0.0,  0.0, 0.0,

		0.0,  0.0, 0.0,
		0.0,  0.0, 0.0,
		0.0,  0.0, 0.0,
		0.0,  0.0, 0.0,

		0.0,  0.0, 0.0,
		0.0,  0.0, 0.0,
		0.0,  0.0, 0.0,
		0.0,  0.0, 0.0,


};

//Laranja
static GLfloat cor5[] = {

		  233 / 255.f,  136 / 255.f, 0 / 255.f,
		  233 / 255.f,  136 / 255.f, 0 / 255.f,
		  233 / 255.f,  136 / 255.f, 0 / 255.f,
		  233 / 255.f,  136 / 255.f, 0 / 255.f,

		  233 / 255.f,  136 / 255.f, 0 / 255.f,
		  233 / 255.f,  136 / 255.f, 0 / 255.f,
		  233 / 255.f,  136 / 255.f, 0 / 255.f,
		  233 / 255.f,  136 / 255.f, 0 / 255.f,

		  233 / 255.f,  136 / 255.f, 0 / 255.f,
		  233 / 255.f,  136 / 255.f, 0 / 255.f,
		  233 / 255.f,  136 / 255.f, 0 / 255.f,
		  233 / 255.f,  136 / 255.f, 0 / 255.f,

		  233 / 255.f,  136 / 255.f, 0 / 255.f,
		  233 / 255.f,  136 / 255.f, 0 / 255.f,
		  233 / 255.f,  136 / 255.f, 0 / 255.f,
		  233 / 255.f,  136 / 255.f, 0 / 255.f,

		  233 / 255.f,  136 / 255.f, 0 / 255.f,
		  233 / 255.f,  136 / 255.f, 0 / 255.f,
		  233 / 255.f,  136 / 255.f, 0 / 255.f,
		  233 / 255.f,  136 / 255.f, 0 / 255.f,

		  233 / 255.f,  136 / 255.f, 0 / 255.f,
		  233 / 255.f,  136 / 255.f, 0 / 255.f,
		  233 / 255.f,  136 / 255.f, 0 / 255.f,
		  233 / 255.f,  136 / 255.f, 0 / 255.f,


};

static GLfloat texturas[] = {
0, 0,
1, 0,
1, 1,
0, 1,
0, 0,
1, 0,
1, 1,
0, 1,
0, 0,
1, 0,
1, 1,
0, 1,
0, 0,
1, 0,
1, 1,
0, 1,
0, 0,
1, 0,
1, 1,
0, 1,
0, 0,
1, 0,
1, 1,
0, 1,
};


//=========================================================== FACES DO CUBO BASE ======================================================
GLboolean   frenteVisivel = 1;
static GLint faces[6][4] = {
				{0, 1,  2,  3 },    //esquerda
				{4, 7,  6,  5 },    //direita
				{8, 11, 10, 9 },    //cima
				{12, 13, 14, 15},   //baixo
				{16, 17, 18, 19 },  //tras_1
				{20, 23, 22, 21 }   //frente_1
};



//------------------------------------------------ Objetos (sistema coordenadas) ------------------------------------------
GLint		wScreen = 800, hScreen = 600;			//.. janela (pixeis)
GLfloat		xC = 10.0, yC = 10.0, zC = 10.0;		//.. Mundo  (unidades mundo)

//------------------------------------------------ Visualizacao/Observador -------------------------------------------------

GLfloat M = 0, N = 0, incMN = 1 / 180.f;
GLfloat  rVisao = 10, thetaV = M * PI / 180.f + 0.5 * PI, phiV = N * PI / 180.f + 0.5 * PI, incVisao = 0.05;   //rVisao = distancia 
GLfloat Y = 1;
GLfloat  obsP[] = { rVisao * cos(thetaV) * sin(phiV), rVisao * cos(phiV) , rVisao * sin(thetaV) * sin(phiV) };
GLfloat  angZoom = 45;
GLfloat  incZoom = 3;

GLint     msec = 10;

GLint on_off = -1, rodar = -1;
GLint zoom_in = 0, zoom_out = 0;



//============================================================= TEXTURAS ========================================================

//Funcao que permite inicializar as texturas.
void initTexturas() {

	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	imag.LoadBmpFile("logo_.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	glGenTextures(1, &texture[1]);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	imag.LoadBmpFile("logo_base.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	glGenTextures(1, &texture[2]);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	imag.LoadBmpFile("A.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	glGenTextures(1, &texture[3]);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	imag.LoadBmpFile("Y.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	glGenTextures(1, &texture[4]);
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	imag.LoadBmpFile("X.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	glGenTextures(1, &texture[5]);
	glBindTexture(GL_TEXTURE_2D, texture[5]);
	imag.LoadBmpFile("B.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	glGenTextures(1, &texture[6]);
	glBindTexture(GL_TEXTURE_2D, texture[6]);
	imag.LoadBmpFile("textura_base2.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	glGenTextures(1, &texture[7]);
	glBindTexture(GL_TEXTURE_2D, texture[7]);
	imag.LoadBmpFile("SuperMario.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	

}


//============================================================= INIT ==========================================================

void inicializa(void)
{
	glClearColor(BLACK);	//Apagar
	glEnable(GL_DEPTH_TEST);	//Profundidade
	glShadeModel(GL_SMOOTH);	//Interpolacao de cores

	initTexturas();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	//glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

}

//============================================================ MESH =============================================================

//Funcao que permite desenhar o poligono para a mesh.
void drawMesh(GLfloat meshW, GLfloat meshH, GLfloat h) {
	GLfloat alpha = 0.8;

	glPushMatrix();
	glNormal3f(0, 1, 0);          //normal 

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glBegin(GL_QUADS);
	for (int i = 0; i < dim - 1; i++) {
		for (int j = 0; j < dim - 1; j++) {
			GLfloat w0 = meshW * i / float(dim - 1);
			GLfloat h0 = meshH * j / float(dim - 1);
			GLfloat u0 = i / float(dim - 1);
			GLfloat v0 = j / float(dim - 1);

			GLfloat w1 = meshW * (i + 1) / float(dim - 1);
			GLfloat h1 = meshH * j / float(dim - 1);
			GLfloat u1 = (i + 1) / float(dim - 1);
			GLfloat v1 = j / float(dim - 1);

			GLfloat w2 = meshW * (i + 1) / float(dim - 1);
			GLfloat h2 = meshH * (j + 1) / float(dim - 1);
			GLfloat u2 = (i + 1) / float(dim - 1);
			GLfloat v2 = (j + 1) / float(dim - 1);

			GLfloat w3 = meshW * i / float(dim - 1);
			GLfloat h3 = meshH * (j + 1) / float(dim - 1);
			GLfloat u3 = i / float(dim - 1);
			GLfloat v3 = (j + 1) / float(dim - 1);

			glTexCoord2f(u0, v0);
			glVertex3f(w0, h, h0);
			glTexCoord2f(u1, v1);
			glVertex3f(w1, h, h1);
			glTexCoord2f(u2, v2);
			glVertex3f(w2, h, h2);
			glTexCoord2f(u3, v3);
			glVertex3f(w3, h, h3);
		}
	}
	glEnd();
	glPopMatrix();

}

//Funcao que permite desenhar a grelha para ser mais facilmente visualizada pelo utilizador.
//Através da tecla 'p' 'e possivel visualiza-a ou não.
void grelha(GLfloat meshW, GLfloat meshH, GLfloat h) {
	glPushMatrix();
	glNormal3f(0, 1, 0);          //normal 

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glBegin(GL_QUADS);
	for (int i = 0; i < dim - 1; i++) {
		for (int j = 0; j < dim - 1; j++) {
			GLfloat w0 = meshW * i / float(dim - 1);
			GLfloat h0 = meshH * j / float(dim - 1);
			GLfloat u0 = i / float(dim - 1);
			GLfloat v0 = j / float(dim - 1);

			GLfloat w1 = meshW * (i + 1) / float(dim - 1);
			GLfloat h1 = meshH * j / float(dim - 1);
			GLfloat u1 = (i + 1) / float(dim - 1);
			GLfloat v1 = j / float(dim - 1);

			GLfloat w2 = meshW * (i + 1) / float(dim - 1);
			GLfloat h2 = meshH * (j + 1) / float(dim - 1);
			GLfloat u2 = (i + 1) / float(dim - 1);
			GLfloat v2 = (j + 1) / float(dim - 1);

			GLfloat w3 = meshW * i / float(dim - 1);
			GLfloat h3 = meshH * (j + 1) / float(dim - 1);
			GLfloat u3 = i / float(dim - 1);
			GLfloat v3 = (j + 1) / float(dim - 1);

			glVertex3f(w0, h, h0);
			glVertex3f(w1, h, h1);
			glVertex3f(w2, h, h2);
			glVertex3f(w3, h, h3);
		}
	}
	glEnd();
	glPopMatrix();

}

//=================================================================== MATERIAIS =======================================================

//Funcao que permite auxilixar a definicao das propriedades dos materiais.
void define_material(float mat_ambient[], float mat_diffuse[], float mat_specular[]) {

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

}

//Funcao que permite mudar para o material pretendido através da variável 'material' passada
//por parametro.
void changeMaterial(int material) {
	if (material == 0) {
		float mat_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		float mat_diffuse[] = { 0.01f, 0.01f, 0.01f, 1.0f };
		float mat_specular[] = { 0.50f, 0.50f, 0.50f, 1.0f };
		float shine = 32.0f;
		define_material(mat_ambient, mat_diffuse, mat_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shine);
		//preto
	}

	if (material == 1) {
		float mat_ambient[] = { 0.19125f, 0.0735f, 0.0225f, 1.0f };
		float mat_diffuse[] = { 0.7038f, 0.27048f, 0.0828f, 1.0f };
		float mat_specular[] = { 0.256777f, 0.137622f, 0.086014f, 1.0f };
		float shine = 32.0f;
		define_material(mat_ambient, mat_diffuse, mat_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shine);
		//laranja
	}

	if (material == 2) {
		float mat_ambient[] = { 0.1745f, 0.01175f, 0.01175f, 1.0f };
		float mat_diffuse[] = { 0.61424f, 0.04136f, 0.04136f, 1.0f };
		float mat_specular[] = { 0.727811f, 0.626959f, 0.626959f, 1.0f};
		define_material(mat_ambient, mat_diffuse, mat_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, ks * 128);
		//vermelho
	}
	if (material == 3) {
		float mat_ambient[] = { 0.0f,0.1f,0.06f ,1.0f };
		float mat_diffuse[] = { 0.0f,0.50980392f,0.50980392f,1.0f };
		float mat_specular[] = { 0.50196078f,0.50196078f,0.50196078f,1.0f };
		float shine = 32.0f;
		define_material(mat_ambient, mat_diffuse, mat_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shine);
		//azul
	}

	if (material == 4) {
		float mat_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		float mat_diffuse[] = { 0.01f, 0.01f, 0.01f, 1.0f };
		float mat_specular[] = { 0.50f, 0.50f, 0.50f, 1.0f };
		float shine = 32.0f;
		define_material(mat_ambient, mat_diffuse, mat_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shine);
		//preto
	}
	if (material == 5) {
		float mat_ambient[] = { 0.19225f, 0.19225f, 0.19225f, 1.0f };
		float mat_diffuse[] = { 0.50754f, 0.50754f, 0.50754f, 1.0f };
		float mat_specular[] = { 0.508273f, 0.508273f, 0.508273f, 1.0f };
		float shine = 51.2f;
		define_material(mat_ambient, mat_diffuse, mat_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shine);
		//cinzento claro
	}
	if (material == 6) {
		float mat_ambient[] = { 0.0f,0.0f,0.0f,1.0f };
		float mat_diffuse[] = { 0.55f,0.55f,0.55f,1.0f };
		float mat_specular[] = { 0.70f,0.70f,0.70f,1.0f };
		float shine = 51.2f;
		define_material(mat_ambient, mat_diffuse, mat_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shine);
		//cinzento escuro
	}
	if (material == 7) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		float mat_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		float mat_diffuse[] = { 0.01f, 0.01f, 0.01f, .40f };
		float mat_specular[] = { 0.50f, 0.50f, 0.50f, 1.0f };
		float shine = 32.0f;
		define_material(mat_ambient, mat_diffuse, mat_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shine);
		//transparente
	}

	if (material == 8) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		float mat_ambient[] = { 0.05f,0.05f,0.05f,1.0f };
		float mat_diffuse[] = { 0.5f,0.5f,0.5f,1.0f };
		float mat_specular[] = { 0.7f,0.7f,0.7f,1.0f };
		float shine = 10.0f;
		define_material(mat_ambient, mat_diffuse, mat_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shine);
		//transparente utilizada no ecrã
	}

}

//==================================================================== ILUMINACAO ==================================================

//Funcao que permite modificar a intensidade da luz pontual.
void updateLuz() {
	localCorAmb[0] = luzR * intensidadeT;
	localCorAmb[1] = luzG * intensidadeT;
	localCorAmb[2] = luzB * intensidadeT;
	localCorDif[0] = luzR * intensidadeT;
	localCorDif[1] = luzG * intensidadeT;
	localCorDif[2] = luzB * intensidadeT;
	localCorEsp[0] = luzR * intensidadeT;
	localCorEsp[1] = luzG * intensidadeT;
	localCorEsp[2] = luzB * intensidadeT;
	glLightfv(GL_LIGHT0, GL_AMBIENT, localCorAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, localCorDif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, localCorEsp);
	glLightfv(GL_LIGHT0, GL_POSITION, localPos);
}

//Funcao que permite inicializar o foco com as duas devidas carateristicas.
void updateLuzFoco() {
	GLfloat Foco_direccao[] = { 0.0, -1.0, 0.0, 0.0 };
	GLfloat Foco1_cor[] = { 1, 1,  1, 1 };	
	GLfloat Foco_ak = 1.0;
	GLfloat Foco_al = 0.05f;
	GLfloat Foco_aq = 0.0f;
	GLfloat Foco_Expon = 0.5;		// Foco, SPOT_Exponent

	//Foco Esquerda
	glLightfv(GL_LIGHT1, GL_POSITION, Pos1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Foco1_cor);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, Foco_ak);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, Foco_al);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, Foco_aq);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, aberturaFoco);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, Foco_direccao);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, Foco_Expon);

}

//Funcao que permite inicializar as luzes utilizadas ambiente, luz pontual e foco.
void defineLuzes(){
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCorAmb);

	updateLuz();
	updateLuzFoco();
}

//==============================================================================================================================


//Funcao que permite inicializar os comandos laterais assim como o seu contorno.
void Laterais(int material) {
	glVertexPointer(3, GL_FLOAT, 0, vertices2);
	glNormalPointer(GL_FLOAT, 0, normais2);

	changeMaterial(material);

	glPolygonMode(GL_FRONT, GL_FILL);

	for (int i = 0; i < 6; i++) {
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, faces[i]);
	}

	changeMaterial(0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	for (int j = 0; j < 6; j++) {
		glBegin(GL_POLYGON);
		for (int i = 0; i < 4; i++) {
			glVertex3f(vertices2[12 * j + 3 * i], vertices2[12 * j + 3 * i + 1], vertices2[12 * j + 3 * i + 2]);
		}
		glEnd();
	}
}

//Funcao que permite definir o movimento dos 8 botoes (quando o mesmo é pressionado sobe automaticamente).
void movBotao(int index){
	if (flags[index] == true) {
		flags[index] = false;
		if (pos[index] - inc <= 0.24 && pos[index] - inc >= 0.1) {
			pos[index] -= inc;
			glutPostRedisplay();
		}
	}
	else {
		if (pos[index] + inc <= 0.24 && pos[index] + inc >= 0.1) {
			pos[index] += inc;
			glutPostRedisplay();
		}
	}
}

//Funcao que permite desenhar as diversas esferas utilizadas na Nitendo.
void drawSphere(int material) {
	changeMaterial(material);

	float radius = 1.0f;
	GLUquadricObj* quad = gluNewQuadric();

	gluQuadricDrawStyle(quad, GLU_FILL);
	gluQuadricNormals(quad, GLU_SMOOTH);
	gluQuadricTexture(quad, GL_TRUE);

	gluSphere(quad, radius, 400, 40);
	gluDeleteQuadric(quad);
}

//Funcao que permite desenhar o contorno de cada um dos cubos e paralelepipedos usados assim como a sua textura.
//Com base nos parametros flag_base e material é escolhida a textura pretendida.
void drawShape( GLint flag_base, int material, int foco=0) {
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glNormalPointer(GL_FLOAT, 0, normais);
	glTexCoordPointer(2, GL_FLOAT, 0, texturas);   // coordenadas textura

	//8->4     0->5     1->6     6->7

	changeMaterial(material);

	if (flag_base >= 1 && flag_base <= 7) {
		glEnable(GL_TEXTURE_2D);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	}

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	for (int i = 0; i < 6; i++) {
		if (flag_base == 1) {
			if (i == 3) {
				glBindTexture(GL_TEXTURE_2D, texture[0]);
			}
			else {
				glBindTexture(GL_TEXTURE_2D, texture[1]);
			}
		}
		else if (flag_base <= 5 && flag_base >= 2) {
			if (i == 2) {
				glBindTexture(GL_TEXTURE_2D, texture[flag_base]);
			}
			else {
				if (flag_base == 4 || flag_base == 5) {
					glBindTexture(GL_TEXTURE_2D, texture[6]);
				}
				else {
					glBindTexture(GL_TEXTURE_2D, texture[1]);
				}
			}
		}

		else {
			if (i == 2) {
				if (flag_base == 7) {
					glBindTexture(GL_TEXTURE_2D, texture[7]);
					changeMaterial(8);
					glPushMatrix();
						glShadeModel(GL_FLAT);
						glTranslatef(-0.8, 0, 0.8);
						glRotatef(90, 0, 1, 0);
						if (malha) {
							grelha(1.6, 1.6, 0.8);
						}
						drawMesh(1.6, 1.6, 0.8);
						glShadeModel(GL_SMOOTH);
					glPopMatrix();
				}
			}
			else {
				glBindTexture(GL_TEXTURE_2D, texture[6]);
			}

		}

		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, faces[i]);
	}

	if (flag_base >= 1 && flag_base <= 7) {
		glDisable(GL_TEXTURE_2D);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	changeMaterial(0);

	for (int j = 0; j < 6; j++) {
		glBegin(GL_POLYGON);
		for (int i = 0; i < 4; i++) {
			glVertex3f(vertices[12 * j + 3 * i], vertices[12 * j + 3 * i + 1], vertices[12 * j + 3 * i + 2]);
		}
		glEnd();
	}
}

//Funcao que permite desenhar os eixos.
void drawEixos(){
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo X
	glColor4f(RED);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(10, 0, 0);
	glEnd();
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo Y
	glColor4f(GREEN);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(0, 10, 0);
	glEnd();
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo Z
	glColor4f(BLUE);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(0, 0, 10);
	glEnd();
}


//Funcao que permite desenhar os dois joysticks.
//Chamada na funcao drawScene()
void drawAlavanca(GLfloat corx) {
	glPushMatrix();
		glTranslatef(corx, 0.16, 0.50);
		glScalef(0.1, 0.3, 0.1);
		drawShape(1, 4);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(corx, 0.50, 0.50);
		glScalef(0.2, 0.1, 0.2);
		drawSphere(1);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(corx, 0.10, 0.50);
		glScalef(0.18, 0.18, 0.18);
		drawSphere(0);
	glPopMatrix();
}

//Funcao utilizada para desenhar e definir o movimento do botão de ligar a Nitendo.
//Chamada na funcao drawScene()
void drawBotaoLigar() {
	glPushMatrix();
		if (flags[16] == false) {
			glTranslatef(0, 0.06, 0);
		}
		else {
			glTranslatef(0, -0.06, 0);
		}
		glTranslatef(2.78, 0.16, 1.0);
		glScalef(0.08, 0.08, 0.08);
		drawShape(6, 7);
	glPopMatrix();

	glDisable(GL_BLEND);
}

//Funcao utilizada para desenhar os 8 botões da Nitendo.
//Chamada na funcao drawScene()
void drawBotao(GLfloat corx1, GLfloat corx2, GLfloat corx3, GLfloat corx4, GLint flag, GLint flagView) {
	glPushMatrix();
		movBotao(0 + 4 * flag + 8 * flagView);
		glTranslatef(corx1, pos[0 + 4 * flag], -0.50);
		glScalef(0.15, 0.10, 0.15);
		if (flag == 0) {
			drawShape(2, 6);
		}
		else {
			drawShape(0, 6);
		}
	glPopMatrix();

	glPushMatrix();
		movBotao(1 + 4 * flag + 8 * flagView);
		glTranslatef(corx2, pos[1 + 4 * flag], -0.50);
		glScalef(0.15, 0.10, 0.15);
		if (flag == 0) {
			drawShape(3, 6);
		}
		else {
			drawShape(0, 6);
		}
	glPopMatrix();


	glPushMatrix();
		movBotao(2 + 4 * flag + 8 * flagView);
		glTranslatef(corx3, pos[2 + 4 * flag], -0.80);

		glScalef(0.15, 0.10, 0.15);
		if (flag == 0) {
			drawShape(4, 6);
		}
		else {
			drawShape(0, 0);
		}
	glPopMatrix();

	glPushMatrix();
		movBotao(3 + 4 * flag + 8 * flagView);
		glTranslatef(corx4, pos[3 + 4 * flag], -0.20);
		glScalef(0.15, 0.10, 0.15);
		if (flag == 0) {
			drawShape(5, 6);
		}
		else {
			drawShape(0, 0);
		}
	glPopMatrix();

}



void drawScene(GLint flagView) {
	//Desenha base
	//Desenhar laterais

	glPushMatrix();
		glPushMatrix();
			glTranslatef(-2.8, 0, 0);
			glScalef(0.5, 0.2, 1.75);
			glRotatef(180, 0, 1, 0);
			Laterais(3);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(2.8, 0, 0);
			glScalef(0.5, 0.2, 1.75);
			Laterais(2);
		glPopMatrix();
	glPopMatrix();

	//Desenhar o paralepipedo
	glPushMatrix();
		glScalef(3, 0.2, 1.75);
		drawShape(1, 5);
	glPopMatrix();

	//Desenhar ecrã
	GLint ecra;
	if (flagCor[0] == true) {
		ecra = 7;
		glutPostRedisplay();
	}
	else {
		ecra = 0;
		glutPostRedisplay();
	}
	glPushMatrix();
		glTranslatef(0, 0.16, 0);
		glScalef(2.9, 0.01, 1.66);
		drawShape( ecra, 0, 1);
	glPopMatrix();


	//Desenhar o joystick do lado direito
	glPushMatrix();
		glTranslatef(2.8, 0.10, 0.50);
		glRotatef(rotacaoDireita, 1, 0, 0);
		glRotatef(rotacaoDireita2, 0, 0, 1);
		glTranslatef(-2.8, -0.10, -0.50);
		drawAlavanca(2.8);
	glPopMatrix();

	//Desenhar o joystick do lado esquerdo
	glPushMatrix();
		glTranslatef(-2.8, 0.10, 0.50);
		glRotatef(rotacaoEsquerda, 1, 0, 0);
		glRotatef(rotacaoEsquerda2, 0, 0, 1);
		glTranslatef(2.8, -0.10, -0.50);
		drawAlavanca(-2.8);
	glPopMatrix();

	//Desenha botões lado direito
	drawBotao(2.975, 2.625, 2.8, 2.8, 0, flagView);

	//Desenha botões lado esquerdo
	drawBotao(-2.975, -2.625, -2.8, -2.8, 1, flagView);

	//Desenhar botão de ligar
	drawBotaoLigar();

	

}

//Permite definir e representar o observador
void drawObservador() {
	GLfloat tamO = 0.5;

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glPushMatrix();
	changeMaterial(1);
	glTranslatef(obsP[0] / 2.f, obsP[1] / 2.f, obsP[2] / 2.f);
	glBegin(GL_POLYGON);
	glVertex3f(-tamO, tamO, -tamO);
	glVertex3f(tamO, tamO, -tamO);
	glVertex3f(0, tamO, tamO);
	glEnd();
	glPopMatrix();

}


void display(void) {

	if (rodar == 1) {
		M++;
		N++;
		thetaV = M * PI / 180.f + 0.5 * PI;
		//phiV = N * PI / 180.f + 0.5 * PI;
		obsP[0] = rVisao * cos(thetaV) * sin(phiV);
		obsP[1] = rVisao * cos(phiV);
		obsP[2] = rVisao * sin(thetaV) * sin(phiV);
	}


//========================================================= Apaga ecrã e lida com profundidade (3D)==========================================

	defineLuzes();
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (on_off == 1) {
		glViewport(60, 80, wScreen / 1.1, hScreen / 1.1);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-4, 4, -3, 3, -4, 4);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(0, 4, 0, 0, 0, 0, 0, 0, -1);
		glPushMatrix();
		drawScene(0);
		glPopMatrix();



	}
	else {

		glViewport(0, 0, 0.25 * wScreen, 0.25 * hScreen);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-9, 9, -7, 7, -7, 7);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(0, 1, 0, 0, 0, 0, 0, 0, -1);

		glPushMatrix();
		drawObservador();
		drawScene(1);
		glPopMatrix();

		glViewport(0, 0, wScreen, hScreen);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(angZoom, (float)wScreen / hScreen, 0.1, 3 * zC);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(obsP[0], obsP[1], obsP[2], 0, 0, 0, 0, Y, 0);

	}

	drawScene(0);

	//Objetos
	drawEixos();


	//Atualizacao
	glutSwapBuffers();
}

void Timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(msec, Timer, 1);
}

//======================================================= EVENTOS ======================================================================
void keyboard(unsigned char key, int x, int y) {

	switch (key) {
		//Joystick do lado Direito
		//Para tras.
	case 's':
	case 'S':
		if (rotacaoDireita + inc_r <= 35 && rotacaoDireita + inc_r >= -35) {
			rotacaoDireita += inc_r;
			glutPostRedisplay();
		}
		break;

		//Para a frente.
	case 'w':
	case 'W':
		if (rotacaoDireita - inc_r <= 35 && rotacaoDireita - inc_r >= -35) {
			rotacaoDireita -= inc_r;
			glutPostRedisplay();
		}
		break;

		//Para a esquerda.
	case 'a':
	case 'A':
		if (rotacaoDireita2 + inc_r <= 35 && rotacaoDireita2 + inc_r >= -35) {
			rotacaoDireita2 += inc_r;
			glutPostRedisplay();
		}
		break;

		//Para a direita.
	case 'd':
	case 'D':
		if (rotacaoDireita2 - inc_r <= 35 && rotacaoDireita2 - inc_r >= -35) {
			rotacaoDireita2 -= inc_r;
			glutPostRedisplay();
		}
		break;

		//Joystick do lado Esquerdo
		//Andar para a frente.
	case 'c':
	case 'C':
		if (rotacaoEsquerda + inc_r <= 35 && rotacaoEsquerda + inc_r >= -35) {
			rotacaoEsquerda += inc_r;
			glutPostRedisplay();
		}
		break;

		//Andar para tras.
	case 'v':
	case 'V':
		if (rotacaoEsquerda - inc_r <= 35 && rotacaoEsquerda - inc_r >= -35) {
			rotacaoEsquerda -= inc_r;
			glutPostRedisplay();
		}
		break;

		//Andar para o lado Esquerdo.
	case 'b':
	case 'B':
		if (rotacaoEsquerda2 + inc_r <= 35 && rotacaoEsquerda2 + inc_r >= -35) {
			rotacaoEsquerda2 += inc_r;
			glutPostRedisplay();
		}
		break;

		//Andar para o lado Direito.
	case 'n':
	case 'N':
		if (rotacaoEsquerda2 - inc_r <= 35 && rotacaoEsquerda2 - inc_r >= -35) {
			rotacaoEsquerda2 -= inc_r;
			glutPostRedisplay();
		}
		break;

		//Botoes do lado Direito
		//Botao lado Direito.
	case 'h':
	case 'H':
		flags[0] = true;
		flags[8] = true;
		break;

		//Botao lado Esquerdo.
	case 'f':
	case 'F':
		flags[1] = true;
		flags[9] = true;
		break;

		//Botao cima.
	case 't':
	case 'T':
		flags[2] = true;
		flags[10] = true;
		break;

		//Botao baixo.
	case 'g':
	case 'G':
		flags[3] = true;
		flags[11] = true;
		break;

		//Botoes do lado Esquerdo
		//Botao lado esquerdo.
	case 'j':
	case 'J':
		flags[4] = true;
		flags[12] = true;
		break;

		//Botao lado direito.
	case 'l':
	case 'L':
		flags[5] = true;
		flags[13] = true;
		break;

		//Botao cima.
	case 'i':
	case 'I':
		flags[6] = true;
		flags[14] = true;
		break;

		//Botao baixo.
	case 'k':
	case 'K':
		flags[7] = true;
		flags[15] = true;
		break;

		//Botao ligar o ecra.
	case 'o':
	case 'O':
		on_off = -on_off;
		if (flags[16] == false) {
			flags[16] = true;
			flagCor[0] = true;
		}
		else {
			flags[16] = false;
			flagCor[0] = false;
		}
		break;


		//Permite efetuar a rotacao
	case 'r':
		rodar = -rodar;
		glutPostRedisplay();
		break;

		//Aumentar o zoom
	case 'z':
	case 'Z':
		if ((angZoom - incZoom) > 20) {
			angZoom -= incZoom;
			glutPostRedisplay();
		}
		break;

		//Diminuir o zoom
	case 'x':
	case 'X':
		if ((angZoom + incZoom < 183)) {
			angZoom += incZoom;
			glutPostRedisplay();
		}
		break;

		//Mover-se para a esquerda
	case 'q':
	case 'Q':
		centrox = centrox + 0.5;
		glutPostRedisplay();
		break;

		//Mover-se para a direita
	case 'e':
	case 'E':
		centrox = centrox - 0.5;
		glutPostRedisplay();
		break;

		//Ligar e desligar foco
	case '2':
		if (on_off==1) {
			Focos = !Focos;

			if (Focos)
				glEnable(GL_LIGHT1);

			else
				glDisable(GL_LIGHT1);
		}
		
		glutPostRedisplay();
		break;

		//Ligar e desligar luz do teto/pontual
	case '3':
		ligaTeto = !ligaTeto;
		if (ligaTeto)
			glEnable(GL_LIGHT0);

		else
			glDisable(GL_LIGHT0);
		glutPostRedisplay();
		break;

		//Mudar a intensidade da luz pontual/teto
	case '4':
		intensidadeT = intensidadeT + 0.1;
		if (intensidadeT > 1.1) intensidadeT = 0;
		glutPostRedisplay();
		break;

		//Mudar a cor da luz pontual/teto
	case '5':
		luzR = (GLint)(luzR + 1) % 2;
		glutPostRedisplay();
		break;
	case '6':
		luzG = (GLint)(luzG + 1) % 2;
		glutPostRedisplay();
		break;
	case '7':
		luzB = (GLint)(luzB + 1) % 2;
		glutPostRedisplay();
		break;

		//Aumentar a abertura do foco
	case '8':
		aberturaFoco = aberturaFoco + anguloINC;
		if (aberturaFoco > anguloMAX)
			aberturaFoco = anguloMAX;
		glutPostRedisplay();
		break;

		//Diminuir a abertura do foco
	case '9':
		aberturaFoco = aberturaFoco - anguloINC;
		if (aberturaFoco < anguloMIN)
			aberturaFoco = anguloMIN;
		glutPostRedisplay();
		break;
	
		//Aumentar o número de quadrados na malha
	case 'm':
	case 'M':
		dim++;
		if (dim > 256) dim = 256;
		glutPostRedisplay();
		break;

		//Diminuir o número de quadrados na malha
	case ' ':
		dim--;
		if (dim < 2) dim = 2;
		glutPostRedisplay();
		break;
	
		//Liga e desliga a malha
	case 'p':
	case 'P':
		malha = !malha;
		glutPostRedisplay();
		break;

		//Diminui o coeficiente de especularidade
	case '1': {
		if (ks > 0.05f)
			ks -= 0.05f;
		glutPostRedisplay();
		break;
        }

		//Aumenta o coeficiente de especularidade
    case 'u': {
		if (ks < 1.0f)
			ks += 0.05f;
		glutPostRedisplay();
		break;
        }
		//Escape
	case 27:
		exit(0);
		break;
	}

}


//O observador pode andar em torno do eixo do y (setas esquerda / direita)
//O observador pode andar em torno do eixo do x (setas cima / baixo )
void teclasNotAscii(int key, int x, int y) {

	if (key == GLUT_KEY_UP)
		N++;

	if (key == GLUT_KEY_DOWN)
		N--;

	if (key == GLUT_KEY_LEFT)
		M++;

	if (key == GLUT_KEY_RIGHT)
		M--;


	thetaV = M * PI / 180.f + 0.5 * PI;
	phiV = N * PI / 180.f + 0.5 * PI;


	if (phiV == 0) {
		phiV = 0.00002;
	}

	if (abs((int)N % 360) >= 0 && abs((int)N % 360) < 91) {
		Y = 1;
	}
	else if (abs((int)N % 360) >= 91 && abs((int)N % 360) < 181) {
		Y = -1;
	}

	else if (abs((int)N % 360) >= 181 && abs((int)N % 360) < 271) {
		Y = -1;
	}

	else if (abs((int)N % 360) >= 271 && abs((int)N % 360) < 360) {
		Y = 1;

	}

	obsP[0] = rVisao * cos(thetaV) * sin(phiV);
	obsP[1] = rVisao * cos(phiV);
	obsP[2] = rVisao * sin(thetaV) * sin(phiV);

	glutPostRedisplay();

}

//======================================================= MAIN =============================================================
int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(wScreen, hScreen);
	glutInitWindowPosition(300, 100);
	glutCreateWindow("inesmarcal@student.dei.uc.pt  |  Nitendo Switch");

	inicializa();

	glutSpecialFunc(teclasNotAscii);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(msec, Timer, 1);

	glutMainLoop();

	return 0;
}