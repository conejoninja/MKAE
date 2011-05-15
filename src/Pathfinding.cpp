#include "includes.h"
#include "Pathfinding.h"
#include "GameView.h"

signed char Pathfinding::lastBox = 0;
Pathfinding::Pathfinding() {
	
};

bool Pathfinding::inTriangle(MKAE_COORD p, MKAE_COORD r, MKAE_COORD s, MKAE_COORD t) {
	
	
	int ot = (r.x-t.x)*(s.y-t.y)-(r.y-t.y)*(s.x-t.x);
	int o1 = (r.x-p.x)*(s.y-p.y)-(r.y-p.y)*(s.x-p.x);
	int o2 = (s.x-p.x)*(t.y-p.y)-(s.y-p.y)*(t.x-p.x);
	int o3 = (t.x-p.x)*(r.y-p.y)-(t.y-p.y)*(r.x-p.x);


	
	
	if( (ot>=0 && o1>=0 && o2>=0 && o3>=0) || (ot<0 && o1<0 && o2<0 && o3<0) ) {
		return true;
	};
	
	return false;
};



bool Pathfinding::inBox(MKAE_BOX box, MKAE_COORD p) {
	
	

	int ot = (GameView::room.vertex[box.v1].x-GameView::room.vertex[box.v3].x)*(GameView::room.vertex[box.v2].y-GameView::room.vertex[box.v3].y)-(GameView::room.vertex[box.v1].y-GameView::room.vertex[box.v3].y)*(GameView::room.vertex[box.v2].x-GameView::room.vertex[box.v3].x);
	int o1 = (GameView::room.vertex[box.v1].x-p.x)*(GameView::room.vertex[box.v2].y-p.y)-(GameView::room.vertex[box.v1].y-p.y)*(GameView::room.vertex[box.v2].x-p.x);
	int o2 = (GameView::room.vertex[box.v2].x-p.x)*(GameView::room.vertex[box.v3].y-p.y)-(GameView::room.vertex[box.v2].y-p.y)*(GameView::room.vertex[box.v3].x-p.x);
	int o3 = (GameView::room.vertex[box.v3].x-p.x)*(GameView::room.vertex[box.v1].y-p.y)-(GameView::room.vertex[box.v3].y-p.y)*(GameView::room.vertex[box.v1].x-p.x);
	

	
	
	if( (ot>=0 && o1>=0 && o2>=0 && o3>=0) || (ot<0 && o1<0 && o2<0 && o3<0) ) {
		return true;
	}; 
	
	ot = (GameView::room.vertex[box.v1].x-GameView::room.vertex[box.v4].x)*(GameView::room.vertex[box.v3].y-GameView::room.vertex[box.v4].y)-(GameView::room.vertex[box.v1].y-GameView::room.vertex[box.v4].y)*(GameView::room.vertex[box.v3].x-GameView::room.vertex[box.v4].x);
	o1 = (GameView::room.vertex[box.v1].x-p.x)*(GameView::room.vertex[box.v3].y-p.y)-(GameView::room.vertex[box.v1].y-p.y)*(GameView::room.vertex[box.v3].x-p.x);
	o2 = (GameView::room.vertex[box.v3].x-p.x)*(GameView::room.vertex[box.v4].y-p.y)-(GameView::room.vertex[box.v3].y-p.y)*(GameView::room.vertex[box.v4].x-p.x);
	o3 = (GameView::room.vertex[box.v4].x-p.x)*(GameView::room.vertex[box.v1].y-p.y)-(GameView::room.vertex[box.v4].y-p.y)*(GameView::room.vertex[box.v1].x-p.x);



	
	if( (ot>=0 && o1>=0 && o2>=0 && o3>=0) || (ot<0 && o1<0 && o2<0 && o3<0) ) {
		return true;
	}; 
	
	
	return false;
	
};

signed char Pathfinding::inWhichBox(MKAE_COORD p) {
	
	int l = GameView::room.boxes.size();
	if(l) {
		for(int k = 0;k<l;k++) {
			if(Pathfinding::inBox(GameView::room.boxes[k],p)) {
				return k;
			};
		};
	};
	
	return -1;
	
};


MKAE_COORD Pathfinding::findCommonEdge(MKAE_BOX box1, MKAE_BOX box2) {
	
	MKAE_COORD n;
	bool firstPoint = false;
	std::vector<signed char> list1;
	std::vector<signed char> list2;
	
	list1.push_back(box1.v1);
	list1.push_back(box1.v2);
	list1.push_back(box1.v3);
	list1.push_back(box1.v4);
	
	list2.push_back(box2.v1);
	list2.push_back(box2.v2);
	list2.push_back(box2.v3);
	list2.push_back(box2.v4);
	

	
	for(int i = 0;i<4;i++) {
		for(int j = 0;j<4;j++) {
			if(list1[i]==list2[j]) {
				if(!firstPoint) {
					n.x = list1[i];
					firstPoint = true;
				} else {
					n.y = list1[i];
					return n;
				};
			};
		};
	};
	
	n.x = n.y = -1;
	return n;

};

