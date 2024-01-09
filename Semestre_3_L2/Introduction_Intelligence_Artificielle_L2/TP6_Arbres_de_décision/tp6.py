
### Import 
import numpy as np
import pandas as pd
from sklearn.metrics import confusion_matrix
from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier
from sklearn.metrics import accuracy_score
from sklearn.metrics import classification_report

# Load Dataset
def importData():
    dataNames = ['Class Name', 'Left-Weight', 'Left-Distance', 'Right-Weight', 'Right-Distance']
    
    ### Link dataset : https://archive.ics.uci.edu/ml/machine-learning-databases/balance-scale/

    # data = pd.read_csv('https://archive.ics.uci.edu/ml/machine-learning-'+
    #     'databases/balance-scale/balance-scale.data', 
    #     sep= ',', header = None)
    data = pd.read_csv("./dataset/balance-scale.data", header=None, names=dataNames)

    # Printing the dataset shape
    print ("Dataset Length: ", len(data))
    print ("Dataset Shape: ", data.shape)
	
    # Printing the dataset obseravtions
    print ("Dataset: \n", data.head())
    return data


# Function to split the dataset
def splitDataset(data):

	# Separating the target variable
	X = data.values[:, 1:5]
	Y = data.values[:, 0]

	# Splitting the dataset into train and test
	trainingX, testX, trainingY, testY = train_test_split(X, Y, test_size = 0.3, random_state = 100)
	
	return X, Y, trainingX, testX, trainingY, testY


# Function to perform training with giniIndex.
def trainingGini(trainingX : list, testX : list, trainingY : list):

	# Creating the classifier object
	clf_Gini = DecisionTreeClassifier(criterion = "gini",
			random_state = 100, max_depth=3, min_samples_leaf=5)

	# Performing training
	clf_Gini.fit(trainingX, trainingY)
	return clf_Gini
	

# Function to perform training with entropy (Shannon).
def trainningEntropy(trainingX : list, testX : list, trainingY : list):

	# Decision tree with entropy
	clf_Entropy = DecisionTreeClassifier(
			criterion = "entropy", random_state = 100,
			max_depth = 3, min_samples_leaf = 5)

	# Performing training
	clf_Entropy.fit(trainingX, trainingY)
	return clf_Entropy


# Function to make predictions
def prediction(testObject, classififObject):

	# Predicton on test with giniIndex
	predicObj = classififObject.predict(testObject)
	print("Predicted values: ")
	print(predicObj)
	return predicObj
	

# Function to calculate accuracy
def calculAccuracy(testObj, predicObj):
	
	print("\nConfusion Matrix: ", confusion_matrix(testObj, predicObj))
	
	print ("\nAccuracy : ", accuracy_score(testObj, predicObj)*100)
	
	print("\nReport : ", classification_report(testObj, predicObj))



# Main function
def main():
	
	# Building Phase
	data = importData()
	X, Y, trainingX, testX, trainingY, testY = splitDataset(data)
	clf_Gini = trainingGini(trainingX, testX, trainingY)
	clf_Entropy = trainningEntropy(trainingX, testX, trainingY)
	
	# Operational Phase
	print("\n\nResults Using Gini Index:")
	
	# Prediction using Gini
	predicY_Gini = prediction(testX, clf_Gini)
	calculAccuracy(testY, predicY_Gini)
	
	print("\n\nResults Using Entropy (Shannon):")
	# Prediction using Entropy Shannon
	predicY_Entropy = prediction(testX, clf_Entropy)
	calculAccuracy(testY, predicY_Entropy)
	
	
# Calling main function
if __name__=="__main__":
	main()
