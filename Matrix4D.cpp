#include "Matrix4D.h"

Matrix4D::Matrix4D() {
	for (int i = 0; i < 4; ++i) {
		rows[i].setCoord(1.0, i);
	}
}

double Matrix4D::getElem(int i, int j) const {
	if (i < 0 || i > 3 || j < 0 || j > 3) {
		throw std::exception("Wrong matrix coordinates");
	} else {
		return rows[i].getCoord(j);
	}
}

void Matrix4D::setElem(double value, int i, int j) {
	if (i < 0 || i > 3 || j < 0 || j > 3) {
		throw std::exception("Wrong matrix coordinates");
	} else {
		rows[i].setCoord(value, j);
	}
}

Point4D Matrix4D::product(const Point4D & point) const {
	Point4D result;

	for (int i = 0; i < 4; ++i) {
		result.setCoord(rows[i].dotProduct(point), i);
	}

	return result;
}

Matrix4D Matrix4D::product(const Matrix4D & matrix) const {
	Matrix4D result;
	double value;

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			value = 0.0;
			for (int k = 0; k < 4; ++k) {
				value += rows[i].getCoord(k) * matrix.getElem(k, j);
			}

			result.setElem(value, i, j);
		}
	}

	return result;
}