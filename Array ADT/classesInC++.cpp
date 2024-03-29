#include <iostream>
#include <stdio.h>

class Array {
private:
    int *A;
    int size;
    int length;
    void Swap(int *x, int *y); // Private because it is only used by other functions in the class
public:
    Array() { // Default Constructor
        size = 10;
        length = 0;
        A = new int[size];
    }
    
    Array(int sz) { // Parameterized Constructor
        size = sz;
        length = 0;
        A = new int[size];
    }
    ~Array () { // Destructor
        delete []A;
    }
    
    // Prototypes
    void Display();
    void Append(int x);
    void Insert(int index, int x);
    int Delete(int index);
    int LinearSearch(int key);
    int BinarySearch(int key);
    int RecBinarySearch(int a[], int l, int h, int key);
    int Get(int index);
    void Set(int index, int x);
    int Max();
    int Min();
    int Sum();
    float Avg();
    void Reverse();
    void Reverse2();
    void InsertSort(int x);
    bool isSorted();
    void Rearrange();
    Array* Merge(Array arr2);
    Array* Union(Array arr2);
    Array* Intersection(Array arr2);
    Array* Difference(Array arr2);
};

void Array::Display() {
    printf("\nElements are: ");
    for (int i = 0; i < length; i++) { printf("%d ", A[i]);}
    printf("\n");
}


void Array::Append(int x) {
    // Check to make sure that there is space in the array for new element
    if (length < size) {
        // Insert x at index 'length'. Then increment the length
        A[length++] = x;
    }
}

void Array::Insert(int index, int x) {
    // Check to make sure that the index is valid
    if (index >= 0 && index <= length) {
        for (int i = length; i > index; i--) { A[i] = A[i-1]; }
        A[index] = x;
        length++; // Update the length of the array
    }
}

int Array::Delete(int index) {
    int x = 0; // We need to return the deleted element
    // Check to make sure that the index is valid
    if (index >= 0 && index <= length-1) {
        x = A[index];
        for (int i = index; i < length-1; i++) {
            A[i] = A[i+1];
        }
        length--; // Update the length of the array
        return x;
    }
    return 0; // Returns 0 if index is invalid
}

int Array::LinearSearch(int key) {
    
    for (int i = 0; i < length; i++) {
        if (key == A[i]) return i;
    }
    return -1;
}

// BINRAY SEARCH - ITERATIVE
int Array::BinarySearch(int key) {
    int l,mid,h;
    l = 0;
    h = length - 1;
    while (l <= h) {
        mid = (l+h)/2;
        if (key == A[mid]) { return mid; }
        else if (key < A[mid]) { h = mid-1;}
        else { l = mid+1;}
    }
    
    return -1;
}

// BINRAY SEARCH - RECURSIVE
int Array::RecBinarySearch(int a[], int l, int h, int key) {
    int mid;
    if (l <= h) {
        mid = (l+h)/2;
        if (key == a[mid]) { return mid; }
        else if (key < a[mid]) { return RecBinarySearch(a, l, mid-1, key); }
        else { return RecBinarySearch(a, mid+1, h, key); }
    }
    return -1;
}

int Array::Get(int index) {
    // Check that the 'index' is valid
    if (index >= 0 && index < length)
        return A[index];
    return -1; // If invalid 'index', return -1
}

// SET -- Replaces an existing element in the array with a new element 'x'
void Array::Set(int index, int x) {
    // Check that the 'index' is valid
    if (index >= 0 && index < length)
        A[index] = x;
}

// MAX - Given an array (either unsorted or sorted), finds the max element
int Array::Max() {
    int max = A[0];
    for (int i = 1; i < length; i++) {
        if (A[i] > max)
            max = A[i];
    }
    return max;
}

// MIN - Given an array (either unsorted or sorted), finds the min element
int Array::Min() {
    int min = A[0];
    for (int i = 1; i < length; i++) {
        if (A[i] < min)
            min = A[i];
    }
    return min;
}

// SUM - Given an array, returns the sum of all the elements
int Array::Sum() {
    int s = 0;
    for (int i = 0; i < length; i++)
        s += A[i];
    return s;
}

// AVG - Given an array, returns the average of all the elements
float Array::Avg() {
    return (float) Sum()/length; // Typecast the result as float
}

// REVERSE (METHOD 1) - Reversing by using an Auxiliary Array
void Array::Reverse() {
    // Creating an Auxiliary Array 'B' in the Heap
    int *B = (int *)malloc(length*sizeof(int));
    // Copy the elements of 'A' to 'B' in REVERSE order
    for (int i = length-1, j = 0; i >= 0; i--, j++)
        B[j] = A[i];
    // Copy the elements of 'B' to 'A' in SAME order
    for (int i = 0; i < length; i++)
        A[i] = B[i];
    free(B); // To avoid memory leak
}

