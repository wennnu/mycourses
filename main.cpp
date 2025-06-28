#include "mycourse.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

using std::cin;
using std::cout;
using std::endl;
using std::setfill;
using std::setw;
using std::string;

bool IsCourseExist(string course_name);
char PromptOptions();
char SummaryOptions();
float CalculateGpa(MyCourse list[]);
float ConvertToGradePoints(string letter_grade);
void FileToArray();
void FindEmptyIndex(string name, string grades, int credits, string term);
void PrintSummary(char summary_type);
void SaveAssignments(int number_of_assignments);
void SaveCourses(int number_of_courses);
void SaveToFile();
void SelectionSort(int list[], int start, int end);
void SortByTerm(int size);
void SplitWords(string array[], string sentence, char symbol);
void Merge(MyCourse array_to_sort[], int begin, int mid, int end, char type);
void MergeSort(MyCourse array_to_sort[], int begin, int end, char type);

// Merge two arrays together, used in Merge function
// value_left corresponds to the value in the index
// of left_array, similarly for value_right. i_array
// is the index of course_list array. 'Any' type should
// take either type int or type float

template <typename Any>
void CompareMerge(MyCourse array_to_sort[], std::vector<MyCourse> array_left,
		              std::vector<MyCourse> array_right, Any value_left, 
		              Any value_right, int& i_left, int& i_right, int& i_array) {
  if (value_left <= value_right) {
    array_to_sort[i_array] = array_left[i_left];
    i_left++;	
  } else {
    array_to_sort[i_array] = array_right[i_right];
    i_right++;
  }
  i_array++;
}

// Uses when user enters information about the assignments of a course
// where assignment type is any graded portion that excludes the 
// final exam (i.e. quiz, midterm, lab...etc.) with the grade user 
// achieved in each assignment and the weighting of the assignment 
// in whole numbers
struct Assignment {
  string assignment_type = "null"; 
  float grade_percentage = 0.0;
  int weighting = 0;
};

float CalculateGrade(Assignment list[], int size, int target_grade, int final_weighting);

// the graded assignments struct for storing the information regarding to 
// its type, grade and weighting then to be stored in an assignment array
Assignment graded_assignments;

// dynamic array with size depends on how many assignments user assigns it
Assignment *assignment_list;

// course class for storing the information regarding to its name,
// final letter grade, credits and the term when the user took in
MyCourse course;

// store course object with maximum 40 courses approximately the number of
// courses taken in four years of university
MyCourse course_list[40];

// for find course function where the function returns the summary of the
// course the user requests with its name, grade, credits and term
MyCourse find_course;

