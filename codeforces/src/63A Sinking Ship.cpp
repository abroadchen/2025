//
// Created by Psy.C on 2025/10/29.
//
/*
*c：存储船长(captain)的名字
w：存储妇女(woman)和儿童(child)的名字
m：存储男人(man)的名字
r：存储老鼠(rat)的名字
*na：临时存储名字(name)
p：临时存储职位(post)
 *
*const string& x：使用常量引用避免拷贝，提高效率
endl：输出换行符
 *
 */
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int n;
vector<string> c, w, m, r;
string na, p;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cin>>n;
    for (int i = 0; i < n; ++i) {
        cin >> na >> p;
        if (p == "captain") c.push_back(na);
        else if (p == "woman" || p == "child") w.push_back(na);
        else if (p == "man") m.push_back(na);
        else r.push_back(na);
    }
    for (const string& x : r) cout << x << endl;
    for (const string& x : w) cout << x << endl;
    for (const string& x : m) cout << x << endl;
    for (const string& x : c) cout << x << endl;
    return 0;
}