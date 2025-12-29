use std::io;

fn main() {
    let names = [
        "Washington", "Adams", "Jefferson", "Madison", "Monroe", "Adams", "Jackson",
        "Van Buren", "Harrison", "Tyler", "Polk", "Taylor", "Fillmore", "Pierce",
        "Buchanan", "Lincoln", "Johnson", "Grant", "Hayes", "Garfield", "Arthur",
        "Cleveland", "Harrison", "Cleveland", "McKinley", "Roosevelt", "Taft",
        "Wilson", "Harding", "Coolidge", "Hoover", "Roosevelt", "Truman",
        "Eisenhower", "Kennedy", "Johnson", "Nixon", "Ford", "Carter", "Reagan"
    ];
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let i: usize = input.trim().parse().unwrap();
    println!("{}", names[i - 1]);//由于数组索引从0开始，而届数从1开始，所以需要减1
}