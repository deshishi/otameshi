#include "IOCSV.h"

const std::string IOCSV::constComma = ",";

IOCSV::IOCSV(){
	Initialize();
};

IOCSV::~IOCSV(){
	Initialize();
};

void IOCSV::Initialize(){
	row_size = 0L;
	col_size = 0L;
	buffer.clear();
}

bool IOCSV::InputBuffer(const std::string file_name){
	Initialize();
	fs.open(file_name.c_str(), std::ios::in);

	if(fs.fail() == true) return false;
	if(ValidCSV() == false) return false;

	buffer.resize(col_size);
	for(unsigned int i = 0; i < col_size; i++){
		buffer[i].resize(row_size);
	}

	if(!ReadData())	return false;

	fs.close();
	return true;
}

bool IOCSV::OutputBuffer(const std::string file_name){

	fs.open(file_name.c_str(), std::ios::out | std::ios::trunc);
	if(fs.fail() == true) return false;
	if(NoBuffer() == true) return false;

	if(ValidBuffer() == false) return false;

	for(unsigned int i = 0; i < col_size; i++){
		std::ostringstream osstream;
		for(unsigned int j = 0; j < row_size; j++){
			if(j != 0) osstream << constComma;
			osstream << buffer[i][j];
		}
		fs << osstream.str() << std::endl;
	}

	fs.close();
	return true;
}

bool IOCSV::ReadData(){
	std::string line, token;
	unsigned int counted_col = 0;
    unsigned int counted_row = 0;

	while(getline(fs, line)){
		std::istringstream isstream(line);
		if(std::count(line.begin(), line.end(), constComma.c_str()[0]) != 0){
			counted_row = 0;
			counted_col++;
			while(getline(isstream, token, constComma.c_str()[0])){
				counted_row++;
				buffer[counted_col-1][counted_row-1] = token;
			}
		}
	}

	if(row_size == counted_row && col_size == counted_col){
		return true;
	}else{
		return false;
	}
}


bool IOCSV::ValidCSV(){
	std::string line, token;
	unsigned int row_size = 0;
	unsigned int counted_col = 0;
    unsigned int this_line_row_size = 0;

	while(getline(fs, line)){
		this_line_row_size = std::count(line.begin(), line.end(), constComma.c_str()[0]) + 1;

    	if(this_line_row_size != 0) {
    		counted_col++;
        	if(this_line_row_size != row_size && row_size != 0) return false;
    		row_size = this_line_row_size;
    	}

	}

	this->row_size = row_size;
	this->col_size = counted_col;
	fs.clear();
	fs.seekg(0, std::ios::beg);

	return true;
}

bool IOCSV::ValidBuffer(){

	unsigned int row_size_buf = buffer[0].size();
	for(unsigned int i = 0; i < buffer.size(); i++){
		if(buffer[i].size() != row_size_buf) return false;
	}

	this->row_size = buffer[0].size();
	this->col_size = buffer.size();
	return true;
}
