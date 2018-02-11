#include <iostream>
#include <string>
#include <fstream>

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
	Cell * head = NULL, *current, *newCell;
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
	newCell->nextPtr = NULL;
	file_students.close();
	return head;
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
}/*
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
	file_students.close();
}
/*
This function adds a lesson code and it's gradeto a student's passedlesson string
*/
int doesThisStudentAlreadyExist(char * stuNum);
void addingLessonGradeToStudent(Student AddingToPassed, char* AddedLessonCode, float AddedLessonGrade)
{
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
	return 1;
}

int main()
{
	/*The line below should be executed just once in the very first execution. then should be commented.*/
	//	createFilesForFirstExecution();
	//	newStudent("peymna", "hs", "12345");
	//	newStudent("salam","ali", "23456");
	//	newStudent("hadi", "haji", "44456");
	//	newStudent("peyman", "hosseini", "44477");
	newStudent("hadi", "haji", "44656");
	//createLinkListOfStudentsFile();
	//firstPanel();
	return 0;
}
