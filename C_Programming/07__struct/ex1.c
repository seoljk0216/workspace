// 구조체 기초
#include <stdio.h>
#include <string.h>

// 구조체 정의
struct Score {
    double kor;
    double eng;
    double math;
};

struct Student {
    int number;
    char name[20];
    // double score;
    struct Score score;
};

void print_student(struct Student s);

int main(int argc, char const *argv[])
{
    struct Student s1; // 구조체 변수
    struct Student s2 = {2, "크롱", {100, 100, 100}};

    // 멤버 참조 연산자(.)
    s1.number = 1;
    strcpy(s1.name, "뽀로로");
    s1.score.kor = 88.5;
    s1.score.math = 90;
    s1.score.eng = 100;

    // 구조체 변수의 대입 연산
    struct Student s3;
    s3 = s1;

    s3.number = 3;
    strcpy(s3.name, "루피");

    print_student(s1);
    print_student(s3);
    return 0;
}

void print_student(struct Student s) {
    printf("[%d] %s %.1f\n", s.number, s.name, s.score.kor);
}