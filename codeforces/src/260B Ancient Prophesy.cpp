//
// Created by Psy.C on 2025/12/19.
//
/*
*x + "*1"：在日期字符串后添加"*1"
例如："12-03-2014" 变成 "12-03-2014*1"
格式字符串 "%2d-%2d-%4d*%d" 要求：
2位数字-2位数字-4位数字*1位数字
这样可以严格验证DD-MM-YYYY格式
 *
*时间复杂度：O(n)，其中n是字符串长度
空间复杂度：O(k)，其中k是不同日期的数量
 */
#include <iostream>
#include <map>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

const int day[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

int main() {
    fast;
    string str, ans; cin>>str;
    int d, m, y, j, n = 0;//d:日, m:月, y:年, j:临时变量, n:最高频率
    map<string, int> mp;//字符串到出现次数的映射
    for (int i = 0; i + 10 <= str.length(); ++i) {
        string x = str.substr(i, 10);
        if (sscanf((x + "*1").c_str(), "%2d-%2d-%4d*%d",
            &d, &m, &y, &j) != 4) continue;
        if (y < 2013 || y > 2015 || m < 1 || m > 12 ||
            d < 1 || d > day[m]) continue;
        mp[x]++;//增加该日期的出现次数
        if (n < mp[x]) { n = mp[x]; ans = x; }//更新最高频率 更新最频繁的日期
    }
    cout<<ans;
    return 0;
}