#include "Creator.h"
#include <fstream>
#include <iostream>
#include <string>

void createBinaryFile(const std::string& fileName, int numRecords) {
    std::fstream file;
    file.open(fileName, std::ios::binary | std::ios::out);
	Employee employee;

	for (int i = 0; i < numRecords; ++i) {
        std::cout << "Enter details for employee " << i + 1 << ":\n";
        std::cout << "Employee number: ";
        std::cin >> employee.num;
        std::cout << "Employee name: ";
        std::cin >> employee.name;
        std::cout << "Hours worked: ";
        std::cin >> employee.hours;

        file.write(reinterpret_cast<char*>(&employee), sizeof(Employee));
    }
    file.close();
}

void displayBinaryFileContents(const std::string& fileName) {
    std::ifstream binaryFile(fileName, std::ios::binary);
    Employee employee;
    std::cout << "Contents of the binary file:\n";
    while (binaryFile.read(reinterpret_cast<char*>(&employee), sizeof(Employee))) {
        std::cout << "Employee " << employee.num << ", " << employee.name << ", " << employee.hours << "\n";
    }
    binaryFile.close();
}

int main(int argc, char* argv[]) {
    
    std::cout << argc;
    
    createBinaryFile(argv[1], atoi(argv[2]));
    displayBinaryFileContents(argv[1]);

    std::string s;
    std::getline(std::cin, s);
}