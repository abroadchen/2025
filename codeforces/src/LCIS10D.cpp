//
// Created by Psy.C on 2025/9/14.
//



#include <iostream>
#include <vector>
using namespace std;



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m; cin >> n;
    int arr1[n];
    for (int i = 0; i < n; ++i) cin >> arr1[i];
    cin >> m;
    int arr2[m], dp[m], parent[m];
    for (int i = 0; i < m; ++i) cin >> arr2[i];
    for (int i = 0; i < m; ++i) dp[i] = 0;

    for (int i = 0; i < n; ++i) {
        int curr = 0, last_one = -1;
        for (int j = 0; j < m; ++j) {
            if (arr1[i] == arr2[j]) {
                if (curr + 1 > dp[j]) {
                    dp[j] = curr + 1;
                    parent[j] = last_one;
                }
            }
            if (arr1[i] > arr2[j]) {
                if (dp[j] > curr) {
                    curr = dp[j];
                    last_one = j;
                }
            }
        }
    }

    int ans = 0, index;
    for (int i = 0; i < m; ++i) {
        if (dp[i] > ans) {
            ans = dp[i];
            index = i;
        }
    }

    vector<int> res;
    if (ans > 0) {
        while (index != -1) {
            res.push_back(arr2[index]);
            index = parent[index];
        }
    }
    cout << ans << endl;
    for (int i = ans - 1; i >= 0; --i) cout << res[i] << " ";
    cout << endl;
    return 0;
}