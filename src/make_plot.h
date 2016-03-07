/*
 * svd.h
 *
 *  Created on: 2013/07/03
 *      Author: user01
 */

#ifndef SVD_H_
#define SVD_H_

#include <boost/program_options.hpp>
#include <cstdio>
#include <iostream>
#include "Eigen/SVD"
#include "Eigen/Core"

#include "IOCSVMatrix.h"




const std::string CONST_DOT_CSV = ".csv";
const std::string CONST_DOT_PNG = ".png";

std::string AddDotCsv(std::string file_name);
std::string RmDotCsv(std::string file_name);

std::string AddDotPng(std::string file_name);
#endif /* SVD_H_ */
