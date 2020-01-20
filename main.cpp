#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cmath>
#include "classes.h"

using namespace std;

// Get length of file
int getLength(string FILENAME);

void ReadDayOne(MaxHeap &heap1, MaxHeap &heap2, string FILENAME, int length);
void printDay(MaxHeap &pHeap, MaxHeap &cHeap, int dayNo);
void printLastDay(MaxHeap &pointsHeap, MaxHeap &callsHeap);

int main() {

    /*      Part1       */

    // Read Day 1
    string filename = "day1.csv";
    int length = getLength(filename);
    MaxHeap pointsHeap(length, 'p');
    MaxHeap callsHeap(length, 'c');
    ReadDayOne(pointsHeap, callsHeap, filename, length);

    pointsHeap.BuildMaxHeap();
    callsHeap.BuildMaxHeap();
    printDay(pointsHeap, callsHeap, 1);

    // Read Day 2-10
    fstream fs;
    int i1, i2;
    bool found, found1, found2;
    for (int i = 2; i < 11; ++i) {
        filename = "day" + to_string(i) + ".csv";
        length = getLength(filename);
        fs.open(filename, ios::in);
        if (!fs.is_open()) {
            cout << "File: " << filename << " cannot be opened" << endl;
        }
        string tmp;
        for (int j = 1; j <= length; ++j) {
            tmp = "";
            getline(fs, tmp, ',');
            int currID = stoi(tmp);
            i1 = 1;
            i2 = 1;
            found = false, found1 = false, found2 = false;
            for (i1; i1 <= pointsHeap.length; i1++) {
                if (pointsHeap.employees[i1].id == currID) {
                    found1 = true;
                    break;
                }
            }
            for (i2; i2 <= callsHeap.length; i2++) {
                if (callsHeap.employees[i2].id == currID) {
                    found2 = true;
                    break;
                }
            }
            if (found1 && found2) {
                found = true;
            }
            else if (found1 || found2) {
                cout << "Error:\nFound1 is: " << found1 << "\tfor i1: " << i1;
                cout << "\nFound2 is: " << found2 << "\tfor i1: " << i2 << endl;
                return 0;
            }
            if (found) {
                // Continue reading the file
                tmp = "";
                getline(fs, tmp, ',');
                pointsHeap.employees[i1].total_calls += stoi(tmp);
                callsHeap.employees[i2].total_calls += stoi(tmp);

                tmp = "";
                getline(fs, tmp, ',');
                pointsHeap.employees[i1].postitive_calls += stoi(tmp);
                callsHeap.employees[i2].postitive_calls += stoi(tmp);

                tmp = "";
                getline(fs, tmp);
                pointsHeap.employees[i1].negative_calls += stoi(tmp);
                callsHeap.employees[i2].negative_calls += stoi(tmp);

                pointsHeap.employees[i1].calculatePoints();
                pointsHeap.HeapIncreaseKey(i1);

                callsHeap.employees[i2].calculatePoints();
                callsHeap.HeapIncreaseKey(i2);
            }
            else {
                // Insert new element
                Employee e1, e2;
                e1.id = currID;
                e2.id = currID;
                tmp = "";
                getline(fs, tmp, ',');
                e1.total_calls = stoi(tmp);
                e2.total_calls = stoi(tmp);
                tmp = "";
                getline(fs, tmp, ',');
                e1.postitive_calls = stoi(tmp);
                e2.postitive_calls = stoi(tmp);
                tmp = "";
                getline(fs, tmp);
                e1.negative_calls = stoi(tmp);
                e2.negative_calls = stoi(tmp);
                e1.calculatePoints();
                e2.calculatePoints();
                pointsHeap.Insert(e1);
                callsHeap.Insert(e2);
            }
        }

        if(i == 10){
            printLastDay(pointsHeap, callsHeap);
        }
        else {
            printDay(pointsHeap, callsHeap, i);
        }
        fs.close();
    }



    /*      Part 2      */

    int length2 = getLength("numbers.csv");
    MaxHeap numbers(length2, 'c');
    fs.open("numbers.csv", ios::in);
    if (!fs.is_open()) {
        cout << "File: numbers.csv cannot be opened" << endl;
    }

    int x;
    for (int i = 1; i <= length2; i++) {
        fs >> x;
        numbers.employees[i].total_calls = x;
        numbers.length += 1;
        numbers.heapSize += 1;
    }
    fs.close();

    fs.open("output.csv", ios::out);
    numbers.BuildMaxHeap();
    numbers.heapSize = numbers.length;

    Employee e;
    clock_t t;
    t = clock();

    for (int i = 1; i <= length2; i++) {
        e = numbers.ExtractMax();
        numbers.MaxHeapify(1);
        fs << e.total_calls << endl;
        if(i % 200000 == 0){
            cout << "The height of the heap after extracting: ";
            cout << floor(log2(numbers.length)) << endl;
            cout << "The running time for the height: ";
            cout << (float)(clock() - t) / (float)CLOCKS_PER_SEC;
            cout << endl << endl;
        }
    }
    fs.close();

    return 0;
}

