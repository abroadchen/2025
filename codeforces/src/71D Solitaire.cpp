//
// Created by Psy.C on 2025/11/3.
//
/*
*定义牌面等级数组，包含数字2-9和字母T(10), J(Jack), Q(Queen), K(King), A(Ace)
定义花色数组，包含C(Clubs梅花), D(Diamonds方块), H(Hearts红桃), S(Spades黑桃)
 *
*定义函数build，用于生成所有52张标准扑克牌
创建一个set容器存储牌面
遍历所有等级和花色的组合，生成如"2C", "3D"等牌面字符串并插入集合
 *
*定义read函数，读取输入数据并返回网格维度
读取网格行数n和列数m
调整grid大小为n行m列
逐行逐列读取卡片数据
返回网格尺寸{n, m}
 *
*定义fju函数，查找鬼牌位置和已使用的标准牌
创建map存储鬼牌("J1","J2")及其位置
创建set存储已使用的标准牌
*遍历整个网格
如果是鬼牌J1或J2，记录其位置到jokers映射中
如果是标准牌，添加到used集合中
返回鬼牌位置映射和已用标准牌集合
 *
*定义check函数，检查以(r,c)为左上角的3x3方格是否有效
收集3x3方格内的所有卡片
如果包含鬼牌则返回false（替换后不应有鬼牌）
 *必须恰好有9张牌才算完整的3x3方格
 *检查是否所有牌花色相同：提取每张牌的花色(第二个字符)放入集合，如果集合大小为1则满足条件
 *检查是否所有牌等级不同：提取每张牌的等级(第一个字符)放入集合，如果集合大小为9则满足条件
 *
*定义find函数，找出所有有效的3x3方格
遍历所有可能的3x3方格左上角位置
调用check检查是否有效
将有效方格的左上角坐标(转为1基索引)存入结果向量
 *
*定义f2nl函数，寻找两个不重叠的有效方格
获取所有有效方格位置
*双重循环比较每对方格
判断是否不重叠：行或列间距大于2
如果找到不重叠的方格对，返回它们的位置
如果没找到，返回特殊值表示无解
 *
*定义get函数，获取未使用的标准牌
遍历所有标准牌，找出未被使用的牌
对结果排序后返回
 *
 *
*处理没有鬼牌的情况：
直接查找两个不重叠的有效方格
如果找到解则输出相关信息
否则输出"No solution"
 *
*处理只有一个鬼牌的情况（异或运算确保只有一个）
确定是哪个鬼牌以及它的位置
 *
*尝试用每张剩余的标准牌替换鬼牌
每次替换后检查是否存在解
如果找到解则输出相关信息
否则恢复原状继续尝试下一张牌
如果所有尝试都失败，输出"No solution"
 *
*处理两个鬼牌都存在的情况
获取两个鬼牌的位置
 *如果剩余可用牌少于2张，无法替换两个鬼牌，直接返回无解
*双重循环生成所有两张不同牌的排列组合
确保两张牌不相同
 *将第一张牌替换J1，第二张牌替换J2
*检查是否存在解
如果找到解则输出相关信息
 *恢复原来的鬼牌状态，继续尝试其他组合
 */
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
using namespace std;

typedef pair<int, int> pii;
typedef vector<vector<string>> vvs;
typedef vector<string> vs;
const vs
ranks = {
    "2", "3", "4", "5", "6",
    "7", "8", "9", "T", "J",
    "Q", "K", "A"
},
suits = { "C", "D", "H", "S" };

set<string> build() {
    set<string> standard;
    for (const string& r : ranks) {
        for (const string& s : suits) {
            standard.insert(r + s);
        }
    }
    return standard;
}
const set<string> STANDARD = build();

vvs grid;
pii read(vvs& grid) {
    int n, m; cin >> n >> m;
    grid.assign(n, vs(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> grid[i][j];
        }
    }
    return {n, m};
}

pair<map<string, pii>, set<string>> fju(const vvs& grid, int n, int m) {
    map<string, pii> jokers;
    set<string> used;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            const string& card = grid[i][j];
            if (card == "J1" || card == "J2") jokers[card] = {i, j};
            else used.insert(card);
        }
    }
    return {jokers, used};
}

vs get(const set<string>& used) {
    vs remaining;
    for (const string& card : STANDARD) {
        if (used.find(card) == used.end()) {
            remaining.push_back(card);
        }
    }
    sort(remaining.begin(), remaining.end());
    return remaining;
}

