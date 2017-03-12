/*
 * Point.cpp
 *
 *  Created on: 24 Jan 2017
 *      Author: Dave
 */

#include <iostream>
#include <cmath>
#include "Point.h"

Point::Point() {

	#if VERBOSE
	std::cout << "Default Constructor" << std::endl;
	#endif

	x_coord = 0;
	y_coord = 0;	
}

Point::Point(double x, double y) {

	#if VERBOSE
		std::cout << "Custom Constructor" << std::endl;
	#endif

	x_coord = x;
	y_coord = y;
}

Point::Point(Point &p) {

	#if VERBOSE
	std::cout << "Copy Constructor" << std::endl;
	#endif

	x_coord = p.getX();
	y_coord = p.getY();	
}

Point::~Point() {
	#if VERBOSE
		std::cout << "Default Destructor" << std::endl;
	#endif
}

void Point::setX(double val) {
	x_coord = val;
}
void Point::setY(double val) {
	y_coord = val;
}
double Point::getX() {
	return x_coord;
}
double Point::getY() {
	return y_coord;
}
double Point::distanceTo(Point &p) {
	double dx, dy;
	
	dx = (getX() - p.getX());
	dy = (getY() - p.getY());
	
	return sqrt(dx*dx + dy*dy);
}
std::ostream& operator<<(std::ostream &output, Point &p) {
	output << "(" << p.getX() << ", " << p.getY() <<")" << std::endl;
	return output;
}



