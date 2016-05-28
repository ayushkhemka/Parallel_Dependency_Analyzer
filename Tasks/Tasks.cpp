#include <iostream>
#include <vector>
#include "Tasks.h"
#include "../DataStore/DataStore.h"
#include "../FileMgr/FileMgr.h"
#include "../Utilities/Utilities.h"
#include "../TypeAnal/TypeAnal.h"
#include "../DepAnal/DepAnal.h"

using namespace Utilities;
using Utils = StringHelper;

#ifdef TEST_TASKS

int main() {
	Utils::Title("Testing tasks class for type analysis");
	putline();

	SymbolTable<std::string, symTableRecord> analTable;
	SymbolTable<std::string, std::vector<std::string>> depTable;
	DataStore ds;
	FileMgr fm("..\\..\\Project2OOD\\TestFiles", ds);
	fm.addPattern("*.h");
	fm.addPattern("*.cpp");
	//fm.search();
	
	Tasks<DataStore> t3;
	t3.start(1);
	Work<DataStore> fileSearch = [&fm, &ds]() {
		fm.search();
		return ds;
	};
	t3.doThreadWork(fileSearch);
	t3.stop();

	Tasks<SymbolTable<std::string, symTableRecord>> t1;
	t1.start(4);
	for (auto fileSpec : ds) {
		//std::cout << "\n  checking file " << fileSpec << std::endl;
		TypeAnal analyzer;
		Work<SymbolTable<std::string, symTableRecord>> anal = [&analyzer, &fileSpec]() {
			analyzer(fileSpec); return analyzer.table();
		};
		t1.doThreadWork(anal);
	}
	t1.stop();

	Utils::title("Results of type analysis");
	putline();

	for (auto res : t1.getResult()) {
		for (auto record : res) {
			analTable.addRecord(record.first, record.second);
		}
	}
	showTable(analTable);

	Tasks<SymbolTable<std::string, std::vector<std::string>>> t2;
	t2.start(4);
	for (auto fileSpec : ds) {
		//std::cout << "\n  checking file " << fileSpec << std::endl;
		DepAnal depanal;
		Work<SymbolTable<std::string, std::vector<std::string>>> anal2 = [&depanal, &fileSpec, &analTable]() {
			depanal(fileSpec, analTable); return depanal.table();
		};
		t2.doThreadWork(anal2);
	}
	t2.stop();
	for (auto res : t2.getResult()) {
		for (auto record : res) {
			depTable.addRecord(record.first, record.second);
		}
	}

	putline();
	Utils::title("Results of dependency analysis");
	putline();
	for (auto result : depTable) {
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