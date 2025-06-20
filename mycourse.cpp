#include "mycourse.h"

// constructors
MyCourse::MyCourse() {
	c_name = "null";
	c_grade = "null";
	c_credits = 0;
	c_term = "null";
}

MyCourse::MyCourse(string name, string grade, int credits, string term) {
	c_name = name;
	c_grade = grade;
	c_credits = credits;
	c_term = term;
}

MyCourse::MyCourse(string name, string grade, int credits) {
	c_name = name;
	c_grade = grade;
	c_credits = credits;
	c_term = "null";
}

// setters
string MyCourse::get_name() {
	return c_name;
}

string MyCourse::get_grade() {
	return c_grade;
}

int MyCourse::get_credits() {
	return c_credits;
}

string MyCourse::get_term() {
	return c_term;
}

// getters
void MyCourse::set_name(string name) {
	c_name = name;
}

void MyCourse::set_grade(string grade) {
	c_grade = grade;
}

void MyCourse::set_credits(int credits) {
	c_credits = credits;
}

void MyCourse::set_term(string term) {
	c_term = term;
}

