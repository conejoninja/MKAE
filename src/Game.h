#include "includes.h"
//#include <ulib/ulib.h>

#ifndef GAME_H_
#define GAME_H_




class Game {
           
	protected:
	
		static MKAE_MSG msgQueue[10];

                                   
	public:
		// GAME CONSTANTS
		static const char *GFX_RESOURCE;
		static const short DEBUG;
		
		
		
		
		static Scroll mainScroll;

		static std::string actionObj;


		static unsigned char action;
		static signed char k;
		static signed char tmpAction;
		static MKAE_PATH path;
		static Character *gili;
		static int giliID; 

		static std::vector<Object> objects;
		static std::vector<Character> characters;
		
		static bool setPlayer(int id);
		
		
		static MKAE_MSG* getMsgQueue();
		static void addMsgQueue(MKAE_MSG msg);
		static void addMsgQueue(std::string msg, int x, int y, int duration, int sender);
		

		Game();
		static void initGame();
		static void EndGame();
		static signed short checkObjects();
		static signed short checkCharacters();
		static void Frame();
		static void addObjectArray(Object* obj);
		~Game();
		 
};



#endif /*GAME_H_*/
