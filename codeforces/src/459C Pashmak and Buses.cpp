//
// Created by Psy.C on 2026/2/11.
//
/**
d, k, n：问题参数//n(需要的组合数)，k(每维选项数)，d(维度数)
s[N][N]：存储结果矩阵
now：当前填充的列索引
a[N]：临时数组，用于DFS路径记录

可行性检查：O(d)
DFS生成：O(n×d)
总体：O(n×d)
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 1002
using namespace std;

ll d, k, n;
///d维空间，每维有k个选项，总共k^d种组合
bool ok() {//是否有解
    ll ans = 1;
    for (ll w = d; w > 0; --w) {
        ans *= k;
        if (ans >= n) return true;
    }
    return false;
}

ll s[N][N], now, a[N];
bool dfs(const int tot) {
    if (tot == d) {//d个维度都已确定
        for (int i = 0; i < tot; ++i) s[i][now] = a[i];//保存当前组合
        now++;//准备填充下一列
        if (now == n) return true;//已生成n个不同的组合
        return false;
    }
    for (int i = 1; i <= k; ++i) {//枚举第tot维的所有可能值
        a[tot] = i;//记录当前维度的值
        if (dfs(tot + 1)) return true;//递归处理下一维度
    }
    return false;
}

void out() {
    for (int i = 0; i < d; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j) cout << ' ';//除了第一列，前面加空格
            cout << s[i][j];
        }
        cout << '\n';
    }
}

int main() {
    fast;
    cin >> n >> k >> d;
    if (ok()) {
        memset(s, 0, sizeof(s)); now = 0; dfs(0);
        out();
    } else cout << "-1\n";
    return 0;
}