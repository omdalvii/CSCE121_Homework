# include <iostream>
# include <string>
# include "LinkedList.h"
# include "Node.h"

using std::string, std::ostream;

LinkedList::LinkedList() /* TODO */ {
	// TODO: implement this function
}

LinkedList::~LinkedList() {
	// TODO: implement this function
}

LinkedList::LinkedList(const LinkedList& source) /* TODO */ {
	// TODO: implement this function
}

LinkedList& LinkedList::operator=(const LinkedList& source) {
	// TODO: implement this function
}

void LinkedList::insert(string location, int year, int month, double temperature) {
	// TODO: implement this function
}

void LinkedList::clear() {
	// TODO: implement this function
}

Node* LinkedList::getHead() const {
	// TODO: implement this function, it will be used to help grade other functions
}

string LinkedList::print() const {
	string outputString;

	// TODO: implement this function

	return outputString;
}

ostream& operator<<(ostream& os, const LinkedList& ll) {
	os << ll.print();
	return os;
}
