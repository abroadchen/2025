//
// Created by Psy.C on 2026/1/12.
//
/**
* m：需要选择的元素个数
a[N]：存储选择结果的数组
s：输入的约束字符串
 *
*n：当前处理的位置（1到m）
d：上一步的差值
如果 n > m，说明已经成功选择了m个数，返回成功标志1
*i = d + 1：从 d + 1 开始遍历（保证单调性）
i <= 10：限制上界为10
s[i-1] == '1'：只有当约束字符串对应位置为'1'时才能选择
i != a[n-1]：当前选择不能等于前一个选择
a[n] = i：将i放入结果数组的第n位
dfs(n + 1, i - d)：递归处理下一个位置，新的差值为 i - d
 *
* 如果 dfs(n + 1, i - d) 返回0（失败）
函数会继续for循环，尝试下一个i值
前一个i的尝试被自动"撤销"（因为会被新的值覆盖或函数结束）
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 1005
using namespace std;

ll m, a[N];
string s;//字符串 s 的索引从 0 开始
ll dfs(const ll n, const ll d) {
    if (n > m) return 1;
    for (ll i = d + 1; i <= 10; ++i) if (s[i-1] == '1' && i != a[n-1]) {
        a[n] = i;//尝试一个可能的解
        if (dfs(n + 1,  i - d)) return 1;
    }
    return 0;
}


int main() {
    fast;
    cin >> s >> m;
    if (dfs(1, 0)) {
        cout << "YES\n";
        for (int i = 1; i <= m; ++i) cout << a[i] << ' ';
    } else {
        cout << "NO\n";
    }
    return 0;
}