// DS Assignment 5
#include<iostream>
#include"Search_Engine.h"


 //input a file name
char* inputFileName() {
	char file[1000] = { '\0' };

	std::cout << "Enter File Name: ";
	std::cin >> file;

	char* fileName = new char[strlen(file) + 1];
	strcpy_s(fileName, strlen(file) + 1, file);

	return fileName;

}

// return list of input files
char** Input_Files(int& numOfFiles)
{
	std::cout << "Enter Number Of Files: ";
	std::cin >> numOfFiles;

	if (numOfFiles < 1) return nullptr;

	char** listOfFiles = new char* [numOfFiles];
	for (int i = 0; i < numOfFiles; ++i) {
		listOfFiles[i] = inputFileName();
	}

	return listOfFiles;
}

 //input query from the end-user
char* Input_Query() {
	char query[5000] = { '\0' };
	std::cout << "Type Your Query: ";
	std::cin.ignore();
	std::cin.getline(query, 5000);

	char* queryRet = new char[strlen(query) + 1];
	strcpy_s(queryRet, strlen(query) + 1, query);

	return queryRet;
}


int main() {
	Search_Engine se;

	int numOfFiles = 0;
	char** listOfDocs = nullptr;

	char choice = 0;
	bool isBreak = false;
	while (!isBreak) {
		system("cls");
		std::cout << "Press 1 to add File\n";
		std::cout << "Press 2 to view index\n";
		std::cout << "Press 3 to search query\n";
		std::cout << "Press 4 to exit\n";
		std::cin >> choice;

		switch (choice) {
		case '1':
		{
			listOfDocs = Input_Files(numOfFiles);			// input files
			se.Create_Index(listOfDocs, numOfFiles);
			system("pause");
			break;
		}
		case '2':
		{
			se.printIndex();
			system("pause");
			break;
		}
		case '3':
		{
			char* query = Input_Query();
			se.Search_Documents(query);

			if (query != nullptr) delete[] query;
			system("pause");
			break;
		}
		default:
			isBreak = true;
			break;
		}
	}
	// deallocate memory
	for (int i = 0; i < numOfFiles; i++) {
		if (listOfDocs[i] != nullptr)
			delete[] listOfDocs[i];
	}
	if (listOfDocs != nullptr)
		delete[] listOfDocs;

	return 0;
}





