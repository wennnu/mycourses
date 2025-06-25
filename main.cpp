// TODO: sort the course info interms of term year (fall 2024 - winter 2025 etc.) also highest to lowest gpa 
// TODO: Fix formatting
#include "mycourse.h"

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>

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
void SaveToFile();
void PrintSummary(char summary_type);
void FindEmptyIndex(string name, string grades, int credits, string term);
bool IsCourseExist(string course_name);
void FileToArray();
char SummaryOptions();
void Sort(MyCourse array[], char type);
void MergeSort(MyCourse array[], int begin, int end, char type);
void Merge(MyCourse array[], int begin, int mid, int end, char type);

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

// for storing founded course;
MyCourse find_course;

// template for merge sort 3(4) different data types: string gpa, int credits, string name
// technically gpa and name are char type
// input MyCourse type array, subarray size int left and right, int begin, any type value_right and left
template <typename Any>
void CompareMerge(MyCourse array[], std::vector<MyCourse> array_left, std::vector<MyCourse> array_right, Any value_left, Any value_right, int& i_left, int& i_right, int& i_array) {
	if (value_left < value_right) {
		array[i_array] = array_left[i_left];
		i_left++;	
	} else {
		array[i_array] = array_right[i_right];
		i_right++;
	}
}

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
	char choice;
	
	do {
		choice = PromptOptions();

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

			SaveToFile();
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
		} else if (choice == 'c') {

			char summary_option = SummaryOptions();

			cout << setfill('/') << setw(31) << "/\n" << endl;
			PrintSummary(summary_option);
			cout << setfill('/') << setw(31) << "/\n" << endl;
			cout << "\n * Done *" << endl;
		} else if (choice == 'a') {
			string course_name;
			cout << "Enter course name: ";
			getline(cin >> std::ws, course_name);	

			cout << setfill('/') << setw(31) << "/\n" << endl;
			if (IsCourseExist(course_name)) {
				cout << "Course: " << find_course.get_name() << "\nFinal Grade: " << 
					find_course.get_grade() << "\nCredits: " << find_course.get_credits() << 
					"\nTerm Taken: " << find_course.get_term() << endl;	
			} else {
				cout << "* Course Not Found x_x *\n" << endl;
			}	
			cout << setfill('/') << setw(31) << "/\n" << endl;
			cout << "\n * Done *" << endl;
		} else if (choice == 'e') {
			cout << "\nSee you." << endl;
		} else {
			cout << "Invalid Input." << endl;
		}
	} while (choice != 'e');

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
		"\n\t| GPA [z] GRADE[x] SUMMARY[c]" << " |\n" <<
		"\t|" << setw(10) << "\tFind Course [a]" << setw(9) << "|\n"<< 
		"\t|" << setw(31) << "|\n" <<
		"\t|" << setw(28) << "EXIT [e]" << " |" << endl;

	cout << "\t" << setfill('-') << setw(31) << "-" << endl;
	
	// Obtain one single character from user
	cin >> option;

	return option;
}

char SummaryOptions() {
	char option;

	// GUI mainly for the look
	cout << "\t" << setfill('-') << setw(31) << "-" << endl;
	cout << "\t|" << setfill(' ') << setw(4) << " " << "CHOOSE A SORTING TYPE" << setw(7) 
		<< "|\t\n" << "\t|" << setw(30) << "|" <<
		"\n\t|  GPA [z] Name[x] CREDITS[c]" << " |\n" <<
		"\t|" << setw(31) << " |\n" << "\t|" << setw(10) << " " << "TERM [a]" << setw(12) << "|" << endl;  
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
		FindEmptyIndex(split_arr[0], split_arr[1], std::stoi(split_arr[2]), split_arr[3]);
	}
}

// put course information into an array
void FindEmptyIndex(string name, string grades, int credits, string term) {
	course = MyCourse(name, grades, credits, term); // name, grades, credits, term
		for (int i = 0; i < 40; i++) {
			if (course_list[i].get_name() == "null") 
			{
				course_list[i] = course;
				break;
			}
		}
}

