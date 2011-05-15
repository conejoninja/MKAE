#include "includes.h"

#ifndef SCROLL_H_
#define SCROLL_H_



class Scroll {
           
	private:
		MKAE_REGION R0;
		MKAE_REGION R1;
		bool active;
		signed long x;
		signed long y;
		signed long dx;
		signed long dy;
		unsigned short moveEasing;
		unsigned short scrollMode;
		Object *camera;

                                   
	public:

		Scroll();
		void setRegions(MKAE_REGION R0, MKAE_REGION R1);
		MKAE_COORD centerScroll(MKAE_COORD n);
		MKAE_COORD getOffset(MKAE_COORD camera);
		MKAE_COORD getOffset();
		void setCamera(Object *obj);
		unsigned short R0Width();
		unsigned short R0Height();
		unsigned short R1Width();
		unsigned short R1Height();
		MKAE_REGION getR0();
		MKAE_REGION getR1();

		
		~Scroll();
		 
};


#endif /*SCROLL_H_*/
