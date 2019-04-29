#include <iostream>
#include <string>

using namespace std;

int main(){
	
	int i, j, n, v[5], res = 0, c;
	string alpha = "ABCDE";
	
	//char alpha[5] = {'A', 'B', 'C', 'D', 'E'};
	
	// cin >> n;
	while(cin >> n){
		   
	    if(n == 0) break;
	    
		for(j = 0; j < n; j++){
			for(i = 0; i < 5; i++){
				cin >> v[i];
				if(v[i] <= 127){
					c = i;
					res++;
				}
			}
			
			if(res != 1){
				cout << "*" << endl;
			} else
				cout << alpha[c] << endl;
			
			res = 0;
		}
		
	}
	return 0;
	
}