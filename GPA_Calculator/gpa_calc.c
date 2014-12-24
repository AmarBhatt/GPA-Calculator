/*
 * gpa_calc.c
 *
 *  Created on: Dec 22, 2014
 *      Author: Amar
 */


#include <stdio.h>
#include <string.h>
enum {
	A,Am,Bp,B,Bm,Cp,C,Cm,D,F,W
} grade_t;

struct course {
	char name[20];
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
		case W :
			return 0.000;
	}
	return -1;
}

void displayGradeMenu() {
	puts("(0) A\n(1) A-\n(2) B+\n(3) B\n(4) B-\n(5) C+\n(6) C\n(7) C-\n(8) D\n(9) F\n(10) W\n");
	return;
}
void getCourses(struct course courses[], int *size){
	struct course c;
	int grade;
	int credit;
	char stop = 'y';
	int i = 0;

	puts("Get Courses!\n");
	while((stop == 'y') && (i < 8)){
		puts("Enter course name:");
		fgets(c.name, 20, stdin);
		puts("Enter number of credits:");
		scanf("%d", &credit);
		c.credits = credit;
		puts("Enter expected grade:");
		displayGradeMenu();
		scanf("%d", &grade);
		c.grade = getGradeValue(grade);
		//validate c
		strcpy(courses[i].name, c.name);
		courses[i].credits = c.credits;
		courses[i].grade = c.grade;
		i++;
		puts("Course Added!\nTo add another course press (y).\n Press Enter to exit.\n");
		getchar();
		stop = getchar();
		getchar();
	}
	*size = i;
}


int main (int argc, char ** argv){
	float grade_points;
	int result;
	int units;
	int i;
	int numCourses = 0;
	struct course courses[8];
	float gpa;
	char c;

	puts("Welcome to GPA Calculator!\n");
	puts("Enter your total grade points:\n");

	result = scanf("%f",&grade_points);
	if (result == EOF){
		puts("Read failed");
	}else if (result == 0){
		puts("Nothing was read");
	}else{
		printf("You entered: %f\n", grade_points);
		getchar(); // Clear buffer of the \n

	}
	puts("Enter your total credits taken:\n");

	result = scanf("%d",&units);
	if (result == EOF){
		puts("Read failed");
	}else if (result == 0){
		puts("Nothing was read");
	}else{
		printf("You entered: %d\n", units);
		getchar(); // Clear buffer of the \n
	}

	printf("Your Current GPA is: %f\n", grade_points/units);

	/*puts("Enter grade:");
	int grade;
	float real;
	displayGradeMenu();
	scanf("%d", &grade);

	real = getGradeValue(grade);
	printf("Grade is %f", real);
	getchar();*/
	puts("To enter to courses press (y).\n");
	c = getchar();
	if( c == 'y') {
		getchar();
		getCourses(courses, &numCourses);
	}
	for (i = 0; i < numCourses; i++){
		printf("Course %d: %s Credits %d Expected Grade %f\n",i,courses[i].name, courses[i].credits, courses[i].grade);
	}

	gpa = calculateGPA(courses, numCourses, grade_points, units);
	// Remember to validate data
	// Add a way for users to enter a GPA threshold and calculate scenarios to be above the threshold

	printf("Your estimated GPA is %f\n", gpa);
	puts("Press Enter to Exit...");
	getchar();

	return 0;
}
