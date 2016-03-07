/*
 * svd.cpp
 *
 *  Created on: 2013/07/03
 *      Author: user01
 */

#include "nmf.h"

using namespace Eigen;
using namespace std;
using namespace boost::program_options;

int main(int argc, char *argv[]){

	string input_file_name,input_W_file_name,input_H_file_name;

	//Analysis of a command line options
    options_description opt("Options");
    variables_map argmap;
    opt.add_options()
        ("help,h", "Show help")
        ("input,i", value<string>(&input_file_name)->default_value("input.csv"), "input csv file name (default:input.csv)")
        ("inputMatW,iw", value<string>(&input_W_file_name)->default_value("input_MatW.csv"), "input csv file name (default:input_MatW.csv)")
        ("inputMatH,ih", value<string>(&input_H_file_name)->default_value("input_MatH.csv"), "input csv file name (default:input_MatH.csv)");
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

	MatrixXd input_matrix;
	MatrixXd matrix_W;
	MatrixXd matrix_H;
    IOCSVMatrix iocsvm;
    input_file_name = RmDotCsv(input_file_name);
    input_W_file_name = RmDotCsv(input_W_file_name);
    input_H_file_name = RmDotCsv(input_H_file_name);

	iocsvm.InputMatrixXd(AddDotCsv(input_file_name),input_matrix);
	iocsvm.InputMatrixXd(AddDotCsv(input_W_file_name),matrix_W);
	iocsvm.InputMatrixXd(AddDotCsv(input_H_file_name),matrix_H);

    matrix_W = matrix_W.cwiseAbs();
    matrix_H = matrix_H.cwiseAbs();

	nmf(input_matrix, matrix_W,matrix_H,1000);

	iocsvm.OutputMatrixXd(AddDotCsv(input_file_name+CONST_MATRIX_W_SUFFIX),matrix_W);
	iocsvm.OutputMatrixXd(AddDotCsv(input_file_name+CONST_MATRIX_H_SUFFIX),matrix_H);
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
