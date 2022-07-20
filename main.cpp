#include "mainwindow.h"
#include "csma.h"
#include <QApplication>

using namespace std;


int main(int argc, char *argv[])
    {
        QApplication app(argc, argv);
        CSMASim window;
        return app.exec();
}




