# A GPA Calculator Project For Learning C++
MyCourse is a GPA calculator written fully in C++ based on [McGill University's Grading Scale](https://www.mcgill.ca/study/2024-2025/university_regulations_and_resources/undergraduate/gi_grading_and_grade_point_averages). The main purpose was not only for my personal use when I need to calculate my gpa in a course, but also applying my C++ knowledge into real practices.
I learned a lot about linking header files, structs/objects, dynamic array using pointers, writing lots of functions, selection/merge sort algorithms and formating code...etc. I used nvim as my text editor and followed google C++ style guide.
Although this was a very simple project, I had a lot of fun adding new ideas like saving to files, sort and search through files...etc. I am hoping to writter C++ code and learn all it can offer.

# To Use
You can download this localy, say, to a `~/download/` folder then going into `~/Project/MyCourses/` folder and use command `make` to compile and link the `.cpp` and `.h` files. Then you can run `./run`.

# Features

## Main Menu
The program will start off with a gui waiting for a single character input.

> [!NOTE]
> This program is not user prooved (yet) so make sure to type as intended.

`GPA`: it will calculate gpa based on the number of courses you entered. Normally it's 4 - 5 courses a semester. I use it to calculate term gpa.
`GRADE`: calculate grade required on the final exam to achieve target final grade in the course. This calculates your current grade excluding final exam.
`SUMMARY`: print a summary of all of the listed courses in a saved file. There is additional 4 summary display options. 
`Find Course`: enters a name of a course and it will return a summary of that course. It will return not found if not exist.

## GPA

Type in a single line for each of course information `course name/course final grade/course credits/term you took the course in`
For example: `chem 120/A/4/Winter 2025`

> [!IMPORTANT]
> It is important that you type in the information with the strict formatting shown. Make sure `term` is Season(first letter capitalized) with a space + Year.  

### Calculation
> GPA is the sum of (course credits x grade points) divided by the sum of credits.

At the end it will ask if you want to save to a file called `CourseFile` in the same format as you entered in one line.

## GRADE
Very similar to option GPA except it asks you for all of the graded assignments not including the final exam. It will ask for `weighting` and `grade` achived
then calculate the current grade for you. You then enter the final grade you wish to achieve in this course and final exam weighting for calculating grade required
on the final exam.

### Calculation
> current grade is the sum of the weighted grade (weighting x assignment grade)
> required grade on the final is the difference between the target grade and the current grade divided by the final weighting

## Find Course
Enter the name of the course you wish to find

> [!TIP]
> Make sure you type it exactly as it is saved, since it is case sensitive (for now)

It will return a summary with its course name, final grade, credits and term taken.

# Summary
There are 4 options when displaying the summary list from the file. You can display them by highest gpa, highest credits, by alphabetical names or by the term taken.

Default value is set to be `sort by gpa` if you input any other character.

> [!WARNING]
> This can be easily broken if the save file is not formatted correctly. Since all of the options are name sensitive

# Conclusion
MyCourse is a GPA calculator for my personal use at school and I stated it to learn how to code in C++. This has taught me most of the fundamental ideas and I look forward to
learn more about C++ and write better code in the future.
