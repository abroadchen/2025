use std::io;
use std::io::{BufRead, BufReader, Write};
use std::net::TcpStream;
use serde::{ Serialize, Deserialize };

#[derive(Debug, Serialize, Deserialize)]
struct Point3D {
    x: f32,
    y: f32,
    z: f32,
}


fn main() -> io::Result<()> {
    let mut stream = TcpStream::connect("127.0.0.1:8080")?;
    loop {
        let mut input = String::new();
        let mut buffer: Vec<u8> = Vec::new();
        io::stdin().read_line(&mut input)?;
        let parts: Vec<&str>= input.trim_matches('\n').split(',').collect();
        let point = Point3D {
            x: parts[0].parse().unwrap(),
            y: parts[1].parse().unwrap(),
            z: parts[2].parse().unwrap(),
        };
        stream.write_all(serde_json::to_string(&point).unwrap().as_bytes())?;
        stream.write_all(b"\n")?;

        let mut reader = BufReader::new(&stream);
        reader.read_until(b'\n', &mut buffer)?;
        let input = str::from_utf8(&buffer).unwrap();
        if input == "" {
            eprintln!("Empty response");
        }
        println!("Response: {:?}", input);
    }


}
