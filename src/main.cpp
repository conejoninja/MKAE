/****************************************************************************
 *                                                                          *
 *                    #     #    #  #     ###     ####                      *
 *                    ##   ##    # #     #   #    #                         *
 *                    # # # #    ##      #####    ###                       *
 *                    #  #  #    # #     #   #    #                         *
 *                    #     #    #  #    #   #    #####                     *
 *                                                                          *
 *                         MIGHTY KICK-ASS ENGINE                           *
 *                                                                          *
 *                      MOTOR DE AVENTURAS GRAFICAS                         *
 *                 _CONEJO - http://www.theNinjaBunny.com/                  * 
 *   Se distibuye bajo la Licencia Privada del _CONEJO (LPVCv1) de la cual  *
 * debe de haber recibido una copia. El hecho de usar este software implica *
 *  la aceptación de dicha licencia. Por favor leala si no lo ha hecho aún  *
 *                                                                          * 
 *   ESTE SOFTWARE PERTENECE A 'LA ORGANIZACION' Y NO PUEDE SER UTILIZADO   * 
 *    POR NINGUNA OTRA ENTIDAD (UNITARIA O GRUPAL) PARA NINGUN FIN          * 
 *                                                                          * 
 *         USTED ES UN PRINGAO (por si aún no se lo habían dicho)           * 
 *                                                                          * 
 ****************************************************************************/



// ---Includes---
#include "CRM32Pro.h"
#ifdef _WINDOWS
 #include <windows.h>
#endif
#include "includes.h"
#include "GameView.h"
#include "Pathfinding.h"

// ---Prototypes---

// ---Defines---
#define EXAMPLE_VERSION "MKAE"
#define GFX_RESOURCE "data/gfx.dpf"     // DPF with graphic resources

