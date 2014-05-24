#include "Ellipse4D.h"
#include <iostream>

Ellipse4D::Ellipse4D(std::vector<Point4D> data) {

	// determine the most distant points
	int leftX, rightX;
	double maxDistance = mostDistantPoints(data, leftX, rightX);

	// shift data so that data[leftIndex] is at the beginning
	Point4D shift = data[leftX];
	shift.scale(-1.0);
	shiftData(data, shift);

	// put data[rightIndex] on the X axis
	double phi, theta, psi;
	data[rightX].getAnglesX(phi, theta, psi);
	Matrix4D rotations1 = getRotMatrix1(phi, theta, psi);
	rotateDataX(data, phi, theta, psi);

	// find the most distant point from X
	int leftY;
	mostDistantFromX(data, leftY);

	// put data[index] on XY
	data[leftY].getAnglesXY(phi, theta);
	Matrix4D rotations2 = getRotMatrix2(phi, theta);
	rotateDataXY(data, phi, theta);

	// find another most distant point from X on XY
	int rightY;
	mostDistantByY(data, data[leftY], rightY);

	// find the most distant point from XY
	int leftZ;
	mostDistantFromXY(data, leftZ);

	// put data[leftZ] on XYZ
	data[leftZ].getAnglesXYZ(phi);
	Matrix4D rotations3 = getRotMatrix3(phi);
	rotateDataXYZ(data, phi);

	// find another most distant point on XYZ
	int rightZ;
	mostDistantByZ(data, data[leftZ], rightZ);

	// find leftT and rightT
	int leftT, rightT;
	mostDistantByT(data, leftT, rightT);

	// calculate the center of the cube
	Point4D minusCenter;
	minusCenter.setCoord(-(data[leftX].getCoord(0) + data[rightX].getCoord(0)) / 2.0, 0);
	minusCenter.setCoord(-(data[leftY].getCoord(1) + data[rightY].getCoord(1)) / 2.0, 1);
	minusCenter.setCoord(-(data[leftZ].getCoord(2) + data[rightZ].getCoord(2)) / 2.0, 2);
	minusCenter.setCoord(-(data[leftT].getCoord(3) + data[rightT].getCoord(3)) / 2.0, 3);

	// calculate matrix D (scale matrix)
	Matrix4D scaleMatrix = getScaleMatrix(data[leftX], data[rightX], data[leftY], data[rightY],
		                                  data[leftZ], data[rightZ], data[leftT], data[rightT]);

	// calculate matrix R (rotations matrix)
	Matrix4D rotationsMatrix = rotations3.product(rotations2.product(rotations1));

	// shift data to center
	shiftData(data, minusCenter);

	// scale data
	scaleData(data, scaleMatrix);

	// find the most distant point from the center
	int maxIndex;
	double radius = mostDistantFromCenter(data, maxIndex);

	// recompute scale matrix
	for (int i = 0; i < 4; ++i) {
		scaleMatrix.setElem(scaleMatrix.getElem(i, i) / radius, i, i);
	}

	// calculate matrix A for ellipse equation
	A = scaleMatrix.product(rotationsMatrix);

	// calculate vector b
	b = rotationsMatrix.product(shift);
	b.translate(minusCenter);
	b = scaleMatrix.product(b);
}

bool Ellipse4D::contains(Point4D point) {
	if (distance(point) <= 1.000001) {
		return true;
	} else {
		return false;
	}
}

double Ellipse4D::distance(Point4D point) {
	Point4D transformed = A.product(point);
	transformed.translate(b);

	return transformed.dotProduct(transformed);
}

double Ellipse4D::mostDistantPoints(const std::vector<Point4D> & data, int & leftIndex, int & rightIndex) const {
	leftIndex = -1;
	rightIndex = -1;
	double maxDistance = -1.0, tempDist;

	for (int i = 0; i < data.size(); ++i) {
		for (int j = 0; j < data.size(); ++j) {
			tempDist = data[i].distance(data[j]);
			if (tempDist > maxDistance) {
				maxDistance = tempDist;
				leftIndex = i;
				rightIndex = j;
			}
		}
	}

	return maxDistance;
}

void Ellipse4D::shiftData(std::vector<Point4D> & data, Point4D point) const {
	for (int i = 0; i < data.size(); ++i) {
		data[i].translate(point);
	}
}

void Ellipse4D::rotateDataX(std::vector<Point4D> & data, double phi, double theta, double psi) const {
	for (int i = 0; i < data.size(); ++i) {
		data[i].rotateX(phi, theta, psi);
	}
}

double Ellipse4D::mostDistantFromX(const std::vector<Point4D> & data, int & index) const {
	double maxDistance = -1.0, tempDist;

	for (int i = 0; i < data.size(); ++i) {
		Point4D projectionX;
		projectionX.setCoord(data[i].getCoord(0), 0);
		tempDist = data[i].distance(projectionX);
		if (tempDist > maxDistance) {
			maxDistance = tempDist;
			index = i;
		}
	}

	return maxDistance;
}

void Ellipse4D::rotateDataXY(std::vector<Point4D> & data, double phi, double theta) const {
	for (int i = 0; i < data.size(); ++i) {
		data[i].rotateXY(phi, theta);
	}
}

double Ellipse4D::mostDistantByY(const std::vector<Point4D> & data, Point4D source, int & index) const {
	index = -1;
	double maxDist = -1.0, tempDist;

	for (int i = 0; i < data.size(); ++i) {
		tempDist = abs(data[i].getCoord(1) - source.getCoord(1));
		if (tempDist > maxDist) {
			maxDist = tempDist;
			index = i;
		}
	}

	return maxDist;
}

