//
// Created by Psy.C on 2026/11/17.
//

/**
真正学会的起点..
一个取最小值的小工具：若 y < x，则把 x 更新为 y 并返回 1（表示更新成功）；否则返回 0。用于求相邻段值的最小值
a[N] 存储各（代表下标处的）值。
cmp 是一个functor，作为 set<int,cmp> 的比较准则：先按 a[x] 从小到大，若值相等再按下标 x 从小到大。这样 s1 里的元素会按"值优先、下标次之"有序
s1：带自定义比较器（按值排）的集合，用于取当前值最小的段。
s2：按下标升序的普通 set<int>，用于按下标定位（找到当前段的相邻段）
lst 记录当前段的首个下标。
逐个读入 a[i]。只要 a[i] 和当前段首字符 a[lst] 不同，说明新一段开始：把上一段的起始下标 lst 插入两个集合，然后更新 lst = i。
循环结束后，把最后一段的起始下标 lst 也插入两个集合。
效果：s1、s2 中保存的是所有连续相同值段的段首下标。例如 a = [1,1,2,2,3,2,2]，段首是下标 1、3、5、6
只要还有超过 1 个段没处理完，就继续贪心消去
取出当前值最小的段首下标 l（因为 s1 按值升序，begin() 就是值最小的段），并从 s1 中移除它
从 s2（按下标有序）中删除 l，s2.erase 返回被删元素的下一个迭代器，记为 nxt。所以 nxt 指向原 l 在按下标顺序中的后一个段首
计算当前段 [l, r] 的右端点 r：若 nxt 是 end()（即 l 是最后一段），则 r = n（到数组末尾）；否则 r = *nxt - 1（到下一个段的段首前一个位置）。
得到当前段的区间为 [l, r]，长度 r-l+1
当前段长度 r-l+1 如果是奇数，直接输出 NO 并结束程序。原因：一个连续同值段要能被合法消去（合并/归并），长度必须为偶数（这类题的配对要求）
计算相邻两段的较小值：nxt 指向后一段，prev(nxt) 指向前一段（在 s2 中）。
用 chkmin 把 val 更新为相邻段值的较小者（如果这两端存在的话）。这是要赋给 a[l] 的"合并值"
把当前段 l 的值改为相邻段的较小值 val（作为"合并后的段的值"）
若右邻段存在，且合并后 a[l] 与右邻段值相同 → 说明可以向右合并：把右邻段从 s1、s2 中删除，nxt 更新为删除右邻段后的下一个。
检查左邻：若左邻存在且值也等于 a[l]，则（左邻段已被删? 这里分支为空 {}，什么都不做，表示"已并入"）；否则把段 l（值已更新）重新插回 s1 和 s2，继续下一轮
所有段都成功消去（s1 只剩 ≤1 个），输出 YES
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

template<class T>
bool chkmin(T &x, const T &y) {
    return x > y ? x = y, 1 : 0;
}

constexpr int N = 2e5+10;

int a[N];
struct cmp {
    bool operator()(int x, int y) const {
        return a[x] != a[y] ? a[x] < a[y] : x < y;
    }
};

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

set<int,cmp> s1;
set<int> s2;
int main() {
    fast;
    int n = rd(), lst = 1;
    for (int i = 1; i <= n; ++i) {
        a[i] = rd();
        if (a[i] != a[lst]) s1.insert(lst), s2.insert(lst), lst = i;
    }
    s1.insert(lst), s2.insert(lst);
    while (s1.size() > 1) {
        int l = *s1.begin(); s1.erase(s1.begin());
        auto nxt = s2.erase(s2.find(l));
        int r = nxt == s2.end() ? n : *nxt-1;
        if ((r-l+1)&1) return cout << "NO\n", 0;
        int val = INT_MAX;
        if (nxt != s2.end()) chkmin(val, a[*nxt]);
        if (nxt != s2.begin()) chkmin(val, a[*prev(nxt)]);
        a[l] = val;
        if (nxt != s2.end() && a[l] == a[*nxt])
            s1.erase(*nxt), nxt = s2.erase(nxt);
        if (nxt != s2.begin() && a[l] == a[*prev(nxt)]) {}
        else s1.insert(l), s2.insert(l);
    }
    cout << "YES\n";
    return 0;
}