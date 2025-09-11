//
// Created by Psy.C on 2025/9/11.
//


#include <ios>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;
    int n = s.length();

    vector<int> dp(n, 0);

    for (int i = 1; i < n; i++) {
        if (s[i] == ')') {
            if (s[i - 1] == '(') {//()
                dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
            }
            else if (dp[i - 1] > 0) {//))
                int match_index = i - dp[i - 1] - 1;
                if (match_index >= 0 && s[match_index] == '(') {
                    dp[i] = dp[i - 1] + 2 + (match_index > 0 ? dp[match_index - 1] : 0);
                }
            }
        }
    }

    int max_length = 0;
    for (int i = 0; i < n; i++) {
        max_length = max(max_length, dp[i]);
    }

    int count = 0;
    for (int i = 0; i < n; i++) {
        if (dp[i] == max_length) count++;
    }

    if (max_length == 0) cout << "0 1\n";
    else cout << max_length << " " << count << "\n";

    return 0;
}