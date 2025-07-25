use std::io;
use std::net::UdpSocket;

fn main() -> io::Result<()> {
    let socket = UdpSocket::bind("0.0.0.0:8080")?;
    socket.connect("127.0.0.1:8080")?;
    loop {
        let mut input = String::new();
        io::stdin().read_line(&mut input)?;
        socket.send(input.as_bytes())?;

        let mut buffer = [0u8; 1500];
        socket.recv_from(&mut buffer)?;
        println!("{}", str::from_utf8(&buffer).unwrap());
    }
}
