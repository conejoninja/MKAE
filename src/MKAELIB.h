/****************************************************************************
 *                                                                          *
 *                    #     #    #  #     ###     ####                      *
 *                    ##   ##    # #     #   #    #                         *
 *                    # # # #    ##      #####    ###                       *
 *                    #  #  #    # #     #   #    #                         *
 *                    #     #    #  #    #   #    #####                     *
 *                                                                          *
 *                         MIGHTY KICK-ASS ENGINE                           *
 *                                                                          *
 *                      MOTOR DE AVENTURAS GRAFICAS                         *
 *                 _CONEJO - http://www.theNinjaBunny.com/                  * 
 *   Se distibuye bajo la Licencia Privada del _CONEJO (LPVCv1) de la cual  *
 * debe de haber recibido una copia. El hecho de usar este software implica *
 *  la aceptación de dicha licencia. Por favor leala si no lo ha hecho aún  *
 *                                                                          * 
 *   ESTE SOFTWARE PERTENECE A 'LA ORGANIZACION' Y NO PUEDE SER UTILIZADO   * 
 *    POR NINGUNA OTRA ENTIDAD (UNITARIA O GRUPAL) PARA NINGUN FIN          * 
 *                                                                          * 
 *         USTED ES UN PRINGAO (por si aún no se lo habían dicho)           * 
 *                                                                          * 
 ****************************************************************************/

#include "includes.h"


#ifndef MKAELIB_H_
#define MKAELIB_H_

//#include "Object.h"
//#include "dataTypes.h"

unsigned long MKAE_Distance(int x1, int y1, int x2, int y2);
float MKAE_RealDistance(int x1, int y1, int x2, int y2);

float MKAE_GetAngle(int x1, int y1, int x2, int y2);

void wiimote_event(struct wiimote_t* wm, int event);

bool collision(Object obj,  MKAE_COORD p);
bool collisionObj(int i, int j);

std::string MKAE_float2str(float f);
std::string MKAE_int2str(int i);

void MKAE_DrawImg(int xpos, int ypos, int width, int high, const unsigned short data[], float rad_ang, float rapport, MKAE_REGION r);


MKAE_COORD MKAE_calculateCoord(Shape * shape, MKAE_COORD n, float scale, float angle);
bool MKAE_collisionPointObj(Shape * shape, MKAE_COORD n);
MKAE_COORD MKAE_proyectionPoint(MKAE_COORD p1, MKAE_COORD p2, MKAE_COORD q);



/*******************************
 * COLISIONES
 * *****************************/
bool MKAE_inBox(MKAE_POLBOX box, MKAE_COORD p);
MKAE_COORD MKAE_middlePoint(MKAE_COORD p, MKAE_COORD q);
MKAE_COORD MKAE_intersectionOfLines(MKAE_COORD u, MKAE_COORD v, MKAE_COORD p, MKAE_COORD q);

//int MKAE_poligonCollision(POLYGON *a, POLYGON *b);



#endif /*MKAELIB_H_*/
