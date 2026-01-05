/**
1. s.chars()
将字符串 s 转换为字符迭代器
返回一个 Chars 类型的迭代器
例如：如果 s = "ABC"，则 s.chars() 产生 ['A', 'B', 'C'] 的迭代器
2. .next()
从迭代器中获取下一个元素（即第一个元素）
返回 Option<char> 类型
如果迭代器不为空：返回 Some(第一个字符)
如果迭代器为空：返回 None
3. .unwrap()
解包 Option 类型
如果是 Some(value)：返回 value（即第一个字符）
如果是 None：panic（程序崩溃）
*/
use std::io::{self, BufRead};

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();
    let s = lines.next().unwrap().unwrap();
    let mut cnt = [0; 128];//字母出现情况
    let mut w = 0;//'?'的数量
    for ch in s.chars() {
        if ch >= 'A' && ch < 'K' { cnt[ch as usize] = 1; }//标记为出现
        else if ch == '?' { w += 1; }
    }
    let mut res = 1;
    let mut tot = 0;
    for i in 'A' as usize..='J' as usize { tot += cnt[i]; }//A到J之间已出现的字母数量
    if tot > 0 {
        if s.chars().next().unwrap() >= 'A' && s.chars().next().unwrap() < 'K' {
            res *= 9;//第一个字符是A到J之间的字母，乘以9
        } else { res *= 10; }
    }
    for i in 1..tot { res *= (10 - i) as i32; }//计算排列数：对于后续的字母位置，可选数字逐渐减少
    if w > 0 && s.chars().next().unwrap() == '?' {//如果有问号且第一个字符是问号
        res *= 9;//第一个位置不能是0，所以有9种选择
        w -= 1;//减少问号计数
    }
    let p = "0".repeat(w as usize);//创建零的填充字符串
    println!("{}{}", res, p);//数字部分 + 零的填充
}