//
// Created by Psy.C on 2026/2/20.
//
/**
n: 线段树大小
tag: 懒标记数组
sum: 区间异或和数组

向上更新节点
如果有标记，区间异或和为val[r]^val[l]
否则合并左右子树结果
叶子节点异或和为0

n: 网格大小
m: 矩形数量
k: 游戏参数
__lg(k)：计算floor(log2(k))，即k的最高位

e: 存储扫描线事件
将矩形转换为两条垂直线段（左边界+1，右边界-1）
a--, b--: 转换为0基索引
emplace_back(a, b, d, 1): 添加左边界事件
emplace_back(c, b, d, -1): 添加右边界事件
收集所有纵坐标用于离散化

对事件按x坐标排序
对纵坐标排序并去重（离散化）

创建线段树
sum: 总异或和
lst: 上一个x坐标
遍历扫描线事件：
找到y1,y2在离散化数组中的位置
sum ^= t.get() & (x^lst): 更新总异或和
t.update(l, r, o): 更新线段树
((1<<(u+1))-1)：构造掩码，保留前u+1位
根据异或和的特定位判断游戏结果

x - 扫描线的横坐标
y1, y2 - 纵坐标的范围
o = +1：矩形左边界，表示开始覆盖
o = -1：矩形右边界，表示结束覆盖

 */
#include <bits/stdc++.h>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

vector<int> val;///存储需要离散化的纵坐标值
struct sgt {
    int n;
    vector<int> tag, sum;
    explicit sgt(const int n) : n(n), tag(n<<2), sum(n<<2) {}
    void push_up(const int p, const int l, const int r) {
        if (tag[p]) sum[p] = val[r]^val[l];
        else if (r - l > 1) sum[p] = sum[p<<1]^sum[p<<1|1];
        else sum[p] = 0;
    }
    ///给节点添加标记并更新
    void add(const int p, const int l, const int r, const int v) {
        tag[p] += v; push_up(p, l, r);
    }
    void update(const int p, const int l, const int r, const int x, const int y, const int v) {
        if (l >= y || r <= x) return;
        if (l >= x && r <= y) { add(p, l, r, v); return; }
        const int m = (l + r)>>1;
        update(p<<1, l, m, x, y, v);
        update(p<<1|1, m, r, x, y, v);
        push_up(p, l, r);
    }
    void update(const int l, const int r, const int v) { update(1, 0, n, l, r, v); }
    ///获取整棵树的异或和
    [[nodiscard]] int get() const {
        if (n == 0) return 0;
        return sum[1];
    }
};

int n, m, k;
int main() {
    fast;
    cin >> n >> m >> k;
    const int u = __lg(k);
    vector<tuple<int,int,int,int>> e;
    for (int i = 0, a, b, c, d; i < m; ++i) {
        cin >> a >> b >> c >> d; a--; b--;
        e.emplace_back(a, b, d, 1);
        e.emplace_back(c, b, d, -1);
        val.push_back(b); val.push_back(d);
    }
    ranges::sort(e); ranges::sort(val);
    val.erase(ranges::unique(val).begin(), val.end());
    sgt t(val.size()-1);
    int sum = 0, lst = 0;
    for (auto [x, y1, y2, o] : e) {
        const int l = lower_bound(val.begin(), val.end(), y1) - val.begin(),
        r = lower_bound(val.begin(), val.end(), y2) - val.begin();
        sum ^= t.get() & (x^lst); lst = x;
        t.update(l, r, o);
    }
    if (sum & ((1<<(u+1))-1)) cout << "Hamed\n";
    else cout << "Malek\n";
    return 0;
}