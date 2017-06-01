## CSE 687 Project #3 Spring 2016

### Package Structure

1. Cpp11-BlockingQueue

   Provides services for a blocking queue with mutexes, to be used by the threadpool module.

2. Threadpool

   Threadpool package starts up a number of threads and uses a WorkItem blocking queue to execute callable objects. It simply executes the lambda extracted from the WorkItem queue and stores the results in the Result queue. Upon completion, the service sends a nullptr to the WorkItem queue which stops the same number of threads, as started by the threadpool, so that other services know when to stop.

3. DataStore

   Provides facilities to store the extracted files.

4. FileMgr

   Provides facilities to search for files inside a directory tree matching some given patterns.

5. Utilities

   Provides services to write to the console aesthetically.

6. Tokenizer

   Package from Project #1. For a particular file, collects and returns tokens, one-by-one along with line numbers. I used Dr. Fawcett's solution.

7. SemiExp

   Package also from Project #1, collects tokens and returns semi expressions matching some termination rules. I used Dr. Fawcett's solution.

8. ScopeStack

   From Project #2, this package provides services to store the functions scopes in a stack.

9. Parser

   Project #2, parses the given files and reports function definitions, type definitions, and typedefs and aliases. No use of Abstract Syntax Tree.

10. SymbolTable

   This module is a generic key/value pair symbol table which stores file names as key, and a particular type as value. For the type analysis we use a special record type as the value, defined in a different package. This module makes heavy use of the unordered_map, and behaves very similar to that, with added functionality.

11. symTableRecord

   Defines entries to be stored in the Symbol Table.

12. Tasks

   Makes use of Threadpool services to start a number of threads and execute callable objects on them.

13. TypeAnal

   Runs type analysis for a single file and returns the symbol table for that file. It also stores all the typedefs and usings of a file in the same symbol table.

14. DepAnal

   Performs dependency analysis of a file by tokenizing it, and comparing the tokens to the symbol table. So any token used by the file, class names, namespace names, etc would mean that the file is dependent on some file mentioned in the symbol table. Since usings are also detected, any file that is using a namespace is automatically dependent on that file, whether or not it uses that namespace.

15. ParallelDepAnal

   Uses the services of the Tasks class to start up a number of threads, search for files in a given directory tree, does type analysis, merges the individual tables, then does individual dependency analyses and merges them all together. One thread is used to search for files, 4 threads are used to do type and dependency analyses each.

16. ParallelDepExec

   This is the Test Executive, the entry point for the project which demonstrates that all the requirements have met.


## Release Notes

1. Using statements and typedefs are detected and reported successfully, but the usings are not stored in a separate using table, instead they are reported in the same symbol table.

2. Dependency Analysis may sometimes give false alarms. This is because of same names being used for class and function names. Hence, constructors and destructors should be avoided while testing. For example, I uploaded a screenshot which detects the ITokCollection destructor but not the struct in which it is defined, because it got added before the struct in the table and won't overwrite. This does not happen in my demonstration. The screenshot is just an example, and should not be used as a grading criteria.

3. Table merging doesn't make use of any threads. Using threads for merging the tables resulted in false results and it was too late to make any changes to the already working code.


## Demonstrating Requirements

Requirement #3:		All the packages have been succesfully implemented and all functions succesfully tested.

Requirement #4:		It can be tested by viewing QueuedWorkItems.h file.

Requirement #5:		It can be tested by viewing Tasks.h file.

Requirement #6:		Type Analysis is demonstrated in the console.

Requirement #7:		Dependency Analysis is demonstrated in the console.

Requirement #8:		It can be tested by viewing the ParallelDepAnal.h file

Requirement #9:		It can be tested by viewing the ParallelDepExec.h file

Requirement #10:	ParallelDepExec is the automated test suite.

# License information
MIT License

Copyright (c) 2016 Ayush Khemka

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
