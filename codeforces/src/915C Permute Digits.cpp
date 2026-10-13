//
// Created by Psy.C on 2026/10/13.
//
/**
把可用数字 a 从大到小排序【1† 的思路：排序确定取数顺序】。
若可用数字个数 la < lb（凑不满 b 的位数），直接输出降序排列就是"位数更短下的最大值"，结束
逐位构造 c：v[j] 标记 a[j] 是否被用过（每个数最多用一次）。对第 i 位，降序找第一个 ≤ b[i] 且未用过的数字放进去【2† 的核心：依次尝试比当前位小的最大数字】。

a[j] != b[i] 说明该位没能取到"正好等于 b[i] 的数"，分为两种情况处理：

若 j == la（降序全扫完都没有 ≤ b[i] 的未用数字）‍：这一位放不了足够小的数，说明之前的选法需要调整 → 回溯到上一位 dfs(i-1)。
否则（取到了某个 < b[i] 的数）‍：这一位严格更小，之后所有位贪心地填满剩余最大可用数字然后输出
dfs(x) 回到第 x 位：先回退该位已放的字符 s=b[x]，并把占用的 a[j]==s 标记清掉（归还）。
重新降序找第一个严格小于 b[x] 且未用过的数字：放进去（该位严格更小）。找得到 → 后面各位填满最大剩余数并输出；找不到 → 继续往前回溯 dfs(x-1)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 110;

bool cmp(char e, char f) { return e > f; }
char b[N], a[N];
string c;
int la, v[N];
void dfs(int x) {
    char s = b[x]; c = c.substr(0, c.size()-1);//撤掉第 x 位的选择
    int i, j;
    for (i = 0; i < la; ++i)
        if (a[i] < s && !v[i]) { c += a[i]; v[i] = 1; break; }
    for (j = 0; j < la; ++j)
        if (a[j] == s && v[j]) { v[j] = 0; break; }
    if (i == la) dfs(x-1);//仍放不满 → 继续往前回溯
    else {
        for (i = 0; i < la; ++i)
            if (!v[i]) c += a[i];//剩余位填满最大可用数
        cout << c;
        exit(0);
    }
}

int lb, i, j;
int main() {
    fast;
    cin >> a >> b; la = strlen(a), lb = strlen(b);
    sort(a, a+la, cmp);
    if (la < lb) {//可用数字比目标短 → 直接输出最大排列
        for (i = 0; i < la; ++i) cout << a[i];
        return 0;
    }
    for (i = 0; i < lb; ++i) {
        for (j = 0; j < la; ++j) {
            if (a[j] <= b[i] && !v[j]) { c += a[j]; v[j] = 1; break; }
        }
        if (a[j] != b[i]) {
            if (j == la) dfs(i-1);
            else {
                for (j = 0; j < la; ++j)
                    if (!v[j]) c += a[j];
                cout << c;
                return 0;
            }
        }
    }
    cout << c;
    return 0;
}