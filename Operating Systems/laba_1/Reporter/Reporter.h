#pragma once
#include <string>

struct Employee {
    int num;
    char name[10];
    double hours;
};

void generateReport(const std::string& inputFileName, const std::string& outputFileName, double hourlyRate);
void displayReport(const std::string& fileName);