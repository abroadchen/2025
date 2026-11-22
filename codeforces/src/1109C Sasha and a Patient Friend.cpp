//
// Created by Psy.C on 2026/11/22.
//

/**
真正学会的起点..
buf：2 亿字节的静态字符数组，当作内存池。
*pos：当前分配游标，指向池中下一个可用位置
*自定义内存池分配器。pos += sizeof(T) 先推进游标；new(pos-sizeof(T))T(args...) 在已预留位置用 placement new 构造对象。
返回构造成的对象指针。作用：避免频繁 malloc/free，加快动态开点
tr：线段树根指针，全局
l, r：当前区间范围。
mn：区间前缀和最小值（从 l 算起，每段高度 s、宽度段长的累计，取最小下沉点）。
sum：区间总长 r-l+1（当作"总深度"）。
lz：懒惰赋值标记，inf 表示无标记。
_ls, _rs：左右孩子指针
len() 返回区间长度；mid() 返回中点（左区间右边界用，注意右区间左边界是 mid()+1）
若左/右孩子不存在，用内存池 get 动态创建（区间分别为 [l,mid]、[mid+1,r]）。否则直接返回已有指针。
动态开点：只建访问过的区间，省内存。
sum = ls->sum + rs->sum：总长度 = 左 + 右。
mn：全局前缀和最小值 = min( 左子区间前缀和min, 左子总长度 + 右子区间前缀和min )。
即：要么最低点落在左半，要么走完左半后落到右半的最小处。
这是"漏斗水位"问题的关键递推
若当前节点有赋值标记 lz（非 inf），下传给左右孩子：
孩子 sum = lz * len()（每单位高度 lz、共 len 长）；
孩子 mn = min(0, lz*len())（若 lz<0，前缀和从 0 开始下降会先到负值，所以取 min(0, 负)；若 lz>0 则 mn=0）。
下传后清空自身标记 lz = inf
初始化区间边界、mn=0, sum=0、lz=inf（无标记）、孩子指针为 nullptr。
完全覆盖 [L,R]：直接设标记 lz=v，更新 mn = min(0, v*len())、sum = v*len()，返回。
否则先 push_down()（把旧标记下传，让孩子一致），再递归更新子区间，最后 push_up() 汇总
完全覆盖且当前 water v 加上此区间最低点 mn 仍 >0 → 水位没有触底，直接 v += sum 消耗整个区间高度，返回 -1（继续向右）。push_down 没调用但作为分支先判断。
l == r（叶子）：此时要么 sum>=0 返回 l（若当前段还能容纳），要么 l - v/sum 计算落点在段内的小数位置（把剩余体积 v 除以段高 sum，得到沿 x 轴的偏移）。
未完全覆盖或需继续：先 push_down 保证孩子状态正确，然后递归搜索左孩子、若左无结果再搜右孩子，返回首个落点坐标（-1 表示未触底）
q：操作数。
mp：有序 map，mp[t] = s，记录"每个分段起点 t 处的段高 s"。用 map 维护分段常数函数
创建根节点覆盖 [1, M]（1e9）。
mp[0]=0、mp[M+1]=0：哨兵，保证 map 边界（lower_bound/upper_bound 始终有兜底，且左边界高度 0）
读入起点 t、段高 s。记录 mp[t]=s。
更新线段树：把区间 [t, 下一个分段起点(排除)-1] 都赋成 s。因为从 t 到下一分段起点前，该段高度都是 s
删除分段 t。删除后从 t 起、到下一个分段起点前，应继承前一段的高度 prev(p)->second（即 t 的前一个分段起点的高度）。
用 p = mp.upper_bound(t) 找 t 后第一个起点，prev(p) 是 t 前最近起点，取其高度赋给 [t, p->first-1]
读入查询区间 [l,r] 和初始体积 v（double）。
若 v==0：直接输出 l（水位不动）。
p = mp.lower_bound(l)：找到 ≥ l 的第一个分段起点。
若该起点 > r（即 [l,r] 内没有分段起点）：输出 -1（无有效段可灌）。
否则调用 tr->qry(p->first, r, v) 求落点答案 ans（double）。若 ans > r 表示超出右边界，输出 -1；否则输出 ans
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

constexpr int N = 2e8, inf = 1e18, M = 1e9;
char buf[N], *pos = buf;
template<typename T, typename... Args>
T* get(Args&&... args) {
    pos += sizeof(T);
    return new(pos-sizeof(T))T(args...);
}

struct node {
    int l, r, mn, sum, lz; node *_ls, *_rs;
    int len() { return r-l+1; }
    int mid() { return (l+r)>>1; }
    node *ls() { return _ls ? _ls : _ls=get<node>(l,mid());}
    node *rs() { return _rs ? _rs : _rs=get<node>(mid()+1,r);}
    void push_up() {
        mn = min(ls()->mn, ls()->sum+rs()->mn);
        sum = ls()->sum + rs()->sum;
    }
    void push_down() {
        if (lz == inf) return;
        ls()->lz = lz; rs()->lz = lz;
        ls()->mn = min(0ll,lz*ls()->len()); ls()->sum = lz*ls()->len();
        rs()->mn = min(0ll,lz*rs()->len()); rs()->sum = lz*rs()->len();
        lz = inf;
    }
    node(int l, int r):l(l), r(r), mn(0), sum(0), lz(inf), _ls(nullptr), _rs(nullptr) {}
    void upd(int L, int R, int v) {
        if (L <= l && r <= R) { lz = v; mn = min(0ll,v*len()); sum = v*len(); return; }
        push_down();
        if (L <= mid()) ls()->upd(L,R,v);
        if (R > mid()) rs()->upd(L,R,v);
        push_up();
    }
    double qry(int L, int R, double &v) {
        if (L <= l && r <= R) {
            if (v+mn > 0) { v += sum; return -1; }
            if (l == r) {
                if (sum >= 0) return l;
                return l-v/sum;
            }
        }
        push_down();
        double res = -1;
        if (L <= mid()) res = ls()->qry(L,R,v);
        if (R > mid() && res == -1) res = rs()->qry(L,R,v);
        return res;
    }
} *tr;

int q;
map<int,int> mp;
signed main() {
    fast;
    cin >> q; tr = get<node>(1,M); mp[0] = 0; mp[M+1] = 0;
    for (int i = 1; i <= q; i++) {
        int op; cin >> op;
        if (op == 1) {
            int t, s; cin >> t >> s; mp[t] = s;
            tr->upd(t,mp.upper_bound(t)->first-1,s);
        } else if (op == 2) {
            int t; cin >> t; mp.erase(t);
            auto p = mp.upper_bound(t);
            tr->upd(t,p->first-1,prev(p)->second);
        } else if (op == 3) {
            int l, r; double v; cin >> l >> r >> v;
            if (v == 0) { cout << fixed << setprecision(7) << l << '\n'; continue; }
            auto p = mp.lower_bound(l);
            if (p->first > r) { cout << -1 << '\n'; continue; }
            double ans = tr->qry(p->first,r,v);
            cout << fixed << setprecision(7) << (ans>r?-1:ans) << '\n';
        }
    }
    return 0;
}