#include "includes.h"
#include "Menu.h"
#include "GameView.h"

//UL_IMAGE *Menu::boton;
unsigned short *Menu::b1;
unsigned short *Menu::b2;
unsigned short *Menu::b3;
unsigned short *Menu::b4;
unsigned short *Menu::b5;
unsigned short *Menu::b6;
unsigned short *Menu::b7;
unsigned short *Menu::b8;
unsigned short *Menu::b9;
Menu::Menu() {
	
};


void Menu::loadImages() {
//	Menu::boton =  ulLoadImageFileGIF("boton.gif", 0, UL_IN_VRAM, UL_PF_PAL4);
	/*Menu::b1 =  menu_abrir_img;
	Menu::b2 =  menu_coger_img;
	Menu::b3 =  menu_usar_img;
	Menu::b4 =  menu_abrir_img;
	Menu::b5 =  menu_hablar_img;
	Menu::b6 =  menu_empujar_img;
	Menu::b7 =  menu_cerrar_img;
	Menu::b8 =  menu_mirar_img;
	Menu::b9 =  menu_tirar_img;*/
	
	/*
	
	
	Menu::b1->x = 5;
	Menu::b1->y = 148;
	Menu::b2->x = 40;
	Menu::b2->y = 148;
	Menu::b3->x = 75;
	Menu::b3->y = 148;
	Menu::b4->x = 5;
	Menu::b4->y = 148+15;
	Menu::b5->x = 40;
	Menu::b5->y = 148+15;
	Menu::b6->x = 75;
	Menu::b6->y = 148+15;
	Menu::b7->x = 5;
	Menu::b7->y = 178;
	Menu::b8->x = 40;
	Menu::b8->y = 178;
	Menu::b9->x = 75;
	Menu::b9->y = 178;
	*/
	
	
	
};




signed char Menu::checkMenu() {
	
	
	MKAE_MOUSE mouse;
	mouse = Controller::getMouse();
	
	signed char state = -1;
	unsigned short baseX = 400;
	unsigned short baseY = 330;
	unsigned char w = 70;
	unsigned char h = 40;
	unsigned char space = 10;
	
	if(mouse.x>baseX && mouse.x<baseX+w) {
		state = 0;
	} else if(mouse.x>baseX+w+space && mouse.x<baseX+2*w+space) {
		state = 3;
	} else if(mouse.x>baseX+2*w+2*space && mouse.x<baseX+3*w+2*space) {
		state = 6;
	} else {
		return -1;
	};		
	
	if(mouse.y>baseY && mouse.y<baseY+h) {
		state += 0;
	} else if(mouse.y>baseY+h+space && mouse.y<baseY+2*h+space) {
		state += 1;
	} else if(mouse.y>baseY+2*h+2*space && mouse.y<baseY+3*h+2*space) {
		state += 2;
	} else {
		return -1;
	};		
	
	
	return state;
};









void Menu::draw() {


		/*ulDrawImage(Menu::b1);
		ulDrawImage(Menu::b2);
		ulDrawImage(Menu::b3);
		ulDrawImage(Menu::b4);
		ulDrawImage(Menu::b5);
		ulDrawImage(Menu::b6);
		ulDrawImage(Menu::b7);
		ulDrawImage(Menu::b8);
		ulDrawImage(Menu::b9);*/


};

Menu::~Menu() {
	//printf("Ya no hay Shape");
};

