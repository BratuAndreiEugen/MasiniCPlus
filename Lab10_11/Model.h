#pragma once
#include <QAbstractTableModel>
#include <vector>
#include "Masina.h"
#include <qdebug.h>

class Model: public QAbstractTableModel
{
	std::vector<Masina> cars;
public:
	Model(QObject* parent, const std::vector<Masina>& m) : QAbstractTableModel(parent), cars{ m } {};

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;

	int columnCount(const QModelIndex& parent = QModelIndex()) const override;

	bool removeRows(int position, int rows, const QModelIndex& parent)
	{
		beginRemoveRows(QModelIndex(), position, position + rows - 1);

		endRemoveRows();
		return true;
	}
	bool insertRows(int position, int rows, const QModelIndex& parent)
	{
		beginInsertRows(QModelIndex(), position, position + rows - 1);

		endInsertRows();
		return true;
	}


	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

	void setCars(const std::vector<Masina>& v) {
		int oldSize = this->cars.size();
		this->cars = v;
		qDebug() << "CARS SIZE : " << cars.size() << " " << rowCount() << "\n";
		auto topLeft = createIndex(0, 0);
		auto bottomRight = createIndex(rowCount(), columnCount());

		/*
		int crrSize = this->cars.size();
		for (int i = oldSize; i < crrSize; i++)
		{
			this->insertRow(rowCount());
		}*/
		/*
		if (crrSize < oldSize)
		{
			while(oldSize != crrSize)
			{
				this->removeRows(oldSize - 1, 1, QModelIndex());
				oldSize--;
			}
		}
		*/
		emit dataChanged(topLeft, bottomRight);
		/// !!!!
		emit layoutChanged();
	}
};

