// 2. 형식지정자를 이용한 출력
#include <stdio.h>

int main(int argc, char const *argv[])
{
    printf("%.2f\n", 3.14);     //소수
    printf("%c\n", 'A');
    printf("%s\n", "ABC");
    printf("%c\n", "ABC");      //0x12345678

    printf("%p\n", main);
    printf("%%\n");

    printf("%c\n", 65);         // A
    printf("%d\n", 'A');        // 65
    printf("%d\n", 'a');        // 97
    printf("%d\n", '0');        // 48

    printf("%d\n", 'Z' - 'A' + 1);        // 26
    printf("%d\n", 'a' - 'A');        // 32
    printf("%d\n", '5' - '0');        // 5

    return 0;
}