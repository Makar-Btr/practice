#ifndef MODEL_H
#define MODEL_H

#include <QAbstractTableModel>
#include "comp.h"


class objModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    objModel(QVector<Comp> *comp, QObject *parent = nullptr);
    objModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    //Возвращает количество строк для отображения в таблице

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    //Возвращает количество столбцов таблицы

    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    //Предоставляет заголовки для столбцов и строк таблицы

    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const override;
    //Возвращает данные для конкретной ячейки таблицы в зависимости от роли

    void setModel(COMP<Comp>* comp);
    //Обновляет данные модели

protected:
    QVector<Comp> *_comp;
};

class objModel2 : public QAbstractTableModel
{
    Q_OBJECT
public:
    objModel2(QVector<Bag> *bag, QObject *parent = nullptr);
    objModel2();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void setModel(COMP<Bag>* bag);
protected:
    QVector<Bag> *_bag;
};

#endif // MODEL_H
