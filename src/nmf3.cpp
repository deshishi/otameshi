/*
 * svd.cpp
 *
 *  Created on: 2015/03/01
 *      Author: user01
 */

#include "nmf.h"

using namespace Eigen;
using namespace std;
using namespace boost::program_options;

void NMF(
    const Eigen::MatrixXd &V, unsigned int k,
    Eigen::MatrixXd &W, Eigen::MatrixXd &H, 
    const unsigned int loop_max);

int main(int argc, char *argv[]){

	string input_file_name,input_W_file_name,input_H_file_name;

	//Analysis of a command line options
    options_description opt("Options");
    variables_map argmap;
    opt.add_options()
        ("help,h", "Show help")
        ("input,i", value<string>(&input_file_name)->default_value("input.csv"), "input csv file name (default:input.csv)");
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

	iocsvm.InputMatrixXd(AddDotCsv(input_file_name),input_matrix);

	NMF(input_matrix, 2,matrix_W,matrix_H,1000);

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

void NMF(
    const Eigen::MatrixXd &V, unsigned int k,
    Eigen::MatrixXd &W, Eigen::MatrixXd &H, 
    const unsigned int loop_max = 1000
){
    // W, Hをランダムな非負数で初期化
    W = Eigen::MatrixXd::Random(V.rows(), k).cwiseAbs();
    H = Eigen::MatrixXd::Random(k, V.cols()).cwiseAbs();
	Eigen::MatrixXd W_n = W,H_n = H;
    // W, Hを更新
    for(unsigned int i = 0; i < loop_max; ++i){
        W_n.array() = W.array() * (V * H.transpose()).array() / 
                     (W * H * H.transpose()).array();
        H_n.array() = H.array() * (W.transpose() * V).array() /
                     (W.transpose() * W * H).array();

        W = W_n; H = H_n;
    }   
}
