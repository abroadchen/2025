use std::io;
#[derive(Clone)]
struct Edge { u: i32, v: i32 }//边的两个端点
struct UnionFind { fa: Vec<usize>, cnt: usize, n: usize }//父节点数组 连通分量的个数 节点总数
impl UnionFind {
    fn new(n: usize) -> Self {
        let mut fa = vec![0; n+1];//索引0不使用
        for i in 1..=n { fa[i] = i; }
        Self { fa, cnt: n, n }//返回初始化的UnionFind实例
    }
    fn find(&mut self, x: usize) -> usize {
        if self.fa[x] == x { x } else {
            self.fa[x] = self.find(self.fa[x]);//将路径上所有节点直接连到根
            self.fa[x]
        }
    }
    fn union(&mut self, x: usize, y: usize) -> bool {
        let rx = self.find(x);//x所在集合的根
        let ry = self.find(y);
        if rx != ry {
            self.fa[rx] = ry;//将x的根连接到y的根下
            self.cnt -= 1;
            true//成功合并
        } else { false }//已在同一集合
    }
    fn reset(&mut self) {
        for i in 1..=self.n { self.fa[i] = i; }
        self.cnt = self.n;
    }
}

fn main() {
    let stdin = io::stdin();
    let mut input = String::new();
    stdin.read_line(&mut input).unwrap();
    let parts: Vec<i32> = input.trim().split_whitespace()
        .map(|x| x.parse().unwrap()).collect();
    let n = parts[0] as usize;
    let m = parts[1] as usize;
    let mut e = vec![Edge { u: 0, v: 0 }; m + 1];//边数组
    for i in 1..=m {
        input.clear();
        stdin.read_line(&mut input).unwrap();
        let parts: Vec<i32> = input.trim().split_whitespace()
            .map(|x| x.parse().unwrap()).collect();
        e[i].u = parts[0];//边的起点
        e[i].v = parts[1];//边的终点
    }
    let mut u = UnionFind::new(n);
    let mut t1 = Vec::new();//存储从左到右的有用边索引
    for i in 1..=m {
        if u.union(e[i].u as usize, e[i].v as usize) { t1.push(i); }//如果合并成功
    }
    u.reset();
    let mut t2 = Vec::new();
    for i in (1..=m).rev() {
        if u.union(e[i].u as usize, e[i].v as usize) { t2.push(i); }
    }
    t2.reverse();//反转数组，使其按升序排列
    input.clear();
    stdin.read_line(&mut input).unwrap();
    let q = input.trim().parse::<i32>().unwrap();
    for _ in 0..q {
        input.clear();
        stdin.read_line(&mut input).unwrap();
        let parts: Vec<i32> = input.trim().split_whitespace()
            .map(|x| x.parse().unwrap()).collect();
        let l = parts[0] as usize;//查询区间左端点
        let r = parts[1] as usize;
        u.reset();//每次查询都重置并查集
        for &i in &t1 {
            //如果边索引小于查询左边界 合并这条边 超出范围则跳出
            if i < l { u.union(e[i].u as usize, e[i].v as usize); } else { break; }
        }
        for &i in t2.iter().rev() {//逆序遍历从右到左的有用边
            if i > r { u.union(e[i].u as usize, e[i].v as usize); } else { break; }
        }
        println!("{}", u.cnt);
    }
}