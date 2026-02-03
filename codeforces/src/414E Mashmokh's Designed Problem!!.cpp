//
// Created by Psy.C on 2026/2/3.
//
/**
* id：节点编号
dep：节点深度
mn：子树中最小深度
mx：子树中最大深度
laz：懒惰标记（延迟更新标记）
*l：左子节点指针
r：右子节点指针
fa：父节点指针
*laz += x：懒惰标记累加 x
mn -= x：最小深度减少 x
mx -= x：最大深度减少 x
dep -= x：当前节点深度减少 x
 *
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 200010
using namespace std;


struct node {
    int id, dep, mn, mx, laz;
    node *l, *r, *fa;
    node(const int id, const int dep, node *fa) : id(id), dep(dep), mn(dep), mx(dep), laz(0),
        l(nullptr), r(nullptr), fa(fa) {}
    void update(const int x) { laz += x; mn -= x; mx -= x; dep -= x; }
    void pushdown() {
        if (!laz) return;//没有懒惰标记
        if (l) l->update(laz);//有左子节点
        if (r) r->update(laz);
        laz = 0;//清空当前节点的懒惰标记
    }
    void check() {
        mn = mx = dep;//当前节点深度
        if (l) mn = min(mn, l->mn), mx = max(mx, l->mx);//存在左子节点，更新最值
        if (r) mn = min(mn, r->mn), mx = max(mx, r->mx);
    }
    node *find(const int x) {//查找深度为 x 的节点
        pushdown();
        //右子树包含深度x，递归查找右子树
        if (r && r->mn <= x && r->mx >= x) return r->find(x);
        if (dep == x) return this;//当前节点深度等于x，返回当前节点
        return l->find(x);//递归查找左子树
    }
} *rt(nullptr);//根节点指针

void rotate(node *x) {//Splay树的旋转操作
    node *fa = x->fa, *g = fa->fa;//获取父节点和祖父节点
    if (fa->l == x) {//x 是左子节点，执行右旋
        fa->l = x->r;//将fa的左子节点改为x的右子节点
        //x是否有右子节点
        if (x->r) x->r->fa = fa;//将原来x的右子节点的父指针指向fa
        x->r = fa;//将fa设置为x的右子节点
    } else {
        fa->r = x->l;
        if (x->l) x->l->fa = fa;
        x->l = fa;
    }
    //重新连接父节点：更新祖父节点与旋转后的节点的连接
    fa->fa = x; x->fa = g;
    if (g && g->l == fa) g->l = x;
    if (g && g->r == fa) g->r = x;
    fa->check(); x->check();//更新两个节点的最值信息
}

#define f(x) (x->fa->l==x)//节点 x 是否为其父节点的左子节点
void splay(node *x, const node *to=nullptr) {//将节点 x 旋转到 to 的下方
    static node *st[N];//静态栈，用于保存路径上的节点
    int t = 0; st[++t] = x;//将节点 x 入栈
    const node *xx = x;
    while (xx->fa != to) xx = st[++t] = xx->fa;//将从 x 到 to 的路径上的所有节点入栈
    while (t) st[t--]->pushdown();
    //双旋操作：使用 zig-zag 和 zig-zig 操作进行 Splay
    while (x->fa != to) {
        if (x->fa->fa != to && f(x) == f(x->fa)) rotate(x->fa);
        rotate(x);
    }
    if (to == nullptr) rt = x;//更新根节点
}

node *add(const int id, const int dep) {//在Splay树中添加新节点
    if (rt == nullptr) return rt = new node(id, dep, nullptr);//创建根节点
    node *p = rt;
    while (p->r) p = p->r;//找到最右边的节点
    p->r = new node(id, dep, p);//在最右节点的右子树添加新节点
    splay(p->r);//将新节点旋转到根部
    return rt;//返回根节点
}

node *get_pre(node *x) {//获取节点 x 的前驱节点（中序遍历的前一个节点）
    splay(x); x = x->l;
    while (x->r) x = x->r;
    return x;
}


node *get_nxt(node *x) {
    splay(x); x = x->r;
    while (x->l) x = x->l;
    return x;
}

//获取区间 [x, y]，将该区间放在树的根的右子树的左子树位置
void get_seg(node *x, node *y) {
    node *xx = get_pre(x), *yy = get_nxt(y);
    splay(xx); splay(yy, xx);
}

vector<int> e[N];
node *in[N], *out[N];//每个节点的进入和退出节点指针
void dfs(const int x, const int dep) {//为每个节点创建进入和退出节点
    in[x] = add(x, dep);
    for (const int y : e[x]) dfs(y, dep + 1);
    out[x] = add(x, dep);
}


int main() {
    fast;
    int n, q; cin >> n >> q;
    for (int i = 1, k, x; i <= n; ++i) {
        cin >> k;
        while (k--) {
            cin >> x;
            e[i].push_back(x);
        }
    }
    //在DFS前后添加哨兵节点
    add(-1, -1); dfs(1, 0); add(-1, -1);
    for (int i = 1, op, x, y; i <= q; ++i) {
        cin >> op >> x;
        if (op == 1) {
            cin >> y;
            //查询的两个节点是否相同
            if (x == y) { cout << "0\n"; continue; }//两个相同节点的距离为0
            //节点x在Splay树中的进入节点（DFS序中第一次访问该节点的时刻）
            node *p1 = in[x], *p2 = in[y];
            //将p1节点旋转到树根
            splay(p1); splay(p2, p1);//将p2节点旋转到p1节点下方
            //确保p1在p2左边（在DFS序中p1的时间戳小于p2）
            if (p1->l == p2) swap(p1, p2);
            get_seg(get_nxt(p1), p2);//获取从p1后继到p2的区间
            const int lca = rt->r->l->mn - 1;
            cout << in[x]->dep+in[y]->dep-2*lca << '\n';
        } else if (op == 2) {
            cin >> y; get_seg(in[1], in[x]);//从根节点到x的区间
            //节点x的深度减去y，即目标深度 在刚才获取的区间中查找指定深度的节点 将找到的节点赋值给p
            node *p = rt->r->l->find(in[x]->dep-y); p = out[p->id];//获取该节点的退出节点（DFS序中最后一次访问该节点的时刻）
            get_seg(in[x], out[x]);//获取节点x的子树区间（在DFS序中，子树的所有节点都在进入和退出之间）
            //获取刚才提取的子树区间
            node *now = rt->r->l; now->update(y - 1);//将子树中所有节点的深度减少y-1（相当于将整个子树向上移动）
            //将子树从Splay树中分离出来
            if (now->fa->l == now) now->fa->l = nullptr; else now->fa->r = nullptr;
            //更新原父节点的最值信息（因为子树已被移除）
            now->fa->check(); now->fa = nullptr;//完全断开now与其原父节点的连接
            //获取节点p的区间（单个节点）
            get_seg(p, p); p->pushdown();//将p节点的懒惰标记下传给子节点
            //将分离出来的子树作为p节点的左子树 设置now的新父节点为p 将now节点旋转到根位置
            p->l = now; now->fa = p; splay(now);
        } else cout << rt->find(x)->id << '\n';//在根节点rt中查找深度为x的节点
    }
    return 0;
}