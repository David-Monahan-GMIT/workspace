/*
 * Matrix.h
 *
 *  Created on: 24 Jan 2017
 *      Author: Dave
 */

#ifndef SRC_MATRIX_H_
#define SRC_MATRIX_H_

#define VERBOSE 1

#include <iostream>
class Matrix {
	private:
		unsigned int rows;
		unsigned int cols;
		//double matrix[10][10];
		double **mat;
		
	public:
	//constructors
		Matrix();
		Matrix(double num);
		Matrix(unsigned int row, unsigned int col);
		Matrix(Matrix&);
		~Matrix();
	// Functions
		unsigned int getRows();
		unsigned int getCols();
		double getElement(unsigned int row, unsigned int col);
		friend std::ostream &operator<<(std::ostream &, Matrix &);	
		void operator=(Matrix &matrix);
		};
#endif /* SRC_MATRIX_H_ */
