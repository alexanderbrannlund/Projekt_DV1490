#include "OperationResearch.h"
#include<iostream>

OR::OR(int nrOfOperationRooms)
{
	this->nrOfOperationRooms = nrOfOperationRooms;
	this->operationRooms = new OperationRoom* [nrOfOperationRooms];

}

OR::~OR()
{
	for (int i = 0; i < nrOfOperationRooms; i++)
	{
		delete operationRooms[i];
	}
	delete[] operationRooms;
}

void OR::addOperationRoom(int roomId, int dayStart, int dayEnd, int nrOfDays)
{
	int totalTimePerDay = calculateTime(dayStart, dayEnd);
	operationRooms[roomId]= new OperationRoom(totalTimePerDay, nrOfDays);
}

void OR::planingAlgorithm(std::vector<Operation>&operations, int nrOfOperations)
{
	sortOperations(operations, 0, operations.size() - 1);

	bool canAdd=true;
	
	while (canAdd && operations.size()!=0)
	{
		for (int i = 0; i < nrOfOperationRooms; i++)
		{
			for (int k = 0; k < operationRooms[i]->getNrOfDays(); k++)
			{


				canAdd = operationRooms[i]->addOperationToRoom(operations[0].getId(), operations[0].getSubspecialty(), operations[0].getEstimatedTime(),k);
				if (canAdd)
				{
					operations.erase(operations.begin());
				}
				else
				{
					for (int u = 1; u < operations.size(); u++)
					{
						canAdd = operationRooms[i]->addOperationToRoom(operations[u].getId(), operations[u].getSubspecialty(), operations[u].getEstimatedTime(),k);
						if (canAdd)
						{
							operations.erase(operations.begin() + u);
							u = operations.size();
						}
					}
				}
			}
		}
		
	}
	double solutionProcentage= printSolution(1);
	if (solutionProcentage!=100)
	{
		
		if (replace(operations))
		{
			solutionProcentage = printSolution(2);
		}
		else
		{
			std::cout << "Could not replace operations.... " << std::endl << std::endl;
		}
	}
	
	if (solutionProcentage != 100)
	{

		if (replace(operations))
		{
			solutionProcentage = printSolution(3);
		}
		else
		{
			std::cout << "Could not replace operations.... " << std::endl << std::endl;
		}
	}

	else
	{
		std::cout << "Can't improve planing..." << std::endl << std::endl;
	}

}

void OR::sortOperations(std::vector<Operation>&operations, int start, int end)
{
	if (start<end)
	{
		int pivot = dividing(operations, start, end);
		sortOperations(operations, start, pivot - 1);
		sortOperations(operations, pivot + 1, end);
	}
}

int OR::dividing(std::vector<Operation>&operations, int start, int end)
{
	int pivot = start;
	Operation value = operations[pivot];
	for (int i = start+1; i <= end; i++)
	{
		if (operations[i] > value)
		{
			std::swap(operations[i], operations[pivot + 1]);
			std::swap(operations[pivot], operations[pivot + 1]);
			pivot++;
		}
	}
	return pivot;
}

double OR::printSolution(int solutionNr) const
{
	double totalprocentage=0;
	int bookedTime = 0;
	int totalTime = 0;
	std::cout << "Lösning nr" << std::to_string(solutionNr) << std::endl;
	for (int i = 0; i < nrOfOperationRooms; i++)
	{
		std::cout << "OperationsSal " << (i + 1) << ": ";
		std::cout << operationRooms[i]->toString()<<std::endl;
		bookedTime += operationRooms[i]->getTotalBookedTime();
		totalTime += operationRooms[i]->getTotalTimeAvailable();
		
	}
	totalprocentage = (double)bookedTime / totalTime * 100;
	std::cout << "Procentage booked time: " << std::to_string(totalprocentage) << "%" << std::endl << std::endl;
	
	return totalprocentage;
}

bool OR::replace(std::vector<Operation>& operations) const
{
	bool replace = false;
	std::vector<Operation> vec = operations;
	int timeLeft = 0;
	int timeLeft2 = 0;
	for (int i = 0; i < operations.size(); i++)
	{
		timeLeft += operations[i].getEstimatedTime();
	}
	timeLeft2 = timeLeft;

	for (int i = 0; i < nrOfOperationRooms; i++)
	{
		for (int k = 0; k < operationRooms[i]->getNrOfDays(); k++)
		{
			if (operationRooms[i]->percentageBookedPerDay(k) != 100)
			{
				replace = operationRooms[i]->replaceOperations(operations, timeLeft, k);
				if (!replace)
				{
					int counter = operations.size() - 1;
					std::vector<Operation> temp = operations;
					while (!replace && counter >= 0)
					{
						timeLeft -= temp[counter].getEstimatedTime();
						temp.erase(temp.begin() + counter);
						replace = operationRooms[i]->replaceOperations(temp, timeLeft, k);
						if (replace)
						{
							operations.erase(operations.begin(), operations.begin() + counter);
							operations.push_back(temp[temp.size() - 1]);
							timeLeft += operations[operations.size() - 1].getEstimatedTime();
						}
						else
						{
							counter--;
						}

					}
					if (!replace)
					{
						temp = operations;
						counter = 1;
						while (!replace && counter<temp.size())
						{
							timeLeft2 -= temp[counter-1].getEstimatedTime();
							temp.erase(temp.begin());
							replace = operationRooms[i]->replaceOperations(temp, timeLeft2, k);
							if (replace)
							{
								operations.erase(operations.begin()+counter, operations.end());
								operations.push_back(temp[temp.size() - 1]);
								timeLeft2 += operations[operations.size() - 1].getEstimatedTime();
							}
							else
							{
								counter++;
							}
						}
						if (!replace)
						{
							
							for (int j = 0; j < operations.size(); j++)
							{
								replace = operationRooms[i]->replaceOperation(operations, j, k);
								if (replace)
								{
									j = operations.size();
								}
							}
						}
						
					}
				}
				else
				{
					operations.erase(operations.begin(), operations.end() - 1);
				}
			}
		}
	}
	if (vec != operations)
	{
		replace = true;
	}
	return replace;
}

int OR::calculateTime(int start, int end) const
{
	int timePerDay = (end - start)*60;
	return timePerDay;
}
