#include"Term_Info.h"


Term_Info::Term_Info(const char* term) {
	if (term == nullptr) this->term = nullptr;
	else {
		this->term = new char[strlen(term) + 1];
		strcpy_s(this->term, strlen(term) + 1, term);
	}
}

// copy constructor
Term_Info::Term_Info(const Term_Info& obj)
{
	if (obj.term != nullptr)
	{
		this->term = new char[strlen(obj.term) + 1];
		strcpy_s(this->term, strlen(obj.term) + 1, obj.term);
	}

	listOfDoc = obj.listOfDoc;		// copy list
}

// copy assignment operator
Term_Info Term_Info::operator = (const Term_Info& obj) {
	
	if (this != &obj) {
		if (obj.term != nullptr)
			this->setTerm(obj.term);

		listOfDoc = obj.listOfDoc;		// copy list
	}
	return *this;
}


// return true, if two words are equal
bool Term_Info::operator == (const Term_Info& obj) {
	return (term == nullptr || obj.term == nullptr) ? (term == obj.term) : !strcmp(term, obj.term);
}

// return true, if this->term > obj.term
bool Term_Info::operator > (const Term_Info& obj) {
	if (term == nullptr || obj.term == nullptr) return false;
	
	return (strcmp(term, obj.term) > 0) ? true : false;
}

// return true, if this->term < obj.term
bool Term_Info::operator < (const Term_Info& obj) {
	if (term == nullptr || obj.term == nullptr) return false;

	return (strcmp(term, obj.term) < 0) ? true : false;
}


// insert a new document information
void Term_Info::insert(Doc_Info obj)
{
	listOfDoc.insertAtTail(obj);
}

// getters
char* Term_Info::getTerm() { return term; }
int Term_Info::getNumberOfDocs() { return listOfDoc.SIZE(); }

// return collective term frequency of a key term in all documents
int Term_Info::getTermFrequency()
{
	int total_tf = 0;
	List<Doc_Info>::Iterator itr;
	for (itr = listOfDoc.begin(); itr != listOfDoc.end(); ++itr) {
		total_tf += (*itr).getTF();
	}
	return total_tf;
}

// return term frequency of a term in a particular document
int Term_Info::getTermFrequency(const char* fileName)
{
	List<Doc_Info>::Iterator itr;
	for (itr = listOfDoc.begin(); itr != listOfDoc.end(); ++itr) {
		if (!strcmp((*itr).getDocId(), fileName)) {
			return (*itr).getTF();
		}
	}
	return 0;
}

// setter
void Term_Info::setTerm(const char* _term) {
	if (term != nullptr) delete[] term;

	term = new char[strlen(_term) + 1];
	strcpy_s(term, strlen(_term) + 1, _term);
}

// increase term freuency of a particular file by 'n' that contain this key term
void Term_Info::increaseTF(const char* fileName, int n)
{
	List<Doc_Info>::Iterator itr;
	for (itr = listOfDoc.begin(); itr != listOfDoc.end(); ++itr) {
		if (!strcmp((*itr).getDocId(), fileName)) {
			(*itr).increaseTF(n);
		}
	}
}

std::ostream& operator << (std::ostream& _cout, Term_Info& obj) {
	if (&obj != nullptr) {
		
		if (obj.term != nullptr)
			std::cout << "'" << obj.term << "'";
		
		if(obj.listOfDoc.SIZE() > 0)
			std::cout << "\t\t\t--->\t";

		List<Doc_Info>::Iterator itr;
		for (itr = obj.listOfDoc.begin(); itr != obj.listOfDoc.end();) {
			Doc_Info temp = *(itr);
			std::cout << temp;
			++itr;
			if (itr != obj.listOfDoc.end())
				std::cout << ", ";
		}
	}
	return _cout;
}

void Term_Info::print()
{
	std::cout << term;
	std::cout << "\t\t\t--->\t";

	List<Doc_Info>::Iterator itr;
	for (itr = listOfDoc.begin(); itr != listOfDoc.end();) {
		Doc_Info temp = *(itr);
		std::cout << (temp);
		++itr;
		if (itr != listOfDoc.end())
			std::cout << ", ";
	}
}

// return document's id based on the index
char* Term_Info::getDocId(int index)
{
	if (index < 0 && index >= listOfDoc.SIZE()) return nullptr;

	int i = 0;
	List<Doc_Info>::Iterator itr;
	for (itr = listOfDoc.begin(); itr != listOfDoc.end(); ++itr, ++i) {
		if (i == index) {
			return (*(itr)).getDocId();
		}
	}
}

// destructor
Term_Info::~Term_Info()
{
// deallocate memory
	if (term != nullptr) delete[] term;
}
