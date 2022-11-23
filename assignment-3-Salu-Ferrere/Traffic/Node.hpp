/*
 * Node.hpp
 *
 *  Created on: 21/09/2021
 *      Author: salustianorodriguezferrere
 */

#ifndef NODE_HPP_
#define NODE_HPP_
#include "Vehicle.hpp"

class Node {
private:
	Vehicle * vehicle;
	Node * next;
public:
	void setNext(Node *n);
    Node* getNext() const;
    Vehicle* getVehicle() const;
    Node(Vehicle *v);
    virtual ~Node();

};

#endif /* NODE_HPP_ */
