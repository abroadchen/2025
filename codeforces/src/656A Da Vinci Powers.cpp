//
// Created by Psy.C on 2026/4/8.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll st[] = {
    1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096,
    8092, 16184, 32368, 64736, 129472, 258944, 517888, 1035776,
    2071552, 4143104, 8286208, 16572416, 33144832, 66289664, 132579328,
    265158656, 530317312, 1060634624, 2121269248, 4242538496, 8485076992,
    16970153984, 33940307968
};

int n;
int main() {
    fast;
    cin >> n;
    cout << st[n] << '\n';
    return 0;
}