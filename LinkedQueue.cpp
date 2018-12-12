//CSC 415 Programming Languages
//Chandler Phillips
//Nov 26, 2018
//
//Description:
//  This file implements the LinkedQueue class's methods.
//  The LinkedQueue class is an implementation of the Queue ADT using a
//  linked structure as the underlying data structure.

#include "LinkedQueue.h"
#include <exception>
#include <iostream>
using namespace std;

//default constructor
LinkedQueue::LinkedQueue()
{
    front = nullptr;
    rear = nullptr;
    count = 0;
}

//copy constructor
LinkedQueue::LinkedQueue(const LinkedQueue& original)
{
    front = nullptr;
    rear = nullptr;
    count = 0;

    Node* current = original.front;
    while(current!=nullptr)
    {
        push(current->getValue());
        current = current->getNext();
    }
}

//overloaded assignment operator (performs a deep copy)
LinkedQueue& LinkedQueue::operator=(const LinkedQueue& original)
{
    //if self-assignment, do nothing
    if(this==&original)
        return *this;

    //deallocate any existing memory
    this->~LinkedQueue();

    //reset properties, start from scratch
    front = nullptr;
    rear = nullptr;
    count = 0;

    //copy the elements
    Node* current = original.front;
    while(current!=nullptr)
    {
        push(current->getValue());
        current = current->getNext();
    }

    return *this;
}

//destructor
LinkedQueue::~LinkedQueue()
{
	Node* current = front; //setting current to front memory cell
	while(current) {
		Node* next = current->getNext();
		delete(current); //deallocating current
		current = next; //current now equal to next
	}
	front = nullptr;
}

//push - adds an element to the back of the queue
void LinkedQueue::push(char element)
{
    Node* newNode = new Node(element);

    if(count==0)
        front = newNode;
    else
        rear->setNext(newNode);

    rear = newNode;
    count++;
}

//pop - removes an element from the front of the queue
char LinkedQueue::pop()
{
    if(count==0)
        throw invalid_argument("Attempt to pop from an empty queue.");

    if(count==1)
        rear = nullptr;
	
	Node* temp = front; //setting temp to front memory cell
	delete(temp); //deallocating front memory cell
	
    char result = front->getValue();
    front = front->getNext();
    count--;
    return result;
}

//peek - returns the element at the front of the queue
char LinkedQueue::peek() const
{
    if(count==0)
        throw invalid_argument("Attempt to peek at an empty queue.");

    return front->getValue();
}

//size - returns the number of elements in the queue
unsigned int LinkedQueue::size() const
{
    return count;
}

//isEmpty - returns whether the queue is empty
bool LinkedQueue::isEmpty() const
{
    return count==0;
}

//overloaded equality operator (performs a deep comparison)
bool LinkedQueue::operator==(const LinkedQueue& q) const
{
    if(count!=q.count)
        return false;

    Node* current = front;
    Node* other = q.front;

    while(current!=nullptr)
    {
        if(current->getValue()!=other->getValue())
            return false;

        current = current->getNext();
        other = other->getNext();
    }

    return true;
}

//overloaded insertion operator
ostream& operator<<(ostream& out, const LinkedQueue& queue)
{
    out << "[ ";

    Node* current = queue.front;
    while(current!=nullptr)
    {
        out << current->getValue() << " ";
        current = current->getNext();
    }
    out << "]";
    return out;
}