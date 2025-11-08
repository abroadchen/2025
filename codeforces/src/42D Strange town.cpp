//
// Created by Psy.C on 2025/9/25.
//
/*
*这是一个贪心构造过程
每一步都选择最小的未被使用的正整数
通过四重循环确保新选择的数不会与已有数组成特定的线性关系
 *
 *
 */
#include <ios>
#include <iostream>
using namespace std;
const int N = 100005, M = 25;
int n, f[M];
bool vis[N];

int main() {

    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cin >> n;
    f[1]=1; f[2]=2; vis[3]=1;
    for (int i = 3; i <= n; ++i) {
        for (int x = 1; x < i; ++x) {
            for (int y = x + 1; y < i; ++y) {
                for (int z = 1; z < i; ++z) {
                    if (f[x] + f[y] - f[z] >= 0)
                        vis[f[x] + f[y] - f[z]] = 1;
                }
            }
        }
        f[i] = 1;
        while (vis[f[i]]) f[i]++;
    }

    for (int i = 1; i <= n; ++i, cout << '\n')
        for (int j = 1; j <= n; ++j)
            cout << (i == j ? 0 : f[i] + f[j]) << ' ';
    return 0;
}