#include <iostream>
#include <string>
#include<string.h>
#include <fstream>
#include <windows.h>
#include <sstream>
typedef struct student Student;
typedef struct lesson Lesson;
typedef struct cell Cell;
typedef struct lessonCell LessonCell;
using namespace std;

struct student {
	char stuNum[6];
	string firstname;
	string lastname;
	string passedLessons;
	float avg;
	int unitsSum;
};

struct lesson {
	char leassonCode[8];
	char lessonName[19];
	int lessonUnit;
	char lessonTeacher[21];
};

struct cell {
	struct student stuData;
	struct cell* nextPtr;
};
struct lessonCell
{
	struct lesson lessonData;
	struct lessonCell* nextPtr;
};

Cell* createLinkListOfStudentsFile()
{
	Student temp_student = { "", "", "", "", 0.0, 0 };
	ifstream file_students;
	file_students.open("students.txt");
	Cell * head = NULL, *current, *newCell = NULL;
	while (!file_students.eof())
	{
		file_students >> temp_student.firstname;
		file_students >> temp_student.lastname;
		file_students >> temp_student.stuNum;
		file_students >> temp_student.passedLessons;
		file_students >> temp_student.avg;
		file_students >> temp_student.unitsSum;
		if (strcmp(temp_student.stuNum, "") == 0)
		{
			break;
		}
		newCell = new cell;
		if (head == NULL)
		{
			head = newCell;
			head->nextPtr = NULL;
			strcpy(head->stuData.stuNum, temp_student.stuNum);
			head->stuData.firstname.assign(temp_student.firstname);
			head->stuData.lastname.assign(temp_student.lastname);
			head->stuData.passedLessons.assign(temp_student.passedLessons);
			head->stuData.avg = temp_student.avg;
			head->stuData.unitsSum = temp_student.unitsSum;
		}
		else
		{
			current->nextPtr = newCell;
			strcpy(newCell->stuData.stuNum, temp_student.stuNum);
			newCell->stuData.firstname.assign(temp_student.firstname);
			newCell->stuData.lastname.assign(temp_student.lastname);
			newCell->stuData.passedLessons.assign(temp_student.passedLessons);
			newCell->stuData.avg = temp_student.avg;
			newCell->stuData.unitsSum = temp_student.unitsSum;
		}
		current = newCell;
	}
	if (strcmp(temp_student.stuNum, "") != 0)
	{
		newCell->nextPtr = NULL;
	}
	file_students.close();
	return head;
}
int newStudent(string firstname, string lastname, char stuNum[]);
void printLinkListOfStudentsInStudentsFile(Cell* head)
{
	FILE* fileName = fopen("students.txt", "w");
	fclose(fileName);
	fstream file_students;
	file_students.open("students.txt");
	for (Cell* i = head; i != NULL; i = i->nextPtr)
	{
		file_students.seekp(0, ios::end);
		file_students << i->stuData.firstname << " " << i->stuData.lastname << " " << i->stuData.stuNum << " " << i->stuData.passedLessons << " " << i->stuData.avg << " " << i->stuData.unitsSum << '\n';
	}
	file_students.close();
}

/* Creating 'students' file and 'lessons' file at the very first execution.
This function should be executed once at the very first execution of the software so be careful.
After firs execution of the software comment this function's name in the 'main' scope*/
void createFilesForFirstExecution()
{
	FILE* file_students = fopen("students.txt", "w");
	fclose(file_students);
	FILE* file_lessons = fopen("lessons.txt", "w");
	fclose(file_lessons);

}
/*
frees the memory we have used from heep
*/
void PreventMemoryLeakProblem(Cell*head)
{
	Cell*temp;
	while (head != NULL)
	{
		temp = head;
		head = head->nextPtr;
		delete temp;
	}
}

