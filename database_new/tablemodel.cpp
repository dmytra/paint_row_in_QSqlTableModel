#include "tablemodel.h"
#include <QColor>

TableModel::TableModel(QObject *parent) : QSqlTableModel(parent)
{

}

QVariant TableModel::data(const QModelIndex &idx, int role) const
{
    if(role == Qt::BackgroundColorRole){
        if(QSqlTableModel::data(this->index(idx.row(), 3)).toInt() >= 100 && QSqlTableModel::data(this->index(idx.row(), 3)).toInt() <= 200){
            return QColor(Qt::red);
        }
        else if(QSqlTableModel::data(this->index(idx.row(), 3)).toInt() <= 100 && QSqlTableModel::data(this->index(idx.row(), 3)).toInt() >= 50){
            return QColor(Qt::green);
        }
        else if(QSqlTableModel::data(this->index(idx.row(), 3)).toInt() >= 200){
            return QColor(Qt::blue);
        }
    } else if(role == Qt::DisplayRole){
        return QSqlTableModel::data(idx);
    }
    return QVariant();
}
