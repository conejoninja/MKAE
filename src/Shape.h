#include "includes.h"
//#include <ulib/ulib.h>

#ifndef SHAPE_H_
#define SHAPE_H_




class Shape {
           
	protected:
		signed long x, y;
		float angle, scale;
		unsigned char radius;
		bool visible;
		std::string name;
		char* filename;

                                   
	public:
		signed long id;
		MKAE_IMG img;

		Shape();
		Shape(int id, MKAE_IMG img, int x, int y);
		bool loadImage(const char *s);
		virtual void setXY(int x, int y);
		void setCenter(int x, int y);
		void setSize(int w, int h);
		void setRadius(unsigned char rad);
		void setScale(float scale);
		void setAngle(float angle);
		float getScale();
		float getAngle();
		MKAE_REGION getBounds();
		
		
		virtual void frame();

		
		unsigned char getRadius();
		void setName(std::string name);
		std::string getName();
		void setFilename(char* name);
		char* getFilename();
		MKAE_COORD getXY();
		void draw();
		virtual int reg();
		~Shape();
		 
};

#endif  /*SHAPE_H_*/
