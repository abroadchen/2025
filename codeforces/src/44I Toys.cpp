//
// Created by Psy.C on 2025/9/28.
//
/*
*seq: 二维向量，存储分组的序列
moved: 记录移动的元素
in: 记录每个元素所在的组索引
add(): 添加新元素到指定组的方法
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
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
#include <vector>
#include <algorithm>
#define sz(n) (int(n))
using namespace std;

struct Pos {
    vector<vector<int>> seq;
    int moved;
    vector<int> in;
    Pos add(int ind, int n, int newMoved) const {
        Pos res = *this;//复制当前对象
        res.moved = newMoved;
        if (ind < sz(res.seq.size())) res.seq[ind].push_back(n);//如果组索引有效，将元素n添加到指定组
        else res.seq.push_back({n});//否则创建新组并添加元素n
        res.in.push_back(ind);//记录新元素n所在的组索引
        return res;//返回新创建的位置对象
    }
};

vector<Pos> getNew(const vector<Pos>& old, int n) {//函数接收旧位置向量和新元素n，返回新位置向量
    vector<Pos> nw;
    for (int i = 0; i < sz(old.size()); ++i) {//遍历所有旧位置
        int my = sz(old[i].seq.size());// 初始化my为当前序列组数（作为默认放置位置）
        if (i) {//如果不是第一个位置
            int ind = nw.back().in[n];// 获取上一个位置中元素n的组索引
            for (auto& el : nw.back().seq[ind]) {//遍历该组中的所有元素
                if (el != n && el != old[i].moved) {//如果元素不是n且不是当前旧位置的moved元素
                    my = old[i].in[el];//更新my为该元素在当前旧位置中的组索引
                    break;
                }
            }
        }
        nw.push_back(old[i].add(my, n, old[i].moved));//使用计算出的my位置添加新元素
        for (int j = 0; j <= sz(old[i].seq.size()); ++j) {//遍历所有可能的组索引（包括创建新组）
            if (j != my) nw.push_back(old[i].add(j, n, n));//在位置j添加新元素，同时将moved设为n
        }
    }
    return nw;
}

void printVector(const vector<int>& res) {
    cout << "{";
    for (int i = 0; i < sz(res.size()); ++i) {
        cout << res[i] + 1 << (i + 1 < sz(res.size()) ? "," : "}");//输出元素值加1（因为内部存储从0开始，输出从1开始）
    }
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    vector<Pos> cur = {{{{0}}, 0, {0}}};
    int n; cin >> n;

    for (int i = 1; i < n; ++i) cur = getNew(cur, i);
    cout << cur.size() << '\n';
    reverse(cur.begin(), cur.end());
    for (auto& p : cur) {//遍历每个位置p
        for (int i = 0; i < sz(p.seq.size()); ++i) {//遍历该位置的所有组
            printVector(p.seq[i]);//打印组内容
            cout << (i + 1 < sz(p.seq.size()) ? "," : "\n");
        }
    }
    return 0;
}