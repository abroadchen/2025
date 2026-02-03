//
// Created by Psy.C on 2026/2/3.
//
/**
* num{}：编号（初始化为0）
cnt{}：数量要求（初始化为0）
w{}：权重/价值（初始化为0）
id{}：桌号ID（初始化为0）
v=0：是否被使用（初始化为0，表示未使用）
 *
*num{}：桌子编号（初始化为0）
p{}：桌子容量/能力（初始化为0）
v=false：桌子是否被占用（初始化为false）
 *
*按权重w降序排列（x.w > y.w）
如果权重相同，按数量要求cnt升序排列（x.cnt < y.cnt）
 *
 *ans计数成功匹配，sum累计权重和
 *桌子j未被占用 桌子j的能力值≥节点i的需求量
 *
 *时间复杂度 O(n×k)
 */
#include <algorithm>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 10000
using namespace std;

struct node { int num{}, cnt{}, w{}, id{}, v=0; } a[N];
struct desk { int num{}, p{}; bool v=false; } b[N];

int main() {
    fast;
    int n; cin >> n;//节点数量
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].cnt >> a[i].w; a[i].num = i;
    }
    int k; cin >> k;//桌子数量
    for (int i = 1; i <= k; ++i) {
        cin >> b[i].p; b[i].num = i;
    }
    sort(a + 1, a + n + 1, [](const node &x, const node &y) {
        if (x.w == y.w) return x.cnt < y.cnt;
        return x.w > y.w;
    });
    sort(b + 1, b + 1 + k, [](const desk &x, const desk &y) {
        return x.p < y.p;
    });
    int ans = 0, sum = 0;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= k; ++j) {
        if (!b[j].v && b[j].p >= a[i].cnt) {
            ans++;//匹配计数加1
            sum += a[i].w;//累加权重
            b[j].v = true;//标记桌子j为已占用
            a[i].v = 1;//标记节点i为已匹配
            a[i].id = b[j].num;//记录节点i匹配的桌子编号
            break;
        }
    }
    cout << ans << ' ' << sum << '\n';
    for (int i = 1; i <= n; ++i) if (a[i].v) {//节点i被匹配了
        cout << a[i].num << ' ' << a[i].id << '\n';
    }
    return 0;
}