//
// Created by Psy.C on 2026/1/24.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define rep(i,n) for (int i = 0; i <= n; ++i)
using namespace std;

ll x, k;//目标值 递归深度或步数
/**
 *
 * @param now 当前递归层数
 * @param a1 当前的两个值
 * @param a2
 * @param s1 四个状态标志
 * @param e1
 * @param s2
 * @param e2
 * @return
 */
ll dfs(const int now, const ll a1, const ll a2, const int s1, const int e1, const int s2, const int e2) {
    if (a2 > x) return a2;//大于目标值
    if (now == k) return a2;//达到最大递归深度k
    //递归调用，更新参数
    return dfs(now + 1, a2, a1 + a2 + (e1 && s2 ? 1 : 0), s2, e2, s1, e2);
}


ll n, m;
bool ok(const ll a1, const ll a2, const int s1, const int e1, const int s2, const int e2) {
    if ((a1<<1) + s1 + e1 > n) return false;
    if ((a2<<1) + s2 + e2 > m) return false;
    if (dfs(2, a1, a2, s1, e1, s2, e2) == x) return true;//是否等于目标值
    return false;
}

/**
 *
 * @param a  要放置的AC对数量
 * @param s 开始和结束标志
 * @param e
 * @param len
 * @return
 */
string build(int a, const int s, const int e, int len) {
    string ss; ss.resize(len);//创建并调整字符串大小
    int l = 0;//当前填充位置
    if (s) ss[l++] = 'C';//s为真，在开头放置'C'
    if (e) ss[--len] = 'A';//e为真，在末尾放置'A'
    while (a--) { ss[l++] = 'A'; ss[l++] = 'C'; }//循环放置AC对
    while (l < len) ss[l++] = 'X';//用'X'填充剩余位置
    return ss;
}


int main() {
    fast;
    cin >> k >> x >> n >> m;
    rep(a1,n/2) rep(a2,m/2) rep(i,15) {//4位二进制的所有可能
        //检查i的最低位 第二位 第三位 第四位
        if (ok(a1, a2, (i&1) > 0, (i&2) > 0, (i&4) > 0, (i&8) > 0)) {
            cout << build(a1, (i&1) > 0, (i&2) > 0, static_cast<int>(n)) << '\n';
            cout << build(a2, (i&4) > 0, (i&8) > 0, static_cast<int>(m)) << '\n';
            return 0;
        }
    }
    cout << "Happy new year!\n";
    return 0;
}