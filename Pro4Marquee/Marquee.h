#pragma once
using namespace std;

/*
 * CHANGELOG:
 * 2023.03.02 Alexi Brooks - Created
*/

#include <string>

//Class for holding a single bulletin
//Copied directly from in-class implementation
template <typename T>
class ListNode {
	//fields
private:
	T data;
	ListNode<T>* next;
	//methods
public:
	//constructor
	ListNode(T data) {
		this->data = data;
		next = nullptr;
	}
	ListNode(T data, ListNode<T>* next) {
		this->data = data;
		this->next = next;
	}
	//getters, setters
	T getData() { return data; }
	ListNode<T>* getNext() { return next; }
	void setData(T d) { data = d; }
	void setNext(ListNode<T>* n) { next = n; }
};

//Class for holding a linked list of string bulletins
class Marquee {
//FIELDS
private:
	ListNode<string>* upcoming{nullptr}; //Only maintain the "upcoming" (pre-current) pointer
	int size{ 0 };

	//Helper function to help the copy constructor and copy assignment
	void copyHelper(int size, ListNode<string>* otherc) {
		if (size > 0) {
			upcoming = new ListNode<string>{ otherc->getData() };
			ListNode<string>* current = upcoming;
			size--;
			while (size > 0) {
				otherc = otherc->getNext();
				current->setNext(new ListNode<string>{ otherc->getData() });
				current = current->getNext();
				size--;
			}
			current->setNext(upcoming);
		}
	}

public:
	//Constructor
	Marquee() {}

	//Copy Constructor
	Marquee(const Marquee& other) {
		copyHelper(other.size, other.upcoming);
	}

	//Destructor
	~Marquee() {
		ListNode<string>* prev = upcoming->getNext();
		ListNode<string>* n = upcoming->getNext();
		while (n != upcoming) {
			n = prev->getNext();
			delete prev;
			prev = n;
		}
		delete upcoming;
	}

	//Copy Assignment Operator
	Marquee& operator=(const Marquee& other) {
		copyHelper(other.size, other.upcoming);
		return *this;
	}

	//Return the next string and advance
	string rotate() {
		string toReturn = upcoming->getData();
		upcoming = upcoming->getNext();
		return toReturn;
	}

	//add as next to plays
	void playNext(string s) {
		ListNode<string>* newNode = new ListNode{s};
		if (size == 0) {
			upcoming = newNode;
			upcoming->setNext(upcoming);
		}
		else {
			ListNode<string>* current = upcoming;
			for (int i = 0; i < size - 1; i++) {
				current = current->getNext();
			}
			current->setNext(newNode);
			newNode->setNext(upcoming);
			upcoming = newNode;
		}
		size++;
	}

	//remove the next and return it
	string decomission() {
		string toReturn = upcoming->getData();
		ListNode<string>* toDelete = upcoming;
		if (size == 0) {
			delete toDelete;
			return toReturn;
		}
		ListNode<string>* current = upcoming;
		for (int i = 0; i < size - 1; i++) {
			current = current->getNext();
		}
		upcoming = upcoming->getNext();
		current->setNext(upcoming);
	 	delete toDelete;
		size--;
		return toReturn;
	}

	int getSize() { 
		return size;
	}
};