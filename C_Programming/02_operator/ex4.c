// 4. 연산자 (비트, 삼항)
#include <stdio.h>

int main(int argc, char const *argv[])
{
    // 비트 논리 연산자
    int a = 8, b = 10; // 0000 1000, 0000 1010
    printf("%d\n", a & b);
    printf("%d\n", a | b);
    printf("%d\n", a ^ b);
    printf("%d\n", ~a); // 2의 보수
    
    // &: 특정비트 확인
    printf("%s\n", (a & 1) ? "홀수" : "짝수");

    // |: 특정 비트 켜기
    a = a | 1;
    printf("%d\n", a);

    // SWAP 처리
    // 1) temp 변수 이용
    a = 2, b = 3;
    int temp = a;
    a = b;
    b = temp;
    
    // 2) xor 이용
    a ^= b;
    b ^= a;
    a ^= b;
    printf("%d, %d\n", a, b);

    // 3) 덧셈, 뺄셈 이용
    a = a + b;
    b = a - b;
    a = a - b;

    // 비트 이동 연산자
    a = 10;
    a = a << 1;
    printf("%d\n", a); // 20

    a = a >> 1;
    printf("%d\n", a); // 10

    char i = 65; // 0100 0001
    printf("%d\n", i << 1); // 1000 0010 (130)

    char c = i << 1;
    printf("%d\n", c); // -126
    
    // 삼항연산자
    // 90점 이상이면 'A', 80점 이상이면 'B'
    // 70점 이상이면 'C', 60점 이상이면 'D'
    // 60점 미만이면 'F'
    int score = 85;
    char grade = (score >= 90) ? 'A' : (score >= 80) ? 'B' : (score >= 70) ? 'C' :(score >= 60) ? 'D' : 'F';
    printf("%d점 %c등금\n", score, grade);


    return 0;
}
