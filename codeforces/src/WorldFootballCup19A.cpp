//
// Created by Psy.C on 2025/9/17.
//

#include <ios>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

/**
* name: 队伍名称
pts: 获得的积分
diff: 净胜球数（进球数减去失球数）
scored: 总进球数

 */
struct perf {
    string name;
    long pts, diff, scored;
};

/**
* 主要标准：积分高的排名靠前
次要标准：积分相同时，净胜球多的排名靠前
第三标准：积分和净胜球都相同时，进球数多的排名靠前
 * @param a
 * @param b
 * @return
 */
bool perfCompare(perf a, perf b) {
    if (a.pts > b.pts) return true;
    else if (a.pts == b.pts && a.diff > b.diff) return true;
    else if (a.pts == b.pts && a.diff == b.diff && a.scored > b.scored) return true;
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    
    long n; cin >> n;
    map<string, perf> m;//创建一个映射表来存储各队伍的表现数据
    for (long p = 0; p < n; ++p) {
        string s; cin >> s;
        m[s].name = s;
        m[s].pts = m[s].diff = m[s].scored = 0;
    }

    for (long p = 0; p < n * (n - 1) / 2; ++p) {
        string names, goals; cin >> names >> goals;
        string xn(""), yn("");
        bool dash(0);

        for (long p = 0; p < names.size(); ++p) {
            if (names[p] == '-') dash = true;
            else if (dash) yn += names[p];
            else xn += names[p];
        }

        long xg(0), yg(0); bool colon(0);
        for (long p = 0; p < goals.size(); ++p) {
            if (goals[p] == ':') colon = true;
            else if (colon) yg = 10 * yg + (goals[p] - '0');//将字符串数字转换为整数
            else xg = 10 * xg + (goals[p] - '0');
        }

        m[xn].scored += xg; m[yn].scored += yg;
        m[xn].diff += xg - yg; m[yn].diff += yg - xg;
        if (xg > yg) m[xn].pts += 3;
        else if (xg < yg) m[yn].pts += 3;
        else {
            m[xn].pts += 1;
            m[yn].pts += 1;
        }
    }

    vector<perf> v;//将映射表数据转换为向量以便排序
    for (map<string, perf>::iterator it = m.begin(); it != m.end(); ++it) v.push_back(it->second);
    sort(v.begin(), v.end(), perfCompare);
    vector<string> res(n / 2);
    for (long p = 0; p < n / 2; ++p) res[p] = v[p].name;
    sort(res.begin(), res.end());
    for (long p = 0; p < res.size(); ++p) cout << res[p] << endl;
    return 0;
}