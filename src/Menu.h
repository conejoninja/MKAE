#include "includes.h"


#ifndef MENU_H_
#define MENU_H_



class Menu {
           
	private:
		static unsigned char *boton;
		static unsigned short *b1;
		static unsigned short *b2;
		static unsigned short *b3;
		static unsigned short *b4;
		static unsigned short *b5;
		static unsigned short *b6;
		static unsigned short *b7;
		static unsigned short *b8;
		static unsigned short *b9;
                                   
	public:

		Menu();
		static void draw();
		static void loadImages();
		static signed char checkMenu();
		~Menu();

		 
};


#endif /*MENU_H_*/
