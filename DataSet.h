#ifndef DATASET_H
#define DATASET_H

#include "Instance.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

class Dataset {
    private:
        vector<Instance*> instances;
        
        // Private helper functions
        double distance(vector<double>, vector<double>);
        bool exists(vector<int>, int);
        void printSubset(vector<int>);
    public:
        Dataset() {};
        Dataset(string);
        void normalize();
        bool nearestNeighbor(int, vector<int>);
        double validator(vector<int>);
        void forwardSelection();
        void backwardElimination();
};

#endif