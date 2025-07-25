
use std::io::{self, BufRead, BufReader, Error, Write};
use std::net::TcpStream;

fn main() -> io::Result<()> {
    let mut stream = TcpStream::connect("127.0.0.1:8080")?;
    for _ in 0..10 {
        let mut input = String::new();
        io::stdin().read_line(&mut input).expect("Failed to read line");
        stream.write(input.as_bytes()).expect("Failed to write to stream");

        let mut reader = BufReader::new(&stream);
        let mut buffer: Vec<u8> = Vec::new();
        reader.read_until(b'\n', &mut buffer).expect("Failed to read line");
        println!("read from server: {}", String::from_utf8_lossy(&buffer));
    }
    Ok(())
}
