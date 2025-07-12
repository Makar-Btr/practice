#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QDebug>
#include <QVector>
#include <QString>

#include "figure.h"

class paintScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit paintScene(QObject *parent = 0);
    ~paintScene();

    void setPenColor(const QColor &color);

    int typeFigure() const;
    void setTypeFigure(const int type);

    enum DrawMode
    {
        ModeDraw,
        ModeFigure
    };
    enum FigureTypes
    {
        SquareType,
        RombType,
        TriangleType
    };

    void setDrawMode(DrawMode mode);
    DrawMode drawMode() const;

    bool saveFigures(const QString &filename);
    bool loadFigures(const QString &filename);

    QVector<Figure *> figures;

signals:
    void typeFigureChanged();

private:
    QPointF previousPoint;
    QColor penColor = Qt::red;

    Figure *tempFigure;
    int m_typeFigure;
    DrawMode m_drawMode = ModeDraw;

private:
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // PAINTSCENE_H
