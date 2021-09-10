#include "Doc_Info.h"

// constructors
Doc_Info::Doc_Info() : docId(nullptr), tf(1), numOfTerms(1) {}
Doc_Info::Doc_Info(const char* _docId, int _tf, int _numOfTerms)
{
	tf = _tf;
	numOfTerms = _numOfTerms;
	docId = new char[strlen(_docId) + 1];
	strcpy_s(docId, strlen(_docId) + 1, _docId);
}
Doc_Info::Doc_Info(const Doc_Info& obj)
{
	tf = obj.tf;
	numOfTerms = obj.numOfTerms;
	docId = new char[strlen(obj.docId) + 1];
	strcpy_s(docId, strlen(obj.docId) + 1, obj.docId);
}

// overload assignment operator
Doc_Info Doc_Info::operator = (const Doc_Info& obj) {
	if (&obj != this) {
		if (docId != nullptr) delete[] docId;

		this->tf = obj.tf;
		this->numOfTerms = obj.numOfTerms;

		docId = new char[strlen(obj.docId) + 1];
		strcpy_s(docId, strlen(obj.docId) + 1, obj.docId);
	}
	return *this;
}

// setters
void Doc_Info::setTF(int _tf) { tf = _tf; }
void Doc_Info::increaseTF(int n) { tf += n; }
void Doc_Info::setNumOfTerms(int n) { numOfTerms = n; }
void Doc_Info::increaseTerms() { ++numOfTerms; }
void Doc_Info::setDocIDd(const char* _docId)
{
	if (docId != nullptr) delete[] docId;

	docId = new char[strlen(_docId) + 1];
	strcpy_s(docId, strlen(_docId) + 1, _docId);
}

// getters
int Doc_Info::getTF() { return tf; }
char* Doc_Info::getDocId() { return docId; }

// return true, if 'str1' is alphabetically greater than 'str2'
bool Doc_Info::isGreater(const char* str1, const char* str2)
{
	if (!strcmp(str1, str2)) return false;

	int size1 = strlen(str1);
	int size2 = strlen(str2);

	for (int i = 0; i < size1 && i < size2; i++) {
		if (str1[i] > str2[i]) return false;
	}

	return (size1 <= size2);
}

// NOTE: check according to "Ranking Rules"
// return true, if this is greater than obj
bool Doc_Info::operator >(const Doc_Info& obj)
{
	// RULE #1: document with more number of key terms
	if (numOfTerms > obj.numOfTerms) return true;

	// RULE #2: document with more term frequency
	if (numOfTerms == obj.numOfTerms) {
		if (tf > obj.tf) {
			return true;
		}
		else if (tf == obj.tf)
		{
			// RULE #3: Ranked documents alphabatically by 'Document's ID'
			if (isGreater(docId, obj.docId)) {
				return true;
			}
		}
	}
	return false;
}

// print a documnent's information 
std::ostream& operator << (std::ostream& _cout, Doc_Info& obj)
{
	std::cout << obj.getDocId() << " : " << obj.getTF();
	return _cout;
}

// destructor
Doc_Info::~Doc_Info()
{
	if (docId != nullptr) delete[] docId;
}

