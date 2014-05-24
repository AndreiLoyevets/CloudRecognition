#ifndef ELLIPSE4D_H
#define ELLIPSE4D_H

#include "Point4D.h"
#include "Matrix4D.h"
#include <vector>

class Ellipse4D {

public:

	Ellipse4D(std::vector<Point4D> data);
	bool contains(Point4D point);
	double distance(Point4D point);

protected:
	
	double mostDistantPoints(const std::vector<Point4D> & data, int & leftIndex, int & rightIndex) const;
	void shiftData(std::vector<Point4D> & data, Point4D point) const;
	void rotateDataX(std::vector<Point4D> & data, double phi, double theta, double psi) const;
	double mostDistantFromX(const std::vector<Point4D> & data, int & index) const;
	void rotateDataXY(std::vector<Point4D> & data, double phi, double theta) const;
	double mostDistantByY(const std::vector<Point4D> & data, Point4D source, int & index) const;
	double mostDistantFromXY(const std::vector<Point4D> & data, int & index) const;
	void rotateDataXYZ(std::vector<Point4D> & data, double phi) const;
	double mostDistantByZ(const std::vector<Point4D> & data, Point4D source, int & index) const;
	void mostDistantByT(const std::vector<Point4D> & data, int & leftIndex, int & rightIndex) const;
	Matrix4D getRotMatrix1(double phi, double theta, double psi) const;
	Matrix4D getRotMatrix2(double phi, double theta) const;
	Matrix4D getRotMatrix3(double phi) const;
	Matrix4D getScaleMatrix(Point4D leftX, Point4D rightX, Point4D leftY, Point4D rightY,
		                    Point4D leftZ, Point4D rightZ, Point4D leftT, Point4D rightT) const;
	double mostDistantFromCenter(const std::vector<Point4D> & data, int & index) const;
	void scaleData(std::vector<Point4D> & data, const Matrix4D & scaleMatrix) const;
	void showData(std::vector<Point4D> & data) const;

	// Ellipse equation: (Ax + b)'(Ax + b) <= 1
	Matrix4D A;
	Point4D b;
};

#endif