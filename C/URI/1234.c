#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char strupr(char str) {
    str = toupper(str);
    return str;
}

char strlwr(char str) {
    str = tolower(str);
    return str;
}

int main(){
	
	int i = 0, j = 0;
	char entrada[100];
	
	while(gets(entrada)){														//scanf("%[^\n]s", &batata);
		while(entrada[i] != '\0'){
			
			if(entrada[i] == ' '){
				i++;
			}
			else{
				if((j % 2) == 0)
					entrada[i] = strupr(entrada[i]);
				else
				    entrada[i] = strlwr(entrada[i]);
				i++;
				j++;
			}
		}
		
		
		i = 0;
		j = 0;
		printf("%s\n", entrada);
		fflush(stdin);
	}
}

//Solved