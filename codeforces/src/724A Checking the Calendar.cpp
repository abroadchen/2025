//
// Created by Psy.C on 2026/4/24.
//
/**
(mp[a]+28)%7 == mp[b] - 检查经过28天后是否为对应星期几（28天=4周，星期不变）
(mp[a]+30)%7 == mp[b] - 检查经过30天后是否为对应星期几
(mp[a]+31)%7 == mp[b] - 检查经过31天后是否为对应星期几
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

map<string, int> mp;///星期几及其对应的数字编号
string a, b;///第一个和第二个星期几
int main() {
    fast;
    mp["monday"]=0;mp["tuesday"]=1;mp["wednesday"]=2;mp["thursday"]=3;
    mp["friday"]=4;mp["saturday"]=5;mp["sunday"]=6;
    cin >> a >> b;
    if ((mp[a]+28)%7 == mp[b] || (mp[a]+30)%7 == mp[b] || (mp[a]+31)%7 == mp[b])
        cout << "YES\n";
    else cout << "NO\n";
    return 0;
}