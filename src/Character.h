#include "includes.h"
#include "Object.h"


#ifndef CHARACTER_H_
#define CHARACTER_H_

class Character : public Object {
           
	private:
		unsigned char colorTalk;
                                   
	public:

		Character();
		void say(std::string talk); 
		int reg();
		void setXY(int x, int y);
		
		
		void calculateScale();
		unsigned char getColorTalk();
		void setColorTalk(unsigned char color);
		
		
		//void autoRegister();
		//bool loadImage(char *s, int pal); 
		~Character();
		 
};



#endif /*CHARACTER_H_*/
