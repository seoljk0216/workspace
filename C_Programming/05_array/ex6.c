// 6. 2차원 문자 배열
#include <stdio.h>
#include <string.h>

void bubble_sort(int[], int);
void bubble_sort2(char[][20], int);
void print_sort(int[], int);
void print_sort2(char[][20], int);
int main(int argc, char const *argv[])
{
    char fruits[3][7] = {"apple", "banana", "kiwi"};
    for (int i = 0; i < 3; i++)
    {
        puts(fruits[i]);
    }

    // 오늘의 급식 메뉴(밥, 국, 반찬, 디저트)
    char menu[4][100];

    // 칼슘 찹살밥
    // 건새우 아욱국
    // 흑돼지 함박스테이크
    // 꿀자몽 블랙티
    printf("오늘의 급식 메뉴 입력: ");
    for (int i = 0; i < 4; i++)
    {
        fgets(menu[i], sizeof(menu[i]), stdin);
        menu[i][strcspn(menu[i], "\n")] = '\0';
    }

    for (int i = 0; i < 4; i++)
    {
        puts(menu[i]);
    }

    // 일주일 급식 메뉴 (3차원 배열)
    char menu2[5][4][100];

    // 버블 정렬
    int num[5] = {5, 4, 1, 3, 2};
    bubble_sort(num, 5);
    print_sort(num, 5);

    // 문자열 정렬
    char name[4][20] = {"홍길동", "김철수", "이영희", "박영수"};
    bubble_sort2(name, 4);
    print_sort2(name, 4);
    return 0;
}

// call by reference (주솟값만 전달) - 이 방법 사용
// call by value (값 자체 전달)
void bubble_sort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
        printf("=== %d회전 ===\n", i + 1);
        print_sort(arr, 5);
    }
}

void bubble_sort2(char arr[][20], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (strcmp(arr[j], arr[j + 1]) > 0)
            {
                char temp[20];
                strcpy(temp, arr[j]);
                strcpy(arr[j], arr[j + 1]);
                strcpy(arr[j + 1], temp);
            }
        }
        printf("=== %d회전 ===\n", i + 1);
        print_sort2(arr, 4);
    }
}

void print_sort(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void print_sort2(char arr[][20], int n)
{
    for (int i = 0; i < n; i++)
    {
        puts(arr[i]);
    }
}
