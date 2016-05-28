#include <iostream>
#include <vector>
#include <string>
#include "symTableRecord.h"

#ifdef TEST_SYMTABLERECORD
int main() {
	std::cout << "\n\n  Testing Symbol Table Record\n";
	
	symTableRecord record;
	std::string key1 = "X";
	record.type() = "class";
	record.fileName() = "X.h";
	record.addNameSpace("TypeAnalysis");
	record.addNameSpace("MT4");
	showRecordHeader();
	showRecord(key1, record);

	key1 = "fun";
	record.type() = "method";
	record.fileName() = "X.h";
	record.addNameSpace("TypeAnalysis");
	record.addNameSpace("MT4");
	showRecord(key1, record);

	std::cout << "\n\n";
}
#endif