// 3. 함수 - 재귀함수
#include <stdio.h>

int factorial(int n);
int fibo(int n);
int fibo2(int n);
int gcd(int a, int b);
int gcd2(int a, int b);

int main(int argc, char const *argv[])
{
    //팩토리얼
    int n = 5;
    printf("factorial: %d\n", factorial(n));

    //피보나치
    printf("fibo: %d\n", fibo(n));
    printf("fibo: %d\n", fibo2(n));

    //최대공약수 (유클리드 호제법)
    //gcd(a, b) = gcd(b, a % b)
    printf("GCD: %d\n", gcd(72, 30));
    printf("GCD: %d\n", gcd2(72, 30));

    /* 
    
    */

    return 0;
}

int factorial(int n){
    if(n <= 1) return 1;
    return n * factorial(n - 1);
}
int fibo(int n){
    if(n <= 1) return n;
    return fibo(n - 1) + fibo(n - 2);
}
int fibo2(int n){
    if(n <= 1) return n;
    int prev = 0, curr = 1, next;
    for(int i = 2; i <= n; i++){
        next = prev + curr;
        prev = curr;
        curr = next;
    }
    return curr;
}
int gcd(int a, int b){
    if(b == 0) return a;
    return gcd(b, a % b);
}
int gcd2(int a, int b){
    while (b != 0){
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}