#ifndef POINT4D_H
#define POINT4D_H

#include <ostream>

class Point4D {

public:

	Point4D();
	Point4D(double x, double y, double z, double t);

	double getCoord(int index) const;
	void setCoord(double value, int index);
	double dotProduct(const Point4D point) const;
	double distance(const Point4D point) const;
	void translate(const Point4D shift);
	void scale(double coef);
	void rotateX(double phi, double theta, double psi);
	void rotateXY(double phi, double theta);
	void rotateXYZ(double phi);
	void getAnglesX(double & phi, double & theta, double & psi) const;
	void getAnglesXY(double & phi, double & theta) const;
	void getAnglesXYZ(double & phi) const;

	friend std::ostream & operator << (std::ostream & out, Point4D & point);

protected:

	double coords[4];
};

#endif