#include "includes.h"
#include "Shape.h"
#include "GameView.h"

MKAE_IMG img;
//u8 this->radius = 10;




Shape::Shape() {
	this->angle = 0;
	this->scale = 1;
};

Shape::Shape(int idd, MKAE_IMG imgg, int xx, int yy) {
	this->id = idd;
	this->img = imgg;
	this->x = xx;
	this->y = yy;
	this->visible = true;
	this->reg();

};

bool Shape::loadImage(const char *s) {

	// PC Version	
	this->img.sprite = new CRM32Pro_CSprite();
	this->img.sprite->Load((char*)(Game::GFX_RESOURCE),(char*)(s),(char*)("SPR2"));
	this->img.sprite->AutoRestore(0);
	
	
	return true;
};

void Shape::setXY(int xx, int yy) {
	this->x = xx;
	this->y = yy;
	//this->img.image->x = x;
	//this->img.image->y = y;
};

void Shape::setCenter(int x, int y) {
	this->img.centerX = x;
	this->img.centerY = y;
};

void Shape::setSize(int w, int h) {
	this->img.width = w;
	this->img.height = h;

};


void Shape::setRadius(unsigned char rad) {
	this->radius = rad;
};

unsigned char Shape::getRadius() {
	return this->radius;
};

void Shape::setName(std::string namee) {
	this->name = namee;
};

std::string Shape::getName() {
	return this->name;
};

void Shape::setFilename(char* namee) {
	this->filename = namee;
};

char* Shape::getFilename() {
	return this->filename;
};



MKAE_COORD Shape::getXY() {
	MKAE_COORD n;
	n.x = this->x;
	n.y = this->y;
	return n;
};



void Shape::setScale(float scale) {
	this->scale = scale;
};

void Shape::setAngle(float angle) {
	this->angle = angle;
};

float Shape::getScale() {
	return this->scale;
};

float Shape::getAngle() {
	return this->angle;
};


MKAE_REGION Shape::getBounds() {
	MKAE_REGION r;
	r.x0 = this->x;
	r.y0 = this->y;
	r.x1 = this->x+this->img.width;
	r.y1 = this->y+this->img.height;
	return r;
};




void Shape::draw() {
	
	/*
	MKAE_COORD n;
	n.x = this->x;
	n.y = this->y;
	
	GameView::drawImage(this->img, n);
	*/
	
	/* PC Optimized */
	/* Should we draw here or send it to GameView class? */
	//this->img.sprite->SetPosition(100,100,1);
	//this->img.sprite->Draw();
	//ILogSystem.Msg(LOG_NORMAL," XXXXXXXXX %d",this->x);
	
};


int Shape::reg() { 
	
	return 0;
};

void Shape::frame() { 
	//do nothing
};
















Shape::~Shape() {
	//printf("Ya no hay Shape");
};

