#include "includes.h"
#include "Shape.h"
#include <vector>

#ifndef GAMEVIEW_H_
#define GAMEVIEW_H_



class GameView {
           
	private:
		static std::vector<Shape*> sprites;
		static std::vector<Shape> sp;
		static std::vector<Shape*> shapes;
		static MKAE_IMG background;
		static Object temp;
		
		static CRM32Pro_CFont *letras;

		

                                   
	public:
		static unsigned char *text_font1;
		static MKAE_COORD scrollXY;
		static MKAE_ROOM room;
		
		static int charTalkingTime;
		static Character *charac;
		static char scharac[50];
		static std::string schar;

		GameView();
		static void clearScreen();
		static void waitForFrame();
		static void initView();
		static void drawSprites();
		

		static bool loadRoom(MKAE_ROOM room);
		static void drawActionLine();
		static void drawMsgQueue();
		static void draw();
		static void drawPoint(MKAE_COORD n);
		static void drawBoxes();
		
		static void charSay(Character *charac, std::string talk);
		static void charTalking(Character *charac, std::string talk);
		
		static MKAE_IMG loadImage(char *s, int pal);
		static void drawImage(MKAE_IMG img, MKAE_COORD n);
		static void drawBackground(MKAE_IMG img);
		static void drawCrosshair();
		static void drawMenu();
		static void setBackground(MKAE_IMG img);
		static MKAE_COORD getBackgroundSize();
		static void clean();
		
		static void loadFont(char *s);
		static void write(int x, int y, char *s);
		

		
		
		~GameView();
		 
};

#endif