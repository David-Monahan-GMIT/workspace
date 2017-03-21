/*
 * Matrix.cpp
 *
 *  Created on: 14 Mar 2017
 *      Author: Dave
 */
#include <iostream>
#include <cmath>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Matrix.h"

namespace DavesMatrix {

int Matrix::matrix_cnt = 0;

Matrix::Matrix() : rows(0), cols(0) {
	#if VERBOSE
		std::cout << "Default Constructor" << std::endl;
	#endif
	matrix_cnt++;
}

Matrix::Matrix(double num) : rows(10), cols(10){
	#if VERBOSE
		std::cout << "Initialising Constructor" << std::endl;
	#endif


	mat.resize(rows);
	for(unsigned int i=0; i < mat.size(); i++)  {
		mat[i].resize(cols);
	}

	srand((unsigned int)num);
	for(unsigned int i=0;i<rows;i++) {
		for(unsigned int j=0;j<cols;j++) {
			mat[i][j] = rand()%100 +1;
		}
	}
	matrix_cnt++;
}

Matrix::Matrix(unsigned int row, unsigned int col) : rows(row), cols(col) {

	#if VERBOSE
		std::cout << "Custom Matrix Constructor" << std::endl;
	#endif

	mat.resize(rows);
	for(unsigned int i=0; i < mat.size(); i++)  {
		mat[i].resize(cols);
	}
	unsigned int k=1;
	std::vector<double>::iterator p;
	for(p=mat.begin(); p !=mat.end(); p++) {
		*p = k;
		k++;
	}

/*	for(unsigned int i=0;i<rows;i++) {
		for(unsigned int j=0;j<cols;j++) {
			mat[i][j] = k;
			k++;
		}
	}*/
	matrix_cnt++;
}

Matrix::Matrix(const Matrix& matCopy) : rows(0), cols(0) {

	#if VERBOSE
		std::cout << "Copy Constructor" << std::endl;
	#endif

	rows=matCopy.getRows();
	cols=matCopy.getCols();

	mat = matCopy.getMatrix();
	matrix_cnt++;
}

Matrix::~Matrix() {
	#if VERBOSE
		std::cout << "Default Destructor" << std::endl;
	#endif
	matrix_cnt--;
}
}
