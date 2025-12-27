/*
更新函数，用于在树状数组中添加值
c: &mut [i32; N]：树状数组的可变引用
mut i: usize：要更新的位置（可变）
x: i32：要添加的值
n: usize：数组的最大长度
求和函数，用于计算前缀和
c: &[i32; N]：树状数组的不可变引用
mut i: usize：要查询的位置（可变）
-> i32：返回类型为32位整数

初始化树状数组c，所有元素为0
l：当前序列长度
ans：当前总和
循环n次，处理n个操作

操作1：在前a个元素上都加上x
解析参数a和x
使用差分数组技巧：在位置1加x，在位置a+1减x
更新总和ans
操作2：在序列末尾添加一个数k
解析参数k
更新总和
增加序列长度
在树状数组中添加新元素
操作3：删除序列末尾的元素
通过树状数组查询末尾元素的值
更新总和
从树状数组中移除该元素
减少序列长度

原始状态：当元素k被添加到位置l时，我们执行了：
add(&mut c, l, k, n) # 在位置l加k
add(&mut c, l + 1, -k, n) # 在位置l+1减k
删除时的操作：
add(&mut c, l, -k, n) # 在位置l减k（抵消原来的加k）
add(&mut c, l + 1, k, n) # 在位置l+1加k（抵消原来的减k）

在位置l加k，表示从位置l开始所有元素都加k
在位置l+1减k，表示从位置l+1开始不再加k
这样只有位置l的元素实际增加了k
当我们删除这个元素时，需要进行相反的操作来撤销之前的差分更新

*/
use std::io;

const N: usize = 200001;

fn add(c: &mut [i32; N], mut i: usize, x: i32, n: usize) {
    while i <= n {
        c[i] += x;
        i += i & i.wrapping_neg();
    }
}

fn sum(c: &[i32; N], mut i: usize) -> i32 {
    let mut s = 0;
    while i != 0 {
        s += c[i];
        i -= i & i.wrapping_neg();
    }
    s
}

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let n: usize = input.trim().parse().unwrap();
    let mut c = [0i32; N];
    let mut l = 1;
    let mut ans = 0f64;
    for _ in 1..=n {
        let mut input = String::new();
        io::stdin().read_line(&mut input).unwrap();
        let parts: Vec<&str> = input.trim().split_whitespace().collect();
        let t: i32 = parts[0].parse().unwrap();
        if t == 1 {
            let a: usize = parts[1].parse().unwrap();
            let x: i32 = parts[2].parse().unwrap();
            add(&mut c, 1, x, n);
            if a + 1 <= n { add(&mut c, a + 1, -x, n); }
            ans += (a as f64) * (x as f64);
        } else if t == 2 {
            let k: i32 = parts[1].parse().unwrap();
            ans += k as f64;
            l += 1;
            add(&mut c, l, k, n);
            if l + 1 <= n { add(&mut c, l + 1, -k, n); }
        } else if l >= 2 {
            let k = sum(&c, l);
            ans -= k as f64;
            add(&mut c, l, -k, n);
            if l + 1 <= n { add(&mut c, l + 1, k, n); }
            l -= 1;
        }
        println!("{:.6}", ans / l as f64);//当前平均值
    }
}