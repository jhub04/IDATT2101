#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 50000000

// Function to swap two elements
void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

// Median-of-three to choose a good pivot in sorted/reverse sorted data
int medianOfThree(int arr[], int low, int high) {
  int mid = low + (high - low) / 2;

  // Sort the first, middle, and last elements
  if (arr[mid] < arr[low]) swap(&arr[mid], &arr[low]);
  if (arr[high] < arr[low]) swap(&arr[high], &arr[low]);
  if (arr[high] < arr[mid]) swap(&arr[high], &arr[mid]);

  // Now arr[mid] is the median, so use it as the pivot
  swap(&arr[mid], &arr[high - 1]);  // Move pivot to high-1 for partitioning
  return arr[high - 1];
}

// Partition function with the median-of-three pivot selection
int singlePivotPartition(int arr[], int low, int high) {
  int pivot = medianOfThree(arr, low, high);
  int i = low;
  int j = high - 1;  // We already know arr[high - 1] is the pivot

  while (1) {
    while (arr[++i] < pivot);  // Find item on left to swap
    while (arr[--j] > pivot);  // Find item on right to swap

    if (i < j) {
      swap(&arr[i], &arr[j]);
    } else {
      break;
    }
  }

  swap(&arr[i], &arr[high - 1]);  // Restore pivot
  return i;  // Return the pivot index
}

// QuickSort using single pivot with median-of-three pivot selection
void singlePivotQuickSort(int arr[], int low, int high) {
  if (low + 10 <= high) {  // If subarray size > 10, apply QuickSort
    int pivotIndex = singlePivotPartition(arr, low, high);

    singlePivotQuickSort(arr, low, pivotIndex - 1);  // Left partition
    singlePivotQuickSort(arr, pivotIndex + 1, high);  // Right partition
  } else {
    // Use insertion sort for small subarrays (size <= 10)
    for (int i = low + 1; i <= high; i++) {
      int temp = arr[i];
      int j;
      for (j = i; j > low && arr[j - 1] > temp; j--) {
        arr[j] = arr[j - 1];
      }
      arr[j] = temp;
    }
  }
}

// Partition function for dual-pivot QuickSort
int dualPivotPartition(int* arr, int low, int high, int* lp) {
  // Swap for better partitioning
  swap(&arr[low], &arr[low+(high-low)/3]);
  swap(&arr[high], &arr[high-(high-low)/3]);

  if (arr[low] > arr[high])
    swap(&arr[low], &arr[high]);

  int j = low + 1;
  int g = high - 1, k = low + 1, p = arr[low], q = arr[high];
  while (k <= g) {
    if (arr[k] < p) {
      swap(&arr[k], &arr[j]);
      j++;
    } else if (arr[k] >= q) {
      while (arr[g] > q && k < g)
        g--;
      swap(&arr[k], &arr[g]);
      g--;
      if (arr[k] < p) {
        swap(&arr[k], &arr[j]);
        j++;
      }
    }
    k++;
  }
  j--;
  g++;

  swap(&arr[low], &arr[j]);
  swap(&arr[high], &arr[g]);

  *lp = j;  // Return left pivot index
  return g; // Return right pivot index
}

// Dual-Pivot QuickSort function
void dualPivotQuickSort(int* arr, int low, int high) {
  if (low < high) {
    int lp, rp;
    rp = dualPivotPartition(arr, low, high, &lp);
    dualPivotQuickSort(arr, low, lp - 1);
    if (arr[lp] != arr[rp])
      dualPivotQuickSort(arr, lp + 1, rp - 1);
    dualPivotQuickSort(arr, rp + 1, high);
  }
}

// Function to calculate checksum of an array
long long calculateChecksum(int* arr, int size) {
  long long sum = 0;
  for (int i = 0; i < size; i++) {
    sum += arr[i];
  }
  return sum;
}

