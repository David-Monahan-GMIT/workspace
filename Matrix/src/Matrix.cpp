/*
 * Matrix.cpp
 *
 *  Created on: 24 Jan 2017
 *      Author: Dave
 */



#include <iostream>
#include <cmath>
#include "Matrix.h"

Matrix::Matrix() {

	#if VERBOSE
		std::cout << "Default Constructor" << std::endl;
	#endif
	rows=10;
	cols=10;
	
	unsigned int i,j;
	unsigned int k=0;
	
	if(mat != nullptr) {
		mat = new double* [rows];
		for(i=0;i<rows;i++) {
			mat[i] = new double[cols];
			for(j=0;j<cols;j++) {
				mat[i][j] = k;
				k++;
			}
		}	
	}	
}
Matrix::Matrix(double num) {
	#if VERBOSE
		std::cout << "Initialising Constructor" << std::endl;
	#endif
	
	rows=10;
	cols=10;
	
	unsigned int i,j;
	
	if(mat != nullptr) {
		mat = new double* [rows];	// New is an operator that can be overloaded, or to add to an existing class
		for(i=0;i<rows;i++) {
			mat[i] = new double [cols];
			for(j=0;j<cols;j++) {
				mat[i][j] = num;
			}
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
	unsigned int k=0;
	if(mat != nullptr) {
		mat = new double* [rows];
		for(i=0;i<rows;i++) {
			mat[i] = new double[cols];
			for(j=0;j<cols;j++) {
				mat[i][j] = k;
				k++;
			}
		}
	}	
}

Matrix::Matrix(Matrix& matCopy) {

	#if VERBOSE
		std::cout << " Copy Constructor" << std::endl;
	#endif
	rows=matCopy.getRows();
	cols=matCopy.getCols();
	
	unsigned int i,j;
	if(mat != nullptr) {
		mat = new double* [rows];
		for(i=0;i<rows;i++) {
			mat[i] = new double[cols];
			for(j=0;j<cols;j++) {
				mat[i][j] = matCopy.getElement(i,j);
			}
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

unsigned int Matrix::getRows() {
	return rows;
}
unsigned int Matrix::getCols() {
	return cols;
}
double Matrix::getElement(unsigned int row, unsigned int col){
	//return matrix[row][col];
	return mat[row][col];
}

std::ostream& operator<<(std::ostream &output, Matrix &m) {
	//output << "(" << m.getRows() << ", " << m.getCols() <<")" << std::endl;
	unsigned int i,j;
	for(i=0; i<m.getRows();i++) {
		for(j=0;j<m.getCols();j++) {
			output << m.getElement(i,j) << " ";
		}
		output << std::endl;
	}	
	return output;
}
