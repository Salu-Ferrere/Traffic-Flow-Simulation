#include "ExpressLane.hpp"


//has the same functionality as simple lane enqueue except motorbikes will be queued in front of all other non motorbike vehicles
void ExpressLane::enqueue(Vehicle* vehicle){

	Node *n;
	Node *m;

	//if no vehicles in queue, queue vehicle to front of lane

	if (this->frontVehicle == 0) {
		this->frontVehicle = new Node(vehicle);
		this->backVehicle = this->frontVehicle;
		this->vehicleCount++;
		return;
	}

	//if there are no motorbikes in the queue and the vehicle being queued is a motorbike, place at front of lane

	if(vehicle->type() == Vehicle::VT_MOTORCYCLE){
		if(frontVehicle->getVehicle()->type() != Vehicle::VT_MOTORCYCLE){
			n = new Node(vehicle);

			n->setNext(this->frontVehicle);
			this->frontVehicle = n;
			this->vehicleCount++;

			return;
		}
		m = this->frontVehicle;

		//if there are motorbikes in the queue and the vehicle being queued is a motorbike, loop through the lane queue
		//and queue mototrbike behind last motorbike in the queue

		for(int i = 0; i < vehicleCount; i++){
			if(m->getNext() != NULL && m->getNext()->getVehicle()->type() != Vehicle::VT_MOTORCYCLE){
				n = new Node(vehicle);
				n->setNext(m->getNext());
				m->setNext(n);

				this->vehicleCount++;

				return;

			}
			m = m->getNext();
		}

	}

	//if vehicle type is not a motorbike, add vehicle to back of queue

	n = new Node(vehicle);
	this->backVehicle->setNext(n);
	this->backVehicle = n;

	this->vehicleCount++;

	return;

}