/* delete cell from linkList that have this stuNum. This function returns 'Cell* head' */
Cell* deleteStudentCellFromLinkListWithThisStuNum(char stuNum[])
{
	Cell* head, *current, *previous;
	head = createLinkListOfStudentsFile();

	if (strcmp(head->stuData.stuNum, stuNum) == 0)
	{
		current = head->nextPtr;
		free(head);
		head = current;
		if (current == NULL)
		{
			FILE* empty = fopen("students.txt", "w");
			fclose(empty);

		}
		else
		{
			printLinkListOfStudentsInStudentsFile(current);
		}
		cout << "Deleted the student successfully" << endl;
		return head;
	}

	for (Cell* i = head; i != NULL; i = i->nextPtr)
	{
		if (strcmp(i->stuData.stuNum, stuNum) == 0)
		{
			previous->nextPtr = i->nextPtr;
			free(i);
			printLinkListOfStudentsInStudentsFile(head);
			cout << "Deleted the student successfully" << endl;
			return head;
		}
		previous = i;
	}
	cout << "No sudents with the entered student number existed" << endl;

	PreventMemoryLeakProblem(head);

}

void preventLeakfromLessons(LessonCell*head)
{
	LessonCell*temp;
	while (head != NULL)
	{
		temp = head;
		head = head->nextPtr;
		delete temp;
	}
}

/*
This function check wheter the lesson we are trying to add already exists or not
returns 1 if it doesn't exist
returns -1 if it already exists
*/
int doesThisLessonAlreadyExists(Lesson newSampleStructure, FILE*fileNewLesson)
{
	Lesson existingSamples;
	for (int i = 0; i<10000; i++)
	{
		fscanf(fileNewLesson, "%s %s %d %s\n", &existingSamples.leassonCode, &existingSamples.lessonName, &existingSamples.lessonUnit, &existingSamples.lessonTeacher);

		if (strcmp(existingSamples.leassonCode, newSampleStructure.leassonCode) == 0)
		{
			return -1;
		}
	}
	return 1;
}
/*
This function scans the information needed for creatng a new lesson
It returns 1 if it is created successfully
It returns -1 if it isn't created successfully
*/
int getInformationForCreatingNewLesson()
{
	FILE* fileNewLesson = fopen("lessons.txt", "r+");
	Lesson newSampleStructure, existingSamples;
	cout << "Please enter the lesson code (Remember the code must contain less than8 characters!) :" << endl;
	cin.get(newSampleStructure.leassonCode, 8);
	cin.ignore(10000, '\n');
	if (doesThisLessonAlreadyExists(newSampleStructure, fileNewLesson) == -1)
	{
		fclose(fileNewLesson);
		return -1;
	}
	cout << "Now you should enter the lesson name (Name contains at most 18 characters!) :" << endl;
	cin.get(newSampleStructure.lessonName, 19);
	cin.ignore(10000, '\n');
	cout << "Now you should enter the teacher's name:(At most 20 characters !) :" << endl;
	cin.getline(newSampleStructure.lessonTeacher, 21);
	cout << "And finally you should enter this lesson's units : " << endl;
	cin >> newSampleStructure.lessonUnit;
	cin.ignore(10000, '\n');
	fseek(fileNewLesson, 0, SEEK_END);
	fprintf(fileNewLesson, "%s %s %d %s\n", newSampleStructure.leassonCode, newSampleStructure.lessonName, newSampleStructure.lessonUnit, newSampleStructure.lessonTeacher);
	fclose(fileNewLesson);
	return 1;
}
/*
This function is used to create a new lesson
*/
void createNewLesson()
{
	if (getInformationForCreatingNewLesson() == 1)
		cout << "This Record has been successfully added!" << endl;
	else
		cout << "Adding a Lesson failed due to entering existing Lesson code!" << endl;
}
/*
This lesson check wheter the entered code was used before or not
if it existed in string passedlesson it returns -1
and returns 1 if it isn't used before in passedlesson string
*/
int extractingThePassedLessons(Student AddingToPassed, char* AddedLessonCode)
{
	char extractedCode[8];
	int j, k;
	float extractedGrade;
	for (int i = 0; i < AddingToPassed.passedLessons.size(); i++)
	{
		j = 0;
		for (; AddingToPassed.passedLessons[i] != '*'&&i<AddingToPassed.passedLessons.length(); i++)
		{
			if (AddingToPassed.passedLessons[i] != '/')
			{
				extractedCode[j] = AddingToPassed.passedLessons[i];
				j++;
			}
		}
		extractedCode[j] = NULL;
		for (; AddingToPassed.passedLessons[i] != '/'&&i<AddingToPassed.passedLessons.length(); i++);
		if (strcmp(AddedLessonCode, extractedCode) == 0)
		{
			return -1;
		}
	}
	return 1;
}
/*
This function returns the number of units of the lesson we want to add
and it helps us for calculating the average
*/
int numofAddedLessonUnits(Lesson newSampleStructure, FILE*fileNewLesson)
{
	rewind(fileNewLesson);
	int units;
	Lesson existingSamples;
	while (!feof(fileNewLesson))
	{
		fscanf(fileNewLesson, "%s %s %d %s\n", &existingSamples.leassonCode, &existingSamples.lessonName, &existingSamples.lessonUnit, &existingSamples.lessonTeacher);

		if (strcmp(existingSamples.leassonCode, newSampleStructure.leassonCode) == 0)
		{
			units = existingSamples.lessonUnit;
			return units;
		}
	}
}
/*
This function calls createLinkListOfStudentsFile and then modifies it with the new values needed!
*/
void linkListForAddingLessontoStudent(Student AddingToPassed)
{
	Cell * head = NULL, *current, *newCell;
	head = createLinkListOfStudentsFile();
	current = head;
	while (strcmp(current->stuData.stuNum, AddingToPassed.stuNum) != 0)
	{
		current = current->nextPtr;
	}
	current->stuData.avg = AddingToPassed.avg;
	current->stuData.unitsSum = AddingToPassed.unitsSum;
	current->stuData.passedLessons.assign(AddingToPassed.passedLessons);
	fstream file_students;
	file_students.open("students.txt");
	newCell = head;
	while (newCell != NULL)
	{
		file_students << newCell->stuData.firstname << " " << newCell->stuData.lastname << " " << newCell->stuData.stuNum << " " << newCell->stuData.passedLessons << " " << newCell->stuData.avg << " " << newCell->stuData.unitsSum << '\n';
		newCell = newCell->nextPtr;
	}
	PreventMemoryLeakProblem(head);
	file_students.close();
}

