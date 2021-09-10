#pragma once
#include"List.h"
#include"Vector.h"
#include<math.h>
#include<iostream>

template <class Type>
class Hash {
public:
	// constructors
	Hash(int size = 107) {
		this->numOfElements = 0;
		hashTable.setCapacity(size);
	}
	Hash(const Hash& obj) {
		this->hashTable = obj.hashTable;
		this->numOfElements = obj.numOfElements;
	}
	Hash operator = (const Hash& obj) {
		if (&obj != this) {
			this->hashTable = obj.hashTable;
			this->numOfElements = obj.numOfElements;
		}
		return *this;
	}


	// hash function to map key to hash table index for strings
	int hashString(const char* key, int cap) {
		const int p = 31;
		int hash_value = 0;
		long int p_pow = 1;

		for (int i = 0; i < strlen(key); ++i) {
			hash_value += ((int(key[i]) - 'a' + 1) * p_pow ) % cap;
			p_pow = (p_pow * p) % cap;
		}
		return hash_value % cap;
	}

	// to rehash table
	void reHash() 
	{
		Vector<List<Type>> temp(hashTable.Capacity());
		for (int i = 0; i < hashTable.Capacity(); ++i) {
			typename List<Type>::Iterator itr = hashTable[i].begin();
			for (; itr != hashTable[i].end(); ++itr) {
				temp[i].insertAtTail(*(itr));
			}
		}
		hashTable.setCapacity(2 * hashTable.Capacity());	// double the capacity
		for (int i = 0; i < temp.Capacity(); ++i) {
			typename List<Type>::Iterator itr = temp[i].begin();
			for (; itr != temp[i].end(); ++itr) {
				hashTable[hashString((*itr).getTerm(), hashTable.Capacity())].insertAtTail((*itr));
			}
		}
	}

	// insert new element
	void insert(Type element) 
	{
		++numOfElements;
		if (this->loadFactor() > 2.0) {
			reHash();
		}
		int ind = hashString(element.getTerm(), this->hashTable.Capacity());
		hashTable[ind].insertAtTail(element);
	}

	// insert new element
	void remove(const char* key) 
	{
		int ind = hashString(key, this->hashTable.Capacity());
		typename List<Type>::Iterator itr;
		for (itr = hashTable[ind].begin(); itr != hashTable[ind].end(); ++itr) 
		{
			if (!strcmp((*itr).getTerm(), key)) 
			{
				hashTable[ind].remove(itr);
				--numOfElements;
			}
		}
	}

	// insert new element
	bool search(const char* key, Type*& item)
	{
		int ind = hashString(key, this->hashTable.Capacity());
		typename List<Type>::Iterator itr; 
		for (itr = hashTable[ind].begin(); itr != hashTable[ind].end(); ++itr) {
			char* term = (*itr).getTerm();
			if (!strcmp(term, key)) {
				item = &(*(itr));
				return true;
			}
		}
		return false;
	}

	// to print hash table
	void printTable() {
		std::cout << "Capacity: " << this->hashTable.Capacity() << "\n";
		int j = 0;
		for (int i = 0; i < hashTable.Capacity(); ++i) {
			typename List<Type>::Iterator itr = hashTable[i].begin();
			for (; itr != hashTable[i].end(); ++itr, ++j) {
				std::cout<<"["<<j<<"]\t" << *(itr);
				std::cout << "\n";
			}
		}
	}
private:
	Vector<List<Type>> hashTable;
	int numOfElements;	// number of elements

	// return load factor of table
	inline float loadFactor() 
	{
		if (this->hashTable.Capacity() == 0) return 0.0;
		return float(numOfElements) / float(hashTable.Capacity());
	}
};