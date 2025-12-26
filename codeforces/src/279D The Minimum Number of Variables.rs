/**
读取 n
创建一个可变的字符串变量 input，用于存储用户输入
从标准输入读取一行到 input 变量中
读取数组 a
创建新的字符串变量存储数组数据
读取包含数组元素的一行

f: 动态规划数组，f[mask] 表示使用掩码 mask 中的元素的最小操作数
g: 辅助动态规划数组
vis: 访问标记数组
1 << n 等于 2^n，表示所有可能的子集

f[1] = 1，表示只使用第一个元素需要1次操作
从第二个元素开始遍历到第 n 个元素
重置辅助数组 g 和 vis 为初始状态
寻找所有满足 a[j] + a[k] = a[i] 的配对 (j, k)
将所有满足条件的配对存储在 vec 中
如果没有找到任何满足条件的配对，说明无法构造

遍历所有满足条件的配对 (u, v)
遍历所有包含前 i 个元素的子集 s
vis[s] 避免重复处理
(s >> u) & 1 == 0 检查子集 s 是否包含元素 u
(s >> v) & 1 == 0 检查子集 s 是否包含元素 v
标记状态 s 已访问
s | (1 << i) 将第 i 位设为1（加入元素 i）
状态转移：使用 s 中的元素构造 a[i]，操作数为 f[s] + 1
遍历子集 s 中的每个元素 j
(s >> j) & 1 == 0 检查元素 j 是否在子集 s 中
s ^ (1 << i) ^ (1 << j) 将第 i 位和第 j 位翻转
状态转移：从 f[s] 转移到新状态
交换 f 和 g 数组，为下一轮迭代准备

f.iter().min() 找到 f 数组中的最小值
unwrap() 解包 Option 类型
*/
use std::io;

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let n: usize = input.trim().parse().unwrap();
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let a: Vec<i32> = input.trim().split_whitespace()
        .map(|s| s.parse().unwrap()).collect();
    const INF: i32 = 0x3fffffff;
    let mut f = vec![INF; 1<<n];
    let mut g = vec![INF; 1<<n];
    let mut vis = vec![false; 1<<n]; f[1] = 1;
    for i in 1..n {
        g.fill(INF);vis.fill(false);
        let mut vec = Vec::new();
        for j in 0..i {
            for k in j..i {
                if a[j] + a[k] == a[i] { vec.push((j, k)) }
            }
        }
        if vec.is_empty() { println!("-1"); return; }
        for p in &vec {
            let u = p.0;
            let v = p.1;
            for s in 1..(1<<i) {
                if vis[s] || (s>>u)&1 == 0 || (s>>v)&1 == 0 { continue }
                vis[s] = true;
                g[s|(1<<i)] = g[s|(1<<i)].min(f[s] + 1);
                for j in 0..i {
                    if (s>>j)&1 == 0 { continue }
                    g[s^(1<<i)^(1<<j)] = g[s^(1<<i)^(1<<j)].min(f[s]);
                }
            }
        }
        std::mem::swap(&mut f, &mut g);
    }
    let ans = f.iter().min().unwrap();
    println!("{}", ans);
}