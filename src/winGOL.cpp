#include <QtGui>
#include "winGOL.h"

winGOL::winGOL(QWidget *parent):QWidget(parent)
{
	this->ui.setupUi(this);
	
	//chargement du style
	this->changeStyle("Plastique");
	
	//evenements
	QObject::connect(
		this->ui.btnQuit, SIGNAL(clicked()),
		this, SLOT(close()));
	QObject::connect(
		this->ui.btnNext, SIGNAL(clicked()),
		this->ui.wgtGOL, SLOT(computeNextGeneration()));
	QObject::connect(
		this->ui.btnClear, SIGNAL(clicked()),
		this->ui.wgtGOL, SLOT(clearGameTable()));
	QObject::connect(
		this->ui.wgtGOL, SIGNAL(nbLifeChanged(int)),
		this, SLOT(updateText(int)));
}

void winGOL::changeStyle(const QString &styleName)
{
	QApplication::setStyle(QStyleFactory::create(styleName));
	QApplication::setPalette(QApplication::style()->standardPalette());
}

void winGOL::updateText(const int nbr)
{
	char txt[128];
	sprintf(txt, "Nombre: %d", nbr);
	this->ui.txtNbLife->setText(txt);
}
