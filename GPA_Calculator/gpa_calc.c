/*
 * gpa_calc.c
 *
 *  Created on: Dec 22, 2014
 *      Author: Amar Bhatt
 */


#include <stdio.h>
#include <string.h>
enum {
	A,Am,Bp,B,Bm,Cp,C,Cm,D,F
} grade_t;

struct course {
	char name[50];
	int credits;
	float grade;
};


float calculateGPA(const struct course courses[], int size, float grade_points, int units){

	float points = grade_points;
	float cred = units;
	int i;
	for (i = 0; i < size; i++){
		points += courses[i].credits * courses[i].grade;
		cred += courses[i].credits;
	}


	return points/cred;
}


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

void displayGradeMenu() {
	puts("(0) A\n(1) A-\n(2) B+\n(3) B\n(4) B-\n(5) C+\n(6) C\n(7) C-\n(8) D\n(9) F/W\n");
	return;
}
void getCourses(struct course courses[], int *size){
	struct course c;
	int grade;
	int credit;
	char stop = 'y';
	int i = 0;
	int result;
	char temp[50];

	puts("Get Courses!\n");
	while((stop == 'y') && (i < 8)){
		puts("Enter course name:");
		fgets(c.name, 50, stdin);
		puts("Enter number of credits:");
		fgets(temp, 50, stdin);
		result = sscanf(temp, "%2d", &credit);
		while (result != 1){
			puts("Read failed. Please enter a valid number:\n");
			fgets(temp, 50, stdin);
			result = sscanf(temp, "%2d", &credit);
		}
		c.credits = credit;
		puts("Enter expected grade:");
		displayGradeMenu();
		fgets(temp, 50, stdin);
		result = sscanf(temp,"%1d", &grade);
		while (result != 1){
			puts("Read failed. Please enter a valid number:\n");
			fgets(temp, 50, stdin);
			result = sscanf(temp,"%1d", &grade);
		}
		c.grade = getGradeValue(grade);
		strcpy(courses[i].name, c.name);
		courses[i].credits = c.credits;
		courses[i].grade = c.grade;
		i++;
		puts("Course Added!\nTo add another course press (y).\nPress Enter to exit.\n");
		stop = getchar();
		getchar();
	}
	*size = i;
}

// Remember to validate data
// Add a way for users to enter a GPA threshold and calculate scenarios to be above the threshold
int main (int argc, char ** argv){
	float grade_points;
	int result;
	int units;
	int i;
	int numCourses = 0;
	struct course courses[8];
	float gpa;
	char c;
	char temp[50];

	puts("Welcome to GPA Calculator!\n");
	puts("Enter your total grade points:\n");
	fgets(temp, 50, stdin);
	result = sscanf(temp,"%f",&grade_points);

	while (result != 1){
		puts("Read failed. Please enter a valid number:\n");
		fgets(temp, 50, stdin);
		result = sscanf(temp,"%f",&grade_points);
	}

	printf("You entered: %.3f grade points\n", grade_points);

	puts("Enter your total credits taken:\n");

	fgets(temp, 50, stdin);
	result = sscanf(temp,"%d",&units);

	while (result != 1){
		puts("Read failed. Please enter a valid number:\n");
		fgets(temp, 50, stdin);
		result = sscanf(temp,"%d",&units);
	}

	printf("You entered: %d credits\n", units);


	printf("Your Current GPA is: %.3f\n", grade_points/units);

	puts("To enter courses to calculate your estimated GPA press (y).\nOtherwise press enter.\n");
	c = getchar();
	if( c == 'y') {
		getchar();
		getCourses(courses, &numCourses);
		puts("List of Courses:\n");
		for (i = 0; i < numCourses; i++){
			printf("%d). %s Credits: %d Expected Grade: %.3f\n",i+1,courses[i].name, courses[i].credits, courses[i].grade);
		}
		gpa = calculateGPA(courses, numCourses, grade_points, units);
		printf("Your estimated GPA is %.3f\n", gpa);
	}
	puts("Press Enter to Exit...");
	getchar();

	return 0;
}
