/*
 * svd.h
 *
 *  Created on: 2013/07/03
 *      Author: user01
 */

#ifndef NMF_H_
#define NMF_H_

#include <boost/program_options.hpp>
#include "Eigen/Core"

#include "IOCSVMatrix.h"


const std::string CONST_DOT_CSV = ".csv";

const std::string CONST_MATRIX_W_SUFFIX = "_MatW";
const std::string CONST_MATRIX_H_SUFFIX = "_MatH";

std::string AddDotCsv(std::string file_name);
std::string RmDotCsv(std::string file_name);
void nmf(Eigen::MatrixXd &V, Eigen::MatrixXd &W, Eigen::MatrixXd &H, unsigned int loop_max);

#endif /* NMF_H_ */
