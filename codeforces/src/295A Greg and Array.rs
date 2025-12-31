/**
在位置l增加值，表示从l开始的所有位置都要加上这个值
在位置r+1减少值，表示从r+1开始不再加这个值
最小访问索引：1（因为循环从1开始）
最大访问索引：n+1（因为r+1，r最大为n）
所以数组长度需要是n+2（索引0到n+1）
r的最大值可能是m（如果所有操作的右边界都是m）
因此r + 1的最大值是m + 1
为了访问b[m+1]，数组长度至少要是m + 2
在某些情况下，可能存在r = m+1的输入
或者算法逻辑中可能出现r+1 = m+2的情况
使用m+3提供了额外的安全边界
*/
use std::io::{self, BufRead};
#[derive(Clone)]
struct Node { l: i64, r: i64, val: i64, cnt: i64 }
fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();//获取输入流的迭代器，每次产生一行
    let line = lines.next().unwrap().unwrap();//获取下一行
    let parts: Vec<i64> = line.split_whitespace().map(|x| x.parse().unwrap()).collect();
    let n = parts[0];
    let m = parts[1];//操作数
    let k = parts[2];//操作次数
    let line = lines.next().unwrap().unwrap();
    let arr: Vec<i64> = line.split_whitespace().map(|x| x.parse().unwrap()).collect();
    let mut a = vec![0i64; n as usize + 1];//使索引从1开始
    for i in 1..=n as usize { a[i] = arr[i - 1]; }
    let mut op = vec![Node { l: 0, r: 0, val: 0, cnt: 0}; m as usize + 1];//创建指定大小的向量，用初始值填充
    for i in 1..=m as usize {
        let line = lines.next().unwrap().unwrap();
        let parts: Vec<i64> = line.split_whitespace().map(|x| x.parse().unwrap()).collect();
        op[i].l = parts[0];
        op[i].r = parts[1];
        op[i].val = parts[2];
    }
    let mut b = vec![0i64; (m + 3) as usize];
    for _ in 1..=k as usize {
        let line = lines.next().unwrap().unwrap();
        let parts: Vec<i64> = line.split_whitespace().map(|x| x.parse().unwrap()).collect();
        let l = parts[0] as usize;
        let r = parts[1] as usize;
        b[l] += 1;//区间的开始位置+1
        b[r + 1] -= 1;//区间的结束位置+1处-1
    }
    for i in 1..=m as usize {
        b[i] += b[i - 1];//第i个操作的执行次数
        op[i].cnt = b[i];//存储到对应操作结构体中
    }
    let mut res = vec![0i64; (n + 2) as usize];
    for i in 1..=m as usize {
        let x = &op[i];
        res[x.l as usize] += x.val * x.cnt;//在区间开始处加上增加值
        res[(x.r + 1) as usize] -= x.val * x.cnt;
    }
    for i in 1..=n as usize { res[i] += res[i - 1]; }//位置i的总增加值
    for i in 1..=n as usize {
        if i == 1 { print!("{}", a[i] + res[i]); } else {//原数组值加上操作增加值
            print!(" {}", a[i] + res[i]);
        }
    }
    println!();
}