// 4. 자료형
#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <stdbool.h>

int main(int argc, char const *argv[])
{
    // 기본 자료형 : 정수형, 실수형, 문자형
    // 1. 정수형 : short, int(기본), long, long long

    // 자료형 크기
    printf("%d, %d\n", sizeof(short), sizeof(unsigned short));
    printf("%d, %d\n", sizeof(int), sizeof(unsigned int));
    printf("%d, %d\n", sizeof(long long), sizeof(unsigned long long));

    //값의 범위
    printf("%d ~ %d\n", SHRT_MIN, SHRT_MAX);
    printf("%u ~ %u\n", 0, USHRT_MAX);
    printf("%d ~ %d\n", INT_MIN, INT_MAX);
    printf("%u ~ %u\n", 0, UINT_MAX);
    printf("%lld ~ %lld\n", LLONG_MIN, LLONG_MAX);
    printf("%u ~ %u\n", 0, ULLONG_MAX);

    // 2. 실수형 : float, double(기본), long double
    float f;
    double d;
    long double ld;

    printf("%d, %d, %d\n", sizeof(f), sizeof(d), sizeof(ld));
    printf("%e, %e\n", -FLT_MAX, FLT_MAX);

    // 유효자리수
    printf("%d, %d, %d\n", FLT_DIG, DBL_DIG, LDBL_DIG);

    float f2 =  1.23456;
    printf("%.10f\n", f2);

    f2 = 123456789.0;
    printf("%.0f\n", f2);

    float sum = 0;

    for(int i = 0; i < 10; i++){
        sum = sum + 0.1f;
    }
    printf("%.10f\n", sum);
    printf("%.10f\n", 0.1f);

    // 3. 문자형 : char
    printf("%d\n", sizeof(char));

    printf("%d ~ %d\n", CHAR_MIN, CHAR_MAX);
    printf("%d ~ %d\n", 0, UCHAR_MAX);

    // 논리형은 C에서 별도로 지원하지 않음
    printf("%d\n", 10 < 20);    // 1
    printf("%d\n", 10 > 20);    // 0

    bool b = true;
    printf("%d\n", b);


    // 오버플로우
    char c = 127;
    c = c + 1;
    printf("%d\n", c);
    
    c = -128;
    c = c - 1;
    printf("%d\n", c);

    return 0;
}
