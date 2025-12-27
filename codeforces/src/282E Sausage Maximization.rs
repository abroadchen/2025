use std::io;

const N: usize = 6000005;

fn main() {
    let mut input = String::new();//读取第一行输入，解析为整数n（数组长度）
    io::stdin().read_line(&mut input).unwrap();
    let n: usize = input.trim().parse().unwrap();
    let mut input = String::new();//读取第二行输入，解析为u64整数向量
    io::stdin().read_line(&mut input).unwrap();
    let a: Vec<u64> = input.trim().split_whitespace()
        .map(|s| s.parse().unwrap()).collect();
    let mut z = [[0; 2]; N];//字典树结构，每个节点最多2个子节点（0和1）
    let mut c = 0;//已分配的节点数

    fn insert(s: u64, z: &mut [[usize; 2]; N], c: &mut usize) {//向字典树中插入一个数
        let mut u = 0;//从根节点0开始
        for i in (0..=62).rev() {//从高位到低位
            let x = ((s>>i)&1) != 0;//提取第i位的值（0或1
            let j = x as usize;//将布尔值转换为usize索引
            if z[u][j] == 0 { *c += 1; z[u][j] = *c; }//如果当前位的子节点不存在，创建新节点
            u = z[u][j];//移动到下一个节点
        }
    }
    fn query(s: u64, z: &mut [[usize; 2]; N]) -> u64 {//查找与s异或结果最大的数
        let mut ans = 0;//初始化答案为0，从根节点开始搜索
        let mut u = 0;
        for i in (0..=62).rev() {
            let x = ((s>>i)&1) != 0;//获取当前位的值
            let j = x as usize;//优先选择与当前位相反的路径（这样异或结果为1）
            if z[u][1-j] != 0 { ans += 1<<i; u = z[u][1-j]; }//加上对应的位值 移动到相反路径
            else { u = z[u][j]; }//移动到相同位的路径
        }
        ans
    }

    insert(0, &mut z, &mut c);//插入0，表示可以取空前缀
    let mut x = 0u64;//存储当前前缀异或值
    for i in 1..=n {
        x ^= a[i-1];//数组索引从0开始
        insert(x, &mut z, &mut c);
    }
    x = 0;
    let mut mx = 0u64;
    for i in (1..=n).rev() {
        x ^= a[i-1];
        mx = mx.max(query(x, &mut z));//对每个后缀异或值，在字典树中查找能产生最大异或值的前缀
    }
    println!("{}", mx);
}