#include <iostream>
#include <iomanip>

using namespace std;

int main(){
	
	double n;
	int i, num, notas[] = {10000, 5000, 2000, 1000, 500, 200};
	int moedas[] = {100, 50, 25, 10, 5, 1};
   
	cin >> n;
	
	num = (int) (n * 100);
	
	cout << "NOTAS:" << endl;
	
	for(i = 0; i < 6; i++){
		
		cout << (int) (num / notas[i]) << " nota(s) de R$ " << notas[i] / 100 << ".00" << endl;
		num = num % notas[i];
	}
	

	//cerr << "Num = " << num << endl;
	cout << "MOEDAS:" << endl;
	
	cout << fixed;
	for(i = 0; i < 6; i++){
		
		cout << (int) (num / moedas[i]) << " moeda(s) de R$ " << setprecision(2) << (float)moedas[i] / 100 << endl;
		num = num % moedas[i];
	}
	
	return 0;
}