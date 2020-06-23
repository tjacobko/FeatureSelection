# FeatureSelection
## Description
This program utilizes feature selection to determine the best features in a data set for classifying objects.

### Project Design
The project design includes a class called DataSet, a class called Instance, and a user interface. The DataSet class inherits the Instance class, and creates a vector of Instances that will represent our entire data set. Each instance has its own classification and features, which DataSet uses to perform nearest neighbor classifications, leave-one-out validations, forward selections, and backward eliminations. Through the interface, the user enters the data file they would like to assess, and chooses either the forward selection algorithm or the backward elimination algorithm.

### Normalization
Since the program executes nearest neighbor classification, it is necessary to normalize the data. The normalization method of choice for this project is Z-Score Normalization, which follows the formula:
value - 
where value is the data value to be normalized,  is the mean of the feature, and  is the standard deviation of the feature.
Z-Score Normalization was chosen since it is able to handle outliers, which I believe is useful for large data sets, where outliers are more difficult to identify at a glance. Also, since most of the data is around the same range, I found it unnecessary to guarantee the normalized data have the exact same scale (as opposed to Min-max Normalization).

### Challenges
The most difficult challenge was dealing with large amounts of data with many features (i.e. the cs_170_large data files). With the large data files, the leave-one-out validator and nearest neighbor classifier struggled immensely in time performance, since all 1000 instances need go through the validator multiple times and many large feature subsets go through the classifier. This is especially noticeable when using backwards elimination, where the feature subset starts at 40 features, which makes each level very taxing. Possible ways to remedy this issue are to implement sorting and indexing features or data edit by throwing away some data; however, this was not explored in my project.

#### Feature Selection Algorithms
The project includes forward selection and the backward elimination algorithms. Both algorithms utilize the leave-one-out validator (which uses the nearest neighbor classifier to classify each instance) to judge the accuracy of various feature subsets. The forward selection algorithm starts with an empty set and adds one feature at a time, choosing the subset with the best accuracy, and repeating. The backward elimination algorithm starts with all features in the subset and deletes one feature at a time, choosing the subset with the best accuracy, and repeating. Both algorithms will give a warning when the best accuracy begins to decrease, and the algorithms will stop if accuracy decreases further (in case of local maxima). This is to prevent from going through every possible subset, which could be extremely inefficient.
