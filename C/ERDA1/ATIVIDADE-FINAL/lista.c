#include <stdio.h>
#include <ctype.h>
#include "lista.h"


void upper(char *p){
	while(*p){ 
		*p = toupper(*p); 
		p++; 
	}
}