#include "paintscene.h"
#include "square.h"
#include "romb.h"
#include "triangle.h"
#include <QFile>
#include <QTextStream>
#include <QColor>

paintScene::paintScene(QObject *parent) : QGraphicsScene(parent)
{
    tempFigure = nullptr;
    m_drawMode = ModeDraw;
    m_typeFigure = SquareType;
}

paintScene::~paintScene()
{

}

void paintScene::setPenColor(const QColor &color)
{
    penColor = color;
    setDrawMode(ModeDraw); // Switch to draw mode when color is selected
}

int paintScene::typeFigure() const
{
    return m_typeFigure;
}

void paintScene::setTypeFigure(const int type)
{
    m_typeFigure = type;
    setDrawMode(ModeFigure); // Switch to figure mode when figure is selected
}

void paintScene::setDrawMode(DrawMode mode)
{
    m_drawMode = mode;
}

paintScene::DrawMode paintScene::drawMode() const
{
    return m_drawMode;
}

void paintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_drawMode == ModeDraw) {
        // При нажатии кнопки мыши отрисовываем эллипс
        addEllipse(event->scenePos().x() - 5,
                   event->scenePos().y() - 5,
                   10,
                   10,
                   QPen(Qt::NoPen),
                   QBrush(penColor)); // Use the current pen color
        // Сохраняем координаты точки нажатия
        previousPoint = event->scenePos();
    } else if (m_drawMode == ModeFigure) {
        if (tempFigure) {
            removeItem(tempFigure);
            delete tempFigure;
            tempFigure = nullptr;
        }
        switch (m_typeFigure) {
        case SquareType:
            tempFigure = new Square(event->scenePos());
            break;
        case RombType:
            tempFigure = new Romb(event->scenePos());
            break;
        case TriangleType:
            tempFigure = new Triangle(event->scenePos());
            break;
        }
        if (tempFigure) {
            tempFigure->setStartPoint(event->scenePos());
            tempFigure->setEndPoint(event->scenePos());
            tempFigure->setPenColor(penColor);
            addItem(tempFigure);
        }
    }
}

void paintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_drawMode == ModeDraw) {
        // Отрисовываем линии с использованием предыдущей координаты
        addLine(previousPoint.x(),
                previousPoint.y(),
                event->scenePos().x(),
                event->scenePos().y(),
                QPen(penColor, 10, Qt::SolidLine, Qt::RoundCap)); // Use the current pen color
        // Обновляем данные о предыдущей координате
        previousPoint = event->scenePos();
    } else if (m_drawMode == ModeFigure && tempFigure) {
        tempFigure->setEndPoint(event->scenePos());
    }
}

void paintScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_drawMode == ModeFigure && tempFigure) {
        tempFigure->setEndPoint(event->scenePos());
        // Сохраняем фигуру в вектор и сбрасываем tempFigure
        figures.append(tempFigure);
        tempFigure = nullptr;
    }
}

// Сохранение фигур в файл
bool paintScene::saveFigures(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    QTextStream out(&file);
    for (Figure *fig : figures) {
        int type = -1;
        if (dynamic_cast<Square *>(fig)) type = SquareType;
        else if (dynamic_cast<Romb *>(fig)) type = RombType;
        else if (dynamic_cast<Triangle *>(fig)) type = TriangleType;
        QColor c = fig->WhatCa();
        out << type << " "
            << fig->startPoint().x() << " " << fig->startPoint().y() << " "
            << fig->endPoint().x() << " " << fig->endPoint().y() << " "
            << c.red() << " " << c.green() << " " << c.blue() << "\n";
    }
    return true;
}

// Загрузка фигур из файла
bool paintScene::loadFigures(const QString &filename)
{
    figures.clear();
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
    QTextStream in(&file);
    while (!in.atEnd()) {
        int type, r, g, b;
        qreal x1, y1, x2, y2;
        in >> type >> x1 >> y1 >> x2 >> y2 >> r >> g >> b;
        if (in.status() != QTextStream::Ok)
            break;
        Figure *fig = nullptr;
        QPointF p1(x1, y1), p2(x2, y2);
        switch (type) {
        case SquareType:
            fig = new Square(p1);
            break;
        case RombType:
            fig = new Romb(p1);
            break;
        case TriangleType:
            fig = new Triangle(p1);
            break;
        }
        if (fig) {
            fig->setStartPoint(p1);
            fig->setEndPoint(p2);
            fig->setPenColor(QColor(r, g, b));
            figures.append(fig);
            addItem(fig); // Добавить на сцену
        }
    }
    return true;
}