// -------------MAIN FUNCTION----------------
int main(int argc,char *argv[])
{
   Uint8       done = 0;
   SDL_Event   event;
   Uint32      cCursor;     // Cursor ID 
            

  
   
	Controller::initController();
	Game::initGame();
   
   




	//****************************************************
	//**** LOAD RESOURCES MANUALLY ****
	//****************************************************
	





	MKAE_ROOM room;
	room.id = 1;


/*
	MKAE_VERTEX p;
	p.x = 0;
	p.y = 0;
	room.vertex.push_back(p);
	p.x = 640;
	p.y = 0;
	room.vertex.push_back(p);
	p.x = 640;
	p.y = 480;
	room.vertex.push_back(p);
	p.x = 0;
	p.y = 480;
	room.vertex.push_back(p);
	
	MKAE_BOX b;
	b.v1 = 0;
	b.v2 = 1;
	b.v3 = 2;
	b.v4 = 3;
	room.boxes.push_back(b);
*/



	MKAE_VERTEX p;
	p.x = 0;
	p.y = 404;
	p.scale = 50;
	room.vertex.push_back(p);
	p.x = 230;
	p.y = 336;
	p.scale = 100;
	room.vertex.push_back(p);
	p.x = 354;
	p.y = 373;
	p.scale = 100;
	room.vertex.push_back(p);
	p.x = 0;
	p.y = 480;
	p.scale = 100;
	room.vertex.push_back(p);
	p.x = 252;
	p.y = 252;
	p.scale = 100;
	room.vertex.push_back(p);
	p.x = 468;
	p.y = 281;
	p.scale = 100;
	room.vertex.push_back(p);
	p.x = 640;
	p.y = 314;
	p.scale = 200;
	room.vertex.push_back(p);
	p.x = 640;
	p.y = 406;
	p.scale = 100;
	room.vertex.push_back(p);

	
	MKAE_BOX b;
	b.v1 = 0;
	b.v2 = 1;
	b.v3 = 2;
	b.v4 = 3;
	room.boxes.push_back(b);

	b.v1 = 1;
	b.v2 = 4;
	b.v3 = 5;
	b.v4 = 2;
	room.boxes.push_back(b);

	b.v1 = 2;
	b.v2 = 5;
	b.v3 = 6;
	b.v4 = 7;
	room.boxes.push_back(b);
	
	room.numberBoxes = 3;
	room.matrix[0][0][0] = 0;
	room.matrix[0][0][1] = 0;
	room.matrix[0][1][0] = 1;
	room.matrix[0][1][1] = 1;
	room.matrix[0][2][0] = 2;
	room.matrix[0][2][1] = 1;
	room.matrix[1][0][0] = 1;
	room.matrix[1][0][1] = 0;
	room.matrix[1][1][0] = 0;
	room.matrix[1][1][1] = 1;
	room.matrix[1][2][0] = 1;
	room.matrix[1][2][1] = 2;
	room.matrix[2][0][0] = 2;
	room.matrix[2][0][1] = 1;
	room.matrix[2][1][0] = 1;
	room.matrix[2][1][1] = 1;
	room.matrix[2][2][0] = 0;
	room.matrix[2][2][1] = 2;
	
	


	
	GameView::loadRoom(room);
	
	









 
	Object ob;
	ob.id = 1;
	ob.setFilename((char*)("beer"));
	ob.img.width = 64;
	ob.img.height = 64;
	ob.setSize(64, 64);
	ob.setCenter(25,35);
	ob.setXY(200,400);
	ob.setRadius(20);
	ob.setAngle(60);
	ob.setScale(2.3);
	ob.setName("Cerveza");
	ob.setTextOfAction(0,"No puedo darle a la cerveza");
	ob.setTextOfAction(1,"Una cerveza no se abre");
	ob.setTextOfAction(2,"Una cerveza no se cierra");
	ob.setTextOfAction(3,"Mejor me la bebo");
	ob.setTextOfAction(4,"Hola, ¿que tal?");
	ob.setTextOfAction(5,"Es una cerveza, y esta llena");
	ob.setTextOfAction(6,"Ahora no, despues tengo que conducir");
	ob.setTextOfAction(7,"se podria caer");
	ob.setTextOfAction(8,"una cerveza NO se tira, NUNCA, JAMAS");
	ob.setTextOfAction(9,"Texto de IR A");
	ob.reg();
 

	ob.id = 2;
	ob.setFilename((char*)("beer"));
	ob.img.width = 64;
	ob.img.height = 64;
	ob.setSize(64, 64);
	ob.setCenter(25,35);
	ob.setXY(440,200);
	ob.setRadius(20);
	ob.setAngle(0);
	ob.setScale(1);
	ob.setName("Segunda Jarra");
	ob.setTextOfAction(0,"No puedo darle a la cerveza");
	ob.setTextOfAction(1,"Una cerveza no se abre");
	ob.setTextOfAction(2,"Una cerveza no se cierra");
	ob.setTextOfAction(3,"Mejor me la bebo");
	ob.setTextOfAction(4,"Hola, ¿que tal?");
	ob.setTextOfAction(5,"Es una cerveza, y esta llena");
	ob.setTextOfAction(6,"Ahora no, despues tengo que conducir");
	ob.setTextOfAction(7,"se podria caer");
	ob.setTextOfAction(8,"una cerveza NO se tira, NUNCA, JAMAS");
	ob.setTextOfAction(9,"Texto de IR A");
	ob.reg();

	
	
	
	
	
	
	Character gili;
	gili.id = 3;
	gili.setFilename((char*)("sito"));
	gili.img.width = 88;
	gili.img.height = 244;
	gili.setCenter(53, 232);
	gili.setAngle(0);
	gili.setScale(1);
	gili.destX = gili.destY = 300;
	gili.setXY(300,300);
	gili.setColorTalk(12);
	gili.setName("Sito");
	gili.setTextOfAction(0,"No puedo darme cosas a mi mismo");
	gili.setTextOfAction(1,"Eres un pervertido");
	gili.setTextOfAction(2,"Asi no podemos avanzar");
	gili.setTextOfAction(3,"Y me autoguardo en el bolsillo");
	gili.setTextOfAction(4,"No estoy tan loco como para hablar conmigo mismo");
	gili.setTextOfAction(5,"Hey! soy YO!");
	gili.setTextOfAction(6,"¿Me pretendes usar?");
	gili.setTextOfAction(7,"Yo tambien te quiero");
	gili.setTextOfAction(8,"No voy a tirarme");
	gili.setTextOfAction(9,"Texto de IR A");
	gili.reg();
	Game::setPlayer(3);

	Game::mainScroll.setCamera(&Game::characters[Game::giliID]);


	Controller::loadCrosshair((char*)("crosshair"));



	ICursor->Init();
	ICursor->Hide();





	MKAE_IMG fondo1;
	fondo1.filename = (char*)("fondo");
	fondo1.width = 640;
	fondo1.height = 480;
	GameView::setBackground(fondo1);
	
	
	GameView::loadFont((char*)("hola"));






	Game::addMsgQueue("esto es una prueba", 100, 100, 5000, 0);



   // -Main loop-
   done = 0;
   while(!done)
   {
   	
   	
   		
		Game::Frame();
		if(CRM32Pro.GetKeystate(SDLK_ESCAPE)) { done = 1; };
		
	}
	
	ICursor->Delete(cCursor);

	Game::EndGame();
	return 0;
}
