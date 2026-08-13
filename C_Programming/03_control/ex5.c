// 5. 반복문 - for문
#include <stdio.h>

int main(int argc, char const *argv[])
{
    // 구구단 출력
    for(int i = 2; i <= 9; i++){
        if(i % 2 == 0) continue;
        for(int j = 1; j <= 9; j++){
            printf("%d * %d = %2d\t", i, j, i * j);
        }
        printf("\n");
    }

    // 각 자릿수의 합
    int num, sum = 0;
    printf("숫자 입력 => ");
    scanf("%d", &num);

    for(int i = num; i > 0; i /= 10){
        sum += i % 10;
    }
    printf("%d\n", sum);

    // 별표 삼각형 출력1
    // *
    // **
    // ***
    // ****
    // *****
    int n = 5;

    for(int i = 0; i < n; i++){
        for(int j = 0; j <= i; j++){
            printf("*");
        }
        printf("\n");
    }

    // 별표 삼각형 출력2
    // *****
    // ****
    // ***
    // **
    // *
    for(int i = 0; i < n; i++){
        for(int j = i; j < n; j++){
            printf("*");
        }
        printf("\n");
    }
    // 별표 삼각형 출력3
    //     *
    //    **
    //   ***
    //  ****
    // *****
    for(int i = 0; i < n; i++){
        for(int j = i; j < n - 1; j++){
            printf(" ");
        }
        for(int j = 0; j <= i; j++){
            printf("*");
        }
        for(int j = 0; j < i; j++){
            printf("*");
        }
        printf("\n");
    }

    return 0;
}
