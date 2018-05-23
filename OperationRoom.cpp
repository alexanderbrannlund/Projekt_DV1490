#include "OperationRoom.h"
#include <sstream>

OperationRoom::OperationRoom(int totalTimePerDay, int nrOfDays)
{
	this->totalTimePerDay = totalTimePerDay;
	this->nrOfDays = nrOfDays;
	totalTime = totalTimePerDay * nrOfDays;
	this->operations = new List<Operation>[nrOfDays];
	this->bookedTimePerDay = new int[nrOfDays];
	bookedTimeinitiate();
}

OperationRoom::~OperationRoom()
{
	
	delete[] this->operations;
	delete[] this->bookedTimePerDay;

}

bool OperationRoom::addOperationToRoom(int id, const std::string & subspecialty, int estimatedTime, int day)
{
	bool added = false;
	if (bookedTimePerDay[day] + estimatedTime <= totalTimePerDay)
	{
		Operation toAdd(id, subspecialty, estimatedTime);
		operations[day].insertAt(0, toAdd);
		bookedTime += estimatedTime;
		bookedTimePerDay[day] += estimatedTime;
		added++;
	}
	return added;
}

double OperationRoom::totalpercentageBooked() const
{
	return ((double)bookedTime/totalTime)*100.0;
}

double OperationRoom::percentageBookedPerDay(int day) const
{
	return ((double)bookedTimePerDay[day]/totalTimePerDay)*100.0;
}

int OperationRoom::getBookedTimePerDay(int day) const
{
	return bookedTimePerDay[day];
}

int OperationRoom::getTotalBookedTime() const
{
	return this->bookedTime;
}

int OperationRoom::getTotalTimeAvailable() const
{
	return this->totalTime;
}

int OperationRoom::getNrOfDays() const
{
	return this->nrOfDays;
}

std::string OperationRoom::toString() const
{
	std::stringstream ss;
	if (nrOfDays>1)
	{
		for (int i = 0; i < nrOfDays; i++)
		{
			ss << "\nDay " << (i + 1) << ": ";
			for (int u = 0; u < operations[i].length(); u++)
			{
				ss << operations[i].getAt(u).getId()<<", ";
			}
			ss << this->percentageBookedPerDay(i) << "%";
			ss << std::endl;
		}
	}
	else
	{
		for (int u = 0; u < operations[0].length(); u++)
		{
			ss << operations[0].getAt(u).getId() << ", ";
		}
		ss << "Procentage booked time: " << this->totalpercentageBooked() << "%";
		ss << std::endl;
	}
	
	

	return ss.str();
}

bool OperationRoom::replaceOperations(std::vector<Operation>& operationsVec, int timeLeft, int day)
{
	bool replaced=false;
	for (int i = operations[day].length()-1 ; i >=0; i--)
	{
		int timeAtPos = operations[day].getAt(i).getEstimatedTime();
		if (timeLeft>timeAtPos && (timeLeft+(bookedTimePerDay[day]- timeAtPos))<=totalTimePerDay)
		{
			this->bookedTimePerDay[day] -= timeAtPos;
			this->bookedTime -= timeAtPos;
			Operation toRemove = operations[day].getAt(i);
			operations[day].removeAt(i);
			for (int u = 0; u <operationsVec.size(); u++)
			{
				replaced=addOperationToRoom(operationsVec[u].getId(), operationsVec[u].getSubspecialty(), operationsVec[u].getEstimatedTime(), day);
			}
			i = -1;
			operationsVec.push_back(toRemove);
		}
	}
	return replaced;
}

bool OperationRoom::replaceOperation(std::vector<Operation>&operationsVec, int pos, int day)
{
	bool replaced = false;
	for (int i = operations[day].length() - 1; i >= 0; i--)
	{
		int timeAtPos = operations[day].getAt(i).getEstimatedTime();
		if (operationsVec[pos].getEstimatedTime()>timeAtPos && (operationsVec[pos].getEstimatedTime() + (bookedTimePerDay[day] - timeAtPos)) <= totalTimePerDay)
		{
			this->bookedTimePerDay[day] -= timeAtPos;
			this->bookedTime -= timeAtPos;
			Operation toRemove = operations->getAt(i);
			operations[day].removeAt(i);
			replaced = addOperationToRoom(operationsVec[pos].getId(), operationsVec[pos].getSubspecialty(), operationsVec[pos].getEstimatedTime(), day);
			
			i = -1;
			operationsVec.erase(operationsVec.begin() + pos);
			operationsVec.push_back(toRemove);
		}
	}
	return replaced;
}

void OperationRoom::bookedTimeinitiate()
{
	for (int i = 0; i < nrOfDays; i++)
	{
		bookedTimePerDay[i] = 0;
	}
}


