// 1. 조건문 - if문
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int num = 3;

    if (num > 1 && num < 5){
        printf("실행됨\n");
    }

    if (num % 2 == 0){
        printf("짝수\n");
    }
    else{
        printf("홀수\n");
    }

    int a = 10, b = 20;
    // a > b : a, a < b : b, a == b : 같은 값
    if(a > b)
        printf("%d\n", a);
    else if(a < b)
        printf("%d\n", b);
    else
        printf("같은 값\n");
    
    // 90점 이상이면 'A', 80점 이상이면 'B'
    // 70점 이상이면 'C', 60점 이상이면 'D'
    // 60점 미만이면 'F'

    int score = 90;
    char grade;

    if(score >= 90)
        grade = 'A';
    else if(score >= 80)
        grade = 'B';
    else if(score >= 80)
        grade = 'C';
    else if(score >= 80)
        grade = 'D';
    else
        grade = 'F';
    printf("%d점 %c등급", score, grade);

    

    return 0;
}
