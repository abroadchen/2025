//
// Created by Psy.C on 2025/10/26.
//
/*
 *定义宏sz，用于获取容器大小并转换为int类型
*k: 字符集大小
n: 字符串长度
ok(1): 标志变量，表示是否可能构造回文串，初始为1(可能)
cnt(0): 问号计数器
p(0): 中间位置索引
nd: 需要的不同字符数
s: 输入字符串
v: 存储前k个小写字母的向量
m: 字符频率映射
st, st2: 两个字符集合
 *
 *将前k个小写字母('a'到'a'+k-1)添加到向量v中
 *检查是否可能构造：如果字符种类数的两倍大于字符串长度+1，则不可能构造回文串
 *否则继续处理：统计字符串中每个字符的出现次数
*遍历字符串的前半部分，检查对称位置的字符：
a是前半部分字符，b是对应后半部分字符
如果两个都不是问号且不相等，则无法构造回文串，设置ok=0
 *如果一边是问号另一边不是，将问号替换为非问号字符以保持对称
*计算中间位置p：
如果字符串长度为奇数，p为中间位置+1
否则p为中间位置
*遍历前半部分（包括中间字符）：
统计问号数量
将非问号字符插入集合st中
 *计算还需要的不同字符数：k减去已有的不同字符数
*处理每个问号：
如果当前问号数不等于需要的不同字符数，将问号替换为'a'
否则，在前k个字母中找到一个尚未使用的字符来替换问号
 *检查最终字符串是否包含k种不同字符，如果不包含则标记为不可能
 */
#include <vector>
#include <ios>
#include <iostream>
#include <map>
#include <set>
#define sz(a) ((int)(a).size())
using namespace std;

int k, n, ok(1), cnt(0), p(0), nd;
string s;
vector<char> v;
map<char, int> m;
set<char> st, st2;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    cin >> k >> s; n = sz(s);
    for (int i = 0; i < k; ++i) v.push_back('a' + i);

    if (k * 2 > n + 1) ok = 0;
    else {
        for (auto c : s) m[c]++;
        for (int i = 0; i < n / 2; ++i) {
            char a = s[i], b = s[n - i - 1];
            if (s[i] != '?' && s[n - i - 1] != '?' && a != b) { ok = 0; break; }
            if (a == '?' && b != '?') s[i] = b;
            if (b == '?' && a != '?') s[n - i - 1] = a;
        }

        if (n % 2) p = n / 2 + 1;
        else p = n / 2;

        for (int i = 0; i < p; ++i) {
            if (s[i] == '?') cnt++;
            else st.insert(s[i]);
        }
        nd = sz(st);
        nd = k - nd;
        for (int i = 0; i < p; ++i) {
            char a = s[i];
            if (a == '?') {
                if (cnt != nd) {
                    s[i] = 'a', s[n - i - 1] = 'a';
                    cnt--;
                } else {
                    for (auto x : v) {
                        if (m[x] == 0) {
                            s[i] = x;
                            s[n - i - 1] = x;
                            m[x]++;
                            break;
                        }
                    }
                }
            }
        }
        for (auto c : s) st2.insert(c);
        if (sz(st2) != k) ok = 0;
    }
    if (!ok) cout << "IMPOSSIBLE";
    else cout << s;

    return 0;
}