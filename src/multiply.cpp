/*
 * svd.cpp
 *
 *  Created on: 2013/07/03
 *      Author: user01
 */

#include "multiply.h"

using namespace Eigen;
using namespace std;
using namespace boost::program_options;

int main(int argc, char *argv[]){

	vector<string> input_file_name;
	string output_file_name;
	//Analysis of a command line options
    options_description opt("Options");
    variables_map argmap;
    opt.add_options()
        ("help,h", "Show help")
        ("input,i", value< vector<string> >(&input_file_name)->required(), "input csv file name")
        ("output,o", value<std::string>(&output_file_name)->default_value("output_UxSxV^T"), "output csv file name (default:input.csv)");
        //detail console output option tukuru

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
    IOCSVMatrix iocsvm;
	MatrixXd output_matrix;
	MatrixXd input_matrix_buf;

	iocsvm.InputMatrixXd(AddDotCsv(input_file_name[0]),output_matrix);

	for(int i = 1; i < input_file_name.size(); i++){
		iocsvm.InputMatrixXd(AddDotCsv(input_file_name[i]),input_matrix_buf);
		output_matrix *= input_matrix_buf;
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

