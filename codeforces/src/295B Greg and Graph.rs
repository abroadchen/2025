use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();//迭代器状态会改变
    let n: usize = lines.next().unwrap().unwrap().trim().parse().unwrap();
    let mut mp = vec![vec![0i64; n + 1]; n + 1];
    for i in 1..=n {
        let line = lines.next().unwrap().unwrap();
        let row: Vec<i64> = line.split_whitespace().map(|s| s.parse().unwrap()).collect();
        for j in 1..=n { mp[i][j] = row[j - 1]; }
    }
    let line = lines.next().unwrap().unwrap();
    //存储要逆序激活的节点序列
    let query: Vec<usize> = line.split_whitespace().map(|s| s.parse().unwrap()).collect();
    let mut vis = vec![false; n + 1];//当前哪些节点已被激活
    let mut ans = Vec::new();//存储每步的答案
    for k in (1..=n).rev() {
        let cur = query[k - 1];//向量索引从0开始
        vis[cur] = true;
        for i in 1..=n {
            for j in 1..=n {//原距离和通过cur节点的路径距离的最小值
                mp[i][j] = mp[i][j].min(mp[i][cur] + mp[cur][j]);
            }
        }
        let mut sum = 0i64;
        for i in 1..=n {
            for j in 1..=n {
                if vis[i] && vis[j] { sum += mp[i][j]; }//当两个节点都被激活时才计算距离
            }
        }
        ans.push(sum);
    }
    ans.reverse();//逆序处理询问，所以答案也是逆序的
    //&val：解引用获取实际值
    for (i, &val) in ans.iter().enumerate() {//同时获取索引和值的迭代器
        if i == ans.len() - 1 { print!("{}", val); } else {//最后一个元素后不加空格，其他元素后加空格
            print!("{} ", val);
        }
    }
    println!();
}