#pragma once
#include <vector>

struct Data;

void quickSort(Data* arr, int left, int right);
void merge(Data* arr, int left, int mid, int right);
void mergeSort(Data* arr, int left, int right);
void bucketSort(Data* arr, int size);
void bogoSort(Data* arr, int size);
void Shuffle(Data* arr, int size);
bool IsSorted(Data* arr, int size);
bool isSorted(Data* arr, int size);