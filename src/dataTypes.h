#include "includes.h" //<ulib/ulib.h>


#include <vector>
#include <deque>
#include <string>


#ifndef DATATYPES_H_
#define DATATYPES_H_



int const MKAE_TRANSPARENT = 0xf81f;//0xf01e; //supuesto magenta = transparente


#define MAX_WIIMOTES				4

typedef struct MKAE_IMG {
	//WII
	unsigned char *image; //Cambiar el UL_IMAGE por la correspondiente de la plataforma
	//PC
	CRM32Pro_CSprite *sprite;
	int width;
	int height;
	int centerX;
	int centerY;
	int numFrames;
	bool loaded;
	bool *bitmap;	
	char *filename;
} MKAE_IMG;




typedef std::deque<void*> Params;




typedef struct MKAE_COORD {
	int x;
	int y;
} MKAE_COORD;


typedef struct MKAE_POLBOX {
	MKAE_COORD v1,v2,v3,v4;
} MKAE_POLBOX;

typedef struct MKAE_VERTEX {
	int x;
	int y;
	unsigned short scale;
} MKAE_VERTEX;

typedef struct MKAE_REGION {
	int x0;
	int y0;
	int x1;
	int y1;
} MKAE_REGION;

typedef struct MKAE_MOUSE {
	short state;
	int x;
	int y;
} MKAE_MOUSE;


typedef struct MKAE_OBJ {
	/*****Game Variables*****
	 * id : id del objeto
	 * useid : id del object con el que se usa
	 * catch : si se puede coger o no
	 * x,y : coord del objeto en la habitacion
	 ************************/
	unsigned short id, useid;
	bool coger;
	signed short x,y,radius;
	
	//Graphic variables
	int width,height;
	char *file;
	int pal;
} MKAE_OBJ;


typedef struct MKAE_BOX {
	int v1,v2,v3,v4;
} MKAE_BOX;


typedef struct MKAE_BCKGND {
	bool animate;
	int delay;
	char *file;
	int pal; //paleta de coores del fondo
} MKAE_BCKGND;

// Creamos un vector de MKAE_ROOM's y lo llenamos con los datos de un fichero
// Asi los guardamos en la memoria del juego, luego deben de ser utilizados por 
// el GameView para ponerlos a la vista.
typedef struct MKAE_ROOM {
	int id;
	std::vector<MKAE_OBJ> objects; 
	std::vector<MKAE_OBJ> characters; 
	MKAE_BCKGND background; 
	std::vector<MKAE_VERTEX> vertex;
	std::vector<MKAE_BOX> boxes;
	unsigned char numberBoxes;
	unsigned char matrix[20][20][2];
} MKAE_ROOM;

typedef struct MKAE_PATH {
	std::deque<MKAE_COORD> xy; 
} MKAE_PATH;

typedef struct MKAE_STRUCT1 {
	float dist;
	unsigned char nbox;
	//MKAE_COORD n;
} MKAE_STRUCT1;

typedef struct MKAE_STRUCT2 {
	float dist;
	MKAE_COORD n;
} MKAE_STRUCT2;



typedef struct MKAE_WIIMOTE {
	unsigned long irx;
	unsigned long iry;
	bool buttonA;
	bool buttonB;
	float fx;
	float fy;
	float fz;
} MKAE_WIIMOTE;


typedef struct MKAE_MSG {
	
	std::string msg;
	MKAE_COORD coord;
	int startTime;
	int duration;
	int sender;
	
} MKAE_MSG;




typedef enum
{
	GIVE = 0,
	OPEN,
	CLOSE,
	PICKUP,
	TALK,
	LOOKAT,
	USE,
	PUSH,
	PULL,
	GOTO,
	WALKING,
	IDLE,
	SCRIPT
  
} ACTION;






typedef struct MKAE_ACTION {
	ACTION action;
	Params p;
} MKAE_ACTION;


typedef std::deque<MKAE_ACTION> MKAE_SCRIPT;













/*
#define PAL32		UL_PF_PAL5_A3;
#define PAL4		UL_PF_PAL2;
#define PAL16		UL_PF_PAL4;
#define PAL256		UL_PF_PAL8;
#define PAL8		UL_PF_PAL5_A5;
#define PAL16b		UL_PF_5551;
#define PAL15b		UL_PF_5550;
#define PAL16bit	UL_PF_5551;
#define PAL15bit	UL_PF_5550;*/


#endif /*DATATYPES_H_*/
