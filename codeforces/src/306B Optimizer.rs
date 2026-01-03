use std::io;

const N: usize = 2_000_010;
fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let parts: Vec<i32> = input.trim().split_whitespace()
        .map(|s| s.parse().unwrap()).collect();
    let n = parts[0] as usize;
    let m = parts[1] as usize;
    let mut d = vec![0; N];//差分数组
    let mut mx = vec![0; N];//最大右端点
    let mut num = vec![0; N];//区间编号
    let mut flag = vec![false; N];//是否选择
    for i in 1..=m {
        input.clear();
        io::stdin().read_line(&mut input).unwrap();
        let parts: Vec<i32> = input.trim().split_whitespace()
            .map(|s| s.parse().unwrap()).collect();
        let l = parts[0] as usize;
        let s = parts[1] as usize;
        let r = l + s - 1;//（左端点+长度-1）
        d[l] += 1;
        d[r + 1] -= 1;
        if r as i32 > mx[l] {//当前右端点比记录的最大值大
            mx[l] = r as i32;
            num[l] = i as i32;
        }
    }
    for i in 1..=n { d[i] += d[i - 1]; }//位置i被多少个区间覆盖
    let mut cur = 0;//当前处理位置
    let mut v = 0;//当前最大右端点
    let mut p = 0;//对应的区间编号
    for i in 1..=n {
        if mx[i] > v { v = mx[i]; p = num[i]; };
        if d[i] != 0 && cur < i as i32 {//位置i被覆盖且当前处理位置小于i
            cur = v;//更新当前处理位置为最大右端点
            flag[p as usize] = true;//标记该区间被选中
        }
    }
    let mut ans = Vec::new();//未被选中的区间编号
    for i in 1..=m { if !flag[i] { ans.push(i as i32); } }
    println!("{}", ans.len());
    if !ans.is_empty() {
        print!("{}", ans[0]);
        for i in 1..ans.len() { print!(" {}", ans[i]); }
        println!();
    }
}