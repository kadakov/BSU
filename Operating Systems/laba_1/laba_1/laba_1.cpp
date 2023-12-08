#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>

struct Employee {
	int num;
	char name[10];
	double hours;
};

int main() {
	std::string binaryFileName;
	int numRecords;

	std::cout << "Enter the binary file name";
	std::cin >> binaryFileName;
	std::cout << binaryFileName;

	std::cout << "Enter the number of records";
	std::cin >> numRecords;

	STARTUPINFO creatorStartUpInfo;
	creatorStartUpInfo.cb = sizeof(creatorStartUpInfo);
	PROCESS_INFORMATION creatorProcessInfo;
	std::string creatorCommand = "Creator.exe " + binaryFileName + " " + std::to_string(numRecords);
	ZeroMemory(&creatorStartUpInfo, sizeof(creatorStartUpInfo));
	ZeroMemory(&creatorProcessInfo, sizeof(creatorProcessInfo));
	if (CreateProcess(NULL, const_cast<char*>(creatorCommand.c_str()), NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &creatorStartUpInfo, &creatorProcessInfo))
		std::cout << "OK";
	else
		std::cout << "NOT OKJ";

	WaitForSingleObjectEx(creatorProcessInfo.hProcess, INFINITE, FALSE);

	std::ifstream binaryFile(binaryFileName, std::ios::binary | std::ios::in);
	Employee employee;
	std::cout << "Content of the binary file: \n";
	while (binaryFile.read(reinterpret_cast<char*>(&employee), sizeof(Employee))) {
		std::cout << "Employee " << employee.num << " " << employee.name << " " << employee.hours << "\n";
	}
	binaryFile.close();

	std::string reportFileName;
	double hourlyRate;

	std::cout << "Enter the report file name: ";
	std::cin >> reportFileName;
	std::cout << "Enter the hourly rate: ";
	std::cin >> hourlyRate;

	STARTUPINFO reporterStartUpInfo = { sizeof(STARTUPINFO) };
	PROCESS_INFORMATION reporterProcessInfo;
	std::string reporterCommand = "Reporter.exe " + binaryFileName + " " + reportFileName + " " + std::to_string(hourlyRate);
	ZeroMemory(&reporterStartUpInfo, sizeof(reporterStartUpInfo));
	ZeroMemory(&reporterProcessInfo, sizeof(reporterProcessInfo));
	CreateProcess(NULL, const_cast<char*>(reporterCommand.c_str()), NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &reporterStartUpInfo, &reporterProcessInfo);

	WaitForSingleObjectEx(reporterProcessInfo.hProcess, INFINITE, FALSE);

	std::ifstream reportFile(reportFileName, std::ios::in);
	if (reportFile.is_open()) {
		std::string line;
		while (std::getline(reportFile, line)) {
			std::cout << line << "\n";
		}
		reportFile.close();
	}
	else {
		std::cerr << "Unable to open the report file\n";
	}

	return 0;
}