#include <QtGui>
#include <QtOpenGL>
#include <stdlib.h>

#include <math.h>

#include "lifeWidget.h"

#include "QtHud.h"

#include "engine/LifeGame.h"

LifeWidget::LifeWidget(QWidget *parent, int nbCases)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
	assert(nbCases);
	
	showGrid = true;
	
	refreshTimer.setSingleShot(false);
    connect(&refreshTimer, SIGNAL(timeout()), this, SLOT(update()));
    refreshTimer.start(15);

    setAttribute(Qt::WA_NoSystemBackground);
    setMinimumSize(320, 320);
    setWindowTitle("LifeGame");
	
	mouseX = 0.0;
	mouseY = 0.0;
	
	posX = 0;
	posY = 0;
	
	setMouseTracking(true);
	
	this->nbCases = nbCases;
	lifeGame = new LifeGame(this->nbCases);
	
	toggleFullScreenAction = new QAction(this);
	toggleFullScreenAction->setShortcutContext(Qt::ApplicationShortcut);
	toggleFullScreenAction->setCheckable(true);
	toggleFullScreenAction->setShortcut(Qt::Key_Return | Qt::AltModifier);
	connect(toggleFullScreenAction, SIGNAL(triggered(bool)),
			this, SLOT(toggleFullScreen(bool)));
	
	toggleGridAction = new QAction(this);
	toggleGridAction->setShortcutContext(Qt::ApplicationShortcut);
	toggleGridAction->setCheckable(true);
	toggleGridAction->setShortcut(Qt::Key_G | Qt::AltModifier);
	connect(toggleGridAction, SIGNAL(triggered(bool)),
			this, SLOT(toggleGrid(bool)));
	
	nextGenerationAction = new QAction(this);
	nextGenerationAction->setShortcutContext(Qt::ApplicationShortcut);
	nextGenerationAction->setShortcut(Qt::Key_Plus);
	connect(nextGenerationAction, SIGNAL(triggered()),
			this, SLOT(computeNextGeneration()));
	
	clearGameAction = new QAction(this);
	clearGameAction->setShortcutContext(Qt::ApplicationShortcut);
	clearGameAction->setShortcut(Qt::Key_Asterisk);
	connect(clearGameAction, SIGNAL(triggered()),
			this, SLOT(clearGameTable()));
	
	addAction(toggleFullScreenAction);
	addAction(toggleGridAction);
	addAction(nextGenerationAction);
	addAction(clearGameAction);
	
	gameHud = new QtHud(this);
	QFont font;
	font.setFamily("Lucida Console");
	font.setPixelSize(14);
	font.setBold(true);
	gameHud->setFont(font);
	gameHud->setForeColor(QColor::fromRgb(0, 255, 127));
}

LifeWidget::~LifeWidget()
{
    makeCurrent();
}

void LifeWidget::initializeGL()
{
}

void LifeWidget::mousePressEvent(QMouseEvent *event)
{
    updateSelection(event);
	
	if (event->buttons() & Qt::MidButton)
		gameHud->setVisible(!gameHud->isVisible());
	
	lastPos = event->pos();
}

void LifeWidget::mouseMoveEvent(QMouseEvent *event)
{
	int side = qMin(width(), height());
    mouseX = (float)(event->x() - (width()  - side)/2.) / (float)side;
    mouseY = (float)(event->y() - (height() - side)/2.) / (float)side;
	
	gameHud->setPosition(QPoint(event->x()+5, event->y()+5));
	
	updateSelection(event);
	
	lastPos = event->pos();
}

void LifeWidget::updateSelection(QMouseEvent *event)
{
	posX = int(mouseX * nbCases);
	posY = int(mouseY * nbCases);
	
	if (posX < 0) posX = 0;
	if (posX > nbCases-1) posX = nbCases-1;
	if (posY < 0) posY = 0;
	if (posY > nbCases-1) posY = nbCases-1;
	
	if (event->buttons() & Qt::LeftButton)
	{
		lifeGame->setAlive(posX, posY, true);
		emit nbLifeChanged(lifeGame->getNbLife());
	}
	if (event->buttons() & Qt::RightButton)
	{
		lifeGame->setAlive(posX, posY, false);
		emit nbLifeChanged(lifeGame->getNbLife());
	}
}

