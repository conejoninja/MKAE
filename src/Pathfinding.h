#include "includes.h"

#ifndef PATHFINDING_H_
#define PATHFINDING_H_


class Pathfinding {
           
	private:
		static signed char lastBox;                        
	public:

		Pathfinding();
		static bool inBox(MKAE_BOX box, MKAE_COORD p);
		static signed char inWhichBox(MKAE_COORD p);
		static MKAE_COORD findCommonEdge(MKAE_BOX box1, MKAE_BOX box2);
		static MKAE_COORD middlePoint(MKAE_COORD p, MKAE_COORD q);
		static MKAE_COORD middlePointCoord(MKAE_COORD p);
		static MKAE_COORD findNextPoint(MKAE_COORD p, MKAE_COORD q);
		static MKAE_PATH findPath(MKAE_COORD p, MKAE_COORD q);
		static signed char nearBox(MKAE_COORD p);
		static signed char nearBox2(MKAE_COORD p);
		static signed char nearBox3(MKAE_COORD p);
		static signed char nearBox3fixed(MKAE_COORD q, signed char box);
		static signed char shortestPath(signed char box, signed char boxA, signed char boxB);
		static MKAE_COORD boundaryPoint(MKAE_COORD p);
		static MKAE_STRUCT2 nearEdge(MKAE_BOX box, MKAE_COORD p);
		static MKAE_COORD intersectionOfLines(MKAE_BOX box, MKAE_COORD p, MKAE_COORD q);
		static MKAE_COORD intersectionOfLines2(MKAE_BOX box, MKAE_COORD p, MKAE_COORD q);//NOT WORKING
		static MKAE_COORD intersectionOfLines3(MKAE_BOX box, MKAE_COORD p, MKAE_COORD q);
		static bool inTriangle(MKAE_COORD p, MKAE_COORD r, MKAE_COORD s, MKAE_COORD t);
		~Pathfinding();
		

		 
};

#endif /*PATHFINDING_H_*/
