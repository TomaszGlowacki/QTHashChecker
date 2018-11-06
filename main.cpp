// HashChecker.cpp : Defines the entry point for the console application.
/*
 * App Is not well tested.
 * Created By Tomasz Głowacki
 *

*/

#include <iostream>

#include "wchar.h"

#include <QObject>
#include <QApplication>
#include <QPushButton>
#include <QProgressBar>
#include <QTabBar>
#include "window.h"
#include "mainwindow.h"
int main(int argc, char **argv)
{

    QApplication app(argc, argv);

    MainWindow mw;
    mw.show();

    return app.exec();

}

