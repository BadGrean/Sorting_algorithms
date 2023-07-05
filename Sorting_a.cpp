#pragma once
#include "Sorting_a.h"
#include <algorithm>
#include <string>
#include <cstdlib>
#include <ctime>
struct Data {
    int key_number;
    std::string title;
    float rating;
};

void quickSort(Data* arr, int left, int right) 
{
    int i = left, j = right;
    float pivot = arr[(left + right) / 2].rating;

    while (i <= j) {
        while (arr[i].rating < pivot) {
            i++;
        }
        while (arr[j].rating > pivot) {
            j--;
        }
        if (i <= j) {
            std::swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }

    if (left < j) {
        quickSort(arr, left, j);
    }
    if (i < right) {
        quickSort(arr, i, right);
    }
}

void merge(Data* arr, int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    Data* L = new Data[n1];
    Data* R = new Data[n2];

    // Copy data to temporary arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Merge the temporary arrays back into arr[left..right]
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (L[i].rating <= R[j].rating) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    // Free the temporary arrays
    delete[] L;
    delete[] R;
}

void mergeSort(Data* arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

void bucketSort(Data* arr, int size) {
    const int numBuckets = 10;
    std::vector<Data> buckets[numBuckets];

    // Assign elements to respective buckets based on rating
    for (int i = 0; i <= size; i++) {
        int bucketIndex = arr[i].rating - 1;
        buckets[bucketIndex].push_back(arr[i]);
    }

    // Merge sorted buckets back into original array
    int index = 0;
    for (int i = 0; i < numBuckets; i++) {
        for (const auto& data : buckets[i]) {
            arr[index] = data;
            index++;
        }
    }
}
bool IsSorted(Data* arr, int size)
{
    while (--size >= 1)
        if (arr[size].rating < arr[size - 1].rating) return false;

    return true;
}

void Shuffle(Data* arr, int size)
{
    int rnd;
    Data temp;

    for (int i = 0; i < size; ++i)
    {
        rnd = rand() % size;
        temp = arr[i];
        arr[i] = arr[rnd];
        arr[rnd] = temp;
    }
}

void bogoSort(Data* arr, int size)
{
    while (!IsSorted(arr, size))
        Shuffle(arr, size);
}

bool isSorted(Data* arr, int size) 
{
    for (int i = 1; i < size; i++) {
        if (arr[i].rating < arr[i - 1].rating) {
            return false;
        }
    }
    return true;
}