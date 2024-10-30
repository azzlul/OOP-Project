#pragma once
#include "GUI.h"
#include "QAbstractTableModel"

class TableModel:public QAbstractTableModel{
private:
    vector<Film> films;
public:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override
    {
        return films.size();
    }
    int columnCount(const QModelIndex &parent = QModelIndex()) const override
    {
        return 4;
    }
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override
    {
        int row = index.row();
        if(role == Qt::DisplayRole)
        {
            switch (index.column())
            {
                case 0:
                    return QString::fromStdString(films[row].getTitle());
                case 1:
                    return QString::fromStdString(films[row].getGenre());
                case 2:
                    return QString::number(films[row].getYear());
                case 3:
                    return QString::fromStdString(films[row].getActor());
            }
        }
        return {};
    }

    void reload(const vector<Film>& list)
    {
        emit layoutAboutToBeChanged();
        films = list;
        emit layoutChanged();
    }
};