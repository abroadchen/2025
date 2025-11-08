//
// Created by Psy.C on 2025/9/18.
//

#include <ios>
#include <iostream>
#include <set>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    
    string input;
    getline(cin, input);
    int output(0);

    for (size_t i = input.size() - 1; i >= 1; --i) {
        if (output > 0) break;
        set<string> present;

        for (size_t j = 0; j < input.size() - i + 1; ++j) {
            string current = input.substr(j, i);
            if (present.find(current) == present.end())
                present.insert(current);
            else {
                output = i;
                break;
            }
        }
    }

    cout << output << endl;
    return 0;
}