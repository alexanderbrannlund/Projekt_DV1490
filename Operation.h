#pragma once
#include <string>
class Operation
{
public:
	Operation(int id=-1, const std::string & subspecialty="default", int estimatedTime=0);
	virtual ~Operation();

	int getId()const;
	int getEstimatedTime()const;
	std::string getSubspecialty()const;
	void setId(int id);
	void setEstimatedTime(int estimatedTime);
	void setSubspecialty(const std::string & subspecialty);

	bool operator==(const Operation& other) const;
	bool operator>(const Operation& other) const;
	std::string toString()const; 
	

private:
	int id;
	std::string subspecialty;
	int estimatedTime;
	
};

