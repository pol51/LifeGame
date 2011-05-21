#include <QtGui/QPainter>
#include <QtGui/QImage>

#include "QtHud.h"

QtHud::QtHud(QObject *parent)
  : QObject(parent)
{
  _image = NULL;
  _textAlignment = Qt::AlignLeft;
  _foreColor = Qt::white;
  _backColor = QColor::fromRgb(0, 0, 0, 95);	//semi-transparent
  _position.setX(0);
  _position.setY(0);
  _size.setHeight(0);
  _size.setWidth(0);
  _autoSize = true;
  _border = 4;
  _visible = false;
  _updatable = true;
}

QtHud::~QtHud()
{
  if (_image)
    delete _image;
}

const QString & QtHud::getText() const
{
  return _text;
}

void QtHud::setText(QString value)
{
  _text = value;
  _updatable = true;
}

const int QtHud::getTextAlignment() const
{
  return _textAlignment;
}

void QtHud::setTextAlignment(int value)
{
  _textAlignment = value;
  _updatable = true;
}

const QFont & QtHud::getFont() const
{
  return _font;
}

void QtHud::setFont(QFont value)
{
  _font = value;
  _updatable = true;
}

const QColor & QtHud::getForeColor() const
{
  return _foreColor;
}

void QtHud::setForeColor(QColor value)
{
  _foreColor = value;
  _updatable = true;
}

const QColor & QtHud::getBackColor() const
{
  return _backColor;
}

void QtHud::setBackColor(QColor value)
{
  _backColor = value;
  _updatable = true;
}

const QPoint & QtHud::getPosition() const
{
  return _position;
}

void QtHud::setPosition(QPoint value)
{
  _position = value;
}

const QSize & QtHud::getSize() const
{
  return _size;
}

void QtHud::setSize(QSize value)
{
  _size = value;
  _updatable = true;
}

const bool QtHud::isAutoSize() const
{
  return _autoSize;
}

void QtHud::setAutoSize(bool value)
{
  _autoSize = value;
  _updatable = true;
}

const int QtHud::getBorder() const
{
  return _border;
}

void QtHud::setBorder(int value)
{
  _border = value;
  _updatable = true;
}

const bool QtHud::isVisible() const
{
  return _visible;
}

void QtHud::setVisible(bool value)
{
  _visible = value;
}

void QtHud::updateImage()
{
  if (!_updatable)
    return;

  QSize size;
  int width = 0, height = 0;

  if (_image)
    size = _image->size();

  if (_autoSize)
  {
    QFontMetrics metrics = QFontMetrics(_font);
    QRect rect = metrics.boundingRect(0, 0, 5000, 5000,
              _textAlignment, _text);
    _size = rect.size() + 2 * QSize(_border, _border);
  }

  if (size != _size)
  {
    delete _image;
    _image = new QImage(_size, QImage::Format_ARGB32_Premultiplied);
  }

  if (_image)
  {
    _image->fill(_backColor.rgba());

    QPainter painter;
    painter.begin(_image);
    painter.setRenderHint(QPainter::TextAntialiasing);
    painter.setPen(_foreColor.rgba());
    painter.setFont(_font);
    painter.drawText(_border, _border, _image->width() - _border,
                _image->height() - _border, _textAlignment, _text);
    painter.end();
  }

  _updatable = false;
}

void QtHud::draw(QPainter* painter)
{
  if (painter && true)
  {
    updateImage();
    painter->drawImage(_position, *_image);
  }
}
