//
// Created by Psy.C on 2025/9/19.
//

#include <ios>
#include <iostream>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    
    string input; getline(cin, input);
    long unmatched(0), matched(0);

    for (int i = 0; i < input.size(); ++i) {
        if (input[i] == '(') ++unmatched;
        else if (input[i] == ')' && unmatched > 0) {
            --unmatched;
            ++matched;
        }
    }

    cout << 2 * matched << endl;

    return 0;
}