#ifndef _LIFEWIDGET_H
#define _LIFEWIDGET_H

#include <QGLWidget>
#include <QTimer>
#include <QAction>

class LifeGame;
class QtHud;

class LifeWidget : public QGLWidget
{
	Q_OBJECT
	
public:
	LifeWidget(QWidget *parent = 0, int nbCases = 64);
	~LifeWidget();

	QSize sizeHint() const;

protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void updateSelection(QMouseEvent *event);
	void updateHud();
	void swapGameTable();
	
public slots:
	void toggleFullScreen(bool state);
	void toggleGrid(bool state);
	void computeNextGeneration();
	void clearGameTable();

signals:
	void nbLifeChanged(const int);

private:
	GLuint makeObject();
	GLuint object;
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
