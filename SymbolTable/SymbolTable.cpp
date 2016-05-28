#include <iostream>
#include <vector>
#include <string>
#include "SymbolTable.h"
#include "../Utilities/Utilities.h"
using namespace Utilities;
using Utils = StringHelper;

#ifdef TEST_SYMBOLTABLE
int main() {
	Utils::Title("Testing Symbol Table");
	putline();

	SymbolTable<std::string, symTableRecord> table;

	symTableRecord record;
	std::string key1 = "X";
	record.type() = "class";
	record.fileName() = "X.h";
	record.addNameSpace("TypeAnalysis");
	record.addNameSpace("MT4");

	table.addRecord(key1, record);

	key1 = "fun";
	record.type() = "method";
	record.fileName() = "X.h";
	record.addNameSpace("TypeAnalysis");
	record.addNameSpace("MT4");

	table.addRecord(key1, record);

	showTable(table);
	putline();
	
	Utils::Title("Finding element X");
	if (table.find("X") != table.end()) {
		std::cout << "\n  Name: " << table.find("X")->first;
		std::cout << "\n  File: " << table.find("X")->second.fileName();
	}
	std::cout << "\n\n";
}
#endif