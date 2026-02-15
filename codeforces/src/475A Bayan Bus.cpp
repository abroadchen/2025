//
// Created by Psy.C on 2026/2/15.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

char s[6][30] = {
    "+------------------------+",
    "|#.#.#.#.#.#.#.#.#.#.#.|D|)",
    "|#.#.#.#.#.#.#.#.#.#.#.|.|",
    "|#.......................|",
    "|#.#.#.#.#.#.#.#.#.#.#.|.|)",
    "+------------------------+",
};
int k;

int main() {
    fast;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        bool flag = true;
        for (int j = 1; j < 30 && flag; j += 2)//奇数列
            for (int l = 1; l < 6 && flag; ++l)
                if (s[l][j] == '#') {
                    s[l][j] = 'O';
                    flag = false;
                    break;
                }
    }
    for (const auto& i : s) cout << i << '\n';
    return 0;
}