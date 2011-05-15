

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "includes.h"
//#include "dataTypes.h"
#include "Shape.h"
#include <vector>


class Controller {
           
	private:
		static MKAE_MOUSE mouse;
		static short lastState;
		static bool semiClick;
		static bool clicks;
		static signed char timeClick;
		static signed char timeDblClick;
		//static ir_t ir;
                                   
	public:
		//static wiimote** wiimotes;
		//static MKAE_WIIMOTE wiimoteData;
		static MKAE_IMG crosshair;
		
		static bool readed;
		

		Controller();
		static void readData();
		static void loadCrosshair(const char *s);
		static void initController();
		static short getState();
		static MKAE_MOUSE getMouse();
		static MKAE_COORD getXY();
		~Controller();
		 
};
#endif /*CONTROLLER_H_*/
