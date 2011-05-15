#include "includes.h"
#include "Object.h"
#include "Game.h"
#include "GameView.h"
#include "Character.h"



#define DAR			0
#define ABRIR		1
#define CERRAR		2
#define COGER		3
#define HABLAR		4
#define MIRAR		5
#define USAR		6
#define EMPUJAR		7
#define TIRAR		8
#define IR_A		9



// GAME CONSTANTS
const char *Game::GFX_RESOURCE = "data/gfx.dpf";
const short Game::DEBUG = 0;

std::string Game::actionObj = ""; 
signed char Game::k = 0;
unsigned char Game::action = IR_A;
signed char Game::tmpAction;
//Character g;
//Character &Game::gili = g;
Character* Game::gili;
int Game::giliID = 0;
MKAE_MSG Game::msgQueue[10];

Scroll Game::mainScroll;

//std::vector<Object*> Game::objs;
std::vector<Object> Game::objects;
std::vector<Character> Game::characters;
MKAE_PATH Game::path;




Game::Game() {
	
};

void Game::initGame() {
	
	
	// -Log system initialize-  
	ILogSystem.Init((char*)("MKAE_PC.log"),LOG_FILE,LOG_NORMAL, (char*)("MKAE_PC"));
 
	// -CRM32Pro and SDL initialize- 
	if(CRM32Pro.Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0) {
		ILogSystem.Msg(LOG_NORMAL,(char*)(" · [LOG] - Couldnt initialize CRM32Pro: %s\n"),SDL_GetError());
	}

	// -Desired config-
	CRM32Pro.Config.Title = (char*)("MKAE");
	CRM32Pro.Config.bMTFriendly = 1;

	
	
	
	
	MKAE_REGION R0;
	MKAE_REGION R1;

	R0.x0 = R0.y0 = 0;
	R1.x0 = R1.y0 = 100;
	R0.x1 = 640;
	R0.y1 = 480;
	R1.x1 = 540;
	R1.y1 = 380;
	
	Game::mainScroll.setRegions(R0, R1);
	
	GameView::initView();
	//Sound::initSound();
	//Sound::play();
	
	
	// -Time system initialize-
	ITimeSystem->Init();
	ITimeSystem->SetRate(0,20);  // Optional: desired Rendering and Logic Frame Rate

	
	
	
	
	
};



bool Game::setPlayer(int id) {
	
	int l = Game::characters.size();
	//l += Game::objects.size();
	for(int i = 0;i<l;i++) {
		if(Game::characters[i].id == id) {
			Game::giliID = i;
			//Game::gili = (Character*)(&Game::characters[i]);
			return true;
		}
	};
	
	return false;
	
};
void Game::Frame() {
	
	Controller::readData();
	GameView::draw();
	
	
	MKAE_MOUSE mouse;
	
	mouse = Controller::getMouse();
	
	MKAE_COORD cam = Game::characters[Game::giliID].getXY();
	MKAE_COORD sc = Game::mainScroll.getOffset();	
	
	// Por cosas como estas necesitamos tener una única lista U_U
	signed short obk = Game::checkObjects();
	if(obk!=-1) {
		Game::actionObj = Game::objects[obk].getName();
	} else {
		obk = Game::checkCharacters();
		if(obk!=-1) {
			Game::actionObj = Game::characters[obk].getName();
		} else {
			Game::actionObj = "";
		};
	};
	   
	

	if(mouse.state==1) {	
		
		
			
	
		tmpAction = Menu::checkMenu();
		if(tmpAction!=-1) {
	   		Game::action = tmpAction;
		} else {   
			obk = Game::checkObjects();
			if(obk!=-1) {
					Params p;
					if(Game::action==0) {
						p.push_back((void*)(&Game::objects[obk]));
						Game::characters[Game::giliID].addAction(GIVE,p);
					} else if(Game::action==1) {
						p.push_back((void*)(&Game::objects[obk]));
						Game::characters[Game::giliID].addAction(OPEN,p);
					} else if(Game::action==2) {
						p.push_back((void*)(&Game::objects[obk]));
						Game::characters[Game::giliID].addAction(CLOSE,p);
					} else if(Game::action==3) {
						p.push_back((void*)(&Game::objects[obk]));
						Game::characters[Game::giliID].addAction(PICKUP,p);
					} else if(Game::action==4) {
						p.push_back((void*)(&Game::objects[obk]));
						Game::characters[Game::giliID].addAction(TALK,p);
					} else if(Game::action==5) {
						p.push_back((void*)(&Game::objects[obk]));
						Game::characters[Game::giliID].addAction(LOOKAT,p);
					} else if(Game::action==6) {
						p.push_back((void*)(&Game::objects[obk]));
						Game::characters[Game::giliID].addAction(USE,p);
					} else if(Game::action==7) {
						p.push_back((void*)(&Game::objects[obk]));
						Game::characters[Game::giliID].addAction(PUSH,p);
					} else if(Game::action==8) {
						p.push_back((void*)(&Game::objects[obk]));
						Game::characters[Game::giliID].addAction(PULL,p);
					} else if(Game::action==9) {
						MKAE_COORD n;
						n = Game::objects[obk].getXY();
						p.push_back((void*)(n.x));
						p.push_back((void*)(n.y));
						Game::characters[Game::giliID].addAction(GOTO,p);
					};
			} else {
				obk = Game::checkCharacters();
				if(obk!=-1) {
					Params p;
					p.push_back((void*)(&Game::characters[obk]));
					if(Game::action==0) {
						Game::characters[Game::giliID].addAction(GIVE,p);
					} else if(Game::action==1) {
						Game::characters[Game::giliID].addAction(OPEN,p);
					} else if(Game::action==2) {
						Game::characters[Game::giliID].addAction(CLOSE,p);
					} else if(Game::action==3) {
						Game::characters[Game::giliID].addAction(PICKUP,p);
					} else if(Game::action==4) {
						Game::characters[Game::giliID].addAction(TALK,p);
					} else if(Game::action==5) {
						Game::characters[Game::giliID].addAction(LOOKAT,p);
					} else if(Game::action==6) {
						Game::characters[Game::giliID].addAction(USE,p);
					} else if(Game::action==7) {
						Game::characters[Game::giliID].addAction(PUSH,p);
					} else if(Game::action==8) {
						Game::characters[Game::giliID].addAction(PULL,p);
					} else if(Game::action==9) {
						MKAE_COORD n;
						n = Game::characters[obk].getXY();
						p.push_back((void*)(n.x));
						p.push_back((void*)(n.y));
						Game::characters[Game::giliID].addAction(GOTO,p);
					};
				} else {
					if(Game::action!=9) { //9 = GOTO Action
						Game::action = 9;
					} else {
						Params p;
						p.push_back((void*)(mouse.x-sc.x));
						p.push_back((void*)(mouse.y-sc.y));
						Game::characters[Game::giliID].resetActions();
						Game::characters[Game::giliID].addAction(GOTO, p);
					};
				};
			};	
		};
		
		
	} else if(mouse.state==2) {
		
		Game::characters[Game::giliID].setXY(mouse.x, mouse.y);		
		
	} else {
		
		
	};
	
	
	
	
	
	// Ejecutamos los frames en los objetos y personajes
	// cada uno tiene su propio ciclo
	int l = Game::objects.size();
	for(int k = 0;k<l;k++) {
		Game::objects[k].frame();
	};
	l = Game::characters.size();
	for(int k = 0;k<l;k++) {
		Game::characters[k].frame();
	};
	
	
	
	
	
	
	
	
	
	
	//Sound::frame(); //workaround for fadeIn fadeOut



	
	

	GameView::waitForFrame();
	
};



