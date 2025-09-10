//
// Created by Psy.C on 2025/9/10.
//

#include <iostream>
#include <vector>
#include <map>
using namespace std;
int main()
{
    int n;
    cin >> n;

    vector<pair<string, int>> rounds(n);
    map<string, int> final_scores;

    for(int i = 0; i < n; i++) {
        string name;
        int score;
        cin >> name >> score;
        rounds[i] = {name, score};

        final_scores[name] += score;
    }

    int max_score = 0;
    for(auto& player : final_scores) {
        max_score = max(max_score, player.second);
    }

    vector<string> candidates;
    for(auto& player : final_scores) {
        if(player.second == max_score) {
            candidates.push_back(player.first);
        }
    }

    if(candidates.size() == 1) {
        cout << candidates[0] << endl;
        return 0;
    }

    map<string, int> current_scores;
    for(int i = 0; i < n; i++) {
        string name = rounds[i].first;
        int score = rounds[i].second;

        current_scores[name] += score;

        if(find(candidates.begin(), candidates.end(), name) != candidates.end()
            && current_scores[name] >= max_score) {
            cout << name << endl;
            return 0;
        }
    }
    return 0;
}
