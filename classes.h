#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>

class Employee{

public:
    int id, total_calls;
    int postitive_calls, negative_calls;
    int points;
    void calculatePoints();
    explicit Employee(int _id=-1, int _tc=-1, int _pc=-1, int _nc=-1);
    ~Employee();
};

class MaxHeap{

public:
    int length;
    int heapSize;
    char mode;
    Employee *employees;
    explicit MaxHeap(int numberOfEmployees, char _mode);
    ~MaxHeap();

    void MaxHeapify(int i);
    void BuildMaxHeap();
    void HeapSortAsc();
    Employee ExtractMax();
    Employee PeekMax();
    void HeapIncreaseKey(int i);
    void Insert(Employee &key);
};

class MinHeap{

public:
    int length;
    int heapSize;
    char mode;
    Employee *employees;
    explicit MinHeap(int numberOfEmployees, char _mode);
    ~MinHeap();

    void MinHeapify(int i);
    void BuildMinHeap();
    void HeapSortDesc();
    Employee ExtractMin();
    Employee PeekMin();
    void HeapIncreaseKey(int i);
    void Insert(Employee &key);
};

int Left(int i);
int Right(int i);
int Parent(int i);

#endif //CLASSES_H
