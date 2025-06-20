// TODO: ask user to save course info to a file
// TODO: sort the course info interms of term year (fall 2024 - winter 2025 etc.) also highest to lowest gpa 
// TODO: add 'summary' section
// TODO: read summary from file
// TODO: use do-while loop and exit only when user wants to exit (enter 'e')
// TODO: add sortAlphabetical() method
// TODO: add sortGpa() method
// TODO: add sortCredit() method
// TODO: add findCourse(string name) method and print a summary information about that course
#include "mycourse.h"

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::setfill;
using std::setw;

char PromptOptions();
void SaveCourses(int number_of_courses);
void SplitWords(string array[], string sentence, char symbol);
float CalculateGpa(MyCourse list[]);
float ConvertToGradePoints(string letter_grade);
void SaveAssignments(int number_of_assignments);

// storing name, grade, credits and term information
MyCourse course;

// Maximum 40 courses with default constructor, about four years of classes
MyCourse course_list[40];

// assignment struct for storing current grade and assignment in an on-going course
struct Assignment {
	string assignment_type = "null"; // quiz, midterm, lab...etc.
	float grade_percentage = 0.0; // often given in percentage %
	int weighting = 0; // weighting also in percentage and should be in whole numbers
};

float CalculateGrade(Assignment list[], int size, int target_grade, int final_weighting);

// store assignment type, grade and weighting need to access globally
Assignment graded_assignments;

// dynamic array since I don't know how many assignments there are for any course
Assignment * assignment_list;

int main() {
	int N_courses; 
	string course_name;
	char letter_grade;
	int credits;
	string term;
	
	Assignment placeholder; // for initializing array
	int N_assignments;
	int final_weighting;
	int target_grade;
	
	char choice = PromptOptions();

	if (choice == 'z') {
		cout << "Enter number of courses: "; 
		cin >> N_courses;
		
		cout << setfill('/') << setw(31) << "/" << endl;
		cout << "\nEnter in the format:(name/grade/credits/term)\n" <<
			"(i.e. chem 120/A/4/Winter 2025)" << endl;
		cout << setfill('-') << setw(31) << "-" << endl;
		SaveCourses(N_courses);
		
		// output gpa with 2 decimal places precision with no roundings
		// with total credits 
		cout << "\n" << std::setprecision(3) << "Your gpa is:\t" << CalculateGpa(course_list) << endl;
		cout << setfill('/') << setw(31) << "/" << endl;
	} else if (choice == 'x') {
		cout << "Enter number of graded assignments (midterm, lab, quiz...etc. EXCLUDE FINAL): ";
		cin >> N_assignments; 
		assignment_list = new Assignment[N_assignments]{placeholder}; // allocate new memory

		cout << setfill('/') << setw(31) << "/" << endl;
		cout << "\nEnter in the format (assignment/grade percentage/weighting)\n" <<
			"(i.e. midterm 1/85/15)"<< endl;
		cout << setfill('-') << setw(31) << "-" << endl;
		SaveAssignments(N_assignments);	

		cout << setfill('-') << setw(31) << "-" << endl;
		cout << "\nEnter final exam weighting: ";
		cin >> final_weighting;

		cout << "\nEnter grade you want to achieve in this course: ";
		cin >> target_grade;

		cout << "\n" << std::setprecision(4) << "Your target grade:\t" << target_grade <<
			"\nRequire:\t\t" << CalculateGrade(assignment_list, N_assignments, target_grade, final_weighting) << 
			" on the final exam.\n\n" << "GOOD LUCK!" << endl;
		cout << setfill('/') << setw(31) << "/" << endl;

		delete[] assignment_list; // free memory
	}
	return 0;
}

// Ask user if they want to
// calculate term gpa or 
// calculate course grade or
// print out an academic summary
// return one single character
char PromptOptions() {
	char option;

	// GUI mainly for the look
	cout << "\t" << setfill('-') << setw(31) << "-" << endl;

	cout << "\t|\tCHOOSE AN OPTION" << setfill(' ') << setw(9) << "|\t\n" <<
		"\t|" << setw(30) << "|" <<
		"\n\t|\tGPA [z]\tGRADE[x]" << setw(8) << "|\n" <<
		"\t|" << setw(31) << "|\n" <<
		"\t|" << setw(28) << "EXIT [e]" << " |" << endl;

	cout << "\t" << setfill('-') << setw(31) << "-" << endl;
	
	// Obtain one single character from user
	cin >> option;

	return option;
}

