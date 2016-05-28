#include "TypeAnal.h"
#include "../Utilities/Utilities.h"
#include "../SymbolTable/SymbolTable.h"
#include "../FileMgr/FileMgr.h"
#include "../DataStore/DataStore.h"

using namespace Utilities;
using Utils = StringHelper;
using Table = SymbolTable<std::string, symTableRecord>;
using UsingTable = SymbolTable<std::string, std::vector<std::string>>;

#ifdef TEST_TYPEANAL

int main() {
	Utils::Title("Testing Type Analyzer for single file", '=');
	TypeAnal analyzer;
	Utils::title("Testing file:");
	std::string fileSpec = "..\\..\\Project2OOD\\TestFiles\\Test.txt";
	putline();
	std::cout << fileSpec << std::endl;
	analyzer(fileSpec);
	Table _table = analyzer.table();
	if(_table.size() > 0) showTable(_table);
	putline();

	Utils::title("Testing file:");
	fileSpec = "..\\..\\Project2OOD\\TestFiles\\Test1.h";
	putline();
	std::cout << fileSpec << std::endl;
	analyzer(fileSpec);
	_table = analyzer.table();
	if (_table.size() > 0) showTable(_table);
	
	std::cout << "\n\n";
	return 0;
}

#endif