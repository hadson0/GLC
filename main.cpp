#include <bits/stdc++.h>

using namespace std;

vector<vector<string>> cyk;
map<string, string> pd;
map<string, vector<string>> grammar;

// Armazena a gramatica dada no input
void getGrammar() {
    //int n;
    //cin >> n;

    //while (n--) {
    //    string a, b;
    //    grammar[a].push_back(b);
    //}

    grammar["S"] = vector<string>({"AX", "AB"});
    grammar["R"] = vector<string>({"AX", "AB"});
    grammar["X"] = vector<string>({"RB", "b"});
    grammar["A"] = vector<string>({"a"});
    grammar["B"] = vector<string>({"b"});   
}

// Verifica se a string c é produto cartesiano das strings a e b
bool isCartesianProduct(string a, string b, string c) {
    for (int i = 0, n = a.length() * b.length(); i < n; i++) {
        string product = string() + a[i / b.size()] + b[i % b.size()];
        if (product == c) return true;
    }

    return false;
}

void dp(string w) {
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
                                if (pd[subW].find(a) == string::npos) {            
                                    pd[subW] = (pd[subW] == "") ? a : pd[subW] + a;
                                }

                                cyk[ns - 1][i] = pd[subW];
                            }
                        } catch(...) {}
                    }
                }        
            }
        }   
    }    
}

int main() {    
    getGrammar();

    string w;
    while (getline(std::cin, w) and w.compare("*")) {
        cyk = vector<vector<string>> (w.length(), vector<string> (w.length(), ""));  
        dp(w);
        cout << w << ": " << ((cyk[w.length() - 1][0].find("S") != string::npos) ? "SIM" : "NAO") << endl;
    }

    return 0;
}