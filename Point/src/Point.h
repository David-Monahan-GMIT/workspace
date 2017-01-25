/*
 * Point.h
 *
 *  Created on: 17 Jan 2017
 *      Author: Dave
 */
#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED
#define VERBOSE 1

#include <iostream>

class Point {
	private:
		double x_coord;	// X coordinate
		double y_coord;
	public:
		Point();
		Point(double x, double y);
		Point(Point &);
		~Point();

		void setX(double val);
		void setY(double val);
		double getX();
		double getY();
		double distanceTo(Point &p);

		friend std::ostream &operator<<(std::ostream &, Point &);
};
#endif
