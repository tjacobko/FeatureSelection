#include "DataSet.h"

Dataset::Dataset(string userFile) {
    ifstream input;
    input.open(userFile);
    
    if (input.is_open()) {
        string line;
        while (getline(input, line)) {
            Instance* newInstance = new Instance(line);
            this->instances.push_back(newInstance);
        }
        
        cout << "This dataset has " << this->instances.at(0)->numFeatures() << " features (not including the class attribute), with "
        << this->instances.size() << " instances." << endl << endl;
    }
    else {
        cout << "Error opening file" << endl;
    }
    
    input.close();
}

// Normalizes the data using z-score normalization
void Dataset::normalize() {
    int numFeatures = this->instances.at(0)->numFeatures();
    int numInstances = this->instances.size();
    double mean;
    double std;
    double sum;
    double norm;
    
    for (int i = 1; i <= numFeatures; i++) {
        mean = 0;
        std = 0;
        for (int j = 0; j < numInstances; j++) {            // gets the mean of the feature
            this->instances.at(j)->getFeature(i);
            mean = mean + this->instances.at(j)->getFeature(i);
        }
        mean = mean / numInstances;
        
        sum = 0;
        for (int k = 0; k < numInstances; k++) {            // gets the std deviation of the feature
            double x = this->instances.at(k)->getFeature(i);
            sum = sum + pow((x-mean),2);
        }
        std = sqrt(sum / numInstances);
        
        norm = 0;
        for (int l = 0; l < numInstances; l++) {            // normalizes the data using (value-mean)/std
            norm = (this->instances.at(l)->getFeature(i) - mean) / std;
            this->instances.at(l)->setFeature(i,norm);
        }
    }
    cout << "Done!" << endl << endl;
}

/* Takes in instance i and finds its nearest neighbor
    If the nearest neighbor is the correct classification, return true, else false */
bool Dataset::nearestNeighbor(int i, vector<int> subset) {
    Instance* inst = this->instances.at(i);
    int classification = inst->getClassification();
    int neighborClass;
    vector<double> instFeatures = inst->getSubset(subset);
    vector<double> neighbor;
    double min;
    double temp;
    
    for (int j = 0; j < this->instances.size(); j++) {
        if (j != i) {
            neighbor = this->instances.at(j)->getSubset(subset);
            temp = distance(instFeatures, neighbor);
            
            if (j == 0) {
                min = temp;
                neighborClass = this->instances.at(j)->getClassification();
            }
            if (min > temp) {
                min = temp;
                neighborClass = this->instances.at(j)->getClassification();
            }
        }
    }
    
    if (classification == neighborClass) {
        return true;
    }
    else {
        return false;
    }
}

/* Takes in a subset of features, goes through every instance and uses nearestNeighbor
    to see if instance is correctly classified, returns percentage */
double Dataset::validator(vector<int> subset) {
    double trueCount = 0;
    double percentage;
    
    for (int i = 0; i < this->instances.size(); i++) {
        if (nearestNeighbor(i, subset) == true) {
            trueCount++;
        }
    }

    percentage = round((trueCount / this->instances.size()) * 1000);
    percentage = percentage / 10;

    return percentage;
}

// Forward Selection Search Algortithm
void Dataset::forwardSelection() {
    int numFeatures = this->instances.at(0)->numFeatures();
    vector<int> curr_set_features;
    vector<int> best_set_features;
    int feature_to_add;
    double best_accuracy = 0;
    double overall_accuracy = 0;
    bool accuracy_drop = false;
    
    for (int i = 1; i <= numFeatures; i++) {
        cout << "--- On level " << i << " of the search tree ---" << endl;
        feature_to_add = 0;
        best_accuracy = 0;
        
        for (int j = 1; j <= numFeatures; j++) {
            if (exists(curr_set_features, j)) {
                curr_set_features.push_back(j);
                double accuracy = validator(curr_set_features);
                cout << "       Using feature(s) {";
                printSubset(curr_set_features);
                cout << "} accuracy is " << accuracy << "%" << endl;
                
                if (accuracy > best_accuracy) {
                    best_accuracy = accuracy;
                    feature_to_add = j;
                }
                if (best_accuracy > overall_accuracy) {
                    overall_accuracy = best_accuracy;
                    best_set_features = curr_set_features;
                }
                curr_set_features.pop_back();
            }
        }
        
        if (overall_accuracy > best_accuracy) {
            if (accuracy_drop == true) {
                cout << "(Accuracy decreased again. Search will stop.)" << endl << endl;
                break;
            }
            cout << "(Warning, Accuracy has decreased! Continuing search in case of local maxima)" << endl;
            accuracy_drop = true;
            curr_set_features.push_back(feature_to_add);
            cout << "Feature set {";
            printSubset(curr_set_features);
            cout << "} was best, accuracy is " << best_accuracy << "%" << endl << endl;
        }
        else {
            accuracy_drop = false;
            curr_set_features.push_back(feature_to_add);
            cout << "Feature set {";
            printSubset(curr_set_features);
            cout << "} was best, accuracy is " << best_accuracy << "%" << endl << endl;
        }
    }
    cout << "Finished search! The best feature subset is {";
    printSubset(best_set_features);
    cout << "} which has an accuracy of " << overall_accuracy << "%" << endl << endl;
}

