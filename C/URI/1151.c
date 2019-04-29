#include <stdio.h>

int fib (int num, int x){
	
	if(num <= 1)
		return x;
	else
		return fib(num - 1) + fib(num - 2);
}

int main(){
	
	int i, x;
	
	scanf("%i", &x);
		
	fib(i, 1);

	return 0;
}