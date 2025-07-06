#include "model.h"
#include <QString>
objModel::objModel(QVector<Comp> *data, QObject *parent) : QAbstractTableModel(parent), _comp(data)
{}

objModel::objModel():_comp(new QVector<Comp>()) {}

int objModel::rowCount([[maybe_unused]] const QModelIndex &parent) const
{
    return _comp->count();
}

int objModel::columnCount([[maybe_unused]] const QModelIndex &parent) const
{
    return 3;
}

QVariant objModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
    {
        return QVariant();
    }

    if(orientation == Qt::Horizontal)
    {
        switch(section)
        {
        case 0: return tr("Название");
        case 1: return tr("Секция");
        case 2: return tr("Цена");
        default: return QVariant();
        }
    }
    else
    {
        return QString("%1").arg(section + 1);//номер секции увеличивается на 1, отображение заголовка
    }

}

QVariant objModel::data(const QModelIndex &index, int role) const
{
    if(role != Qt::DisplayRole)
    {
        return QVariant();
    }

    switch(index.column())
    {
    case 0: return QString((*_comp)[index.row()].Name);
    case 1: return QString("%1").arg((*_comp)[index.row()].Section);
    case 2: return QString("%1").arg((*_comp)[index.row()].Price);
    default: return QVariant();
    }

    return QVariant();
}

void objModel::setModel(COMP<Comp> *comp)
{
    beginResetModel();
    _comp->clear();
    for (int i=0; i < comp->GetCount(); i++)
    {
        *_comp<<(comp->operator[](i));}
    endResetModel();
}

//------------------------------------

objModel2::objModel2(QVector<Bag> *data, QObject *parent) : QAbstractTableModel(parent), _bag(data)
{}

objModel2::objModel2():_bag(new QVector<Bag>()) {}

int objModel2::rowCount([[maybe_unused]] const QModelIndex &parent) const
{
    return _bag->count();
}

int objModel2::columnCount([[maybe_unused]] const QModelIndex &parent) const
{
    return 3;
}

QVariant objModel2::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
    {
        return QVariant();
    }

    if(orientation == Qt::Horizontal)
    {
        switch(section)
        {
        case 0: return tr("Название");
        case 1: return tr("Секция");
        case 2: return tr("Количество");
        default: return QVariant();
        }
    }
    else
    {
        return QString("%1").arg(section + 1);//номер секции увеличивается на 1, отображение заголовка
    }

}

QVariant objModel2::data(const QModelIndex &index, int role) const
{
    if(role != Qt::DisplayRole)
    {
        return QVariant();
    }

    switch(index.column())
    {
    case 0: return QString((*_bag)[index.row()].Name);
    case 1: return QString("%1").arg((*_bag)[index.row()].Section);
    case 2: return QString("%1").arg((*_bag)[index.row()].Count);
    default: return QVariant();
    }

    return QVariant();
}

void objModel2::setModel(COMP<Bag> *bag)
{
    beginResetModel();
    _bag->clear();
    for (int i=0; i < bag->GetCount(); i++)
    {
        *_bag<<(bag->operator[](i));}
    endResetModel();
}
