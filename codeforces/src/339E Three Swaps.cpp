//
// Created by Psy.C on 2026/1/12.
//
/**
* n：数组长度
a[N]：待排序的数组
 *
*检查数组是否已经变成 [1, 2, 3, ..., n]
如果已排序，输出操作次数和具体操作
 *如果已经进行了3次操作但仍未排序，返回false
 *
*外层循环：选择左端点 l
内层循环：选择右端点 r
条件检查：
a[l] != l：位置 l 的值不是 l
abs(a[l]-a[l-1])>1 || abs(a[l]-a[l+1])>1：当前位置与相邻位置的差值大于1
*for 循环：反转区间 [L, R]
swap(a[i],a[R-i+L])：将 a[i] 与 a[R-i+L] 交换，实现区间反转
记录操作到 q[k+1]
*如果后续搜索成功，恢复数组状态（撤销反转操作）
返回 true
*如果当前操作不能达到目标，撤销操作
继续尝试其他可能的反转区间
 *
 *设置边界哨兵值（避免边界检查）
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1010
using namespace std;

struct node { int l, r; } q[4];

int n, a[N];
bool dfs(const int k) {
    bool ok = true;
    for (int i = 1; i <= n; ++i) if (a[i] != i) { ok = false; break; }
    if (ok) {
        cout << k << '\n';
        for (int i = k; i; --i) cout << q[i].l << ' ' << q[i].r << '\n';
        return true;
    }
    if (k == 3) return false;
    for (int l = 1; l <= n; ++l) if (a[l]!=l&&(abs(a[l]-a[l-1])>1||abs(a[l]-a[l+1])>1)) {
        for (int r = l + 1; r <= n; ++r) if (a[r]!=r&&(abs(a[r]-a[r-1])>1||abs(a[r]-a[r+1])>1)) {
            int L = l, R = r;
            for (int i = L; i <= (L+R)>>1; ++i) swap(a[i],a[R-i+L]);
            q[k+1] = {L, R};
            if (dfs(k + 1)) {
                L = q[k+1].l; R = q[k+1].r;
                for (int i = L; i <= (L+R)>>1; ++i) swap(a[i],a[R-i+L]);
                return true;
            }
            L = q[k+1].l; R = q[k+1].r;
            for (int i = L; i <= (L+R)>>1; ++i) swap(a[i],a[R-i+L]);
        }
    }
    return false;
}

int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    a[0] = a[n+1] = -1;
    dfs(0);
    return 0;
}