// 2. 문자 배열
#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    // 문자 배열 선언
    char name[6] = {'a', 'p', 'p', 'l', 'e', '\0'};
    printf("%s\n", name);
    
    char name2[7] = "banana";   // 널 문자가 자동으로 추가
    printf("%s\n", name2);

    printf("%p, %p\n", name, name2);
    
    // 문자열 입출력 함수
    char str[20];
    scanf("%19s", str);   // 공백문자 전까지 읽음, 널문자 붙임
    printf("%s\n", str);

    // 버퍼 지우기
    while (getchar() != '\n');

    //gets(str);
    fgets(str, sizeof(str), stdin); // 한 줄 입력, 엔터키까지 입력
    //str[strlen(str) - 1] = '\0';  마지막 문자를 널문자로 치환
    str[strcspn(str, "\n")] = '\0';
    
    printf("[%s]\n", str);
    puts(str);
    printf("---------------\n");

    return 0;
}
