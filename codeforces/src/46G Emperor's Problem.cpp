//
// Created by Psy.C on 2025/10/8.
//
/*
*seq：存储平方距离（长度的平方）
mp：将平方距离映射到对应的坐标对

 *
*象限 0：x ≥ 0, y ≤ 0（第四象限）
象限 1：x < 0, y ≤ 0（第三象限）
象限 2：x < 0, y > 0（第二象限）
象限 3：x ≥ 0, y > 0（第一象限）

 *
*gt：如果向量 a 的斜率比向量 b 更陡峭则返回true
le：如果向量 a 的斜率比向量 b 更平缓则返回true
它们通过比较交叉积来避免除法运算

 *
*首先按象限排序（0, 1, 2, 3）
在每个象限内，按斜率排序：
对于象限 0 和 2：更陡峭的斜率优先
对于象限 1 和 3：更平缓的斜率优先
 *
 *根据平方和是奇数还是偶数将向量分为奇数长度²组(o)和偶数长度²组(e)。
 *
 *确保奇数长度向量的数量是偶数（多边形闭合所需）。如果不是，则添加一个向量然后删除它以保持奇偶性。
 *合并所有向量并按长度降序排列。
 *
*调整每个向量的方向以保持累积和的平衡：

如果y分量占主导则交换坐标
在适当时翻转符号以保持累积和为负
这有助于确保多边形能够正确闭合
 *使用自定义比较器排序向量并计算累积位置（多边形顶点）。
 *
 *预处理所有可能的向量长度（两个平方数之和，最大到200²）及其对应的坐标对，去除重复项。然后读取输入n并调用求解器
 *
 */
#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

typedef pair<int, int> pii;
vector<int> seq;
map<int, pii> mp;

int getT(const pii& o) {
    if (o.first >= 0) return o.second <= 0 ? 0 : 3;
    return o.second <= 0 ? 1 : 2;
}

bool gt(const pii& a, const pii& b) {
    return abs(a.first) * abs(b.second) > abs(a.second) * abs(b.first);
}

bool le(const pii& a, const pii& b) {
    return abs(a.first) * abs(b.second) < abs(a.second) * abs(b.first);
}

bool cmp(const pii& a, const  pii& b) {
    int x = getT(a), y = getT(b);
    if (x != y) return x < y;
    if (x == 0 || x == 2) return gt(a, b);
    return le(a, b);
}

void solve(int n) {
    vector<pii> o, e;
    for (int i = 0; i < n; ++i) {
        if (seq[i] % 2) o.push_back(mp[seq[i]]);
        else e.push_back(mp[seq[i]]);
    }
    if (o.size() % 2) {
        if (seq[n] % 2) o.push_back(mp[seq[n]]);
        else e.push_back(mp[seq[n]]);
        if (o.size() % 2) o.pop_back();
        else e.pop_back();
    }
    vector<pii> s;
    for (int i = 0; i < o.size(); ++i) s.push_back(o[i]);
    for (int i = 0; i < e.size(); ++i) s.push_back(e[i]);
    sort(s.rbegin(), s.rend());

    vector<pii> res;
    int a(0), b(0);
    for (int i = 0; i < (int)s.size(); ++i) {
        if (abs(b) > abs(a)) swap(s[i].first, s[i].second);
        if (a >= 0) s[i].first = -s[i].first;
        if (b >= 0) s[i].second = -s[i].second;
        a += s[i].first; b += s[i].second;
        res.push_back(s[i]);
    }
    sort(res.begin(), res.end(), cmp);

    vector<pii> ans; pii cur = pii(0, 0);
    for (int i = 0; i < (int)res.size(); ++i) {
        cur.first += res[i].first; cur.second += res[i].second;
        ans.push_back(cur);
    }
    printf("YES\n");
    for (int i = int(ans.size()) - 1; i >= 0; --i) printf("%d %d\n", ans[i].first, ans[i].second);
}

int main() {


    for (int i = 1; i <= 200; ++i)
        for (int j = 0; j <= i; ++j) {
            seq.push_back(i * i + j * j);
            mp[i * i + j * j] = pii(i, j);
        }
    sort(seq.begin(), seq.end());
    seq.erase(unique(seq.begin(), seq.end()), seq.end());

    int n; scanf("%d", &n);
    solve(n);
    return 0;
}