/*
finds the student that we want to add a grade to its passedlessons strings and returns its informations
existence of this student is check before in the functions that call this function
so no need to worry about student existence!
*/
Student findTheStudent(char*studentNumber)
{
	Student temp_student = { "", "", "", "/", 0.0, 0 };
	ifstream file_students;
	file_students.open("students.txt");
	while (!file_students.eof())
	{
		file_students >> temp_student.firstname >> temp_student.lastname >> temp_student.stuNum >> temp_student.passedLessons >> temp_student.avg >> temp_student.unitsSum;
		if (strcmp(studentNumber, temp_student.stuNum) == 0)
		{
			file_students.close();
			return temp_student;
		}
	}
}
/*
This function adds a lesson code and it's gradeto a student's passedlesson string
*/
int doesThisStudentAlreadyExist(char * stuNum);
void addingLessonGradeToStudent(char*studentNumber, char* AddedLessonCode, float AddedLessonGrade)
{
	Student AddingToPassed = { "", "", "", "/", 0.0, 0 };
	Lesson checkingLessonCode;
	FILE *checkingLesson = fopen("lessons.txt", "r+");
	strcpy(checkingLessonCode.leassonCode, AddedLessonCode);
	if (doesThisStudentAlreadyExist(AddingToPassed.stuNum) == 0)
	{
		cout << "There is no such a student!" << endl;
		return;
	}
	if (doesThisLessonAlreadyExists(checkingLessonCode, checkingLesson) == 1)
	{
		cout << "This Lesson Code doesn't exist!" << endl;
		return;
	}
	AddingToPassed = findTheStudent(studentNumber);
	if (extractingThePassedLessons(AddingToPassed, AddedLessonCode) == -1)
	{
		cout << "There is already a grade for this Lesson code for this student!" << endl;
		return;
	}
	AddingToPassed.avg = ((float)(AddingToPassed.avg*AddingToPassed.unitsSum + numofAddedLessonUnits(checkingLessonCode, checkingLesson)*AddedLessonGrade)) / (numofAddedLessonUnits(checkingLessonCode, checkingLesson) + AddingToPassed.unitsSum);
	AddingToPassed.unitsSum += numofAddedLessonUnits(checkingLessonCode, checkingLesson);
	AddingToPassed.passedLessons += AddedLessonCode;
	AddingToPassed.passedLessons += "*";
	ostringstream convertor;
	convertor << AddedLessonGrade;
	string result(convertor.str());
	AddingToPassed.passedLessons += result;
	AddingToPassed.passedLessons += "/";
	fclose(checkingLesson);
	linkListForAddingLessontoStudent(AddingToPassed);
	cout << "Lesson added for this student successfully!" << endl;
}
/*
By executing this function you will be shown information of all the students sorted by their last name
*/
void functionNumber4()
{
	Cell * head, *current, *newCell;
	head = createLinkListOfStudentsFile();
	current = head;
	Student temp;
	for (Cell*i = head; i->nextPtr != NULL; i = i->nextPtr)
	{
		for (Cell*j = i->nextPtr; j != NULL; j = j->nextPtr)
			if (j->stuData.lastname < i->stuData.lastname || (j->stuData.lastname == i->stuData.lastname&&j->stuData.firstname<i->stuData.firstname))
			{
				temp = i->stuData;
				i->stuData = j->stuData;
				j->stuData = temp;
			}
	}
	for (Cell*i = head; i != NULL; i = i->nextPtr)
	{
		cout << "Name: " << i->stuData.firstname << " Last Name: " << i->stuData.lastname << " ID Number: " << i->stuData.stuNum
			<< " GPA: " << i->stuData.avg << endl;
	}
	PreventMemoryLeakProblem(head);
}

