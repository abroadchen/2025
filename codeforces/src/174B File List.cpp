//
// Created by Psy.C on 2025/11/29.
//
/*
*s: 输入的字符串
l, r: 左右边界索引
len: 长度
pos, np: 当前位置和下一个位置
string::npos: 表示"未找到"的特殊值(-1)
fs: 存储分割点位置的向量
ok: 标记格式是否正确
 *
 *由于pos初始为string::npos，pos+1会溢出为0，所以实际从位置0开始查找
 *
*查找下一个点号('.')的位置
如果找到点号：
检查点号位置是否有效(不能在开头，前面部分不能超过8位)
更新当前位置，继续查找下一个点号
*如果还有下一个点号：
计算两点之间的长度
验证长度是否在合法范围内(2-11位)
根据长度确定分割点位置
将分割点存入向量
*处理最后一部分：
检查是否有至少一个点号
验证最后部分长度是否合法(1-3位)
 *
*如果格式不正确输出"NO"，否则：
输出"YES"
按照分割点输出各个部分
 */
#include <iostream>
#include <vector>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

typedef unsigned long long ull;

int main() {
    fast;
    string s; cin >> s;
    ull l, r, len, pos, np;
    l = r = 0, pos = np = string::npos;
    vector<ull> fs;
    bool ok = true;
    np = s.find('.', pos + 1);
    while (np != string::npos) {
        if (np == l || np - l > 8) { ok = false; break; }
        pos = np;//更新当前位置为找到的点号位置
        np = s.find('.', pos + 1);
        if (np != string::npos) {
            len = np - pos - 1;//减1是因为不包括点号本身
            if (len > 11 || len < 2) { ok = false; break; }
            if (len > 8) r = pos + len - 8;//后面数8个字符作为一部分，其余作为另一部分
            else r = pos + 1;
            fs.push_back(r);
            l = r + 1;
        }
    }
    if (pos == string::npos) ok = false;
    else {
        len = s.size() - pos - 1;//最后一个点号之后的字符长度
        if (len <= 0 || len > 3) ok = false;
        else fs.push_back(s.size() - 1);//字符串末尾位置加入分割点向量
    }
    if (!ok) cout << "NO\n";
    else {
        cout << "YES\n";
        int i = 0;
        for (const auto p : fs) {
            while (i <= p) cout << s[i++];//直到分割点p为止
            cout << '\n';
        }
    }
    return 0;
}