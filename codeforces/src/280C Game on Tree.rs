/**
x: 当前访问的节点
f: 父节点
g: 图的邻接表表示（引用）
dep: 深度数组（可变引用）
遍历当前节点 x 的所有邻居节点
&g[x] 获取节点 x 的邻接表
&y 中的 & 表示解引用，y 是邻居节点的值（不是引用）

读取边并构建图
循环 n-1 次（树有n-1条边）
读取每条边的两个端点
split_whitespace() 按空白字符分割
map(|s| s.parse().unwrap()) 将每个部分解析为数字
collect() 收集为向量
添加双向边到邻接表

g[x] 是 Vec<usize> 类型（一个整数向量）
&g[x] 是 &Vec<usize> 类型（对向量的引用）
当你对 &Vec<usize> 进行迭代时，迭代器产生的是 &usize 类型（整数的引用）
所以正常的循环应该是：for y in &g[x]，这时 y 的类型是 &usize

*/
use std::io;

fn dfs(x: usize, f: usize, g: &Vec<Vec<usize>>, dep: &mut Vec<f64>) {
    for &y in &g[x] {
        if y != f {
            dep[y] = dep[x] + 1.;
            dfs(y, x, g, dep);
        }
    }
}

fn main() {
    let mut input = String::new();//读取节点数
    io::stdin().read_line(&mut input).unwrap();
    let n: usize = input.trim().parse().unwrap();
    let mut g = vec![Vec::new(); n + 1];//索引从0到n
    for _ in 0..n - 1 {
        let mut input = String::new();
        io::stdin().read_line(&mut input).unwrap();
        let parts: Vec<usize> = input.trim().split_whitespace()
            .map(|s| s.parse().unwrap()).collect();
        let u = parts[0];
        let v = parts[1];
        g[u].push(v); g[v].push(u);
    }
    let mut dep = vec![0.; n + 1]; dep[1] = 1.;//根节点1的深度为1.
    dfs(1, 0, &g, &mut dep);//父节点设为0（虚拟父节点）
    let mut ans = 0.;
    for i in 1..=n { ans += 1. / dep[i]; }
    println!("{:.7}", ans);
}