/* This function sorts all the students by their stuNum and prints them in the console */
void sortWithStuNum()
{
	Student tempStudent;
	Cell * head, *current, *newCell;
	head = createLinkListOfStudentsFile();
	for (current = head; current != NULL; current = current->nextPtr)
	{
		for (Cell* i = current->nextPtr; i != NULL; i = i->nextPtr)
		{
			if (strcmp(current->stuData.stuNum, i->stuData.stuNum) < 0)
			{
				tempStudent = current->stuData;
				current->stuData = i->stuData;
				i->stuData = tempStudent;
			}
		}
	}
	for (Cell* i = head; i != NULL; i = i->nextPtr)
	{
		cout << "Name: " << i->stuData.firstname << " Last Name: " << i->stuData.lastname << " ID Number: " << i->stuData.stuNum
			<< " GPA: " << i->stuData.avg << endl;
	}
	PreventMemoryLeakProblem(head);
}

/* This function prints the first three person gained the toppest avg */
void showThreeTopAvgStudents()
{
	Student tempStudent, firstStudent, secondStudent, thirdStudent;
	firstStudent.avg = secondStudent.avg = thirdStudent.avg = 0;
	Cell * head, *current, *newCell;
	head = createLinkListOfStudentsFile();
	for (Cell* i = head; i != NULL; i = i->nextPtr)
	{
		if (i->stuData.avg > firstStudent.avg)
		{
			thirdStudent = secondStudent;
			secondStudent = firstStudent;
			firstStudent = i->stuData;
		}
		else if (i->stuData.avg > secondStudent.avg)
		{
			thirdStudent = secondStudent;
			secondStudent = i->stuData;
		}
		else if (i->stuData.avg > thirdStudent.avg)
			thirdStudent = i->stuData;
	}
	tempStudent = firstStudent;
	if (tempStudent.avg > 0)
	{
		cout << "1- " << "Name: " << tempStudent.firstname << " Last Name: " << tempStudent.lastname << " ID Number: " << tempStudent.stuNum
			<< " GPA: " << tempStudent.avg << endl;
	}
	else
	{
		cout << "Not valid grades yet to show the first student" << endl;
	}
	tempStudent = secondStudent;
	if (tempStudent.avg > 0)
	{
		cout << "2- " << "Name: " << tempStudent.firstname << " Last Name: " << tempStudent.lastname << " ID Number: " << tempStudent.stuNum
			<< " GPA: " << tempStudent.avg << endl;
	}
	else
	{
		cout << "Not valid grades exist to show the second student" << endl;
	}
	tempStudent = thirdStudent;
	if (tempStudent.avg > 0)
	{
		cout << "3- " << "Name: " << tempStudent.firstname << " Last Name: " << tempStudent.lastname << " ID Number: " << tempStudent.stuNum
			<< " GPA: " << tempStudent.avg << endl;
	}
	else
	{
		cout << "Not valid grades exist to show the third student" << endl;
	}
	PreventMemoryLeakProblem(head);
}

