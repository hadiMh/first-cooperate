#include <iostream>
#include <string>
typedef struct student Student;
typedef struct lesson Lesson;
using namespace std;

struct student {
    long long int stuNum;
    string firstname;
    string lastname;
    string passedLessons;
};

struct lesson {
    char leassonCode[8];
    char lessonName[19];
    int lessonUnit;
    char lessonTeacher[21];
};

/* Creating 'students' file and 'lessons' file at the very first execution.
   This function should be executed once at the very first execution of the software so be careful.
   After firs execution of the software comment this function's name in the 'main' scope*/
void createFilesForFirstExecution()
{
	FILE* file_students = fopen("students.txt","w");
	fclose(file_students);
	FILE* file_lessons = fopen("lessons.txt", "w");
	fclose(file_lessons);

}
/*
	This function adds a lesson to lesson.txt
*/
void Create_New_Lesson()
{
	Lesson New_sample_structure, Existing_samples;
	FILE* File_New_Lesson = fopen("lessons.txt", "r+");

	cout << "Please enter the lesson code (Remember the password must contain less than8 characters!) :" << endl;
	cin.get(New_sample_structure.leassonCode, 8);
	cin.ignore(10000, '\n');
	while (!feof(File_New_Lesson))
	{
		fread(&Existing_samples, sizeof(Lesson), 1, File_New_Lesson);
		if (strcmp(Existing_samples.leassonCode, New_sample_structure.leassonCode) == 0)
		{
			cout << "THis lesson code already exists!" << endl;
			fseek(File_New_Lesson, 0, SEEK_SET);
			cout << "Please enter the lesson code again(Remember the password must contain less than8 characters!) :" << endl;
			cin.get(New_sample_structure.leassonCode, 8);
			cin.ignore(10000, '\n');
		}
	}
	cout << "Now you should enter the lesson name (Name contains at most 18 characters!) :" << endl;
	cin.get(New_sample_structure.lessonName, 19);
	cin.ignore(10000, '\n');
	cout << "Now you should enter the teacher's name:(At most 20 characters !) :" << endl;
	cin.getline(New_sample_structure.lessonTeacher, 21);
	cout << "And finally you should enter this lesson's units : " << endl;
	cin >> New_sample_structure.lessonUnit;
	cin.ignore(10000, '\n');
	fseek(File_New_Lesson, 0, SEEK_END);
	fwrite(&New_sample_structure, sizeof(Lesson), 1, File_New_Lesson);
	fclose(File_New_Lesson);
}

void firstPanel()
{
    int inputNumber;
    cout<<" Please choose an action:"<<endl<<endl;
    cout<<" 1 - new student"<<endl;
    cout<<" 2 - lesson insertion for a student"<<endl;
    cout<<" 3 - new lesson"<<endl;
    cout<<" 4 - "<<endl;
    cout<<" 5 - "<<endl;
    cout<<" 6 - "<<endl;
    cout<<" 7 - "<<endl;
    cout<<" 8 - "<<endl;
    cout<<" 9 - delete a student"<<endl;
    cout<<" 10- show a student information"<<endl;
    cout<<" 11- delete a lesson"<<endl;
    cout<<" 12- exit"<<endl;
    cin>>inputNumber;
    switch(inputNumber)
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
   return 1: if exist.
   return 0: if doesn't exist */
int doasThisStudentAlreadyExist(string stuNum)
{
	Student temp_student = {0,"","",""};
	FILE* file_students = fopen("students.txt","r");
    fseek(file_students, sizeof(Student)*stuNum, SEEK_SET);
    fread(&temp_student, sizeof(Student), file_students);
    fclose(file_students);
    if(stuNum == temp_student.stuNum)
        return 1;
    return 0;
}

/* This function create a new student in the 'students.txt' file.
   Notice that this function's type isn't void and it return a number.
   If the student Already exist in database it will return 0.
   If the insertation was successful it will return 1.*/
int newStudent(string firstname, string lastname, long long int stuNum)
{
	Student temp_student = {0,"","",""};
	if(doasThisStudentAlreadyExist == 1)
	    return 0;
	temp_student.firstname = firstname;
	temp_student.lastname = lastname;
	temp_student.stuNum = stuNum;
	temp_student.passedLessons = ""; /* just for emphasis */
	FILE* file_students = fopen("students.txt","r+");
	fseek(file_students, sizeof(Student)*stuNum, SEEK_SET);
	fwrite(&temp_student, sizeof(Student), file_students);
	fclose(file_students);
	return 1;
}

int main()
{
	// The line below should be executed just once in the very first execution. then should be commented.
	createFilesForFirstExecution();
	firstPanel();
    return 0;
}
