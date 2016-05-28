#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

/////////////////////////////////////////////////////////////////////
//  SymbolTable.h - generic symbol table for a key, value pair     //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2016, SP1                            //
//  Platform:      Dell Precision T7400, Vista Ultimate SP1        //
//  Application:   CSE 687 Project #3 Spring 2016                  //
//  Author:				 Ayush Khemka, Syracuse University							 //
//								 aykhemka@syr.edu, 538044584										 //
/////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This module is a generic key/value pair symbol table which stores
file names as key, and a particular type as value. For the type analysis
we use a special record type as the value, defined in a different
package.
This module makes heavy use of the unordered_map, and behaves very
similar to that, with added functionality.

Build Process:
==============
Required files
- SymbolTable.h, symTableRecord.h (if doing type analysis)

Maintenance History:
====================
ver 1.0 : 6 Apr 16
- first release

*/

#include <unordered_map>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "../symTableRecord/symTableRecord.h"

template<typename Key, typename Value>
class SymbolTable {
public:
	using Record = std::pair<Key, Value>;
	using iterator = typename std::unordered_map<Key, Value>::iterator;
	
	// -------------< insert into map >------------
	void addRecord(const Key& key, const Value& value) {
		_symTable.insert(std::pair<Key, Value>(key, value));
	}

	// ----------< access operator >------------
	Value operator[](const Key key) {
		if (_symTable.size() == 0 || key == "") throw std::exception("invalid access");
		return _symTable[key];
	}

	size_t size() { return _symTable.size(); }
	iterator find(const Key& key) {
		iterator it = _symTable.begin();
		for (it = _symTable.begin(); it != _symTable.end(); ++it)
			if (it->first == key) return it;
		return _symTable.end();
	}

	iterator begin() { return _symTable.begin(); }
	iterator end() { return _symTable.end(); }
private:
	std::unordered_map<Key, Value> _symTable;
};

inline void showTable(SymbolTable<std::string, symTableRecord> table) {
	showRecordHeader();
	for (auto record : table)
		showRecord(record.first, record.second);
}

#endif