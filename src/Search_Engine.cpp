#include "Search_Engine.h"

// constructors
Search_Engine::Search_Engine() {
	
}

// return true, if word is already present in 'Index'
bool Search_Engine::isWordPresent(const char* word) {
	Term_Info* term = nullptr;
	return Index.search(word, term);
}

// return true, if word is present in list of words
bool Search_Engine::isWordPresent(char**& listOfWords, int lastIndex, const char* word)
{
	for (int i = 0; i < lastIndex; i++)
	{
		if (listOfWords[i] != nullptr) {
			if (!strcmp(listOfWords[i], word)) {
				return true;
			}
		}
	}
	return false;
}

// return true, if document's Id is present
bool Search_Engine::isDocPresent(List<Doc_Info>& listOfDocs, const char* doc)
{
	List<Doc_Info>::Iterator itr;
	for (itr = listOfDocs.begin(); itr != listOfDocs.end(); ++itr) {
		Doc_Info temp = *(itr);
		if (!strcmp(temp.getDocId(), doc))
			return true;
	}
	return false;
}

//convert an uppercase word into small case
char* Search_Engine::upperToSmallCase(const char* word)
{
	int size = strlen(word);
	char* updated_word = new char[size + 1];

	for (int i = 0; i < size; ++i)
	{
		if (word[i] >= 65 && word[i] <= 90) {
			updated_word[i] = word[i] + 32;
		}
		else {
			updated_word[i] = word[i];
		}
	}
	updated_word[size] = '\0';
	return updated_word;
}

// return true, if fileName is match with any of the present file names
bool Search_Engine::matchFile(const char* fileName, Term_Info* temp)
{
	if (temp == nullptr) return false;

	for (int i = 0; i < temp->getNumberOfDocs(); ++i)
	{
		if (!strcmp(fileName, temp->getDocId(i)))
			return true;
	}
	return false;
}

// remove extension from a file name
char* Search_Engine::removeExtension(const char* file)
{
	if (file == nullptr) return nullptr;

	int size = strlen(file);
	char* fileName = new char[size + 1];

	// remove extension from a file name
	int i = 0;
	for (; i < size; i++) {
		if (file[i] == '.')
			break;
		fileName[i] = file[i];
	}fileName[i++] = '\0';

	return fileName;
}

// faster way to read data from a file
// returns a string which contain the whole data
std::string Search_Engine::readFile(const std::string& fileName)
{
	std::ifstream ifs(fileName.c_str(), std::ios::in | std::ios::binary | std::ios::ate);

	std::ifstream::pos_type fileSize = ifs.tellg();
	ifs.seekg(0, std::ios::beg);

	std::vector<char> bytes(fileSize);
	ifs.read(bytes.data(), fileSize);

	return std::string(bytes.data(), fileSize);
}

// convert file data into a list of words
// create index for each unique term
// to create an index of all unique terms present in a file
void Search_Engine::Create_Index(const char* file)
{
	// open file
	std::fstream fin(file);
	if (fin.fail()) {
		std::cout << "Fail to open " << file << " file\n";
		return;
	}

	char** listOfWords = nullptr;
	int numOfWords = 0;

	// read file data in an array 
	std::string dataString = readFile(file);
	char* data = &(dataString[0]);

	// tokenize data into list of words
	tokenize(data, listOfWords, numOfWords);

	// remove extension from file name
	char* fileName = removeExtension(file);

	// create index for all unique words
	for (int i = 0; i < numOfWords; ++i) {
		char* word = listOfWords[i];

		// if word is not present in Index
		if (!isWordPresent(word))
		{
			Doc_Info docInfo(fileName);
			Term_Info newTerm(listOfWords[i]);
			newTerm.insert(docInfo);

			Index.insert(newTerm);
		}
		else {
			Term_Info* newTerm = nullptr;
			Index.search(word, newTerm);

			if (newTerm == nullptr) return;

			// if file is not present
			if (!matchFile(fileName, newTerm)) {
				Doc_Info newDoc(fileName);
				newTerm->insert(newDoc);
			}
			else {
				// if file exist, increase term frequency
				newTerm->increaseTF(fileName);
			}

		}
	}// end for loop

	// deallocate memory
	if (fileName != nullptr) delete[] fileName;

	for (int i = 0; i < numOfWords; i++) {
		if (listOfWords[i] != nullptr)
			delete[] listOfWords[i];
	}
	if (listOfWords != nullptr)
		delete[] listOfWords;

	fin.close();			// close file
}

