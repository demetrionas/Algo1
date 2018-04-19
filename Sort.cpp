// QuickSort2.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

vector<int> generateRandomVector(int size)
{
    vector<int> result;
    if (size <= 0)
        return result;
    result.reserve(size);
    for (auto i = 0; i < size; ++i) {
        result.push_back(rand() % 101);
    }
    return result;
}

void outputVector(const vector<int>& vec)
{
    for (auto& i : vec) {
        cout << i << " ";
    }
    cout << "\n";
}

bool testSorting(const vector<int>& vec)
{
    if (!vec.size())
        return true;
    auto prev = vec[0];
    for (auto i = 1; i < vec.size(); ++i) {
        if (vec[i] < prev)
            return false;
        prev = vec[i];
    }
    return true;
}

void swap(vector<int>& vec, size_t left, size_t right)
{
    auto temp = vec[left];
    vec[left] = vec[right];
    vec[right] = temp;
}

int partition(vector<int>& vec, int lo, int hi)
{
    auto pivot = lo;
    auto i = lo;
    auto j = hi + 1;
    while (true)
    {
        while (vec[++i] <= vec[pivot]) {
            if (i >= hi) break;
        }
        while (vec[--j] > vec[pivot]) {
            if (j <= lo) break;
        }
        if (i >= j) break;
        swap(vec, i, j);
    }
    swap(vec, pivot, j);
    return j;
}

void sort(vector<int>& vec, int lo, int hi)
{
    if (lo >= hi)
        return;
    auto j = partition(vec, lo, hi);
    sort(vec, lo, j - 1);
    sort(vec, j + 1, hi);
}

void merge(vector<int>& vec, vector<int>& aux, int lo, int mid, int hi)
{
    int i, j, k;
    k = i = lo;
    j = mid + 1;
    while (k <= hi) {
        if (i > mid) 
            vec[k] = aux[j++];
        else if (j > hi)
            vec[k] = aux[i++];
        else if (aux[i] < aux[j])
            vec[k] = aux[i++];
        else 
            vec[k] = aux[j++];
        k++;
    }
}

void mergeSort(vector<int>& vec, vector<int>& aux, int lo, int hi)
{
    if (lo >= hi)
        return;
    int mid = lo + (hi - lo) / 2;
    mergeSort(aux, vec, lo, mid);
    mergeSort(aux, vec, mid + 1, hi);
    merge(vec, aux, lo, mid, hi);
}

void quickSort(vector<int>& vec)
{
    auto j = partition(vec, 0, vec.size() - 1);
    sort(vec, 0, j - 1);
    sort(vec, j + 1, vec.size() - 1);
}

void mergeSort(vector<int>& vec)
{
    if (vec.size() <= 1)
        return;
    vector<int> aux(vec);

    int mid = vec.size() / 2;
    mergeSort(aux, vec, 0, mid);
    mergeSort(aux, vec, mid + 1, vec.size() - 1);
    merge(vec, aux, 0, mid, vec.size() - 1);
}

void sort(vector<int>& vec)
{
    //quickSort(vec);
    mergeSort(vec);
}

int main(int argc, char* argv[])
{
    srand(time(nullptr));

    vector<int> test;

    bool f1(false);
    for (auto i = 0; i < 100; ++i)
    {
        cout << "\nTest_" << (i + 1) << "\n Input array:\n";
        test = generateRandomVector(10);
        outputVector(test);
        cout << "Output array:\n";

        sort(test);
        
        outputVector(test);
        auto f = !testSorting(test);
        f1 |= f;
        cout << "\nTest_" << (i + 1) << " RESULT: " << (!f ? "SORTED" : "UNSORTED");
    }
    cout << "\nOVERALL RESULT: " << (!f1 ? "SORTED" : "UNSORTED");
    cin.get();
    return 0;
}

