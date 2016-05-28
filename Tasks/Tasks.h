#ifndef TASKS_H
#define TASKS_H

/////////////////////////////////////////////////////////////////////
//  Tasks.h - start up threads on threadpool				               //
//  ver 1.0                                                        //
//                                                                 //
//  Lanaguage:     Visual C++ 2016                                 //
//  Application:   CSE 687 Project #3 Spring 2016                  //
//  Author:				 Ayush Khemka, Syracuse University							 //
/////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
The tasks package creates a specified number of threads on the
threadpool and passes callable objects to be processed. It collects
the results of the execution in a private vector. There is only one
threadpool created for the whole application, but the tasks are
different for different purposes, since this module is templatized.

Public Interface:
=================
Tasks<...> t;
t.start(int n);
t.doThreadWork(CallObj& co);
t.getResults();

Build Process:
==============
Required files
- Tasks.h, QueuedWorkItems.h, Utilities.h, Tasks.cpp

Maintenance History:
====================
ver 1.0 : 6 Apr 2016
- first release

*/

#include <vector>
#include "../CppThreadTechniques/QueuedWorkItems/QueuedWorkItems.h"

template<typename CallObj>
using Work = std::function<CallObj()>;

template<typename CallObj>
class Tasks {
public:
	void start(int n) {
		numberOfThreads = n; result.clear();
		processor.start(n);
	}
	void doThreadWork(Work<CallObj>& co) {
		processor.doWork(&co);
		result.push_back(processor.result());
	}
	void stop() {
		for (int i = 0; i < numberOfThreads; i++)
			processor.doWork(nullptr);
		processor.wait();
	}
	std::vector<CallObj> getResult() { return result; }
private:
	int numberOfThreads;
	ProcessWorkItem<CallObj> processor;
	std::vector<CallObj> result;
};
#endif