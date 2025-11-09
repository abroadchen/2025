//
// Created by Psy.C on 2025/9/12.
//


#include <iosfwd>
#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

string line;
typedef long long LL;
vector<int> val(5000001);
const LL BASE = 123;

int main(int argc, char **argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (argc > 0) freopen(argv[1], "r", stdin);
    if (argc > 1) freopen(argv[2], "w", stdout);
    cin >> line;
    LL h1 = 0, h2 = 0, pBase = 1, res = 0;
    val.resize(line.size() / 2 + 1);

    for (int i = 0; i < line.size(); i++) {
        h1 = h1 * BASE + line[i];
        h2 = h2 + line[i] * pBase;
        pBase = pBase * BASE;
        int cur = 0;
        if (h1 == h2) cur = val[(i + 1) / 2] + 1;
        res += cur;
        if (i + 1 < val.size()) val[i + 1] = cur;
    }
    cout << res << endl;

    return 0;
}