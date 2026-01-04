use std::io;
use std::io::Read;

fn main() {
    let mut input = String::new();//存储输入内容
    io::stdin().read_to_string(&mut input).unwrap();
    let mut lines = input.lines();//按行分割成迭代器
    let first_line = lines.next().unwrap();
    let parts: Vec<i32> = first_line.split_whitespace()
        .map(|x| x.parse().unwrap()).collect();
    let b = parts[0];//重复次数
    let d = parts[1];//除数
    let a = lines.next().unwrap().as_bytes();//字符串a 转换为字节数组 获取第二行
    let c = lines.next().unwrap().as_bytes();//获取第三行
    let la = a.len();
    let lc = c.len();
    let mut cnt = vec![0; 105];
    let mut nxt = vec![0; 105];//每个位置匹配后结束的位置
    for i in 0..lc {//遍历字符串c的每个位置作为起始点
        let mut x = i;//从位置i开始匹配
        for j in 0..la {//遍历字符串a的每个字符
            if a[j] == c[x] {//字符串a的当前字符与字符串c的当前字符匹配
                x += 1;//移动到字符串c的下一个位置
                if x == lc {//到达字符串c的末尾
                    cnt[i] += 1;//计数器加1（完成了一次完整匹配）
                    x = 0;//重置到字符串c的开头，继续匹配
                }
            }
        }
        nxt[i] = x;//记录从位置i开始匹配后结束的位置
    }
    let mut x = 0;//当前位置
    let mut ans = 0i64;//结果计数器
    for _ in 1..=b {
        ans += cnt[x] as i64;//当前位置的计数值加到结果中
        x = nxt[x];//移动到下一个位置
    }
    println!("{}", ans / d as i64);
}