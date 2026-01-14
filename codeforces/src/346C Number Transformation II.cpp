//
// Created by Psy.C on 2026/1/13.
//
///O((a-b) + n * log(a/b))，其中n是数组长度
/**
* n：输入的数字个数
a, b：目标区间
x[N]：存储输入的数字
r2[N]：存储每个位置能到达的最远位置
to[N]：存储跳跃映射
 *unique(x + 1, x + n + 1)：去重函数，返回去重后的结束迭代器
 *static_cast<int>(unique(...) - x - 1)：计算去重后的长度
 *
 */
#include <algorithm>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 1000100
using namespace std;


int main() {
    fast;
    int n, a, b, x[N], r2[N], to[N]; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> x[i];
    cin >> a >> b;//目标区间[a, b]
    sort(x + 1, x + n + 1);
    n = static_cast<int>(unique(x + 1, x + n + 1) - x - 1);//去重后的长度
    //从位置i开始，能一步到达的最远位置
    for (int i = 0; i <= a - b; ++i) r2[i] = i + 1;//表示可以前进1步
    for (int i = 1; i <= n; ++i) {
        ll st = b / x[i] * x[i];//小于等于b的x[i]的最大倍数
        if (st < b) st += x[i];//跳到下一个倍数
        while (st < a) {//处理区间[b, a]内的所有x[i]的倍数
            ll r = st + x[i] - 1;//当前段的右端点
            if (r > a) r = a;
            r2[st - b] = max(r2[st - b], static_cast<int>(r - b));//更新可达范围
            st = r + 1;//移动到下一段的起始位置
        }
    }
    //to[r]：从位置r可以一步跳到的最远位置
    for (int l = 0, r = 1; l <= a - b; ++l) {
        const int nr = r2[l];//位置l能到达的最远位置
        while (r <= nr) { to[r] = l; ++r; }//构建反向映射
    }
    int ans = 0, now = a - b;//从位置a-b开始，每次跳到to[now]
    while (now) { ans++; now = to[now]; }
    cout << ans << '\n';
    return 0;
}