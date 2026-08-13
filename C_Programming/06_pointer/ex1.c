// 1, 포인터 기초
#include <stdio.h>

int *func();
void swap(int *pa, int *pb);

int main(int argc, char const *argv[])
{
    char c = 'A';
    int i = 10;
    double d = 3.14;
    
    printf("%p, %d\n", &c, sizeof(&c));
    printf("%p, %d\n", &i, sizeof(&i));
    printf("%p, %d\n", &d, sizeof(&d));

    // 포인터 변수
    char *pc = &c;
    int *pi = &i;
    double *pd = &d;

    // 간접 참조 연산자 (*)
    printf("%c, %c\n", c, *pc);
    printf("%d, %d\n", i, *pi);
    printf("%f, %f\n", d, *pd);

    *pi = 20;
    printf("%d, %d\n", i, *pi);

    (*pi)++;
    printf("%d, %d\n", i, *pi);

    int a = 2, b = 3;
    swap(&a, &b);
    printf("%d, %d\n", a, b);

    // 포인터 연산
    printf("%p\n", &i);
    printf("%p\n", &i + 1);
    printf("%p\n", &i + 2);
    // ++&i;

    printf("%p\n", pi);
    printf("%p\n", pi + 1);
    printf("%p\n", pi + 2);
    pi++;

    int *p = func();
    printf("%d\n", *p);

    // int * -> char *
    int num = 10;
    int *iptr = &num;

    char *cptr = (char *)iptr;
    printf("%p, %p\n", cptr, cptr + 1);
    printf("%d, %d, %d, %d\n", *cptr, *(cptr + 1), *(cptr + 2), *(cptr + 3));
    

    return 0;
}

int *func(){
    static int a = 10;
    return &a;
}

void swap(int *pa, int *pb){
    int temp;
    temp = *pa;
    *pa = *pb;
    *pb = temp;
}