// tokenize input into list of words
void Search_Engine::tokenize(const char* input, char**& listOfWords, int& numOfWords)
{
	int capacity = 0;					// capacity of list of words

	char word[5000] = { '\0' };			// a single word in query
	int word_size = 0;

	int input_size = strlen(input);

	// tokenize an input into list of words
	for (int i = 0; i < input_size; i++)
	{
		if (input[i] != ' ' && input[i] != '\n') {
			word[word_size++] = input[i];
		}
		if (input[i] == ' ' || input[i] == '\n' || i + 1 == input_size) {
			word[word_size] = '\0';

			if (capacity == 0) {
				capacity = 1;
				listOfWords = new char* [capacity];
			}
			else if (numOfWords == capacity)
			{
				capacity *= 2;
				char** temp = new char* [capacity];
				for (int i = 0; i < numOfWords; ++i) {
					temp[i] = listOfWords[i];
				}
				if (listOfWords != nullptr) delete[] listOfWords;
				listOfWords = temp;
			}

			char* updated_word = upperToSmallCase(word);

			listOfWords[numOfWords] = new char[strlen(updated_word) + 1];
			strcpy_s(listOfWords[numOfWords], strlen(updated_word) + 1, updated_word);
			++numOfWords;

			if (updated_word != nullptr) delete[] updated_word;

			word_size = 0;
		}
	}
}

// to create an index
void Search_Engine::Create_Index(char** Docs, int n)
{
	if (n == 0) return;			// if there is no file

	// create index of terms present in all file
	for (int i = 0; i < n; ++i)
	{
		if (Docs[i] != nullptr) {
			Create_Index(Docs[i]);
		}
	}
}

// search for each term of query in the documents
void Search_Engine::Search_Documents(const char* query)
{
	char** listOfWords = nullptr;
	int numOfWords = 0;
	tokenize(query, listOfWords, numOfWords);		// tokenize query

	List<Doc_Info> listOfDocs;

	// check for each unique term in query
	for (int i = 0; i < numOfWords; i++)
	{
		// if query word is not repeated
		if (!isWordPresent(listOfWords, i, listOfWords[i]))
		{
			// if query word is not found in index
			Term_Info* newTerm = nullptr;
			if (!Index.search(listOfWords[i], newTerm)) continue;

			for (int k = 0; k < newTerm->getNumberOfDocs(); k++)
			{
				// copy document's ID
				char* docId = new char[strlen(newTerm->getDocId(k)) + 1];
				strcpy_s(docId, strlen(newTerm->getDocId(k)) + 1, newTerm->getDocId(k));

				// if document is not present
				if (!isDocPresent(listOfDocs, docId)) {
					Doc_Info newDoc(docId, newTerm->getTermFrequency(docId));
					listOfDocs.insertAtTail(newDoc);
				}
				else {
					// if document exists
					List<Doc_Info>::Iterator itr;
					for (itr = listOfDocs.begin(); itr != listOfDocs.end(); ++itr) {
						if (!strcmp((*itr).getDocId(), docId)) {
							(*itr).increaseTF(newTerm->getTermFrequency(docId));
							(*itr).increaseTerms();
						}
					}
				}
				if (docId != nullptr) delete[] docId;
			}

		}
	}

	// ranking using table
	rankList(listOfDocs);

	//print ranked list
	printRankedList(listOfDocs);

	for (int i = 0; i < numOfWords; i++) {
		if (listOfWords[i] != nullptr)
			delete[] listOfWords[i];
	}
	if (listOfWords != nullptr)
		delete[] listOfWords;
}

// ranked list according to rules
// (HINT: sorting list)
void Search_Engine::rankList(List<Doc_Info>& listOfDocs)
{
	List<Doc_Info>::Iterator i, j;
	for (i = listOfDocs.begin(); i != listOfDocs.end(); ++i)
	{
		List<Doc_Info>::Iterator max = i;
		for (j = i; j != listOfDocs.end(); ++j)
		{
			Doc_Info maxth((*(max)));
			Doc_Info jth((*(j)));
			if (jth > maxth) {
				max = j;
			}
		}
		if (i != max)
			listOfDocs.swapNodes(i, max);
		i = max;
	}
}

// print ranked list
void Search_Engine::printRankedList(List<Doc_Info>& listOfDocs)
{
	if (listOfDocs.begin() == listOfDocs.end()) {
		std::cout << "Word Not Found\n";
		return;
	};

	std::cout << "Ranked list: \n";
	List<Doc_Info>::Iterator itr;

	std::cout << "\tDocument\tTerm Frequency\t\tNo. Of Terms\n";

	for (itr = listOfDocs.begin(); itr != listOfDocs.end(); ++itr) {
		if ((itr) != nullptr) {
			std::cout << "\t" << (*(itr)).getDocId();
			std::cout << "\t\t\t" << (*(itr)).getTF();
			std::cout << "\t\t\t" << (*(itr)).numOfTerms;
			std::cout << std::endl;
		}
	}
}

// add a new document to Index
void Search_Engine::Add_Doc_to_Index(const char* fileName)
{
	if (fileName == nullptr) return;
	Create_Index(fileName);
}

// print all key terms with their information
void Search_Engine::printIndex() {
	Index.printTable();
}

// destructor
Search_Engine::~Search_Engine() {
	// do nothing
}
