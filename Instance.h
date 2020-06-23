#ifndef INSTANCE_H
#define INSTANCE_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Instance {
    private:
        vector<double> features;
    public:
        Instance() {};
        Instance(string);
        void print();
        int getClassification();                // Returns the classification of an instance
        double getFeature(int);                 // Returns the data of a certain feature
        vector<double> getSubset(vector<int>);  // Returns a vector of the subset of features
        void setFeature(int, double);           // Sets the data of a certain feature
        int numFeatures();                      // Returns the number of features in the instance
};

#endif