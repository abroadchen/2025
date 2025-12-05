//
// Created by Psy.C on 2025/12/6.
//
/*
*n：序列数量
k：当前序列长度
a：当前序列元素值
x, y, m：生成序列的参数
b：临时变量，用于计算下一个序列元素
 *
*x：递减次数
y：序列元素值
z：序列编号 同时声明结构体数组p，用于存储所有序列元素信息
 *
*cnt：已处理的元素总数，初始为0
ans：记录最大的递减次数，初始为-1
 *t记录当前序列的递减次数
 *
*如果已处理元素数量未超过阈值，则将当前元素信息存储到结构体数组p中：
x字段存储当前递减次数t
y字段存储当前元素值a
z字段存储当前序列编号i
 *根据递推公式计算下一个元素的值：b = (x * a + y) % m
 *如果下一个元素b小于当前元素a，且不是序列最后一个元素，则递减次数t加1
 *更新当前元素值为下一个元素值，为下一次循环做准备
 *更新最大递减次数ans为当前序列递减次数t和之前最大值中的较大者
 *
*首先按递减次数x升序排列
如果递减次数相同，则按元素值y升序排列
如果元素值也相同，则按序列编号z升序排列
 *按排序后的顺序输出每个元素的值和所属序列编号
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr  int N = 200010, inf = 2e5;
ll n, k, a, x, y, m, b;

struct node { int x, y, z; } p[N];

int main() {
    fast;
    int cnt = 0, ans = -1;
    cin>>n;
    for (int i = 1; i <= n; ++i) {//处理第1到第n个序列
        int t = 0;
        cin >> k >> a >> x >> y >> m;
        for (int j = 1; j <= k; ++j) {//当前序列的第1到第k个元素
            if (cnt <= inf) p[cnt++] = {t, static_cast<int>(a), i};
            b = (x * a + y) % m;
            if (b < a && j != k) t++;
            a = b;
        }
        ans = max(ans, t);
    }
    cout << ans << '\n';
    if (cnt <= inf) {
        sort(p, p + cnt, [](const node& w, const node& l) {
            if (w.x == l.x) return w.y < l.y || (w.y == l.y && w.z < l.z);
            return w.x < l.x;
        });
        for (int i = 0; i < cnt; ++i) cout << p[i].y << ' ' << p[i].z << '\n';
    }
    return 0;
}