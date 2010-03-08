/*
  myduanli@gmail.com 2010-03-05
*/
#include <QApplication>
#include "roadOfHuarong.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    RoadOfHR mainWin;
    mainWin.show();

    return app.exec();
}

