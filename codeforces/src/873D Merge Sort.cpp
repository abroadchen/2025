//
// Created by Psy.C on 2026/10/6.
//
/**
dfs(l, r) 处理区间 [l, r)（左闭右开）。
终止条件：
!k：配额用完了，停止。
l >= r-1：区间长度不足 2，无法再交换，停止。
否则：取中点 mid = (l+r)>>1（下取整），交换 a[mid-1] 和 a[mid]，消耗一次配额 --k。
然后递归处理左右两个子区间 dfs(l, mid) 和 dfs(mid, r)。
注意：这个交换不是在"中点两边的两个元素"做对称交换，而是只交换中点正中间相邻的两个元素 a[mid-1] 和 a[mid]
先判断 k % 2 == 0：如果 k 是偶数，直接输出 -1 返回（说明输入的 k 必须为奇数才可能有解）。
k /= 2：把配额减半。结合上一行，说明实际允许的操作步数是 k/2（因为 k 必须是奇数，所以 k/2 是整数）。
初始排列设为 a[i] = i，即 1,2,3,...,n。
调用 dfs(1, n+1) 开始构造。
如果递归结束后 k 还没用完（if (k)），说明给出的步数超出了这棵树能提供的最大可交换数，无解，输出 -1。
否则输出构造好的排列
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;

int a[N], k;
void dfs(int l, int r) {
    if (!k || l >= r-1) return;
    int mid = (l+r)>>1;
    swap(a[mid-1], a[mid]); --k;
    dfs(l, mid); dfs(mid, r);
}

int n;
void solve() {
    if (k%2 == 0) return cout << "-1\n", void();
    k /= 2;
    for (int i = 1; i <= n; ++i) a[i] = i;
    dfs(1, n+1);
    if (k) return cout << "-1\n", void();
    for (int i = 1; i <= n; ++i) cout << a[i] << ' ';
    cout << '\n';
}


int main() {
    fast;
    cin >> n >> k;
    solve();
    return 0;
}