MKAE_COORD Pathfinding::middlePoint(MKAE_COORD p, MKAE_COORD q) {
	
	MKAE_COORD n;
	n.x = (p.x+q.x)/2;
	n.y = (p.y+q.y)/2;
	
	return n;
	
};

MKAE_COORD Pathfinding::middlePointCoord(MKAE_COORD p) {
	
	MKAE_COORD n;
	n.x = (GameView::room.vertex[p.x].x+GameView::room.vertex[p.y].x)/2;
	n.y = (GameView::room.vertex[p.x].y+GameView::room.vertex[p.y].y)/2;
	
	return n;
	
};


MKAE_COORD Pathfinding::findNextPoint(MKAE_COORD p, MKAE_COORD q) {
	
	signed char inBox = Pathfinding::inWhichBox(p);
	signed char toBox = Pathfinding::inWhichBox(q);


	
	if(GameView::room.matrix[inBox][toBox][0]==0) {
		return q;
	} else if(GameView::room.matrix[inBox][toBox][0]>1) {
		
	} else { //In case is the next box
		MKAE_COORD n = Pathfinding::findCommonEdge(GameView::room.boxes[inBox],GameView::room.boxes[GameView::room.matrix[inBox][toBox][1]]);
		return Pathfinding::middlePointCoord(n);
	};
	
	return q;
};


MKAE_PATH Pathfinding::findPath(MKAE_COORD p, MKAE_COORD q) {
	
	//		GRRLIB_Print(50,50,font5_char_width,font5_char_high,"GRRLIB TEXTSYSTEM DEMO!",font5,0xffff,0xf01e);
	
	
	MKAE_PATH path;
	
	signed char inBox = Pathfinding::inWhichBox(p);
	if(inBox==-1) {
		inBox = Pathfinding::lastBox;
	};
	signed char toBox = Pathfinding::inWhichBox(q);
	
	path.xy.push_back(p);
	
	bool out = false;
	if(toBox==-1) {
		//toBox = Pathfinding::nearBox3(q);
		toBox = Pathfinding::nearBox3fixed(q, inBox);
		out = true;
	};


	Pathfinding::lastBox = toBox;
	
	if(GameView::room.matrix[inBox][toBox][0]==0) {

	} else { //In case is the next box
		int l = GameView::room.matrix[inBox][toBox][0];

		for(int k =0;k<l;k++) {
			MKAE_COORD n = Pathfinding::findCommonEdge(GameView::room.boxes[inBox],GameView::room.boxes[GameView::room.matrix[inBox][toBox][1]]);

			path.xy.push_back(Pathfinding::middlePointCoord(n));
			inBox = GameView::room.matrix[inBox][toBox][1];

		};
	};
	
	if(!out) {
		path.xy.push_back(q);
	} else {
		
		MKAE_COORD n = Pathfinding::boundaryPoint(q);//GameView::room.boxes[toBox],path.xy[(path.xy.size()-1)],q);

		path.xy.push_back(n);
	};
	return path;
};


