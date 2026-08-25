//
// Created by Psy.C on 2026/5/26.
//
/**
n为数组长度，m为数值范围上限
od, ev: 分别统计奇数和偶数的数量
rod, rev: 分别表示还需要的奇数和偶数的数量
a[N]: 输入数组
vis[N]: 标记数组，记录哪些数字已被使用
ok[N]: 标记数组，记录某个位置的数字是否已确定
sod, sev, ans: set容器，分别存储已有的奇数、偶数和最终答案
vo, vj: vector容器，分别存储可用的偶数和奇数

计算在[1,m]范围内最多可选的奇偶数数量：
如果m是奇数，奇数数量比偶数数量多1
如果m是偶数，奇偶数数量相等
读入数组并分类统计：
标记已使用的数字
对于奇数：增加奇数计数，如果在范围内且未被记录则减少所需奇数数量
对于偶数：增加偶数计数，如果在范围内且未被记录则减少所需偶数数量
计算还需要多少个不同的奇数和偶数
检查是否可行：如果剩余需求超过可用数量则输出-1
输出需要修改的最少元素数量
收集所有未被使用的偶数到vo向量
收集所有未被使用的奇数到vj向量

第一次遍历：尝试保留已有的不同数字，直到奇偶各达到n/2个
cod, cev: 已选择的奇偶数数量
ok[i]: 标记位置i的数字已确定
第二次遍历处理所有未确定的数字，根据需要替换为合适的奇偶数
输出最终修改后的数组


情况1：当前是重复的奇数
ans.contains(a[i])为真，表示该奇数值已经存在于结果集合中
如果还能添加奇数 (cod < n/2)：用一个新的奇数替换 a[i] = vj.back()
否则如果还能添加偶数 (cev < n/2)：用一个新的偶数替换 a[i] = vo.back()
情况2：当前是不重复的奇数
ans.contains(a[i])为假，表示该奇数值未被使用过
如果还能添加奇数 (cod < n/2)：直接使用这个奇数，加入ans集合
否则需要转换为偶数：用一个新的偶数替换 a[i] = vo.back()


 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 6e5+7;
ll n, m, od, ev, rod, rev, a[N];
bool vis[N], ok[N];
set<ll> sod, sev, ans;
vector<int> vo, vj;
int main() {
    fast;
    cin >> n >> m;
    if (m&1) rev = m/2, rod = rev + 1; else rev = rod = m/2;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        if (a[i] < N) vis[a[i]] = 1;
        if (a[i]&1) {
            od++;
            if (a[i] <= m && !sod.contains(a[i])) rod--;
            sod.insert(a[i]);
        } else {
            ev++;
            if (a[i] <= m && !sev.contains(a[i])) rev--;
            sev.insert(a[i]);
        }
    }
    ll bod = n/2-sod.size(), bev = n/2-sev.size();
    if (rod < bod || rev < bev) return 0, puts("-1");
    ll tmp = max(bod, 0ll) + max(bev, 0ll);
    cout << tmp << '\n';
    for (int i = 2; i <= min(m, 1ll*N-1); i += 2) {
        if (vis[i]) continue;
        vo.push_back(i);
    }
    for (int i = 1; i <= min(m, 1ll*N-1); i += 2) {
        if (vis[i]) continue;
        vj.push_back(i);
    }
    ll cod = 0, cev = 0;
    for (int i = 1; i <= n; ++i) {
        if (ans.contains(a[i])) continue;
        ans.insert(a[i]);
        if (a[i]&1 && cod < n/2) cod++, ok[i] = 1;
        else if ((a[i]&1) == 0 && cev < n/2) cev++, ok[i] = 1;
    }
    for (int i = 1; i <= n; ++i) {
        if (ok[i]) continue;//已在第一次遍历中处理，跳过
        if (a[i]&1) {
            if (ans.contains(a[i])) {//这个奇数值已经在ans集合中（重复了）
                if (cod < n/2) a[i] = vj.back(), vj.pop_back(), cod++;
                else if (cev < n/2) a[i] = vo.back(), vo.pop_back(), cev++;
            } else {
                if (cod < n/2) ans.insert(a[i]), cod++;
                else a[i] = vo.back(), vo.pop_back(), cev++;
            }
        } else {
            if (ans.contains(a[i])) {
                if (cod < n/2) a[i] = vj.back(), vj.pop_back(), cod++;
                else if (cev < n/2) a[i] = vo.back(), vo.pop_back(), cev++;
            } else {
                if (cev < n/2) ans.insert(a[i]), cev++;
                else a[i] = vj.back(), vj.pop_back(), cod++;
            }
        }
    }
    for (int i = 1; i <= n; ++i) cout << a[i] << ' ';
    return 0;
}