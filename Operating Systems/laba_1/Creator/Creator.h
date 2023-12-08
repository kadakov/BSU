#pragma once
#include <string>

struct Employee {
    int num;
    char name[10];
    double hours;
};

void createBinaryFile(const std::string& fileName, int numRecords);
void displayBinaryFileContents(const std::string& fileName);