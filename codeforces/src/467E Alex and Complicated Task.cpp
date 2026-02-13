//
// Created by Psy.C on 2026/2/13.
//
/**
res：结果向量，存储输出序列
vals：值栈，用于处理序列
occ：多重集合，统计元素出现次数
mp：映射，存储元素对应关系

如果v在映射中存在，调用init函数并跳过本次循环
如果v在多重集合中存在（第二次或更多次出现）
cnt：如果v出现次数≥2则为1，否则为0
循环直到栈顶元素是v且cnt为0
弹出栈顶元素，同时建立映射关系
将v插入多重集合
将v压入栈
 */
#include <iostream>
#include <vector>
#include <map>
#include <set>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

vector<int> res, vals;
multiset<int> occ;
map<int, int> mp;

void init(const int a, const int b) {
    res.push_back(a); res.push_back(b);
    res.push_back(a); res.push_back(b);
    occ.clear(); mp.clear(); vals.clear();
}

int n;

int main() {
    fast;
    cin >> n;
    for (int i = 0, v; i < n; ++i) {
        cin >> v;
        if (mp.contains(v)) { init(mp[v], v); continue; }
        if (occ.contains(v)) {
            int cnt = occ.count(v) >= 2 ? 1 : 0;
            while (cnt || vals.back() != v) {
                if (vals.back() == v) cnt--;
                mp[vals.back()] = v;
                vals.pop_back();
            }
        }
        occ.insert(v);
        vals.push_back(v);
    }
    cout << res.size() << '\n';
    for (const int re : res) cout << re << ' ';
    cout << '\n';
    return 0;
}