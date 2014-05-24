#include "Point4D.h"
#include <exception>

#define _USE_MATH_DEFINES
#include <math.h>

Point4D::Point4D() {
	for (int i = 0; i < 4; ++i) {
		coords[i] = 0.0;
	}
}

Point4D::Point4D(double x, double y, double z, double t) {
	coords[0] = x;
	coords[1] = y;
	coords[2] = z;
	coords[3] = t;
}

double Point4D::getCoord(int index) const {
	if (index < 0 || index > 3) {
		throw std::exception("Wrong coordinate index", index);
	} else {
		return coords[index];
	}
}

void Point4D::setCoord(double value, int index) {
	if (index < 0 || index > 3) {
		throw std::exception("Wrong coordinate index", index);
	} else {
		coords[index] = value;
	}
}

double Point4D::dotProduct(const Point4D point) const {
	double product = 0.0;

	for (int i = 0; i < 4; ++i) {
		product += coords[i] * point.coords[i];
	}

	return product;
}

double Point4D::distance(const Point4D point) const {
	double sumOfSquares = 0.0;

	for (int i = 0; i < 4; ++i) {
		sumOfSquares += pow(coords[i] - point.coords[i], 2.0);
	}

	return sqrt(sumOfSquares);
}

void Point4D::translate(const Point4D shift) {
	for (int i = 0; i < 4; ++i) {
		coords[i] += shift.coords[i];
	}
}

void Point4D::scale(double coef) {
	for (int i = 0; i < 4; ++i) {
		coords[i] *= coef;
	}
}

void Point4D::rotateX(double phi, double theta, double psi) {
	double x, y, z, t;

	// Split into 3 rotations.
	// Rxy
	x = coords[0];
	y = coords[1];
	coords[0] = x * cos(phi) + y * sin(phi);
	coords[1] = -x * sin(phi) + y * cos(phi);

	// Rxz
	x = coords[0];
	z = coords[2];
	coords[0] = x * cos(theta) + z * sin(theta);
	coords[2] = -x * sin(theta) + z * cos(theta);

	// Rxt
	x = coords[0];
	t = coords[3];
	coords[0] = x * cos(psi) + t * sin(psi);
	coords[3] = -x * sin(psi) + t * cos(psi);
}

void Point4D::rotateXY(double phi, double theta) {
	double y, z, t;

	// Split into 2 rotations.
	// Ryz
	y = coords[1];
	z = coords[2];
	coords[1] = y * cos(phi) + z * sin(phi);
	coords[2] = -y * sin(phi) + z * cos(phi);

	// Ryt
	y = coords[1];
	t = coords[3];
	coords[1] = y * cos(theta) + t * sin(theta);
	coords[3] = -y * sin(theta) + t * cos(theta);
}

void Point4D::rotateXYZ(double phi) {
	double z, t;

	z = coords[2];
	t = coords[3];
	coords[2] = z * cos(phi) + t * sin(phi);
	coords[3] = -z * sin(phi) + t * cos(phi);
}

void Point4D::getAnglesX(double & phi, double & theta, double & psi) const {
	if (coords[0] >= 0) {
		phi = atan(coords[1] / coords[0]);
	} else {
		phi = atan(coords[1] / coords[0]) + M_PI;
	}

	theta = atan(coords[2] * sin(phi) / coords[1]);
	psi = atan(coords[3] * sin(theta) / coords[2]);
}

void Point4D::getAnglesXY(double & phi, double & theta) const {
	if (coords[1] >= 0) {
		phi = atan(coords[2] / coords[1]);
	} else {
		phi = atan(coords[2] / coords[1]) + M_PI;
	}

	theta = atan(coords[3] * sin(phi) / coords[2]);
}

void Point4D::getAnglesXYZ(double & phi) const {
	if (coords[2] >= 0) {
		phi = atan(coords[3] / coords[2]);
	} else {
		phi = atan(coords[3] / coords[2]) + M_PI;
	}
}

std::ostream & operator << (std::ostream & out, Point4D & point)
{
	out << "(" << point.coords[0] << ", " <<
		point.coords[1] << ", " <<point.coords[2] << ", " <<point.coords[3] << ")";

    return out;
}