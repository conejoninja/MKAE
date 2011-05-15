#include "includes.h"
#include "Scroll.h"
#include "GameView.h"

#define NREPEAT		0 //Sin repetir
#define HREPEAT		1 //Se repite horizontalmente
#define VREPEAT		2 //Se repite en vertical
#define DREPEAT		3 //Se repite en todos lados



Scroll::Scroll() {

};

void Scroll::setRegions(MKAE_REGION rr, MKAE_REGION rs) {

	this->R0 = rr;
	this->R1 = rs;
	this->x = 0;
	this->y = 0;
	this->dx = 0;
	this->dy = 0;
	this->active = true;
	this->moveEasing = 0;
	this->scrollMode = NREPEAT;

};




MKAE_COORD Scroll::getOffset(MKAE_COORD camera) {
	
	MKAE_COORD map = GameView::getBackgroundSize();
	//Game::characters[Game::giliID].say(MKAE_int2str(camera.x)+" - "+MKAE_int2str(camera.y)+" - "+MKAE_int2str(this->R1.x1)+" - "+MKAE_int2str(this->x));
	
	
	if(this->active) {
		// RIGTH MOVEMENT
		if(this->x+camera.x>this->R1.x1 ) {
			this->dx = -camera.x+this->R1.x1;
			if((this->dx-this->R0.x0)<-(map.x-this->R0Width())  && (this->scrollMode==0  || this->scrollMode==2 || this->scrollMode==3)) {
				this->dx = this->R0.x0-(map.x-this->R0Width());
			};
		};
		
		// LEFT MOVEMENT
		if(this->x+camera.x<this->R1.x0) {
		this->dx = -camera.x+this->R1.x0;
			if((this->dx-this->R0.x0)>0  && (this->scrollMode==0  || this->scrollMode==2 || this->scrollMode==3)) {
				this->dx = this->R0.x0;
			};
		};
	//};
	//if(getVDir()) {
		// DOWN MOVEMENT		
		if(this->y+camera.y>this->R1.y1) {
			this->dy = -camera.y+this->R1.y1;
			if((this->dy-this->R0.y0)<-(map.y-this->R0Height())  && (this->scrollMode==0  || this->scrollMode==1 || this->scrollMode==3)) {
				this->dy = this->R0.y0-(map.y-this->R0Height());
			};
		};
	
	
		// UPPERMOVEMENT
		if(this->y+camera.y<this->R1.y0) {
			//C.log("Me muevo arriba");
			this->dy = -camera.y+this->R1.y0;
			if((this->dy-this->R0.y0)>0  && (this->scrollMode==0  || this->scrollMode==1 || this->scrollMode==3)) {
				this->dy = this->R0.y0;
			};
		};
	//};
			
		if(this->moveEasing<=1) {
			this->x = this->dx;
			this->y = this->dy;
		} else {
			this->x += (this->dx-this->x)/this->moveEasing;
			this->y += (this->dy-this->y)/this->moveEasing;
		};
			
	
	};
	MKAE_COORD n;
	n.x = this->x;
	n.y = this->y;
	return n;
	
};

MKAE_COORD Scroll::getOffset() {
	
	MKAE_COORD n = this->camera->getXY();
	return this->getOffset(n);
	
};




MKAE_COORD Scroll::centerScroll(MKAE_COORD n) {
	
	
	return n;
	
};



unsigned short Scroll::R0Width() {
	return this->R0.x1-this->R0.x0;
};

unsigned short Scroll::R0Height() {
	return this->R0.y1-this->R0.y0;
};

unsigned short Scroll::R1Width() {
	return this->R1.x1-this->R1.x0;
};

unsigned short Scroll::R1Height() {
	return this->R1.y1-this->R1.y0;
};


MKAE_REGION Scroll::getR0() {
	return this->R0;
};

MKAE_REGION Scroll::getR1() {
	return this->R1;
};


void Scroll::setCamera(Object *obj) {
	
	this->camera = obj;
	
};

Scroll::~Scroll() {
	//printf("Ya no hay Scroll");
};

