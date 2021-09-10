#pragma once
#include<iostream>

class Doc_Info
{
private:
	char* docId;		// document id
	int tf;				// frequency of term in a document
public:
	int numOfTerms;		// number of terms of a query, a documnent contains

	// constructors
	Doc_Info();
	Doc_Info(const char* _docId, int _tf = 1, int _numOfTerms = 1);
	Doc_Info(const Doc_Info& obj);

	Doc_Info operator = (const Doc_Info& obj);	// overload assignment operator

	// setters
	void setTF(int _tf);
	void increaseTF(int n = 1);
	void setDocIDd(const char* _docId);
	void setNumOfTerms(int n);
	void increaseTerms();

	// getters
	int getTF();
	char* getDocId();

	// print document's id with term frequency
	friend std::ostream& operator << (std::ostream& _cout, Doc_Info& obj);

	// return if 'str1' is alphabetically lower than 'str2'
	bool isGreater(const char* str1, const char* str2);

	// NOTE: check according to "Ranking Rules"
	// return true, if this is greater than obj
	bool operator >(const Doc_Info& obj);

	// destructor
	~Doc_Info();
};

