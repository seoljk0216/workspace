// 3. 문자열
#include <stdio.h>

void swap(char**, char**);
void printArr(char**, int);
int main(int argc, char const *argv[])
{
    char str[10] = "apple";
    str[0] = 'A';
    printf("%s\n", str);

    printf("%p, %p, %p\n", "apple", "apple", "apple");

    char *sp = "apple";
    printf("%s\n", sp);
    printf("%c\n", sp[2]);
    sp++;
    printf("%s\n", sp);

    sp = "dimigo"; // dimigo -> imigo -> migo -> igo -> go -> o
    while (*sp)
    {
        printf("%s\n", sp++);
    }

    // 이중 포인터
    int a = 10;
    int* p = &a;
    int** pp = &p;

    printf("%d, %d, %d\n", a, *p, **pp);
    **pp = 20;

    // 문자열 교환하기
    char* str1 = "Hello";
    char* str2 = "World";

    swap(&str1, &str2);
    printf("%s, %s\n", str1, str2); // Hello, World

    // 포인터 배열
    char* ptr_arr[3] = {"apple", "banana", "kiwi"};
    // char ptr_arr[3][10] = {"apple", "banana", "kiwi"}; 불가
    printArr(ptr_arr, 3);

    // void형 포인터
    void *pv = NULL;
    int i = 10;
    pv = &i;
    // printf("%d\n", *pv);
    int* pi = (int*)pv;
    printf("%d\n", *pi);

    // 메모리 동적 할당 (malloc)
    // 정적 할당 : 컴파일 시점에 메모리의 크기가 정해짐
    // 동적 할당 : 런타임 시점에 메모리의 크기가 정해짐
    return 0;
}

void swap(char** pa, char** pb){
    char* temp = *pa;
    *pa = *pb;
    *pb = temp;
}

void printArr(char** arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%s\n", arr[i]);
    }
}