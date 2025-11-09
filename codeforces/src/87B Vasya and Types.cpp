//
// Created by Psy.C on 2025/11/8.
//
/*
*第一个while循环：处理末尾的星号(*)，每遇到一个星号就：
从字符串末尾移除一个星号
增加plus计数器
第二个while循环：处理开头的取地址符(&)，每遇到一个就：
从字符串开头移除一个&
增加minus计数器
 *
*int x(-1);: 初始化类型值为-1（错误类型）
如果映射表中存在类型s，则获取其对应的指针层数
如果不是错误类型：
加上指针增加数plus
减去指针减少数minus
如果结果小于0，设为-1（错误类型）
 *
*如果命令是"typedef"：
读取新的类型名称buf
将该名称与计算出的指针层数x建立映射关系
*如果命令不是"typedef"（应该是"typeof"之类的查询命令）：
如果结果是错误类型，输出"errtype"
否则输出"void"加上x个星号(*)，表示void类型的x重指针
 */
#include <cstdio>
#include <map>
#include <string>
#include <cstring>
using namespace std;

int n;//操作数量
map<string,int> d;//类型名称到指针层数

int main() {
    scanf("%d",&n);
    d["void"] = 0; d["errtype"] = -1;
    for (int i = 0; i < n; ++i) {
        char cmd[1024], buf[1024];
        scanf("%s %s", cmd, buf);
        string s = string(buf);
        int plus(0), minus(0);
        while (s[s.length() - 1] == '*') { s.resize(s.length() - 1); ++plus; }
        while (s[0] == '&') { s = s.substr(1); ++minus; }
        int x(-1);
        if (d.count(s)) x = d[s];
        if (x != -1) { x += plus; x -= minus; if (x < 0) x = -1; }
        if (strcmp(cmd, "typedef") == 0) { scanf("%s", buf); d[string(buf)] = x; }
        else {
            if (x == -1) printf("errtype\n");
            else {
                printf("void");
                for (int j = 0; j < x; ++j) printf("*");
                printf("\n");
            }
        }
    }
    return 0;
}