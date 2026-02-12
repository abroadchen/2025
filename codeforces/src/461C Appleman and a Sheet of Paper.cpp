//
// Created by Psy.C on 2026/2/12.
//
/**
情况1（p ≤ 区间长度/2）：

从区间前p个元素复制到后面
更新左/右边界
情况2（p > 区间长度/2）：

从区间后p个元素复制到前面
更新区间边界并切换方向
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 101000
using namespace std;

inline int low_bit(const int x) { return x & -x; }

int n, a[N];
void add(const int p, const int v) {//将位置p的值增加v
    for (int i = p; i <= n; i += low_bit(i)) a[i] += v;
}
int sum(const int p) {//计算从1到p的前缀和
    int ans = 0;
    for (int i = p; i; i -= low_bit(i)) ans += a[i];
    return ans;
}

int q;
int main() {
    fast;
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) add(i, 1);//每个位置的初始值设为1
    //当前方向状态（0表示正向，1表示反向）
    int flag = 0, l = 1, r = n;//有效区间左端点 右端点
    while (q--) {
        int k; cin >> k;//操作类型（1或2）
        if (k == 1) {//区间操作
            int p; cin >> p;
            if (p <= (r-l+1)/2) {//小于等于区间长度的一半
                if (flag == 0) {
                    for (int i = p+l-1, j = p + l; i >= l; --i, ++j)
                        add(j, sum(i) - sum(i-1));
                    l = l + p;
                } else {
                    for (int i = r-p, j = r-p+1; j <= r; --i, ++j)
                        add(i, sum(j) - sum(j-1));
                    r = r - p;
                }
            } else {
                if (flag == 0) {
                    for (int i = l+p-1, j = p+l; j <= r; ++j, --i)
                        add(i, sum(j) - sum(j-1));
                    r = l + p - 1;
                } else {
                    for (int i = r-p, j = r-p+1; i >= l; --i, ++j)
                        add(j, sum(i) - sum(i-1));
                    l = r - p + 1;
                }
                flag ^= 1;
            }
        }
        else if (k == 2) {///区间查询
            int L, R; cin >> L >> R; L++;//从1开始
            if (flag == 0) {
                L = l + L - 1; R = l + R - 1;
                cout << sum(R) - sum(L - 1) << '\n';
            } else {
                L = r - L + 1; R = r - R + 1;
                cout << sum(L) - sum(R - 1) << '\n';
            }
        }
    }
    return 0;
}