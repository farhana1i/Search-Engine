#pragma once
template <typename Type>
class List
{
private:
	class Node {
	public:
		Type data;				// data of a node
		Node* next;				// points to the next node
		Node* prev;				// points to the previous node
	};

	Node* head;					// head node of list
	Node* tail;					// tail node of list
	int size;					// numbers of elements in a list

	// for default constructor
	void __init__() {
		head = new Node;
		tail = new Node;
		head->prev = nullptr;
		head->next = tail;
		tail->prev = head;
		tail->next = nullptr;
		size = 0;
	}

public:
	class Iterator {
	private:
		Node* curr;
	public:

		// constructors
		Iterator(Node* curr = nullptr) {
			this->curr = curr;
		}
		Iterator(const Iterator& itr) {
			curr = itr.curr;
		}

		// return true, if two nodes point to the same node 
		bool operator == (const Iterator& itr) {
			if (curr == itr.curr) return true;
			return false;
		}

		// return true, if two nodes point to the different nodes
		bool operator != (const Iterator& itr) {
			if (curr != itr.curr) return true;
			return false;
		}

		// points current to the next node
		Iterator& operator ++() {
			curr = curr->next;
			return *this;
		}

		// points current to the previous node
		Iterator& operator --() {
			curr = curr->prev;
			return *this;
		}

		// return data of a node
		Type& operator*() {
			return curr->data;
		}

		friend class List;
	};

	// constructor
	List() {
		__init__();
	}

	// copy constructor 
	List(const List<Type>& list)
	{
		Node* curr = list.head->next;
		Node* last = list.tail;

		__init__();			// default

		while (curr != last)				// copy all nodes
		{
			this->insertAtTail(curr->data);
			curr = curr->next;
		}
	}

	// copy list using assignment operator
	List<Type>& operator = (const List<Type>& list)
	{
		if (this == &list) return *this;

		this->~List();		// delete data, if any
		this->size = 0;

		Node* curr = list.head->next;
		Node* last = list.tail;

		__init__();			// default 

		while (curr != last)				// copy all nodes
		{
			this->insertAtTail(curr->data);
			curr = curr->next;
		}
		return *this;
	}

	// insert an element in list
	Iterator insert(Iterator& itr, Type data)
	{
		Node* newNode = new Node;
		newNode->data = data;
		newNode->prev = itr.curr->prev;
		newNode->next = itr.curr;

		itr.curr->prev->next = newNode;
		itr.curr->prev = newNode;

		++size;			// increase number of elements by 1

		Iterator ret(newNode);
		return ret;
	}

	// insert a new element at the start of the list
	void insertAtHead(Type data) {
		Iterator itr(head->next);
		insert(itr, data);
	}

	// insert a new element at the end of the list
	void insertAtTail(Type data) {
		Iterator itr(tail);
		insert(itr, data);
	}

	// remove an element from a list
	void remove(Iterator& itr)
	{
		itr.curr->prev->next = itr.curr->next;
		itr.curr->next->prev = itr.curr->prev;

		--size;			// decrease number of elements by 1
		if (itr.curr != nullptr)
			delete itr.curr;
	}

	// remove an element at the start of list
	void removeAtStart() {
		if (head->next != tail) {
			Iterator itr(head->next);
			remove(itr);
		}
	}

	// remove an element from the end of list
	void removeAtEnd() {
		if (head->next != tail) {
			Iterator itr(tail->prev);
			remove(itr);
		}
	}

	// begin of list
	Iterator begin() {
		Iterator itr(head->next);
		return itr;
	}

	// end of list
	Iterator end() {
		Iterator itr(tail);
		return itr;
	}

	// return number of elements in a list
	int SIZE() { return this->size; }

	// swap two nodes
	void swapNodes(Node*& node1, Node*& node2)
	{
		Node* prev = node1->prev;
		Node* next = node1->next;

		if (node1 == node2) return;

		// if two nodes are adjacent
		if (node1->next == node2)
		{
			node1->prev = node2;
			node1->next = node2->next;

			node2->prev = prev;
			node2->next = node1;

			prev->next = node2;
			node1->next->prev = node1;
		}

		else {
			node1->prev = node2->prev;
			node1->next = node2->next;

			node2->prev = prev;
			node2->next = next;

			node2->prev->next = node2;
			node2->next->prev = node2;

			node1->prev->next = node1;
			node1->next->prev = node1;
		}
	}

	// swap two nodes using 
	void swapNodes(Iterator& itr1, Iterator& itr2) {
		swapNodes(itr1.curr, itr2.curr);
	}

	// destructor
	~List()
	{
		while (head->next != tail) {
			removeAtEnd();
		}
		if (head != nullptr) delete head;
		if (tail != nullptr) delete tail;
	}
};
