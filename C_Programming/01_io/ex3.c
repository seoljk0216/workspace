//필드 옵션을 이용한 출력
#include <stdio.h>

int main(int argc, char const *argv[])
{
        printf("1234567890\n");
        printf("%10d\n", 123);
        printf("%-10d\n", 123);

        printf("%10.2f\n", 3.14);
        printf("%.3f\n", 3.141592);

        printf("%10s\n", "apple");
        printf("%-10s\n", "apple");

        printf("|%10s|\n", "가나다");

        //Kor Math Eng Tot Avg (10칸 확보)
        //100 90 80 270 80
        printf("%10s %10s %10s %10s %10s\n","Kor", "Math", "Eng", "Tot", "Avg");
        printf("%10d %10d %10d %10d %10f\n", 100, 95, 80, 100 + 95 + 80, (100 + 95 + 80)/3.0);

        printf("%05d\n", 123);

        return 0;
}
