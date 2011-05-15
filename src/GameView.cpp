#include "GameView.h"
#include "includes.h"





MKAE_COORD scrollXY;
MKAE_IMG GameView::background;
MKAE_ROOM GameView::room;
Object GameView::temp;
Character *GameView::charac;// = Game::gili;
char GameView::scharac[50];
std::string GameView::schar;
int GameView::charTalkingTime = 0;
unsigned char *GameView::text_font1;
//SDL_Surface*GameView::backgroundPC;

CRM32Pro_CFont *GameView::letras;




GameView::GameView() {

	// WII Version
	//VIDEO_Init();
    //GRRLIB_InitVideo();
    //GRRLIB_Start();
    
    // PC Version
	// -Graphics system initialize-  
	if(!CRM32Pro.SetVideoMode()) {
		CRM32Pro.Quit();
	}




};


void GameView::initView() {

	/* WII Version
	VIDEO_Init();
    GRRLIB_InitVideo();
    GRRLIB_Start();
    GameView::text_font1 = GRRLIB_LoadTexture(GRRLIB_font1);
	*/
	
	// PC Version
	// -Graphics system initialize-  
	if(!CRM32Pro.SetVideoMode()) {
		CRM32Pro.Quit();
	}

	
	
	
	
};


// Controlamos ambas librerias al tiempo
void GameView::waitForFrame() {

	// WII Version
	//GRRLIB_Render();
	
	// PC Version
	// Main system update and events loop
	while(CRM32Pro.Update());

	

};


void GameView::drawSprites() {
	
	//solucion temporal, el scroll deberia de ir en Game::scroll
	MKAE_REGION r = Game::mainScroll.getR0();
	/*r.x0 = 0;
	r.y0 = 0;
	r.x1 = 640;
	r.y1 = 480;*/
	
	MKAE_COORD cam = Game::characters[Game::giliID].getXY();
	MKAE_COORD sc = Game::mainScroll.getOffset(cam);
	sc.x = 0;
	sc.y = 0;
	int l;
	
	l = Game::objects.size();//GameView::sprites.size();
	
	for(int k = 0;k<l;k++) {
		// Draw it directly
		//I think it consume less CPU

		
		MKAE_COORD n = Game::objects[k].getXY();
		float scale = Game::objects[k].getScale();
		float angle = Game::objects[k].getAngle();


		int centroW = (scale*Game::objects[k].img.width-Game::objects[k].img.width)/2;
		int centroH = (scale*Game::objects[k].img.height-Game::objects[k].img.height)/2;
		MKAE_COORD m = MKAE_calculateCoord(&Game::objects[k], n, scale, angle);


		/* WII Version
		GRRLIB_DrawImg(n.x+m.x+centroW-Game::objects[k].img.centerX*scale, n.y+m.y+centroH-Game::objects[k].img.centerY*scale, Game::objects[k].img.width, Game::objects[k].img.height, Game::objects[k].img.image, angle, scale, scale, 255);
		*/ 
		
		// PC Version
		Game::objects[k].img.sprite->SetEffect(SPREFFECT_ROTATERESIZE, 1, -angle, scale);
		Game::objects[k].img.sprite->SetPosition(n.x+m.x+centroW-Game::objects[k].img.centerX*scale, n.y+m.y+centroH-Game::objects[k].img.centerY*scale,1);
		Game::objects[k].img.sprite->Draw();
		
		
		
		//More OOP-like (i think its more time-consuming)
		//GameView::sprites[k]->draw();
	};
	
	
	l = Game::characters.size();
	
	for(int k = 0;k<l;k++) {

		MKAE_COORD n = Game::characters[k].getXY();
		float scale = Game::characters[k].getScale();
		float angle = Game::characters[k].getAngle();
		

		int centroW = (scale*Game::characters[k].img.width-Game::characters[k].img.width)/2;
		int centroH = (scale*Game::characters[k].img.height-Game::characters[k].img.height)/2;
		MKAE_COORD m = MKAE_calculateCoord(&Game::characters[k], n, scale, angle);
		
		/* WII Version		
		//GRRLIB_DrawImg(n.x+m.x+centroW-Game::characters[k].img.centerX*scale, n.y+m.y+centroH-Game::characters[k].img.centerY*scale, Game::characters[k].img.width, Game::characters[k].img.height, Game::characters[k].img.image, angle, scale, scale, 255); 
		//GRRLIB_DrawImg(sc.x+n.x+centroW-(int)(Game::characters[k].img.centerX*scale), sc.y+n.y+centroH-(int)(Game::characters[k].img.centerY*scale), Game::characters[k].img.width, Game::characters[k].img.height, Game::characters[k].img.image, angle, scale, scale, 255);
		*/
		
		// PC Version 
		Game::characters[k].img.sprite->SetEffect(SPREFFECT_ROTATERESIZE, 1, angle, scale);
		Game::characters[k].img.sprite->SetPosition(sc.x+n.x+centroW-(int)(Game::characters[k].img.centerX*scale), sc.y+n.y+centroH-(int)(Game::characters[k].img.centerY*scale), 1);
		Game::characters[k].img.sprite->Draw();
		
		
		

	};
	
	
};
	
	





