#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
using namespace std;


int main() {
    int N, k;
    cin>>N>>k;
    int X, Y;
    cin>>X>>Y;
    unordered_set<int64_t> obstacles;
    for(int i =0; i< k; ++i)
    {
        int x, y;
        cin>>x>>y;
        int64_t v = (int64_t)x<<32 | (int64_t)y;
        obstacles.insert(v);
    }
    pair<int, int> directions[8] = {
            {+1, 0},
            {-1, 0},
            {0, +1},
            {0, -1},
            {+1, +1},
            {+1, -1},
            {-1, +1},
            {-1, -1}
    };
    int ret = 0;
    for(auto direction:directions)
    {
        bool stop = false;
        int currentX=X;
        int currentY=Y;
        while(!stop)
        {
            int newX= currentX+ direction.first;
            int newY = currentY+direction.second;
            int64_t newPlace= (int64_t)(newX)<<32 | (int64_t)(newY);
            if( newX <=0 || newX > N ||
                newY<=0 || newY> N)
            {
                stop=true;
                break;
            }
            if(obstacles.find(newPlace) != obstacles.end())
            {
                stop = true;
                break;
            }
            currentX = newX;
            currentY = newY;
            ret++;
        }
    }
    cout<<ret<<endl;
    return 0;
}
