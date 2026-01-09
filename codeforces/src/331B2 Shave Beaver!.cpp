//
// Created by Psy.C on 2026/1/9.
//
///query(x, x) == 1 表示：值 x 在数组中的位置在值 x+1 之前（逆序关系）
///query(x, x) == 0 表示：值 x 在数组中的位置在值 x+1 之后（正确顺序）
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1000010
#define low_bit(x) (x&(-x))
using namespace std;

int n, c[N];
void add(int x, const int v) {//在位置 x 添加值 v
    while (x <= n) {
        c[x] += v;
        x += low_bit(x);
    }
}

int query(int x) {//从1到 x 的前缀和
    int res = 0;
    while (x) {
        res += c[x];
        x -= low_bit(x);
    }
    return res;
}
//范围 [x, y] 内的和
int query(const int x, const int y) { return query(y) - query(x-1); }

int id[N];//值 x 在数组中的位置
///
/// 当值 x 和 y 的相对顺序改变时更新树状数组
/// 如果位置 x 目前被"标记"且 x 排在 y 之前，则移除标记
/// 如果位置 x 没被"标记"但 x 应该排在 y 之后，则添加标记
void modify(const int x, const int y) {
    if (x < 1 || y > n) return;
    if (query(x, x)) { if (id[x] < id[y]) add(x, -1); } else {
        if (id[x] > id[y]) add(x, 1);
    }
}

int main() {
    fast;
    int a[N], m; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i], id[a[i]] = i;
    for (int i = 1; i <= n; ++i) if (id[i] > id[i+1]) add(i, 1);//如果值 i 在值 i+1 之后（按位置），则在位置 i 添加1
    cin >> m;
    for (int i = 1, op, x, y; i <= m; ++i) {
        cin >> op >> x >> y;
        if (op == 1) {// [x, y] 内有多少个值与其下一个连续值处于错误顺序
            int ans = query(x, y);
            if (!query(y, y)) ans++;//如果最后一个值 y 没有被"标记"，则答案加1
            cout << ans << '\n';
        }
        if (op == 2) {
            ///交换数组中两个值的位置
            ///更新树状数组以反映新的顺序关系
            ///对于每个受影响的值，检查其与相邻值的关系
            swap(id[a[x]], id[a[y]]); swap(a[x], a[y]);
            modify(a[x]-1, a[x]); modify(a[x], a[x]+1);
            modify(a[y]-1, a[y]); modify(a[y], a[y]+1);
        }
    }
    return 0;
}