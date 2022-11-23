/*
 * Node.cpp
 *
 *  Created on: 21/09/2021
 *      Author: salustianorodriguezferrere
 */

#include "Node.hpp"

Node::Node(Vehicle *v) {
	this->vehicle = v;
	this->next = 0;

}

//returns the vehicle pointer from the node

Vehicle * Node::getVehicle() const {
  return this->vehicle;
}

//sets the next node to the given node pointer

void Node::setNext(Node *n) {
  this->next = n;
}

//retrieves the next node pointer

Node * Node::getNext() const {
  return this->next;
}

Node::~Node() {
	// TODO Auto-generated destructor stub
}