bool GameView::loadRoom(MKAE_ROOM roomm) {
	
	GameView::room = roomm;
	//GameView::background = GameView::loadImage(room.background.file,room.background.pal);
	//if(GameView::background.image) {
		int l = GameView::room.objects.size();
		if(l) {
			for(int k = 0;k<l;k++) {
//				GameView::sprites[k] = new Object(); 
//				GameView::sprites[k]->loadImage("james.gif",UL_PF_PAL4);
//				GameView::sprites[k]->setXY(k*20,k*20);
			};
		};
		
		


	
		return true;
	//} else {
	//	return false;
	//};	
	
};






void GameView::draw() {
	
	
	GameView::drawBackground(GameView::background);
	GameView::drawSprites();
	GameView::drawBoxes();		
	GameView::drawActionLine();
	GameView::drawMsgQueue();
	GameView::drawCrosshair();
	
			
};


void GameView::drawPoint(MKAE_COORD n) {


	/*GRRLIB_PutPixel( n.x, n.y, 0xF800);
	GRRLIB_PutPixel( n.x+1, n.y, 0xF800);
	GRRLIB_PutPixel( n.x+1, n.y+1, 0xF800);
	GRRLIB_PutPixel( n.x, n.y+1, 0xF800);*/

};

void GameView::drawBoxes() {
	
	int l = GameView::room.boxes.size();
	MKAE_BOX box;
	
	if(l) {
		for(int k = 0;k<l;k++) {
			box = GameView::room.boxes[k];
			
			// WII Version
			/*GRRLIB_Line(GameView::room.vertex[box.v1].x,GameView::room.vertex[box.v1].y,GameView::room.vertex[box.v2].x,GameView::room.vertex[box.v2].y,0xF800);
			GRRLIB_Line(GameView::room.vertex[box.v2].x,GameView::room.vertex[box.v2].y,GameView::room.vertex[box.v3].x,GameView::room.vertex[box.v3].y,0xF800);
			GRRLIB_Line(GameView::room.vertex[box.v3].x,GameView::room.vertex[box.v3].y,GameView::room.vertex[box.v4].x,GameView::room.vertex[box.v4].y,0xF800);
			GRRLIB_Line(GameView::room.vertex[box.v4].x,GameView::room.vertex[box.v4].y,GameView::room.vertex[box.v1].x,GameView::room.vertex[box.v1].y,0xF800);*/
			
			// PC Version
			IPrimitives->LineColor(CRM32Pro.screen, GameView::room.vertex[box.v1].x,GameView::room.vertex[box.v1].y,GameView::room.vertex[box.v2].x,GameView::room.vertex[box.v2].y,0xF800);	 
			IPrimitives->LineColor(CRM32Pro.screen, GameView::room.vertex[box.v2].x,GameView::room.vertex[box.v2].y,GameView::room.vertex[box.v3].x,GameView::room.vertex[box.v3].y,0xF800);	 
			IPrimitives->LineColor(CRM32Pro.screen, GameView::room.vertex[box.v3].x,GameView::room.vertex[box.v3].y,GameView::room.vertex[box.v4].x,GameView::room.vertex[box.v4].y,0xF800);	 
			IPrimitives->LineColor(CRM32Pro.screen, GameView::room.vertex[box.v4].x,GameView::room.vertex[box.v4].y,GameView::room.vertex[box.v1].x,GameView::room.vertex[box.v1].y,0xF800);	 
			
			
		};
	};
	


	
};



void GameView::drawMsgQueue() {


	int time = ITimeSystem->GetTime();
	MKAE_MSG* queue = Game::getMsgQueue();
	for(int k=0; k<10;k++) {
		
		if(queue[k].msg!="" && (queue[k].startTime+queue[k].duration)>time) {
			
			// PC Version
			// We could use gameview::write but we need to change the font according to the sender
			GameView::letras->PutString(CRM32Pro.screen, queue[k].coord.x, queue[k].coord.y, (char*)(queue[k].msg.c_str()));
				
		} else {
			queue[k].msg = "";
		};
		
	};

};







void GameView::setBackground(MKAE_IMG img) {


	// WII Version
	//GameView::background = img; 

	// PC Version
	//GameView::backgroundPC = IImage->Load((char*)(Game::GFX_RESOURCE),(char*)(img.filename));
	//SDL_BlitSurface(GameView::backgroundPC,NULL,CRM32Pro.screen,NULL);
	GameView::background.sprite = new CRM32Pro_CSprite();
	GameView::background.sprite->Load((char*)(Game::GFX_RESOURCE),(char*)(img.filename),(char*)("SPR2"));
	GameView::background.sprite->AutoRestore(0);

	GameView::background.width = img.width;
	GameView::background.height = img.height;

};
































