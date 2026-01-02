use std::io;

//计算 x 的最低位1及后面的0组成的数值
fn lb(x: i32) -> i32 { x & (-x) }
fn update(b: &mut [i32], mut x: usize) {
    while x < b.len() && x > 0 {
        b[x] += 1;
        x += lb(x as i32) as usize;
    }
}

fn query(b: &[i32], mut x: usize) -> i32 {//位置 1 到 x 的元素总和
    let mut res = 0;
    while x > 0 {
        res += b[x];
        x -= lb(x as i32) as usize;//在树中向下移动
    }
    res
}

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let parts: Vec<usize> = input.trim().split_whitespace()
        .map(|x| x.parse().unwrap()).collect();
    let n = parts[0];
    let m = parts[1];
    let mut a = vec![0i32; n + 1];//原数组，a[i] 表示位置 i 的值
    let mut p = vec![0i32; n + 1];//位置数组，p[val] 表示值 val 的位置
    let mut b = vec![0i32; n + 1];//树状数组，用于区间查询
    let mut l = vec![0i32; m + 1];//查询区间左端点和右端点
    let mut r = vec![0i32; m + 1];
    let mut ans = vec![0i32; m + 1];
    let mut lv = vec![Vec::<usize>::new(); n + 1];//存储左端点为 i 的所有查询索引
    let mut rv = vec![Vec::<usize>::new(); n + 1];//存储右端点为 i 的所有查询索引
    input.clear();
    io::stdin().read_line(&mut input).unwrap();
    let av: Vec<i32> = input.trim().split_whitespace()
        .map(|x| x.parse().unwrap()).collect();
    for i in 1..=n {
        a[i] = av[i - 1];
        if a[i] as usize <= n { p[a[i] as usize] = i as i32; }//建立值到位置的映射
    }
    for i in 1..=m {
        input.clear();
        io::stdin().read_line(&mut input).unwrap();
        let parts: Vec<i32> = input.trim().split_whitespace()
            .map(|x| x.parse().unwrap()).collect();
        l[i] = parts[0];
        r[i] = parts[1];
        if l[i] as usize <= n { lv[l[i] as usize].push(i); }//将查询索引添加到对应左/右端点的向量中
        if r[i] as usize <= n { rv[r[i] as usize].push(i); }
    }
    for i in 1..=n {
        for j in 0..lv[i].len() {//处理所有左端点为 i 的查询
            let idx = lv[i][j];
            let qr = query(&b, r[idx] as usize);//[1, r[idx]]
            let ql = if i > 1 { query(&b, i - 1) } else { 0 };//[1, i-1]
            ans[idx] -= qr - ql;//减去区间 [i, r[idx]] 的贡献
        }
        let mut j = 1;
        while j * a[i] as usize <= n {
            let val = (j as i32 * a[i]) as usize;
            if val <= n && val > 0 && p[val] != 0 {//倍数在范围内且存在对应位置
                update(&mut b, p[val] as usize);
            }
            j += 1;
        }
        for j in 0..rv[i].len() {//处理所有右端点为 i 的查询
            let idx = rv[i][j];
            let qr = query(&b, i);
            let ql = if l[idx] > 1 { query(&b, l[idx] as usize - 1) } else { 0 };
            ans[idx] += qr - ql;//加上区间 [l[idx], i] 的贡献
        }
    }
    for i in 1..=m { println!("{}", ans[i]); }
}