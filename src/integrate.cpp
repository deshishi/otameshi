/*
 * svd.cpp
 *
 *  Created on: 2013/07/03
 *      Author: user01
 */

#include "integrate.h"

using namespace Eigen;
using namespace std;
using namespace boost::program_options;

int main(int argc, char *argv[]){

	string input_file_name;
	string output_file_name;
	string calculate_type;
	//Analysis of a command line options
    options_description opt("Options");
    variables_map argmap;
    opt.add_options()
        ("help,h", "Show help")
        ("input,i", value< string >(&input_file_name)->default_value("input.csv"), "input csv file name (default:input.csv)")
        ("output,o", value< string >(&output_file_name)->default_value("output.csv"), "output csv file name (default:input.csv)");
        //detail console output option tukuru
        //("type,t", value<string>(&calculate_type)->default_value("Thin"), "calculate matrix type \"Thin\" or \"Full\"  (default:Thin");

	try {
	    store(parse_command_line(argc, argv, opt), argmap);
	    notify(argmap);

	} catch (required_option& e) {   // new exception type
		cerr << "required option : " << e.what() << endl;
		cerr << opt << endl;
		return -1;
	} catch (exception &e) {
		cerr << "error : " << e.what() << endl;
		cerr << opt << endl;
		return -1;
	}
	MatrixXd input_matrix;
    IOCSVMatrix iocsvm;
	MatrixXd output_matrix;

	iocsvm.InputMatrixXd(AddDotCsv(input_file_name),input_matrix);
	output_matrix.resize(input_matrix.rows(),input_matrix.cols());
	for(int j = 0; j < input_matrix.cols(); j++){
			output_matrix.coeffRef(0,j) = input_matrix.coeff(0,j);
	}
	for(int i = 1; i < input_matrix.rows(); i++){
		for(int j = 0; j < input_matrix.cols(); j++){
			output_matrix.coeffRef(i,j) = input_matrix.coeff(i,j) + output_matrix.coeff(i-1,j);
		}
	}

	iocsvm.OutputMatrixXd(AddDotCsv(output_file_name),output_matrix);
}

string AddDotCsv(string file_name){
	string::size_type pos = file_name.find(CONST_DOT_CSV);
	if (pos != string::npos) file_name = file_name.substr(0,pos);
	return file_name + CONST_DOT_CSV;
}

string RmDotCsv(string file_name){
	string::size_type pos = file_name.find(CONST_DOT_CSV);
	if (pos != string::npos) file_name = file_name.substr(0,pos);
	return file_name;
}

