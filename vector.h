// Description of file: This file contains all functions for my vector class.

#ifndef MY_VECTOR_H_
#define MY_VECTOR_H_ 

#include <vector>
#include <iostream>
#include <string>

using namespace std;

struct word 
{
	string key;
	string file_path;
	string sentence;
	int linenum;
	string actual_word;
};

class myVector
{
	public:
		// default constructor
		myVector();
		// destructor
		~myVector();
		void expand();
		// find 
		void searchIndex(string key);
		// insert
		void add(string, string, string, int, string);
		size_t hash_function(string);
		vector<vector<word> > myVec;
		
	private:
		// capacity
		int maxSize; 
		// count
		int tableSize; 
	
};
#endif