// Print out a list of all of the courses with their attributes in the file
void PrintSummary(char summary_type) {
	//string split_arr[4];
	//std::ifstream my_file("CourseFile");
	//string file_line;
	// load course information from file to array
	FileToArray();
	/*
	while (getline(my_file, file_line)) {
		SplitWords(split_arr, file_line, '/');		
		FindEmptyIndex(split_arr[0], split_arr[1], std::stoi(split_arr[2]), split_arr[3]);
	}
	*/
	Sort(course_list, summary_type);
	
	// load array to summary
	for (MyCourse course : course_list) { 
		if (course.get_name() != "null") {
			cout << "Course: " << course.get_name() << "\nFinal Grade: " << course.get_grade() <<
				"\nCredits: " << course.get_credits() << "\nTerm Taken: " << course.get_term() << endl;
			cout << setfill('-') << setw(31) << "-\n" << endl;
		} else {
			break;
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

void SaveToFile() {
	char to_save;
	cout << "Would you like to save [y/n] ";
	cin >> to_save;

	if (to_save == 'y') {
		std::ofstream my_file;
		my_file.open("CourseFile", std::ios::app);

		for (MyCourse course : course_list) {
			// add course to file but avoid repetitive ones
			if (course.get_name() != "null" && !IsCourseExist(course.get_name())) {
				my_file << course.get_name() << "/" << 
					course.get_grade() << "/" << course.get_credits() << 
					"/" << course.get_term() << endl;
			} else {
				break;
			}	
		}
		my_file.close();

		cout << "* Saved! *\n\n" << endl;
	} else if (to_save == 'n') {
		cout << "\n* Note: It is not saved! *\n" << endl;
	} else {
		cout << "Invalid Input." << endl;
	}
}

// check if course is already in the file based on the name
bool IsCourseExist(string course_name) {
	std::ifstream my_file("CourseFile");
	string file_line;
	int char_index;
	string split_arr[4];
	while (getline(my_file, file_line)) {
		char_index = file_line.find("/");
		if (file_line.substr(0, char_index) == course_name) {
			SplitWords(split_arr, file_line, '/');	
			find_course = MyCourse(split_arr[0], split_arr[1], std::stoi(split_arr[2]), split_arr[3]);
			my_file.close();
			return 1;
		}
	}
	return 0;
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

// merge two arrays into one array from smallest
// to biggest number. Input int type array,
// int type beginning of the array, int type
// mid position of the array and int type end
// of the array and char type gpa or credits
void Merge(MyCourse array[], int begin, int mid, int end, char type) {
	// size of the two subarrays
	int subarray_size_left = mid - begin + 1;
	int subarray_size_right = end - mid;

	// create temporary vectors to copy array contents
	std::vector<MyCourse> array_left(subarray_size_left), array_right(subarray_size_right);

	// copy array contents
	for (int i = 0; i < subarray_size_left; i++) {
		array_left[i] = array[begin + i];
	}
	for (int i = 0; i < subarray_size_right; i++) {
		array_right[i] = array[mid + 1+ i];
	}

	int i_left = 0, i_right = 0; // index for subarray left and subarray right
	int i_array = begin;	     // index for array

	// compare and sort from least to greatest
	// need to know if sorting gpa, name or credits
	//(MyCourse array[], std::vector<MyCourse> array_left, std::vector<MyCourse> array_right, Any value_left, Any value_right, int& i_left, int& i_right, int& i_array)
	if (type == 'z') { // gpa
		while (i_left < subarray_size_left && i_right < subarray_size_right) {
			CompareMerge<string>(array, array_left, array_right, array_left[i_left].get_grade(), array_right[i_right].get_grade(), i_left, i_right, i_array);	
		}
	} else if (type == 'x') { // name
		while (i_left < subarray_size_left && i_right < subarray_size_right) {
			CompareMerge<string>(array, array_left, array_right, array_left[i_left].get_name(), array_right[i_right].get_name(), i_left, i_right, i_array);	
		}
	} else if (type == 'c') { // credits
		while (i_left < subarray_size_left && i_right < subarray_size_right) {
			CompareMerge<int>(array, array_left, array_right, array_left[i_left].get_credits(), array_right[i_right].get_credits(), i_left, i_right, i_array);
		}
	}
	

	// sort any left overs
	while (i_left < subarray_size_left) {
		array[i_array] = array_left[i_left];
		i_left++;
		i_array++;
	}

	while (i_right < subarray_size_right) {
		array[i_array] = array_right[i_right];
		i_right++;
		i_array++;
	}
}

// Merge sorting algorithm input int type array
// int type beginning of the array and int type
// end of the array and char type 'g' for gpa
// 'c' for credits
void MergeSort(MyCourse array[], int begin, int end, char type) {
	// return if no more array to split
	if (begin >= end) {
		return;
	}
	// find the middle position of the array
	int mid = begin + (end - begin) / 2;
	MergeSort(array, begin, mid, type); // left portion
	MergeSort(array, mid+1, end, type); // right portion
	
	Merge(array, begin, mid, end, type); // merge left and right arrays together
}

void FileToArray() {
	string split_arr[4];
	string file_line;
	std::ifstream my_file("CourseFile");

	while (getline(my_file, file_line)) {
		SplitWords(split_arr, file_line, '/');		
		FindEmptyIndex(split_arr[0], split_arr[1], std::stoi(split_arr[2]), split_arr[3]);
	}
	my_file.close();
}

// sort from least to greatest
void Sort(MyCourse array[], char type) {
	
	// to find where end is
	int end = 0;
	while (array[end].get_name() != "null") {
		end++;
	}
	// merge sort array
	MergeSort(array, 0, end-1, type);
}
