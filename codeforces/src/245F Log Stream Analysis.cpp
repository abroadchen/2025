//
// Created by Psy.C on 2025/12/16.
//
/*
*定义一个函数inv，将字符串转换为整数
创建stringstream对象in
将字符串str输入到stringstream中
从stringstream中提取整数值
返回转换后的整数
 *
 *n是时间窗口，m是触发次数
 *读取输入缓冲区中剩余的一行（消耗掉第一行末尾的换行符）
 *
 *
*找到在时间窗口内的起始位置
i指向第一个满足v[i] + n > tot的位置
也就是在[n秒窗口]内的最早时间戳位置
 *
*检查当前窗口内是否有至少m个事件
v.size() - i表示在时间窗口内的事件数量
如果满足条件，输出当前行的前19个字符（日期时间部分）并退出程序
 */
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int inv(const string& str) {
    int val;
    stringstream in;
    in << str;
    in >> val;
    return val;
}

int main() {
    fast;
    int n, m; cin >> n >> m;
    string s; getline(cin, s);
    vector<int> v;//存储时间戳
    while (getline(cin, s)) {//循环读取每一行输入，直到文件结束
        const int y[] = {0,31,29,31,30,31,30,31,31,30,31,30,31},
        mon = inv(s.substr(5, 2)),
        d = inv(s.substr(8, 2)),
        h = inv(s.substr(11, 2)),
        minute = inv(s.substr(14, 2)),
        second = inv(s.substr(17, 2));
        int tot = second + minute * 60 + h * 3600 + d * 24 * 3600;//当天的时间戳
        for (int i = 1; i < mon; ++i) tot += y[i] * 24 * 3600;//从年初开始的总秒数
        int i = 0;
        while (i < v.size() && v[i] + n <= tot) i++;
        v.push_back(tot);
        if (v.size() - i >= m) { cout << s.substr(0, 19); return 0; }
    }
    cout << -1 << '\n';
    return 0;
}