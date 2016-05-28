/////////////////////////////////////////////////////////////////////
//  ParallelDepExec.cpp - Test Executive for Pr #3                  //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2015, SP1                            //
//  Application:   CSE 687 Projct #3 Spring 16	                   //
//  Author:        Ayush Khemka, Syracuse University						   //
//                 aykhemka@syr.edu, 538044584					           //
/////////////////////////////////////////////////////////////////////

/*
* Module Operations:
* ==================
* This module is the test executive to demonstrate that all the requirements
* of the project have been met. All the packages mentioned in the Purpose
* section have been successfully implemented and tested. This module makes
* use of the services provided by the Parallel Dependency Analyzer to analyze
* a set of files mentioned on the command line. Please read the ReadMe.txt file
* to look at explanation of the implementation of the requirements, and release
* notes and package structure.
*
* Build Process:
* ==============
* Required files:
* ActionsAndRules.h, ConfigureParser.h, Cpp11-BlockingQueue.h,
* DataStore.h, DepAnal.h, FileMgr.h, FileSystem.h, itokcollection.h,
* ParallelDepAnal.h, Parser.h, QueuedWorkItems.h, SemiExp.h,
* SymbolTable.h, symTableRecord.h, Tasks.h, Tokenizer.h,
* TypeAnal.h, Utilities.h, ParallelDepExec.cpp
*
* Build command:
* ==============
* compile: devenv Project3ood.sln /Rebuild
* run: Debug\ParallelDepExec.exe [directory path] [patterns]
*
* Maintenance History:
* ====================
* ver 1.0 : 6 Apr 16
* - first release
*/

#include <iostream>
#include "../ParallelDepAnal/ParallelDepAnal.h"
#include "../Utilities/Utilities.h"
using namespace Utilities;
using namespace Scanner;
using Utils = StringHelper;

#ifdef TEST_PARALLELDEPEXEC
int main(int argc, char * argv[]) {
	Utils::Title("Demonstrating Requirements for CSE 687 Project #3", '=');
	putline();
	ParallelDepAnal pda;
	std::string path = argv[1];
	std::vector<std::string> patterns;
	for (int i = 1; i < argc; i++) patterns.push_back(argv[i]);
	DataStore ds = pda.searchFiles(path, patterns);
	Utils::Title("Testing these files (Requirement #4 and #5):");
	putline();
	for (auto fileSpec : ds) std::cout << fileSpec << std::endl;
	putline();

	SymbolTable<std::string, symTableRecord> _table1 = pda.doTypeAnal(ds);
	Utils::Title("Result of Type Analysis (Requirement #6)");
	putline();
	showTable(_table1);

	putline();
	SymbolTable<std::string, std::vector<std::string>> _table2 = pda.doDepAnal(ds, _table1);
	Utils::Title("Result of Dependency Analysis (Requirement #7, #8, and #9)");
	putline();
	for (auto result : _table2) {
		std::cout << "\n\n  ..." << result.first.substr(result.first.length() - 50) << " depends on:";
		if (result.second.size() > 0) {
			for (auto file : result.second) std::cout << "\n  .." << file.substr(file.length() - 50);
		}
		else {
			std::cout << "\n  No file";
		}
	}
	std::cout << "\n\n  ----< Explanation of the requirements and release notes is provided in the ReadMe file >----";
	std::cout << "\n\n";
	return 0;
}
#endif