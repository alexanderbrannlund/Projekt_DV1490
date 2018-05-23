#pragma once
#include"List.h"
#include "Operation.h"
#include <vector>

class OperationRoom
{
public:
	OperationRoom(int totalTimePerDay=0,int nrOfDays=1);
	virtual~OperationRoom();

	bool addOperationToRoom(int id, const std::string & subspecialty, int estimatedTime,int day=0);
	double totalpercentageBooked() const;
	double percentageBookedPerDay(int day=0) const;
	int getBookedTimePerDay(int day=0)const;
	int getTotalBookedTime()const;
	int getTotalTimeAvailable()const;
	int getNrOfDays()const;
	std::string toString() const;
	bool replaceOperations(std::vector<Operation>&operationsVec, int timeLeft, int day);
	bool replaceOperation(std::vector<Operation>&operationsVec,int pos, int day);

private:
	int totalTime;
	int totalTimePerDay;
	int bookedTime;
	int* bookedTimePerDay;
	int nrOfDays;
	List<Operation>* operations;
	void bookedTimeinitiate();


};


