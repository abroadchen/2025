//
// Created by Psy.C on 2025/12/5.
//
/*
 *
*遍历所有元素
j获取a[i]在fr中的计数，k获取a[i]在bk中的计数
如果fr中a[i]的数量已达到要求cnt，则输出0并结束程序
如果bk中a[i]的数量能满足剩余需求，则更新最小操作次数ans
*如果还没有找到解，则检查是否可以通过转换得到足够的b[i]元素
如果bk中某个b[i]的数量足够，则设置ans为cnt
*如果ans仍为初始值，说明无解，输出-1
否则输出找到的最小操作次数ans
 */
#include <iostream>
#include <map>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    int n; cin>>n;
    map<ll, int> fr, bk;//出现的次数
    vector<ll> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        cin>>a[i]>>b[i];
        fr[a[i]]++;//将a[i]加入fr映射并增加其计数
        if (a[i] != b[i]) bk[b[i]]++;
    }
    int ans = INT_MAX, j, k;
    const int cnt = (n + 1) / 2;//至少需要多少个相同元素才能满足条件
    for (int i = 0; i < n; ++i) {
        j = fr[a[i]], k = bk[a[i]];
        if (j >= cnt) { cout << "0"; return 0; }
        if (k >= cnt - j) ans = min(ans, cnt - j);
    }
    if (ans == INT_MAX) {
        for (int i = 0; i < n; ++i) {
            if (bk[b[i]] >= cnt) { ans = cnt; break; }
        }
    }
    if (ans == INT_MAX) cout << "-1\n";
    else cout << ans;
    return 0;
}