void GameView::drawActionLine() {
	
	std::string cadena;
	
	switch(Game::action) {
		case 0 : 
			cadena = "DAR ";
		break;
		case 1 : 
			cadena = "ABRIR ";
		break;
		case 2 : 
			cadena = "CERRAR ";
		break;
		case 3 : 
			cadena = "COGER ";
		break;
		case 4 : 
			cadena = "HABLAR A ";
		break;
		case 5 : 
			cadena = "MIRAR ";
		break;
		case 6 : 
			cadena = "USAR ";
		break;
		case 7 : 
			cadena = "EMPUJAR ";
		break;
		case 8 : 
			cadena = "TIRAR ";
		break;
		case 9 :
			cadena = "IR A ";
		break;
		default : 
			cadena = "IR A ";
		break;
	};
	
	
	
	cadena += Game::actionObj;
	char *cadenaChar = (char*)cadena.c_str();
	GameView::write(0, 0, cadenaChar);
	
	
};





void GameView::charSay(Character * charac, std::string talk) {

	

	
	char *cadenaChar = (char*)talk.c_str();
	GameView::write(100, 100, cadenaChar);
	
	GameView::charTalkingTime = 400;
	GameView::charac = charac;
	GameView::schar = talk;

	
};

void GameView::charTalking(Character * charac, std::string talk) {
	

	char *cadenaChar = (char*)talk.c_str();
	GameView::write(100, 100, cadenaChar);
	
};





/*************************************************************
 *                                                           *
 *         TOP-NOTCH DE LAS FUNCIONES DE DIBUJADO            *
 *                                                           *
 ************************************************************/

MKAE_IMG GameView::loadImage(char *s, int pal) {
	MKAE_IMG n;
	//n.image =  ulLoadImageFileGIF(s, 0, UL_IN_VRAM, pal);
	return n;
};

void GameView::drawImage(MKAE_IMG img, MKAE_COORD n) {

	// WII VERSION wiiiiiiiiiiiiiII!!!!
	//GRRLIB_DrawImg(n.x-img.centerX, n.y-img.centerY, img.width, img.height, img.image, 0, 1, 1, 255);
	
	// PC VERSION
	img.sprite->SetPosition(n.x,n.y,1);
	img.sprite->Draw();
	 

};

void GameView::drawBackground(MKAE_IMG img) {

	MKAE_COORD cam = Game::characters[Game::giliID].getXY();
	MKAE_COORD sc = Game::mainScroll.getOffset(cam);
	
	// WII Version
	//GRRLIB_DrawImg(144, 176, 352, 128, img.image, 0, 1, 1, 255 );
	//GRRLIB_DrawImg(sc.x, sc.y, img.width, img.height, img.image, 0, 1, 1, 255);
	
	// PC Version
	//SDL_BlitSurface(GameView::backgroundPC, NULL, CRM32Pro.screen, NULL);
	GameView::background.sprite->SetPosition(sc.x,sc.y,1);
	GameView::background.sprite->Draw();
	
	 

};

MKAE_COORD GameView::getBackgroundSize() {
	MKAE_COORD n;
	n.x = GameView::background.width;
	n.y = GameView::background.height;
	return n;
};

void GameView::drawMenu() {

	//GRRLIB_DrawImg(0, 0, img.width, img.height, img.image, 0, 1); 
	/*GRRLIB_DrawImg(400, 330, 70, 40, menu_dar_img, 0, 1); 
	GRRLIB_DrawImg(480, 330, 70, 40, menu_coger_img, 0, 1); 
	GRRLIB_DrawImg(560, 330, 70, 40, menu_usar_img, 0, 1); 
	GRRLIB_DrawImg(400, 380, 70, 40, menu_abrir_img, 0, 1); 
	GRRLIB_DrawImg(480, 380, 70, 40, menu_hablar_img, 0, 1); 
	GRRLIB_DrawImg(560, 380, 70, 40, menu_empujar_img, 0, 1); 
	GRRLIB_DrawImg(400, 430, 70, 40, menu_cerrar_img, 0, 1); 
	GRRLIB_DrawImg(480, 430, 70, 40, menu_mirar_img, 0, 1); 
	GRRLIB_DrawImg(560, 430, 70, 40, menu_tirar_img, 0, 1);*/ 

};

void GameView::drawCrosshair() {

	MKAE_COORD n = Controller::getXY();
	
	// WII Version
	//GRRLIB_DrawImg(n.x-Controller::crosshair.centerX, n.y-Controller::crosshair.centerY, Controller::crosshair.width, Controller::crosshair.height, Controller::crosshair.image, 0, 1, 1, 255); 

	// PC VERSION
	Controller::crosshair.sprite->SetPosition(n.x,n.y,1);
	Controller::crosshair.sprite->Draw();



};

void GameView::clearScreen() {
	
	//GRRLIB_FillScreen(0xFF000000);
};

void GameView::clean() {
	
	

};


void GameView::loadFont(char *s) {
	
	// PC Version
	//GameView::fondoletras = IImage->Load((char*)(Game::GFX_RESOURCE),(char*)("fondoletras2"));
	GameView::letras = new CRM32Pro_CFont();
	GameView::letras->Load((char*)(Game::GFX_RESOURCE),(char*)("MyFont"));
	
	
};


void GameView::write(int x, int y, char *s) {
	
	// PC Version
	GameView::letras->PutString(CRM32Pro.screen, x, y, (char*)(s));	
	
};




GameView::~GameView() {
	
};





