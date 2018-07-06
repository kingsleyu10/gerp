/* Description of file: This file contains my implementation for the vector 
class. In this impementation, 2D hash table is built and search function
is implemented here. */

#include <vector>
#include <string>
#include <cctype>
#include <cstdlib>
#include <functional>
#include <iostream>
#include "myVector.h"

using namespace std;

// hash function template is declared here
size_t myVector::hash_function(string key) 
{
	return hash<string>{}(key);
}

// default constructor
myVector::myVector() 
{
	maxSize = 997;
	tableSize = 0;
	myVec.resize(maxSize);
}

// destructor
myVector::~myVector() 
{
	myVec.clear();
}

// Function searchIndex
// Inputs: a string
// Returns: nothing
// Does: returns filepath, line # and sentence if a word is found
void myVector::searchIndex(string key) 
{
	size_t index = hash_function(key) % maxSize;
	bool found = false;
	size_t length = myVec[index].size();
	for (size_t i = 0; i < length; i++)
	{
		word value = myVec[index][i];
		// insensitive  & sensitive cases
		if (value.key == key || value.actual_word == key)
		{
			cout << value.file_path << ":" << value.linenum << ": ";
			cout << value.sentence << endl;
		}
		found = true;
	}
	if (found)
		return;
	else
	{
		cout << "query not found. Try with @insensitive or @i" << endl;
		return;
	}
}

// Function add 
// Inputs: 4 strings and an int
// Returns: nothing
// Does: inserts new node 
void myVector::add(string key, string file_path, string 
					sentence, int linenum, string actual_word) 
{
	word newNode;
	// if full, expand
	if (tableSize == maxSize)
		expand();
	// hash function is created
	size_t index = hash_function(key) % maxSize;
	newNode.key = key;
	newNode.file_path = file_path;
	newNode.sentence = sentence;
	newNode.linenum = linenum;
	newNode.actual_word = actual_word;

	(myVec[index]).push_back(newNode); 

	tableSize++; // total words in hash 
}

// Function expand
// Inputs: nothing
// Returns: nothing
// Does: resizes vector when all slots are filled
void myVector::expand() 
{
	// make a temp vector
	vector<vector<word> > temp;
	temp = myVec;
	// clears old vector
	myVec.clear();
	maxSize = maxSize * 3 + 2;
	myVec.resize(maxSize);
	tableSize = 0;

	for (size_t i = 0; i < temp.size(); i++)
	{
	 	if (!temp[i].empty())
	 	{
	 		for (size_t j = 0; j < temp[i].size(); j++)
			{	
				// re-hashes and re-inserts necessary data
				add(temp[i][j].key, temp[i][j].file_path, temp[i][j].sentence,
					temp[i][j].linenum, temp[i][j].actual_word);		
	 		}
	 	}	
	}
}