MKAE_COORD Pathfinding::intersectionOfLines(MKAE_BOX box, MKAE_COORD p, MKAE_COORD q) {
	
	MKAE_COORD n,r;
	

	float m1,m2,n1,n2,a,b;
	a = float(q.y)-float(p.y);
	b = float(q.x)-float(p.x);

	r.x = p.x;
	r.y = q.y;

	m1 = float(a/b);
	n1 = float(p.y)-m1*float(p.x);

	
	m2 = (float(GameView::room.vertex[box.v2].y)-float(GameView::room.vertex[box.v1].y))/(float(GameView::room.vertex[box.v2].x)-float(GameView::room.vertex[box.v1].x));
	n2 = float(GameView::room.vertex[box.v1].y)-m2*float(GameView::room.vertex[box.v1].x);
	

	
	n.x = int((n2-n1)/(m1-m2));
	n.y = int(m2*n.x+n2);
	

	
	if(((p.x-n.x)*(n.x-q.x))>=0 && ((GameView::room.vertex[box.v1].x-n.x)*(n.x-GameView::room.vertex[box.v2].x))>=0 && ((p.y-n.y)*(n.y-q.y))>=0 && ((GameView::room.vertex[box.v1].y-n.y)*(n.y-GameView::room.vertex[box.v2].y))>=0){

//		PA_Draw8bitLine( 1,p.x,p.y,n.x,n.y,7);
//	GRRLIB_Line(p.x,p.y,n.x,n.y,0xF800);

		return n;
	};

	
	m2 = (float(GameView::room.vertex[box.v3].y)-float(GameView::room.vertex[box.v2].y))/(float(GameView::room.vertex[box.v3].x)-float(GameView::room.vertex[box.v2].x));
	n2 = float(GameView::room.vertex[box.v2].y)-m2*float(GameView::room.vertex[box.v2].x);
	
	
	n.x = int((n2-n1)/(m1-m2));
	n.y = int(m2*n.x+n2);
	


	if(((p.x-n.x)*(n.x-q.x))>=0 && ((GameView::room.vertex[box.v2].x-n.x)*(n.x-GameView::room.vertex[box.v3].x))>=0 && ((p.y-n.y)*(n.y-q.y))>=0 && ((GameView::room.vertex[box.v2].y-n.y)*(n.y-GameView::room.vertex[box.v3].y))>=0){

//		PA_Draw8bitLine( 1,p.x,p.y,n.x,n.y,8);
//	GRRLIB_Line(p.x,p.y,n.x,n.y,0xFF00);

		return n;
	};

	m2 = (float(GameView::room.vertex[box.v4].y)-float(GameView::room.vertex[box.v3].y))/(float(GameView::room.vertex[box.v4].x)-float(GameView::room.vertex[box.v3].x));
	n2 = float(GameView::room.vertex[box.v3].y)-m2*float(GameView::room.vertex[box.v3].x);
	
	
	n.x = int((n2-n1)/(m1-m2));
	n.y = int(m2*n.x+n2);
	

	
	if(((p.x-n.x)*(n.x-q.x))>=0 && ((GameView::room.vertex[box.v3].x-n.x)*(n.x-GameView::room.vertex[box.v4].x))>=0 && ((p.y-n.y)*(n.y-q.y))>=0 && ((GameView::room.vertex[box.v3].y-n.y)*(n.y-GameView::room.vertex[box.v4].y))>=0){


//	GRRLIB_Line(p.x,p.y,n.x,n.y,0xF880);

		return n;
	};

	m2 = (float(GameView::room.vertex[box.v1].y)-float(GameView::room.vertex[box.v4].y))/(float(GameView::room.vertex[box.v1].x)-float(GameView::room.vertex[box.v4].x));
	n2 = float(GameView::room.vertex[box.v4].y)-m2*float(GameView::room.vertex[box.v4].x);
	
	
	n.x = int((n2-n1)/(m1-m2));
	n.y = int(m2*n.x+n2);
	

	
	if(((p.x-n.x)*(n.x-q.x))>=0 && ((GameView::room.vertex[box.v4].x-n.x)*(n.x-GameView::room.vertex[box.v1].x))>=0 && ((p.y-n.y)*(n.y-q.y))>=0 && ((GameView::room.vertex[box.v4].y-n.y)*(n.y-GameView::room.vertex[box.v1].y))>=0){
	
//	GRRLIB_Line(p.x,p.y,n.x,n.y,0xF8F8);

		return n;
	};

	
	
	
	

	return p;
	
};





