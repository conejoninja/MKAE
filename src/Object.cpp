#include "includes.h"
#include "Shape.h"
#include "Object.h"
#include "GameView.h"


std::string actions[10];
bool inAction = false;
bool queueEmpty = true;
ACTION currentAction = IDLE;
Params currentParams;

Object::Object() {
	this->angle = 0;
	this->scale = 1;
};

Object::Object(int idd, MKAE_IMG imgg, int xx, int yy) {
	id = idd;
	img = imgg;
	x = xx;
	y = yy;
	visible = true;
	this->reg();

};



int Object::reg() { 
	
	//Game::objects.push_back(this);
	Object obj;
	Game::objects.push_back(obj);
	int l = Game::objects.size()-1;

	//planes para agruparlos en un unico array frustrados
	//Game::objs.push_back(&Game::objects[l]);
	Game::objects[l].id = this->id;
	Game::objects[l].img.image = this->img.image;
	Game::objects[l].img.bitmap = this->img.bitmap;
	Game::objects[l].img.width = this->img.width;
	Game::objects[l].img.height = this->img.height;
	Game::objects[l].setSize(this->img.width, this->img.height);
	Game::objects[l].setCenter(this->img.centerX, this->img.centerY);
	Game::objects[l].setXY(this->x, this->y);
	Game::objects[l].setName(this->name);
	Game::objects[l].setFilename(this->filename);
	Game::objects[l].setAngle(this->angle);
	Game::objects[l].setScale(this->scale);
	Game::objects[l].setTextOfAction(0,this->actions[0]);
	Game::objects[l].setTextOfAction(1,this->actions[1]);
	Game::objects[l].setTextOfAction(2,this->actions[2]);
	Game::objects[l].setTextOfAction(3,this->actions[3]);
	Game::objects[l].setTextOfAction(4,this->actions[4]);
	Game::objects[l].setTextOfAction(5,this->actions[5]);
	Game::objects[l].setTextOfAction(6,this->actions[6]);
	Game::objects[l].setTextOfAction(7,this->actions[7]);
	Game::objects[l].setTextOfAction(8,this->actions[8]);
	Game::objects[l].setTextOfAction(9,this->actions[9]);
	Game::objects[l].loadImage((char*)(this->filename));
	return l;
	//GameView::registerSprite(this);
};



std::string Object::getTextOfAction(int n ) {
	return actions[n];
};


void Object::setTextOfAction(int n, std::string s) {
	
	actions[n] = s;
	
};


void Object::setTextOfActions(std::string actionss[10]) {
	
	for(int k = 0;k<10;k++) {
		actions[k] = actionss[k];
	};
	
};



void Object::setXY(int xx, int yy) {
	this->x = xx;
	this->y = yy;
	//this->img.image->x = x;
	//this->img.image->y = y;
};


void Object::addAction(ACTION action, Params p) {
	
	
	MKAE_ACTION act;
	act.action = action;
	act.p = p;
	MKAE_ACTION actt;
	MKAE_SCRIPT *script;
	
	switch(action) {

		case GIVE:
		case OPEN:
		case CLOSE:
		case PICKUP:
		case TALK:
		case LOOKAT:
		case USE:
		case PUSH:
		case PULL:
		
			Object *o;
			o = (Object*)(p[0]);
			MKAE_COORD n;
			n = o->getXY();
			actt.action = GOTO;
			actt.p.push_back((void*)(n.x));
			actt.p.push_back((void*)(n.y));
			this->buffer.push_back(actt);
			this->buffer.push_back(act);
			break;
			
		case SCRIPT:
						
			script = (MKAE_SCRIPT*)(p[0]);
	
			while(script->size()) {
				
				MKAE_ACTION *acttt;
				acttt = (MKAE_ACTION*)(&script[0]);
				actt.action = acttt->action;
				actt.p = acttt->p;
				this->buffer.push_back(actt);
				script->pop_front();
				
			};
	
			p.pop_front();

			break;
		
		default:
	
			this->buffer.push_back(act);	
			break;
		
	};
	
};


/*****************************************************************
 * 
 * MUCHA PARTE IMPORTANTE SE MANEJA AQUI !!!
 * 
 *****************************************************************/
void Object::frame() {
	
	MKAE_COORD n;
	Object *o;
	std::string cadena;

	if(!this->inAction) {
		if(this->buffer.size()) {
			this->queueEmpty = false;
			this->inAction = true;
			currentAction = this->buffer[0].action;
			currentParams = this->buffer[0].p;
			this->buffer.pop_front();
		} else {
			this->currentAction = IDLE;
			this->queueEmpty = true;	
		};
	} else {

		this->queueEmpty = false;
		
		switch(this->currentAction) {
			
			case WALKING:
					
				n = this->getXY();
				if(MKAE_RealDistance(n.x,n.y,this->destX,this->destY)>10) {
					float	angle = MKAE_GetAngle(n.x, n.y, this->destX, this->destY);
					// It has to be used to display diferents frames of angle
					this->setXY(n.x+4*sin(angle),n.y+4*cos(angle));
		
				} else if(this->path.xy.size()) {
					this->destX = this->path.xy[0].x;
					this->destY = this->path.xy[0].y;
					
					this->path.xy.pop_front();
				} else {
					this->inAction = false;
				};
				
				break;
			
			case GOTO:

				n.x = (int)(currentParams[0]);
				n.y = (int)(currentParams[1]);
				this->path = Pathfinding::findPath(this->getXY(),n);
						
				this->destX = this->path.xy[0].x;
				this->destY = this->path.xy[0].y;
				this->path.xy.pop_front();
				
				currentAction = WALKING;
				break;
				
				
			case LOOKAT:
				
				o = (Object*)(currentParams[0]);
				cadena = o->getTextOfAction(5); // 5 = LOOKAT
				Game::addMsgQueue(cadena, 100, 100, 5000, this->id);
				this->inAction = true;
				break;
				
			case IDLE:
				// AQUI NO SE DEBERIA LLEGAR NUNCA
				this->inAction = false;
				break;
				
			default: 
				this->inAction = false;
				break;			
			
		};
		// DO STUFF HERE		
	
	};
	
};


void Object::resetActions() {
	
	while(this->buffer.size()) {
		this->buffer.pop_front();	
	};
	this->currentAction = IDLE;
	this->queueEmpty = true;
	this->inAction = false;
	
};





Object::~Object() {
	//printf("Ya no hay Object");
};

