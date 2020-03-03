#include "AddressBook.h"
#include <fstream>
#include <iostream>
#include <new>
#include <cctype>
#include <iomanip>

const int SPACE = 15;
AddressBook::AddressBook()
{
}
AddressBook::~AddressBook()
{
}
std::string strLower(std::string tempStr)
{
	if (!tempStr.size())
	{
		return tempStr;
	}
	tempStr.at(0) = toupper(tempStr.at(0));// What if they send empty string
	for (int x = 1; x < tempStr.size(); x++)
	{
		tempStr.at(x) = tolower(tempStr.at(x));
	}
	return tempStr;
}
void InputMenu(AddressBook& recList, int choice)
{
	std::string name="";
	while (name!="Quit")
	{
		
		std::cout << "Enter a name or number youd like to search for.Enter Quit to return to main menu." << std::endl;
		std::cin >> name;
		name = strLower(name);
		clearCin();
		if (choice == 2)
		{
			recList.Search(name);
		}
		else if(choice == 4)
		{
			recList.DeleteRec(name);
		}
	}
	std::cout << "Returning to main menu" << std::endl;
}
void GetEntryInput(AddressBook& recList)
{
	std::string fName,lName,buildNum,streetName,cityName,phoneNum;
	int day, month, year;
	
	std::cout << "Enter in data format below: \n" << std::setw(SPACE) << std::left << "FirstName" << std::setw(SPACE) << "LastName" << std::left << std::setw(SPACE)
		<< "BuildingNum" << std::setw(SPACE) << std::left << "StreetName" << std::setw(SPACE) << std::left << "CityName"
		<< std::setw(SPACE) << std::left << "PhoneNumber" << " DD " << "MM " << " YY" << std::endl;
	std::cin >> fName >> lName >> buildNum >> streetName >> cityName >> phoneNum >> day >> month >> year;
	//Record temp = new (std::nothrow) Record(fName,lName,buildNum,streetName,cityName,phoneNum,day,month,year);
	Record temp(fName, lName, buildNum, streetName, cityName, phoneNum, day, month, year);
	RecordList* temp2= new (std::nothrow) RecordList;
	temp2->data = temp;
	temp2->ptr = nullptr;
	if (!temp2)
	{
		std::cout << "Could not allocate memory. Returning to main menu." << std::endl;
		return;
	}
	recList.AddEntry(temp2, 1);
}
void clearCin()
{
	std::cin.clear();
	std::cin.ignore(1000, '\n');
}
void AddressBook::Load()
{
	std::ifstream inFile;
	RecordList* buffer= new (std::nothrow) RecordList;
	RecordList* trav = buffer;
	if (!buffer)
	{
		std::cout << "Error with allocating dynamic memory, contact system admin." << std::endl;
	}
	inFile.open("input.txt");
	if (!inFile)
	{
		std::cout << "Error opening or finding file." << std::endl;
	}
	//John Doe 6202 Winnetka CanogaPark 8185555555 01 01 1991
	inFile >> buffer->data.firstName >> buffer->data.lastName >> buffer->data.numStreet
		>> buffer->data.streetName >> buffer->data.cityName>> buffer->data.numPhone >> buffer->data.day >> buffer->data.month >> buffer->data.year;
	size++;
	head =trav= buffer;
	while (!inFile.eof())
	{
		buffer = new (std::nothrow) RecordList;
		if (!buffer)
		{
			std::cout << "Error with allocating dynamic memory, contact system admin." << std::endl;
		}
		trav->ptr = buffer;
		trav = buffer;
		size++;
		inFile >> buffer->data.firstName >> buffer->data.lastName >> buffer->data.numStreet >> buffer->data.streetName >> buffer->data.cityName// Maybe prime 
			>> buffer->data.numPhone >> buffer->data.day >> buffer->data.month >> buffer->data.year;
		buffer->data.lastName = strLower(buffer->data.lastName);
		buffer->ptr = nullptr;

	}
	inFile.close();
	std::cout << "Complete" << std::endl;
	//oscar peterson
	//beatles essentia

}
void AddressBook::Search(std::string name)
{
	RecordList* trav = head;
	int index = 1;
	bool found = false;
	if (name == "Quit")
	{
		//std::cout << "Exiting to main menu" << std::endl;
		return;
	}
	else
	{
		while (trav != nullptr && !found) {

			if (trav->data.lastName == name || trav->data.numPhone == name)
			{
				///////////////////////////////////////////////////////Format
				std::cout << "Record #" << index <<" found, Outputting below: \n" << std::setw(SPACE) << std::left << "FirstName" << std::setw(SPACE) << "LastName" << std::left << std::setw(SPACE)
					<< "BuildingNum" << std::setw(SPACE) << std::left << "StreetName" << std::setw(SPACE) << std::left << "CityName"
					<< std::setw(SPACE) << std::left << "PhoneNumber" << "DD" << "MM" << "YY" << std::endl;
				found = true;
				std::cout << std::setw(SPACE) << std::left << trav->data.firstName << std::setw(SPACE) << trav->data.lastName << std::left << std::setw(SPACE)
					<< trav->data.numStreet << std::setw(SPACE) << std::left << trav->data.streetName << std::setw(SPACE) << std::left << trav->data.cityName
					<< std::setw(SPACE) << std::left << trav->data.numPhone << trav->data.day << trav->data.month << trav->data.year << std::endl;
				return;
			}
			else
			{
				trav = trav->ptr;
				index++;
			}
		}
		if (!found)
		{
			std::cout << "Sorry could not find any records matching " << name << ". Please try again or another option." << std::endl;
			return;
		}
	}
}


