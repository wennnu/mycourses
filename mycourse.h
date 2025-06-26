#ifndef MYCOURSE_H_
#define MYCOURSE_H_

#include <iostream>
#include <string>

using std::string;

class MyCourse {
  public:
    // constructors
    MyCourse();
    MyCourse(string name, string grade, int credits, string term);
    MyCourse(string name, string grade, int credits);

    // Setters
    int get_credits();
    string get_name();
    string get_grade();
    string get_term();

    // Getters
    void set_name(string name);
    void set_grade(string grade);
    void set_credits(int credits);
    void set_term(string term);
  protected:
    string course_name_;
  private:
    string course_final_grade_; // letter grade
    int course_credits_;
    string course_term_;
};
#endif // MYCOURSE_H_
