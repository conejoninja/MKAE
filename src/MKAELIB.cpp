#include "includes.h"
#include "GameView.h"


//#include "dataTypes.h"
//include "MKAELIB.h" 
#define PI 3.14159265


unsigned long MKAE_Distance(int x1, int y1, int x2, int y2) {
	
	return ((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
	
};

float MKAE_RealDistance(int x1, int y1, int x2, int y2) {
	
	return sqrtf((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)); // We dont need DOUBLE precision, use float method instead
	
};


float MKAE_GetAngle(int x1, int y1, int x2, int y2) {
	
	return atan2(float(x2-x1), float(y2-y1));
	
};



void wiimote_event(struct wiimote_t* wm, int event) {
	//THIS SHIT DO NOTHING
};





bool collision(Object obj,  MKAE_COORD p) {// ARREGLADO!!
	
	
	
	MKAE_COORD cam = Game::characters[Game::giliID].getXY();
	MKAE_COORD sc = Game::mainScroll.getOffset(cam);
	
	int mx, my, mxdest, mydest; 
	unsigned int bx, by;        
	int x, y;                   
	int ligne_x, ligne_y;       
	int dxi, dyi, dxj, dyj;     
	float tcos, tsin;           
	int largeurdest, hauteurdest;
	
	float angle = obj.getAngle();
	float scale = obj.getScale();
	MKAE_COORD n = obj.getXY();
	int objx = sc.x+n.x-obj.img.centerX*scale;
	int objy = sc.y+n.y-obj.img.centerY*scale;

	
	
	if(int(angle)==0 && int(scale)==1){
		if(p.x>=objx && p.x<=objx+obj.img.width && p.y>=objy && p.y<=objy+obj.img.height) {
		
			int a = p.x-objx;
			int b = p.y-objy;
			if(obj.img.image[b*obj.img.width+a]!=MKAE_TRANSPARENT) {
				return true;
			} else {
				return false;
			};
		} else {
			return false;
		};
		
	} else {
		
		tcos = cos(angle);
		tsin = sin(angle);
		
		largeurdest = (int) ceil( (obj.img.width * fabs(tcos) + obj.img.height * fabs(tsin)) * scale );
		hauteurdest = (int) ceil( (obj.img.width * fabs(tsin) + obj.img.height * fabs(tcos)) * scale );
		
		mxdest = (int) largeurdest/2;
		mydest = (int) hauteurdest/2;
		mx = (int) obj.img.width/2;
		my = (int) obj.img.height/2;
		
		ligne_x = mx*65536 + (-tcos * mxdest - tsin * mydest) / scale * 65536.0;
		ligne_y = my*65536 + ( tsin * mxdest - tcos * mydest) / scale * 65536.0;
		dxi = tcos / scale * 65536.0;
		dxj = tsin / scale * 65536.0;
		dyi = -tsin / scale * 65536.0;
		dyj = tcos / scale * 65536.0;
			
		int b = p.y-objy+mydest-my;
		int a = p.x-objx+mxdest-mx;
		
		x = ligne_x+dxj*b+dxi*a;
		y = ligne_y+dyj*b+dyi*a;
		bx = ((unsigned int) x) >> 16;
		by = ((unsigned int) y) >> 16;
		if (bx>=0 && bx< obj.img.width && by>=0 && by< obj.img.height){
			if(obj.img.image[by*obj.img.width+bx]!=MKAE_TRANSPARENT) {
				return true;
			} else {
				return false;
			};
		} else {
			return false;
		};
	};	

	return false;
};


bool collisionObj(int i, int j) {




	return false;
};



std::string MKAE_float2str(float f) {
	std::stringstream stream;
	stream << f;
	return stream.str();
};


std::string MKAE_int2str(int i) {
	std::stringstream stream;
	stream << i;
	return stream.str();
};













MKAE_COORD MKAE_calculateCoord(Shape * shape, MKAE_COORD n, float scale, float angle) {
	
	float dist = MKAE_RealDistance(shape->img.centerX,shape->img.centerY,(shape->img.width/2),(shape->img.height/2));
	MKAE_COORD m;

	if(dist>4) {
		float angleCentre = atan2(shape->img.centerX-(shape->img.width/2), shape->img.centerY-(shape->img.height/2));
		float rads = PI*angle/180;
		float angleResult = angleCentre-rads;
		m.x = (dist*sin(angleResult))-shape->img.centerX;
		m.y = (dist*cos(angleResult))-shape->img.centerY;
		m.x = scale*(-m.x-(shape->img.width/2));//-shape->img.centerX
		m.y = scale*(-m.y-(shape->img.height/2));//-shape->img.centerY
		//GRRLIB_Printf(100,100,GameView::text_font1,0xFFF00FFF,1,"%d",m.x);
		//GRRLIB_Printf(100,120,GameView::text_font1,0xFFF00FFF,1,"%d",m.y);
		
	} else {
		m = n;
	}; 
	
	return m;
	
};












void MKAE_DrawImg(int xpos, int ypos, int width, int high, const unsigned short data[], float rad_ang, float rapport, MKAE_REGION r ){
 int ni=0;
 int mx, my, mxdest, mydest;    /* Coordonnées des centres des surfaces */
 int i=0, j;                    /* Coordonnées de travail lors du parcourt de la surface de destination */
 unsigned int bx, by;           /* Coordonnées de travail, correspondent à i et j dans l'image d'origine */
 int x, y;                      /* valeurs de travail (bx et by avant arrondit */
 int ligne_x, ligne_y;          /* valeurs au debut des lignes (retour de i à 0) */
 int dxi, dyi, dxj, dyj;        /* increments des x et y suivant i et j (compteurs des x et y) */
 float tcos, tsin;              /* cos et sin de angle_radian */
 int largeurdest, hauteurdest;  /* Dimentions de la surface de destination */

   if((rad_ang==0)&(rapport==1)){
	 for(y=ypos;y<ypos+high;y++){
                for(x=xpos;x<xpos+width;x++){
						if(data[ni]!=MKAE_TRANSPARENT && x>=r.x0 && x<=r.x1 && y>=r.y0 && y<=r.y1) { 
                        	//GRRLIB_PutPixel(x,y,data[ni]);
						};
                        ni++;
                }
        }	
   }
   else{
        tcos = cos(rad_ang);
        tsin = sin(rad_ang);

        largeurdest = (int) ceil( (width * fabs(tcos) + high * fabs(tsin)) * rapport );
        hauteurdest = (int) ceil( (width * fabs(tsin) + high * fabs(tcos)) * rapport );

        mxdest = (int) largeurdest;///2;
        mydest = (int) hauteurdest;///2;
        mx = (int) width;///2;
        my = (int) high;///2;

        /* Initialisation et calculs des incréments */
        ligne_x = mx*65536 + (-tcos * mxdest - tsin * mydest) / rapport * 65536.0;
        ligne_y = my*65536 + ( tsin * mxdest - tcos * mydest) / rapport * 65536.0;
        dxi = tcos / rapport * 65536.0;
        dxj = tsin / rapport * 65536.0;
        dyi = -tsin / rapport * 65536.0;
        dyj = tcos / rapport * 65536.0;

        for(j=0;j<hauteurdest;j++){
                x = ligne_x;
                y = ligne_y;
                for(i=0;i<largeurdest;i++) {
                        bx = ((unsigned int) x) >> 16;
                        by = ((unsigned int) y) >> 16;
                        /* on vérifie que l'on ne sort pas des bords*/
                        if (bx>=0 && bx< width && by>=0 && by< high){
								if(data[by*width+bx]!=MKAE_TRANSPARENT  && (i+xpos)>=r.x0 && (i+xpos)<=r.x1 && (j+ypos)>=r.y0 && (j+ypos)<=r.y1) {
                                	//GRRLIB_PutPixel(i+xpos,j+ypos,data[by*width+bx]);
								};
								/*if(data[by*width+bx]!=MKAE_TRANSPARENT  && (i+xpos-mxdest+mx)>=r.x0 && (i+xpos-mxdest+mx)<=r.x1 && (j+ypos-mydest+my)>=r.y0 && (j+ypos-mydest+my)<=r.y1) {
                                	GRRLIB_PutPixel(i+xpos-mxdest+mx,j+ypos-mydest+my,data[by*width+bx]);
								};*/
                        }

                                /* On incrémente les coordonnées dans l'image d'origine */
                        x += dxi;
                        y += dyi;
                }
                /* incrément pour le changement de ligne */
                ligne_x += dxj;
                ligne_y += dyj;
        }

   }
}


bool MKAE_inBox(MKAE_POLBOX box, MKAE_COORD p) {
	
	

	int ot = (box.v1.x-box.v3.x)*(box.v2.y-box.v3.y)-(box.v1.y-box.v3.y)*(box.v2.x-box.v3.x);
	int o1 = (box.v1.x-p.x)*(box.v2.y-p.y)-(box.v1.y-p.y)*(box.v2.x-p.x);
	int o2 = (box.v2.x-p.x)*(box.v3.y-p.y)-(box.v2.y-p.y)*(box.v3.x-p.x);
	int o3 = (box.v3.x-p.x)*(box.v1.y-p.y)-(box.v3.y-p.y)*(box.v1.x-p.x);
	

	
	
	if( (ot>=0 && o1>=0 && o2>=0 && o3>=0) || (ot<0 && o1<0 && o2<0 && o3<0) ) {
		return true;
	}; 
	
	ot = (box.v1.x-box.v4.x)*(box.v3.y-box.v4.y)-(box.v1.y-box.v4.y)*(box.v3.x-box.v4.x);
	o1 = (box.v1.x-p.x)*(box.v3.y-p.y)-(box.v1.y-p.y)*(box.v3.x-p.x);
	o2 = (box.v3.x-p.x)*(box.v4.y-p.y)-(box.v3.y-p.y)*(box.v4.x-p.x);
	o3 = (box.v4.x-p.x)*(box.v1.y-p.y)-(box.v4.y-p.y)*(box.v1.x-p.x);



	
	if( (ot>=0 && o1>=0 && o2>=0 && o3>=0) || (ot<0 && o1<0 && o2<0 && o3<0) ) {
		return true;
	}; 
	
	
	return false;
	
};


bool MKAE_collisionPointObj(Shape *shape, MKAE_COORD m) {
	
	
	/* WII Version
	MKAE_COORD n = shape->getXY();
	float scale = shape->getScale();
	float angle = shape->getAngle();
	
	float dist = MKAE_RealDistance(0,0,shape->img.centerX*scale,shape->img.centerY*scale);
	MKAE_POLBOX box;
	MKAE_COORD q;

	float angleCentre = atan2(-(shape->img.centerX), -(shape->img.centerY));
	float rads = PI*angle/180;
	float angleResult = angleCentre-rads;
	box.v1.x = (dist*sin(angleResult))-0;
	box.v1.y = (dist*cos(angleResult))-0;

	box.v1.x = n.x+box.v1.x;
	box.v1.y = n.y+box.v1.y;


	//GRRLIB_Line(box.v1.x, box.v1.y-5, box.v1.x, box.v1.y+5, 0xFFFFFFFF);
	//GRRLIB_Line(box.v1.x-5, box.v1.y, box.v1.x+5, box.v1.y, 0xFFFFFFFF);


	dist = MKAE_RealDistance(shape->img.width*scale,0,shape->img.centerX*scale,shape->img.centerY*scale);
	angleCentre = atan2(shape->img.width-(shape->img.centerX), -(shape->img.centerY));
	angleResult = angleCentre-rads;
	box.v2.x = (dist*sin(angleResult))-0;
	box.v2.y = (dist*cos(angleResult))-0;

	box.v2.x = n.x+box.v2.x;
	box.v2.y = n.y+box.v2.y;
		
	//GRRLIB_Line(box.v2.x, box.v2.y-5, box.v2.x, box.v2.y+5, 0xFFFFF000);
	//GRRLIB_Line(box.v2.x-5, box.v2.y, box.v2.x+5, box.v2.y, 0xFFFFF000);
		
	dist = MKAE_RealDistance(shape->img.width*scale,shape->img.height*scale,shape->img.centerX*scale,shape->img.centerY*scale);
	angleCentre = atan2(shape->img.width-(shape->img.centerX), shape->img.height-(shape->img.centerY));
	angleResult = angleCentre-rads;
	box.v3.x = (dist*sin(angleResult))-0;
	box.v3.y = (dist*cos(angleResult))-0;

	box.v3.x = n.x+box.v3.x;
	box.v3.y = n.y+box.v3.y;
		
	//GRRLIB_Line(box.v3.x, box.v3.y-5, box.v3.x, box.v3.y+5, 0xFFFFFFFF);
	//GRRLIB_Line(box.v3.x-5, box.v3.y, box.v3.x+5, box.v3.y, 0xFFFFFFFF);
		
	dist = MKAE_RealDistance(0,shape->img.height*scale,shape->img.centerX*scale,shape->img.centerY*scale);
	angleCentre = atan2(-(shape->img.centerX), shape->img.height-(shape->img.centerY));
	angleResult = angleCentre-rads;
	box.v4.x = (dist*sin(angleResult))-0;
	box.v4.y = (dist*cos(angleResult))-0;

	box.v4.x = n.x+box.v4.x;
	box.v4.y = n.y+box.v4.y;
		
	//GRRLIB_Line(box.v4.x, box.v4.y-5, box.v4.x, box.v4.y+5, 0xFFFFF000);
	//GRRLIB_Line(box.v4.x-5, box.v4.y, box.v4.x+5, box.v4.y, 0xFFFFF000);
		
	//GRRLIB_Line(m.x, m.y-10, m.x, m.y+10, 0xFFFFF000);
	//GRRLIB_Line(m.x-10, m.y, m.x+10, m.y, 0xFFFFF000);
		

		

	if(MKAE_inBox(box, m)) {
		q = MKAE_proyectionPoint(box.v1, box.v2, m);
		//GRRLIB_Line(q.x, q.y-10, q.x, q.y+10, 0xFFFFF000);
		//GRRLIB_Line(q.x-10, q.y, q.x+10, q.y, 0xFFFFF000);
		
		float dx = MKAE_RealDistance(box.v1.x, box.v1.y, q.x, q.y)/scale;
		float dy = MKAE_RealDistance(m.x, m.y, q.x, q.y)/scale;
		
		int pos = floor(dx)+shape->img.width*floor(dy);
		
		if(shape->img.bitmap[pos]==1) {
			return true;
		} else {
			return false;
		}
		
		
		//return true;
	} else {
		return false;
	};
	
	return false	
	*/
	
	// PC Version
	SDL_Rect rect;
	rect.x = m.x;
	rect.y = m.y;
	rect.w = 1;
	rect.h = 1;
	return shape->img.sprite->Collision(CRM32Pro.screen,&rect,-1,-1,1);

	
	
};

MKAE_COORD MKAE_proyectionPoint(MKAE_COORD v1, MKAE_COORD v2, MKAE_COORD q) {
	
	MKAE_COORD n;
	float d1,dx,dy;
	
	dx = v2.x-v1.x;
	dy = v2.y-v1.y;
	
	d1 = (float(q.x-v1.x)*float(v2.x-v1.x)+float(q.y-v1.y)*float(v2.y-v1.y))/MKAE_Distance(v1.x,v1.y,v2.x,v2.y);//(float(v2.x-v1.x)*float(v2.x-v1.x)-float(v2.y-v1.y)*float(v2.y-v1.y));
	
		
	
	n.x = int(v1.x+float(d1*(v2.x-v1.x)));
	n.y = int(v1.y+float(d1*(v2.y-v1.y)));
	

	
	return n;
	
};
MKAE_COORD MKAE_middlePoint(MKAE_COORD p, MKAE_COORD q) {
	
	MKAE_COORD n;
	n.x = (p.x+q.x)/2;
	n.y = (p.y+q.y)/2;
	
	return n;
	
};

MKAE_COORD MKAE_intersectionOfLines(MKAE_COORD u, MKAE_COORD v, MKAE_COORD p, MKAE_COORD q) {
	
	float m1 = (v.y-u.y)/(v.x-u.x);
	float m2 = (q.y-p.y)/(q.x-p.x);
	float n1 = u.y-(float)(m1*u.x);
	float n2 = p.y-(float)(m2*p.x);
	
	MKAE_COORD n;
	n.x = (float)(n2-n1)/(float)(m1-m2);
	n.y = (float)(m1+n.x+n1);
	
	if(((u.x-n.x)*(n.x-v.x))>=0 && ((u.y-n.y)*(n.y-v.y))>=0) {
		return n;
	} else {
		MKAE_COORD zero;
		zero.x = zero.y = 0;
		return zero;
	};
	
	MKAE_COORD zero;
	zero.x = zero.y = 0;
	return zero;
	
};




MKAE_REGION getCollisionRect(Shape* target1, Shape* target2, bool pixelPrecise = false, int tolerance = 0) {

	MKAE_REGION rect1 = target1->getBounds();
	MKAE_REGION rect2 = target2->getBounds();

	return rect1;
};







