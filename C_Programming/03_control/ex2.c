// 2. 조건문 - switch~case문
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int score = 100;
    char grade;

    switch(score/10){
        case 10:
        case 9:
            grade = 'A';
            break;
        case 8:
            grade = 'B';
            break;
        case 7:
            grade = 'C';
            break;
        case 6:
            grade = 'D';
            break;
        default:
            grade = 'F';
    }
    printf("%d점 %c등급", score, grade);
    
    // 사칙연산 (2 + 3 = 5)
    char op;
    int op1, op2, result;
    printf("연산식 입력 (2 + 3) => ");
    scanf("%d %c %d", &op1, &op, &op2);

    switch(op)
    {
        case '+':
            result = op1 + op2;
            break;
        case '-':
            result = op1 - op2;
            break;
        case '*':
            result = op1 * op2;
            break;
        case '/':
            if(op2 != 0)
                result = op1 / op2;
            else
                printf("나눌 수 없는 값입니다.\n");
            break;
    }
    printf("%d %c %d = %d\n", op1, op, op2, result);

    // 메뉴 선택
    int menu;
    printf("1. 라면\n");
    printf("2. 마카롱\n");
    printf("3. 스테이크\n");
    scanf("%d", &menu);

    switch(menu){
        case 1:
            printf("라면을 선택하셨습니다.\n");
            break;
        case 2:
            printf("마카롱을 선택하셨습니다.\n");
            break;
        case 3:
            printf("스테이크을 선택하셨습니다.\n");
            break;
        default:{
            printf("없는 메뉴입니다.\n");
        }
    }

    return 0;
}