void LifeWidget::updateHud()
{
	char txt[64];
	sprintf(txt, "X = %5d\nY = %5d\nN = %5d", posX, posY, lifeGame->getNbLife());
	gameHud->setText(txt);
}

void LifeWidget::paintGL()
{
	float caseXmin, caseYmin, caseXmax, caseYmax;
	
	if ((mouseX <= 1.0) && (mouseX >= 0.0) && (mouseY <= 1.0) && (mouseY >= 0.0))
		setCursor(NULL);
	else
		setCursor(Qt::ArrowCursor);
	
	glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
	
	glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
	
	resizeGL(width(), height());
	
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
	
	glColor3f(0.0, 0.2, 0.8);
	glBegin(GL_QUADS);
		for (int i = 0; i < nbCases; i++)
			for (int j = 0; j < nbCases; j++)
				if (lifeGame->isAlive(i, j))
				{
					caseXmin =(float)i / (float)nbCases;
					caseXmax =(float)(i + 1) / (float)nbCases;
					caseYmin =(float)j / (float)nbCases;
					caseYmax =(float)(j + 1) / (float)nbCases;
				
					glVertex3f(caseXmin, caseYmin, -0.1);
					glVertex3f(caseXmin, caseYmax, -0.1);
					glVertex3f(caseXmax, caseYmax, -0.1);
					glVertex3f(caseXmax, caseYmin, -0.1);
				}
	glEnd();
	
	if (showGrid)
	{
		glColor3f(0.5, 0.5, 0.5);
		glBegin(GL_LINES);
			for (int i = 0; i <= nbCases; i++)
			{
			float j = (float)i / (float)nbCases;
				
				glVertex3f(0.0, j, -0.05);
				glVertex3f(1.0, j, -0.05);
			
				glVertex3f(j, 0.0, -0.05);
				glVertex3f(j, 1.0, -0.05);
			}
		glEnd();
	}
		
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
		caseXmin =(float)posX / (float)nbCases;
		caseXmax =(float)(posX + 1) / (float)nbCases;
		caseYmin =(float)posY / (float)nbCases;
		caseYmax =(float)(posY + 1) / (float)nbCases;
		
		glVertex3f(caseXmin, caseYmin, -0.02);
		glVertex3f(caseXmin, caseYmax, -0.02);
		glVertex3f(caseXmax, caseYmax, -0.02);
		glVertex3f(caseXmax, caseYmin, -0.02);
	glEnd();
	
	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_LINES);
		glVertex3f(mouseX - 0.01, mouseY, -0.01);
		glVertex3f(mouseX - 0.0025, mouseY, -0.01);
		glVertex3f(mouseX + 0.01, mouseY, -0.01);
		glVertex3f(mouseX + 0.0025, mouseY, -0.01);
		glVertex3f(mouseX, mouseY - 0.01, -0.01);
		glVertex3f(mouseX, mouseY - 0.0025, -0.01);
		glVertex3f(mouseX, mouseY + 0.01, -0.01);
		glVertex3f(mouseX, mouseY + 0.0025, -0.01);
	glEnd();
	
	glFlush();
	
	glPopAttrib();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}

void LifeWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);
	
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-0.001, 1.001, 1.001, -0.001, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

void LifeWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter;
    painter.begin(this);
	
	paintGL();

	painter.setRenderHint(QPainter::Antialiasing);

	updateHud();
	gameHud->draw(&painter);

	painter.end();
}

QSize LifeWidget::sizeHint() const
{
    return QSize(640, 640);
}

void LifeWidget::toggleFullScreen(bool state)
{
	if (state)
		setWindowState(Qt::WindowFullScreen);
	else
		setWindowState(Qt::WindowNoState);
}

void LifeWidget::toggleGrid(bool state)
{
	showGrid = !state;
}

void LifeWidget::computeNextGeneration()
{
	lifeGame->computeNextGeneration();
	emit nbLifeChanged(lifeGame->getNbLife());
}

void LifeWidget::clearGameTable()
{
	lifeGame->endOfLife();
	emit nbLifeChanged(lifeGame->getNbLife());
}
