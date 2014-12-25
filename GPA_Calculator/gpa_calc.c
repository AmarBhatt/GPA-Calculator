/*
 *  Author: Amar Bhatt
 *  Created on: Dec 22, 2014
 *
 *  File: gpa_calc.c
 *  Project: GPA Calculator
 *
 *  Description:  Program that takes user input to
 *  			  calculate current and estimated GPA
 *
 *
 */


#include <stdio.h>
#include <string.h>

// Enum for Grades
enum {
	A,Am,Bp,B,Bm,Cp,C,Cm,D,F
} grade_t;

/*
 * Structure for course
 *
 *  name ->    Name of the course (limit 50 characters)
 *  credits -> Integer value of number of credits the
 *  		   course is worth
 *  grade ->   Float value of the estimated grade in the
 *  		   class *
 */
struct course {
	char name[50];
	int credits;
	float grade;
};


/*
 * displayCourses
 *
 * Formats user entered courses into an asthetically pleasing
 * view
 *
 * courses[] -> Array of course structs
 * size -> Number of courses
 */
void displayCourses(struct course courses[], int size){
	int i;
	puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++"); // 54
	puts("+                                                    +");
	puts("+                      Courses                       +");
	puts("+                                                    +");
	puts("+----------------------------------------------------+");
	for (i = 0; i < size; i++){
		//puts("+                                                    +");
		printf("\t%d).%s\t\tCredits: %d\tExpected Grade: %.3f\n",i+1,courses[i].name, courses[i].credits, courses[i].grade);
		//puts("+                                                    +");
		puts("+----------------------------------------------------+");
	}
}

/*
 * calculateGPA
 *
 * Calculates estimated GPA using estimated course grades and current GPA
 *
 * courses[] -> Array of course structs
 * size -> Number of courses
 * grade_points -> Current grade points user has
 * units -> Current amount of units the user has
 */
float calculateGPA(const struct course courses[], int size, float grade_points, int units){
	float points = grade_points;
	float cred = units;
	int i;
	for (i = 0; i < size; i++){
		points += courses[i].credits * courses[i].grade; // add to the total points
		cred += courses[i].credits; // add to the total credits
	}
	return points/cred; // GPA = Grade Points / Number of Credits
}

/*
 * getGradeValue
 *
 * Helper function for course entry, returns the real value of the passed in grade
 *
 * grade -> Enum value representing letter grade
 */
float getGradeValue(int grade){
	switch (grade){
		case A :
			return 4.000;
		case Am :
			return 3.667;
		case Bp :
			return 3.333;
		case B :
			return 3.000;
		case Bm :
			return 2.667;
		case Cp :
			return 2.333;
		case C :
			return 2.000;
		case Cm :
			return 1.667;
		case D :
			return 1.000;
		case F :
			return 0.000;
	}
	return -1;
}

/*
 * displayGradeMenu
 *
 * Displays formated grade menu for user to choose grade
 */
void displayGradeMenu() {
	puts("\t\t(0) A\t(4.000)\n\t\t(1) A-\t(3.667)\n\t\t(2) B+\t(3.333)\n\t\t(3) B\t(3.000)\n\t\t(4) B-\t(2.667)\n\t\t(5) C+\t(2.333)\n\t\t(6) C\t(2.000)\n\t\t(7) C-\t(1.667)\n\t\t(8) D\t(1.000)\n\t\t(9) F/W\t(0.000)\n");
	return;
}

/*
 * getCourses
 *
 * Prompts user to enter in up to 8 courses with credits and estimated grade
 *
 * courses[] -> Array of course structs
 * size -> Pointer to number of courses added at the end of the function
 */
