/**
 *
*
计算d1数组的前缀和，sum1[i]表示前i个元素的和
计算d2数组的前缀和，sum2[i]表示前i个元素的和
 *
*双重循环遍历所有可能的选择组合
l = i + j * 2：计算选择的数量（i个类型1的元素，j个类型2的元素，每个类型2算作2个）
r = (sum1[c1] - sum1[i]) + (sum2[c2] - sum2[j])：计算剩余元素的总和
如果选择的数量l大于等于剩余元素和r，则更新答案为最小值
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define N 105
#define inf 0x3f3f3f3f
using namespace std;


int main() {
    fast;
    int n, d1[N], d2[N], c1 = 0, c2 = 0; cin >> n;
    for (int i = 1, op, w; i <= n; ++i) {
        cin >> op >> w;
        if (op == 1) d1[++c1] = w; else d2[++c2] = w;
    }
    sort(d1 + 1, d1+c1+1, greater<>());
    sort(d2 + 1, d2+c2+1, greater<>());
    int sum1[N], sum2[N], ans = inf;
    for (int i = 1; i <= c1; ++i) sum1[i] = d1[i] + sum1[i-1];
    for (int i = 1; i <= c2; ++i) sum2[i] = d2[i] + sum2[i-1];
    for (int i = 0, l = 0; i <= c1; ++i) {
        for (int j = 0, r; j <= c2; ++j) {
            l = i + j * 2;
            r = (sum1[c1] - sum1[i]) + (sum2[c2] - sum2[j]);
            if (l >= r) ans = min(ans, l);
        }
    }
    cout << ans << '\n';
    return 0;
}