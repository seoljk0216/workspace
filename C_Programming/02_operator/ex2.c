// 2. 연산자 (복합대입, 증감)
#include <stdio.h>

int main(int argc, char const *argv[])
{
    // 복합 대입 연산자
    int a = 10;

    // a = a + 3;
    a += 3;
    printf("%d\n", a); // 13
    a -= 3;
    printf("%d\n", a); // 10
    a *= 3;
    printf("%d\n", a); // 30
    a /= 3;
    printf("%d\n", a); // 10
    a %= 3;
    printf("%d\n", a); // 1

    // 증감 연산자
    a = 1;
    a++;
    printf("%d\n", a); // 2
    --a;
    printf("%d\n", a); // 1
    
    // 수식 내에서 쓸 때 주의
    int b = ++a;
    printf("%d, %d\n", a, b); // 2, 2
    
    b = a++;
    printf("%d, %d\n", a, b); // 3, 2

    return 0;
}
