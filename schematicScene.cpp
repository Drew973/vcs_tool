#include "schematicScene.h"

schematicScene::schematicScene(QObject *parent) : QGraphicsScene(parent)
{

}



//void schematicScene::addFeature(feature feat,lane xsp,position pos,float s_ch,float e_ch)
//{}


float top(lane xsp,position pos)
{
    float top=0;
    if (xsp==HS){top=0;}
    if (xsp==CL1){top=0.25;}
    if (xsp==CL2){top=0.5;}
    if (xsp==CL3){top=0.75;}

    if (pos==R){top+=0.25*2/3;}
    if (pos==N){top+=0.25*1/3;}

    return top;

};



float bottom(lane xsp,position pos)
{
    float bottom = 0;
    if (xsp==HS){bottom=0;}
    if (xsp==CL1){bottom=0.25;}
    if (xsp==CL2){bottom=0.5;}
    if (xsp==CL3){bottom=0.75;}

    if (pos==L){bottom+=0.25*1/3;}
    if (pos==R){bottom+=0.25;}
    if (pos==F){bottom+=0.25;}
    if (pos==N){bottom+=0.25*2/3;}

    return bottom;

};



/*
xspTops = {'HS':0,'CL1':1/4,'CL2':1/2,'CL3':3/4}
locTops = {'L':0,'R':2/3,'F':0,'N':1/3}


#return fraction from 0 to 1 representing leftmost point
def top(xsp,loc):
    return xspTops[xsp]+locTops[loc]*0.25


#xspBottoms = {'HS':1/4,'CL1':1/2,'CL2':3/4,'CL3':1}
locBottoms = {'L':1/3,'R':1,'F':1,'N':2/3}


#return fraction from 0 to 1 representing leftmost point
def bottom(xsp,loc):
    return xspTops[xsp]+locBottoms[loc]*0.25


*/