MKAE_COORD Pathfinding::intersectionOfLines3(MKAE_BOX box, MKAE_COORD p, MKAE_COORD q) {
	
	MKAE_COORD n;
	std::vector<MKAE_STRUCT2> data;
	
	
	

	float m1,m2,n1,n2;

	
	m2 = (float(GameView::room.vertex[box.v2].y)-float(GameView::room.vertex[box.v1].y))/(float(GameView::room.vertex[box.v2].x)-float(GameView::room.vertex[box.v1].x));
	n2 = float(GameView::room.vertex[box.v1].y)-m2*float(GameView::room.vertex[box.v1].x);
	m1 = float(-1/m2);
	n1 = float(q.y)-m1*float(q.x);
	


	
	
	n.x = int((n2-n1)/(m1-m2));
	n.y = int(m1*n.x+n1);
	
	
	if(((GameView::room.vertex[box.v1].x-n.x)*(n.x-GameView::room.vertex[box.v2].x))>=0 && ((GameView::room.vertex[box.v1].y-n.y)*(n.y-GameView::room.vertex[box.v2].y))>=0){

		
		MKAE_STRUCT2 st;
		st.dist = MKAE_Distance(p.x,p.y,n.x,n.y);
		st.n = n;
		data.push_back(st);

	};

	
	m2 = (float(GameView::room.vertex[box.v3].y)-float(GameView::room.vertex[box.v2].y))/(float(GameView::room.vertex[box.v3].x)-float(GameView::room.vertex[box.v2].x));
	n2 = float(GameView::room.vertex[box.v2].y)-m2*float(GameView::room.vertex[box.v2].x);
	m1 = float(-1/m2);
	n1 = float(q.y)-m1*float(q.x);
	
	
	n.x = int((n2-n1)/(m1-m2));
	n.y = int(m1*n.x+n1);
	


	if(((GameView::room.vertex[box.v2].x-n.x)*(n.x-GameView::room.vertex[box.v3].x))>=0 && ((GameView::room.vertex[box.v2].y-n.y)*(n.y-GameView::room.vertex[box.v3].y))>=0){

		MKAE_STRUCT2 st;
		st.dist = MKAE_Distance(p.x,p.y,n.x,n.y);
		st.n = n;
		data.push_back(st);

	};

	m2 = (float(GameView::room.vertex[box.v4].y)-float(GameView::room.vertex[box.v3].y))/(float(GameView::room.vertex[box.v4].x)-float(GameView::room.vertex[box.v3].x));
	n2 = float(GameView::room.vertex[box.v3].y)-m2*float(GameView::room.vertex[box.v3].x);
	m1 = float(-1/m2);
	n1 = float(q.y)-m1*float(q.x);
	
	
	n.x = int((n2-n1)/(m1-m2));
	n.y = int(m1*n.x+n1);
	

	
	if(((GameView::room.vertex[box.v3].x-n.x)*(n.x-GameView::room.vertex[box.v4].x))>=0 && ((GameView::room.vertex[box.v3].y-n.y)*(n.y-GameView::room.vertex[box.v4].y))>=0){

		MKAE_STRUCT2 st;
		st.dist = MKAE_Distance(p.x,p.y,n.x,n.y);
		st.n = n;
		data.push_back(st);

	};

	m2 = (float(GameView::room.vertex[box.v1].y)-float(GameView::room.vertex[box.v4].y))/(float(GameView::room.vertex[box.v1].x)-float(GameView::room.vertex[box.v4].x));
	n2 = float(GameView::room.vertex[box.v4].y)-m2*float(GameView::room.vertex[box.v4].x);
	m1 = float(-1/m2);
	n1 = float(q.y)-m1*float(q.x);
	
	
	n.x = int((n2-n1)/(m1-m2));
	n.y = int(m1*n.x+n1);
	

	
	if(((GameView::room.vertex[box.v4].x-n.x)*(n.x-GameView::room.vertex[box.v1].x))>=0 && ((GameView::room.vertex[box.v4].y-n.y)*(n.y-GameView::room.vertex[box.v1].y))>=0){

		MKAE_STRUCT2 st;
		st.dist = MKAE_Distance(p.x,p.y,n.x,n.y);
		st.n = n;
		data.push_back(st);

	};

	
	
		int l = data.size();
		float dmin = 5000000.0;
		
		
		if(l) {
			for(int k = 0;k<l;k++) {
				if(data[k].dist<dmin) {
					dmin = data[k].dist;
					n = data[k].n;
				};
			};
			return n;
		} else {

			return q;
		};
		
		
	
	
	

	
	
	return q;
	
};






