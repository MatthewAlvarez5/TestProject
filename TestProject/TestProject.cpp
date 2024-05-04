/******************************************************************************
Author(s): Matthew Alvarez, Jovani Benavides, Mateo Sspina, Nestor Garcia
Course: CSCI 115 Project
Assignment: Sorting Algorithms

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
    return 1;
}

// Array Sort Types ----------------------------------------------------------------------------------------------------------------------------------------------
// Array of all zeros
void zeroArr(int* arr, int size) {
    for (int i = 0; i < size; i++) {

        arr[i] = 0;  //best
    }
}

// sorted 0 to size-1
void sortedArr(int* arr, int size) {
    for (int i = 0; i < size; i++) {

        arr[i] = i;  //best
    }
}

// reverse sorted size to 1
void reverseArr(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = size-i;  //worst
    }
}

// array of random values < size
void randomArr(int* arr, int size) {
    for (int i = 0; i < size; i++) {   
        arr[i] = rand()%size;
    }
}

// random values of 7 digits 
void randomLargeArr(int* arr, int size) {
    for (int i = 0; i < size; i++) {

        arr[i] = rand()+1000000 % (10000000);
    }
}

// array of random values where one is much larger than the others
// radix worst case
void oneArr(int* arr, int size) {
    arr[size - 1] = 1000000;
    for (int i = 0; i < size-1; i++) {

        arr[i] = rand()%1000;
    }
}

// Swap ----------------------------------------------------------------------------------------------------------------------------------------------
void Swap(int* a, int* b) //swap values in Node
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 1 Bubble Sort ----------------------------------------------------------------------------------------------------------------------------------------------
// Written By: Matteo Spina
// Formatted by: Matthew Alvarez
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

// 2 Selection ----------------------------------------------------------------------------------------------------------------------------------------------
// Written By: Nestor Garcia
// Formatted by: Matthew Alvarez
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

// 3 Insertion ----------------------------------------------------------------------------------------------------------------------------------------------
// Written By: Jovani Benavides
// Formatted by: Matthew Alvarez
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

// 4 Merge ----------------------------------------------------------------------------------------------------------------------------------------------
// Written By: Matteo Spina
// Formatted by: Matthew Alvarez
// merge 
void merge(int* arr, int low, int mid, int high) {
    // Calculate sizes of two subarrays to be merged
    int n1 = mid - low + 1; // Size of the left subarray
    int n2 = high - mid;    // Size of the right subarray

    // Create temporary arrays to hold the elements of the two subarrays
    int* lowArr;
    lowArr = new int[n1];   // Array for the left subarray
    int* highArr;
    highArr = new int[n2];  // Array for the right subarray

    // Copy data to temporary arrays lowArr[] and highArr[]
    for (int i = 0; i < n1; i++)
    {
        lowArr[i] = arr[low + i]; // Copy elements from the left subarray
    }
    for (int j = 0; j < n2; j++)
    {
        highArr[j] = arr[mid + 1 + j]; // Copy elements from the right subarray
    }

    // Merge the two temporary arrays back into arr[low..high]
    int i = 0, j = 0, k = low; // Initialize indices for merging
    while (i < n1 && j < n2)
    {
        if (lowArr[i] <= highArr[j]) // Compare elements from the two subarrays
        {
            arr[k] = lowArr[i]; // Copy smaller element to arr
            i++;
        }
        else
        {
            arr[k] = highArr[j]; // Copy smaller element to arr
            j++;
        }
        k++;
    }

    // Copy the remaining elements of lowArr[], if any
    while (i < n1)
    {
        arr[k] = lowArr[i]; // Copy remaining elements from left subarray
        i++;
        k++;
    }

    // Copy the remaining elements of highArr[], if any
    while (j < n2)
    {
        arr[k] = highArr[j]; // Copy remaining elements from right subarray
        j++;
        k++;
    }

    // Free the dynamically allocated memory
    delete[] lowArr;
    delete[] highArr;
}
// merge sort algorithm
void mergeSort(int* arr, int low, int high) {
    if (low < high)
    {
        int mid = (low + high) / 2;

        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);

        merge(arr, low, mid, high);
    }
}

// 5 Quick ----------------------------------------------------------------------------------------------------------------------------------------------
// Written By: Jovani Benavides
// Formatted by: Matthew Alvarez
// user input changes pivot 5
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
// The pivot element is chosen based on the choice parameter.
int partition(int* arr, int low, int high, int choice) {
    // Choose the pivot element based on the specified choice
    int pivot = pivotChoice(arr, low, high, choice); // pivot element

    // Initialize indices i and j for partitioning
    int i = low - 1;
    int j = high + 1;

    // Continue partitioning until i and j meet
    while (true) {
        // Move j towards left until arr[j] is less than or equal to the pivot
        do {
            j--;
        } while (arr[j] > pivot);   //arr[j] = pivot

        // Move i towards right until arr[i] is greater than or equal to the pivot
        do {
            i++;
        } while (arr[i] < pivot);   //arr[i] = pivot

        // If there are elements to be swapped, swap arr[i] and arr[j]
        // Otherwise, return the partition index (j)
        if (i < j) {
            swap(arr[i], arr[j]); // Swap elements to maintain partition
        }
        else {
            return j; // Return the partition index
        }
    }
}

// Quick sort algorithm
void quickSort(int* arr, int low, int high, int choice)
{
    if (low < high) {
        int pivot = partition(arr, low, high, choice);

        quickSort(arr, pivot + 1, high, choice);
        quickSort(arr, low, pivot, choice);
    }
}

// 6 Heap ----------------------------------------------------------------------------------------------------------------------------------------------
// Written By: Matthew Alvarez
// Formatted by: Matthew Alvarez
class Heap
{
private:
    int size;
    int maxSize;
    int* arr;
    int Parent(int i) { return (i - 1) / 2; }
    int LeftChild(int i) { return (2 * i + 1); }
    int RightChild(int i) { return (2 * i + 2); }
    void MaxHeapify(int i);

public:
    Heap(int mSize) {                   // constructor Heap (new array)
        size = 0;
        maxSize = mSize;
        arr = new int[mSize];
    }

    Heap(int* array, int nSize, int mSize) { // constructor Heap (input array)
        size = nSize;
        maxSize = mSize;
        arr = array;
    }

    /*~Heap() //delete entire heap
    {
        delete[] arr;
    }*/

    void BuildMaxHeap() {       // Build Max Heap
        for (int i = size / 2 - 1; i >= 0; i--) // Heapify Each Parent
        {
            MaxHeapify(i);
        }
    }

    void AscendingHeapSort();
    int ExtractMax();
};

