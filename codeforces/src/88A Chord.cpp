//
// Created by Psy.C on 2025/11/8.
//
/*
 *这里H代表西方音乐中的B音（有些地区用H表示B，用B表示B♭）
 *
*遍历所有音符位置：
如果当前位置i有音符（idx[i]为1）：
检查是否构成大三和弦：根音+i，大三度+i+4，完全五度+i+7
检查是否构成小三和弦：根音+i，小三度+i+3，完全五度+i+7
使用模运算(%12)处理十二平均律的循环特性
 *
*如果有重复音符，输出"strange"（不构成和弦）
如果遍历完所有可能都没有找到匹配，也输出"strange"
 *
 */
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    string str[12] = {
        "C", "C#", "D", "D#",
        "E", "F", "F#", "G",
        "G#", "A", "B", "H"
    };
    vector<string> v(3);
    cin >> v[0] >> v[1] >> v[2];
    if (v[0] != v[1] && v[1] != v[2] && v[0] != v[2]) {//检查三个音符是否互不相同
        vector<int> idx(12, 0);
        for (int i = 0; i < 12; ++i) {//遍历12个音名，如果输入的音符匹配，则在对应位置标记为1
            if (v[0] == str[i] || v[1] == str[i] ||
                v[2] == str[i]) idx[i] = 1;
        }
        for (int i = 0; i < 12; ++i) {
            if (idx[i]) {
                if (idx[(i + 4) % 12] && idx[(i + 7) % 12]) { cout << "major"; return 0; }
                if (idx[(i + 3) % 12] && idx[(i + 7) % 12]) { cout << "minor"; return 0; }
            }
        }
    } else { cout << "strange"; return 0; }
    cout << "strange";
    return 0;
}