int getLength(string FILENAME){
    fstream fs;
    fs.open(FILENAME, ios::in);
    if (!fs.is_open()) {
        cout<<"File: "<<FILENAME<<" cannot be opened" << endl;
    }
    int i = 0;
    string temp;
    while(fs.good()){
        getline(fs, temp);
        if(fs.eof()) break;
        i++;
    }
    //cout << "File length is: " << i << endl;
    fs.close();
    return i;
}

void ReadDayOne(MaxHeap &pHeap, MaxHeap &cHeap, string FILENAME, int length) {
    fstream fs;
    fs.open(FILENAME, ios::in);
    string tmp;
    for (int i = 1; i <= length; i++) {
        tmp = "";
        getline(fs, tmp, ',');
        pHeap.employees[i].id = stoi(tmp);
        cHeap.employees[i].id = stoi(tmp);
        tmp = "";
        getline(fs, tmp, ',');
        pHeap.employees[i].total_calls = stoi(tmp);
        cHeap.employees[i].total_calls = stoi(tmp);
        tmp = "";
        getline(fs, tmp, ',');
        pHeap.employees[i].postitive_calls = stoi(tmp);
        cHeap.employees[i].postitive_calls = stoi(tmp);
        tmp = "";
        getline(fs, tmp);
        pHeap.employees[i].negative_calls = stoi(tmp);
        cHeap.employees[i].negative_calls = stoi(tmp);
        pHeap.employees[i].calculatePoints();
        cHeap.employees[i].calculatePoints();
        pHeap.length += 1;
        pHeap.heapSize += 1;
        cHeap.length += 1;
        cHeap.heapSize += 1;
    }
    fs.close();
}

void printDay(MaxHeap &pHeap, MaxHeap &cHeap, int dayNo) {

    Employee max1, max2, max3;
    max1 = pHeap.ExtractMax();
    max2 = pHeap.ExtractMax();
    max3 = pHeap.ExtractMax();
    cout << endl << endl << "After Day-" << dayNo << endl;
    cout << "Best Performance: " << max1.id << ", ";
    cout << max2.id <<", "<< max3.id <<endl;
    pHeap.Insert(max1);
    pHeap.Insert(max2);
    pHeap.Insert(max3);

    max1 = cHeap.ExtractMax();
    max2 = cHeap.ExtractMax();
    max3 = cHeap.ExtractMax();
    cout << "Maximum Calls: " << max1.id << ", ";
    cout << max2.id <<", "<< max3.id <<endl;
    cHeap.Insert(max1);
    cHeap.Insert(max2);
    cHeap.Insert(max3);
}

void printLastDay(MaxHeap &pointsHeap, MaxHeap &callsHeap) {

    MinHeap h1(pointsHeap.length, 'p');
    MinHeap h2(callsHeap.length, 'c');
    int length = pointsHeap.length;
    for (int i = 1; i <= length; ++i) {
        h1.employees[i] = pointsHeap.employees[i];
        h2.employees[i] = callsHeap.employees[i];
        h1.length += 1;
        h1.heapSize += 1;
        h2.length += 1;
        h2.heapSize += 1;
    }

    h1.BuildMinHeap();
    h2.BuildMinHeap();

    Employee max1, max2, max3, min1, min2, min3;

    max1 = pointsHeap.ExtractMax();
    max2 = pointsHeap.ExtractMax();
    max3 = pointsHeap.ExtractMax();
    min1 = h1.ExtractMin();
    min2 = h1.ExtractMin();
    min3 = h1.ExtractMin();
    cout << endl << endl << "After Day-10" << endl;
    cout << "Best Performance: " << max1.id << ", ";
    cout << max2.id <<", "<< max3.id <<endl;
    cout << "Worst Performance: " << min1.id << ", ";
    cout << min2.id <<", "<< min3.id <<endl;
    pointsHeap.Insert(max1);
    pointsHeap.Insert(max2);
    pointsHeap.Insert(max3);
    h1.Insert(min1);
    h1.Insert(min2);
    h1.Insert(min3);

    max1 = callsHeap.ExtractMax();
    max2 = callsHeap.ExtractMax();
    max3 = callsHeap.ExtractMax();
    min1 = h2.ExtractMin();
    min2 = h2.ExtractMin();
    min3 = h2.ExtractMin();
    cout << "Maximum Calls: " << max1.id << ", ";
    cout << max2.id <<", "<< max3.id << endl;
    cout << "Minimum Calls: " << min1.id << ", ";
    cout << min2.id <<", "<< min3.id << endl << endl;
    callsHeap.Insert(max1);
    callsHeap.Insert(max2);
    callsHeap.Insert(max3);
    h2.Insert(min1);
    h2.Insert(min2);
    h2.Insert(min3);

}

