#ifndef SYMTABLERECORD_H
#define SYMTABLERECORD_H

/////////////////////////////////////////////////////////////////////
//  symTableRecord.h - define records stored in symbol table       //
//  ver 1.0                                                        //
//                                                                 //
//  Lanaguage:     Visual C++ 2016                                 //
//  Application:   CSE 687 Project #3 Spring 2016                  //
//  Author:				 Ayush Khemka, Syracuse University							 //
/////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This module defines the Value for type analysis symbol table.
The table generated from the type analysis contains fields for
storing the type, file name, namespaces, classes. Classes are
not displayed on the console. It can be extended to store multiple
namespaces and multiple files in order to resolve overloads and
overrides. Public methods allow to browse through the table and
set/retrieve values.
Public methods allow for easy viewing of the table. These are
defined inline to avoid multiple definitions.

Build Process:
==============
Required files
- symTableRecord.h, symTableRecord.cpp

Maintenance History:
====================
ver 1.0 : 6 Apr 16
- first release
*/

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

class symTableRecord { // application specific
public:
	using Name = std::string;
	using Namespace = std::string;
	using Class = std::string;
	using Classes = std::vector<std::string>;
	using Type = std::string;
	using FileName = std::string;
	using Namespaces = std::vector<Namespace>;
	using iterator = std::vector<std::string>::iterator;

	Type& type() { return _type; }
	Namespaces& namespaces() { return _namespaces; }
	Classes& classes() { return _classes; }
	FileName& fileName() { return _file; }
	void addNameSpace(const Namespace& ns)
	{
		if (_namespaces.size() == 1 && _namespaces[0] == "") {
			_namespaces[0] = ns;
			return;
		}
		if (find(_namespaces.begin(), _namespaces.end(), ns) == _namespaces.end())
			_namespaces.push_back(ns);
	}
	void addClass(const Class& cl)
	{
		if (_classes.size() == 1 && _classes[0] == "") {
			_classes[0] = cl;
			return;
		}
		if (find(_classes.begin(), _classes.end(), cl) == _classes.end())
			_classes.push_back(cl);
	}
	size_t numberOfNameSpaces() { return _namespaces.size(); }
	iterator begin() { return _namespaces.begin(); }
	iterator end() { return _namespaces.end(); }
	Namespace operator[](size_t n) const
	{
		if (n < 0 || n >= _namespaces.size())
			throw(std::exception("index out of range"));
		return _namespaces[n];
	}
private:
	std::string _type;
	std::string _file;
	std::vector<std::string> _namespaces;
	std::vector<std::string> _classes;
};

inline void showRecordHeader()
{
	std::cout << std::left << "\n  ";
	std::cout << std::setw(20) << "Name";
	std::cout << std::setw(12) << "Type";
	std::cout << std::setw(30) << "Filename";
	//std::cout << std::setw(16) << "Classes";
	std::cout << std::setw(16) << "Namespaces" << "\n";
	std::cout << std::setw(20) << std::string(6, '-');
	std::cout << std::setw(12) << std::string(10, '-');
	std::cout << " " << std::setw(30) << std::string(14, '-');
	//std::cout << std::setw(16) << std::string(10, '-');
	std::cout << std::setw(16) << std::string(14, '-');
}
inline void showRecord(std::string name, symTableRecord& record)
{
	std::cout << "\n  ";
	std::cout << std::setw(20) << name;
	std::cout << std::setw(12) << record.type();
	// truncate file name for better formatting, file name
	if (record.fileName().length() > 16)
		std::cout << std::setw(30) << "..." + record.fileName().substr(record.fileName().length() - 16);
	else
		std::cout << std::setw(30) << record.fileName();
	//for (auto cl : record.classes())
		//std::cout << std::setw(16) << cl;
	for (auto ns : record.namespaces())
		std::cout << std::setw(16) << ns;
}
#endif