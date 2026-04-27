//
// Created by Psy.C on 2026/4/27.
//
/**
首先比较a，a小的在前
若a相等，比较b，b小的在前
若a和b都相等，比较c，c小的在前
ans记录当前最优答案，id1和id2记录最优解对应的索引
将三个数重新排列成递减顺序，确保a ≥ b ≥ c
第一步：如果c > b，交换b和c，确保b ≥ c
第二步：如果c > a，交换a和c，确保a ≥ c
第三步：如果a < b，交换a和b，确保a ≥ b
如果当前c值大于已有最优答案ans
更新ans = c，并记录这个最优单个三元组的ID为i+1
将处理后的a, b, c值存入结构体数组
记录原始索引i+1作为ID（题目要求从1开始编号）
初始化指针i=0，r用于标记同一组的右边界
内层循环找到所有a和b值相同的元素范围
r--将r调整到该组的最后一个元素
如果r == i，说明当前组只有一个元素
移动到下一组，继续循环
res = tr[r].b：取当前组中b的最大值（因为已排序，最右边的元素b值最大）
res = min(res, tr[r].c + tr[r-1].c)：计算当前组最后两个元素的c值之和与b值的较小者
如果新的组合解比当前最优解更好
更新ans = res
设置id1 = -1表示最优解来自两个三元组
设置id2 = r记录第二个三元组的位置
移动到下一组，继续查找

如果id1 > 0，说明最优解来自单个三元组：
输出1表示使用一个三元组
输出id1即最优单个三元组的ID
否则最优解来自两个三元组：
输出2表示使用两个三元组
输出tr[id2-1].id和tr[id2].id即最优双三元组的ID
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e6+7;

struct node {
    int a, b, c, id;
    bool operator<(const node &o) const {
        if (a != o.a) return a < o.a;
        if (b != o.b) return b < o.b;
        return c < o.c;
    }
} tr[N];

int n;
int main() {
    fast;
    cin >> n;
    int ans = 0, id1 = 0, id2 = 0;
    for (int i = 0, a, b, c; i < n; ++i) {
        cin >> a >> b >> c;
        if (c > b) swap(b, c);
        if (c > a) swap(a, c);
        if (a < b) swap(a, b);
        if (ans < c) { ans = c; id1 = i + 1; }
        tr[i].a = a; tr[i].b = b; tr[i].c = c;
        tr[i].id = i + 1;
    }
    sort(tr, tr + n);
    int i = 0, r;
    while (i < n) {
        r = i;
        while (r < n && tr[r].a == tr[i].a && tr[r].b == tr[i].b) r++;
        r--;
        if (r == i) { i = r + 1; continue; }
        int res = tr[r].b;
        res = min(res, tr[r].c + tr[r-1].c);
        if (ans < res) { ans = res; id1 = -1; id2 = r; }
        i = r + 1;
    }
    if (id1 > 0) cout << 1 << '\n' << id1 << '\n';
    else cout << 2 << '\n' << tr[id2-1].id << ' ' << tr[id2].id << '\n';
    return 0;
}