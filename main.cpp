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
	Student pattern_student = {0,"","",""};
	FILE* file_students = fopen("students.txt","w");
	for (long long int i = 0; i < 1000000; i++)
	   fwrite(&pattern_student, sizeof(Student), 1, file_students);
	fclose(file_students);
	FILE* file_lessons = fopen("lessons.txt", "w");
	fclose(file_lessons);

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



int main()
{
	// The line below should be executed just once in the very first execution. then should be commented.
	createFilesForFirstExecution();
	firstPanel();
    return 0;
}
