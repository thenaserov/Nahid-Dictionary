#include "mainwindow.h"

#include <QApplication>
#include <QSplashScreen>
#include <QTimer>
#include <time.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSplashScreen *splash = new QSplashScreen();
    splash->setPixmap(QPixmap(":/Files/pngaaa.com-1524756.png"));
    splash->show();
    MainWindow w;
    QTimer::singleShot(300, splash, SLOT(close()));
    QTimer::singleShot(1000, &w, SLOT(Show()));
    w.show();
    return a.exec();
}
