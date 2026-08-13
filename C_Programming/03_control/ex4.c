// 4. 반복문 do ~ while문
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char const *argv[])
{
    /*int menu = 0;
    printf("1. 치킨\n");
    printf("2. 피자\n");
    printf("3. 떡볶이\n");
    printf("9. 종료\n");

    int chicken = 0, pizza = 0, dduk = 0;

    do{
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
    } while (menu != 9);*/

    // 숫자 맞추기 게임
    int answer, guess, cnt = 0;
    srand(time(NULL));

    /*for(int i = 0; i < 5; i++){
        answer = rand() % 10 + 1;    // 1 ~ 10 랜덤값
        printf("%d\n", answer);
    }*/
    answer = rand() % 100 + 1;  // 1 ~ 100 랜덤값

    do
    {
        printf("숫자 입력 = > ");
        scanf("%d", &guess);

        if(guess < answer){
            printf("Up\n");
            cnt++;
        }
        else if(guess > answer){
            printf("Down\n");
            cnt++;
        }
        else
            printf("정답입니다\n");
        if(cnt == 5){
            printf("다음기회에\n");
            break;
        }
    } while (guess != answer);
        
    return 0;
}
