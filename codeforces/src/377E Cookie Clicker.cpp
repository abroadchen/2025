//
// Created by Psy.C on 2026/1/24.
//

#include <iostream>
#include <map>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define N 200010
#define inf 10000000000000001
using namespace std;

struct node {
    __int128 st, ed, k, b;//起始点st、结束点ed、斜率k、截距b
    [[nodiscard]] __int128 f(const __int128 x) const { return k * x + b; }
} t[N];//存储多个线段

int hd = 1, tl;//线段数组的起始索引 线段数组的结束索引
pair<int, __int128> fd(const int v) {//给定价值v，返回能达到该价值的最小位置和对应值
    if (v == 0) return {0, 0};
    int ans = -1, l = hd, r = tl;//未找到有效位置 二分查找的左右边界
    __int128 pt;//存储找到的值
    while (l <= r) {
        //当前线段最大值小于v，向右查找    中点线段在结束点的函数值是否小于目标值v
        if (const int mid = (l + r) >> 1; t[mid].f(t[mid].ed) < v) l = mid + 1; else {
            //达到价值v所需位置（向上取整）(a + b - 1) / b是向上取整的技巧
            int pos = static_cast<int>((v - t[mid].b + t[mid].k - 1) / t[mid].k);
            pos = max(pos, static_cast<int>(t[mid].st));//确保位置不小于线段起始点
            if (pos >= t[mid].st && pos <= t[mid].ed) {
                if (ans == -1 || pos < ans)//还没有找到答案或者找到了更小的位置
                    ans = pos, pt = t[mid].f(pos);//更新更优答案位置和对应的函数值
            }
            r = mid - 1;//由于找到了可能的解，缩小右边界继续搜索更优解
        }
    }
    return {ans, pt};
}


signed main() {
    fast;
    int n, s; cin >> n >> s;//物品数量和目标分数
    map<int, int> mp;//价格到成本的映射
    for (int i = 1, v, c; i <= n; ++i) {
        cin >> v >> c;
        if (mp.contains(v)) mp[v] = min(mp[v], c);//已有相同价值，保留最小成本
        else mp[v] = c;//直接添加
    }
    t[++tl] = {0, inf, 0, 0};//第一个位置创建线段 初始线段：从0到无穷大，斜率为0，截距为0
    for (auto [fst, snd] : mp) {//遍历所有不同的价值-成本对
        const int v = fst, c = snd;
        auto [fst1, snd1] = fd(c);//达到成本c所需的最小位置
        const int pos = fst1;
        const __int128 val = snd1;
        if (pos == -1) continue;
        //新线段：从pos+1开始，斜率为v(当前价值)，截距为val-c-v*pos
        auto seg = node{pos + 1, inf, v, val - c - v * pos};
        if (seg.f(inf) <= t[tl].f(inf)) continue;//新线段在无穷处不如现有线段好
        while (hd <= tl) {//维护循环
            int lim = static_cast<int>(max(seg.st, t[tl].st));//计算重叠区域的起始点
            //重叠起始点超过当前线段结束点 新线段在结束点不优于当前线段
            if (lim > t[tl].ed || seg.f(t[tl].ed) <= t[tl].f(t[tl].ed)) {//调整新线段起始点
                seg.st = t[tl].ed + 1; break;
            }
            //计算新旧线段的交点 确保交点在重叠区域内
            if (const int lst = max(lim, static_cast<int>((t[tl].b-seg.b+seg.k-t[tl].k-1)/(seg.k-t[tl].k)));
                lst > lim || lim != t[tl].st) {//检查交点是否有效
                seg.st = lst, t[tl].ed = lst - 1; break;//调整线段边界
            }
            --tl;//移除被新线段完全覆盖的旧线段
        }
        t[++tl] = seg;//将新线段添加到数组中
    }
    cout << fd(s).first;//达到目标分数s所需的最小位置
    return 0;
}