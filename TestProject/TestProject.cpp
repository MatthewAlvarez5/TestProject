/******************************************************************************
Author: Group
Course: CSCI 115 Project
Assignment: Sorting Algorithms

Notes:
*******************************************************************************/
#include <iostream>
#include <ctime>
using namespace std;

// Function to calculate power recursively
int power(int base, int exponent) {
    // Base case
    if (exponent == 0) {
        return 1;
    }
    // Recursive case
    else if (exponent > 0) {
        return base * power(base, exponent - 1);
    }
    else { // exponent < 0
        return 1 / (base * power(base, -exponent - 1));
    }
}


// inserts sorted values until halfway then random
void randomArr(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        //arr[i] = rand()%1000;
        arr[i] = size-i;
    }
}

// prints array 
void printArray(int arr[], int size) {
    cout << "[";
    for (int i = 0; i < size - 1; i++) {
        cout << arr[i] << ",";
    }
    cout << arr[size - 1] << "]\n";
    return;
}

//swap values
void Swap(int* a, int* b) //swap values in Node
{
    int temp = *a;
    *a = *b;
    *b = temp;
}


/**********************************************************************************************************************************************/

//Bubble Sort
void bubbleSort(int* arr, int size)
{
    int min;
    for (int i = size; i > 0; i--)
    {
        for (int j = 0; j < i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                min = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = min;
            }
        }
    }
}

// selectionSort
void selectionSort(int arr[], int size) {
    int min;

    for (int i = 0; i < size; i++) {
        min = arr[i];
        for (int j = i; j < size; j++) {
            if (arr[j] < min) {
                // swap i and j
                min = arr[j];
                arr[j] = arr[i];
                arr[i] = min;
            }
        }
    }
    return;
}


// Insertion Sort
void insertionSort(int* arr, int size)
{
    int j, key;
    for (int i = 1; i < size; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// merge
void merge(int* arr, int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;

    int* lowArr;
    lowArr = new int[n1];
    int* highArr;
    highArr = new int[n2];

    for (int i = 0; i < n1; i++)
    {
        lowArr[i] = arr[low + i];
    }
    for (int j = 0; j < n2; j++)
    {
        highArr[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = low;
    while (i < n1 && j < n2)
    {
        if (lowArr[i] <= highArr[j])
        {
            arr[k] = lowArr[i];
            i++;
        }
        else
        {
            arr[k] = highArr[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = lowArr[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = highArr[j];
        j++;
        k++;
    }
}

// merge sort
void mergeSort(int* arr, int low, int high) {
    if (low < high)
    {
        int mid = (low + high) / 2;

        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);

        merge(arr, low, mid, high);
    }
}

// user input changes pivot
int pivotChoice(int* arr, int low, int high, int choice) {
    if (choice == 1) {    // first value in array
        return arr[low];
    }
    else if (choice == 2) {   // random value in array
        int n = high - low;
        int random = rand() % n + low;
        return arr[random];
    }
    else if (choice == 3) {  //median value
        return arr[(high + low) / 2];
    }
    return 0;
}

// Quick sort partition
int partition(int* arr, int low, int high, int choice) {
    int pivot = pivotChoice(arr, low, high, choice); // pivot element
    int i = low - 1;
    int j = high + 1;

    while (true) {
        do {
            j--;
        } while (arr[j] > pivot);   //arr[j] = pivot

        do {
            i++;
        } while (arr[i] < pivot);   //arr[i] = pivot

        if (i < j) {
            swap(arr[i], arr[j]);
        }
        else {
            return j;
        }
    }
}

// Quick sort   
void quickSort(int* arr, int low, int high, int choice)
{
    if (low < high) {
        int pivot = partition(arr, low, high, choice);

        quickSort(arr, pivot + 1, high, choice);
        quickSort(arr, low, pivot, choice);
    }
}

// Counting Sort
void countingSort(int* arr, int size) {
    int max = 0;

    // get max
    for (int i = 0; i < size; i++) {
        if (max < arr[i]) {
            max = arr[i];
        }
    }

    // create auxilary
    int* aux = new int[max + 1];
    for (int i = 0; i < max + 1; i++) {
        aux[i] = 0;
    }
    // aux = count
    for (int i = 0; i < size; i++) {
        aux[arr[i]] = aux[arr[i]] + 1;
    }
    // aux = cumulative count
    for (int i = 1; i < max + 1; i++) {
        aux[i] = aux[i] + aux[i - 1];
    }
    // second array copies first
    // second array adds to complexity
    int* arr2 = new int[size];
    for (int i = 0; i < size; i++) {
        arr2[i] = arr[i];
    }
    // sorts
    for (int i = size - 1; i >= 0; i--) {
        arr[aux[arr2[i]] - 1] = arr2[i];
    }
}

// Radix sort
void radixSort(int* arr, int size) {
    int max = 0;
    // get max
    for (int i = 0; i < size; i++) {
        if (max < arr[i]) {
            max = arr[i];
        }
    }

    // Find # of digits in max
    int temp = max;
    int digits = 0;
    while (temp != 0) {
        temp = temp / 10;
        digits++;
    }

    // Create auxilary array
    int* aux = new int[10];
    for (int i = 0; i < 10; i++) {
        aux[i] = 0;
    }

    // count tracks units
    int count = 0;
    int* arr2 = new int[size];
    while (count < digits) {
        //create aux
        for (int i = 0; i < 10; i++) {
            aux[i] = 0;
        }
        // find count
        for (int i = 0; i < size; i++) {
            aux[(arr[i] / power(10, count)) % 10] = aux[(arr[i] / power(10, count)) % 10] + 1;
        }
        // cumulative count
        for (int i = 1; i < 10; i++) {
            aux[i] = aux[i] + aux[i - 1];
        }
        // copy array
        for (int i = 0; i < size; i++) {
            arr2[i] = arr[i];
        }

        // sort and decrement each count
        for (int i = size - 1; i >= 0; i--) {
            arr[aux[(arr2[i] / power(10, count)) % 10] - 1] = arr2[i];
            aux[(arr2[i] / power(10, count)) % 10] = aux[(arr2[i] / power(10, count)) % 10] - 1;
        }
        count++;
    }

}

// Main
int main()
{
    int size = 500000;
    int* arr = new int[size];


    cout << "Random array values prior to sort:\t\t";
    randomArr(arr, size);
    //printArray(arr, size);
    clock_t start1 = clock();
    selectionSort(arr, size);
    clock_t end1 = clock();
    cout << "\nRandom array values after counting sort:\t";
    //printArray(arr, size);
    cout << "\nTime taken to sort:\t\t\t" << (end1 - start1) / CLOCKS_PER_SEC << " seconds" << endl << endl;


    // cout << "Random array values prior to sort:\t";
    // randomArr(arr, size);
    // //printArray(arr, size);
    // clock_t start2 = clock();
    // radixSort(arr, size);
    // clock_t end2 = clock();
    // cout << "\nRandom array values after radix sort:\t";
    // //printArray(arr, size);
    // cout << "\nTime taken to sort:\t\t\t" << (end2 - start2) / CLOCKS_PER_SEC << " seconds" << endl;

    return 0;
}



