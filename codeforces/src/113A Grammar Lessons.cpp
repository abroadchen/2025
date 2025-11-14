//
// Created by Psy.C on 2025/11/14.
//
/*
*条件1：sz(s) >= sz(t)确保s长度不小于t
条件2：s.substr(sz(s) - sz(t))提取s的后缀，与t比较
 *
*词性代码：
1：形容词 (adjective)
2：名词 (noun)
3：动词 (verb)
性别代码：
0：阳性 (masculine)
1：阴性 (feminine)
 *
*如果只有一个单词
如果该单词有效（性别代码不为-1），输出"YES"
否则输出"NO"
 *
*如果有任何单词无效（性别代码为-1），输出"NO"并结束
如果有任何单词与第一个单词性别不一致，输出"NO"并结束
 *
*col：记录第一个单词的词性代码
cnt：计数名词个数（如果第一个词是名词则为1，否则为0）
flag：标记语法规则是否满足，初始为true
 *
*遍历剩余单词，检查语法顺序规则：
如果前一个是形容词(col==1)：后续只能是形容词(1)或名词(2)
如果前一个是名词或动词(col!=1)：后续只能是动词(3)
更新当前词性到col
如果当前词是名词，计数器加1
 *
 *如果语法规则满足(flag为true)且恰好有一个名词(cnt==1)，输出"YES"
 */
#include <iostream>
#include <vector>
#define sz(a) ((int)(a).size())
using namespace std;

typedef pair<int,int> ii;
string s;
//检查字符串s是否以t结尾
bool ok(string s, string t) { return sz(s) >= sz(t) && s.substr(sz(s) - sz(t)) == t; }

ii f(string s) {//识别单词的词性和性别
    if (ok(s, "lios")) return {1, 0};
    if (ok(s, "liala")) return {1, 1};
    if (ok(s,"etr")) return {2, 0};
    if (ok(s, "etra")) return {2, 1};
    if (ok(s, "initis")) return {3, 0};
    if (ok(s, "inites")) return {3, 1};
    return {-1, -1};
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    vector<ii> v;//存储词性分析结果
    while (cin >> s) v.push_back(f(s));
    if (sz(v) == 1) {
        if (v[0].second != -1) puts("YES");
        else puts("NO");
        return 0;
    }
    for (int i = 0; i < sz(v); ++i) {
        if (v[i].second == -1 || v[i].second != v[0].second) {
            puts("NO");
            return 0;
        }
    }
    int col = v[0].first, cnt = v[0].first == 2; bool flag = true;
    for (int i = 1; i < sz(v); ++i) {
        if (col == 1) flag = flag && (v[i].first == 1 || v[i].first == 2);
        else flag = flag && v[i].first == 3;
        col = v[i].first;
        cnt += col == 2;
    }
    if (flag && cnt == 1) puts("YES");
    else puts("NO");
    return 0;
}