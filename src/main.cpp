#include <QApplication>
#include "winGOL.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
    winGOL gameWindow;
	gameWindow.show();
	
    return app.exec();
}
