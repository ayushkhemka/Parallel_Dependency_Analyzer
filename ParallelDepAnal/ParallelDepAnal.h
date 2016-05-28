#ifndef PARALLELDEPANAL_H
#define PARALLELDEPANAL_H

/////////////////////////////////////////////////////////////////////
//  ParallelDepAnal.h - dependency analysis for a set of files     //
//  ver 1.0                                                        //
//                                                                 //
//  Lanaguage:     Visual C++ 2016                                 //
//  Application:   CSE 687 Project #3 Spring 2016                  //
//  Author:				 Ayush Khemka, Syracuse University							 //
/////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This module inputs a directory path, searches for files inside the
directory tree, runs type analysis on each of the files, merges the
individual symbol tables, then runs dependency analysis for each file,
and reports the final merged table.
This modules makes use of the services provided by the Tasks package.
The tasks are used to start up a specified number of threads, and do
some specified work. File search starts up 1 thread, and each of the
analysis starts up 4 threads. This speeds up performance by a scale
of 4 for the overall system.

Public Interface:
=================
ParallelDepAnal pda;
pda.fileSearch(std::string path, std::vector<std::string> patterns);
pda.doTypeAnal(DataStore& ds);
pda.doDepAnal(DataStore&ds, AnalTable& table);

Build Process:
==============
Required files
- ActionsAndRules.h, ConfigureParser.h, Cpp11-BlockingQueue.h,
DataStore.h, DepAnal.h, FileMgr.h, FileSystem.h, itokcollection.h,
ParallelDepAnal.h, Parser.h, QueuedWorkItems.h, SemiExp.h,
SymbolTable.h, symTableRecord.h, Tasks.h, Tokenizer.h,
TypeAnal.h, Utilities.h, ParallelDepAnal.cpp

Maintenance History:
====================
ver 1.0 : 6 Apr 16
- first release

*/

#include <iostream>
#include "../Tasks/Tasks.h"
#include "../DataStore/DataStore.h"
#include "../FileMgr/FileMgr.h"
#include "../TypeAnal/TypeAnal.h"
#include "../DepAnal/DepAnal.h"
#include "../SymbolTable/SymbolTable.h"
#include "../symTableRecord/symTableRecord.h"
using namespace Scanner;

using AnalTable = SymbolTable<std::string, symTableRecord>;
using DepTable = SymbolTable<std::string, std::vector<std::string>>;

class ParallelDepAnal {
public:
	DataStore searchFiles(std::string path, std::vector<std::string> patterns);
	AnalTable doTypeAnal(DataStore& ds);
	DepTable doDepAnal(DataStore& ds, AnalTable table);
	void mergeAnalTable(std::vector<AnalTable>& vecAnalTable);
	void mergeDepTable(std::vector<DepTable>& vecDepTable);
private:
	AnalTable analTable;
	DepTable depTable;
	Tasks<DataStore> fileSearchTask;
	Tasks<SymbolTable<std::string, symTableRecord>> analTask;
	Tasks<SymbolTable<std::string, std::vector<std::string>>> depTask;
};

// ----------< search for files in a specified directory with specified patterns >------------
DataStore ParallelDepAnal::searchFiles(std::string path, std::vector<std::string> patterns) {
	DataStore ds;
	FileMgr fm(path, ds);
	for (auto pattern : patterns) fm.addPattern(pattern);
	fileSearchTask.start(1);
	Work<DataStore> fileSearch = [&fm, &ds]() {
		fm.search();
		return ds;
	};
	fileSearchTask.doThreadWork(fileSearch);
	fileSearchTask.stop();
	return ds;
}

// -----------< do type analysis for a specified set of files >-------------
AnalTable ParallelDepAnal::doTypeAnal(DataStore& ds) {
	analTask.start(4);
	for (auto fileSpec : ds) {
		TypeAnal analyzer;
		Work<SymbolTable<std::string, symTableRecord>> anal = [&analyzer, &fileSpec]() {
			analyzer(fileSpec); return analyzer.table();
		};
		analTask.doThreadWork(anal);
	}
	analTask.stop();
	mergeAnalTable(analTask.getResult());
	return analTable;
}

// ------------< do dependency analysis for a set of files
//							 against a symbol table >---------------
DepTable ParallelDepAnal::doDepAnal(DataStore& ds, AnalTable table) {
	depTask.start(4);
	for (auto fileSpec : ds) {
		DepAnal depanal;
		Work<SymbolTable<std::string, std::vector<std::string>>> anal2 = [&depanal, &fileSpec, &table]() {
			depanal(fileSpec, table); return depanal.table();
		};
		depTask.doThreadWork(anal2);
	}
	depTask.stop();
	mergeDepTable(depTask.getResult());
	return depTable;
}

// --------------< merge symbol tables of individual files >--------------
void ParallelDepAnal::mergeAnalTable(std::vector<AnalTable>& vecAnalTable) {
	for (auto res : vecAnalTable) {
		for (auto record : res) {
			analTable.addRecord(record.first, record.second);
		}
	}
}

// -------------< merge dependency tables of individual files >-------------
void ParallelDepAnal::mergeDepTable(std::vector<DepTable>& vecDepTable) {
	for (auto res : vecDepTable) {
		for (auto record : res) {
			depTable.addRecord(record.first, record.second);
		}
	}
}

#endif