MKAE_COORD Pathfinding::intersectionOfLines2(MKAE_BOX box, MKAE_COORD p, MKAE_COORD q) {
	
	MKAE_VERTEX v1,v2,v3,v4;
	MKAE_COORD n,n1,n2,n3,n4;
	n1.x = n2.x = n3.x = n4.x = 0;
	n1.y = n2.y = n3.y = n4.y = 0;
	
	v1 = GameView::room.vertex[box.v1];
	v2 = GameView::room.vertex[box.v2];
	v3 = GameView::room.vertex[box.v3];
	v4 = GameView::room.vertex[box.v4];
	

	float d1,d2,d3,d4,dmin,dx,dy;
	dmin = 500;
	
	dx = v2.x-v1.x;
	dy = v2.y-v1.y;
	
	d1 = (float(q.x-v1.x)*float(v2.x-v1.x)+float(q.y-v1.y)*float(v2.y-v1.y))/MKAE_Distance(v1.x,v1.y,v2.x,v2.y);//(float(v2.x-v1.x)*float(v2.x-v1.x)-float(v2.y-v1.y)*float(v2.y-v1.y));
	d2 = (float(q.x-v2.x)*float(v3.x-v2.x)+float(q.y-v2.y)*float(v3.y-v2.y))/MKAE_Distance(v2.x,v2.y,v3.x,v3.y);//(float(v3.x-v2.x)*float(v3.x-v2.x)-float(v3.y-v2.y)*float(v3.y-v2.y));
	d3 = (float(q.x-v3.x)*float(v4.x-v3.x)+float(q.y-v3.y)*float(v4.y-v3.y))/MKAE_Distance(v3.x,v3.y,v4.x,v4.y);//(float(v4.x-v3.x)*float(v4.x-v3.x)-float(v4.y-v3.y)*float(v4.y-v3.y));
	d4 = (float(q.x-v4.x)*float(v1.x-v4.x)+float(q.y-v4.y)*float(v1.y-v4.y))/MKAE_Distance(v4.x,v4.y,v1.x,v1.y);//(float(v1.x-v4.x)*float(v1.x-v4.x)-float(v1.y-v4.y)*float(v1.y-v4.y));
	
	
		

	
	n.x = int(v1.x+float(d1*(v2.x-v1.x)));
	n.y = int(v1.y+float(d1*(v2.y-v1.y)));
	
	GameView::drawPoint(n);
	
	if(((v1.x-n.x)*(n.x-v2.x))>=0 && ((v1.y-n.y)*(n.y-v2.y))>=0) {
		n1.x = n.x;
		n1.y = n.y;
	}
	
	n.x = int(v2.x+float(d2*(v3.x-v2.x)));
	n.y = int(v2.y+float(d2*(v3.y-v2.y)));
	
	GameView::drawPoint(n);

	if(((v2.x-n.x)*(n.x-v3.x))>=0 && ((v2.y-n.y)*(n.y-v3.y))>=0) {
		n2.x = n.x;
		n2.y = n.y;
	}
	
	n.x = int(v3.x+float(d3*(v4.x-v3.x)));
	n.y = int(v3.y+float(d3*(v4.y-v3.y)));
	
	GameView::drawPoint(n);

	if(((v3.x-n.x)*(n.x-v4.x))>=0 && ((v3.y-n.y)*(n.y-v4.y))>=0) {
		n3.x = n.x;
		n3.y = n.y;
	}
	
	n.x = int(v4.x+float(d4*(v1.x-v4.x)));
	n.y = int(v4.y+float(d4*(v1.y-v4.y)));
	
	GameView::drawPoint(n);

	if(((v4.x-n.x)*(n.x-v1.x))>=0 && ((v4.y-n.y)*(n.y-v1.y))>=0) {
		n4.x = n.x;
		n4.y = n.y;
	}
	
	
	if(n1.x != 0) {
		if(d1<dmin) {
			dmin = d1;
			n = n1;
		};
	};
	
	if(n2.x != 0) {
		if(d2<dmin) {
			dmin = d2;
			n = n2;
		};
	};
	
	if(n3.x != 0) {
		if(d3<dmin) {
			dmin = d3;
			n = n3;
		};
	};
	
	if(n4.x != 0) {
		if(d4<dmin) {
			dmin = d4;
			n = n4;
		};
	};
	
	if(dmin==500) {
		return p;
	} else {




		return n;
	};
	

	return p;
	
};


signed char Pathfinding::nearBox(MKAE_COORD p) {
	
	int l = GameView::room.boxes.size();
	signed char min = -1;
//	u16 dist = 0; // comentar al descomentar la de abajo
	unsigned long dist = MKAE_Distance(0,0,300,200);
	unsigned long tmpDist = 0;
	if(l) {
		for(int k = 0;k<l;k++) {
			tmpDist = MKAE_Distance(GameView::room.vertex[GameView::room.boxes[k].v1].x,GameView::room.vertex[GameView::room.boxes[k].v1].y,p.x,p.y);
			if(tmpDist<dist) {
				dist = tmpDist;
				min = k;
			};
			tmpDist = MKAE_Distance(GameView::room.vertex[GameView::room.boxes[k].v2].x,GameView::room.vertex[GameView::room.boxes[k].v2].y,p.x,p.y);
			if(tmpDist<dist) {
				dist = tmpDist;
				min = k;
			};
			tmpDist = MKAE_Distance(GameView::room.vertex[GameView::room.boxes[k].v3].x,GameView::room.vertex[GameView::room.boxes[k].v3].y,p.x,p.y);
			if(tmpDist<dist) {
				dist = tmpDist;
				min = k;
			};
			tmpDist = MKAE_Distance(GameView::room.vertex[GameView::room.boxes[k].v4].x,GameView::room.vertex[GameView::room.boxes[k].v4].y,p.x,p.y);
			if(tmpDist<dist) {
				dist = tmpDist;
				min = k;
			};
		};
	};
	

	
	return min;
	
};



