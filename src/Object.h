#include "includes.h"


#ifndef OBJECT_H_
#define OBJECT_H_



class Object : public Shape {
	
	
	protected:
		std::string actions[10];

           
	private:
		ACTION currentAction;
		Params currentParams;
		bool inAction;
		bool queueEmpty;
		std::deque<MKAE_ACTION> buffer;
	

                                   
	public:

		signed long destX,destY;
		//static std::vector<MKAE_COORD> path;
		MKAE_PATH path;


		Object();
		Object(int id, MKAE_IMG img, int x, int y);
		
		
		
		
		std::string getTextOfAction(int n);
		void setTextOfAction(int n, std::string s);
		void setTextOfActions(std::string actionss[10]);
		void resetActions();
		
		void addAction(ACTION action, Params p);


		virtual void setXY(int x, int y);
		void frame();
		
		
		
		int reg();
		//virtual void autoRegister();
		
		~Object();
		 
};

#endif /*OBJECT_H_*/
