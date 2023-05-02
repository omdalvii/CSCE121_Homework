# include <string>
# include "Node.h"

using std::string;

Node::Node() /* TODO */ {
	// TODO: implement this function
}

Node::Node(string id, int year, int month, double temperature) /* TODO */ {
	// TODO: implement this function
}

bool Node::operator<(const Node& b) {	
	return this->data < b.data;
}