signed char Pathfinding::nearBox2(MKAE_COORD q) {
	
	std::vector<MKAE_STRUCT1> data;
	MKAE_VERTEX n,v1,v2,v3,v4,n1,n2,n3,n4;
	n1.x = n2.x = n3.x = n4.x = 0;
	n1.y = n2.y = n3.y = n4.y = 0;
	int l = GameView::room.boxes.size();
	signed char nearBox = -1;


	float d1,d2,d3,d4,dmin,tmpDist,dx,dy;

	dmin = 500000000;

	if(l) {
		for(int k = 0;k<l;k++) {

			
			v1 = GameView::room.vertex[GameView::room.boxes[k].v1];
			v2 = GameView::room.vertex[GameView::room.boxes[k].v2];
			v3 = GameView::room.vertex[GameView::room.boxes[k].v3];
			v4 = GameView::room.vertex[GameView::room.boxes[k].v4];
			
		
			dmin = 500000000;
			
			dx = v2.x-v1.x;
			dy = v2.y-v1.y;


			
			

			
			d1 = (float(q.x-v1.x)*float(v2.x-v1.x)+float(q.y-v1.y)*float(v2.y-v1.y))/MKAE_Distance(v1.x,v1.y,v2.x,v2.y);//(float(v2.x-v1.x)*float(v2.x-v1.x)-float(v2.y-v1.y)*float(v2.y-v1.y));
			d2 = (float(q.x-v2.x)*float(v3.x-v2.x)+float(q.y-v2.y)*float(v3.y-v2.y))/MKAE_Distance(v2.x,v2.y,v3.x,v3.y);//(float(v3.x-v2.x)*float(v3.x-v2.x)-float(v3.y-v2.y)*float(v3.y-v2.y));
			d3 = (float(q.x-v3.x)*float(v4.x-v3.x)+float(q.y-v3.y)*float(v4.y-v3.y))/MKAE_Distance(v3.x,v3.y,v4.x,v4.y);//(float(v4.x-v3.x)*float(v4.x-v3.x)-float(v4.y-v3.y)*float(v4.y-v3.y));
			d4 = (float(q.x-v4.x)*float(v1.x-v4.x)+float(q.y-v4.y)*float(v1.y-v4.y))/MKAE_Distance(v4.x,v4.y,v1.x,v1.y);//(float(v1.x-v4.x)*float(v1.x-v4.x)-float(v1.y-v4.y)*float(v1.y-v4.y));
			
			
				
			
			n.x = int(v1.x+float(d1*(v2.x-v1.x)));
			n.y = int(v1.y+float(d1*(v2.y-v1.y)));
			
			if(((v1.x-n.x)*(n.x-v2.x))>=0 && ((v1.y-n.y)*(n.y-v2.y))>=0) {
				n1.x = n.x;
				n1.y = n.y;
		


			}
			
			n.x = int(v2.x+float(d2*(v3.x-v2.x)));
			n.y = int(v2.y+float(d2*(v3.y-v2.y)));
			
			if(((v2.x-n.x)*(n.x-v3.x))>=0 && ((v2.y-n.y)*(n.y-v3.y))>=0) {
				n2.x = n.x;
				n2.y = n.y;



			}
			
			n.x = int(v3.x+float(d3*(v4.x-v3.x)));
			n.y = int(v3.y+float(d3*(v4.y-v3.y)));
			
			if(((v3.x-n.x)*(n.x-v4.x))>=0 && ((v3.y-n.y)*(n.y-v4.y))>=0) {
				n3.x = n.x;
				n3.y = n.y;



			}
			
			n.x = int(v4.x+float(d4*(v1.x-v4.x)));
			n.y = int(v4.y+float(d4*(v1.y-v4.y)));
			
			if(((v4.x-n.x)*(n.x-v1.x))>=0 && ((v4.y-n.y)*(n.y-v1.y))>=0) {
				n4.x = n.x;
				n4.y = n.y;



			}
			
			
			if(n1.x != 0) {
				d1 = MKAE_Distance(q.x,q.y,n1.x,n1.y);

				if(d1<dmin) {
					dmin = d1;

	
				};
			};
			
			if(n2.x != 0) {
				d2 = MKAE_Distance(q.x,q.y,n2.x,n2.y);
				if(d2<dmin) {
					dmin = d2;
	
				};
			};
			
			if(n3.x != 0) {
				d3 = MKAE_Distance(q.x,q.y,n3.x,n3.y);
				if(d3<dmin) {
					dmin = d3;
	
				};
			};
			
			if(n4.x != 0) {
				d4 = MKAE_Distance(q.x,q.y,n4.x,n4.y);
				if(d4<dmin) {
					dmin = d4;
	
				};
			};
			

				
				tmpDist = MKAE_Distance(GameView::room.vertex[GameView::room.boxes[k].v1].x,GameView::room.vertex[GameView::room.boxes[k].v1].y,q.x,q.y);
				if(tmpDist<dmin) {
					dmin = tmpDist;
				};
				tmpDist = MKAE_Distance(GameView::room.vertex[GameView::room.boxes[k].v2].x,GameView::room.vertex[GameView::room.boxes[k].v2].y,q.x,q.y);
				if(tmpDist<dmin) {
					dmin = tmpDist;
				};
				tmpDist = MKAE_Distance(GameView::room.vertex[GameView::room.boxes[k].v3].x,GameView::room.vertex[GameView::room.boxes[k].v3].y,q.x,q.y);
				if(tmpDist<dmin) {
					dmin = tmpDist;
				};
				tmpDist = MKAE_Distance(GameView::room.vertex[GameView::room.boxes[k].v4].x,GameView::room.vertex[GameView::room.boxes[k].v4].y,q.x,q.y);
				if(tmpDist<dmin) {
					dmin = tmpDist;
				};
				


			MKAE_STRUCT1 st;
			st.dist = dmin;
			st.nbox = k;
			data.push_back(st);
		};
		
		
		int ll = data.size();
		dmin = 500000000;
		
		

		
		if(ll) {
			for(int k = 0;k<ll;k++) {

				if(data[k].dist<dmin) {
					dmin = data[k].dist;
					nearBox = data[k].nbox;
				};
			};
		};
		
		
		
		
	};
	

	
	return nearBox;
	
};



