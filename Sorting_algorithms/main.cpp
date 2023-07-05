#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "time_measure.h"
#include "Sorting_a.h"


struct Data {
    int key_number;
    std::string title;
    float rating;
};

void addDataToFile(int arraySize, double executionTime, float median, float average) {
    std::ofstream outputFile("bogo.txt", std::ios_base::app);
    if (outputFile.is_open()) {
        outputFile << arraySize << "," << executionTime << "," << median << "," << average << std::endl;
        outputFile.close();
    }
    else {
        std::cout << "Failed to open output file." << std::endl;
    }
}

int main() {
    float median = 0;
    float avrege = 0;
    Data* dataArray;
    int arraySize;

    std::ifstream dataFile("movie_data.csv");

    if (!dataFile.is_open()) {
        std::cout << "Failed to open data file." << std::endl;
        return 1;
    }
    int numLinesToRead = 0;
    std::cout << "Enter the number of lines to read (0 for all): ";
    std::cin >> numLinesToRead;
    // Count the number of lines in the file
    int numLines = 0;
    std::string line;

    if (numLinesToRead == 0)
    {
        while (getline(dataFile, line))
        {
            numLines++;
        }
        dataFile.clear();
        dataFile.seekg(0, std::ios::beg);
    }


    if (numLinesToRead == 0)
    {
        numLinesToRead = numLines;
    }

    dataArray = new Data[numLinesToRead];
    arraySize = 0;

    bool firstline = true;
    int lineCount = 0;

    while (getline(dataFile, line) && lineCount < numLinesToRead)
    {
        if (firstline)
        {
            firstline = false;
            continue;
        }

        int comma1 = line.find(",");
        dataArray[arraySize].key_number = stoi(line.substr(0, comma1));

        int comma2 = line.find_last_of(",");
        dataArray[arraySize].title = line.substr(comma1 + 1, comma2 - comma1 - 1);

        try
        {
            dataArray[arraySize].rating = stof(line.substr(comma2 + 1));

            if (dataArray[arraySize].title.empty())
            {
                //std::cout << "Warning: 2nd column is an empty string, skipping line." << std::endl;
                continue;
            }

            arraySize++;
            lineCount++;
        }
        catch (const std::invalid_argument&)
        {
            //std::cout << "Not float on line: " << dataArray[arraySize].key_number << std::endl;
        }

    }



    dataFile.close();

    
    Data* tempArray = new Data[arraySize];
    for (int i = 0; i < arraySize; i++)
    {
        tempArray[i] = dataArray[i];
    }
    delete[] dataArray;
    dataArray = tempArray;

    std::cout << "here" << std::endl;

    double start_time_wall = get_wall_time();
    double start_time_cpu = get_cpu_time();

    //quickSort(dataArray, 0, arraySize - 1);
    //mergeSort(dataArray, 0, arraySize - 1);
    //bucketSort(dataArray, arraySize - 1);
    bogoSort(dataArray, arraySize);

    double end_time_cpu = get_cpu_time();
    double end_time_wall = get_wall_time();

    if (arraySize % 2 == 0)
    {
        median = median = (dataArray[arraySize / 2].rating + dataArray[(arraySize / 2) - 1].rating)/2;
    }
    else
    {
        median = dataArray[arraySize / 2].rating;
    }

    for (int i = 0; i < arraySize; i++)
    {
        avrege += dataArray[i].rating;
    }
    avrege = avrege / arraySize;


    /*for (int i = 0; i < arraySize; i++)
    {
        std::cout << dataArray[i].key_number << " " << dataArray[i].title << " " << dataArray[i].rating << std::endl;
    }*/

    std::cout << arraySize << std::endl;
    std::cout << "execution time cpu: " << (end_time_cpu - start_time_cpu) << "wall time: " << (end_time_wall - start_time_wall) << std::endl;
    std::cout << isSorted(dataArray, arraySize);

    if (isSorted(dataArray, arraySize))
    {
        addDataToFile(arraySize, (end_time_wall - start_time_wall), median, avrege);
    }

    delete[] dataArray;

    return 0;
}
