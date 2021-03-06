//assignment.h
#ifndef _ASSIGNMENT_H_
#define _ASSIGNMENT_H_

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Test.h"

using namespace std;

class Assignment {
	private:
		//vector assignments
		string assignmentName;
		Test temp;
		vector<Test> classTests;

		//float variable assignments
		float high;
		float low;
		float mean;
		float curve;
		float mode;
		float median;

	public://Pass in vector containing grades to calculate stats
		Assignment(string temp_assignment_name);

		vector<float> grades;

		void add_test(Test temp);
		void calculateHigh();
 		void calculateLow();
 		float calculateMean();
 		void calculateMode();
 		void calculateMedian();
	 	void calculateCurve();
		void printStatistics();
		void printAnswers(string studentName);
		void printGrades();
		void printStudentGrade(string studentName);
		//void displayAll();
		void omitQuestion(int deletedIndex, vector<string> test_key, bool correct);

		//Accessor methods
		float getHigh();
		float getLow();
		float getMean();

		//mutator methods
		void set_vector_index(float numerical_grade);
		void set_name(string name);
};

Assignment::Assignment(string temp_assignment_name) {
	assignmentName = temp_assignment_name;
	vector<Test> assignmentName (0);
}

void Assignment::set_vector_index(float numerical_grade) {
	grades.push_back(numerical_grade);
}

void Assignment::set_name(string name) {
	assignmentName = name;
}

void Assignment::add_test(Test temp) {
	classTests.push_back(temp);
}

//method that calculates the highest value in the vector of grades
void Assignment::calculateHigh() {
	high = 0;
	int size = grades.size();
	//for loops that accesses each grade in the vector and compares it to the current high
	for (int i = 0; i < size; i++) {
		if (grades[i] > high) {
			high = grades[i];
		}
	}
}

//calculates the lowest value in the vector of grades
void Assignment::calculateLow() {
	low = 100;
	int size = grades.size();
	//for loops that accesses every grade in the vector and compares it to the current low
	for (int i = 0; i < size; i++) {
		if (grades[i] < low) {
			low = grades[i];
		}
	}
}

//calculates te average
float Assignment::calculateMean() {
	float sum = 0;
	int size = grades.size();
	for (int i = 0; i < size; i++) {
		sum += grades[i];
	}
	mean = sum / size;
	return mean;
}

//adds a curve to the tests
void Assignment::calculateCurve() {
	float inputAverage;
	string temp = assignmentName;

	cout << "\tPlease enter the desired average for this exam.\n\t";
	cin >> inputAverage;
	
	float realAverage = calculateMean(); //**calculateMean(grades)
	
	if (realAverage < inputAverage) {
		curve = inputAverage - realAverage;
	} else {
		curve = 0;
	}

	int size = grades.size();

	for (int i = 0; i < size; i++) {
		grades[i] += curve;
	}
	assignmentName = temp;
}

//I think .size will give us a bit value of the actual size of the array, not
//the amt of elements, we may need to use *sizeof(grades)/sizeof(grades[0])*
//maybe .capacity() is what we are looking for? need to test -mike
void Assignment::calculateMedian() {
	//Odd student size case
	int size = grades.size();
	if (size % 2 == 1) {
		median = grades[( 1 + size) / 2 - 1];
	} else {
		median = (grades[size / 2 - 1] + grades[size / 2 ]) / 2;
	}
}

//assuming grade array will be in order for mode calculation
void Assignment::calculateMode() {
	int mode = 1;
	int currentMode = 0;
	float possibleMode = grades[0];
	int size = grades.size();	
	for (int i = 1; i < size; i++) {//loops through grades and counts recurring grades
		if (grades[i] == grades[i - 1]){
			currentMode++;
		} else if (currentMode > mode) {//sets the possible mode once it is greater than the current
			possibleMode = grades[i - 1];
			mode = currentMode;
			currentMode = 0;
		}
	}
	mode = possibleMode;
}

//printing method that displays the grade statistics 
void Assignment::printStatistics(){
    cout<<"\t| Mean: "<< mean <<" | High: "<< high << " | Low: "<< low <<" |"<<endl;
}

void Assignment::printGrades()
{
	int size=classTests.size();
	for(int i=0;i<size;i++)
	{
		cout<<classTests[i].getName()<<": "<< grades[i] <<"%"<<endl;
	}
}

void Assignment::printStudentGrade(string studentName)
{
	int size=classTests.size();
	for(int i=0;i<size;i++)
	{
		cout <<"student: " << classTests[i].getName() << endl;
		if ((classTests[i].getName()).find(studentName) != string::npos )
		{
			cout << "\t" << classTests[i].getName() << "'s grade is: " << grades[i] << "\n";
			return;
		}
	}
	cout<<"\tThere is no student named "<<studentName;
}

void Assignment::printAnswers(string studentName) {
	int size=classTests.size();
	for(int i=0;i<size;i++)
	{
		if(classTests[i].getName()==studentName)
		{
			string nameI=classTests[i].getName();
			cout<<nameI<<"'s answers are: "<<endl;
			classTests[i].printAnswers();
			cout<<""<<endl;
			return;
		}
	}
	cout<<"There is no student named "<<studentName;
}

/*void Assignment::displayAll() {
	vector <string> names = getTest().getName();
	for(it = getGrades.begin(); itt = names.begin();  it != getGrades.end(); itt = names.end(); it++,itt++ ) {
		cout<< "\t" << *itt << "\t|\t" << *it << endl;
	}
}*/

void Assignment::omitQuestion(int deletedIndex, vector<string> test_key, bool correct) {
	int size = classTests.size();
	string temp = test_key[deletedIndex];
	for (int i = 0; i < size; i++) {
		if (classTests[i].student_answers[deletedIndex] == temp) {
			correct = true;
			cout << "fuck my life\n";
		}
		test_key[deletedIndex] = "ignorethisanswer";
		classTests[i].student_answers[deletedIndex] = "ignorethisanswer";
		grades[i] = classTests[i].grader(classTests[i].student_answers, test_key, correct);
		cout << "i am counting " << i << endl;
		correct = false;
	}
}

//accessor methods for grade statistics
float Assignment::getHigh() {
	return high;
}

float Assignment::getLow() {
	return low;
}

float Assignment::getMean() {
	return mean;
}
#endif
