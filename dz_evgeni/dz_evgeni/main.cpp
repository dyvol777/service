#include "WelcomeWindow.h"
#include <QtWidgets/QApplication>

#include "Pancer.h"
deque<char> tree::tempOutput;
int tree::biggestLevel = 0;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WelcomeWindow w;
    w.show();
    return a.exec();
}
