# include <iostream>
# include <string>
# include "LinkedList.h"
# include "Node.h"

using std::string, std::ostream;

LinkedList::LinkedList():
head(nullptr),
tail(nullptr) {}

LinkedList::~LinkedList() {
	Node* currNode = head;
	head = nullptr;
	tail = nullptr;

	while (currNode != nullptr) {
		Node* nextNode = currNode->next;

		delete currNode;

		currNode = nextNode;
	}
}

LinkedList::LinkedList(const LinkedList& source) /* TODO */ {
	Node* copyNode = source.head;

	while (copyNode != nullptr) {
		TemperatureData data = copyNode->data;

		this->insert(data.id, data.year, data.month, data.temperature);

		copyNode = copyNode->next;
	}

}

LinkedList& LinkedList::operator=(const LinkedList& source) {
	this->clear();

	Node* copyNode = source.head;

	while (copyNode != nullptr) {
		TemperatureData data = copyNode->data;

		this->insert(data.id, data.year, data.month, data.temperature);

		copyNode = copyNode->next;
	}

	return *this;
}

void LinkedList::insert(string location, int year, int month, double temperature) {
	Node* addNode = new Node(location, year, month, temperature);

	if (head == nullptr) { // Case empty list (gets inserted as new head/tail)
		head = addNode;
		tail = addNode;
	}
	else if (addNode < head) { // Case new node is less than head node (gets inserted as new head)
		addNode->next = head;
		head = addNode;
	}
	else if (tail < addNode) { // Case new node is greater than tail node (gets inserted as new tail)
		tail->next = addNode;
		tail = addNode;
	}
	else {					   // Case new node is somewhere in middle (have to find location to insert)
		Node* checkNode = head;
		Node* nextNode = checkNode->next;
		
		while(checkNode != nullptr) {
			if(checkNode < addNode && addNode < nextNode){
				checkNode->next = addNode;
				addNode->next = nextNode;

				break;
			}

			checkNode = nextNode;
			nextNode = checkNode->next;
		}
	}
}

void LinkedList::clear() {
	Node* currNode = head;
	head = nullptr;
	tail = nullptr;

	while (currNode != nullptr) {
		Node* nextNode = currNode->next;

		delete currNode;

		currNode = nextNode;
	}
}

Node* LinkedList::getHead() const {
	return head;
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
