//3. 문자열 함수
#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char str1[] = "apple banana";
    char str2[10] = {0};

    // 문자열의 길이
    printf("%d\n", strlen(str1));
    printf("%d\n", sizeof(str1));

    //strcpy(str2, str1);
    strncpy(str2, str1, 5);
    puts(str2);
    
    char str3[10] = "apple";
    char str4[10] = "abple";
    printf("%d\n", strcmp(str3, str4));

    //문자열 연결
    //strcat(str3, str4);
    strncat(str3, str4, sizeof(str3) - strlen(str3));

    //문자열 교환
    // int a = 10, b = 20;
    // int temp = a;
    // a = b;
    // b = temp;

    char a[10] = "apple";
    char b[10] = "banana";
    char c[10];

    strcpy(c, a);
    strcpy(a, b);
    strcpy(b, c);

    puts(a);
    puts(b);
    

    return 0;
}
