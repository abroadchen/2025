//
// Created by Psy.C on 2026/11/7.
//

/**
真正学会的起点..
cross(a,b,c) 判断从 a→b→c 的转向：>0 左转（逆时针），<0 右转，=0 共线。
dist 用平方距离（避免开根号）
按纵坐标升序，相同则横坐标升序 —— 用于找一个"最低点"作为凸包起点。
以 O 为基准，按极角排序；极角相同则距离近的在前（Andrew 算法的预处理）
标准 Graham：找最低点作 O，其余按极角排序，维护栈，遇到右转或共线（叉积≤0）‍就 pop，最终栈内为逆时针的凸包顶点。
con = 凸包顶点序列
check_inside 用面积法判断 P 是否在三角形 ABC 内部（严格内部，边界/顶点不算）

这是三角剖分+颜色隔离的核心：给定三角形 ABC 及其中点集 S。
若 S 中所有点都和 A 同色，则只需把 A 连到每个点，保证"不会把异色点连在一起造成跨越"。
若存在一个与 A 异色的点 p（取第一个），先连 C - p，再把三角形沿 A-p、C-p 分成 3 个子三角形分别递归。
目的是：每次把三角形二分，逐步把两种颜色"隔离"到边上，避免出现"不同色点之间的非法连接"

沿凸包环走一圈，统计颜色变化次数（相邻两点异色则计 1，首尾也算首尾）。
因为要让不同色两两可被同色路径"分隔"，若凸包上颜色交替超过 2 段（即 >2 次颜色切换），则无法构造 → Impossible。
凸包上颜色全一致时：
若所有点同色，直接用星形连接到 0 号（0 表示点编号？这里输出 0,i，连到首个点）即可。
否则选一个内部异色点 mid 作锚，把凸包每对相邻边与 mid 组成三角形，分别 solve。
con[0]、con.back()（首尾）与 mid 也形成一个三角形处理。
因为凸包上只有 2 段颜色，把它重排为"先一段颜色A、再一段颜色B"的两段式排列，方便后续处理
处理两色各成块的凸包：
把交界处 b 附近不同色的两个点设为不连（跳过，避免跨色）。
对两段分别以对面的那个异色锚点（con[b] 和 con[0]）做三角剖分 solve。
这样保证剖分出的所有三角形内部要么单色、要么由锚点隔离，实现颜色正确分离
ans 存的是所有应连的边对（同色节点对），fst-1, snd-1 把 1 起始的 id 转成 0 起始输出。
ans.emplace_back(con[i].id, con[i+1].id) 存的边，输出的就是这些同色对的连接方案。


求凸包：convex 给出外轮廓顶点。
判定可行性：统计凸包上的颜色段数 cnt：
cnt>2 → 无法构造，输出 Impossible。
cnt==0 → 凸包全同色，星形连接 or 用异色锚点三角剖分。
cnt==2 → 凸包两种颜色各占一段，重排后分两段三角剖分。
核心 solve：对任意三角形递归，内部若全与 A 同色则星形连 A；否则找异色点 p，连 C-p 并沿 Ap、Cp 剖成 3 个子三角形，递归到每个子三角形里，从而把两种颜色完全隔开（不同色点永不直接相连，或由剖分保证不跨越）。
关键点：

用凸包 + 三角剖分把平面点集凸包内部所有点归类到若干三角形里，三角形的顶点要么单色、要么由锚点分割，最终连边全在同色点之间。
每个点（node）的 id 用于输出边的两端点（0 起始）。
cross <= 0 的弹出保证凸包严格凸且逆时针。
*/
#include <bits/stdc++.h>
#define ii pair<int, int>
using namespace std;

constexpr int N = 1005;

struct Point {
    int x, y;
    Point() = default;
    Point(int a, int b) : x(a), y(b) {}
    friend Point operator+(const Point& a, const Point& b) { return {a.x+b.x, a.y+b.y}; }
    friend Point operator-(const Point& a, const Point& b) { return {a.x-b.x, a.y-b.y}; }
    friend bool operator==(const Point& a, const Point& b) { return a.x == b.x && a.y == b.y; }
    friend bool operator!=(const Point& a, const Point& b) { return a.x != b.x || a.y != b.y; }
} O;
int cross(Point a, Point b) { return a.x*b.y - a.y*b.x; }
int cross(Point a, Point b, Point c) { return cross(b-a, c-a); }
int dot(Point a, Point b) { return a.x*b.x + a.y*b.y; }
int dist(Point a, Point b) { return dot(a-b, a-b); }

struct node {//坐标、颜色、编号
    Point p; int c, id;
    node() = default;
    node(Point p, int c, int id) : p(p), c(c), id(id) {}
};

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

node get(int id) {//读入一个点
    Point p{}; p.x = rd(), p.y = rd();
    int c = rd();
    return {p,c,id};
}

bool cmp(Point a, Point b) { return a.y != b.y ? a.y < b.y : a.x < b.x; }
bool cmp2(node a, node b) {
    int c = cross(O, a.p, b.p);
    return c ? c > 0 : dist(O, a.p) < dist(O, b.p);
}

