/*
 * svd.cpp
 *
 *  Created on: 2013/07/03
 *      Author: user01
 */

#include "svd.h"

using namespace Eigen;
using namespace std;
using namespace boost::program_options;

int main(int argc, char *argv[]){

	string input_file_name;
	string calculate_type;
	bool is_thin;
	//Analysis of a command line options
    options_description opt("Options");
    variables_map argmap;
    opt.add_options()
        ("help,h", "Show help")
        ("input,i", value<string>(&input_file_name)->default_value("input.csv"), "input csv file name (default:input.csv)")
        //("output,o", value<std::string>(), "output csv file name (default:input.csv)")
        //detail console output option tukuru
        ("type,t", value<string>(&calculate_type)->default_value("Thin"), "calculate matrix type \"Thin\" or \"Full\"  (default:Thin");

	try {
	    store(parse_command_line(argc, argv, opt), argmap);
	    notify(argmap);
	    if(calculate_type == CONST_THIN){
	    	is_thin = true;
	    }else if(calculate_type == CONST_FULL){
	    	is_thin = false;
	    }else{
			cerr << "invalid value of type" << endl;
			cerr << opt << endl;
			return -1;
	    }
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
	MatrixXd matrix_U;
	MatrixXd matrix_V;
	MatrixXd singular_values;
	MatrixXd matrix_S;
    IOCSVMatrix iocsvm;
    input_file_name = RmDotCsv(input_file_name);
	iocsvm.InputMatrixXd(AddDotCsv(input_file_name),input_matrix);

	JacobiSVD< MatrixXd > svd(input_matrix,Eigen::ComputeThinU | Eigen::ComputeThinV);

	matrix_U = svd.matrixU();
	matrix_V = svd.matrixV();
	singular_values = svd.singularValues();
	int s_rows = singular_values.rows();
	matrix_S = MatrixXd::Zero(s_rows,s_rows);
	for(int i = 0; i < s_rows; i++){
		matrix_S.coeffRef(i,i) = singular_values(i,0);
	}
	iocsvm.OutputMatrixXd(AddDotCsv(input_file_name+CONST_MATRIX_U_SUFFIX),matrix_U);
	iocsvm.OutputMatrixXd(AddDotCsv(input_file_name+CONST_MATRIX_V_SUFFIX),matrix_V);
	iocsvm.OutputMatrixXd(AddDotCsv(input_file_name+CONST_MATRIX_S_SUFFIX),matrix_S);
	iocsvm.OutputMatrixXd(AddDotCsv(input_file_name+CONST_VECTOR_S_SUFFIX),singular_values);
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

