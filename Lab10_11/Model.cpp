#include "Model.h"
#include <qbrush.h>

int Model::rowCount(const QModelIndex& ) const {
	return cars.size();
}

int Model::columnCount(const QModelIndex& ) const {
	return 4;
}

QVariant Model::data(const QModelIndex& index, int role) const {

	if (role == Qt::DisplayRole) {
		Masina m = cars[index.row()];
		if( index.row() == 6)
			qDebug() << "SUNT LA : " << index.row() << " " << index.column() << "\n";
		switch(index.column()) {
			case 0:
				return QString::number(m.getNumar());
			case 1:
				return QString::fromStdString(m.getProducator());
			case 2:
				return QString::fromStdString(m.getModel());
			case 3:
				return QString::fromStdString(m.getTip());
		}
	}
	else if (role == Qt::BackgroundRole) {
		auto car = this->cars[index.row()];
		if (car.getTip() == "Limuzina") {
			return QBrush(Qt::darkMagenta);
		}
		if (car.getTip() == "Sport") {
			return QBrush(Qt::yellow);
		}
		if (car.getTip() == "Sedan") {
			return QBrush(Qt::cyan);
		}
		if (car.getTip() == "SUV") {
			return QBrush(Qt::darkGreen);
		}
	}
	return QVariant();
}

QVariant Model::headerData(int section, Qt::Orientation orientation, int role) const {
	if (role == Qt::DisplayRole) {
		if (orientation == Qt::Horizontal) {
			switch (section) {
				case 0:
					return QString("Numar de inmatriculare");
				case 1:
					return QString("Producator");
				case 2:
					return QString("Model");
				case 3:
					return QString("Tip");
			}
		}
		else {
			return QString("%1").arg(section);
		}
	}
	return QVariant();
}