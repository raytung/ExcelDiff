/// Created by Ray Tung 2014
#ifndef EXCELDIFF_H
#	define EXCELDIFF_H
#	include <dirent.h>
#	include <stdio.h>
#	include <wchar.h>
#	include "ExcelFormat.h"
#	include <deque>
using namespace ExcelFormat;
 
class ExcelDiff
{
	private:
		bool checkStyle;
		DIR* dir_one;
		DIR* dir_two;
		string str_dir_one;
		string str_dir_two;
		BasicExcel* xls_one;
		BasicExcel* xls_two;
		
	public:
		ExcelDiff(const char* dir_one, const char* dir_two);
		~ExcelDiff();
	
	/* Function Prototypes */
		bool compare(const char* wb_one, const char* wb_two);
		bool compareRowsAndCols(int xb1Rows, int xb1Cols, int xb2Rows, int xb2Cols);
		bool compareCell(BasicExcelWorksheet* sheet1, BasicExcelWorksheet* sheet2, int rows, int cols);
		bool compareCellContent(BasicExcelCell* cell, BasicExcelCell* cell2);
		void readXLS(const char *wb1, const char *wb2);
		void cleanup();
		void run();
		DIR* openDirectory(const char *dir);
		deque<string> findXLS(DIR* directory);
		void setCheckStyle(bool check);
};
#endif
