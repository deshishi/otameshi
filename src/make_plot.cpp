/*
 * svd.cpp
 *
 *  Created on: 2013/07/03
 *      Author: user01
 */

#include "make_plot.h"

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
        ("output,o", value< string >(&output_file_name)->default_value("output.png"), "output csv file name (default:input.csv)");
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

	iocsvm.InputMatrixXd(AddDotCsv(input_file_name),input_matrix);

	FILE *fp = popen("pgnuplot.exe", "w");
	if (fp == NULL)	return -1;
	fputs("set terminal png\n", fp);
	fputs("set output '/dev/null'\n", fp);
	fputs(string("set title '"+RmDotCsv(input_file_name)+"'\n").c_str(), fp);
	fputs("set datafile separator ','\n", fp);
	if(input_matrix.cols() != 0){
		fputs(string("plot '" + AddDotCsv(input_file_name) + "' using 0:1 with lines title '1'\n").c_str(),fp);
		for(int i = 1; i < input_matrix.cols(); i++){
			stringstream ss;
			ss << "replot '" << AddDotCsv(input_file_name) << "' using 0:" << i+1 << " with lines title '" << i+1 << "'\n";
			fputs(ss.str().c_str(),fp);
		}
	}

	fputs(string("set output '"+AddDotPng(output_file_name)+"'\n").c_str(), fp);
	fputs("replot\n", fp);
	fflush(fp);
	//cin.get();
	pclose(fp);
	return 0;
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

string AddDotPng(string file_name){
	string::size_type pos = file_name.find(CONST_DOT_PNG);
	if (pos != string::npos) file_name = file_name.substr(0,pos);
	return file_name + CONST_DOT_PNG;
}
