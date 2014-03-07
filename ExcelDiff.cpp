#include "ExcelDiff.hpp"

/// Created by Ray Tung 2014

/* Functions */
ExcelDiff::ExcelDiff(const char* d_one, const char* d_two)
{
	dir_one = openDirectory(d_one);
	dir_two = openDirectory(d_two);
	
	//saves to member variables
	string tmp_str(d_one);
	string tmp_str_two(d_two);
	str_dir_one = tmp_str;
	str_dir_two = tmp_str_two;
	
	xls_one = new BasicExcel;
	xls_two = new BasicExcel;
}

ExcelDiff::~ExcelDiff()
{

}

void ExcelDiff::run()
{
	deque<string> xls_dir_one = findXLS(dir_one);
	deque<string> xls_dir_two = findXLS(dir_two);
	for(int i = 0; i < xls_dir_one.size(); i++){
		string tmp(xls_dir_one.at(i));
		
		for(int j = 0; j < xls_dir_two.size(); j++){
			string tmp_two(xls_dir_two.at(j));
			string tmp_dir_str     = str_dir_one;
			string tmp_dir_str_two = str_dir_two;
			
			if(tmp == tmp_two) {
				cout << tmp.c_str() << endl;
				tmp_dir_str.append(tmp);
				tmp_dir_str_two.append(tmp_two);
				cout << compare(tmp_dir_str.c_str(), tmp_dir_str_two.c_str()) << endl;
			}
		}
	}	
}

void ExcelDiff::setCheckStyle(bool check = false)
{
	checkStyle = check;
}

DIR* ExcelDiff::openDirectory(const char *dir)
{
	DIR* directory = opendir(dir);
	if(directory == NULL){
		cout << "Error opening directory" << endl;
		//need to deal with mem leaks
		exit(1);
	}
	
	return directory;
}

std::deque<string> ExcelDiff::findXLS(DIR* directory)
{
	//use deque because dynamic insertion. Unknown no. of xls docs.
	std::deque<string> xlsDeque;
	struct dirent *ent;
	while((ent=readdir(directory)) != NULL) {
		string file(ent->d_name);
		int sub    = file.find(".xls");
		int length = file.length();
		
		if(ent->d_type == DT_REG 
		&& sub != -1 //.xls is found
		&& file.substr(length-4, 4) == ".xls") //make sure it's not .xlsSAFADF
		   		xlsDeque.push_back(file);
	}

	return xlsDeque;
}

void ExcelDiff::readXLS(const char *wb1, const char *wb2)
{
	xls_one->Load(wb1);
	xls_two->Load(wb2);
}

//remove, then add to deconstructor?
void ExcelDiff::cleanup()
{
	xls_one->Close();
	xls_two->Close();
	
	delete xls_one;
	delete xls_two;
		
	closedir(dir_one);
	closedir(dir_two);
}

bool ExcelDiff::compare(const char* wb_one, const char* wb_two)
{	
	readXLS(wb_one, wb_two);
#ifdef DEBUG
	std::cout << "xls Number of worksheets: " << xls_one->GetTotalWorkSheets() << std::endl;
	std::cout << "xls2 Number of worksheets: " << xls_one->GetTotalWorkSheets() << std::endl;
#endif
	BasicExcelWorksheet *sheet_one = xls_one->GetWorksheet(0);
	BasicExcelWorksheet *sheet_two = xls_two->GetWorksheet(0);
	int xb1Rows = sheet_one ->GetTotalRows();
	int xb1Cols = sheet_one ->GetTotalCols();
	int xb2Rows = sheet_two->GetTotalRows();
	int xb2Cols = sheet_two->GetTotalCols();
#ifdef DEBUG
	std::cout << "xls Number of Rows: " << xb1Rows << std::endl;
	std::cout << "xls Number of Cols: " << xb1Cols << std::endl;
	std::cout << "xls2 Number of Rows: " << xb2Rows << std::endl;
	std::cout << "xls2 Number of Cols: " << xb2Cols << std::endl;
#endif
	//compareRowsAndCols is evaluated first. Will terminate check if false.
	return (compareRowsAndCols(xb1Rows, xb1Cols, xb2Rows, xb2Cols)
				&& compareCell(sheet_one, sheet_two, xb1Rows, xb1Cols));
}

bool ExcelDiff::compareRowsAndCols(int xb1Rows, int xb1Cols, int xb2Rows, int xb2Cols)
{
	return (xb1Rows == xb2Rows) && (xb1Cols == xb2Cols);
}

bool ExcelDiff::compareCell(BasicExcelWorksheet* sheet_one, BasicExcelWorksheet* sheet_two, int rows, int cols)
{
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++) {
			BasicExcelCell* cell_one = sheet_one->Cell(i, j);
			BasicExcelCell* cell_two = sheet_two->Cell(i, j);
			
			if(!compareCellContent(cell_one, cell_two))
				return false;
		}
	}
	return true;
}

bool ExcelDiff::compareCellContent(BasicExcelCell* cell_one, BasicExcelCell* cell_two)
{
	//Switches don't like declarations
	const char* str_one = cell_one->GetString();
	const char* str_two = cell_two->GetString();
	const wchar_t* wstr_one = cell_one->GetWString();
	const wchar_t* wstr_two = cell_two->GetWString();
	
	switch(cell_one->Type()){
		case BasicExcelCell::INT      : return cell_one->GetInteger() == cell_two->GetInteger(); 
		case BasicExcelCell::DOUBLE   : return cell_one->GetDouble()  == cell_two->GetDouble(); 
		case BasicExcelCell::UNDEFINED: return cell_two->Type() == BasicExcelCell::UNDEFINED;
		case BasicExcelCell::WSTRING  : return !wcscmp(wstr_one, wstr_two);
		case BasicExcelCell::STRING   :
			//do I really need to check for NULL?
			if(str_one != NULL && str_two != NULL){
				std::string s1(str_one);
				std::string s2(str_two);
				return !s1.compare(s2); //compare() returns 0 if identical, bool true is 1 
			}
		default:
			cout<< "NULL String or Something went wrong" << endl;
			exit(1);
	}

	//happy compiler is happy
	return false;
}
