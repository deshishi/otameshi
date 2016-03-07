/*
 * IOCSVMatrix.h
 *
 *  Created on: 2013/07/02
 *      Author: user01
 */

#ifndef IOCSVMATRIX_H_
#define IOCSVMATRIX_H_

#include <cfloat>
#include "IOCSV.h"
#include "Eigen/Core"

class IOCSVMatrix : public IOCSV{

public:
	IOCSVMatrix(){};
	~IOCSVMatrix(){};
	bool InputMatrixXd(const std::string file_name, Eigen::MatrixXd& matrix);
	bool OutputMatrixXd(const std::string file_name, const Eigen::MatrixXd matrix);
};

#endif /* IOCSVMATRIX_H_ */
