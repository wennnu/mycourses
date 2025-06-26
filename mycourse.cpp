#include "mycourse.h"

// constructors
MyCourse::MyCourse() {
  course_name_ = "null";
  course_final_grade_ = "null";
  course_credits_ = 0;
  course_term_ = "null";
}

MyCourse::MyCourse(string name, string grade, int credits, string term) {
  course_name_ = name;
  course_final_grade_ = grade;
  course_credits_ = credits;
  course_term_ = term;
}

MyCourse::MyCourse(string name, string grade, int credits) {
  course_name_ = name;
  course_final_grade_ = grade;
  course_credits_ = credits;
  course_term_ = "null";
}

// setters
int MyCourse::get_credits() {
  return course_credits_;
}

string MyCourse::get_name() {
  return course_name_;
}

string MyCourse::get_grade() {
  return course_final_grade_;
}

string MyCourse::get_term() {
  return course_term_;
}

// getters
void MyCourse::set_name(string name) {
  course_name_ = name;
}

void MyCourse::set_grade(string grade) {
  course_final_grade_ = grade;
}

void MyCourse::set_credits(int credits) {
  course_credits_ = credits;
}

void MyCourse::set_term(string term) {
  course_term_ = term;
}

