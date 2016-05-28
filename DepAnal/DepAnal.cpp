#include <iostream>
#include "DepAnal.h"
#include "../Utilities/Utilities.h"

/////////////////////////////////////////////////////////////////////
//  DepAnal.cpp - Finds out dependencies of a file                 //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2015, SP1                            //
//  Platform:      Dell Precision T7400, Vista Ultimate SP1        //
//  Application:   CSE 687 Projct #3 Spring 16	                   //
//  Author:        Ayush Khemka, Syracuse University						   //
//                 aykhemka@syr.edu, 538044584					           //
/////////////////////////////////////////////////////////////////////

/*
* Module Operations:
* ==================
* This module finds, for a specified files, all the other files
* that it is dependent upon. This module requires that the file
* name and the table obtained after performing type analysis be
* provided to it.
* It then tokenizes the file, and for each token collected, checks
* the corresponding entry in the symbol table. If there is a match,
* the file in inspection is dependent upon the file in which the
* token was defined.
*
* Build Process:
* ==============
* Required files:
* ActionAndRules.h, ConfigureParser.h, DepAnal.h, Parser.h
* SemiExp.h, SymbolTable.h, Tokenizer.h, TypeAnal.h
* Utilities.h, DepAnal.cpp
*
* Maintenance History:
* ====================
* ver 1.0 : 6 Apr 16
* - first release
*/

using namespace Utilities;
using Utils = StringHelper;
using Table = SymbolTable<std::string, symTableRecord>;

#ifdef TEST_DEPANAL
int main() {
	Utils::Title("Testing Dependency Analysis of a single file", '=');
	std::string fileSpec1 = "..\\..\\Project2OOD\\TestFiles\\Test2.h";
	std::string fileSpec2 = "..\\..\\Project2OOD\\TestFiles\\Test2.cpp";

	TypeAnal analyzer;
	analyzer(fileSpec2);
	Table result = analyzer.table();
	Utils::Title("Results of type analysis");
	showTable(result);

	DepAnal depend;
	depend(fileSpec1, result);
	DepTable results = depend.table();
	putline();

	Utils::title("Results of dependency analysis");
	for (auto result : results) {
		std::cout << "\n  " << result.first << " depends on:";
		for (auto file : result.second) std::cout << "\n  " << file << std::endl;
	}

	std::cout << "\n\n";
	return 0;
}
#endif