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
void meghdardehiavvalie()
{
	/*
	please execute this function in <<main>> only once and the comment it.

	*/
	Student pattern_student = {0,"","",""};
	FILE *file_student=fopen("student.txt","w");
	for (long long int i = 0; i < 1000000; i++)
	{
		fwrite(&pattern_student, sizeof(Student), 1, file_student);
	}
	fclose(file_student);
	FILE *file_lesson = fopen("course.txt", "w");
	fclose(file_lesson);

}
int main()
{
	meghdardehiavvalie();
    return 0;
}
