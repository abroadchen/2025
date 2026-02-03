//
// Created by Psy.C on 2026/2/3.
//
/**
* flag：是否在寻找模式的初始阶段
ok：当前是否在有效的等差数列模式中
*cnt：连续-1的数量
d：当前等差数列的公差
ans：修改次数
 *
*条件1：当前是-1，不在有效模式中，处于初始阶段
cnt++：累加连续-1的个数
*条件2：当前是-1，但在有效模式中
填充规则：a[i] = a[i-1] + d（等差数列）
验证：必须大于0
失败处理：如果不符合条件，增加修改次数
*
条件3：当前是-1，不在初始阶段
寻找后续：跳过连续的-1
计算公差：dif = a[j] - a[i-1]，dis = j + 1 - i
验证整除：dif % dis == 0，确保能形成整数等差数列
更新状态：设置公差，跳转到j位置
*条件4：当前不是-1，但之前有连续-1
计算公差：基于两端的已知值
验证首项：a[i] - d*cnt > 0，确保首项为正
状态更新：根据验证结果更新状态
*条件5：初始阶段结束
条件6：不在有效模式中，计算公差
条件7：当前值不满足等差数列，增加修改次数
 *
 *算法复杂度：O(n) - 单次遍历数组
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 200005
using namespace std;


int main() {
    fast;
    ll n, a[N]; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i]; a[n+1] = -2;//结束标记
    bool flag = true, ok = false;
    ll cnt = 0, d = 0, ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (a[i] == -1 && !ok && flag) cnt++;
        else if (a[i] == -1 && ok) {
            if (a[i-1] + d > 0) a[i] = a[i-1] + d;
            else ans++, cnt = 1, flag = true, ok = false;
        }
        else if (a[i] == -1 && !flag) {
            int j = i + 1;
            while (a[j] == -1) j++;
            if (a[j] == -2) break;
            if (ll dis = j + 1 - i, dif = a[j] - a[i-1]; dif % dis == 0) {
                ok = true;
                d = dif / dis;
                i = j;
            }
            else ok = false, flag = true, i = j - 1, ans++;
        }
        else if (a[i] != -1 && cnt) {
            int j = i + 1;
            while (a[j] == -1) j++;
            if (a[j] == -2) break;
            if (ll dis = j - i, dif = a[j] - a[i]; dif % dis == 0) {
                d = dif / dis;
                if (a[i] - d*cnt > 0) ok = true, flag = false, i = j;
                else i = j - 1, ok = false, flag = true, ans++;
            }
            else i = j - 1, ok = false, flag = true, ans++;
            cnt = 0;
        }
        else if (flag) flag = false;
        else if (!ok) d = a[i] - a[i-1], ok = true;
        else if (a[i-1] + d != a[i]) ans++, flag = true, ok = false, i--;
    }
    cout << ans + 1 << '\n';
    return 0;
}