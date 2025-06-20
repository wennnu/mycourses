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
		string get_name();
		string get_grade();
		int get_credits();
		string get_term();

		// Getters
        	void set_name(string name);
		void set_grade(string grade);
		void set_credits(int credits);
		void set_term(string term);
	private:
		string c_grade; // letter grade
		int c_credits;
		string c_term;

	protected:
		string c_name;
};
#endif // MYCOURSE_H_
