// 1. 함수 - 기본
#include <stdio.h>
#include <ctype.h>
#include "myheader.h"

int main(int argc, char const *argv[])
{
    // 사칙연산 함수 작성
    printf("%d\n", add(5, 2));
    printf("%d\n", sub(5, 2));
    printf("%d\n", mul(5, 2));
    printf("%.1f\n", div(5, 2));

    // 입력문자 -> 알파벳, 숫자인지 판별
    char c;
    printf("문자 입력 => ");
    scanf("%c", &c);

    if(isalpha(c)) printf("알파벳\n");
    else if(isdigit(c)) printf("숫자\n");
    else printf("기타문자\n");

    return 0;
}
int add(int a, int b){
    return a + b;
}
int sub(int a, int b){
    return a - b;
}
int mul(int a, int b){
    return a * b;
}
double div(int a, int b){
    return (double)a / b;
}
