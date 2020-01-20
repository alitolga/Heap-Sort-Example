#include "classes.h"

int Left(int i) {
    return (2*i);
}

int Right(int i) {
    return (2*i + 1);
}

int Parent(int i) {
    return (i / 2);
}

Employee::Employee(int _id, int _tc, int _pc, int _nc) {
    id = _id;
    total_calls = _tc;
    postitive_calls = _pc;
    negative_calls = _nc;
}

void Employee::calculatePoints() {
    points = 2 * total_calls + postitive_calls - negative_calls;
}

Employee::~Employee() = default;


MaxHeap::MaxHeap(int numberOfEmployees, char _mode) {
    employees = new Employee[numberOfEmployees + 10000];
    length = 0;
    heapSize = 0;
    mode = _mode;
}

MaxHeap::~MaxHeap() {
    if(employees != nullptr){
        delete[] employees;
        //std::cout << "Max Heap destroyed" << std::endl;
    }
    else {
        std::cout << "There are no elements to delete in the max heap" << std::endl;
    }
}

void MaxHeap::MaxHeapify(int i) {
    int l = Left(i);
    int r = Right(i);
    int largest;
    if (mode == 'p') {
        if (l <= heapSize && employees[l].points > employees[i].points) {
            largest = l;
        } else {
            largest = i;
        }
        if (r <= heapSize && employees[r].points > employees[largest].points) {
            largest = r;
        }
        if (largest != i) {
            Employee temp;
            temp = employees[i];
            employees[i] = employees[largest];
            employees[largest] = temp;
            MaxHeapify(largest);
        }
    }
    else if(mode == 'c'){
        if (l <= heapSize && employees[l].total_calls > employees[i].total_calls){
            largest = l;
        } else {
            largest = i;
        }
        if (r <= heapSize && employees[r].total_calls > employees[largest].total_calls){
            largest = r;
        }
        if (largest != i) {
            Employee temp;
            temp = employees[i];
            employees[i] = employees[largest];
            employees[largest] = temp;
            MaxHeapify(largest);
        }
    }
}

void MaxHeap::BuildMaxHeap() {
    heapSize = length;
    int i = heapSize/2;
    for (i; i>=1; i--){
        MaxHeapify(i);
    }
}

void MaxHeap::HeapSortAsc() {
    BuildMaxHeap();
    int i = heapSize;
    Employee temp;
    for (i; i > 1; i--) {
        temp = employees[1];
        employees[1] = employees[i];
        employees[i] = temp;
        heapSize -= 1;
        MaxHeapify(1);
    }
}

Employee MaxHeap::ExtractMax() {
    if (heapSize < 1) {
        printf("Function ExtractMax: Heap underflow\n");
        Employee err;
        return err;
    }
    Employee max;
    max = employees[1];
    employees[1] = employees[heapSize];
    heapSize -= 1;
    length -= 1;
    MaxHeapify(1);
    return max;
}

Employee MaxHeap::PeekMax() {
    return employees[1];
}

void MaxHeap::HeapIncreaseKey(int i) {
    if(mode == 'p') {
        Employee temp;
        while (i > 1 && employees[Parent(i)].points < employees[i].points) {
            temp = employees[i];
            employees[i] = employees[Parent(i)];
            employees[Parent(i)] = temp;
            i = Parent(i);
        }
    }
    else if(mode == 'c'){
        Employee temp;
        while (i > 1 && employees[Parent(i)].total_calls < employees[i].total_calls){
            temp = employees[i];
            employees[i] = employees[Parent(i)];
            employees[Parent(i)] = temp;
            i = Parent(i);
        }
    }
}

void MaxHeap::Insert(Employee &key) {
    heapSize += 1;
    length += 1;
    employees[heapSize] = key;
    HeapIncreaseKey(heapSize);
}


MinHeap::MinHeap(int numberOfEmployees, char _mode) {
    employees = new Employee[numberOfEmployees + 10000];
    length = 0;
    heapSize = 0;
    mode = _mode;
}

MinHeap::~MinHeap() {
    if(employees != nullptr){
        delete[] employees;
        //std::cout << "Min Heap destroyed" << std::endl;
    }
    else {
        std::cout << "There are no elements to delete in the min heap" << std::endl;
    }
}

void MinHeap::MinHeapify(int i) {
    int l = Left(i);
    int r = Right(i);
    int smallest;
    if (mode == 'p') {
        if (l <= heapSize && employees[l].points < employees[i].points) {
            smallest = l;
        } else {
            smallest = i;
        }
        if (r <= heapSize && employees[r].points < employees[smallest].points) {
            smallest = r;
        }
        if (smallest != i) {
            Employee temp;
            temp = employees[i];
            employees[i] = employees[smallest];
            employees[smallest] = temp;
            MinHeapify(smallest);
        }
    }
    else if(mode == 'c'){
        if (l <= heapSize && employees[l].total_calls < employees[i].total_calls){
            smallest = l;
        } else {
            smallest = i;
        }
        if (r <= heapSize && employees[r].total_calls < employees[smallest].total_calls){
            smallest = r;
        }
        if (smallest != i) {
            Employee temp;
            temp = employees[i];
            employees[i] = employees[smallest];
            employees[smallest] = temp;
            MinHeapify(smallest);
        }
    }
}

void MinHeap::BuildMinHeap() {
    heapSize = length;
    int i = heapSize/2;
    for (i; i>=1; i--){
        MinHeapify(i);
    }
}

void MinHeap::HeapSortDesc() {
    BuildMinHeap();
    int i = heapSize;
    Employee temp;
    for (i; i >= 2; i--) {
        temp = employees[1];
        employees[1] = employees[i];
        employees[i] = temp;
        heapSize -= 1;
        MinHeapify(1);
    }
}

Employee MinHeap::ExtractMin() {
    if (heapSize < 1) {
        printf("Function ExtractMin: Heap underflow\n");
        Employee err;
        return err;
    }
    Employee min;
    min = employees[1];
    employees[1] = employees[heapSize];
    heapSize -= 1;
    length -= 1;
    MinHeapify(1);
    return min;
}

Employee MinHeap::PeekMin() {
    return employees[1];
}

void MinHeap::HeapIncreaseKey(int i) {
    MinHeapify(i);
}

void MinHeap::Insert(Employee &key) {
    heapSize += 1;
    length += 1;
    employees[heapSize] = key;
    int i = heapSize;
    if(mode == 'p') {
        Employee temp;
        while (i > 1 && employees[Parent(i)].points > employees[i].points) {
            temp = employees[i];
            employees[i] = employees[Parent(i)];
            employees[Parent(i)] = temp;
            i = Parent(i);
        }
    }
    else if(mode == 'c'){
        Employee temp;
        while (i > 1 && employees[Parent(i)].total_calls > employees[i].total_calls){
            temp = employees[i];
            employees[i] = employees[Parent(i)];
            employees[Parent(i)] = temp;
            i = Parent(i);
        }
    }
}
