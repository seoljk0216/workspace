// 2. 배열과 포인터
#include <stdio.h>

void printArr(int *p, int size);
void printArr2(int (*)[3], int);

int main(int argc, char const *argv[])
{
    int a[3] = {1, 2, 3};

    printf("%p, %p, %p\n", a, a + 1, a + 2);
    printf("%p, %p, %p\n", &a[0], &a[1], &a[2]);

    // 간접 참조 연산자
    printf("%d, %d, %d\n", *a, *(a + 1), *(a + 2));
    printf("%d, %d, %d\n", a[0], a[1], a[2]);

    // a[1] = *(a + 1) = *(1 + a) = 1[a]
    printf("%d, %d, %d\n", 0[a], 1[a], 2[a]);

    // 포인터 변수
    int *p = a;
    printf("%d, %d, %d\n", p[0], p[1], p[2]);
    // a++;
    p++;

    printf("%d, %d\n", a[-1], p[-1]);

    printArr(a, 3);

    int b[2][3] = {1, 2, 3, 4, 5, 6};
    printArr2(b, 2);

    return 0;
}

void printArr2(int (*p)[3], int rows){
    int cols = sizeof(*p) / sizeof(int);
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++)
            printf("%d ", p[i][j]);
        printf("\n");
    }
}

void printArr(int *p, int size){

    for(int i = 0; i < size; i++){
        printf("%d\n", p[i]);
    }
}