void AddressBook::AddEntry(RecordList* buffer, int index) 
{
	//If zero
	RecordList* trav = head;
	if (!index)
	{
		buffer->ptr = head;
		head = buffer;
		std::cout << "Successfully added to Addressbook " << std::endl;
	}
	else if (index >= size)// End
	{
		std::cout <<"Adding it to end of file since index exceeded AddressBook size." << std::endl;
		
		while (trav->ptr != nullptr)
		{
			trav = trav->ptr;
		}
		trav->ptr = buffer;

	}
	// Middle
	else {

		while(index)
		{
			index--;
			trav = trav->ptr;
			
		}
		buffer->ptr = trav->ptr;
		trav->ptr = buffer;
		std::cout << "Successfully added to Addressbook " << std::endl;
	}
	
}
void AddressBook::DeleteRec(std::string name)
{
	RecordList* toDelete;
	int index = 1;
	bool found = false;
	RecordList* trav=head;
	if (name == "Quit")
	{
		//std::cout << "Returning to main menu" << std::endl;
		return;
	}
	else if (trav == nullptr)
	{
		std::cout << "List is empty, cannot delete anything." << std::endl;
	}
	else if (trav->data.lastName == name || trav->data.numPhone == name)// if head needs to be deleted
	{
		toDelete = trav;
		head = head->ptr;
		std::cout << "Record #"<< index <<  " found, deleting below: \n" << std::setw(SPACE) << std::left << "FirstName" << std::setw(SPACE) << "LastName" << std::left << std::setw(SPACE)
			<< "BuildingNum" << std::setw(SPACE) << std::left << "StreetName" << std::setw(SPACE) << std::left << "CityName"
			<< std::setw(SPACE) << std::left << "PhoneNumber" << "DD" << "MM" << "YY" << std::endl;
		std::cout << std::setw(SPACE) << std::left << trav->data.firstName << std::setw(SPACE) << trav->data.lastName << std::left << std::setw(SPACE)
			<< trav->data.numStreet << std::setw(SPACE) << std::left << trav->data.streetName << std::setw(SPACE) << std::left << trav->data.cityName
			<< std::setw(SPACE) << std::left << trav->data.numPhone << trav->data.day << trav->data.month << trav->data.year << std::endl;
		delete toDelete;
		found = true;
		
	}
	else {
		while (trav->ptr != nullptr && !found) {
			index++;
			if (trav->ptr->data.lastName == name || trav->ptr->data.numPhone == name)
			{
				std::cout << "Record "<< index << " found, deleting below: \n" << std::setw(SPACE) << std::left << "FirstName" << std::setw(SPACE) << "LastName" << std::left << std::setw(SPACE)
					<< "BuildingNum" << std::setw(SPACE) << std::left << "StreetName" << std::setw(SPACE) << std::left << "CityName"
					<< std::setw(SPACE) << std::left << "PhoneNumber" << "DD" << "MM" << "YY" << std::endl;
				///////////////////////////////////////////////////////Format
				std::cout << std::setw(SPACE) << std::left << trav->ptr->data.firstName << std::setw(SPACE) << trav->ptr->data.lastName << std::left << std::setw(SPACE)
					<< trav->ptr->data.numStreet << std::setw(SPACE) << std::left << trav->ptr->data.streetName << std::setw(SPACE) << std::left << trav->ptr->data.cityName
					<< std::setw(SPACE) << std::left << trav->ptr->data.numPhone << trav->ptr->data.day << trav->ptr->data.month << trav->ptr->data.year << std::endl;
				found = true;
				toDelete = trav->ptr;



				trav->ptr = trav->ptr->ptr;
				delete toDelete;
			}
			if (trav->ptr != nullptr)
				trav = trav->ptr;
		}
	}
	if (!found)
	{
		std::cout << "Sorry could not find any records matching, " << name << ". Please try again or another option." << std::endl;
	}
}
void AddressBook::WriteFile()
{
	std::ofstream outFile;
	outFile.open("test.txt",std::fstream::out);
	outFile << std::setw(SPACE) << std::left << "FirstName" << std::setw(SPACE) << "LastName" << std::left << std::setw(SPACE)
		<< "BuildingNum" << std::setw(SPACE) << std::left << "StreetName" << std::setw(SPACE) << std::left << "CityName"
		<< std::setw(SPACE) << std::left << "PhoneNumber" << "DD" << "MM" << "YY" << std::endl;

	for (RecordList* trav = head; trav != nullptr; trav = trav->ptr)
	{

		
		
		outFile << std::setw(SPACE) << std::left << trav->data.firstName << std::setw(SPACE) << trav->data.lastName << std::left << std::setw(SPACE)
			<< trav->data.numStreet << std::setw(SPACE) << std::left << trav->data.streetName << std::setw(SPACE) << std::left << trav->data.cityName
			<< std::setw(SPACE) << std::left << trav->data.numPhone << trav->data.day << trav->data.month << trav->data.year << std::endl;
		
	}
	outFile.close();
	std::cout << "Successfully entered into file." << std::endl;

}