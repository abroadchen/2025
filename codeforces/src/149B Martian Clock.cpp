//
// Created by Psy.C on 2025/11/22.
//
/*
 *f: 标记是否遇到冒号（0表示小时部分，1表示分钟部分）
 *b: 最小可能的进制基数（至少比最大数字大1）
 *
 *解析时间字符串
 *如果遇到冒号，标记进入分钟部分
 *如果是数字字符(0-9)
 *如果是字母字符(A-Z)
 *如果是小时部分，且数字大于0或hour不为空（去除前导零）
 *如果是分钟部分，且数字大于0或minute不为空（去除前导零）
 *更新最小进制基数（必须比最大数字大1）
 *
 *如果小时和分钟都是单个有效数字，输出-1
 *遍历所有可能的进制（从最小进制到60）
 *
 *
 */
#include <vector>
#include <iostream>
using namespace std;

int main() {
    string time; getline(cin, time);//时间字符串
    vector<int> hour, minute;//小时和分钟部分的数字
    bool f(0); int b(2);
    for (int i = 0, c; i < time.size(); ++i) {
        if (time[i] == ':') { f = 1; continue; }
        else if ('0' <= time[i] && time[i] <= '9') c = time[i] - '0';
        else if ('A' <= time[i] && time[i] <= 'Z') c = 10 + (time[i] - 'A');

        if (!f && (c > 0 || !hour.empty())) hour.push_back(c);
        else if (f && (c > 0 || !minute.empty())) minute.push_back(c);
        if (c + 1 > b) b = c + 1;
    }
    vector<int> ans;
    if ((hour.empty() || (hour.size() == 1 && hour[0] < 24)) &&
        (minute.empty() || (minute.size() == 1 && minute[0] < 60)))
        puts("-1");
    else {
        for (int i = b; i <= 60; ++i) {
            bool p = 1;//标记当前进制是否合法
            int m = 0;//分钟数值
            for (int j : minute) {// 计算分钟部分在进制i下的十进制值
                m = i * m + j;
                if (m >= 60) { p = 0; break; }//分钟不能超过59
            }
            int h = 0;//小时数值
            for (int j : hour) {//计算小时部分在进制i下的十进制值
                h = i * h + j;
                if (h >= 24) { p = 0; break; }//小时不能超过23
            }
            if (p) ans.push_back(i);//如果当前进制合法，加入结果列表
        }
        if (ans.empty()) puts("0");//没有合法进制
        else {
            for (const int x : ans) printf("%d ", x);
            puts("");
        }
    }
    return 0;
}