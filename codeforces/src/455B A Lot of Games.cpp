//
// Created by Psy.C on 2026/2/11.
//
/**
SG值为0 → 转换为3
SG值为1 → 转换为2
SG值为2 → 转换为1
SG值为3 → 转换为0
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100007
using namespace std;

int t[N][26];//节点 i 在第 j 个字母（a-z）下的子节点编号
int dfs(const int x) {
    int ans = 0, flag = true;
    for (int i = 0; i < 26; ++i) if (t[x][i]) {//存在以字母 i ('a'+i) 为边的子节点
        flag = false;//不是叶子节点
        ans |= dfs(t[x][i]);
    }
    ans ^= 3;
    if (flag) ans = 1;
    return ans;
}

int n, k, sz;
char str[N];

int main() {
    fast;
    cin >> n >> k;
    for (int i = 0, now; i < n; ++i) {
        cin >> str; now = 0;
        for (int j = 0; j < strlen(str); ++j) {
            if (!t[now][str[j] - 'a'])//当前字符对应子节点不存在，则创建新节点
                t[now][str[j] - 'a'] = ++sz;
            now = t[now][str[j] - 'a'];//到下一个节点
        }
    }
    if (const int ans = dfs(0); !ans || (k&1 && ans == 2)) cout << "First\n";
    else cout << "Second\n";
    return 0;
}