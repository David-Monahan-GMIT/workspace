/*
 * Matrix.cpp
 *
 *  Created on: 24 Jan 2017
 *      Author: Dave
 */



#include <iostream>
#include <cmath>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Matrix.h"

int Matrix::matrix_cnt = 0;
Matrix::Matrix() {

	#if VERBOSE
		std::cout << "Default Constructor" << std::endl;
	#endif
	rows=0;
	cols=0;
	mat = nullptr;
}
Matrix::Matrix(double num) {
	#if VERBOSE
		std::cout << "Initialising Constructor" << std::endl;
	#endif
	
	rows=10;
	cols=10;
	srand((unsigned int)num);
	
	unsigned int i,j;

	mat = new double* [rows];	// New is an operator that can be overloaded, or to add to an existing class
	for(i=0;i<rows;i++) {
		mat[i] = new double [cols];
		for(j=0;j<cols;j++) {
			mat[i][j] = rand()%100 +1;
		}
	}

}

Matrix::Matrix(unsigned int row, unsigned int col) {

	#if VERBOSE
		std::cout << "Custom Matrix Constructor" << std::endl;
	#endif
	rows=row;
	cols=col;
	
	unsigned int i,j;
	unsigned int k=1;
	mat = new double* [rows];
	for(i=0;i<rows;i++) {
		mat[i] = new double[cols];
		for(j=0;j<cols;j++) {
			mat[i][j] = k;
			k++;
		}
	}
}

Matrix::Matrix(const Matrix& matCopy) {

	#if VERBOSE
		std::cout << "Copy Constructor" << std::endl;
	#endif

	rows=matCopy.getRows();
	cols=matCopy.getCols();

	unsigned int i,j;

	mat = new double* [rows];
	for(i=0;i<rows;i++) {
		mat[i] = new double[cols];
		for(j=0;j<cols;j++) {
			mat[i][j] = matCopy.getElement(i,j);
		}
	}

}

Matrix::~Matrix() {
	#if VERBOSE
		std::cout << "Default Destructor" << std::endl;
	#endif
	if(mat != nullptr){ 
		for(unsigned int i=0; i<rows; i++) {
			delete [] mat[i];
		}
		delete [] mat;
	}
}

unsigned int Matrix::getRows() const {
	return rows;
}
unsigned int Matrix::getCols() const {
	return cols;
}
double Matrix::getElement(unsigned int row, unsigned int col) const {
	// returns the element located at [row,col]
	return mat[row][col];
}

void Matrix::setElement(unsigned int row, unsigned int col, double i){
	// sets the element located at [row,col]
	mat[row][col] = i;
}

std::ostream& operator<<(std::ostream &output, const Matrix &m) {
	// Generate a formatted string for the matrix and return it
	unsigned int i,j;
	for(i=0; i<m.getRows();i++) {
		for(j=0;j<m.getCols();j++) {
			output << m.getElement(i,j) << " ";
		}
		output << std::endl;
	}	
	return output;
}

Matrix& Matrix::operator=(const Matrix &matrix) {

	// Check for self assignment
	if(this != &matrix){

		// If it's not null delete whatever it has
		if(mat != nullptr){
			for(unsigned int i=0; i<rows; i++) {
				delete [] mat[i];
			}
			delete [] mat;
		}

		// Reassign the rows and cols
		rows = matrix.getRows();
		cols = matrix.getCols();

		unsigned int i,j; // elements
		// Allocate memory for a new matrix and assign it's elements the correct values

		mat = new double* [rows];
		for(i=0;i<rows;i++) {
			mat[i] = new double[cols];
			for(j=0;j<cols;j++) {
				mat[i][j] = matrix.getElement(i,j);
			}
		}
	}
	return *this;
}

const Matrix Matrix::operator+(const Matrix &matrix) const {
	Matrix result(*this);
	if(matrix.getCols() == cols && matrix.getRows() == rows){
		unsigned int i,j;
		for(i=0;i<rows;i++) {
			for(j=0;j<cols;j++) {
				result.setElement(i,j, (mat[i][j] + matrix.getElement(i,j)));
			}
		}
	}
	return result;
}

const Matrix Matrix::operator-(const Matrix &matrix) const {
	Matrix result(*this);
	if(matrix.getCols() == cols && matrix.getRows() == rows){
		unsigned int i,j;
		for(i=0;i<rows;i++) {
			for(j=0;j<cols;j++) {
				result.setElement(i,j, (mat[i][j] - matrix.getElement(i,j)));
			}
		}
	}
	return result;
}

void Matrix::operator+=(const Matrix &matrix) {
	if(matrix.getCols() == cols && matrix.getRows() == rows){
		unsigned int i,j;
		for(i=0;i<rows;i++) {
			for(j=0;j<cols;j++) {
				mat[i][j] += matrix.getElement(i,j);
			}
		}
	}
}

void Matrix::operator-=(const Matrix &matrix) {
	if(matrix.getCols() == cols && matrix.getRows() == rows){
		unsigned int i,j;
		for(i=0;i<rows;i++) {
			for(j=0;j<cols;j++) {
				mat[i][j] -= matrix.getElement(i,j);
			}
		}
	}
}

const bool Matrix::operator==(const Matrix &matrix) {
	if(matrix.getCols() == cols && matrix.getRows() == rows){
		unsigned int i,j, flag;
		flag=0;
		for(i=0;i<rows;i++) {
			for(j=0;j<cols;j++) {
				if(mat[i][j] == matrix.getElement(i,j)){
				} else {
					flag += 1;
				}
			}
		}
		if(flag == 0) {
			return true;
		}
	}
	return false;
}

const bool Matrix::operator!=(const Matrix &matrix) {
	if(matrix.getCols() == cols && matrix.getRows() == rows){
		unsigned int i,j, flag;
		flag=0;
		for(i=0;i<rows;i++) {
			for(j=0;j<cols;j++) {
				if(mat[i][j] == matrix.getElement(i,j)){
				} else {
					flag += 1;
				}
			}
		}
		if(flag == 0) {
			return false;
		}
	}
	return true;
}

const Matrix Matrix::operator*(const Matrix &matrix) const {
	std::cout << "Compare rows to cols: " << matrix.getRows() << " " << cols << std::endl;
	if(matrix.getRows() == cols) {
		double temp = 0;
		Matrix result(rows, matrix.getCols());
		std::cout << result;

		for(unsigned int i=0;i<rows;i++) {
			for(unsigned int j=0;j<matrix.getCols();j++) {
				for(unsigned int m=0; m<cols; m++) {
					temp += mat[i][m] * matrix.getElement(m,j);
				}
				result.setElement(i,j,temp);
				temp=0;
			}
		}
		return result;
	} else {
		return *this;
	}
}
const double Matrix::operator()(unsigned int i, unsigned int j) {
	return *(*mat +i) +j;
}

