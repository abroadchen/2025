//
// Created by Psy.C on 2026/4/21.
//
/**
滑动窗口：检查每个长度为26的连续子串
提取子串：t = s.substr(i, 26) 获取从位置i开始的26个字符
初始化容器：
st：存储已存在的字母
mp：记录每个字母出现次数
cnt：统计问号数量

处理边界：将目标窗口外的问号替换为'A'
找出缺失字母：遍历A-Z，找出目标窗口内没有的字母
填充问号：用缺失的字母替换目标窗口内的问号
时间复杂度：O(n×26)，其中n是字符串长度
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

string s;
set<char> st;
map<char, int> mp;
queue<char> q;
int main() {
    fast;
    cin >> s;
    if (s.length() < 26) { cout << "-1"; return 0; }
    int flag = 0, cnt;

    for (int i = 0; i < s.length()-25; ++i) {
        string t = s.substr(i, 26);
        cnt = 0;
        st.clear(); mp.clear();
        for (int j = 0; j < 26; ++j) {
            if (t[j] == '?') cnt++;
            else {
                st.insert(t[j]);//添加已存在字母
                mp[t[j]]++;//记录字母出现次数
            }
        }

        if (st.size() + cnt == 26) {
            flag = 1;//标记找到解决方案
            //将非目标窗口内的问号替换为'A'
            for (int j = 0; j < i; ++j)
                if (s[j] == '?') s[j] = 'A';
            for (int j = i + 26; j < s.length(); ++j)
                if (s[j] == '?') s[j] = 'A';
            //找出缺失的字母
            q = queue<char>();
            for (char j = 'A'; j <= 'Z'; ++j)
                if (!mp[j]) q.push(j);//将未出现的字母加入队列
            //用缺失的字母替换窗口内的问号
            for (int j = i; j < i+26; ++j)
                if (s[j] == '?') {
                    s[j] = q.front();//依次填入缺失字母
                    q.pop();
                }
        }
        if (flag) break;
    }
    if (flag) cout << s; else cout << "-1";
    return 0;
}