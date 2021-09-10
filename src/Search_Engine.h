#ifndef  SEARCH_ENGINE
#define SEARCH_ENGINE

#include<iostream>
#include<fstream>
#include<vector>
#include"Hash.h"
#include"Term_Info.h"


class Search_Engine {
public:
	// constructors
	Search_Engine();

	// return true, if word is already present in 'Index'
	bool isWordPresent(const char* word);

	// return true, if word is present in list of words
	bool isWordPresent(char**& listOfWords, int lastIndex, const char* word);

	// return true, if document's Id is present
	bool isDocPresent(List<Doc_Info>& listOfDocs, const char* doc);

	//convert an uppercase word into small case
	char* upperToSmallCase(const char* word);

	// return true, if fileName is match with any of the present file names
	bool matchFile(const char* fileName, Term_Info* temp);

	// remove extension from a file name
	char* removeExtension(const char* file);

	// fastest way to read data from a file
	// returns a string which contain the whole data
	static std::string readFile(const std::string& fileName);

	// tokenize input into list of words
	void tokenize(const char* input, char**& listOfWords, int& numOfWords);

	// to create an index of unique terms present in 'n' files
	void Create_Index(char** Docs, int n);

	// to create an index of unique terms present in a file
	void Create_Index(const char* fileName);

	// search for each term of query in the documents
	void Search_Documents(const char* query);

	// add a new document to Index
	void Add_Doc_to_Index(const char* fileName);

	// ranked list according to rules
	void rankList(List<Doc_Info>& listOfDocs);

	// print ranked list
	void printRankedList(List<Doc_Info>& listOfDocs);

	// print all key terms with their information
	void printIndex();

	// destructor
	~Search_Engine();
private:
	Hash<Term_Info> Index;
};

#endif // !SEARCH_ENGINE