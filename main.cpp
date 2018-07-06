#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <cctype>
#include <functional>
#include "DirNode.h"
#include "FSTree.h"
#include "myVector.h"

using namespace std;

// prototype of functions
void FSTreeTraversal(DirNode *, string, myVector &, FSTree);
string stripNonAlphaNum(string);

int main(int argc, char *argv[])
{
    if (argc != 2) 
    {
        cerr << "Usage:   ./gerp directory";
        cerr << " your directory is not a valid directory" << endl;
        exit(EXIT_FAILURE);
    }

    myVector dot;
    FSTree fall(argv[1]);
    bool insensitive = false;
    string input1;
    string DirectoryToIndex = "";

    // user enters executable & directory to index in command line
    // user gets prompted for a word
    if (argc == 2) 
    {
        // tree is built
        FSTreeTraversal(fall.get_root(), DirectoryToIndex, dot, fall);
        cout << "Query? " << endl;
        while (cin >> input1)
        {
            if (input1 == "@q" || input1 == "@quit")
            {
                cout << "Goodbye! Thank you and have a nice day.\n";
                exit(1);
            }
            if (input1 == "@i" || input1 == "@insensitive")
            {
                insensitive = true;
                cin >> input1;
                size_t size = input1.length();
                for (size_t i = 0; i < size; i++)
                    if (isupper(input1[i]))
                        input1[i] = tolower(input1[i]);
            }
            input1 = stripNonAlphaNum(input1);
            dot.searchIndex(input1);
        }
    }
    return 0;
}

void FSTreeTraversal(DirNode *curr, string path, myVector &dot, FSTree fall)
{
    string directory = path + curr->get_name() + "/";
    string input;
    word book;
    ifstream infile;
    if (curr->is_empty())
        return;
    else 
    {
        // if root doesn't point to a leaf
        if (curr->has_subdir())
        {
            int num_subdirs = curr->num_subdirs();
            for (int i = 0; i < num_subdirs; i++)
                FSTreeTraversal(curr->get_subdir(i), directory, dot, fall);
        }
        // if root points to a leaf
        if (curr->has_files()) 
        {
            int num_files = curr->num_files();
            for (int i = 0; i < num_files; i++) 
            {
                infile.open(directory + curr->get_file(i));
                book.linenum = 0;
                if (infile.is_open()) 
                {
                    while(!infile.eof()) 
                    {
                        getline(infile, input);
                        book.sentence = input;
                        book.linenum++;
                        stringstream line(input);
                        while (!line.eof())
                        {
                            line >> book.key;
                            book.actual_word = stripNonAlphaNum(book.actual_word);
                            book.file_path = directory + curr->get_file(i);
                            dot.add(book.key, book.file_path, book.sentence, 
                                    book.linenum, book.actual_word);
                        } 
                    }
                }   
                infile.close();
            }
        }
        // prints name of file
        path + curr->get_name();
    }
}

// implementation of prototype function
// takes in a string and returns a string
string stripNonAlphaNum(string input) 
{
    // initializes
    size_t i = 0;
    size_t size = input.length();
    while (i < size) 
    {
        // checks if string is a alnum
        // if not, it makes it one
        if (!isalnum(input[i]) || input[i] == ' ') 
        {
            input.erase(i,1);
            size--;
        }
        else
            i++;
    }
    return input;
}
