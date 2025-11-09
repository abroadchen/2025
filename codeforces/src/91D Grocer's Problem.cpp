//
// Created by Psy.C on 2025/11/9.
//
/*
*bp(a,x)：从向量a中取出最后一个元素赋给x，并删除该元素
p(x)：从b[i]中取出最后一个元素赋给x
 *
*a[N]：存储输入的排列
f[N]：标记数组，记录哪些元素已被处理
b[N]：存储每个循环的元素
c2, c3：分别存储长度为2和3的循环索引
 *
*找循环节：
对每个未处理的元素i开始
跟踪置换循环：从j=i开始，沿着a[j]移动，直到回到已处理元素
标记访问过的元素，并将它们加入b[i]
 *
*处理长度大于4的循环：
反复取出5个元素
创建一个5元循环操作：(x,y,z,u,v) → (y,z,u,v,x)
将x重新放回循环中，继续处理
 *
*分类处理不同长度的循环：
长度2：加入c2列表
长度3：加入c3列表
长度4：转换为4元循环操作
 *
*处理剩余的长度2和3的循环：
当还有多个短循环时，将它们组合成更复杂的操作
混合2元和3元循环：组合成5元操作
两个3元循环：组合成5元操作，产生一个2元循环
两个2元循环：组合成4元操作
 *
*处理最后剩余的循环：
如果还有3元循环，直接处理
如果还有2元循环，直接处理
 *
 */
#include <vector>
#include <iostream>
#define rep(i,n) for(i=1;i<=(n);++i)
#define bp(a,x) x=a.back(),a.pop_back()
#define p(x) bp(b[i],x)
using namespace std;

typedef long long ll;
const ll N = 1e5+5;
ll n, i, j, a[N],
v, u, z, y, x;
bool f[N];
vector<ll> b[N], c2, c3;

struct Node { vector<ll> a, b; };
vector<Node> s;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin>>n;
    rep(i,n) cin>>a[i];
    rep(i,n) if (!f[i]) {
        for (j = i; !f[j]; j = a[j]) f[j] = 1, b[i].emplace_back(j);
        while (b[i].size() > 4) {
            p(v); p(u); p(z); p(y); p(x);
            s.emplace_back(Node{{x,y,z,u,v},{y,z,u,v,x}});
            b[i].emplace_back(x);
        }
        if (b[i].size() == 2) c2.emplace_back(i);
        if (b[i].size() == 3) c3.emplace_back(i);
        if (b[i].size() == 4) {
            p(u); p(z); p(y); p(x);
            s.emplace_back(Node{{x,y,z,u},{y,z,u,x}});
        }
    }
    while (c2.size() + c3.size() > 1) {
        if (c2.size() && c3.size()) {
            bp(c3,i); p(z); p(y); p(x); bp(c2,i); p(v); p(u);
            s.emplace_back(Node{{x,y,z,u,v},{y,z,x,v,u}});
        } else if (c3.size() > 1) {
            bp(c3,i); p(z); p(y); p(x); bp(c3,i); p(v); p(u);
            s.emplace_back(Node{{x,y,z,u,v},{y,z,x,v,u}});
            c2.emplace_back(i); b[i].emplace_back(u);
        } else if (c2.size() > 1) {
            bp(c2,i); p(y); p(x); bp(c2,i); p(v); p(u);
            s.emplace_back(Node{{x,y,u,v},{y,x,v,u}});
        }
    }
    if (c3.size()) {
        bp(c3,i); p(z); p(y); p(x);
        s.emplace_back(Node{{x,y,z},{y,z,x}});
    }
    if (c2.size()) {
        bp(c2,i); p(y); p(x);
        s.emplace_back(Node{{x,y},{y,x}});
    }
    cout << s.size() << '\n';
    for (Node& t : s) {
        cout << t.a.size() << '\n';
        for (ll x : t.a) cout << x << ' '; cout << '\n';
        for (ll x : t.b) cout << x << ' '; cout << '\n';
    }
    return 0;
}