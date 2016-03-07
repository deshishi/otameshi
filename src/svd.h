/*
 * svd.h
 *
 *  Created on: 2013/07/03
 *      Author: user01
 */

#ifndef SVD_H_
#define SVD_H_

#include <boost/program_options.hpp>
#include "Eigen/SVD"
#include "Eigen/Core"

#include "IOCSVMatrix.h"


const std::string CONST_DOT_CSV = ".csv";

const std::string CONST_MATRIX_U_SUFFIX = "_MatU";
const std::string CONST_MATRIX_V_SUFFIX = "_MatV";
const std::string CONST_MATRIX_S_SUFFIX = "_MatS";
const std::string CONST_VECTOR_S_SUFFIX = "_VecS";

const std::string CONST_THIN = "Thin";
const std::string CONST_FULL = "Full";

std::string AddDotCsv(std::string file_name);
std::string RmDotCsv(std::string file_name);

#endif /* SVD_H_ */
