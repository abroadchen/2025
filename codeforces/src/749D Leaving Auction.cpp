//
// Created by Psy.C on 2026/8/27.
//
/**
- vector<int> v[N] ： 编号→值列表 ， v[x] 存储编号为 x 的所有值（可能多个值共享同一编号）。
- int mx[N] ： 编号的最大值映射 ， mx[x] 存储编号 x 对应的 最大那个值 （ v[x] 中的最大值）。初始值为0（编号不存在）。
- int l[N] ： 临时删除列表 ，每次操作中存储要删除的编号，操作结束后恢复。
- map<int, int> mp ： 值→编号 的有序映射， mp 按值 降序 排列（ map 默认升序，配合 --mp.end() 取最大值），用于快速查询当前最大值。
- 键（key）：值 y 。
- 值（value）：编号 x 。
- 特殊： mp[0] = 0 作为哨兵，保证 mp 非空

读入初始元素个数 n
读入 n 个元素，每个元素是一对 (编号x, 值y) ：
- mx[x] = y ：将编号 x 的 最大值 设为 y （如果同一编号多次出现，后面的值会覆盖前面的，但 v[x] 会保留所有值）。
- v[x].push_back(y) ：将值 y 加入编号 x 的值列表
遍历所有可能的编号 i ，若 mx[i] 非零（编号存在），则将其 最大值 和编号加入 mp ：
- mp[mx[i]] = i ：键为编号 i 的最大值，值为编号 i 。
- 此时 mp 按值升序排列，最大值在最后
- cin >> n ：读入操作次数（注意此处复用了 n 变量，覆盖了之前的元素个数）。
- mp[0] = 0 ：插入哨兵值，保证 mp 始终非空，后续 --mp.end() 不会越界
循环处理 n 次操作，每次操作先读入 要删除的编号数量 k
依次读入 k 个要临时删除的编号，从 mp 中移除：
- cin >> l[j] ：读入要删除的编号，存入临时数组 l （操作结束后会恢复）。
- if (mx[l[j]]) ：仅当编号存在时才删除。
- mp.erase(mx[l[j]]) ：根据编号的 最大值 作为键，从 mp 中删除该编号。
- 此时 mp 中存储的是 删除后剩余元素 的值→编号映射
- auto p = mp.end(); --p ： mp 是升序排列的， end() 指向末尾后一位， --p 指向 最大键值 的元素（即值最大的剩余元素）。
- if (p == mp.begin()) ：若 mp 只剩哨兵（ mp[0]=0 ），说明没有剩余元素，输出 0 0

- int id = p->second ：取出最大值对应的 编号 id 。
- --p ：向前移动迭代器，得到 次大值 的键（即当前 mp 中第二大的值，记为 second_max ）。
  - 这里的 p->first 就是次大值。
- ranges::lower_bound(v[id], p->first) ：
  - ranges::lower_bound 是 C++20特性 ，等价于 lower_bound(v[id].begin(), v[id].end(), target) 。
  - 在**编号 id 的所有值列表 v[id] 中，找到 第一个 ≥ 次大值 second_max **的值。
  - 这个值就是编号 id 在所有剩余元素中的"排序位置"。
- *迭代器 ：解引用得到实际的值。
- cout << id << ' ' << 值 << '\n' ：输出编号和该值。
核心逻辑 ：找到编号 id 在所有值中的 相对排名位置 ，用 lower_bound 定位它在排序后的值列表中的插入位置
- 遍历临时删除列表 l[1..k] ，将之前删除的编号 重新加回 mp 。
- mp[mx[l[j]]] = l[j] ：用最大值作为键，重新建立值→编号的映射。
- 循环结束 ，准备处理下一次操作
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+5;
vector<int> v[N];
int mx[N], l[N];
map<int, int> mp;
int main() {
    fast;
    int n; cin >> n;
    for (int i = 1, x, y; i <= n; ++i) {
        cin >> x >> y;
        mx[x] = y; v[x].push_back(y);
    }
    for (int i = 1; i <= n; ++i)
        if (mx[i]) mp[mx[i]] = i;
    cin >> n;
    mp[0] = 0;
    for (int i = 1, k; i <= n; ++i) {
        cin >> k;
        for (int j = 1; j <= k; ++j) {
            cin >> l[j];
            if (mx[l[j]]) mp.erase(mx[l[j]]);
        }
        auto p = mp.end(); --p;
        if (p == mp.begin()) cout << "0 0" << '\n';
        else {
            int id = p->second; --p;
            cout << id << ' ' << *ranges::lower_bound(v[id], p->first) << '\n';
        }
        for (int j = 1; j <= k; ++j)
            if (mx[l[j]]) mp[mx[l[j]]] = l[j];
    }
    return 0;
}