// SWAP function
void Array::Swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void Array::Reverse2() {
    // Swapping stops once i >= j
    for (int i = 0, j = length-1; i<j; i++, j--)
        Swap(&A[i],&A[j]);
}

// INSERT SORT - Given a sorted array and an element 'x'
void Array::InsertSort(int x) {
    int i = length-1;
    // Check that there is free space in the array
    if (length == size)
        return;
    // Shift all the elements which are larger than 'x' to the right
    // Also ensure that 'i' will not go to negative
    while (i >= 0 && A[i] > x) {
        A[i+1] = A[i];
        i--;
    }
    A[i+1] = x;
    length++; // Increment the length of the array
}

bool Array::isSorted() {
    // i stops before the last element in the list
    for (int i = 0; i < length-1; i++) {
        if (A[i] > A[i+1])
            return false;
    }
    return true;
}

void Array::Rearrange() {
    int i = 0, j = length-1;
    
    while (i < j) {
        while (A[i] < 0) i++;
        while (A[j] >= 0) j--;
        if (i < j)
            Swap(&A[i], &A[j]);
    }
}

// MERGE - Merges two SORTED arrays
Array* Array::Merge(Array arr2) {
    int i = 0, j = 0, k = 0;
    Array *arr3 = new Array(length+arr2.length);
    
    while (i < length && j < arr2.length) {
        if (A[i] < arr2.A[j])
            arr3->A[k++] = A[i++];
        else
            arr3->A[k++] = arr2.A[j++];
    }
    for (; i < length; i++)
        arr3->A[k++] = A[i];
    
    for (; j < arr2.length; j++)
        arr3->A[k++] = arr2.A[j];
    
    arr3->length = length + arr2.length;
    arr3->size = 10;
    return arr3;
}

// UNION Set operation for SORTED sets
Array* Array::Union(Array arr2) {
    int i = 0, j = 0, k = 0;
    Array *arr3 = new Array(length+arr2.length);
    
    while (i < length && j < arr2.length) {
        if (A[i] < arr2.A[j])
            arr3->A[k++] = A[i++];
        else if (A[i] > arr2.A[j])
            arr3->A[k++] = arr2.A[j++];
        // If A[i] == A[j], we only copy one of them to arr3
        else {
            arr3->A[k++] = A[i++];
            j++;
        }
    }
    for (; i < length; i++)
        arr3->A[k++] = A[i];
    
    for (; j < arr2.length; j++)
        arr3->A[k++] = arr2.A[j];
    
    arr3->length = k;
    arr3->size = 10;
    return arr3;
}


Array* Array::Intersection(Array arr2) {
    int i = 0, j = 0, k = 0;
    Array *arr3 = new Array(length+arr2.length);
    
    while (i < length && j < arr2.length) {
        if (A[i] < arr2.A[j])
            i++;
        else if (A[i] > arr2.A[j])
            j++;
        // If A[i] == A[j], we only copy one of them to arr3
        else {
            arr3->A[k++] = A[i++];
            j++;
        }
    }
    
    arr3->length = k;
    arr3->size = 10;
    return arr3;
}


Array* Array::Difference(Array arr2) {
    int i = 0, j = 0, k = 0;
    Array *arr3 = new Array(length+arr2.length);
    
    while (i < length && j < arr2.length) {
        if (A[i] < arr2.A[j])
            arr3->A[k++] = A[i++];
        else if (A[i] > arr2.A[j])
            j++;
        else {
            i++;
            j++;
        }
    }
    for (; i < length; i++)
        arr3->A[k++] = A[i];
    
    arr3->length = k;
    arr3->size = 10;
    return arr3;
}

int main(){
    
    Array* arr1;
    int ch, x, index, sz;
    
    printf("Enter the Size of Array: ");
    scanf("%d", &sz);
    arr1 = new Array(sz);
    
    do {
        printf("MENU\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. Sum\n");
        printf("5. Display\n");
        printf("6. Exit\n");
        
        printf("Enter your choice: ");
        scanf("%d", &ch);
        
        switch(ch) {
            case 1: printf("Enter an element and index: ");
                scanf("%d%d", &x, &index);
                arr1->Insert(index, x);
                break;
            case 2: printf("Enter index: ");
                scanf("%d", &index);
                x = arr1->Delete(index);
                printf("Deleted element is %d\n", x);
                break;
            case 3: printf("Enter element to search: ");
                scanf("%d", &x);
                index = arr1->LinearSearch(x);
                printf("Element index is %d\n", index);
                break;
            case 4: printf("Sum is %d\n", arr1->Sum());
                break;
            case 5: arr1->Display();
                break;
                
        }
    } while(ch < 6);

    return 0;
}
