//
// Created by Psy.C on 2026/3/10.
//
/**
n：数组长度
cnt：块大小
b[N]：每个位置所属的块
tot：块的数量
v[N]：每个块内的有序元素
a[N]：原数组

n：数组长度
cnt：块大小
b[N]：每个位置所属的块
tot：块的数量
v[N]：每个块内的有序元素
a[N]：原数组

查询值y的左右边界
找到最左边的y的位置l
找到最右边的y的位置r
返回r-l（如果y不存在返回-1）

构建：O(n√n)
更新：O(√n)
查询：O(√n log n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 5e5+5;

int n, cnt, b[N], tot;
vector<ll> v[N];
ll a[N];
void build() {
    cnt = sqrt(n);
    tot = n/cnt;
    if (n%cnt) tot++;
    for (int i = 1; i <= n; ++i) {
        b[i] = (i-1)/cnt + 1;
        v[b[i]].push_back(a[i]);
    }
    for (int i = 1; i <= tot; ++i)
        ranges::sort(v[i]);
}

void reset(int x) {
    v[x].clear();
    for (int i = (x-1)*cnt + 1; i <= x*cnt; ++i)
        v[x].push_back(a[i]);
    ranges::sort(v[x]);
}

ll tag[N];
void add(int l, int r, int x) {
    int b1 = b[l], b2 = b[r];
    if (b1 == b2) {
        for (int i = l; i <= r; ++i) a[i] += x;
        reset(b1);
    } else {
        for (int i = l; i <= b1*cnt; ++i) a[i] += x;
        reset(b1);
        for (int i = b1+1; i < b2; ++i) tag[i] += x;
        for (int i = (b2-1)*cnt+1; i <= r; ++i)
            a[i] += x;
        reset(b2);
    }
}

int query(int y) {
    int l = 0, r = 0;
    for (int i = 1; i <= tot; ++i) {
        int pos = lower_bound(v[i].begin(), v[i].end(), y-tag[i]) - v[i].begin();
        if (y - tag[i] == v[i][pos]) {
            for (int j = (i-1)*cnt+1; j <= i*cnt; ++j)
                if (a[j] + tag[i] == y) { l = j; break; }
            break;
        }
    }
    if (l == 0) return -1;
    for (int i = tot; i >= 1; --i) {
        int pos = lower_bound(v[i].begin(), v[i].end(), y-tag[i]) - v[i].begin();
        if (y - tag[i] == v[i][pos]) {
            for (int j = i*cnt; j > (i-1)*cnt; --j)
                if (a[j] + tag[i] == y) { r = j; break; }
            break;
        }
    }
    return r - l;
}

int q;
int main() {
    fast;
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) cin >> a[i]; build();
    for (int i = 1, op, l, r, y; i <= q; ++i) {
        cin >> op;
        if (op == 1) {
            cin >> l >> r >> y;
            add(l, r, y);
        } else {
            cin >> y;
            cout << query(y) << '\n';
        }
    }
    return 0;
}