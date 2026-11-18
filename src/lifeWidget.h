#ifndef _LIFEWIDGET_H
#define _LIFEWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QAction>

class LifeGame;
class QtHud;

class LifeWidget : public QWidget
{
	Q_OBJECT
	
public:
	LifeWidget(QWidget *parent = nullptr, int nbCases = 64);
	~LifeWidget();

	QSize sizeHint() const;

protected:
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void updateSelection(QMouseEvent *event);
	void updateHud();
	
public slots:
	void toggleFullScreen(bool state);
	void toggleGrid(bool state);
	void computeNextGeneration();
	void clearGameTable();

signals:
	void nbLifeChanged(const int);

private:
	QPoint lastPos;
	QTimer refreshTimer;
	QAction *toggleFullScreenAction;
	QAction *toggleGridAction;
	QAction *nextGenerationAction;
	QAction *clearGameAction;

	QtHud *gameHud;
	
	LifeGame *lifeGame;
	int nbCases;
	
	float mouseX;
	float mouseY;
	bool showGrid;
	int posX;
	int posY;
};

#endif