// Backward Selection Search Algorithm
void Dataset::backwardElimination() {
    int numFeatures = this->instances.at(0)->numFeatures();
    vector<int> curr_set_features;
    vector<int> best_set_features;
    int feature_to_erase;
    double best_accuracy = 0;
    double overall_accuracy = 0;
    bool accuracy_drop = false;
    
    for (int k = 1; k <= numFeatures; k++) {
        curr_set_features.push_back(k);
    }
    
    cout << "--- On level 0 of the search tree ---" << endl;
    cout << "       Using ALL features {";
    printSubset(curr_set_features);
    cout << "} accuracy is " << validator(curr_set_features) << "%" << endl << endl;
    
    for (int i = 1; i <= numFeatures; i++) {
        cout << "--- On level " << i << " of the search tree ---" << endl;
        feature_to_erase = 0;
        best_accuracy = 0;
        
        for (int j = 0; j < numFeatures-(i-1); j++) {
            int erasedFeature = curr_set_features.at(j);
            curr_set_features.erase(curr_set_features.begin()+j);
            double accuracy = validator(curr_set_features);
            cout << "       Using feature(s) {";
            printSubset(curr_set_features);
            cout << "} accuracy is " << accuracy << "%" << endl;
            
            if (accuracy > best_accuracy) {
                best_accuracy = accuracy;
                feature_to_erase = j;
            }
            if (best_accuracy > overall_accuracy) {
                overall_accuracy = best_accuracy;
                best_set_features = curr_set_features;
            }
            curr_set_features.insert(curr_set_features.begin()+j, erasedFeature);
        }
        
        if (overall_accuracy > best_accuracy) {
            if (accuracy_drop == true) {
                cout << "(Accuracy decreased again. Search will stop.)" << endl << endl;
                break;
            }
            cout << "(Warning, Accuracy has decreased! Continuing search in case of local maxima)" << endl;
            accuracy_drop = true;
            curr_set_features.erase(curr_set_features.begin()+feature_to_erase);
            cout << "Feature set {";
            printSubset(curr_set_features);
            cout << "} was best, accuracy is " << best_accuracy << "%" << endl << endl;
        }
        else {
            accuracy_drop = false;
            curr_set_features.erase(curr_set_features.begin()+feature_to_erase);
            cout << "Feature set {";
            printSubset(curr_set_features);
            cout << "} was best, accuracy is " << best_accuracy << "%" << endl << endl;
        }
    }
    cout << "Finished search! The best feature subset is {";
    printSubset(best_set_features);
    cout << "} which has an accuracy of " << overall_accuracy << "%" << endl << endl;
}

/* Private Helper Fxn, calculates the distance between two instances
 Used in nearestNeighbor fxn */
double Dataset::distance(vector<double> v1, vector<double> v2) {
    double distance = 0;
    
    for (int i = 0; i < v1.size(); i++) {
        distance = distance + pow((v1.at(i)-v2.at(i)), 2);
    }

    return distance;
}

/* Private Helper Fxn
    If i exists in vector v, returns false, else returns true */
bool Dataset::exists(vector<int> v, int num) {
    for (int i = 0; i < v.size(); i++) {
        if (v.at(i) == num) {
            return false;
        }
    }
    return true;
}

/* Private Helper Fxn
    Prints the subset*/
void Dataset::printSubset(vector<int> subset) {
    for (int i = 0; i < subset.size(); i++) {
        if (i != subset.size()-1) {    
            cout << subset.at(i) << ",";
        }
        else {
            cout << subset.at(i);
        }
    }
}