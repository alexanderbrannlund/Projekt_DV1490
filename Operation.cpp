#include "Operation.h"
#include <sstream>

Operation::Operation(int id, const std::string & subspecialty, int estimatedTime)
{
	this->id = id;
	this->estimatedTime = estimatedTime;
	this->subspecialty = subspecialty;
}

Operation::~Operation()
{
}

int Operation::getId() const
{
	return this->id;
}

int Operation::getEstimatedTime() const
{
	return this->estimatedTime;
}

std::string Operation::getSubspecialty() const
{
	return this->subspecialty;
}

void Operation::setId(int id)
{
	this->id = id;
}

void Operation::setEstimatedTime(int estimatedTime)
{
	this->estimatedTime = estimatedTime;
}

void Operation::setSubspecialty(const std::string & subspecialty)
{
	this->subspecialty = subspecialty;
}

bool Operation::operator==(const Operation & other) const
{
	return this->id==other.id;
}

bool Operation::operator>(const Operation & other) const
{
	return this->estimatedTime>other.estimatedTime;
}

std::string Operation::toString() const
{
	std::stringstream ss;
	ss << "Id : " << id << "\tSubspecialty: " << subspecialty << "\tEstimatedTime " << estimatedTime << "\n";
	
	return ss.str();
}
