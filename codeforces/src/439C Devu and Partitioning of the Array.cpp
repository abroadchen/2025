//
// Created by Psy.C on 2026/2/7.
//
/**
k: 要创建的组数
p: 必须包含至少一个同奇偶性配对的组数
n1: 奇数的个数
n2: 偶数的个数
ans[N]: 每个组的结果数组
v1: 包含奇数的向量
v2: 包含偶数的向量

如果我们需要k-p个包含至少一个奇数的组，但奇数少于k-p个，这是不可能的
将一个奇数分配给前k-p个组中的每一个
这些组不需要配对，所以一个奇数就能满足它们
在给k-p个组分配一个奇数后，检查剩余奇数是否为偶数
如果奇数数量仍为奇数，我们无法从它们形成配对
n1-t1: 初始分配后剩余的奇数
(n1-t1)>>1: 我们可以形成的奇数对数量
n2: 偶数数量（每个都可以与另一个偶数形成配对）
我们需要p个具有同奇偶性配对的组
如果需要的配对 > 可用配对，返回false
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100005
using namespace std;

int k, p, n1, n2;
vector<int> ans[N], v1, v2;
bool ok() {
    if (k - p > n1) return false;
    int t1 = 0, t2 = 0;
    for (int i = 0; i < k - p; ++i) ans[i].push_back(v1[t1++]);
    if ((n1-t1)&1) return false;
    if (p > n2 + ((n1-t1)>>1)) return false;
    if (p) {
        int i = k - p;//从需要配对的组开始
        while (t1 < n1) {//分发剩余的奇数配对
            ans[i].push_back(v1[t1++]);//添加第一个奇数
            ans[i].push_back(v1[t1++]);//添加第二个奇数
            i++;
            if (i == k) i = k - p;//循环回到配对需要的组
        }
        //偶数：一个一个处理，累积后自动形成配对
        while (t2 < n2) {
            ans[i].push_back(v2[t2++]);
            i++;
            if (i == k) i = k - p;
        }
    } else {
        int i = 0;
        while (t1 < n1) {
            ans[i].push_back(v1[t1++]);
            ans[i].push_back(v1[t1++]);
            i++;
            i %= k;//循环到开头
        }
        while (t2 < n2) {
            ans[i].push_back(v2[t2++]);
            i++;
            i %= k;
        }
    }
    return true;
}


int main() {
    fast;
    int n; cin >> n >> k >> p; n1 = n2 = 0;
    for (int i = 1, a[N]; i <= n; ++i) {
        cin >> a[i];
        if (a[i]&1) n1++, v1.push_back(a[i]);//计数并存储奇数
        else n2++, v2.push_back(a[i]);
    }
    if (ok()) {
        cout << "YES\n";
        for (int i = 0; i < k; ++i) {
            cout << ans[i].size();
            for (const int j : ans[i]) cout << ' ' << j;
            cout << '\n';
        }
    } else cout << "NO\n";
    return 0;
}