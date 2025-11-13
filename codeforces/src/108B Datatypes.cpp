//
// Created by Psy.C on 2025/11/13.
//

#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main() {
    int n; scanf("%d",&n);
    vector<int> bits(n, 0);

    for (int i = 0; i < n; ++i) scanf("%d",&bits[i]);
    sort(bits.begin(), bits.end());

    string ans = "NO";
    for (int i = 1; i < n; ++i) {
        if (bits[i - 1] != bits[i] &&
            2 * bits[i - 1] > bits[i]) {
            ans = "YES";
            break;
        }
    }
    printf("%s\n",ans.c_str());
    return 0;
}