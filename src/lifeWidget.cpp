#include <QtWidgets>
#include <cassert>

#include "lifeWidget.h"

#include "QtHud.h"

#include "engine/LifeGame.h"

LifeWidget::LifeWidget(QWidget *parent, int nbCases)
    : QWidget(parent)
{
	assert(nbCases);
	
	showGrid = true;
	
	refreshTimer.setSingleShot(false);
    connect(&refreshTimer, SIGNAL(timeout()), this, SLOT(update()));
    refreshTimer.start(15);

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
	toggleFullScreenAction->setShortcut(QKeySequence(Qt::ALT | Qt::Key_Return));
	connect(toggleFullScreenAction, SIGNAL(triggered(bool)),
			this, SLOT(toggleFullScreen(bool)));
	
	toggleGridAction = new QAction(this);
	toggleGridAction->setShortcutContext(Qt::ApplicationShortcut);
	toggleGridAction->setCheckable(true);
	toggleGridAction->setShortcut(QKeySequence(Qt::ALT | Qt::Key_G));
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
	delete lifeGame;
}

void LifeWidget::mousePressEvent(QMouseEvent *event)
{
    updateSelection(event);
	
	if (event->buttons() & Qt::MiddleButton)
		gameHud->setVisible(!gameHud->isVisible());
	
	lastPos = event->position().toPoint();
}

void LifeWidget::mouseMoveEvent(QMouseEvent *event)
{
	int side = qMin(width(), height());
	const QPointF pos = event->position();
    mouseX = (float)(pos.x() - (width()  - side)/2.) / (float)side;
    mouseY = (float)(pos.y() - (height() - side)/2.) / (float)side;
	
	gameHud->setPosition(QPoint(pos.x()+5, pos.y()+5));
	
	updateSelection(event);
	
	lastPos = event->position().toPoint();
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
	gameHud->setText(QString("X = %1\nY = %2\nN = %3")
		.arg(posX, 5).arg(posY, 5).arg(lifeGame->getNbLife(), 5));
}

void LifeWidget::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.fillRect(rect(), Qt::black);
	
	if ((mouseX <= 1.0) && (mouseX >= 0.0) && (mouseY <= 1.0) && (mouseY >= 0.0))
		unsetCursor();
	else
		setCursor(Qt::ArrowCursor);
	
	const int side = qMin(width(), height());
	painter.save();
	painter.translate((width() - side) / 2.0, (height() - side) / 2.0);
	painter.scale(side / 1.002, side / 1.002);
	painter.translate(0.001, 0.001);
	painter.setRenderHint(QPainter::Antialiasing);
	
	const double cell = 1.0 / nbCases;
	
	painter.setPen(Qt::NoPen);
	painter.setBrush(QColor::fromRgbF(0.0, 0.2, 0.8));
	for (int i = 0; i < nbCases; i++)
		for (int j = 0; j < nbCases; j++)
			if (lifeGame->isAlive(i, j))
				painter.drawRect(QRectF(i * cell, j * cell, cell, cell));
	
	painter.setBrush(Qt::NoBrush);
	if (showGrid)
	{
		QPen pen(QColor::fromRgbF(0.5, 0.5, 0.5));
		pen.setCosmetic(true);
		painter.setPen(pen);
		for (int i = 0; i <= nbCases; i++)
		{
			const double j = i * cell;
			painter.drawLine(QPointF(0.0, j), QPointF(1.0, j));
			painter.drawLine(QPointF(j, 0.0), QPointF(j, 1.0));
		}
	}
	
	QPen selection(Qt::red);
	selection.setCosmetic(true);
	painter.setPen(selection);
	painter.drawRect(QRectF(posX * cell, posY * cell, cell, cell));
	
	QPen cross(Qt::cyan);
	cross.setCosmetic(true);
	painter.setPen(cross);
	painter.drawLine(QPointF(mouseX - 0.01, mouseY), QPointF(mouseX - 0.0025, mouseY));
	painter.drawLine(QPointF(mouseX + 0.01, mouseY), QPointF(mouseX + 0.0025, mouseY));
	painter.drawLine(QPointF(mouseX, mouseY - 0.01), QPointF(mouseX, mouseY - 0.0025));
	painter.drawLine(QPointF(mouseX, mouseY + 0.01), QPointF(mouseX, mouseY + 0.0025));
	painter.restore();
	
	updateHud();
	gameHud->draw(&painter);
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
