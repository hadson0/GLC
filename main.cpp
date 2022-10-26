#include <bits/stdc++.h>

using namespace std;

vector<vector<string>> cyk;
map<string, vector<string>> grammar;

void getGrammar() {
    int n;
    cin >> n;

    while (n--) {
        string a, b;
        grammar[a].push_back(b);
    }
}

// Verifica se a string c é produto cartesiano das strings a e b
bool isCartesianProduct(string a, string b, string c) {
    string product;

    for (int i = 0; i < product.size(); i++) {
        product = a[i / b.size()] + b[i % b.size()];
        if (product == c) return true;
    }

    return false;
}


void dp(string w) {
    int n = w.size();
    cyk = vector<vector<string>> (5, vector<string> (5));

    for (int i = 0; i < n; i++) {
        for (auto it = grammar.begin(); it != grammar.end(); it++) {
            string a = it->first;
            vector<string> b = it->second;

            for (int j = 0; j < b.size(); j++) {
                if (w[i] == b[j][0] and b[j].length() == 1) {
                    cyk[i][i] = (cyk[i][i] == "") ? cyk[i][i] : cyk[i][i] + a;
                }                
            }
        }
    }
    
    for (int l = 2; l <= n; l++) {        
        for (int i = 0; i <= n - l; i++) {
            int j = i + l - 1;
            for (int k = i; l < j; k++) {
                for (auto it = grammar.begin(); it != grammar.end(); it++) {
                    string a = it->first;
                    vector<string> b = it->second;

                    for (int j = 0; j < b.size(); j++) {
                        if (b[j].length() == 2) {
                            if (isCartesianProduct(cyk[i][k], cyk[k + 1][j], b[j])) {
                                cyk[i][j] = (cyk[i][j] == "") ? cyk[i][j] : cyk[i][j] + a;
                            }
                        }
                    }
                }
            }
        }
    }
}

int main() {
    getGrammar();
    
    return 0;
}