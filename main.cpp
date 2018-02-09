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

int main()
{
    return 0;
}
