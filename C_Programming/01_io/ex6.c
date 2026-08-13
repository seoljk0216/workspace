// 데이터 입력
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int a, b, c;
    printf("%p %p %p\n", &a, &b, &c);

    /*scanf("%d %d", &a, &b);
    printf("%d, %d\n", a, b); */
    
    //10:20:30
    /*scanf("%d:%d:%d", &a, &b, &c);
    printf("%d시 %d분 %d초\n", a, b, c);*/

    /*int r = scanf("%d", &a);
    printf("%d\n", r);*/

    //%f %lf 구분
    /*float f;
    double d;
    scanf("%f %lf", &f, &d);
    printf("%f, %f\n", f, d);*/

    // %c 사용 시 주의
    /*char ch;
    scanf(" %c", &ch);
    printf("%c", ch);*/

    // 키, 몸무게, 혈액형
    float height;
    double weight;
    char blood_type;
    scanf("%f %lf %c", &height, &weight, &blood_type);
    printf("키: %.2fcm, 몸무게: %.2fkg, 혈액형: %c형\n", height, weight, blood_type);
    

    return 0;
}