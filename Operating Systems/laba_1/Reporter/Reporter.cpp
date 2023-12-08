#include "Reporter.h"
#include <fstream>
#include <iostream>


void generateReport(const std::string& inputFileName, const std::string& outputFileName, double hourlyRate) {
    std::ifstream inputFile(inputFileName, std::ios::binary | std::ios::in);
    std::ofstream outputFile(outputFileName, std::ios::out);

    outputFile << "Report ifle \"" << inputFileName << "\":\n";
    
    outputFile << "Num, F, 3, 3\n";

    Employee employee;
    while (inputFile.read(reinterpret_cast<char*>(&employee), sizeof(Employee))) {
        double salary = employee.hours * hourlyRate;
        outputFile << employee.num << ", " << employee.name << ", " << employee.hours << ", " << salary << "\n";
        std::cout << employee.num << ", " << employee.name << ", " << employee.hours << ", " << salary << "\n";
    }

    inputFile.close();
    outputFile.close();
}

void displayReport(const std::string& fileName) {
    std::ifstream reportFile(fileName, std::ios::in);
    if (reportFile.is_open()) {
        std::string line;
        while (std::getline(reportFile, line)) {
            std::cout << line << "\n";
        }
        reportFile.close();
    }
    else {
        std::cerr << "Unable to open the report file.\n";
    }
}

int main(int argc, char* argv[]) {
    generateReport(argv[1], argv[2], std::stod(argv[3]));
    displayReport(argv[1]);
    
    std::string s;
    std::getline(std::cin, s);
}