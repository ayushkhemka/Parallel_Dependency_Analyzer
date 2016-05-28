#ifndef TYPEANAL_H
#define TYPEANAL_H

/////////////////////////////////////////////////////////////////////
//  TypeAnal.h - Perform type analysis for a file			             //
//  ver 1.0                                                        //
//                                                                 //
//  Lanaguage:     Visual C++ 2016                                 //
//  Application:   CSE 687 Project #3 Spring 2016                  //
//  Author:				 Ayush Khemka, Syracuse University							 //
//								 aykhemka@syr.edu, 538044584										 //
/////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This module performs type analysis for a given file. It does that by
detecting all the functions, types, and aliases in a give file
and generates a symbol table, denoting the name, type, file, and
associated namespaces, if any.

Build Process:
==============
Required files
- ActionsAndRules.h, ConfigureParser.h, DataStore.h,
FileMgr.h, FileSystem.h, Parser.h, SemiExp.h, SymbolTable.h,
Tokenizer.h, TypeAnal.h, Utilities.h, TypeAnal.cpp

Maintenance History:
====================
ver 1.0 : 6 Apr 16
- first release

*/

#include <iostream>
#include "../Parser/ActionsAndRules.h"
#include "../Parser/ConfigureParser.h"
#include "../Parser/Parser.h"
#include "../SymbolTable/SymbolTable.h"
#include "../SemiExp/SemiExp.h"
#include "../Tokenizer/Tokenizer.h"
using namespace Scanner;

class TypeAnal {
public:
	// ---------< return symbol table generated >------------
	SymbolTable<std::string, symTableRecord> table() { return _symTable; }
	
	// ------------< operator() performing type analysis for a single file >-----------
	void operator()(std::string fileSpec) {
		ConfigParseToConsole configure;
		Parser * pParser = configure.Build();
		try {
			if (pParser) {
				if (!configure.Attach(fileSpec)) {
					std::cout << "\n  could not open file " << fileSpec << std::endl;
					return;
				}
			}
			else {
				std::cout << "\n\n  parser not built";
				return;
			}
			while (pParser->next())
				pParser->parse();
			Repository * p_Repo = Repository::getInstance();
			symTableRecord * Record;
			std::vector<std::string> usings;
			// iterate over the scopestack and add elements to table
			while (p_Repo->scopeStack().size() > 0) {
				astNode elem = p_Repo->scopeStack().pop();
				std::string key = elem.name();
				Record = new symTableRecord();
				Record->fileName() = fileSpec;
				Record->type() = elem.type();
				Record->addClass(elem.getClass());
				Record->addNameSpace(elem.getNamespace());
				_symTable.addRecord(key, *Record);
				delete Record;
			}
		}
		catch (std::exception& ex)
		{
			std::cout << "\n\n  " << ex.what() << "\n\n";
		}
	}

private:
	SymbolTable<std::string, symTableRecord> _symTable;
};

#endif