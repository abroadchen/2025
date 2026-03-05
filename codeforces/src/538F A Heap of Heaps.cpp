//
// Created by Psy.C on 2026/3/5.
//
/**
找到相同值的区间：while (a[i].x == a[p].x && p <= n) p++;

找到所有具有相同x值的元素范围 [i, p)
处理相同值的元素：
对于每个相同值的元素，其原始位置为id
枚举k值，计算区间 [k*(id-1)+1, min(n, k*id+1)] 中已处理元素的个数
将当前处理过的元素位置加入树状数组
跳过已处理元素：i = p-1;
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+10;
struct node {
    int x, id;
    bool operator < (const node &o) const {
        return x < o.x;
    }
} a[N];

int low_bit(const int x) { return x & -x; }

int tr[N];
int query(const int x) {
    int res = 0;
    for (int i = x; i; i -= low_bit(i)) res += tr[i];
    return res;
}

int n;
void update(const int pos, const int val) {
    for (int i = pos; i <= n; i += low_bit(i)) tr[i] += val;
}

int ans[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].x, a[i].id = i;
    }
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; ++i) {
        int p = i;
        while (a[i].x == a[p].x && p <= n) p++;
        for (int j = i; j < p; ++j) {
            const int id = a[j].id;
            for (int k = 1; k <= n-1 && k*(id-1)+2 <= n; ++k)
                ans[k] += query(min(n, k*id+1)) - query(k*(id-1)+1);
        }
        for (int j = i; j < p; ++j) update(a[j].id, 1);
        i = p-1;
    }
    for (int i = 1; i < n; ++i) cout << ans[i] << " \n"[i==n-1];
    return 0;
}