/* This function shows the students that their unitsSum is lower than 14 */
void showStudentsWithUnitsSumUnder14()
{
	Student tempStudent;
	Cell* head, *current, *newCell;
	head = createLinkListOfStudentsFile();
	for (Cell * i = head; i != NULL; i = i->nextPtr)
	{
		if (i->stuData.unitsSum < 14)
		{
			tempStudent = i->stuData;
			cout << "1- " << "Name: " << tempStudent.firstname << " Last Name: " << tempStudent.lastname << " ID Number: " << tempStudent.stuNum << " GPA: " << tempStudent.avg << endl;
		}
	}
}

/*
By executing this function you'll be shown students whose GPA is lower than 12
*/
void functionNumber6()
{
	Cell * head, *current, *newCell;
	head = createLinkListOfStudentsFile();
	current = head;
	Student temp;
	for (Cell*i = head; i != NULL; i = i->nextPtr)
	{
		if (i->stuData.avg <12)
		{
			cout << "Name: " << i->stuData.firstname << " Last Name: " << i->stuData.lastname << " ID Number: " << i->stuData.stuNum
				<< " GPA: " << i->stuData.avg << endl;
		}
	}
	PreventMemoryLeakProblem(head);
}
/*
This function creates a linklist from the lessons in the lessons.txt
*/
LessonCell* creatingLinkListOfLessonsFile()
{
	Lesson temp_lesson = { "", "", 0, "" };
	FILE* file_lessons = fopen("lessons.txt", "r+");
	LessonCell * head = NULL, *current, *newCell;
	while (!feof(file_lessons))
	{
		fscanf(file_lessons, "%s %s %d %s\n", &temp_lesson.leassonCode, &temp_lesson.lessonName, &temp_lesson.lessonUnit, &temp_lesson.lessonTeacher);
		newCell = new LessonCell;
		if (head == NULL)
		{
			head = newCell;
			strcpy(head->lessonData.leassonCode, temp_lesson.leassonCode);
			strcpy(head->lessonData.lessonName, temp_lesson.lessonName);
			strcpy(head->lessonData.lessonTeacher, temp_lesson.lessonTeacher);
			head->lessonData.lessonUnit = temp_lesson.lessonUnit;
		}
		else
		{
			strcpy(newCell->lessonData.leassonCode, temp_lesson.leassonCode);
			strcpy(newCell->lessonData.lessonName, temp_lesson.lessonName);
			strcpy(newCell->lessonData.lessonTeacher, temp_lesson.lessonTeacher);
			newCell->lessonData.lessonUnit = temp_lesson.lessonUnit;
			current->nextPtr = newCell;
		}
		current = newCell;
	}
	newCell->nextPtr = NULL;
	fclose(file_lessons);
	return head;
}


