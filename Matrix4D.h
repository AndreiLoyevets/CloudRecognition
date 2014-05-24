#ifndef MATRIX4D_H
#define MATRIX4D_H

#include "Point4D.h"

class Matrix4D {

public:

	Matrix4D(); // identity matrix

	double getElem(int i, int j) const;
	void setElem(double value, int i, int j);
	Point4D product(const Point4D & point) const;
	Matrix4D product(const Matrix4D & matrix) const;

protected:

	Point4D rows[4];
};

#endif