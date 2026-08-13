// 구조체 응용
#include <stdio.h>
#include <string.h>

typedef struct Student {
    int number;
    char name[10];
    double score;
} Student;

// Node 구조체 정의
// int data;
// Node라는 구조체의 포인터를 저장하는 포인터 변수
// 연결리스트 (Linked list)
typedef struct Node {
    int data;
    struct Node *p;
} Node;

void print_student(Student *p, int n);

int main(int argc, char const *argv[])
{  
    Student s = {1, "뽀로로", 100};
    Student *p = &s;

    // 간접 멤버 참조 연산자 (->)
    // printf("[%d] %s %.1f\n", p->number, p->name, p->score);
    // printf("[%d] %s %.1f\n", (*p).number, (*p).name, (*p).score);

    // 구조체 배열
    Student arr[4] = {
        {1, "뽀로로", 100},
        {2, "크롱", 90},
        {3, "루피", 80},
        {4, "포비", 70},
    };
    print_student(arr, 4);
    return 0;
}

void print_student(Student *p, int n) {
    for (int i = 0; i < n; i++) {
        // printf("[%d] %s %.1f\n", p[i].number, p[i].name, p[i].score);
        // printf("[%d] %s %.1f\n", (p + i)->number, (p + i)->name, (p + i)->score);
        printf("[%d] %s %.1f\n", (*(p + i)).number, (*(p + i)).name, (*(p + i)).score);
    }
}