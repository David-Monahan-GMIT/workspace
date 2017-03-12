/*
 * Main.cpp
 *
 *  Created on: 24 Jan 2017
 *      Author: Dave
 */

#include <iostream>
#include <string>
#include "Point.h"

void testPoint();
void testConstructor();

int main(int argc, char *argv[]) {
	std::string test = "test";
	
	if (argc >= 2 && !test.compare(argv[1])) {
		testPoint();
		testConstructor();
	} else {
		std::cout << "Nothing to do." << std::endl;
	}

	return 0;
}
void testPoint(void) {

		
	std::string stars("*******************");
	std::string message("Test Default Constructor");

	std::cout << stars << message << stars << std::endl;

	Point p1;
	Point p2;

	std::cout << "P1 = (" << p1.getX() << "," << p1.getY() << ")" << std::endl;
	std::cout << "P2 = (" << p2.getX() << "," << p2.getY() << ")" << std::endl;

	p1.setX(1.1);
	p1.setY(2.2);
	p2.setX(-1.1);
	p2.setY(-2.2);

	//std::cout << "P1 = (" << p1.getX() << "," << p1.getY() << ")" << std::endl;
	std::cout << "P1 = " << p1;
	std::cout << "P2 = " << p2;
	
	std::cout << "Distance between P1 and P2 = (" << p1.distanceTo(p2) << ")" << std::endl;
	
	Point p4(p2);
	std::cout << "Point P4 copied from P2 = " << p4;
	
}
void testConstructor(void) {
	Point p3(3.3, -3.3);
	std::cout << "P3 = " << p3;
}
