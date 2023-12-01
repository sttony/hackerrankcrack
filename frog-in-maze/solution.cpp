#include <iostream>
#include <vector>
#include <map>


using namespace std;

void dumpMatrix(const vector<vector<double>> & m )
{
    for(const auto& row : m){
        for(const auto& cell : row){
            printf("%02f, ", cell);
        }
        cout<<";"<<endl;
    }
}

void dumpState(const vector<pair<int, double>> & s )
{
    for(const auto& row : s) {
        printf("%d:%.9f, ", row.first, row.second);
    }
    cout<<endl;
}

int main()
{
    int n, m, k;
    cin>>n>>m>>k;
    vector<vector<char>>  maze( n, vector<char>(m, 0));
    map<pair<int, int>,  pair<int, int>> adjust;

    for(int i =0; i<n; ++i){
        for(int j =0; j< m; ++j){
            cin>> maze[i][j];
        }
    }

    for(int i=0; i<k; ++i){
        int x1, y1, x2, y2;
        cin>>x1>>y1>>x2>>y2;
        adjust[make_pair(x1-1, y1-1)] = make_pair(x2-1, y2-1);
        adjust[make_pair(x2-1, y2-1)] = make_pair(x1-1, y1-1);
    }

    vector<vector<pair<int, double>>>  markovMatrix( n*m, vector<pair<int, double>>());
    map<int, double> state;

    static pair<int, int> offsets[4] = {
            {-1, 0},
            {+1, 0},
            {0, -1},
            {0, +1}
    };
    int count_space=0;
    for(int i =0; i<n; ++i){
        for(int j =0; j<m; ++j){
            if( maze[i][j] == 'A'){
                state[i*m +j]=1.0;
            }
            else if( maze[i][j] == '#'){
                continue;
            }
            else if( maze[i][j] == '*'){
                continue;
            }
            else if( maze[i][j] == 'O'){
                count_space++;
            }

            vector<pair<int, int>> possible_moves;
            for(auto [x, y] : offsets){
                if( i+x >=0 && i+x <n &&
                    j+y >=0 && j+y <m ){
                    if( maze[i+x][j+y] == '#'){
                        continue;
                    }
                    else if( maze[i+x][j+y] == 'O'){
                        auto it = adjust.find( make_pair(i+x, j+y));
                        if(it != adjust.end()){
                            possible_moves.push_back(it->second);
                        }
                        else{
                            possible_moves.push_back(make_pair(i+x, j+y));
                        }
                    }
                    else {
                        possible_moves.push_back(make_pair(i+x, j+y));
                    }
                }
            }

            for(auto [x,y]: possible_moves){
                markovMatrix[i*m+j].push_back(make_pair( x*m+y, 1.0/possible_moves.size()));
            }
        }
    }
    //dumpMatrix(markovMatrix);
    double ret = 0.0;
    double err = 1.0;
    double pre_ret = 0.0;
    int delay = count_space;
    double eps = 1e-10;
    while( err>ret*eps){
        map<int, double>  tempState;
        for(auto item : state ){
            for( auto cell :  markovMatrix[item.first]){
                if(maze[cell.first/m][cell.first%m] == '%') {
                    ret += item.second* cell.second;
                }
                else if(maze[cell.first/m][cell.first%m] == '*') {
                }
                else {
                    tempState[cell.first] += item.second * cell.second;
                }
            }
        }

        //dumpState(tempState);
        swap(tempState, state);
        err = ret - pre_ret;
        if( err ==0  ){
            if(delay >0){
                err = 1.0;
                delay --;
            }
        }
        else{
            delay = count_space;
        }
        pre_ret = ret;
        //printf("%.9lf\n", ret);
    }
    printf("%.9lf\n", ret);
    return 0;
}
