use std::io::{self, BufRead};

#[derive(Clone, Copy, Default)]
struct Node { a: i32, b: i32, s: i32, id: usize }
impl PartialOrd for Node {
    fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
        Some(self.s.cmp(&other.s))//返回按s字段的比较结果
    }
}
impl PartialEq for Node {
    fn eq(&self, other: &Self) -> bool {
        self.s == other.s//s字段是否相等
    }
}

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let n: usize = input.trim().parse().unwrap();
    let x = (n + 2) / 3;
    let mut ans = vec![Node::default(); n + 1];
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let val: Vec<i32> = input.trim().split_whitespace().map(|x| x.parse().unwrap()).collect();
    for i in 1..=n {
        ans[i].s = val[i - 1];
        ans[i].id = i;
    }
    ans[1..=n].sort_by(|a, b| a.s.cmp(&b.s));//按s字段升序
    for i in 1..=x {//前x个元素
        ans[i].a = (i - 1) as i32;//a字段为i-1
        ans[i].b = ans[i].s - (i - 1) as i32;//b字段为s-(i-1)
    }
    for i in x + 1..=n - x {//中间n-2x个元素（从x+1到n-x）
        ans[i].b = (i - 1) as i32;
        ans[i].a = ans[i].s - (i - 1) as i32;
    }
    for i in n - x + 1..=n {//最后x个元素（从n-x+1到n）
        ans[i].b = (n - i) as i32;
        ans[i].a = ans[i].s - ans[i].b;
    }
    ans[1..=n].sort_by(|a, b| a.id.cmp(&b.id));//恢复原始顺序
    println!("YES");
    for i in 1..=n { print!("{} ", ans[i].a); } println!();//输出a数组
    for i in 1..=n { print!("{} ", ans[i].b); } println!();
}