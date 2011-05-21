#ifndef __WINGOL_H
#define __WINGOL_H
#include "ui_GOL.h"

class winGOL : public QWidget
{
	Q_OBJECT
	private:
		Ui_GOL ui;
		QPalette originalPalette;
	public:
		winGOL(QWidget *parent = 0);
	public slots:
		void changeStyle(const QString &styleName);
		void updateText(const int nbr);
};

#endif
