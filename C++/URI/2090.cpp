#include <iostream>
#include <vector>

using namespace std;

int nlc(int conju) {
    return conju + 1;
}

int main(){

    vector<string> palavras;
    string p;

    int k, n;

    cin >> n >> k;

    for (int i = 0; i < n; i++)
    {
        cin >> p;
        palavras.push_back(p);
    }

    int conju = 0;
    int letras = 0;

    while (letras + nlc(conju) < k) {
        letras += nlc(conju);
        conju++;
    }
    
    int off = k - letras - 1;

    cout << palavras[off ] << endl;
}