signed char Pathfinding::nearBox3(MKAE_COORD q) {
	
	int l = GameView::room.boxes.size();
	signed char nearBox = -1;

	MKAE_STRUCT2 st;
	

	float dmin;

	dmin = 500000000;

	if(l) {
		for(int k = 0;k<l;k++) {

			st = Pathfinding::nearEdge(GameView::room.boxes[k],q);
			
			if(st.dist<dmin) {
				dmin = st.dist;
				nearBox = k;
			};				
				
			
			
		};

	};
	

	
	return nearBox;
	
};


signed char Pathfinding::nearBox3fixed(MKAE_COORD q, signed char box) {
	
	int l = GameView::room.boxes.size();
	signed char nearBox = -1;

	MKAE_STRUCT2 st;
	

	float dmin;

	dmin = 500000000;

	if(l) {
		for(int k = 0;k<l;k++) {

			st = Pathfinding::nearEdge(GameView::room.boxes[k],q);
			
			if(st.dist<dmin) {
				dmin = st.dist;
				nearBox = k;
			} else if(st.dist==dmin) {
				
				nearBox = Pathfinding::shortestPath(box, nearBox, k);
				
			};				
				
			
			
		};

	};
	

	
	return nearBox;
	
};



signed char Pathfinding::shortestPath(signed char box, signed char boxA, signed char boxB) {
	
	if(GameView::room.matrix[box][boxA][0]<=GameView::room.matrix[box][boxB][0]) {
		return boxA;
	} else {
		return boxB;
	};
	
};






