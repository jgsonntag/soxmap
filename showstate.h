// $Id: showstate.h,v 1.3 2005/07/22 20:38:16 sonntag Exp $
#ifndef SHOWSTATE_H
#define SHOWSTATE_H

#include <math.h>
#include <qvbox.h>
#include <qlabel.h>

#include "position.h"


class Showstate : public QVBox
{
  Q_OBJECT

  public:
    Showstate(Position *cur,QWidget *parent=0,const char *name=0);
    ~Showstate();

  private:
    QString stemp;
    Position *current;
    QLabel *timelab;
    QLabel *latlab;
    QLabel *lonlab;
    QLabel *htlab;
    QLabel *hdglab;
    QLabel *spdlab;
    QLabel *roclab;

  public slots:
    void update();

};

#endif // SHOWSTATE_H