vector<node> convex(vector<node> p) {
    vector<node> st(0);
    int n = p.size();
    for (int i = 1; i < n; i++)
        if (!cmp(p[0].p, p[i].p))
            swap(p[0], p[i]);
    O = p[0].p;
    sort(p.begin()+1, p.end(), cmp2);
    for (int i = 0; i < n; i++) {
        while (st.size() > 1 && cross(st[st.size()-2].p, st.back().p, p[i].p) <= 0)
            st.pop_back();
        st.push_back(p[i]);
    }
    return st;
}

int n;
vector<node> p;
int check_same() {//所有点是否同色（与首个颜色比）
    for (int i = 1; i < n; i++)
        if (p[i].c != p[0].c)
            return 0;
    return 1;
}
int check_inside(Point A, Point B, Point C, Point P) {
    if (P==A||P==B||P==C) return 0;
    int S1=abs(cross(A,B,C));//大三角形面积(2倍)
    int S2=abs(cross(P,A,B))+abs(cross(P,B,C))+abs(cross(P,C,A));//三个小三角形面积和
    return S1==S2;
}

//取出点集 S 中落在三角形 ABC 内的全部点
vector<node> get_inside(Point A, Point B, Point C, vector<node> S) {
    static vector <node> res; res.clear();
    for (auto v : S)
        if (check_inside(A,B,C,v.p))
            res.push_back(v);
    return res;
}

vector<ii> ans;
void solve(node A, node B, node C, vector<node> S) {
    int flag=0; node p{};
    for (auto c : S)
        if (c.c!=A.c){//找三角形内颜色与 A 不同的点
            flag=1,p=c;
            break;
        }
    if (!flag){//三角形内全部与 A 同色
        for (auto c : S)//把 A 连到内部所有点
            ans.emplace_back(A.id,c.id);
        return;
    }
    ans.emplace_back(C.id,p.id);//连 C 到该异色点
    solve(A,B,p,get_inside(A.p,B.p,p.p,S));//递归分割子三角形 ABp
    solve(C,p,A,get_inside(C.p,p.p,A.p,S));
    solve(C,p,B,get_inside(C.p,p.p,B.p,S));
}

vector<node> con;
int main() {
    n = rd();
    for (int i=1;i<=n;i++) p.push_back(get(i));
    con=convex(p);//求凸包
    int cnt=con[0].c^con.back().c;//首尾颜色不同则+1
    for (int i=1;i<con.size();i++) cnt+=con[i-1].c^con[i].c;//相邻异色+1
    if (cnt>2) return puts("Impossible"),0;
    ans.clear();
    if (cnt==0){
        if (check_same()){//全部点都同色
            printf("%d\n",n-1);
            for (int i=1;i<n;i++) printf("%d %d\n",0,i);
            return 0;
        }
        for (int i=1;i<con.size();i++) ans.emplace_back(con[i-1].id,con[i].id);//连凸包边
        node mid{};//找一个与凸包颜色不同的内部点作为锚点
        for (auto c : p)
            if (c.c!=con[0].c){
                mid=c;
                break;
            }
        solve(con[0],con.back(),mid,get_inside(con[0].p,con.back().p,mid.p,p));//处理含 mid 的三角形
        for (int i=1;i<con.size();i++)
            solve(con[i-1],con[i],mid,get_inside(con[i-1].p,con[i].p,mid.p,p));//每个凸包边与 mid 组成三角形
    }
    else {
        vector <node> _con(0);
        int stco=con[0].c^1,i;//从凸包上第一种颜色的"对立色"开始抓取连续段
        int m=con.size();
        for (i=0;;i=(i+1)%m)
            if (con[i].c==stco){
                _con.push_back(con[i]);
                if (con[(i+1)%m].c!=stco) break;// 连续同色段结束
            }
        stco^=1;//换到另一颜色
        for (i=(i+1)%m;;i=(i+1)%m)
            if (con[i].c==stco){
                _con.push_back(con[i]);
                if (con[(i+1)%m].c!=stco) break;
            }
        con=_con;//重新排列凸包：现在两段颜色各聚成连续块
        for (i=0;i<m;i++)
            if (con[i].c!=con[(i+1)%m].c) break;//找到两色交界处 b
        int b=i;
        for (i=0;i<b;i++) ans.emplace_back(con[i].id,con[i+1].id);//连前半段同色凸包边
        for (i=b+1;i<m-1;i++) ans.emplace_back(con[i].id,con[i+1].id);//连两边界之后的同色边
        b++;
        //b之前的边，以 con[b]为锚
        for (i=0;i<b-1;i++)solve(con[i],con[i+1],con[b],get_inside(con[i].p,con[i+1].p,con[b].p,p));
        //b之后的边，以 con[0]为锚
        for (i=b;i<m-1;i++)solve(con[i],con[i+1],con[0],get_inside(con[i].p,con[i+1].p,con[0].p,p));
    }
    printf("%d\n",(int)ans.size());
    for (auto [fst, snd] : ans) printf("%d %d\n",fst-1,snd-1);
    return 0;
}