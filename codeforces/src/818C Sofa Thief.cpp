//
// Created by Psy.C on 2026/9/22.
//
/**
每个沙发读入 4 个数，代表两个端点的横纵坐标：端点1 (a, b)、端点2 (c, d)。两个端点要么横坐标相同（垂直段），要么纵坐标相同（水平段）
swap 把每个端点的两个坐标对调，目的是让后面统一按"第一个坐标=横坐标(列)，第二个坐标=纵坐标(行)"来抽取，实际上是分别收集 x 方向、y 方向的 min/max。设端点横坐标为 xa,xb，纵坐标为 ya,yb：

p[1].push_back( min(b, d) ) = 左边界（x 最小）
p[2].push_back( max(b, d) ) = 右边界（x 最大）
p[3].push_back( min(a, c) ) = 上边界（y 最小）
p[4].push_back( max(a, c) ) = 下边界（y 最大）
随后对这四个数组分别排序
op = 1 或 3：返回数组里严格小于 x 的元素个数（最后一个 < x 的下标 q，个数为 q+1）。
op = 2 或 4：返回数组里严格大于 x 的元素个数（第一个 > x 的下标 q，其后 size - q 个）。
两个都是标准二分，O(log d)
左边数量 f：取本沙发右边界 max(b,d)，查 p[1](所有沙发的左边界) 中严格小于它的个数，再去掉自身（若 b!=d 即水平放，自身左边界 < 右边界会被计入）。得到的正是"完全在本沙发左边的沙发数"。
右边数量 g：取本沙发左边界 min(b,d)，查 p[2](所有沙发的右边界) 中严格大于它的个数，同样扣除自身。
上边数量 h：取本沙发下边界 max(a,c)，查 p[3](所有沙发的上边界) 中严格小于它的个数，若垂直放置（a!=c）则自身计入要减 1。
下边数量 l：取本沙发上边界 min(a,c)，查 p[4](所有沙发的下边界) 中严格大于它的个数。
只有当四个方向的统计全部等于给定的 f、g、h、l 时，该沙发才是答案；找到第一个满足的就输出编号并结束。若整个循环结束都没找到，输出 -1（题目保证答案唯一）。


 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

constexpr int N = 1e6+2;
struct sofa { int a, b, c, d; } S[N];

vector<int> p[5];
int find(int op, int x) {
    if (op == 1 || op == 3) {
        int l = 0, r = p[op].size()-1, q = -1;
        while (l <= r) {
            int mid = (l+r)>>1;
            if (p[op][mid] < x) l = mid+1, q = mid;
            else r = mid-1;
        }
        return q + 1;
    }
    int l = 0, r = p[op].size()-1, q = p[op].size();
    while (l <= r) {
        int mid = (l+r)>>1;
        if (p[op][mid] > x) r = mid-1, q = mid;
        else l = mid+1;
    }
    return p[op].size() - q;
}

int d, n, m, f, g, h, l;
signed main() {
    fast;
    int t = 1;
    while (t--) {
        cin >> d >> n >> m;
        for (int i = 1; i <= d; ++i) {
            cin >> S[i].a >> S[i].b >> S[i].c >> S[i].d;
            swap(S[i].a, S[i].b);
            swap(S[i].c, S[i].d);
            p[1].push_back(min(S[i].b, S[i].d));
            p[2].push_back(max(S[i].b, S[i].d));
            p[3].push_back(min(S[i].a, S[i].c));
            p[4].push_back(max(S[i].a, S[i].c));
        }
        ranges::sort(p[1]); ranges::sort(p[2]);
        ranges::sort(p[3]); ranges::sort(p[4]);
        cin >> f >> g >> h >> l;
        bool ok = false;
        for (int i = 1; i <= d; ++i) {
            int a = S[i].a, b = S[i].b, c = S[i].c, d = S[i].d, x, pos;
            x = max(b, d); pos = find(1, x);
            if (b != d) --pos;
            if (pos != f) continue;
            x = min(b, d); pos = find(2, x);
            if (b != d) --pos;
            if (pos != g) continue;
            x = max(a, c); pos = find(3, x);
            if (a != c) --pos;
            if (pos != h) continue;
            x = min(a, c); pos = find(4, x);
            if (a != c) --pos;
            if (pos != l) continue;
            ok = true;
            cout << i << '\n';
            break;
        }
        if (!ok) cout << "-1\n";
        p[1].clear(); p[2].clear(); p[3].clear(); p[4].clear();
    }
    return 0;
}