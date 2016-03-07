#ifndef _IOCSV_H__
#define _IOCSV_H__
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

/*
#define CCSVFILE_is_sjis1(c) (((((unsigned char)(c))>=0x81)&&(((unsigned char)(c))<=0x9F))||((((unsigned char)(c))>=0xE0)&&(((unsigned char)(c))<=0xFC)))
#define CCSVFILE_is_sjis2(c) ((((unsigned char)(c))!=0x7F)&&(((unsigned char)(c))>=0x40)&&(((unsigned char)(c))<=0xFC))
*/
#define CCSVFILE_NOBUFFER() (rowsize == 0L && colsize == 0L && buffer == NULL)

typedef std::vector< std::vector<std::string> > StringArray2D;

class IOCSV{
protected:
	std::fstream fs;
	unsigned long	row_size;
	unsigned long	col_size;

	static const std::string constComma;

	std::vector< std::vector<std::string> > buffer;

	bool			ValidCSV();
	bool			ValidBuffer();
	bool			ReadData();
	bool			NoBuffer(){ return buffer.empty() == true; };
	unsigned int	CountComma(const std::string text);

public:
	IOCSV();
	~IOCSV();

	bool	InputBuffer(const std::string file_name);
	bool	OutputBuffer(const std::string file_name);

	bool	InputBuffer(const std::string file_name, StringArray2D& buffer){
		bool ret;
		ret = InputBuffer(file_name);
		buffer = this->buffer;
		return ret;
	}

	bool	OutputBuffer(const std::string file_name, const StringArray2D buffer){
		this->buffer = buffer;
		return OutputBuffer(file_name);
	}

	void			Initialize();

	StringArray2D&	GetBufferRef(){ return buffer; };
	StringArray2D	GetBuffer(){ return buffer; };
	unsigned long	GetRowSize(){ return row_size; };
	unsigned long	GetColSize(){ return col_size; };
};

#endif //_IOCSV_H__
