#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
using namespace std;

struct Node{
    Node* next[26] ={nullptr};
    vector<pair<size_t, int>> values;
    bool endFlag = false;
    ~Node(){
        for(Node* p:next){
            delete p;
        }
    }
};

void insert(Node* p, const string& s, int val, size_t idx){
    const char* pStr = &s[0];
    while(*pStr){
        if(p->next[*pStr-'a'] == nullptr){
            p->next[*pStr-'a'] = new Node();
        }
        p = p->next[*pStr-'a'];
        pStr++;
    }
    p->values.emplace_back(idx, val);
    p->endFlag = true;
}

size_t query(Node* root, const string& s, size_t ssIdx, size_t seIdx,  size_t startIdx, size_t endIdx){
    Node* p = root;
    size_t result =0;
    for(size_t idx = ssIdx; idx< seIdx; ++idx){
        if(p->next[s[idx] - 'a' ] == nullptr){
            return result;
        }
        p = p->next[ s[idx] -'a'];
        if(p->endFlag){
            for(auto [index, val] : p->values){
                if( index <startIdx)
                    continue;
                else if( index >endIdx)
                    break;
                else{
                    result += val;
                }
            }
        }
    }


    return result;
}


int main()
{
    int n;
    cin>>n;
    vector<string> dnaPattern(n);

    for(int i=0; i<n;++i){
        cin>>dnaPattern[i];
    }

    Node root;
    for(int i =0 ; i<n; ++i){
        int value;
        cin>>value;
        insert(&root, dnaPattern[i], value, i);
    }

    int t;
    cin>>t;
    size_t minHealth = numeric_limits<size_t>::max();
    size_t maxHealth = 0;
    while(t--){
        int s, e;
        string dna;
        cin>>s>>e;
        cin>>dna;

        size_t ret = 0;
        size_t len = dna.size();
        for(int i =0; i< len; ++i){
            ret += query(&root, dna, i, len, s, e);
        }
        if(ret >maxHealth)
            maxHealth = ret;
        if(ret <minHealth)
            minHealth = ret;


    }
    cout<<minHealth <<" " << maxHealth <<endl;

    return 0;
}

