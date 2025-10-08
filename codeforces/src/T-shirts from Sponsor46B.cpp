//
// Created by Psy.C on 2025/9/30.
//
/*
*参数a表示首选尺寸的索引
首先检查首选尺寸是否可用，如果可用则直接返回
否则按照接近程度顺序搜索（先搜索较大尺寸，再搜索较小尺寸）
返回找到的第一个可用尺寸的索引
 *
 */
#include <ios>
#include <iostream>
using namespace std;

int num[5];//存储每种T恤尺寸的数量
char T_shirts[5][5] = {"S", "M", "L", "XL", "XXL"};

int solve(int a) {
    int b = a;// 保存原始首选尺寸索引
    if (num[a]) return a;// 如果首选尺寸有库存，直接返回
    else {// 首选尺寸缺货，开始寻找替代品
        while (a < 5) {
            a++;// 向更大的尺寸方向搜索
            if (num[a]) return a;// 找到可用的大一号尺寸
            else if (b > 0) {
                b--;// 同时向更小的尺寸方向搜索
                if (num[b]) return b;// 找到可用的小一号尺寸
            }
        }
        while (b > 0) {// 如果向上搜索完还没找到，则继续向下搜索
            b--;
            if (num[b]) return b;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int k, t, x;
    char people[1010][5];
    while (cin >> num[0] >> num[1] >> num[2] >> num[3] >> num[4]) {
        cin >> k;
        for (int i = 0; i < k; ++i) cin >> people[i];
        for (int i = 0; i < k; ++i) {
            if (people[i][0] == 'S') t = 0;
            else if (people[i][0] == 'M') t = 1;
            else if (people[i][0] == 'L') t = 2;
            else if (people[i][0] == 'X' && people[i][1] == 'L') t = 3;
            else if (people[i][0] == 'X' && people[i][1] == 'X') t = 4;
            x = solve(t);
            num[x]--;//分配了一件该尺寸的T恤给当前用户，库存减1
            cout << T_shirts[x] << endl;
        }
    }

    return 0;
}