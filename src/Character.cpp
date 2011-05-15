#include "includes.h"
#include "Shape.h"
#include "GameView.h"



Character::Character() {
	this->angle = 0;
	this->scale = 1;
};


int Character::reg() { 
	Character cha;
	Game::characters.push_back(cha);
	int l = Game::characters.size()-1;

	//planes para agruparlos en un unico array frustrados
	//Game::objs.push_back(&Game::characters[l]);
	Game::characters[l].id = this->id;
	Game::characters[l].img.image = this->img.image;
	Game::characters[l].img.bitmap = this->img.bitmap;
	Game::characters[l].img.width = this->img.width;
	Game::characters[l].img.height = this->img.height;
	Game::characters[l].setSize(this->img.width, this->img.height);
	Game::characters[l].setCenter(this->img.centerX, this->img.centerY);
	Game::characters[l].setXY(this->x, this->y);
	Game::characters[l].destX = this->x;
	Game::characters[l].destY = this->y;
	Game::characters[l].setName(this->name);
	Game::characters[l].setFilename(this->filename);
	Game::characters[l].setAngle(this->angle);
	Game::characters[l].setScale(this->scale);
	Game::characters[l].setTextOfAction(0,this->actions[0]);
	Game::characters[l].setTextOfAction(1,this->actions[1]);
	Game::characters[l].setTextOfAction(2,this->actions[2]);
	Game::characters[l].setTextOfAction(3,this->actions[3]);
	Game::characters[l].setTextOfAction(4,this->actions[4]);
	Game::characters[l].setTextOfAction(5,this->actions[5]);
	Game::characters[l].setTextOfAction(6,this->actions[6]);
	Game::characters[l].setTextOfAction(7,this->actions[7]);
	Game::characters[l].setTextOfAction(8,this->actions[8]);
	Game::characters[l].setTextOfAction(9,this->actions[9]);
	Game::characters[l].loadImage((char*)(this->filename));
	return l;
	//GameView::registerSprite(this);
};


void Character::say(std::string talk) {
	GameView::charSay(this, talk);
}; 


void Character::setColorTalk(unsigned char color) {
	this->colorTalk = color;
};

unsigned char Character::getColorTalk() {
	return this->colorTalk;
};


void Character::setXY(int xx, int yy) {
	this->calculateScale();
	this->x = xx;
	this->y = yy;
};




void Character::calculateScale() {
	
	/* THIS IS BROKEN! BROKEN!
	MKAE_COORD p = this->getXY();;
	
	signed char box = Pathfinding::inWhichBox(p);
	
	if(box>=0) {
		float d1 = MKAE_RealDistance(p.x, p.y, GameView::room.vertex[GameView::room.boxes[box].v1].x, GameView::room.vertex[GameView::room.boxes[box].v1].y);
		float d2 = MKAE_RealDistance(p.x, p.y, GameView::room.vertex[GameView::room.boxes[box].v2].x, GameView::room.vertex[GameView::room.boxes[box].v2].y);
		float d3 = MKAE_RealDistance(p.x, p.y, GameView::room.vertex[GameView::room.boxes[box].v3].x, GameView::room.vertex[GameView::room.boxes[box].v3].y);
		float d4 = MKAE_RealDistance(p.x, p.y, GameView::room.vertex[GameView::room.boxes[box].v4].x, GameView::room.vertex[GameView::room.boxes[box].v4].y);
		float dmax = d1;
		if(d2<dmax) {
			dmax = d2;
		} else if(d3>dmax) {
			dmax = d3;
		} else if(d4>dmax) {
			dmax = d4;
		};
			
		float total = (dmax/d1)+(dmax/d2)+(dmax/d3)+(dmax/d4);
		this->scale = (GameView::room.vertex[GameView::room.boxes[box].v1].scale*(dmax/d1)+GameView::room.vertex[GameView::room.boxes[box].v2].scale*(dmax/d2)+GameView::room.vertex[GameView::room.boxes[box].v3].scale*(dmax/d3)+GameView::room.vertex[GameView::room.boxes[box].v4].scale*(dmax/d4))/(total*100);
	} else {
		this->scale = 1;
	};*/
	this->scale = 1;
	
};





Character::~Character() {
	//printf("Ya no hay Character");
};

