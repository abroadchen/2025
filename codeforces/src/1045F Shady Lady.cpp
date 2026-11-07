//
// Created by Psy.C on 2026/11/7.
//

/**
真正学会的起点..
每个节点：坐标 (x,y)、编号 num、标记 flg。
flg=1 或许表示"可作为有利点 / 特殊点"
按横坐标升序，相同则纵坐标升序 —— 用于 Andrew 凸包算法的坐标排序。
三点叉积，判断转向：>0 左转，<0 右转，=0 共线。
标准 Andrew 算法：先扫一遍得下凸壳，再反向扫得上凸壳，去掉首尾重复，返回凸包顶点数 top。<=0 表示舍去右转和共线点，保证凸包严格凸
遍历凸包上成对的点（每 2 个一组：i、i+1），把两组分别赋予 num=1 和 num=2。
p[1].num=0：将某固定点（下标1，即原点映射）的 num 置 0。
把 num != s 的点复制到数组 tp[1..k-1]，供下一次凸包计算使用。即剔除某类点后再求凸包
判断凸包顶点中是否存在 flg==0 的点（即不是"有利/特殊点"的点）。存在则返回 true

把原点 (0,0) 设为 1 号点（flg=1）。
读入其余点；坐标均为偶数（x%2==0 && y%2==0）的点标记 flg=1。
这暗示 flg=1 表示"偶偶点 / 有利点"，是分类的关键
先求全体点的凸包：
若凸包上有 flg==0 的点（非偶偶点）→ 输出 "Ani"。
剔除 num==1 的点后，对剩余点再求凸包并 check，若仍有非偶点 → Ani。
再剔除 num==2 的点后求凸包并 check，若仍有非偶点 → Ani；否则最终 "Borna"。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for (int i=j; i<=k; ++i)
#define per(i,n) for (int i=n; i; --i)
#define ll long long
using namespace std;

constexpr int N = 3e5+5;

struct node { ll x, y; int num; bool flg = 0; };
bool cmp(node a, node b) {
    if (a.x == b.x) return a.y < b.y;
    return a.x < b.x;
}
ll cross(node a, node b, node c) { return (b.x-a.x)*(c.y-a.y) - (b.y-a.y)*(c.x-a.x); }

int andrew(node p[], node ch[], ll n) {
    sort(p+1, p+n+1, cmp);
    ll top = 0;
    rep(i,1,n) {
        while (top > 1 && cross(ch[top-1],ch[top],p[i]) <= 0) --top;
        ch[++top] = p[i];
    }
    ll tmp = top;
    per(i,n-1) {
        while (top > tmp && cross(ch[top-1],ch[top],p[i]) <= 0) --top;
        ch[++top] = p[i];
    }
    if (n > 1) top--;
    return top;
}

map<pair<ll,ll>, int> mp;
void draw(int top, node ch[], node p[]) {
    rep(i,2,top) {
        p[mp[{ch[i].x,ch[i].y}]].num = 1; ++i;
        p[mp[{ch[i].x,ch[i].y}]].num = 2;
    }
    p[1].num = 0;
}

int k;
ll n;
node p[N], tp[N];
void preset(int s) {
    k = 1;
    rep(i,1,n) {
        if (p[i].num == s) continue;
        tp[k++] = p[i];
    }
}
bool check(int top, node ch[]) {
    rep(i,1,top) if (!ch[i].flg) return 1;
    return 0;
}

node ch[N];
int main() {
    fast;
    cin >> n; ++n; p[1].flg = 1; mp[{0,0}] = 1;
    rep(i,2,n) {
        cin >> p[i].x >> p[i].y;
        if (p[i].x == 0 && p[i].y == 0) { --i, --n; continue; }
        if (p[i].x%2 == 0 && p[i].y%2 == 0) p[i].flg = 1;
    }
    int top = andrew(p,ch,n);
    rep(i,1,n) mp[{p[i].x,p[i].y}] = i;
    draw(top,ch,p);
    if (check(top,ch)) { cout << "Ani\n"; return 0; }
    preset(1);
    top = andrew(tp,ch,k-1);
    if (check(top,ch)) { cout << "Ani\n"; return 0; }
    preset(2);
    top = andrew(tp,ch,k-1);
    if (check(top,ch)) { cout << "Ani\n"; return 0; }
    cout << "Borna\n";
    return 0;
}