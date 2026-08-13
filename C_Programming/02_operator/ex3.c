// 3. 연산자 (비교, 논리)
#include <stdio.h>

int main(int argc, char const *argv[])
{
    // 비교 연산자
    int a = 1, b = 2;
    printf("%d\n", a < b);
    printf("%d\n", a > b);
    printf("%d\n", a <= b);
    printf("%d\n", a >= b);
    printf("%d\n", a == b);
    printf("%d\n", a != b);

    // 점수가 60점 이상이면 "Pass"
    // 60점 미만이면 "Fail" 출력
    int score = 90;
    (score >= 60) ? printf("Pass\n") : printf("Fail\n");
    printf("%s\n",(score >= 60) ? "Pass" : "Fail");

    // 논리 연산자
    a = 0;
    b = 1;
    printf("%d\n", !a);
    printf("%d\n", a && b);
    printf("%d\n", a || b);

    // 윤년 계산(365.2422)
    // 1) 4로 나누어 떨어지고, 100으로 나누어 떨어지지 않거나
    // 2) 400으로 나누어 떨어지면 윤년
    // 윤년: 2024, 2028, 2400 / 평년: 2100
    int year = 2024;
    if(year % 4 == 0 && year % 100 != 0 || year % 400 == 0){
        printf("%d는 윤년입니다\n", year);
    }
    else{
        printf("%d는 평년입니다\n", year);
    }
    
    if(year % 4 != 0 || year % 100 == 0 && year % 400 != 0){
        printf("%d는 평년입니다\n", year);
    }
    else{
        printf("%d는 윤년입니다\n", year);
    }

    // Short-Circuit
    a = 0;

    if(a != 0 && 10 / a > 1){
        printf("실행된\n");
    }
    
    a = 1, b = 2;
    if(a || b++ > 5){
        printf("실행됨\n");
    }
    printf("%d\n", b);
    return 0;
}
