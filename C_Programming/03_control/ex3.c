// 3. 반복문 ~while문
#include <stdio.h>

int main(int argc, char const *argv[])
{
    // 1 ~ n까지의 합 출력
    int i = 1, n;
    int sum = 0;
    printf("숫자 입력 => ");
    scanf("%d", &n);

    while(i <= n){
        sum += i;
        i++;
    }
    printf("%d\n", sum);

    char c;
    printf("문자열 입력 => ");
    scanf(" %c", &c);

    // abcDE1234 : 소문자 3개, 대문자 2개, 숫자 4개
    int lower = 0, upper = 0, num = 0;
    while (c != '\n'){
        if(c >= 'A' && c <= 'Z')
            lower++;
        else if(c >= 'a' && c <= 'z')
            upper++;
        else if(c >= '0' && c <= '9')
            num++;
        scanf("%c", &c);
    }
    printf("대문자: %d개, 소문자: %d개, 숫자: %d개\n", lower, upper, num);

    // 메뉴 선택
    int menu = 0;
    printf("1. 치킨\n");
    printf("2. 피자\n");
    printf("3. 떡볶이\n");
    printf("9. 종료\n");

    int chicken = 0, pizza = 0, dduk = 0;

    while(menu != 9){
        scanf("%d", &menu);
        switch (menu)
        {
            case 1:
                chicken++;
                break;
            case 2:
                pizza++;
                break;
            case 3:
                dduk++;
                break;
            case 9:
                printf("치킨: %d개, 피자: %d개, 떡볶이: %d개\n", chicken, pizza, dduk);
                break;
        
           default:
                printf("없는 메뉴입니다.\n");
                break;
        }
    }
    

    return 0;
}
