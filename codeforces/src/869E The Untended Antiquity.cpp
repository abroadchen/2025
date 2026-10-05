//
// Created by Psy.C on 2026/10/5.
//
/**
用进制 seed=2333 把四元组 (x1,y1,x2,y2) 编码为一个 ll 值
由于 2333 较大、四个分量拆成不同权重位，碰撞概率极低，可视为每个矩形唯一
这也是为什么 op==2（删除）用 val = -val 即可精确抵消 同一矩形算出同一哈希值
add 用两重 i&-i 传播，sum 求 [1..x][1..y] 的累加和

op=3 查询：求 (x1,y1) 与 (x2,y2) 两个位置的前缀“覆盖哈希和”，相等则 Yes
op=2 删除：val = -val，再走与添加相同的差分过程，从而把该矩形的影响抵消掉
差分四角：先 y2++; x2++ 把闭区间 [x1..x2]×[y1..y2] 转成差分所需的“右上角外移一格”形式，再按 (x1,y1)+、 (x1,y2)−、 (x2,y1)−、 (x2,y2)+ 做二维差分
配合 sum 前缀查询，即可让 (x1..x2)×(y1..y2) 内每个点都 +val
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define low_bit(x) (x&(-x))
using namespace std;
constexpr int N = 2500+10, seed = 2333;

ll ha(int a, int b, int c, int d) { return static_cast<ll>(a)*seed*seed*seed+b*seed*seed+c*seed+d; }

struct BIT {
    int nx, ny; ll c[N][N];
    void add(int x, int y, ll val) {
        for (int i = x; i <= nx; i += low_bit(i))
            for (int j = y; j <= ny; j += low_bit(j))
                c[i][j] += val;
    }
    ll sum(int x, int y) {
        ll ans = 0;
        for (int i = x; i > 0; i -= low_bit(i))
            for (int j = y; j > 0; j -= low_bit(j))
                ans += c[i][j];
        return ans;
    }
} bit;

int main() {
    fast;
    memset(bit.c, 0, sizeof(bit.c));
    int q; cin >> bit.nx >> bit.ny >> q;
    int op, x1, y1, x2, y2; ll val;
    while (q--) {
        cin >> op >> x1 >> y1 >> x2 >> y2;
        val = ha(x1, y1, x2, y2);
        if (op == 3) {
            ll a = bit.sum(x1, y1), b = bit.sum(x2, y2);
            cout << (a == b ? "Yes" : "No") << '\n';
            continue;
        }
        if (op == 2) val = -val;
        y2++; x2++;//差分右边界右移一格（开区间技巧）
        bit.add(x1, y1, val); bit.add(x1, y2, -val);
        bit.add(x2, y1, -val); bit.add(x2, y2, val);
    }
    return 0;
}