MKAE_STRUCT2 Pathfinding::nearEdge(MKAE_BOX box, MKAE_COORD q) {
	
	MKAE_VERTEX n,v1,v2,v3,v4,n1,n2,n3,n4;
	n1.x = n2.x = n3.x = n4.x = 0;
	n1.y = n2.y = n3.y = n4.y = 0;
	
	v1 = GameView::room.vertex[box.v1];
	v2 = GameView::room.vertex[box.v2];
	v3 = GameView::room.vertex[box.v3];
	v4 = GameView::room.vertex[box.v4];
	

	float d1,d2,d3,d4,dmin,dx,dy;
	dmin = 500000000.0;
	
	dx = v2.x-v1.x;
	dy = v2.y-v1.y;
	
	d1 = (float(q.x-v1.x)*float(v2.x-v1.x)+float(q.y-v1.y)*float(v2.y-v1.y))/MKAE_Distance(v1.x,v1.y,v2.x,v2.y);//(float(v2.x-v1.x)*float(v2.x-v1.x)-float(v2.y-v1.y)*float(v2.y-v1.y));
	d2 = (float(q.x-v2.x)*float(v3.x-v2.x)+float(q.y-v2.y)*float(v3.y-v2.y))/MKAE_Distance(v2.x,v2.y,v3.x,v3.y);//(float(v3.x-v2.x)*float(v3.x-v2.x)-float(v3.y-v2.y)*float(v3.y-v2.y));
	d3 = (float(q.x-v3.x)*float(v4.x-v3.x)+float(q.y-v3.y)*float(v4.y-v3.y))/MKAE_Distance(v3.x,v3.y,v4.x,v4.y);//(float(v4.x-v3.x)*float(v4.x-v3.x)-float(v4.y-v3.y)*float(v4.y-v3.y));
	d4 = (float(q.x-v4.x)*float(v1.x-v4.x)+float(q.y-v4.y)*float(v1.y-v4.y))/MKAE_Distance(v4.x,v4.y,v1.x,v1.y);//(float(v1.x-v4.x)*float(v1.x-v4.x)-float(v1.y-v4.y)*float(v1.y-v4.y));
	
	
		
	
	n.x = int(v1.x+float(d1*(v2.x-v1.x)));
	n.y = int(v1.y+float(d1*(v2.y-v1.y)));
	

	
	if(((v1.x-n.x)*(n.x-v2.x))>=0 && ((v1.y-n.y)*(n.y-v2.y))>=0) {
		n1.x = n.x;
		n1.y = n.y;
	}
	
	n.x = int(v2.x+float(d2*(v3.x-v2.x)));
	n.y = int(v2.y+float(d2*(v3.y-v2.y)));
	


	if(((v2.x-n.x)*(n.x-v3.x))>=0 && ((v2.y-n.y)*(n.y-v3.y))>=0) {
		n2.x = n.x;
		n2.y = n.y;
	}
	
	n.x = int(v3.x+float(d3*(v4.x-v3.x)));
	n.y = int(v3.y+float(d3*(v4.y-v3.y)));
	


	if(((v3.x-n.x)*(n.x-v4.x))>=0 && ((v3.y-n.y)*(n.y-v4.y))>=0) {
		n3.x = n.x;
		n3.y = n.y;
	}
	
	n.x = int(v4.x+float(d4*(v1.x-v4.x)));
	n.y = int(v4.y+float(d4*(v1.y-v4.y)));
	


	if(((v4.x-n.x)*(n.x-v1.x))>=0 && ((v4.y-n.y)*(n.y-v1.y))>=0) {
		n4.x = n.x;
		n4.y = n.y;
	}
	
	
	if(n1.x != 0) {
		d1 = MKAE_Distance(q.x,q.y,n1.x,n1.y);
		if(d1<dmin) {
			dmin = d1;
			n = n1;
		};
	};
	
	if(n2.x != 0) {
		d2 = MKAE_Distance(q.x,q.y,n2.x,n2.y);
		if(d2<dmin) {
			dmin = d2;
			n = n2;
		};
	};
	
	if(n3.x != 0) {
		d3 = MKAE_Distance(q.x,q.y,n3.x,n3.y);
		if(d3<dmin) {
			dmin = d3;
			n = n3;
		};
	};
	
	if(n4.x != 0) {
		d4 = MKAE_Distance(q.x,q.y,n4.x,n4.y);
		if(d4<dmin) {
			dmin = d4;
			n = n4;
		};
	};
	
	float dtemp;
	dtemp = MKAE_Distance(q.x,q.y,v1.x,v1.y);
	if(dtemp<dmin) {
		dmin = dtemp;
		n = v1;
	};
	
	dtemp = MKAE_Distance(q.x,q.y,v2.x,v2.y);
	if(dtemp<dmin) {
		dmin = dtemp;
		n = v2;
	};
	
	dtemp = MKAE_Distance(q.x,q.y,v3.x,v3.y);
	if(dtemp<dmin) {
		dmin = dtemp;
		n = v3;
	};
	
	dtemp = MKAE_Distance(q.x,q.y,v4.x,v4.y);
	if(dtemp<dmin) {
		dmin = dtemp;
		n = v4;
	};
	
	
	MKAE_STRUCT2 st;
	st.dist = dmin;
	st.n = q;
	
	if(dmin==500000000.0) {

		st.n = q;
		return st;
	} else {




		MKAE_COORD nn;
		nn.x = n.x;
		nn.y = n.y;
		st.n = nn;
		return st;
	};
	

	return st;
	
};





MKAE_COORD Pathfinding::boundaryPoint(MKAE_COORD q) {
	
	int l = GameView::room.boxes.size();
	MKAE_COORD n;

	MKAE_STRUCT2 st;
	

	float dmin;

	dmin = 500000000;

	if(l) {
		for(int k = 0;k<l;k++) {

			st = Pathfinding::nearEdge(GameView::room.boxes[k],q);
			
			if(st.dist<dmin) {
				dmin = st.dist;
				n = st.n;
			};				
				
			
			
		};

	};
	
//	PA_Draw8bitLine( 1,q.x,q.y,n.x,n.y,10);
	
	
	return n;
	
};





Pathfinding::~Pathfinding() {
	//printf("Ya no hay Character");
};

