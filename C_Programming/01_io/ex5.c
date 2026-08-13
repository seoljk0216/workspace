// 5. 자료형
#include <stdio.h>

void my_func(); // 함수 프로토타입 선언
int global_var; // 전역변수

int main(int argc, char const *argv[])
{
    // 변수 선언 : 자료형 변수형;
    int num = 10;

    int n1 = 10, n2 = 10;
    n1 = n2 = 20;
    printf("%d, %d\n", n1, n2);

    // 지역변수
    int x = 10;
    {                           // 블록 선언
        int y = 20;
        printf("%d, %d\n", x, y);
    }
    // printf("%%d, %d", x, y);

    // 전역변수
    printf("%d\n", global_var);
    my_func();
    printf("%d\n", global_var);

    // 변수의 범위(Scope)
    int i = 3;
    {
        int i = 5;
        printf("%d\n", i);
    }
    
    // 식별자
    int score, score2, _score;
    // int 2score;
    int $score; // 안 쓰는 게 좋다
    // int int;
    int Int; // 안 쓰는 게 좋다22
    
    // 상수

    int max_len = 0;
    const int MAX_LEN = 0; // 대문자를 쓰자

    max_len = 10;
    // MAX_LEN = 10;

    return 0;
}

void my_func()
{
    printf("%d\n", global_var);
    global_var = 10;
}