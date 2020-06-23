#include "Instance.h"

// Creates a new instance of data with classification and features e.g. f1, f2, f3, ...
Instance::Instance(string line) {
    double feature;

    istringstream iss(line);
    while (iss >> feature) {
        this->features.push_back(feature);
    }
}

void Instance::print() {
    for (int i = 0; i < this->features.size(); i++) {
        cout << this->features.at(i) << " ";
    }
    cout << endl;
}

// Returns the classification of the instance (1 or 2)
int Instance::getClassification() {
    if (!this->features.empty()) {
        return this->features.at(0);
    }
    else {
        cout << "Error. Instance has no classification or features." << endl;
        return -1;
    }
}

// Returns the data of a certain feature
double Instance::getFeature(int index) {
    return this->features.at(index);
}

/* Returns a vector of the subset of features
    Does not include the classification */
vector<double> Instance::getSubset(vector<int> subset) {
    vector<double> instanceFeatures;
    for (int i = 0; i < subset.size(); i++) {
        instanceFeatures.push_back(getFeature(subset.at(i)));
    }
    
    return instanceFeatures;
}

// Changes the data of a ceartain feature
void Instance::setFeature(int index, double newData) {
    this->features.at(index) = newData;
}

/* Returns the number of instances
    Does NOT include the classification (element 0 in the vector) */
int Instance::numFeatures() {
    return this->features.size() - 1;
}