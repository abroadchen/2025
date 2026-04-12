//
// Created by Psy.C on 2026/4/12.
//
/**

if (n <= 1000)        N = 3e4;     // 30倍
else if (n <= 1e4)    N = 3e5;     // 30倍
else if (n <= 1e5)    N = 2e6;     // 20倍
else if (n <= 1e6)    N = 3e7;     // 30倍
else                  N = 5e7;     // 50倍

tr[N][2]: 字典树结构，每个节点有2个子节点（二进制0或1）
tot: 使用的字典树节点总数
cnt[N]: 通过每个字典树节点的数字计数

将数字x插入二进制字典树
从最重要的位（第30位）迭代到最不重要的位（第0位）
x>>i&1: 提取x的第i位
如果节点不存在则创建新节点
在路径上的每个节点增加计数

计算字典树中与x的XOR ≤ k的数字数量
对于每个位位置，根据x和k的当前位决定要跟随哪个分支
如果k的当前位是1，我们可以采取两个分支，但需要适当计数
如果k的当前位是0，我们只能沿着相同的XOR结果分支走下去

初始化答案并将0插入字典树（用于从索引0开始的子数组）
对于每个前缀XOR，计算有多少个先前的前缀形成XOR ≤ k的子数组
将当前前缀XOR添加到字典树以供将来查询
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 3e7+5, M = 1e6+5;

int tr[N][2], tot, cnt[N];
void insert(int x) {
    int rt = 0;
    for (int i = 30; i >= 0; --i) {
        int now = x>>i&1;
        if (!tr[rt][now]) tr[rt][now] = ++tot;
        rt = tr[rt][now];
        cnt[rt]++;
    }
}
int get(int x, int k) {
    int ans = 0, rt = 0;
    for (int i = 30; i >= 0; --i) {
        int nx = x>>i&1, nk = k>>i&1;
        if (!nx) {//x的第i位是0
            if (!nk) {//k的第i位是0
                ans += cnt[tr[rt][1]];//所有第i位为1的路径数量
                if (!tr[rt][0]) return ans;
                rt = tr[rt][0];
            } else {
                if (!tr[rt][1]) return ans;
                rt = tr[rt][1];
            }
        } else {
            if (!nk) {
                ans += cnt[tr[rt][0]];
                if (!tr[rt][1]) return ans;
                rt = tr[rt][1];
            } else {
                if (!tr[rt][0]) return ans;
                rt = tr[rt][0];
            }
        }
    }
    return ans + cnt[rt];
}

int n, k, a[M];
int main() {
    fast;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i]; a[i] = a[i]^a[i-1];//前i个元素的XOR
    }
    ll ans = 0; insert(0);
    for (int i = 1; i <= n; ++i) {
        ans += 1ll*get(a[i], k);
        insert(a[i]);
    }
    cout << ans << '\n';
    return 0;
}