int main() {
  // user input for option prompt
  char choice;  

  // default struct for initializing dynamic array with new spaces
  Assignment placeholder;  
  
  // prompt user with options of whether they want to calculate their 
  // final gpa, calculate the grade required on the final exam, print
  // a summary list of all the courses they took or if they want to
  // find the summary about a particular course. Repeat until user
  // quiz eventually
  do {
    choice = PromptOptions(); // asking for one single character user input

    // store courses objects to array then calculate and return final gpa
    // up to 2 decimal places rounded and ask if user wants to save courses
    // to file. If yes then iterate through course_list array and save
    // to file in the format "name/grade/credits/term"
    if (choice == 'z') {
      int N_courses;
      cout << "Enter number of courses: "; 
      cin >> N_courses;

      cout << setfill('/') << setw(31) << "/" << endl;
      cout << "\nEnter in the format:(name/grade/credits/term)" 
           << "\n(i.e. chem 120/A/4/Winter 2025)" << endl;
      cout << setfill('-') << setw(31) << "-" << endl;
      SaveCourses(N_courses);

      cout << "\n" << std::setprecision(3) << "Your gpa is:\t" << CalculateGpa(course_list) << endl;
      cout << setfill('/') << setw(31) << "/" << endl;

      SaveToFile();
      
      // store assignment struct to array then calculate current grade and 
      // grade required on the final exam to achieve target final grade
      // given final weighting
    } else if (choice == 'x') {
      int N_assignments;
      cout << "Enter number of graded assignments (midterm, lab, quiz...etc. EXCLUDE FINAL): ";
      cin >> N_assignments; 

      // allocate new memory to dynamic array assignment_list
      assignment_list = new Assignment[N_assignments]{placeholder}; 

      cout << setfill('/') << setw(31) << "/" << endl;
      cout << "\nEnter in the format (assignment/grade percentage/weighting)" 
           << "\n(i.e. midterm 1/85/15)"<< endl;
      cout << setfill('-') << setw(31) << "-" << endl;
      SaveAssignments(N_assignments);	

      int final_weighting;
      cout << setfill('-') << setw(31) << "-" << endl;
      cout << "\nEnter final exam weighting: ";
      cin >> final_weighting;

      int target_grade;
      cout << "\nEnter grade you want to achieve in this course: ";
      cin >> target_grade;

      cout << "\n" << std::setprecision(4) << "Your target grade:\t" << target_grade 
           << "\nRequire:\t\t" << CalculateGrade(assignment_list, N_assignments, target_grade, final_weighting) 
           << " on the final exam.\n\n" << "GOOD LUCK!" << endl;
      cout << setfill('/') << setw(31) << "/" << endl;

      delete[] assignment_list; 

      // prompt user with summary options whether they want to the summary
      // in the order (highest to lowest) of gpa, name, credits or term taken
    } else if (choice == 'c') {
      char summary_option = SummaryOptions();

      cout << setfill('/') << setw(31) << "/\n" << endl;
      PrintSummary(summary_option);
      cout << setfill('/') << setw(31) << "/\n" << endl;

      cout << "\n * Done *" << endl;

      // enter the name of the course then iterate through the file
      // if the course name exists then get the file line with its name
      // grade, credits and term then displays it like a summary else
      // tell user the course is not found in the file
    } else if (choice == 'a') {
      string course_name;
      cout << "Enter course name: ";
      getline(cin >> std::ws, course_name);	

      cout << setfill('/') << setw(31) << "/\n" << endl;
      if (IsCourseExist(course_name)) {
        cout << "Course: " << find_course.get_name() 
             << "\nFinal Grade: " << find_course.get_grade()
             << "\nCredits: " << find_course.get_credits()
             << "\nTerm Taken: " << find_course.get_term() << endl;	
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

// Iterate through the file and match course name with user entered 
// course name. Return false if no matched course name found else
// returns true
bool IsCourseExist(string course_name) {
  // array that take part of the string split by a character
  // for example "name/grade/credits/term" will be split by
  // the character '/' and stored in each index of the array
  string split_arr[4];  
  string file_line;
  std::ifstream my_file("CourseFile");

  while (getline(my_file, file_line)) {
    int char_index = file_line.find("/");
    if (file_line.substr(0, char_index) == course_name) {
      SplitWords(split_arr, file_line, '/');	
      find_course = MyCourse(split_arr[0], split_arr[1], std::stoi(split_arr[2]), split_arr[3]);
      my_file.close();
      return 1;
    }
  }
  my_file.close();
  return 0;
}

// User Interface asking user whether they want to calculate term gpa,
// calculate required grade on the final exam to achieve required final
// grade, print a sorted course summary or return the summary of a user
// chosen course. Returns a character
char PromptOptions() {
  char option;

  cout << "\t" << setfill('-') << setw(31) << "-" << endl;
  cout << "\t|\tCHOOSE AN OPTION" << setfill(' ') << setw(7) << "|"
       << "\n\t|" << setw(30) << "|" 
       << "\n\t| GPA [z] GRADE[x] SUMMARY[c]" << " |" 
       << "\n\t|" << setw(10) << "\tFind Course [a]" << setw(8) << "|"
       << "\n\t|" << setw(30) << "|" 
       << "\n\t|" << setw(28) << "EXIT [e]" << " |" << endl;
  cout << "\t" << setfill('-') << setw(31) << "-" << endl;
  cin >> option;
  return option;
}

// User Interface asking user whether they want to sort the course list
// (from highest to lowest) gpa, name, credits or term
char SummaryOptions() {
  char option;

  cout << "\t" << setfill('-') << setw(31) << "-" << endl;
  cout << "\t|" << setfill(' ') << setw(4) << " " << "CHOOSE A SORTING TYPE" << setw(7) 
       << "|\t\n" << "\t|" << setw(30) << "|" 
       << "\n\t|  GPA [z] Name[x] CREDITS[c]" << " |\n" 
       << "\t|" << setw(31) << " |\n" 
       << "\t|" << setw(10) << " " << "TERM [a]" << setw(12) << "|" << endl;  
  cout << "\t" << setfill('-') << setw(31) << "-" << endl;
  cin >> option;
  return option;
}

// Itegrate through course_list and get each course gpa and their credits
// convert letter grade to grade points following McGill University gpa 
// scheme sum up the total of (grade points * credits) and total credits
// return float type gpa by dividing the sum of (grade points * credits) 
// by the total credits
float CalculateGpa(MyCourse list[]) {
  int total_credits = 0;
  float grade_points_times_credits = 0.0;

  for (int i = 0; i < 40; i++) {
    // break out of the loop when there is no more courses to count
    if (list[i].get_name() == "null") { 
      break;
    }
    float grade_points = ConvertToGradePoints(list[i].get_grade());
    grade_points_times_credits += grade_points * list[i].get_credits();
    total_credits += list[i].get_credits();
  }
  float gpa = grade_points_times_credits / total_credits; 
  return gpa;
}

// Iterate through Assignment struct array and sum up
// the grade and the weighting divided by 100, then find the required
// final grade on the final exam by getting the difference beteween the 
// current grade and target grade divided by the final weighting (divided by 100)
// Return float type final grade. int size represents the size of the array
float CalculateGrade(Assignment list[], int size, 
                     int target_grade, int final_weighting) {
  float current_grade = 0.0;

  for (int i = 0; i < size; i++) {
    current_grade += list[i].grade_percentage * list[i].weighting / 100;
  }
  float final_grade = (target_grade - current_grade) / (final_weighting / 100.0);
  return final_grade;
}

// Convert grade letter to grade points following McGill University grading scheme
// returns float type grade points
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

// Iterate through the course list and input course information to file
// following the format "name/grade/credits/term"
void FileToArray() {
  // array for storing words seperated by a character for example,
  // "name/grade/credits/term" seperated by '/' and each string is
  // stored in each corresponding index 
  string split_arr[4];
  string file_line;
  std::ifstream my_file("CourseFile");

  while (getline(my_file, file_line)) {
    SplitWords(split_arr, file_line, '/');		
    // store course information from file to array
    FindEmptyIndex(split_arr[0], split_arr[1], std::stoi(split_arr[2]), split_arr[3]);
  }
  my_file.close();
}

// Iterate through course list and replace the first course object with name "null"
// with the new course object with new user entered information
void FindEmptyIndex(string name, string grades, int credits, string term) {
  course = MyCourse(name, grades, credits, term); 
  for (int i = 0; i < 40; i++) {
    if (course_list[i].get_name() == "null") {
      course_list[i] = course;
      break;
    } 
  }
}

// Print a summary list of all of the courses used saved to the file with
// options of sorting them based on their gpa, name, credits or term (highest to lowest)
void PrintSummary(char summary_type) {
  // Get course objects from file line to individual index of the array 
  FileToArray();

  // Get how many courses in the list are not in the default attributes (i.e. name not "null")
  int end = 0;
  while (course_list[end].get_name() != "null") {
    end++;
  }

  summary_type != 'a' ? MergeSort(course_list, 0, end-1, summary_type) : SortByTerm(end);

  // Print out every single course with their name, final grade, credits and term taken
  for (MyCourse course : course_list) { 
    if (course.get_name() != "null") {
      cout << "Course: " << course.get_name() 
           << "\nFinal Grade: " << course.get_grade() 
           << "\nCredits: " << course.get_credits() 
           << "\nTerm Taken: " << course.get_term() << endl;
      cout << setfill('-') << setw(31) << "-\n" << endl;
    } else {
      break;
    }
  }	
}

// Store Assignment structs to an array 
void SaveAssignments(int number_of_assignments) {
  // Store words seperated by a char for example
  // "name/grade/weighting" will seperated by '/'
  // and each string stored to corresponding index
  string split_arr[3];

  // User entered "name/grade/weighting" in one line
  string assignment_info;

  for (int n = 0; n < number_of_assignments; n++) {
    cout << "Course " << n+1 << ": "; 
    getline(cin >> std::ws, assignment_info); 

    SplitWords(split_arr, assignment_info, '/'); 

    graded_assignments.assignment_type = split_arr[0];	
    graded_assignments.grade_percentage = (float) std::stoi(split_arr[1]);	
    graded_assignments.weighting = std::stoi(split_arr[2]);	
    
    // Replace where an assignment name is "null" with new user entered information
    for (int i = 0; i < number_of_assignments; i++) {
      if (assignment_list[i].assignment_type == "null") {
        assignment_list[i] = graded_assignments;
        break;
      }
    }
  }
}

// Save course objects to an array
void SaveCourses(int number_of_courses) {
  // Store words seperated by a char for example
  // "name/grade/creidts/term will seperated by '/'
  // and each string stored to corresponding index
  string split_arr[4];

  // User input in one line "name/grade/credits/term"
  string course_info; 

  for (int n = 0; n < number_of_courses; n++) {
    cout << "Course " << n+1 << ": ";
    getline(cin >> std::ws, course_info); 

    SplitWords(split_arr, course_info, '/');
    // Replace objects with name "null" with new user entered information
    FindEmptyIndex(split_arr[0], split_arr[1], std::stoi(split_arr[2]), split_arr[3]);
  }
}

// If user wants to save, itereate through the course_list array and 
// append course information in the format "name/grade/credits/term"
// to a file. Also checks if a course name already exist in the file
// to avoid repetitiveness
void SaveToFile() {
  char to_save;
  cout << "Would you like to save [y/n] ";
  cin >> to_save;

  if (to_save == 'y') {
    std::ofstream my_file;
    my_file.open("CourseFile", std::ios::app);

    for (MyCourse course : course_list) {
      // save to file only if the name does not already exist
      if (course.get_name() != "null" && !IsCourseExist(course.get_name())) {
        my_file << course.get_name() << "/" 
                << course.get_grade() << "/" 
                << course.get_credits() << "/" 
                << course.get_term() << endl;
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

// Iterate through the course list with the same year
// sort the list by the season Summer > Fall > WInter
void SelectionSort(MyCourse list[], int start, int end) {
  std::map<string, int> season_map = {{"Summer", 0}, {"Fall", 1}, {"Winter", 2}};
  string ini_season = course_list[start].get_season();
  int min_value = season_map.at(ini_season);

  while (start < end) {
    int j = start+1;
    int min_position = start; // index with the lowest value
    while (j < end) {
      string current_season = course_list[j].get_season();
      int current_season_value = season_map.at(current_season);

      if (current_season_value < min_value) {
        min_value = current_season_value;
        min_position = j;
      }
      j++;
    }
    // swap positions between the index with the minimum value
    // and the initial value
    MyCourse temp_course = course_list[start];
    course_list[start] = course_list[min_position];
    course_list[min_position] = temp_course; 
    start++;
  }
}

// Sort "season year" from most recent to the oldest
// then within the same term sort courses by gpa highest
// to lowest
void SortByTerm(int size) {
  // sort by year first
  MergeSort(course_list, 0, size-1, 'y');

  int ini_year = course_list[0].get_year();

  // map a year starting with value 0 increment by 1 with added new year
  std::map<int, int> year_index_map = {{ini_year, 0}};

  // Iterate through course list and add years without repeats 
  std::vector<int> distinct_year;
  distinct_year.push_back(ini_year); 

  for (int i = 1; i < size; i++) {
    int current_year = course_list[i].get_year();

    // map a new year and the first index it occured
    if (course_list[i].get_year() != ini_year) {
      distinct_year.push_back(current_year);
      year_index_map[current_year] = i;
      ini_year = current_year;
    }
  }

  for (auto key : year_index_map) {
    cout << "second: " << key.second << endl;
  }

  // Iterate through the year map and sort courses by the seasons
  // within the same year
  for (int i_year = 0, size = year_index_map.size()-2; i_year <= size; i_year++) {
    int year_before = distinct_year.at(i_year);
    int year_after = distinct_year.at(i_year+1);

    SelectionSort(course_list, year_index_map.at(year_before), year_index_map.at(year_after));
  } 

  // include last index
  SelectionSort(course_list, size-2, size);
}

// Iterate through an split_array that has a fixed size
// for storing seperate strings. Sentence is a string
// seperate by a character, and symbol is a character that
// gives information about where to split the sentence into
// For example "name/grade/credits/term" with symbol '/' will
// split each string by '/' and put in corresponding index of
// the split array
void SplitWords(string split_array[], string sentence, char symbol) {
  // string seperated by a character 'symbol'
  string word; 
  
  // for navigating split_array
  int split_i = 0; 
  std::stringstream sentence_to_be_split(sentence);

  while (getline(sentence_to_be_split, word, symbol)) {
    split_array[split_i] = word;			
    split_i++;
  }
}

/***************************************************************************
*  Title: Merge Sort Algorithm
*  Author: Programiz
*  Date: 2025
*  Availability: https://www.programiz.com/dsa/merge-sort
*
***************************************************************************/
// Standard Merge Sort Algorithm, with additional parameter of character type 
// for the type of sorting user wants such as by name, credits, term or by gpa
void Merge(MyCourse array_to_sort[], int begin, int mid, int end, char type) {
  int subarray_size_left = mid - begin + 1;
  int subarray_size_right = end - mid;

  // create temporary vectors to copy array contents
  std::vector<MyCourse> array_left(subarray_size_left), array_right(subarray_size_right);

  // copy array contents to temporary vectors
  for (int i = 0; i < subarray_size_left; i++) {
    array_left[i] = array_to_sort[begin + i];
  }
  for (int i = 0; i < subarray_size_right; i++) {
    array_right[i] = array_to_sort[mid + 1 + i];
  }

  int i_left = 0, i_right = 0, i_array = begin;

  // merge and sort
  if (type == 'x') { // sort by name
    while (i_left < subarray_size_left && i_right < subarray_size_right) {
      string value_L = array_left[i_left].get_name();
      string value_R = array_right[i_right].get_name();
      CompareMerge<string>(array_to_sort, array_left,
                        array_right, value_L, 
                        value_R, i_left, i_right, i_array);
    }
  } else if (type == 'c') { // sort by credits
    while (i_left < subarray_size_left && i_right < subarray_size_right) {
      int value_L = array_left[i_left].get_credits();
      int value_R = array_right[i_right].get_credits();
      CompareMerge<int>(array_to_sort, array_left,
                        array_right, value_L, 
                        value_R, i_left, i_right, i_array);
    } 
  } else if (type == 'y') { // sort by year
    while (i_left < subarray_size_left && i_right < subarray_size_right) {
      int value_L = array_left[i_left].get_year();
      int value_R = array_right[i_right].get_year();
      CompareMerge<int>(array_to_sort, array_left,
                          array_right, value_L, 
                          value_R, i_left, i_right, i_array);
    } 
  } else { // default sort by gpa
    while (i_left < subarray_size_left && i_right < subarray_size_right) {
      float value_L = ConvertToGradePoints(array_left[i_left].get_grade());
      float value_R = ConvertToGradePoints(array_right[i_right].get_grade());
      CompareMerge<float>(array_to_sort, array_left,
                          array_right, value_L, 
                          value_R, i_left, i_right, i_array);
    }
  }

  //  // store any left overs in the subarrays 
  while (i_left < subarray_size_left) {
    array_to_sort[i_array] = array_left[i_left];
    i_left++;
    i_array++;
  }

  while (i_right < subarray_size_right) {
    array_to_sort[i_array] = array_right[i_right];
    i_right++;
    i_array++;
  }
}

void MergeSort(MyCourse array_to_sort[], int begin, int end, char type) {
  // split the array in halves if length is greater than 1
  if (begin < end) {
    // find the middle position of the array
    int mid = begin + (end - begin) / 2;
    MergeSort(array_to_sort, begin, mid, type); // left portion
    MergeSort(array_to_sort, mid+1, end, type); // right portion
    Merge(array_to_sort, begin, mid, end, type); 
  }
}