void Heap::MaxHeapify(int i)
{
    int max = i;
    int left = LeftChild(i);
    int right = RightChild(i);

    // Recursion stops when parent is larger than children or children are not within the heap

    if (left < size && arr[left] > arr[max]) {    // max is parent or left
        max = left;
    }
    if (right < size && arr[right] > arr[max]) {    // max is previous max or right
        max = right;
    }
    if (i != max) {
        Swap(&arr[i], &arr[max]); // swap parent with largest child
        MaxHeapify(max);
    }
}

void Heap::AscendingHeapSort() {
    BuildMaxHeap();
    int cSize = size;   // stores current size and allows size to change
    for (int i = size - 1; i >= 0; i--) {   //swaps max number to last index
        Swap(&arr[0], &arr[i]);
        size--;
        MaxHeapify(0);  //root is new largest
    }
    size = cSize;       // returns size to original value
}

int Heap::ExtractMax() {
    int temp = arr[0];
    size--;
    arr[0] = arr[size]; //replace and delete root
    MaxHeapify(0);
    return(temp);       //return root(max)
}

// 7 Counting ----------------------------------------------------------------------------------------------------------------------------------------------
// Written By: Matthew Alvarez
// Formatted by: Matthew Alvarez
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

// 8 Radix ----------------------------------------------------------------------------------------------------------------------------------------------
// Written By: Matthew Alvarez
// Formatted by: Matthew Alvarez
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

