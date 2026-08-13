// 4. 1차원 배열 - 응용
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
int fibo(int n);
int fibo2(int n );

int memo[101] = {0}; // 메모이제이션

int main(int argc, char const *argv[])
{
    clock_t start,end;
    double result1,result2;
    int n=10;
    // 피보나치 수열
    // 0 1 2 3 5 8 ..
    // a(0) = 0, f(1) = 1
    // f(n) = f(n-1) + f(n-2)
    start = clock();
    printf("%d\n",fibo(n));
    end = clock();
    result1=(double) (end-start)/ CLOCKS_PER_SEC;

    start = clock();
    printf("%d\n",fibo2(n));
    end = clock();
    result2=(double) (end-start)/ CLOCKS_PER_SEC;

    printf("%.3f\n",result1);
    printf("%.3f\n",result2);

    // 에라토스테네스의 체: 2~100 사이의 모든 소수 찾기
    int prime[101]; // 소수는 1 나눠떨어지면 0
    memset(prime,1,sizeof(prime));
    int m = 100;

    prime[0]=0;
    prime[1]=0;
    for(int i=2; i<=sqrt(m); i++)
    {
        if(prime[i])
        {
            for(int j = i * i; j<=m; j+=i)
                prime[j] = 0;
        }
    }
    for(int i= 2; i<=m; i++)
    {
        if(prime[i])
            printf("%d ",i);
    }

    return 0;
}

int fibo(int n)
{
    if(n <= 1) return n;
    return fibo(n-1) + fibo(n-2);
}

int fibo2(int n)
{
    if(n<=1) return n;
    if(memo[n]!=0) return memo[n];

    memo[n] = fibo2(n-1)+fibo2(n-2);
    return memo[n];
}