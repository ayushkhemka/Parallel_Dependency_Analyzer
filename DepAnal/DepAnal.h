#ifndef DEPANAL_H
#define DEPANAL_H

/////////////////////////////////////////////////////////////////////
//  DepAnal.h - Finds out dependencies of a file                   //
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

#include <vector>
#include <string>
#include <unordered_map>
#include "../SymbolTable/SymbolTable.h"
#include "../Tokenizer/Tokenizer.h"
#include "../TypeAnal/TypeAnal.h"
using namespace Scanner;

using DepTable = SymbolTable<std::string, std::vector<std::string>>;
// -----------< perform dependency analysis >------------
class DepAnal {
public:
	// ---------< return the table generated >---------
	DepTable& table() { return _table; }

	// --------------< operator() performing dependency analysis >------------
	void operator()(std::string fileSpec, SymbolTable<std::string, symTableRecord>& symTable) {
		result.clear();
		try {
			std::ifstream in(fileSpec);
			if (!in.good()) {
				std::cout << "can't open " << fileSpec << "\n\n";
				return;
			}
			Toker toker;
			toker.returnComments(false);
			toker.attach(&in);
			do {
				std::string tok = toker.getTok();
				if (symTable.find(tok) != symTable.end()) {
					std::string filename = symTable.find(tok)->second.fileName();
					if (filename != fileSpec && (find(result.begin(), result.end(), filename) == result.end()))
						result.push_back(filename);
				}
			} while (in.good());
			_table.addRecord(fileSpec, result);
		}
		catch (std::logic_error& ex) {
			std::cout << "\n  " << ex.what();
		}
	}

private:
	DepTable _table;
	std::vector<std::string> result;
};

#endif