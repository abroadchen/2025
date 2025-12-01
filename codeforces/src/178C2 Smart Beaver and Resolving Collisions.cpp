//
// Created by Psy.C on 2025/11/30.
//
/*
*N = 2e5+5：数组大小常量
op[2]：操作符数组（'+'或'-'）
h：哈希表大小
m：探测步长
n：操作数量
tot = gcd(h,m)：h和m的最大公约数
len = h/tot：每个循环的长度
pos[N]：存储每个位置在循环中的序号
x, y：临时变量
ans：总探测次数
 *
*tr：树状数组存储
n：数组大小
init()：初始化数组大小
upd(p,t)：在位置p增加t（单点更新）
qry(p)：查询[1,p]区间和
sum(l,r)：查询[l,r]区间和
 *
 *存储ID到(块编号, 位置)的映射
*将0到h-1的位置划分为tot个循环块
对于每个循环块：
计算每个位置在循环中的序号（1到len）
初始化对应树状数组，大小为2*len
 *
*读入要插入的值y
计算所属块编号bl = y % tot
获取在循环中的位置p = pos[y]
*在区间[p, p+len-1]中二分查找
如果区间[p,mid]中实际元素数小于理论元素数(mid-p+1)，说明有空位
否则说明该区间已满
 *累加探测次数
*如果位置超过len，使用循环性质更新
否则正常更新
记录该元素的位置信息
*获取要删除元素的位置信息
在树状数组中将对应位置减1
 *
*时间复杂度：
单次操作：O(log²h)
总体：O(n log²h)
空间复杂度：
O(h)
 */
#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 2e5+5;
char op[2];
int h, m, n, tot, len, pos[N],
x, y, ans;

struct node {
    vector<int> tr; int n{};
    void init(const int t) { n = t; tr.resize(t + 1); }
    void upd(int p, const int t) {
        while (p <= n) tr[p] += t, p += (p & -p);
    }
    int qry(int p) const {//不修改类的任何成员变量 支持在const对象上调用
        int res = 0;
        while (p) res += tr[p], p ^= (p & -p);
        return res;
    }
    int sum(const int l, const int r) const { return qry(r) - qry(l - 1); }
} t[N];

map<int,pair<int,int>> mp;
int main() {
    fast;
    cin >> h >> m >> n; tot = __gcd(h, m); len = h / tot;
    for (int i = 0; i < tot; ++i) {
        for (int j = 1, p = i; j <= len; ++j, p = (p + m) % h)
            pos[p] = j;
        t[i].init(2 * len);
    }
    while (n--) {
        cin >> op >> x;
        if (op[0] == '+') {
            cin >> y;
            const int bl = y % tot, p = pos[y];
            int l = p, r = p + len - 1;
            while (l < r) {
                const int mid = (l + r) >> 1;
                if (t[bl].sum(p, mid) < mid - p + 1) r = mid;
                else l = mid + 1;
            }
            ans += r - p;//累加探测次数
            if (r > len) t[bl].upd(r, 1), t[bl].upd(r - len, 1),
                mp[x] = {bl, r - len};
            else t[bl].upd(r, 1), t[bl].upd(r + len, 1),
                mp[x] = {bl, r};
        } else {
            y = mp[x].second;
            x = mp[x].first;
            t[x].upd(y, -1);
            t[x].upd(y + len, -1);
        }
    }
    cout << ans;
    return 0;
}