bool check(const vvs& grid, int r, int c, int n, int m) {
    vs cards;
    for (int i = r; i < r + 3 && i < n; ++i) {
        for (int j = c; j < c + 3 && j < m; ++j) {
            const string& card = grid[i][j];
            if (card == "J1" || card == "J2") return false;
            cards.push_back(card);
        }
    }
    if (cards.size() != 9) return false;
    set<char> suitsIn;
    for (const string& card : cards) {
        suitsIn.insert(card[1]);
    }
    if (suitsIn.size() == 1) return true;
    set<char> ranksIn;
    for (const string& card : cards) {
        ranksIn.insert(card[0]);
    }
    if (ranksIn.size() == 9) return true;
    return false;
}



vector<pii> find(const vvs& grid, int n, int m) {
    vector<pii> pos;
    for (int r = 0; r <= n - 3; ++r) {
        for (int c = 0; c <= m - 3; ++c) {
            if (check(grid, r, c, n, m)) {
                pos.push_back({r + 1, c + 1});
            }
        }
    }
    return pos;
}


pair<pii, pii> f2nl(const vvs& grid, int n, int m) {
    vector<pii> pos = find(grid, n, m);
    int l = pos.size();
    for (int i = 0; i < l; ++i) {
        int r1 = pos[i].first, c1 = pos[i].second;
        for (int j = i + 1; j < l; ++j) {
            int r2 = pos[j].first, c2 = pos[j].second;
            if (r1 + 2 < r2 || r2 + 2 < r1 ||
                c1 + 2 < c2 || c2 + 2 < c1) {
                return {pos[i], pos[j]};
            }
        }
    }
    return {{-1, -1}, {-1, -1}};
}


int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    auto [n, m] = read(grid);
    auto [jokers, used] = fju(grid, n, m);
    vs remaining = get(used);

    if (jokers.find("J1") == jokers.end() &&
        jokers.find("J2") == jokers.end()) {
        auto res = f2nl(grid, n, m);
        if (res.first.first != -1) {
            auto [s1, s2] = res;
            cout << "Solution exists.\n";
            cout << "There are no jokers.\n";
            cout << "Put the first square to (" << s1.first << ", " << s1.second << ").\n";
            cout << "Put the second square to (" << s2.first << ", " << s2.second << ").\n";
            return 0;
        } else {
            cout << "No solution.\n";
            return 0;
        }
    }

    if ((jokers.find("J1") != jokers.end()) ^
        (jokers.find("J2") != jokers.end())) {
        string label = (jokers.find("J1") != jokers.end()) ? "J1" : "J2";
        auto [r, c] = jokers[label];
        for (const string& card : remaining) {
            grid[r][c] = card;
            auto res = f2nl(grid, n, m);
            if (res.first.first != -1) {
                auto [s1, s2] = res;
                cout << "Solution exists.\n";
                cout << "Replace " << label << " with " << card << ".\n";
                cout << "Put the first square to (" << s1.first << ", " << s1.second << ").\n";
                cout << "Put the second square to (" << s2.first << ", " << s2.second << ").\n";
                return 0;
            }
            grid[r][c] = label;
        }
        cout << "No solution.\n";
        return 0;
    }

    auto [r1, c1] = jokers["J1"];
    auto [r2, c2] = jokers["J2"];
    if (remaining.size() < 2) {
        cout << "No solution.\n";
        return 0;
    }

    for (size_t i = 0; i < remaining.size(); ++i) {
        for (size_t j = 0; j < remaining.size(); ++j) {
            if (i != j) {
                string a = remaining[i], b = remaining[j];
                grid[r1][c1] = a;
                grid[r2][c2] = b;
                auto res = f2nl(grid, n, m);
                if (res.first.first != -1) {
                    auto [s1, s2] = res;
                    cout << "Solution exists.\n";
                    cout << "Replace J1 with " << a << " and J2 with " << b << ".\n";
                    cout << "Put the first square to (" << s1.first << ", " << s1.second << ").\n";
                    cout << "Put the second square to (" << s2.first << ", " << s2.second << ").\n";
                    return 0;
                }
                grid[r1][c1] = "J1";
                grid[r2][c2] = "J2";
            }
        }
    }
    cout << "No solution.\n";
    return 0;
}