#include <iostream>
#include "ParallelDepAnal.h"
#include "../Utilities/Utilities.h"
using namespace Utilities;
using Utils = StringHelper;

#ifdef TEST_PARALLELDEPANAL

int main() {
	Utils::Title("Testing Parallel Dependency Analysis for predefined path", '=');
	putline();
	ParallelDepAnal pda;
	std::string path = "..\\SemiExp";
	std::vector<std::string> patterns = { "*.h", "*.cpp" };
	DataStore ds = pda.searchFiles(path, patterns);
	Utils::Title("Testing these files:");
	putline();
	for (auto fileSpec : ds) std::cout << fileSpec << std::endl;
	putline();

	SymbolTable<std::string, symTableRecord> _table1 = pda.doTypeAnal(ds);
	Utils::Title("Result of Type Analysis");
	putline();
	showTable(_table1);

	putline();
	SymbolTable<std::string, std::vector<std::string>> _table2 = pda.doDepAnal(ds, _table1);
	Utils::Title("Result of Dependency Analysis");
	putline();
	for (auto result : _table2) {
		std::cout << "\n  ..." << result.first.substr(result.first.length() - 20) << " depends on:";
		if (result.second.size() > 0) {
			for (auto file : result.second) std::cout << "\n  .." << file.substr(file.length() - 30) << std::endl;
			std::cout << "\n";
		}
		else {
			std::cout << "\n  No file";
			std::cout << "\n";
		}
	}
	std::cout << "\n\n";
	return 0;
}

#endif