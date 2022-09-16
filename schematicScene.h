#ifndef SCHEMATICSCENE_H
#define SCHEMATICSCENE_H

#include <QGraphicsScene>
#include <QObject>



enum lane {HS,CL1,CL2,CL3};
enum position {L,N,R,F};
//enum feature {HRA,TSSC,I(G),I(MH)}; //brackets give syntax error. qstring instead
//what if need to add other lanes?
//lanes table? lane,pos,fraction



class schematicScene : public QGraphicsScene
{
public:
    explicit schematicScene(QObject *parent = nullptr);
    //addFeature(QObject *parent = nullptr);


};



float top(lane xsp,position pos);

float bottom(lane xsp,position pos);

#endif // SCHEMATICSCENE_H


