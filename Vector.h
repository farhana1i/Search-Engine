#pragma once

template <class Type>
class Vector {
private:
	Type* array;
	int size;		// number of elements in array
	int capacity;	// max size
public:
	// constructors
	Vector(int n = 1) {
		this->size = 0;
		if (n > 0) {
			this->capacity = n;
			this->array = new Type[this->capacity];
		}
		else {
			this->capacity = 1;
			this->array = new Type[this->capacity];
		}
	}
	Vector(const Vector& obj) {
		this->size = obj.size;
		this->capacity = obj.capacity;
		this->array = new Type[this->capacity];

		for (int i = 0; i < this->size; ++i) {
			this->array[i] = obj.array[i];
		}
	}

	Vector operator = (const Vector& obj) 
	{
		if (&obj != this) {
			this->size = obj.size;
			this->capacity = obj.capacity;
			
			if (this->array != nullptr) delete[] this->array;
			this->array = new Type[this->capacity];

			for (int i = 0; i < this->size; ++i) {
				this->array[i] = obj.array[i];
			}
		}
		return *this;
	}


	// to insert new element
	void push_back(const Type& element) 
	{
		if (this->size < this->capacity) {
			this->array[size++] = element;
		}
	}

	// to delete an element from the end of array
	void pop_back() {
		if (this->size == 0) return;
		this->size--;
	}

	// to set capacity of array
	void setCapacity(int newCapacity)
	{
		if (newCapacity <= 0) return;
		this->capacity = newCapacity;
		this->array = new Type[newCapacity];
	}

	// to return element at ith index
	Type& operator [] (int ind) {
		if (ind >= 0 && ind < this->capacity) {
			return this->array[ind];
		}
	}

	// getters
	int Capacity() { return this->capacity; }
	int Size() { return this->size; }


	// destructor
	~Vector() {
		if (this->array != nullptr)
			delete[] this->array;
		this->size = 0;
		this->capacity = 0;
	}
};