void Game::addObjectArray(Object* obj) {
	
	//Game::objects->push_back(obj);
	
};


signed short Game::checkObjects() {
	
	unsigned char l = Game::objects.size();
	
	//MKAE_MOUSE mouse = Controller::getMouse(); 
	MKAE_COORD n = Controller::getXY();
	
	for(unsigned char k = 0;k<l;k++) {
	
		// Perfect pixel collision
		// we have to solve or problem with vector of pointer/object
		if(MKAE_collisionPointObj(&Game::objects[k], n)) {
			return k;
		};


		// based on radius
		/*MKAE_COORD n = Game::objects[k]->getXY();
		if(MKAE_Distance(mouse.x,mouse.y,n.x,n.y)<(Game::objects[k]->getRadius()*Game::objects[k]->getRadius())) {
			return k;
		};*/
	};
	
	
	return -1;
	
};


signed short Game::checkCharacters() {
	
	unsigned char l = Game::characters.size();
	
	//MKAE_MOUSE mouse = Controller::getMouse(); 
	MKAE_COORD n = Controller::getXY();
	
	for(unsigned char k = 0;k<l;k++) {
		// Perfect pixel collision
		// we have to solve or problem with vector of pointer/object
		if(MKAE_collisionPointObj(&Game::characters[k], n)) {
			return k;
		};


		// based on radius
		/*MKAE_COORD n = Game::objects[k]->getXY();
		if(MKAE_Distance(mouse.x,mouse.y,n.x,n.y)<(Game::objects[k]->getRadius()*Game::objects[k]->getRadius())) {
			dreturn k;
		};*/
	};
	
	
	return -1;
	
};




MKAE_MSG* Game::getMsgQueue() {
	
	return Game::msgQueue;
	
};


void Game::addMsgQueue(MKAE_MSG msg) {
	
	for(int k=0;k<10;k++) {
		if(Game::msgQueue[k].msg=="") {
			Game::msgQueue[k].msg = msg.msg;
			Game::msgQueue[k].coord.x = msg.coord.x;
			Game::msgQueue[k].coord.y = msg.coord.y;
			Game::msgQueue[k].duration = msg.duration;
			Game::msgQueue[k].sender = msg.sender;

			// PC Version
			Game::msgQueue[k].startTime = ITimeSystem->GetTime();

		}
	};
	
};


void Game::addMsgQueue(std::string msg, int x, int y, int duration, int sender) {
	
	for(int k=0;k<10;k++) {
		if(Game::msgQueue[k].msg=="") {
			Game::msgQueue[k].msg = msg;
			Game::msgQueue[k].coord.x = x;
			Game::msgQueue[k].coord.y = y;
			Game::msgQueue[k].duration = duration;
			Game::msgQueue[k].sender = sender;

			// PC Version
			Game::msgQueue[k].startTime = ITimeSystem->GetTime();

		}
	};
	
};





void Game::EndGame() {
	// -Print useful information-
   ITimeSystem->Info();
   ICursor->Info();
   CRM32Pro.VideoInfo();

   // -Free resources and exit-
   CRM32Pro.Quit();
};


Game::~Game() {
	//END
};

