#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <fstream>
using namespace std;


struct Node{
    int leftNumber ;
    int rightNumber;
    size_t pLeft;
    size_t pRight;
    int data;
    int count;
    Node(){
        leftNumber =0;
        rightNumber =0;
        pLeft = -1;
        pRight = -1;
        data = 0;
        count = 0;
    }
};

size_t insert(vector<Node>& nodesBuff, size_t rootIdx, int d){
    size_t ret = 0;
    size_t p = rootIdx;

    for(int i = 24; i >0; --i){
        int mask = 0x01<<(i-1);
        if((d & mask) == 0){
            nodesBuff[p].leftNumber ++;
            ret += (nodesBuff[p].rightNumber + nodesBuff[p].count);
            if(nodesBuff[p].pLeft==-1){
                nodesBuff.emplace_back();
                nodesBuff[p].pLeft = nodesBuff.size()-1;
            }
            p = nodesBuff[p].pLeft;
        }else{
            nodesBuff[p].rightNumber ++;
            if(nodesBuff[p].pRight==-1){
                nodesBuff.emplace_back();
                nodesBuff[p].pRight = nodesBuff.size()-1;
            }
            p = nodesBuff[p].pRight;
        }
    }
    nodesBuff[p].count++;
    nodesBuff[p].data = d;

    return ret;
}


size_t fun(istream& xin, int N){

    size_t ret = 0;
    int maxN = 0;
    vector<Node> nodes;
    nodes.reserve(1024*1024);
    nodes.emplace_back();
    size_t  rootIdx  = nodes.size()-1;

    for(int i=0; i<N; ++i){
        int a ;
        xin >>a;
        ret = ret + insert(nodes, rootIdx, a);
    }

    return ret;
}

int main() {
    int T;
    cin>>T;

    for(int i =0; i<T; ++i){
        int N;
        cin>>N;
        cout<<fun(cin, N)<<endl;
    }
}
