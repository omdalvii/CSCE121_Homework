# include <string>
# include "Node.h"

using std::string;

Node::Node() {
	TemperatureData data;

	this->data = data;
	this->next = next;
}

Node::Node(string id, int year, int month, double temperature) {
	TemperatureData data(id, year, month, temperature);

	this->data = data;
	this->next = nullptr;
}

bool Node::operator<(const Node& b) {	
	return this->data < b.data;
}