// Instantiate mycourse object and save to the array
// Input int number of courses taken
void SaveCourses(int number_of_courses) {
	// this array is for storing name, grade, credits and term
	// used in the split function for-loop where the extracted 
	// words are put seperatedly in each of the position 
	string split_arr[4];
	string course_info; // user input in the format (name/grade/credits/term)
	
	for (int n = 0; n < number_of_courses; n++) {
		cout << "Course " << n+1 << ": ";
		getline(cin >> std::ws, course_info); 
		
		SplitWords(split_arr, course_info, '/');

		// save to to an empty spot in course array
		course = MyCourse(split_arr[0], split_arr[1], std::stoi(split_arr[2]), split_arr[3]); // name, grades, credits, term
		for (int i = 0; i < 40; i++) {
			if (course_list[i].get_name() == "null") 
			{
				course_list[i] = course;
				break;
			}
		}
	}
}

// Save assignment object to array
// input int number of graded assignments
void SaveAssignments(int number_of_assignments) {
	// this array is for storing name, grade and weighting
	// used in the split function for-loop where the extracted 
	// words are put seperatedly in each of the position 
	string split_arr[3];
	string assignment_info; // user input in the format (name/grade/weighting)
	
	for (int n = 0; n < number_of_assignments; n++) {
		cout << "Course " << n+1 << ": "; // formatting output
		getline(cin >> std::ws, assignment_info); 
		
		SplitWords(split_arr, assignment_info, '/'); // split sentences by character delimeter '/'
		
		graded_assignments.assignment_type = split_arr[0];	
		graded_assignments.grade_percentage = (float) std::stoi(split_arr[1]);	
		graded_assignments.weighting = std::stoi(split_arr[2]);	
		
		// save to an empty index in assignment_list array
		for (int i = 0; i < number_of_assignments; i++) {
			if (assignment_list[i].assignment_type == "null") {
				assignment_list[i] = graded_assignments;
				break;
			}
		}
	}
}

// split strings with symbol char
// store words individually in array
void SplitWords(string array[], string sentence, char symbol) {
	string word; // individual words seperated by '/'
	int split_i = 0; // for navigating through split_arr
		     
	std::stringstream split(sentence);
	while (getline(split, word, symbol)) {
		array[split_i] = word;			
		split_i++;
	}
}

// return floating number gpa to 2 decimal places
// input MyCourse list and iterate through, get
// gpa from each course object divide by total
// credits
float CalculateGpa(MyCourse list[]) {
	// sum up gpa and credits
	float grade_points = 0.0;
	int total_credits = 0;
	float grade_points_times_credits = 0.0;

	for (int i = 0; i < 40; i++) {
		if (list[i].get_name() == "null") { // exit when there is no more courses to count
			break;
		}
		grade_points = ConvertToGradePoints(list[i].get_grade());
		grade_points_times_credits += grade_points * list[i].get_credits();
		total_credits += list[i].get_credits();
	}
	// calculate gpa
	float gpa = grade_points_times_credits / total_credits; 

	return gpa;
}

// Return float grade on the final exam to achieve
// target grade. Input assignment array and 
// int target grade and int final exam weighting
// and int array size 
float CalculateGrade(Assignment list[], int size, int target_grade, int final_weighting) {
	float current_grade;
	float final_grade;
	
	// calculate the sum of graded assignments with their weighting
	for (int i = 0; i < size; i++) {
		if (list[i].assignment_type == "null") {
			break;
		}
		current_grade += list[i].grade_percentage * list[i].weighting / 100;
	}
	final_grade = (target_grade - current_grade) / (final_weighting / 100.0);

	return final_grade;
}

// Return float gpa using the sum of (credits * grade points)
// divided by the sum of course credits with input
// string letter grade (i.e. A or A-)
float ConvertToGradePoints(string letter_grade) {
	if (letter_grade == "A") {
		return 4.0;
	} else if (letter_grade == "A-") {
		return 3.7;
	} else if (letter_grade == "B+") {
		return 3.3;
	} else if (letter_grade == "B") {
		return 3.0;
	} else if (letter_grade == "B-") {
		return 2.7;
	} else if (letter_grade == "C+") {
		return 2.3;
	} else if (letter_grade == "C") {
		return 2.0;
	} else if (letter_grade == "D") {
		return 1.0;
	}
	return 0.0;
}
