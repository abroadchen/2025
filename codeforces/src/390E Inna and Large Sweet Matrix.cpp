//
// Created by Psy.C on 2026/1/28.
//
/**
* v 为操作类型标识符
(x1,y1) 到 (x2,y2) 为操作的矩形区域
 *
*当 v 非零时执行查询操作
计算矩形区域 (x1,y1) 到 (x2,y2) 的和
使用前缀和差分公式：S(x2,y2) - S(x1-1,y2) - S(x2,y1-1) + S(x1-1,y1-1)
当 v 为0时执行更新操作
将矩形区域 (x1,y1) 到 (x2,y2) 内的所有元素增加 val
分别在两个维度上进行区间更新
乘以 (y2-y1+1) 或 (x2-x1+1) 是为了处理二维更新的面积

 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 1000005<<2
using namespace std;

ll get(const ll *b, int x) {//从位置 x 向前累加，直到 x 变为 0
    ll ans = 0;
    while (x > 0) {
        ans += b[x];
        x -= x & -x;//树状数组的向上遍历
    }
    return ans;
}

ll b1[2][N], b2[2][N];
ll Get(const int id, const int r) {// id 维度上到位置 r 的前缀和 原始值 × 位置 + 偏移量
    return get(b1[id], r) * r + get(b2[id], r);
}

void insert(ll *b, const int m, int x, const ll val) {//位置 x 增加 val
    while (x <= m) {//x 一直向上更新到不超过 m
        b[x] += val;
        x += x & -x;
    }
}

int x[2];//存储两个维度的最大值
void Insert(const int id, const int l, const int r, const ll val) {//对 id 维度的区间 [l, r] 进行值 val 的更新
    insert(b1[id], x[id], l, val);//在 l 位置加 val，在 r+1 位置减 val（实现区间加法）
    insert(b1[id], x[id], r + 1, -val);
    insert(b2[id], x[id], l, -val * (l-1));//维护相关的偏移量
    insert(b2[id], x[id], r + 1, val * r);
}


int main() {
    fast;
    int q, v, x1, y1, x2, y2; cin >> x[0] >> x[1] >> q;//第一个维度大小
    while (q--) {
        cin >> v >> x1 >> y1 >> x2 >> y2;
        if (v) {
            const ll ans = Get(1, y2) - Get(1, y1-1) -
                (Get(0, x[0]) - Get(0, x2) + Get(0, x1-1));
            cout << ans << '\n';
        } else {
            ll val; cin >> val;
            Insert(0, x1, x2, val * (y2 - y1 + 1));// y 方向的宽度
            Insert(1, y1, y2, val * (x2 - x1 + 1));
        }
    }
    return 0;
}