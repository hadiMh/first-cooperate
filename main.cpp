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
	Student initial_student = {0,"","",""};
	FILE *st=fopen("student.txt","w");
	for (long long int i = 0; i < 1000000; i++)
	{
		fwrite(&initial_student, sizeof(Student), 1, st);
	}
	fclose(st);
	Lesson initial_lesson = { "","",0,"" };
	FILE *les = fopen("course.txt", "w");
	for (long long int i = 0; i < 1000000; i++)
	{
		fwrite(&initial_lesson, sizeof(Lesson), 1, les);
	}
	fclose(les);

}
int main()
{
    return 0;
}
