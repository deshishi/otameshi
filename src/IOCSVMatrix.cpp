/*
 * IOCSVMatrix.cpp
 *
 *  Created on: 2013/07/02
 *      Author: user01
 */

#include "IOCSVMatrix.h"

bool IOCSVMatrix::InputMatrixXd(const std::string file_name, Eigen::MatrixXd& matrix){
	double buf_double;
	bool ret = InputBuffer(file_name);
	matrix.resize(col_size,row_size);

	for(unsigned int i = 0; i < col_size; i++){
		for(unsigned int j = 0; j < row_size; j++){
			std::stringstream ss;
			ss << buffer[i][j];
			ss >> buf_double;
			matrix.coeffRef(i,j) = buf_double;
		}
	}
	return ret;
}

bool IOCSVMatrix::OutputMatrixXd(const std::string file_name, const Eigen::MatrixXd matrix){

	row_size = matrix.cols();//row_size = s‚Ì’·‚³@cols = —ñ”  —¼•û‚Æ‚às—ñ‚Ì‰¡•
	col_size = matrix.rows();

	buffer.resize(col_size);
	for(unsigned int i = 0; i < col_size; i++){
		buffer[i].resize(row_size);
		for(unsigned int j = 0; j < row_size; j++){
			std::stringstream ss;
			ss << matrix.coeffRef(i,j);
			buffer[i][j] = ss.str();
		}
	}

	return 	OutputBuffer(file_name);
}
