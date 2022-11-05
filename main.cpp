#include <bits/stdc++.h>
using namespace std;

vector<vector<string>> cykTable;
map<string, vector<string>> grammar;

// Verifica se a string c é produto cartesiano das strings a e b
bool isCartesianProduct(string a, string b, string c) {
    for (int i = 0, n = a.length() * b.length(); i < n; i++) {
        string product = string() + a[i / b.size()] + b[i % b.size()];
        if (product == c) return true;
    }
    return false;
}

void CYK(string w) {
    map<string, string> pd;
    cykTable = vector<vector<string>> (w.length(), vector<string> (w.length(), ""));
    for (int ns = 1, n = w.length(); ns <=  n; ns++) {  // Tamanho do conjunto de letras  
        for (int i = 0; i <= n - ns; i++) { // Itera pelos conjuntos possiveis
            string subW = w.substr(i, ns); // Conjunto 

            for (auto it = grammar.begin(); it != grammar.end(); it++) { // Itera pela gramatica
                string a = it->first; // Variaveis
                vector<string> b = it->second; // Simbolos (terminais e nao-terminais)

                for (int j = 0; j < b.size(); j++) { // Itera pelas producoes
                    for (int k = 1, wn = subW.length(); k <= wn; k++) { // Controla as combinacoes do conjunto
                        try { // As vezes a subW eh pequena e quebra na funcao isCartesianProduct, poderia ser resolvido com ifs, mas assim fica menor                   
                            if (!subW.compare(b[j]) or isCartesianProduct(pd[subW.substr(0, k)], pd[subW.substr(k, wn - k)], b[j])) {
                                if (pd[subW].find(a) == string::npos) {  // Caso o simbolo nao estiver na pd, o insere          
                                    pd[subW] = (pd[subW] == "") ? a : pd[subW] + a;
                                }
                                cykTable[ns - 1][i] = pd[subW];
                            }
                        } catch(...) {}
                    }
                }        
            }
        }   
    }    

    if ((cykTable[w.length() - 1][0].find("S") != string::npos)) 
        cout << w << ": " << "SIM" << endl;
    else 
        cout << w << ": " << "NAO" << endl;
}

int main() {
    string w, leftSymb, aux, rightSymb;
    int n;
    cin >> n;

    while (n--) { 
        cin >> leftSymb >> aux >> rightSymb;
        grammar[leftSymb].push_back(rightSymb);
    }

    while (getline(cin >> ws, w) and w.compare("*"))         
        CYK(w);

    return 0;
}