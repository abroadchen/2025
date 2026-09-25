//
// Created by Psy.C on 2026/9/24.
//
/**
a[i] 存每个元素的值 num 和它原始下标 id。
排序规则 cmp：先按值从小到大，值相同再按原始下标从小到大。
排序后，相同值的元素会被连续排在一起，方便按"值分组"处理
b[] 是 BIT。
sum(x)：查询前缀和（1..x 中还有多少个未被删除的位置）。
update(x, c)：给位置 x 加上 c（用于删除位置，即 c = -1）
读入每个值，记录下标。
update(i, 1)：把所有位置在 BIT 中标为 1（表示未处理/存活)
排序后遍历，值变化一次就新起一组，把同组元素（它们的原始下标 id）收集到 v[sz] 中。
v[i] 是按值从小到大排列后第 i 组的原始下标集合（组内下标是升序的，因为排序时同值按下标升序)
mn：当前"指针"位置（上一个处理完的元素下标）。初始为 0（环形起点）。
对每一组 v[i]，要沿着环从 mn 走到这组的所有元素，统计途中经过的还存活的位置数，累加进 ans，然后把这组的元素标记为已删除。
环形访问的核心逻辑

一组内元素下标是升序的。需要决定从 mn 出发往哪个方向走能经过更少存活点。用 lower_bound 找组内第一个 ≥ mn 的元素位置 pos：

分支 1：pos == 0（整组都在 mn 之后，方向前进，不绕环）‍

取这组最后一个元素 pos = v[i][最后]（走到组尾）。
步数 = sum(pos) - sum(mn)：从 mn 到 pos 之间还存活的位置数。
更新 mn = pos。
把这一整组的元素全部删除（update(.., -1)），i 正常 ++ 进入下一组。
分支 2：pos != 0（组里有一部分在 mn 之前，需要先绕环到头部）‍

先绕一圈到尾：步数 = sum(n) - sum(mn)（从 mn 环到序列末尾的存活数）。
回到起点 mn = 0。
删除这组中下标 ≥ pos 的部分（即在 mn 之后能直接走到的那一段）。
关键：i--——因为这一组中下标 < pos 的那部分（在 mn 之前、还没被访问到）‍需要被再次处理，所以把 i 撤回一步，让这组"剩下的上半段"在下一轮从 mn=0 重新访问。
这样通过"绕环 + i-- 回头"的技巧，保证每组元素无论它在 mn 前还是后，都只被完整走一遍，且总步数最小。
输出所有分组处理过程中经过的存活位置总数 = 最小总步数。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 1e5+1e2;
struct node { int num, id; } a[N];
bool cmp(const node& x, const node& y) {
    if (x.num == y.num) return x.id < y.id;
    return x.num < y.num;
}

int b[N];
int sum(int x) {
    int ans = 0;
    while (x) { ans += b[x]; x -= x&(-x); }
    return ans;
}

int n;
void update(int x, int c) {
    for (; x <= n; x += x&-x) b[x] += c;
}

vector<int> v[N];
signed main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].num; a[i].id = i;
        update(i, 1);
    }
    sort(a+1, a+1+n, cmp);
    int sz = 1; v[sz].push_back(a[1].id);
    for (int i = 2; i <= n; ++i) {
        if (a[i].num != a[i-1].num) sz++;
        v[sz].push_back(a[i].id);
    }
    int ans = 0, mn = 0;
    for (int i = 1; i <= sz; ++i) {
        int pos = lower_bound(v[i].begin(), v[i].end(), mn) - v[i].begin();
        if (pos == 0) {
            pos = v[i][v[i].size()-1];
            ans += sum(pos) - sum(mn);
            mn = pos;
            for (int j = v[i].size()-1; j >= 0; --j)
                update(v[i][j], -1), v[i].pop_back();
        } else {
            ans += sum(n) - sum(mn);
            mn = 0;
            for (int j = v[i].size()-1; j >= pos; --j)
                update(v[i][j], -1), v[i].pop_back();
            i--;
        }
    }
    cout << ans << '\n';
    return 0;
}