void getCourses(struct course courses[], int *size){
	struct course c; // temporary struct to store current entered course
	int grade;
	int credit;
	char stop = 'y'; // if not y then stop
	int i = 0;
	int result; //temp variable for detecting success of user input
	char temp[50]; // temp variable to get user input from stdin

	while((stop == 'y') && (i < 8)){ // if user did not press y or if 8 courses have been added, break
		// Get course name
		printf("\n");
		printf("\tDetails for Course %d\n\n", i+1);
		puts("\t[A]\tEnter course name:");
		printf("\t\t");
		fgets(c.name, 50, stdin);
		// Get number of credits
		printf("\n");
		puts("\t[B]\tEnter number of credits:");
		printf("\t\t");
		fgets(temp, 50, stdin);
		result = sscanf(temp, "%2d", &credit); // format user input
		while (result != 1){ //Prompt user if invalid
			puts("\t\tRead failed. Please enter a valid number:");
			printf("\t\t");
			fgets(temp, 50, stdin);
			result = sscanf(temp, "%2d", &credit);
		}
		c.credits = credit; // store credit into temp variable
		// Get estimated grade
		printf("\n");
		puts("\t[C]\tChoose expected grade (type the number next to the grade):");
		displayGradeMenu(); // display options
		printf("\t\t");
		fgets(temp, 50, stdin);
		result = sscanf(temp,"%1d", &grade); // format user input
		while (result != 1){ // Prompt user if invalid
			puts("\t\tRead failed. Please enter a valid number:");
			printf("\t\t");
			fgets(temp, 50, stdin);
			result = sscanf(temp,"%1d", &grade);
		}
		c.grade = getGradeValue(grade);// store grade into temp variable
		// Store temp struct course into courses array
		strcpy(courses[i].name, c.name);
		courses[i].credits = c.credits;
		courses[i].grade = c.grade;
		i++; // Add 1 to the number of courses added
		//Prompt user to enter another course
		printf("\nCourse Added!\n\n[%d]\tTo add another course press (y).\n\tOtherwise press enter to exit course addition.\n", i+3);
		printf("\t");
		stop = getchar(); // get user input
		getchar(); //clear buffer of Enter
	}
	*size = i; // store number of courses for return
}
/*
 * main
 *
 * Carries out the main flow for user.  Prompts user to input data to calculate GPA
 */
int main (int argc, char ** argv){
	float grade_points; // total number of grade points
	int result; // temp variable for detecting success of user input
	int units; // number of credits taken
	int numCourses = 0; // number of courses
	struct course courses[8]; // list of courses
	float gpa;
	char c; // used to detect whether courses are needed to be entered
	char temp[50]; // temp variable to get user input from stdin

	//Start Program
	puts("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"); // 80
	puts("+                                   Welcome                                   +");
	puts("+                                     to                                      +");
	puts("+                                GPA Calculator                               +");
	puts("+-----------------------------------------------------------------------------+");
	puts("+                                    RULES                                    +");
	puts("+                         Follow the on screen prompts.                       +");
	puts("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
	puts("\n");
	// Get Current Grade Points
	puts("[1]\tEnter your total grade points:");
	printf("\t");
	fgets(temp, 50, stdin); // get user input
	result = sscanf(temp,"%f",&grade_points); // format user input
	while (result != 1){ // Prompt if invalid input
		puts("\tRead failed. Please enter a valid number:");
		printf("\t");
		fgets(temp, 50, stdin); // read input again
		result = sscanf(temp,"%f",&grade_points); // format user input
	}
	printf("\nYou entered: %.3f grade points\n\n", grade_points); // echo user input and round to 3 decimal places

	// Get Current Credits Taken
	puts("[2]\tEnter your total credits taken:");
	printf("\t");
	fgets(temp, 50, stdin); // get user input
	result = sscanf(temp,"%d",&units); // format user input
	while (result != 1){ // Prompt if invalid input
		puts("\tRead failed. Please enter a valid number:");
		printf("\t");
		fgets(temp, 50, stdin); // read input again
		result = sscanf(temp,"%d",&units); // format user input
	}

	printf("\nYou entered: %d credits\n", units); // echo user input
	printf("\nYour Current GPA is: %.3f\n\n", grade_points/units); //Calculate current GPA; GPA = Grade Points/Credits Taken
	// Ask user if they want to enter courses
	puts("[3]\tPress 'y' to enter courses to calculate your estimated GPA.\n\tOtherwise press enter.\n");
	printf("\t");
	c = getchar();
	if( c == 'y') { // if yes (c='y') then add courses
		getchar(); // clear input
		getCourses(courses, &numCourses); // get courses
		displayCourses(courses, numCourses); // display entered courses
		gpa = calculateGPA(courses, numCourses, grade_points, units); // calculate new gpa
		printf("Your estimated GPA is %.3f\n\n\n", gpa); // echo estimated gpa round to 3 decimal places
	}
	puts("Press Enter to Exit..."); // Prompt user to press enter before exiting so they can view results
	getchar();

	return 0;
}
