use std::io;

//x（要查找的元素索引）
fn find(x: usize, fa: &mut [usize]) -> usize {//返回元素的根节点
    //fa[x]直接指向根节点（路径压缩优化）
    if fa[x] != x { fa[x] = find(fa[x], fa); } fa[x]
}

fn unit(x: usize, y: usize, fa: &mut [usize], siz: &mut [i32]) {//元素个数
    let fx = find(x, fa);//x 所在集合的根节点
    let fy = find(y, fa);
    if fx != fy {//将较小的树合并到较大的树上
        if siz[fx] >= siz[fy] { fa[fy] = fx; siz[fx] += siz[fy]; } else {
            fa[fx] = fy; siz[fy] += siz[fx];
        }
    }
}

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let parts: Vec<&str> = input.trim().split_whitespace().collect();
    let n: usize = parts[0].parse().unwrap();
    let m: usize = parts[1].parse().unwrap();
    let mut fa = vec![0; 100];
    let mut siz = vec![0; 100];//每个根节点代表的集合大小
    let mut flag = vec![0; 100];//0表示已输出，1表示未输出
    for i in 1..=n { fa[i] = i; siz[i] = 1; flag[i] = 1; }
    for _ in 0..m {
        input.clear();
        io::stdin().read_line(&mut input).unwrap();
        let parts: Vec<&str> = input.trim().split_whitespace().collect();
        let a: usize = parts[0].parse().unwrap();
        let b: usize = parts[1].parse().unwrap();
        unit(a, b, &mut fa, &mut siz);
    }
    let mut x = 0;//大小为2的连通分量数量
    let mut y = 0;//大小为1的连通分量数量
    for i in 1..=n {
        if find(i, &mut fa) == i {//找出根节点
            if siz[i] > 3 { println!("-1"); return; }
            else if siz[i] == 2 { x += 1; }
            else if siz[i] == 1 { y += 1; }
        }
    }
    if x > y { println!("-1"); return; }
    let mut s = 0;
    for i in 1..=n {
        if siz[i] == 3 {//输出该组的所有成员
            print!("{} ", i);
            s = 1;
            flag[i] = 0;
            for j in 1..=n {
                if find(j, &mut fa) == i && flag[j] != 0 {
                    s += 1;
                    if s != 3 { print!("{} ", j); } else { println!("{}", j); }
                    flag[j] = 0;
                }
            }
        }
    }
    for i in 1..=n {
        if siz[i] == 2 {//输出大小为2的连通分量的元素
            print!("{} ", i);
            flag[i] = 0;
            for j in 1..=n {
                if find(j, &mut fa) == i && flag[j] != 0 {//确保 j 和 i 在同一组
                    print!("{} ", j);
                    flag[j] = 0;
                }
            }
            for j in 1..=n {//再找一个大小为1的连通分量凑成3人组
                if find(j, &mut fa) == j && siz[j] == 1 && flag[j] != 0 {
                    println!("{}", j);
                    flag[j] = 0;
                    break;
                }
            }
        }
    }
    let mut j = 0;
    for i in 1..=n {
        if find(i, &mut fa) == i && siz[i] == 1 && flag[i] != 0 {//输出所有未处理的单个元素
            if j != 2 { print!("{} ", i); j += 1; } else {//每3个元素一行输出（凑成3人组）
                j = 0; println!("{}", i);
            }
        }
    }
}
