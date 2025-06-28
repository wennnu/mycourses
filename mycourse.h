#ifndef MYCOURSE_H_
#define MYCOURSE_H_

#include <iostream>
#include <string>

using std::string;

// Use MyCourse class when user enters
// information about a course such as its
// name, final grade, credits and term, when
// the user took the course in
class MyCourse {
  public:
  
    MyCourse();
    MyCourse(string name, string grade, int credits, string term);
    MyCourse(string name, string grade, int credits);

    int get_credits();
    int get_year();
    string get_grade();
    string get_name();
    string get_season();
    string get_term();

    void set_credits(int credits);
    void set_grade(string grade);
    void set_name(string name);
    void set_term(string term);

  private:
    int course_credits_;
    string course_name_;
    string course_final_grade_; // letter grade
    string course_term_; // i.e. Fall 2025
};
#endif // MYCOURSE_H_
