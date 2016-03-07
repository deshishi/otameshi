/*
 * svd.cpp
 *
 *  Created on: 2013/07/03
 *      Author: user01
 */

#include "extract.h"

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
    	//("output,o", value<std::string>(), "output csv file name (default:input.csv)")
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
	MatrixXd input_matrix_buf;
	MatrixXd output_matrix;
	bool ret = iocsvm.InputMatrixXd(AddDotCsv(input_file_name[0]),input_matrix_buf);
	cout << ret << " " << input_file_name[0] << endl;
	cout << input_matrix_buf;
	output_matrix = input_matrix_buf;
	ret = iocsvm.OutputMatrixXd(AddDotCsv(output_file_name),input_matrix_buf);
	cout << ret;
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

void nmf(MatrixXd &V, MatrixXd &W, MatrixXd &H, unsigned int loop_max){

    // Create an identity matrix
    MatrixXd ones = MatrixXd::Constant(V.cols(),V.rows(),1.0);

    // Run the update rules for numUpdate iterations
    for(int i = 0; i < loop_max; i++) {


        // update spectra
        MatrixXd WH = (W * H).array() + 0.00001;

        MatrixXd numerator = (V.array() / WH.array());

        numerator = numerator * H.transpose();

        MatrixXd denominator = (H * ones).array() + 0.00001;


        W = W.array() * numerator.array();
        W = W.array() / denominator.transpose().array();


        // update gains
        WH = (W * H).array() + 0.00001;

        numerator = (V.array() / WH.array());
        numerator = W.transpose() * numerator;

        denominator = (ones * W).array() + 0.00001;

        H = H.array() * numerator.array();
        H = H.array() / denominator.transpose().array();

    }
    return;
}
