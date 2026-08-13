// 1. 1차원 배열
#include <stdio.h>
#define SIZE 5

int main(int argc, char const *argv[])
{
    // 배열 선언
    char arr[SIZE];
    int arr2[SIZE];
    double arr3[SIZE];

    printf("%d\n", sizeof(arr));    // 1 * 5 = 5
    printf("%d\n", sizeof(arr2));    // 4 * 5 = 20
    printf("%d\n", sizeof(arr3));    // 8 * 5 = 40

    int num[5] = {1, 2, 3, 4, 5};

    int len = sizeof(num) / sizeof(int);    // 20 / 4 = 5
    for(int i = 0; i < len; i++){
        printf("%d ", num[i]);
    }
    printf("\n");

    // 5 4 3 2 1 역순 출력
    for(int i = len - 1; i >= 0; i--){
        printf("%d ", num[i]);
    }
    printf("\n");

    // 배열명은 첫 번째 배열요소의 시작 주소값
    printf("%p\n", num);
    printf("%p\n", &num[0]);
    // num = 10;

    // 배열명에 +, - 연산을 하면 자료형의 크기만큼 연산이 일어남
    printf("%p\n", num + 1);    // | num + 0 | num + 1 | num + 2 |
    printf("%p\n", num - 1);

    // 5명의 플밍 점수를 입력받아 평균 계산하기
    int score[5];
    int sum = 0;

    for(int i = 0; i < 5; i++){
        scanf("%d", &score[i]);
        //scanf("%d", score + i);
        sum += score[i];
    }
    printf("평균: %.2f\n", sum / 5.0);
    

    return 0;
}
