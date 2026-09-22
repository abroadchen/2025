//
// Created by Psy.C on 2026/9/22.
//
/**
(x, y) 起点、(x2, y2) 终点、(a, b) 每步的横纵增量。
横向要想到达，|x-x2| 必须能被 a 整除；纵向同理要能被 b 整除。
flag=1 默认"不行"，只有通过了才会被改成 0。
若任一方向不能整除，直接 flag 保持 1，最后输出 NO。
t1 = |x-x2|/a：横向需要的步数；t2 = |y-y2|/b：纵向需要的步数。
之所以要"奇偶一致"：每次移动横纵同时各走一步，所以整个过程中横向总步数 = 纵向总步数。若 t1、t2 奇偶不同，就永远没法用相同步数同时满足两个方向。
等价写法 abs(t1-t2)%2==0（两数之差为偶 ⇔ 二者同奇偶）。仅在通过时输出 YES 并把 flag 置 0
若前面没输出 YES（flag 仍为 1），输出 NO。最终只输出一个答案。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int x, y, x2, y2, a, b;
    cin >> x >> y >> x2 >> y2 >> a >> b;
    int flag = 1;
    if (abs(x-x2)%a == 0 && abs(y-y2)%b == 0) {
        int t1 = abs(x-x2)/a, t2 = abs(y-y2)/b;
        if (abs(t1-t2)%2 == 0) {
            cout << "YES";
            flag = 0;
        }
    }
    if (flag == 1) cout << "NO";
    return 0;
}