double Ellipse4D::mostDistantFromXY(const std::vector<Point4D> & data, int & index) const {
	double maxDistance = -1.0, tempDist;

	for (int i = 0; i < data.size(); ++i) {
		Point4D projectionXY;
		projectionXY.setCoord(data[i].getCoord(0), 0);
		projectionXY.setCoord(data[i].getCoord(1), 1);
		tempDist = data[i].distance(projectionXY);
		if (tempDist > maxDistance) {
			maxDistance = tempDist;
			index = i;
		}
	}

	return maxDistance;
}

void Ellipse4D::rotateDataXYZ(std::vector<Point4D> & data, double phi) const {
	for (int i = 0; i < data.size(); ++i) {
		data[i].rotateXYZ(phi);
	}
}

double Ellipse4D::mostDistantByZ(const std::vector<Point4D> & data, Point4D source, int & index) const {
	index = -1;
	double maxDist = -1.0, tempDist;

	for (int i = 0; i < data.size(); ++i) {
		tempDist = abs(data[i].getCoord(2) - source.getCoord(2));
		if (tempDist > maxDist) {
			maxDist = tempDist;
			index = i;
		}
	}

	return maxDist;
}

void Ellipse4D::mostDistantByT(const std::vector<Point4D> & data, int & leftIndex, int & rightIndex) const {
	leftIndex = 0;
	rightIndex = 0;
	double minT = data[0].getCoord(3), maxT = minT, tempT;

	for (int i = 1; i < data.size(); ++i) {
		tempT = data[i].getCoord(3);
		if (tempT < minT) {
			minT = tempT;
			leftIndex = i;
		} else if (tempT > maxT) {
			maxT = tempT;
			rightIndex = i;
		}
	}
}

Matrix4D Ellipse4D::getRotMatrix1(double phi, double theta, double psi) const {
	Matrix4D Rxy;
	Rxy.setElem(cos(phi), 0, 0);
	Rxy.setElem(cos(phi), 1, 1);
	Rxy.setElem(sin(phi), 0, 1);
	Rxy.setElem(-sin(phi), 1, 0);

	Matrix4D Rxz;
	Rxz.setElem(cos(theta), 0, 0);
	Rxz.setElem(cos(theta), 2, 2);
	Rxz.setElem(sin(theta), 0, 2);
	Rxz.setElem(-sin(theta), 2, 0);

	Matrix4D Rxt;
	Rxt.setElem(cos(psi), 0, 0);
	Rxt.setElem(cos(psi), 3, 3);
	Rxt.setElem(sin(psi), 0, 3);
	Rxt.setElem(-sin(psi), 3, 0);

	return Rxt.product(Rxz.product(Rxy));
}

Matrix4D Ellipse4D::getRotMatrix2(double phi, double theta) const {
	Matrix4D Ryz;

	Ryz.setElem(cos(phi), 1, 1);
	Ryz.setElem(cos(phi), 2, 2);
	Ryz.setElem(sin(phi), 1, 2);
	Ryz.setElem(-sin(phi), 2, 1);

	Matrix4D Ryt;
	Ryt.setElem(cos(theta), 1, 1);
	Ryt.setElem(cos(theta), 3, 3);
	Ryt.setElem(sin(theta), 1, 3);
	Ryt.setElem(-sin(theta), 3, 1);

	return Ryt.product(Ryz);
}

Matrix4D Ellipse4D::getRotMatrix3(double phi) const {
	Matrix4D Rzt;

	Rzt.setElem(cos(phi), 2, 2);
	Rzt.setElem(cos(phi), 3, 3);
	Rzt.setElem(sin(phi), 2, 3);
	Rzt.setElem(-sin(phi), 3, 2);

	return Rzt;
}

Matrix4D Ellipse4D::getScaleMatrix(Point4D leftX, Point4D rightX, Point4D leftY, Point4D rightY,
		                           Point4D leftZ, Point4D rightZ, Point4D leftT, Point4D rightT) const {
	Matrix4D scaleMatrix;

	scaleMatrix.setElem(2.0 / abs(rightX.getCoord(0) - leftX.getCoord(0)), 0, 0);
	scaleMatrix.setElem(2.0 / abs(rightY.getCoord(1) - leftY.getCoord(1)), 1, 1);
	scaleMatrix.setElem(2.0 / abs(rightZ.getCoord(2) - leftZ.getCoord(2)), 2, 2);
	scaleMatrix.setElem(2.0 / abs(rightT.getCoord(3) - leftT.getCoord(3)), 3, 3);

	return scaleMatrix;
}

void Ellipse4D::scaleData(std::vector<Point4D> & data, const Matrix4D & scaleMatrix) const {
	for (int i = 0; i < data.size(); ++i) {
		data[i] = scaleMatrix.product(data[i]);
	}
}

double Ellipse4D::mostDistantFromCenter(const std::vector<Point4D> & data, int & index) const {
	double maxDist = 0.0, tempDist;
	Point4D center;

	for (int i = 0; i < data.size(); ++i) {
		tempDist = data[i].distance(center);
		if (tempDist > maxDist) {
			maxDist = tempDist;
			index = i;
		}
	}

	return maxDist;
}

void Ellipse4D::showData(std::vector<Point4D> & data) const {
	for (int i = 0; i < data.size(); ++i) {
		std::cout<<data[i]<<std::endl;
	}
}