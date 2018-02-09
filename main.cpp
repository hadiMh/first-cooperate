#include <iostream>
#include <string>
#include <fstream>

typedef struct student Student;
typedef struct lesson Lesson;
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
			cout << "THis lesson code already exists!" << endl;
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
void firstPanel()
{
	int inputNumber;
	cout << " Please choose an action:" << endl << endl;
	cout << " 1 - new student" << endl;
	cout << " 2 - lesson insertion for a student" << endl;
	cout << " 3 - new lesson" << endl;
	cout << " 4 - " << endl;
	cout << " 5 - " << endl;
	cout << " 6 - " << endl;
	cout << " 7 - " << endl;
	cout << " 8 - " << endl;
	cout << " 9 - delete a student" << endl;
	cout << " 10- show a student information" << endl;
	cout << " 11- delete a lesson" << endl;
	cout << " 12- exit" << endl;
	cin >> inputNumber;
	switch (inputNumber)
	{
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
		break;
	case 10:
		break;
	case 11:
		break;
	case 12:
		break;
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
	for (int i = 0; i<10000; i++)
	{
		file_students >> temp_student.stuNum >> temp_student.firstname >> temp_student.lastname >> temp_student.passedLessons >> temp_student.avg >> temp_student.unitsSum;
		if (strcmp(stuNum, temp_student.stuNum) == 0)
			return 1;
	}
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
		return -1;
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
	return 1;

}

int main()
{
	// The line below should be executed just once in the very first execution. then should be commented.
	//	createFilesForFirstExecution();
	//	newStudent("peymna", "hs", "12345");
	//	newStudent("salam","ali", "23456");
	//	newStudent("hadi", "haji", "44456");
	newStudent("peyman", "hosseini", "44477");

	//firstPanel();
	return 0;
}