// ---------------------------------------------------------------------------------------------------------------------------------------------------
// Main ----------------------------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------------------------------------
int main()
{
    int size;
    int algo = -1;
    int cont = -1;
    bool exit1 = false;

    //bbl, sel, ins, merge, quick, heap, counting, radix

    // Choose Algorithm ----------------------------------------------------------------------------------------------------------------------------------------------
    cout << "Choose one of the following sorting algorithms: \n";
    cout << "[1]: Bubble Sort, [2]: Selection Sort, [3]: Insertion Sort, [4]: Merge Sort, [5]: Quick Sort, [6]: Heap Sort, [7]: Counting Sort, [8]: Radix Sort\n";

    do {
        cout << "Select one of the above choices: ";
        cin >> algo;
        switch (algo)
        {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
                exit1 = true;
                break;
            default: // otherwise tell the user what went wrong
                cout << "Oops, that input is invalid.  Please try again.\n";
        }
    } while (exit1 == false);

    exit1 = false;

    // Choose Size ----------------------------------------------------------------------------------------------------------------------------------------------
    cout << "\nChoose one of the following sizes for the array: \n";
    cout << "[1]: 100,000, [2]: 1,000,000, [3]: 3,000,000\n";

    do {
        cout << "Select one of the above choices: ";
        cin >> size;
        switch (size)
        {
            case 1:
                size = 100000;
                exit1 = true;
                break;
            case 2:
                size = 1000000;
                exit1 = true;
                break;
            case 3:
                size = 3000000;
                exit1 = true;
                break;
            default: // otherwise tell the user what went wrong
                cout << "Oops, that input is invalid.  Please try again.\n";
        }
    } while (exit1 == false);

    int* arr = new int[size];

    cout << "\n----------------------------------------------------------" << endl;

    switch(algo) {
        // 1 Bubble ----------------------------------------------------------------------------------------------------------------------------------------------
        case 1:
        {
            cout << "Bubble Best Case: " << endl;
            sortedArr(arr, size);
            clock_t start1 = clock();
            bubbleSort(arr, size);
            clock_t end1 = clock();
            cout << "\nTime taken to sort:\t\t\t" << (double)(end1 - start1) * 1000.0 / CLOCKS_PER_SEC << " milliseconds" << endl << endl;

            cout << "----------------------------------------------------------" << endl;

            cout << "Bubble Average Case: " << endl;
            randomArr(arr, size);
            clock_t start2 = clock();
            bubbleSort(arr, size);
            clock_t end2 = clock();
            cout << "\nTime taken to sort:\t\t\t" << (double)(end2 - start2) * 1000.0 / CLOCKS_PER_SEC << " milliseconds" << endl << endl;

            cout << "----------------------------------------------------------" << endl;

            cout << "Bubble Worst Case: " << endl;
            reverseArr(arr, size);
            clock_t start3 = clock();
            bubbleSort(arr, size);
            clock_t end3 = clock();
            cout << "\nTime taken to sort:\t\t\t" << (double)(end3 - start3) * 1000.0 / CLOCKS_PER_SEC << " milliseconds" << endl << endl;

            cout << "----------------------------------------------------------" << endl;
            break;
        }
        // 2 Selection ----------------------------------------------------------------------------------------------------------------------------------------------
        case 2:
        {
            cout << "Selection Best Case: " << endl;
            sortedArr(arr, size);
            clock_t start4 = clock();
            selectionSort(arr, size);
            clock_t end4 = clock();
            cout << "\nTime taken to sort:\t\t\t" << (double)(end4 - start4) * 1000.0 / CLOCKS_PER_SEC << " milliseconds" << endl << endl;

            cout << "----------------------------------------------------------" << endl;

            cout << "Selection Average Case: " << endl;
            randomArr(arr, size);
            clock_t start5 = clock();
            selectionSort(arr, size);
            clock_t end5 = clock();
            cout << "\nTime taken to sort:\t\t\t" << (double)(end5 - start5) * 1000.0 / CLOCKS_PER_SEC << " milliseconds" << endl << endl;

            cout << "----------------------------------------------------------" << endl;

            cout << "Selection Worst Case: " << endl;
            reverseArr(arr, size);
            clock_t start6 = clock();
            selectionSort(arr, size);
            clock_t end6 = clock();
            cout << "\nTime taken to sort:\t\t\t" << (double)(end6 - start6) * 1000.0 / CLOCKS_PER_SEC << " milliseconds" << endl << endl;

            cout << "----------------------------------------------------------" << endl;
            break;
        }
        // 3 Insertion ----------------------------------------------------------------------------------------------------------------------------------------------
        case 3:
        {
            cout << "Insertion Best Case: " << endl;
            sortedArr(arr, size);
            clock_t start7 = clock();
            insertionSort(arr, size);
            clock_t end7 = clock();
            cout << "\nTime taken to sort:\t\t\t" << (double)(end7 - start7) * 1000.0 / CLOCKS_PER_SEC << " milliseconds" << endl << endl;

            cout << "----------------------------------------------------------" << endl;

            cout << "Insertion Average Case: " << endl;
            randomArr(arr, size);
            clock_t start8 = clock();
            insertionSort(arr, size);
            clock_t end8 = clock();
            cout << "\nTime taken to sort:\t\t\t" << (double)(end8 - start8) * 1000.0 / CLOCKS_PER_SEC << " milliseconds" << endl << endl;

            cout << "----------------------------------------------------------" << endl;

            cout << "Insertion Worst Case: " << endl;
            reverseArr(arr, size);
            clock_t start9 = clock();
            insertionSort(arr, size);
            clock_t end9 = clock();
            cout << "\nTime taken to sort:\t\t\t" << (double)(end9 - start9) * 1000.0 / CLOCKS_PER_SEC << " milliseconds" << endl << endl;

            cout << "----------------------------------------------------------" << endl;
            //break;
        }
        // 4 merge ----------------------------------------------------------------------------------------------------------------------------------------------
        case 4:
        {
            cout << "Merge Best Case: " << endl;
            sortedArr(arr, size);
            clock_t start10 = clock();
            mergeSort(arr, 0, size);
            clock_t end10 = clock();
            cout << "\nTime taken to sort:\t\t\t" << (double)(end10 - start10) * 1000.0 / CLOCKS_PER_SEC << " milliseconds" << endl << endl;

            cout << "----------------------------------------------------------" << endl;

            cout << "Merge Average Case: " << endl;
            randomArr(arr, size);
            clock_t start11 = clock();
            mergeSort(arr, 0, size);
            clock_t end11 = clock();
            cout << "\nTime taken to sort:\t\t\t" << (double)(end11 - start11) * 1000.0 / CLOCKS_PER_SEC << " milliseconds" << endl << endl;

            cout << "----------------------------------------------------------" << endl;

            cout << "Merge Worst Case: " << endl;
            reverseArr(arr, size);
            clock_t start12 = clock();
            mergeSort(arr, 0, size);
            clock_t end12 = clock();
            cout << "\nTime taken to sort:\t\t\t" << (double)(end12 - start12) * 1000.0 / CLOCKS_PER_SEC << " milliseconds" << endl << endl;

            cout << "----------------------------------------------------------" << endl;
            break;
        }
        // 5 Quick ----------------------------------------------------------------------------------------------------------------------------------------------
        case 5:
        {
            cout << "Quick Best Case: " << endl;
            sortedArr(arr, size);
            clock_t start13 = clock();
            quickSort(arr, 0, size, 3);
            clock_t end13 = clock();
            cout << "\nTime taken to sort:\t\t\t" << (double)(end13 - start13) * 1000.0 / CLOCKS_PER_SEC << " milliseconds" << endl << endl;

            cout << "----------------------------------------------------------" << endl;

            cout << "Quick Average Case: " << endl;
            randomArr(arr, size);
            clock_t start14 = clock();
            quickSort(arr, 0, size, 2);
            clock_t end14 = clock();
            cout << "\nTime taken to sort:\t\t\t" << (double)(end14 - start14) * 1000.0 / CLOCKS_PER_SEC << " milliseconds" << endl << endl;

            cout << "----------------------------------------------------------" << endl;

            cout << "Quick Worst Case: " << endl;
            reverseArr(arr, size);
            clock_t start15 = clock();
            quickSort(arr, 0, size, 2);
            clock_t end15 = clock();
            cout << "\nTime taken to sort:\t\t\t" << (double)(end15 - start15) * 1000.0 / CLOCKS_PER_SEC << " milliseconds" << endl << endl;

            cout << "----------------------------------------------------------" << endl;
            break;
        }
        // 6 Heap ----------------------------------------------------------------------------------------------------------------------------------------------
        case 6:
        {
            cout << "Heap Best Case: " << endl;
            sortedArr(arr, size);
            Heap prioQ1(arr, size, size + 10);
            prioQ1.BuildMaxHeap();
            clock_t start16 = clock();
            prioQ1.AscendingHeapSort();
            clock_t end16 = clock();
            cout << "\nTime taken to sort:\t\t\t" << (double)(end16 - start16) * 1000.0 / CLOCKS_PER_SEC << " milliseconds" << endl << endl;

            cout << "----------------------------------------------------------" << endl;

            cout << "Heap Average Case: " << endl;
            randomArr(arr, size);
            Heap prioQ2(arr, size, size + 10);
            prioQ2.BuildMaxHeap();
            clock_t start17 = clock();
            prioQ2.AscendingHeapSort();
            clock_t end17 = clock();
            cout << "\nTime taken to sort:\t\t\t" << (double)(end17 - start17) * 1000.0 / CLOCKS_PER_SEC << " milliseconds" << endl << endl;

            cout << "----------------------------------------------------------" << endl;

            cout << "Heap Worst Case: " << endl;
            reverseArr(arr, size);
            Heap prioQ3(arr, size, size + 10);
            prioQ3.BuildMaxHeap();
            clock_t start18 = clock();
            prioQ3.AscendingHeapSort();
            clock_t end18 = clock();
            cout << "\nTime taken to sort:\t\t\t" << (double)(end18 - start18) * 1000.0 / CLOCKS_PER_SEC << " milliseconds" << endl << endl;

            cout << "----------------------------------------------------------" << endl;
            break;
        }
        // 7 counting ----------------------------------------------------------------------------------------------------------------------------------------------
        case 7:
        {
            cout << "Counting Best Case: " << endl;
            zeroArr(arr, size);
            clock_t start19 = clock();
            countingSort(arr, size);
            clock_t end19 = clock();
            cout << "\nTime taken to sort:\t\t\t" << (double)(end19 - start19) * 1000.0 / CLOCKS_PER_SEC << " milliseconds" << endl << endl;

            cout << "----------------------------------------------------------" << endl;

            cout << "Counting Average Case: " << endl;
            randomArr(arr, size);
            clock_t start20 = clock();
            countingSort(arr, size);
            clock_t end20 = clock();
            cout << "\nTime taken to sort:\t\t\t" << (double)(end20 - start20) * 1000.0 / CLOCKS_PER_SEC << " milliseconds" << endl << endl;

            cout << "----------------------------------------------------------" << endl;

            cout << "Counting Worst Case: " << endl;
            randomLargeArr(arr, size);
            clock_t start21 = clock();
            countingSort(arr, size);
            clock_t end21 = clock();
            cout << "\nTime taken to sort:\t\t\t" << (double)(end21 - start21) * 1000.0 / CLOCKS_PER_SEC << " milliseconds" << endl << endl;

            cout << "----------------------------------------------------------" << endl;
            break;
        }
        // 8 radix ----------------------------------------------------------------------------------------------------------------------------------------------
        case 8:
        {
            cout << "Radix Best Case: " << endl;
            zeroArr(arr, size);
            clock_t start22 = clock();
            radixSort(arr, size);
            clock_t end22 = clock();
            cout << "\nTime taken to sort:\t\t\t" << (double)(end22 - start22) * 1000.0 / CLOCKS_PER_SEC << " milliseconds" << endl << endl;

            cout << "----------------------------------------------------------" << endl;

            cout << "Radix Average Case: " << endl;
            randomArr(arr, size);
            clock_t start23 = clock();
            radixSort(arr, size);
            clock_t end23 = clock();
            cout << "\nTime taken to sort:\t\t\t" << (double)(end23 - start23) * 1000.0 / CLOCKS_PER_SEC << " milliseconds" << endl << endl;

            cout << "----------------------------------------------------------" << endl;

            cout << "Radix Worst Case: " << endl;
            oneArr(arr, size);
            clock_t start24 = clock();
            radixSort(arr, size);
            clock_t end24 = clock();
            cout << "\nTime taken to sort:\t\t\t" << (double)(end24 - start24) * 1000.0 / CLOCKS_PER_SEC << " milliseconds" << endl << endl;

            cout << "--------------------------------------------------------------------------------------------------------------------------------" << endl;
            break;
        }
    }
    
    return 0;
}