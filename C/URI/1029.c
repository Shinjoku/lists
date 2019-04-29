#include <stdio.h>

int count = 0;

long int fibonacci(int n){
	
	if(n <= 0)
		return 0;
	if(n == 1)
		return 1;
	else
		return fibonacci(n-1) + fibonacci(n-2);
}

long int fibonacciCalls(int n){
	
	count++;
	
	if(n <= 0)
		return 0;
	if(n == 1)
		return 0;
	else{
		fibonacciCalls(n-1);
		fibonacciCalls(n-2);
		return count - 1;
	}
}

int main(){
	
	int x, n, i;
	
	scanf("%i", &x);
	
	for(i = 0; i < x; i++){
		scanf("%i", &n);
		printf("fib(%i) = %li calls = %li\n", n, fibonacciCalls(n), fibonacci(n));
		count = 0;
	}
}

//Solved