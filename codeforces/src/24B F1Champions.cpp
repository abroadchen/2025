//
// Created by Psy.C on 2025/9/19.
//
/*
*首先按总分降序排列
如果总分相同，则按第一名次数降序排列
如果第一名次数也相同，则按第二名次数降序排列，以此类推
 *
 *
*首先按第一名次数降序排列
如果第一名次数相同，则按总分降序排列
如果总分也相同，则按第二名次数降序排列，以此类推
 *
 *
*n：比赛场次数量
m：每场比赛的参赛人数
z：不同选手总数
num[55]：名次对应的分数数组（第1名25分，第2名18分，...，第10名1分，其他名次0分）
s：临时存储选手姓名的字符串
mp：映射，用于快速查找选手是否已存在
 *
 *
*如果是新选手（mp[s]为0）：
增加选手计数z
初始化该选手的名次统计数组
记录选手姓名
更新该名次次数和总分
在映射中标记该选手已存在
如果是已存在的选手：
在数组中找到该选手
更新该名次次数和总分
 *
 *
 *
 *
 *
 *
 *
 */
#include <ios>
#include <iostream>
#include <map>
#include <string>
#include <cstring>
using namespace std;

struct Node {
    int score, r[55];
    string name;
} a[1005];

int cmp1(Node a, Node b) {
    if (a.score == b.score) {
        int w = 1;
        while (a.r[w] == b.r[w]) w++;
        return a.r[w] > b.r[w];
    }
    return a.score > b.score;
}

int cmp2(Node a, Node b) {
    if (a.r[1] == b.r[1]) {
        if (a.score == b.score) {
            int w = 2;
            while (a.r[w] == b.r[w]) w++;
            return a.r[w] > b.r[w];
        }
        return a.score > b.score;
    }
    return a.r[1] > b.r[1];
}


int n, m, z, num[55]={0, 25,18,15,12,10,8,6,4,2,1, 0};
string s;
map<string, int> mp;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    
    cin >> n;
    while (n--) {
        cin >> m;

        for (int i = 1; i <= m; ++i) {
            cin >> s;

            if (!mp[s]) {
                z++;
                memset(a[z].r, 0, sizeof(a[z].r));
                a[z].name = s;
                a[z].r[i]++;
                a[z].score += num[i];
                mp[s] = 1;
            } else {
                for (int j = 1; j <= z; ++j) {
                    if (s == a[j].name) {
                        a[j].r[i]++;
                        a[j].score += num[i];
                        break;
                    }
                }
            }
        }
    }

    sort(a + 1, a + z + 1, cmp1); cout << a[1].name << endl;
    sort(a + 1, a + z + 1, cmp2); cout << a[1].name;



    return 0;
}