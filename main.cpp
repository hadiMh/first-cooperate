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
	FILE* file_lesson = fopen("lessons.txt", "w");
	fclose(file_lessons);

}

int main()
{
	// The line below should be executed just once in the very first execution. then should be commented.
	createFilesForFirstExecution();
    return 0;
}
