//#include "dataTypes.h"
#include "Controller.h"
#include "CRM32Pro.h"




#define MKAE_FPS		60 //unused
#define DBLCLICKTIME	21


MKAE_MOUSE Controller::mouse;


//ir_t Controller::ir;
MKAE_IMG Controller::crosshair;
short Controller::lastState = OVER;
bool Controller::semiClick = false;
signed char Controller::timeClick = 0;
bool Controller::clicks = false;
bool Controller::readed = true;
signed char Controller::timeDblClick = 0;


Controller::Controller() {

};


void Controller::initController() {

	/* WII
	PAD_Init();
	WPAD_Init();
	*/
		
	Controller::mouse.x = 300;
	Controller::mouse.y = 300;
	
	/* WII
	WPAD_SetDataFormat(0, WPAD_FMT_BTNS_ACC_IR);
	WPAD_SetVRes(0, 640, 480);
	*/	
	

	
	
	
	

};


void Controller::readData() {
	
	// Por defecto siempre sera OVER
	Controller::mouse.state = OVER;
	//bool touched = false;
	Controller::timeClick = (Controller::timeClick+1)%125;
	Controller::timeDblClick = (Controller::timeDblClick+1)%125;
	
	
	
	/* WII
	PAD_ScanPads();
	WPAD_ScanPads();
			
	
	
	Controller::mouse.x += 2*PAD_StickX(0)/abs(PAD_StickX(0));
	Controller::mouse.y -= 2*PAD_StickY(0)/abs(PAD_StickY(0));
	
	
	

	



	if ((PAD_ButtonsDown (0) & PAD_BUTTON_A) || (WPAD_ButtonsDown(0) & WPAD_BUTTON_A)){// || Controller::wiimoteData.buttonA){
		Controller::mouse.state = CLICK;
	} else if ((PAD_ButtonsDown (0) & PAD_BUTTON_B) || (WPAD_ButtonsDown(0) & WPAD_BUTTON_B)){// || Controller::wiimoteData.buttonB){
		Controller::mouse.state = DBLCLICK;
	} else {
		Controller::mouse.state = OVER;
	};
	
	if ((WPAD_ButtonsDown(0) & WPAD_BUTTON_1)) {
		WPAD_Rumble(0, 1);
	};
		
	if ((WPAD_ButtonsDown(0) & WPAD_BUTTON_2)) {
		WPAD_Rumble(0, 0);
	};

	if ((WPAD_ButtonsDown(0) & WPAD_BUTTON_PLUS)) {
		//Sound::fadeIn(2000);
		Game::characters[Game::giliID].setAngle(Game::characters[Game::giliID].getAngle()+10);
	};
		
	if ((WPAD_ButtonsDown(0) & WPAD_BUTTON_MINUS)) {
		//Sound::fadeOut(2000);
		Game::characters[Game::giliID].setAngle(Game::characters[Game::giliID].getAngle()-10);
	};
	
	
	if ((WPAD_ButtonsDown(0) & WPAD_BUTTON_UP)) {
		//char *cancion = "bso.ogg";
		//Sound::loadFile2(cancion);
		GRRLIB_ScrShot("Screenshot.png");
	};
		
		

	WPAD_IR(0, &Controller::ir);
	if(Controller::ir.valid==1) {
		Controller::mouse.x = int(Controller::ir.x);
		Controller::mouse.y = int(Controller::ir.y);
	};
	*/






	//Controlled by keyboard!!	
	//Controller::mouse.x += 2*PAD_StickX(0)/abs(PAD_StickX(0));
	//Controller::mouse.y -= 2*PAD_StickY(0)/abs(PAD_StickY(0));
	


	if (CRM32Pro.GetKeystate(SDLK_RETURN) || (CRM32Pro.mouse_buttons==CRM32PRO_BUTTON_LEFT)){// || Controller::wiimoteData.buttonA){
		Controller::mouse.state = CLICK;
	} else if (CRM32Pro.GetKeystate(SDLK_SPACE) || (CRM32Pro.mouse_buttons==CRM32PRO_BUTTON_RIGHT)){// || Controller::wiimoteData.buttonB){
		Controller::mouse.state = DBLCLICK;
	} else {
		Controller::mouse.state = OVER;
	};
		
	if (CRM32Pro.GetKeystate(SDLK_q)) {
		Game::action = GIVE;
	} else if (CRM32Pro.GetKeystate(SDLK_w)) {
		Game::action = PICKUP;
	} else if (CRM32Pro.GetKeystate(SDLK_e)) {
		Game::action = USE;
	} else if (CRM32Pro.GetKeystate(SDLK_a)) {
		Game::action = OPEN;
	} else if (CRM32Pro.GetKeystate(SDLK_s)) {
		Game::action = LOOKAT;
	} else if (CRM32Pro.GetKeystate(SDLK_d)) {
		Game::action = PUSH;
	} else if (CRM32Pro.GetKeystate(SDLK_z)) {
		Game::action = CLOSE;
	} else if (CRM32Pro.GetKeystate(SDLK_x)) {
		Game::action = TALK;
	} else if (CRM32Pro.GetKeystate(SDLK_c)) {
		Game::action = PULL;
	}
		

	Controller::mouse.x = CRM32Pro.mouse_x;
	Controller::mouse.y = CRM32Pro.mouse_y;





	



};

short Controller::getState() {
	return Controller::mouse.state;
};

MKAE_COORD Controller::getXY() {
	MKAE_COORD n;
	n.x = Controller::mouse.x;
	n.y = Controller::mouse.y;
	return n;
};

MKAE_MOUSE Controller::getMouse() {
	return Controller::mouse;
};


void Controller::loadCrosshair(const char *s) {
	
	Controller::crosshair.sprite = new CRM32Pro_CSprite();
	Controller::crosshair.sprite->Load((char*)(Game::GFX_RESOURCE),(char*)(s),(char*)("SPR2"));
	Controller::crosshair.sprite->AutoRestore(0);
	
};
















Controller::~Controller() {
	
};






