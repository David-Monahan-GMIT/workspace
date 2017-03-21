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
namespace DavesMatrix {
class Matrix {
	private:
		unsigned int rows;
		unsigned int cols;
		double **mat;
		static int matrix_cnt = 0;
		
	public:
	//constructors
		Matrix();
		Matrix(double num);
		Matrix(unsigned int row, unsigned int col);
		Matrix(const Matrix&);
		~Matrix();
	// Functions
		unsigned int getRows() const { return rows; }
		unsigned int getCols() const { return cols; }
		int getMatrixCnt() const { return matrix_cnt; }

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
}
#endif /* SRC_MATRIX_H_ */
