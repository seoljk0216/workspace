// 5. 2차원 배열
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    int arr[2][3];

    // 배열 사이즈
    printf("%d\n", sizeof(arr)); // 24
    printf("%d\n", sizeof(arr[0])); // 12
    printf("%d\n", sizeof(arr[0][0])); // 4

    // 배열 초기화
    int num[2][3] = {{1, 2}, {4}};

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%d ", num[i][j]);
        }
        printf("\n");
    }

    // 주소값
    printf("%p\n", num);
    printf("%p\n", num[0]);
    printf("%p\n", &num[0][0]);

    printf("%p\n", num[1]);
    printf("%p\n", num[0] + 3);
    printf("%p\n", &num[1][0]);
    printf("%p\n", &num[0][3]);

    // 점수 평균
    int score[2][4] = {0,};

    for (int i = 0; i < 2; i++)
    {
        printf("%d번 점수 입력=>", i + 1);
        for (int j = 0; j < 3; j++)
        {
            scanf("%d", &score[i][j]);
            score[i][3] += score[i][j];
        }
        printf("%d번 평균 : %.2f\n", i + 1, score[i][3] / 3.0);
    }

    // 가변 길이 배열(VLA)
    int n;
    scanf("%d", &n);
    int a[n][n];

    memset(a, 0, sizeof(a));
    
    for(int i = 0; i < n; i++){
        a[i][i] = 1;
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }

    // 3차원 배열 선언
    int arr2[2][3][4];

    printf("%d\n", sizeof(arr2));
    printf("%d\n", sizeof(arr2[0]));
    printf("%d\n", sizeof(arr2[0][0]));
    printf("%d\n", sizeof(arr2[0][0][0]));

    return 0;
}