// Function to check if the array is sorted correctly
int isSorted(int* arr, int size) {
  for (int i = 0; i < size - 1; i++) {
    if (arr[i] > arr[i + 1]) {
      return 0;  // Array is not sorted
    }
  }
  return 1;  // Array is sorted
}

// Function to print if a test passed or failed
void printTestResult(const char* testName, int result) {
  if (result) {
    printf("%s: Passed\n", testName);
  } else {
    printf("%s: Failed\n", testName);
  }
}

// Function to fill the array with random data
void fillRandomData(int* arr, int size) {
  for (int i = 0; i < size; i++) {
    arr[i] = rand();
  }
}

// Function to fill the array with duplicate data
void fillDuplicateData(int* arr, int size) {
  int duplicateValue = 1;  // Constant value for duplicates
  for (int i = 0; i < size; i += 2) {
    arr[i] = duplicateValue;       // Every even index gets the duplicate value
    if (i + 1 < size) {
      arr[i + 1] = rand();  // Every odd index gets a random value
    }
  }
}

// Function to fill the array with sorted data
void fillSortedData(int* arr, int size) {
  for (int i = 0; i < size; i++) {
    arr[i] = i;
  }
}

// Function to fill the array with reverse sorted data
void fillReverseSortedData(int* arr, int size) {
  for (int i = 0; i < size; i++) {
    arr[i] = size - i;
  }
}

// Function to measure the time taken by a sorting function
void measureTime(void (*sortFunc)(int*, int, int), int* arr, int size, const char* desc) {
  printf("\n%s:\n", desc);

  long long checksumBefore = calculateChecksum(arr, size);

  clock_t start = clock();
  sortFunc(arr, 0, size - 1);
  clock_t end = clock();

  long long checksumAfter = calculateChecksum(arr, size);
  double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;

  // Print sorting time
  printf("Time: %f seconds\n", elapsed_time);

  // Run tests
  printTestResult("Checksum Test", checksumBefore == checksumAfter);
  printTestResult("Sorted Order Test", isSorted(arr, size));
}

int main() {
  int* arr = (int*)malloc(ARRAY_SIZE * sizeof(int));
  if (arr == NULL) {
    printf("Memory allocation failed\n");
    return -1;
  }

  // Random Data
  fillRandomData(arr, ARRAY_SIZE);
  measureTime(singlePivotQuickSort, arr, ARRAY_SIZE, "Single-Pivot QuickSort on Random Data");
  fillRandomData(arr, ARRAY_SIZE);
  measureTime(dualPivotQuickSort, arr, ARRAY_SIZE, "Dual-Pivot QuickSort on Random Data");

  // Duplicate Data
  fillDuplicateData(arr, ARRAY_SIZE);
  measureTime(singlePivotQuickSort, arr, ARRAY_SIZE, "Single-Pivot QuickSort on Duplicate Data");
  fillDuplicateData(arr, ARRAY_SIZE);
  measureTime(dualPivotQuickSort, arr, ARRAY_SIZE, "Dual-Pivot QuickSort on Duplicate Data");

  // Sorted Data
  fillSortedData(arr, ARRAY_SIZE);
  measureTime(singlePivotQuickSort, arr, ARRAY_SIZE, "Single-Pivot QuickSort on Sorted Data");
  fillSortedData(arr, ARRAY_SIZE);
  measureTime(dualPivotQuickSort, arr, ARRAY_SIZE, "Dual-Pivot QuickSort on Sorted Data");

  // Reverse-Sorted Data
  fillReverseSortedData(arr, ARRAY_SIZE);
  measureTime(singlePivotQuickSort, arr, ARRAY_SIZE, "Single-Pivot QuickSort on Reverse-Sorted Data");
  fillReverseSortedData(arr, ARRAY_SIZE);
  measureTime(dualPivotQuickSort, arr, ARRAY_SIZE, "Dual-Pivot QuickSort on Reverse-Sorted Data");

  free(arr);
  return 0;
}


