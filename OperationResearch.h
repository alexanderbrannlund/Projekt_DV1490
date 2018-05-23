#pragma once
#include"List.h"
#include "OperationRoom.h"
#include <vector>


class OR
{
public:
	OR(int nrOfOperationRooms);
	~OR();
	
	void addOperationRoom(int roomId, int dayStart,int dayEnd, int nrOfDays);
	void planingAlgorithm(std::vector<Operation>&operations,int nrOfOperations);
	void sortOperations(std::vector<Operation>&operations, int start, int end);



private:
	int nrOfOperationRooms;
	
	OperationRoom** operationRooms;
	int dividing(std::vector<Operation>&operations, int start, int end);
	double printSolution(int solutionNr)const;
	bool replace(std::vector<Operation>&operations)const;
	int calculateTime(int start, int end)const;
};


