#include "SimpleLane.hpp"


SimpleLane::SimpleLane() {
	this->vehicleCount = 0;
	this->backVehicle = 0;
	this->frontVehicle = 0;
}

//deletes queued vehicles in lane when destructor is called

SimpleLane::~SimpleLane() {

	while (this->vehicleCount > 0) {
		Vehicle* v = this->dequeue();
		delete v;
		vehicleCount--;
	}
}

//queues vehicle pointer to back of lane

void SimpleLane::enqueue(Vehicle* vehicle) {

	Node *n;

	if (this->frontVehicle == 0) {
		this->frontVehicle = new Node(vehicle);
		this->backVehicle = this->frontVehicle;
	}else{
	n = new Node(vehicle);
	this->backVehicle->setNext(n);
	this->backVehicle = n;
	}
	this->vehicleCount++;

	return;


}

//dequeues vehicle pointer from front of lane returning a pointer to the dequeued vehicle

Vehicle* SimpleLane::dequeue() {

	Node *n = this->frontVehicle;

	if(this->vehicleCount == 0)  return 0;

	if(this->vehicleCount == 1){
		this->frontVehicle = 0;
		this->backVehicle = 0;
		this->vehicleCount--;
		return n->getVehicle();
		}
	this->frontVehicle = n->getNext();
	this->vehicleCount--;

	return n->getVehicle();

}

//checks to see if the lane is empty, returning true if so

bool SimpleLane::empty() const {
	if(vehicleCount == 0){
		return true;
	}
	return false;
}

//returns the number of vehicles in the lane

unsigned int SimpleLane::count() const {
	return vehicleCount;
}

//returns a pointer to the front vehicle in the lane

const Vehicle* SimpleLane::front() const {
	if(vehicleCount > 0){
		return frontVehicle->getVehicle();
	}
	return 0;
}

//returns a pointer to the back vehicle in the lane

const Vehicle* SimpleLane::back() const {
	if(vehicleCount > 0){
		return backVehicle->getVehicle();
	}
	return 0;
};
