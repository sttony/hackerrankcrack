#include <iostream>
#include <map>

using namespace std;

int main()
{
    int scores_count;
    cin >> scores_count;
    map<int, int, std::greater<>> score_to_rank;
    int current_rank=1;
    int current_score = 0;
    cin>>current_score;
    score_to_rank.insert({current_score, current_rank});
    for(int i =1; i< scores_count; ++i){
        int score;
        cin >>score;
        if(score != current_score){
            current_rank++;
            score_to_rank.insert({score, current_rank});
            current_score = score;
        }

    }
    int m;
    cin >> m;
    for(int i = 0; i< m; ++i){
        int q;
        cin>>q;
        auto it = score_to_rank.lower_bound(q);
        if(it!= score_to_rank.end() ){
            cout<< it->second <<endl;
        }
        else{
            cout<< score_to_rank.size()+1<<endl;
        }
    }
    return 0;
}