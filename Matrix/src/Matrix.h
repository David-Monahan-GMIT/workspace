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
		double **mat;
		static int matrix_cnt;
		
	public:
	//constructors
		Matrix();
		Matrix(double num);
		Matrix(unsigned int row, unsigned int col);
		Matrix(const Matrix&);
		~Matrix();
	// Functions
		unsigned int getRows() const;
		unsigned int getCols() const;
		double getElement(unsigned int row, unsigned int col) const;
		void setElement(unsigned int row, unsigned int col, double i);
		friend std::ostream &operator<<(std::ostream &, const Matrix &);
		Matrix& operator=(const Matrix &matrix);
		void operator+=(const Matrix &matrix);
		void operator-=(const Matrix &matrix);
		const bool operator==(const Matrix &matrix);
		const bool operator!=(const Matrix &matrix);
		const Matrix operator+(const Matrix &matrix) const;
		const Matrix operator-(const Matrix &matrix) const;
		const Matrix operator*(const Matrix &matrix) const;
		const double operator()(unsigned int, unsigned int);
	};
#endif /* SRC_MATRIX_H_ */