/*
This function is called to write the new lesson(after deleting one of them) on the related file(lessons.txt)
*/
void writingNewLessonsinFileAfterDeletion(LessonCell*head)
{
	FILE*lessonsFile = fopen("lessons.txt", "w");
	for (LessonCell*temp = head; temp != NULL; temp = temp->nextPtr)
	{
		fprintf(lessonsFile, "%s %s %d %s\n", temp->lessonData.leassonCode, temp->lessonData.lessonName, temp->lessonData.lessonUnit, temp->lessonData.lessonTeacher);
	}
	fclose(lessonsFile);
}
/*
This function Deletes a Lesson from the related file(lessons.txt)
*/
void lessonDelete(char* wantingtobeDeletedLessonCode)
{
	FILE*lessonsFile = fopen("lessons.txt", "r+");
	Lesson checkExistence = { "", "", 0, "" };
	strcpy(checkExistence.leassonCode, wantingtobeDeletedLessonCode);
	if (doesThisLessonAlreadyExists(checkExistence, lessonsFile) == 1)
	{
		cout << "There is no such a lesson code to delete!" << endl;
		fclose(lessonsFile);
		return;
	}
	LessonCell *head, *temp;
	LessonCell*i;
	head = creatingLinkListOfLessonsFile();
	if (strcmp(head->lessonData.leassonCode, wantingtobeDeletedLessonCode) != 0)
	{
		for (i = head; strcmp(i->nextPtr->lessonData.leassonCode, wantingtobeDeletedLessonCode) != 0; i = i->nextPtr);
		temp = i->nextPtr->nextPtr;
		i->nextPtr = temp;
	}
	else
	{
		temp = head->nextPtr;
		head = temp;
	}
	fclose(lessonsFile);
	writingNewLessonsinFileAfterDeletion(head);
	cout << "This record is Deleted successfully" << endl;
	preventLeakfromLessons(head);
	fclose(lessonsFile);
	return;
}
void function10(char *stunum)
{

	if (doesThisStudentAlreadyExist(stunum) == 0)
	{
		cout << "There is no such a student!" << endl;
		return;
	}
	Cell*head, *i;
	head = createLinkListOfStudentsFile();
	for (i = head; strcmp(i->stuData.stuNum, stunum) != 0; i = i->nextPtr);
	cout << "First Name :" << i->stuData.firstname << " Last Name: " << i->stuData.lastname << " GPA: " << i->stuData.avg << endl;
	cout << "Student Number: " << i->stuData.stuNum << endl;
	cout << "Passed Lesson:  " << i->stuData.passedLessons << endl << endl << endl << endl;
	PreventMemoryLeakProblem(head);
}
enum colors { darkblue = 1, darkgreen, lessdarkblue, darkred, darkpink, darkyellow, darkwhite, gray, blue, green, blueandgreen, red, pink, yellow, white };
HANDLE hconsole;
void firstPanel()
{
	string stu_first_name, stu_last_name;
	char stunum[6];
	char studentNumber[6];
	char lessonCode[8];
	float lessonGrade;
	char deletingStudentNumber[8];
	char student_Number[6];
	char deletingLessonCode[8];
	int inputNumber;
	hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	while (1)
	{
		SetConsoleTextAttribute(hconsole, white);
		cout << " Please choose an action:" << endl << endl;
		SetConsoleTextAttribute(hconsole, pink);
		cout << " 1 - Add a new student to students.txt" << endl;
		cout << " 2 - Insert a lesson for a student" << endl;
		cout << " 3 - Add a new lesson to lessons.txt" << endl;
		cout << " 4 - Show Name,Student number and GPA of all the students sorted by their lastname" << endl;
		cout << " 5 - Show Name,Student number and GPA of all the students sorted by their student number" << endl;
		cout << " 6 - Show Name,Student number and GPA of all the students whose GPA is lower than 12" << endl;
		cout << " 7 - Show Name,Student number and GPA of The first,The second,and The third Student according to GPA" << endl;
		cout << " 8 - Show Name,Student number and GPA of all the students that have passed less than 14 units " << endl;
		cout << " 9 - delete a student from students.txt" << endl;
		cout << " 10 - show a student information" << endl;
		cout << " 11 - delete a lesson from lessons.txt" << endl;
		cout << " 12 - exit" << endl;
		SetConsoleTextAttribute(hconsole, darkwhite);
		cin >> inputNumber;
		cin.ignore(10000, '\n');
		switch (inputNumber)
		{
		case 1:
			cout << "Please enter the student first name :" << endl;
			cin >> stu_first_name;
			cin.ignore(10000, '\n');
			cout << "Now please enter the student last name :" << endl;
			cin >> stu_last_name;
			cin.ignore(10000, '\n');
			cout << "And finally you shoul enter the student number :" << endl;
			cin >> stunum;
			cin.ignore(10000, '\n');
			newStudent(stu_first_name, stu_last_name, stunum);
			break;
		case 2:

			cout << "First enter the student number you want to add a Grade for" << endl;
			cin >> studentNumber;
			cin.ignore(10000, '\n');
			cout << "Now please enter the lesson code " << endl;
			cin >> lessonCode;
			cin.ignore(10000, '\n');
			cout << "And Finally please enter the Grade you want to add for this student" << endl;
			cin >> lessonGrade;
			addingLessonGradeToStudent(studentNumber, lessonCode, lessonGrade);
			break;
		case 3:createNewLesson();
			break;
		case 4:functionNumber4();
			break;
		case 5:sortWithStuNum();
			break;
		case 6:functionNumber6();
			break;
		case 7:showThreeTopAvgStudents();
			break;
		case 8: showStudentsWithUnitsSumUnder14();
			break;
		case 9:
			cout << "Please enter the Student number you want to delete it's record" << endl;
			cin >> deletingStudentNumber;
			cin.ignore(10000, '\n');
			if (doesThisStudentAlreadyExist(deletingStudentNumber) == 0)
			{
				cout << "There is no such student to delete" << endl;
			}
			else
				deleteStudentCellFromLinkListWithThisStuNum(deletingStudentNumber);
			break;
		case 10:

			cout << "Please enter the student number that you want to see his/her informations" << endl;
			cin >> student_Number;
			cin.ignore(10000, '\n');
			function10(student_Number);
			break;
		case 11:
			cout << "Please enter the lesson code you want to delete it's record" << endl;
			cin >> deletingLessonCode;
			cin.ignore(10000, '\n');
			lessonDelete(deletingLessonCode);
			break;
		case 12:
			exit(0);
		}
	}
}
/* This function checks if a student with the "stuNum" student number exist in 'students.txt database or not.
return 1: already exist.
return 0: doesn't exist */
int doesThisStudentAlreadyExist(char * stuNum)
{
	Student temp_student = { "", "", "", "/", 0.0, 0 };
	ifstream file_students;
	file_students.open("students.txt");
	while (!file_students.eof())
	{
		file_students >> temp_student.firstname >> temp_student.lastname >> temp_student.stuNum >> temp_student.passedLessons >> temp_student.avg >> temp_student.unitsSum;
		if (strcmp(stuNum, temp_student.stuNum) == 0)
		{
			return 1;
		}
	}
	file_students.close();
	return 0;
}
/* This function create a new student in the 'students.txt' file.
Notice that this function's type isn't void and it return a number.
If the student Already exist in database it will return -1.
If the insertation was successful it will return 1.*/
int newStudent(string firstname, string lastname, char stuNum[])
{
	Student temp_student = { "", "", "", "/", 0.0, 0 };
	if (doesThisStudentAlreadyExist(stuNum) == 1)
	{
		cout << "This student couldn't be added because already a student with that student number exists!" << endl;
		return -1;
	}
	temp_student.firstname = firstname;
	temp_student.lastname = lastname;
	strcpy(temp_student.stuNum, stuNum);
	temp_student.passedLessons = "/"; /* just for emphasis */
	temp_student.avg = 0.0; /* just for emphasis */
	temp_student.unitsSum = 0; /* just for emphasis */
	fstream file_students;
	file_students.open("students.txt");
	file_students.seekp(0, ios::end);
	file_students << temp_student.firstname << " " << temp_student.lastname << " " << temp_student.stuNum << " " << temp_student.passedLessons << " " << temp_student.avg << " " << temp_student.unitsSum << '\n';
	file_students.close();
	cout << "Student added successfully" << endl;
	return 1;
}

int main()
{
	/*
	Please notice createFilesForFirstExecution must be executed only once and then you should comment it
	*/
	/*only one time execute this*/createFilesForFirstExecution();/*only one time execute this*/
	firstPanel();
	return 0;
}