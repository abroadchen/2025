//
// Created by Psy.C on 2026/2/4.
//
/**
* 前半部分（1到S）：存储历史状态，用于一致性检查
后半部分（S+1到2S）：存储当前可用位置
 *
*单次查询：O(log²n)，二分查找×树状数组操作
总体复杂度：O(m log²n + n)，其中m是查询数，n是序列长度
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 1e6+7, S = N-4;

int cnt[N<<1];
void update(const int p, const int c) {
    for (int i = p; i <= S+S; i += i&-i) cnt[i] += c;
}
int query(const int p) {//位置1到p的元素总和
    int res = 0;
    for (int i = p; i; i -= i&-i) res += cnt[i];
    return res;
}

int main() {
    fast;
    int n, m; cin >> n >> m;
    //树状数组的后半部分（S+1到2S）初始化为1
    for (int i = 1; i < S+1; ++i) update(i + S, 1);
    int p = S, ans[N], pre[N<<1]; bool vis[N];
    for (int i = 1, v, x; i < m+1; ++i) {
        cin >> v >> x;
        int l = 1, r = S+S, res = -1;
        while (l <= r) {
            if (const int mid = (l + r) >> 1; query(mid) < x) {//第x个可用位置
                res = mid + 1;
                l = mid + 1;
            } else r = mid - 1;
        }
        if (res > S) {
            if (vis[v]) { cout << "-1\n"; return 0; }
            vis[v] = true;
            ans[res - S] = v;//位于后半部分，分配给新元素
        } else {//位于前半部分，必须与之前相同
            if (pre[res] != v) { cout << "-1\n"; return 0; }
        }
        update(res, -1);//移除当前位置
        update(p, 1);//添加到前半部分
        pre[p] = v;//记录该位置的值
        --p;//更新指针
    }
    for (int i = 1, j = 1; i <= n; ++i) if (!ans[i]) {//填充未确定的位置
        while (vis[j]) ++j;//每个数字恰好使用一次
        ans[i] = j;
        vis[j] = true;
    }
    for (int i = 1; i < n + 1; ++i) cout << ans[i] << " \n"[i==n];
    return 0;
}