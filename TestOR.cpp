#include"OperationResearch.h"
#include<iostream>
#include<fstream>
#include <vector>
bool readFromFile(std::string filename, std::vector<Operation>&operations);
void printOperations(std::vector<Operation>&operations);
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	OR planningOR(3);
	planningOR.addOperationRoom(0, 8, 19, 1);
	planningOR.addOperationRoom(1, 8, 19, 1);
	planningOR.addOperationRoom(2, 8, 19, 1);
	
	std::vector<Operation> operations;

	bool added = readFromFile("Operationer_1a.txt",operations);

	if (added)
	{
		printOperations(operations);
	}

	std::cout << std::endl << std::endl;

	planningOR.planingAlgorithm(operations, operations.size());

	std::cout << std::endl << std::endl;
	printOperations(operations);
	std::cin.get();
	std::system("cls");

	OR planningOR1b(3);
	planningOR1b.addOperationRoom(0,8 ,19, 1);
	planningOR1b.addOperationRoom(1, 8, 19, 1);
	planningOR1b.addOperationRoom(2, 8, 19, 1);

	std::vector<Operation> operations1b;
	added = readFromFile("Operationer_1b.txt", operations1b);

	if (added)
	{
		printOperations(operations1b);
	}

	std::cout << std::endl << std::endl;

	planningOR1b.planingAlgorithm(operations1b, operations1b.size());

	std::cout << std::endl << std::endl;
	printOperations(operations1b);


	std::cin.get();
	std::system("cls");

	OR planningOR2(3);
	planningOR2.addOperationRoom(0, 8, 19, 2);
	planningOR2.addOperationRoom(1, 8, 22, 2);
	planningOR2.addOperationRoom(2, 8, 17, 2);

	std::vector<Operation> operations2;
	 added = readFromFile("Operationer_2.txt", operations2);

	if (added)
	{
		printOperations(operations2);
	}

	std::cout << std::endl << std::endl;

	planningOR2.planingAlgorithm(operations2, operations2.size());

	printOperations(operations2);

	
	std::cin.get();
	return 0;
}


bool readFromFile(std::string filename, std::vector<Operation>&operations)
{
	bool done = false;
	std::string line;
	std::ifstream fileIn(filename);
	if (fileIn.is_open())
	{
		while (std::getline(fileIn,line))
		{
			int pos = line.find(",");
			if (pos >= 0)
			{
				int id = std::stoi(line.substr(0, pos));
				std::string restOfLine = line.substr(pos + 1);
				pos = restOfLine.find(",");
				std::string subspecialty = restOfLine.substr(0, pos);
				int estimatedTime = std::stoi(restOfLine.substr(pos + 1));
				Operation toAdd(id, subspecialty, estimatedTime);
				operations.push_back(toAdd);
			}
		}
		done = true;
	}
	return done;
}


void printOperations(std::vector<Operation>&operations)
{
	for (int i = 0; i < operations.size(); i++)
	{
		std::cout << operations[i].toString();
	}
}
