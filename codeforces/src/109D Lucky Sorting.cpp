//
// Created by Psy.C on 2025/11/13.
//
/*
*n: 存储元素个数。
i, t: 循环控制变量或临时存储值。
z: 记录第一个幸运数字的位置索引（初始为 -1）。
p: 存放原始数据及其位置的 pair 向量（first 是数值，second 是原索引）。
a: 存储交换操作记录的向量。
 *
*取出当前最后一位数字 (t = x % 10)。
如果不是 4 或 7，则返回 false。
继续除以 10 直到所有位都被检查完。
 *
 *执行索引 x 和 y 对应的数据项交换，并更新其关联索引及记录交换动作
*如果 x 不等于 y 才进行交换。
使用 swap() 交换两个元素的第一字段（即数值）。
更新这两个元素的新索引关系。
将此次交换记录添加到 a 中。
 *
*遍历读取每个元素 t 并将其连同原始索引一起加入向量 p。
如果尚未找到幸运数且当前元素是幸运数，则记录它的索引 z
*按照数值大小对 p 排序。
根据排序后的顺序重新设置每项的实际索引值（构建映射）
 *
*查找第一个不在正确位置上的元素索引 i。
如果所有元素都在正确位置上（i == n），说明无需任何交换，输出 "0" 并结束。
如果存在未归位元素但没有找到幸运数（z == -1），无法完成任务，输出 "-1" 结束。
 *
*对于每一个不处于目标位置的元素：
获取它现在所在的位置 t。
通过两次调用 jh() 把这个元素放到最终应该放置的位置上。
更新新的“幸运数”位置 z

 */
#include <algorithm>
#include <cstdio>
#include <vector>
#define rep(i, n) for (i = 0; i < (n); ++i)
using namespace std;

int n, i, t, z(-1);
vector<pair<int, int> > p, a;

bool ok(int& x) {
    int t;
    do {
        t = x % 10;
        if (t != 4 && t != 7) return false;
    } while (x /= 10);
    return true;
}

void  jh(int x, int y) {
    if (x != y) {
        swap(p[x].first, p[y].first);
        p[p[x].first].second = x;
        p[p[y].first].second = y;
        a.push_back({x, y});
    }
}


int main() {
    scanf("%d", &n);
    rep(i, n) {
        scanf("%d", &t);
        p.push_back({t, i});
        if (z == -1) if (ok(t)) z = i;
    }
    sort(p.begin(), p.end());
    rep(i,n) p[p[i].second].first = i;
    rep(i,n) p[p[i].first].second = i;
    for (i = 0; i < n && p[i].first == i; ++i);
    if (i == n) return puts("0");
    if (i < n && z == -1) return puts("-1");
    for (; i < n; ++i) if (p[i].first != i) {
        t = p[i].second;
        jh(z, i);
        jh(i, t);
        z = t;
    }
    printf("%d\n", a.size());
    rep(i,a.size()) printf("%d %d\n", a[i].first+1, a[i].second+1);
    return 0;
}