#pragma once
//#include <string>
#include <fstream>
class Address // Made class in case they want to alter data. Methods should be here.
{
private:
	std::string firstName;
	std::string lastName;
	std::string numStreet;
	std::string streetName;
	std::string cityName;
	std::string stateName;
	std::string zipCode;
	std::string numPhone;

public:
	Address();
	Address(std::string firstName, std::string lastName, std::string numStreet, std::string streetName, std::string cityName, std::string stateName,std::string zipCodeTemp, std::string numPhone);
	std::string GetPhoneNum();
	std::string GetLastName();


	void Print();
	void SaveToFile(std::ofstream &);
	~Address();
};