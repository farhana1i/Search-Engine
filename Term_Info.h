#pragma once
#include"Doc_Info.h"
#include"List.h"

class Term_Info
{
private:
	char* term;						// key term/word
	List<Doc_Info> listOfDoc;		// list of documents that contain this term
public:
	// constructor
	Term_Info(const char* term = nullptr);
	Term_Info(const Term_Info& obj);

	// copy assignment operator
	Term_Info operator = (const Term_Info& obj);

	bool operator == (const Term_Info& obj);		// return true, if two words are equal
	bool operator > (const Term_Info& obj);			// return true, if greater
	bool operator < (const Term_Info& obj);			// return true, if smaller

	friend std::ostream& operator << (std::ostream& _cout, Term_Info& obj);	// to print a term's detail

	// insert a new document information
	void insert(Doc_Info obj);

	// getters
	int getNumberOfDocs();
	char* getTerm();
	char* getDocId(int i);


	// return collective term frequency of a key term in all documents
	int getTermFrequency();

	// return term frequency of a term in a particular document
	int getTermFrequency(const char* fileName);

	// setters
	void setTerm(const char* _term);

	// increase term freuency of a particular file by 'n' that contain this key term
	void increaseTF(const char* fileName, int n = 1);

	// print a key term with list of documents that contain it
	void print();

	// destructor
	~Term_Info();
};

