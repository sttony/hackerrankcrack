#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
using namespace std;

int main() {
    int T;
    cin >> T;

    for (int i = 0; i<T; ++i) {
        int len, A, B;
        cin >> len >> A >> B;
        string strBuff;
        cin >> strBuff;
        const char* str = strBuff.c_str();
        vector<unsigned long long> values(len);
        values[0] = A;

        vector<int> dict[26];
        dict[str[0] - 'a'].push_back(0);

        for (int j = 1; j < len; ++j) {
            unsigned long long minCost = values[j - 1] + A;
            int r = j;
            int l = j - 1;
            for(int kd= dict[str[j]-'a'].size()-1; kd >=0; --kd){
                l = dict[str[j] - 'a'][kd];
                int xlen = 1;
                int maxL = min(l, r - l-1);
                while (xlen <= maxL
                       && str[l - xlen] == str[r - xlen])
                    xlen++;


                if (minCost > values[r - xlen] + B) {
                    minCost = values[r - xlen] + B;
                }
            }
            dict[str[j] - 'a'].push_back(j);
            values[j] = minCost;
        }
        cout << values[len - 1] << endl;
    }

    return 0;
}
