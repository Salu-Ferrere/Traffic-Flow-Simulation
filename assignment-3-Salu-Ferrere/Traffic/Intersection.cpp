#include "Intersection.hpp"
#include "Vehicle.hpp"
#include "Node.hpp"
#include <iostream>
using namespace std;



Intersection::Intersection() {
	this->LaneDirections[0] = UNSET;
	this->LaneDirections[1] = UNSET;
	this->LaneDirections[2] = UNSET;
	this->LaneDirections[3] = UNSET;
	this->Lanes[0] = 0;
	this->Lanes[1] = 0;
	this->Lanes[2] = 0;
	this->Lanes[3] = 0;

}

//if any lane has not been set, it will have a value of 0, if any lane has a value of 0 the intersection is not valid and method will return false

bool Intersection::valid() {
	if(Lanes[0] == 0 || Lanes[1] == 0 || Lanes[2] == 0|| Lanes[3] == 0){
		return false;
	}
	return true;
}

//assigns a lane pointer and direction to the north lane

Lane* Intersection::connectNorth(Lane* lane, LaneDirection direction) {
	Lane* old = Lanes[0];
	Lanes[0] = lane;

	LaneDirections[0] = direction;

	return old;
}

//assigns a lane pointer and direction to the East lane

Lane* Intersection::connectEast(Lane* lane, LaneDirection direction) {
	Lane* old = Lanes[1];
	Lanes[1] = lane;

	LaneDirections[1] = direction;

	return old;
}

//assigns a lane pointer and direction to the south lane

Lane* Intersection::connectSouth(Lane* lane, LaneDirection direction) {
	Lane* old = Lanes[2];
	Lanes[2] = lane;

	LaneDirections[2] = direction;

	return old;
}

//assigns a lane pointer and direction to the west lane

Lane* Intersection::connectWest(Lane* lane, LaneDirection direction) {
	Lane* old = Lanes[3];
	Lanes[3] = lane;
	LaneDirections[3] = direction;

	return old;
}

//returns corresponding straight ahead lane

int Intersection::GetStraight(Lane* lane){
	for(unsigned int i = 0; i < 4; i++){
		if(Lanes[i] == lane){
			if(i <= 1){
				return i+2;
			}
			return i-2;
		}
	}
	return 0;
}

//returns corresponding left lane

int Intersection::GetLeft(Lane* lane){
	for(unsigned int i = 0; i < 4; i++){
		if(Lanes[i] == lane){
			if(i == 3){
				return 0;
			}
			return i+1;
		}
	}
	return 0;
}

//returns corresponding right lane

int Intersection::GetRight(Lane* lane){
	for(unsigned int i = 0; i < 4; i++){
		if(Lanes[i] == lane){
			if(i == 0){
				return 3;
			}
			return i-1;
		}
	}
	return 0;
}

//simulates the intersection following the given road rules, then dequeues valid turning vehicles, makes the turn on the vehicle,
//and re-queues them in their respective lane. Assuming vehicle have only been given valid turns

void Intersection::simulate() {

	int outgoing = 0;
	int incoming = 0;
    int count = 0;

    //allow all vehicles traveling straight to do so then finish simulation

	for(unsigned int i = 0; i < 4; i++){

		if(LaneDirections[i] == LD_INCOMING && Lanes[i]->front() != NULL && Lanes[i]->front()->nextTurn() == Vehicle::TD_STRAIGHT ){
			Vehicle* vehicle = Lanes[i]->dequeue();
			vehicle->makeTurn();
			Lanes[GetStraight(Lanes[i])]->enqueue(vehicle);
			count++;
		}
	}
	if(count > 0){
		return;
	}

	//if no vehicles have turned straight allow all left turning vehicles to do so

	count = 0;
	for(unsigned int i = 0; i < 4; i++){
		if(LaneDirections[i] == LD_INCOMING && Lanes[i]->front() != NULL && Lanes[i]->front()->nextTurn() == Vehicle::TD_LEFT){
			Vehicle* vehicle = Lanes[i]->dequeue();
			vehicle->makeTurn();
			Lanes[GetLeft(Lanes[i])]->enqueue(vehicle);
			count++;
			outgoing = GetLeft(Lanes[i]);
			incoming = i;
		}
	}
	if(count > 0){
		return;

	//if no vehicles have gone straight or turned left, allow all right turning vehicles to do so

	}
	for(int i = 0; i < 4; i++){
		if(LaneDirections[i] == LD_INCOMING && Lanes[i]->front() != NULL && Lanes[i]->front()->nextTurn() == Vehicle::TD_RIGHT){
			if(count == 0){
				Vehicle* vehicle = Lanes[i]->dequeue();
				vehicle->makeTurn();
				Lanes[GetRight(Lanes[i])]->enqueue(vehicle);
			} else if(outgoing != GetRight(Lanes[i]) && incoming != i){
				Vehicle* vehicle = Lanes[i]->dequeue();
				vehicle->makeTurn();
				Lanes[GetRight(Lanes[i])]->enqueue(vehicle);
				return;
			}
		}
	}
	return;
}
