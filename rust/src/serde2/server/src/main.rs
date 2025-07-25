use std::{io, thread};
use std::io::{BufRead, BufReader, Write};
use std::net::{TcpListener, TcpStream};
use serde::{Serialize, Deserialize};
use serde_json;
#[derive(Debug, Serialize, Deserialize)]
struct Point3D {
    x: f32,
    y: f32,
    z: f32,
}

fn handle_client(stream: TcpStream) -> io::Result<()> {
    println!("Client {:?}", stream.peer_addr());
    let mut data = Vec::new();
    let mut stream = BufReader::new(stream);

    loop {
        data.clear();
        let n = stream.read_until(b'\n', &mut data)?;
        if n == 0 {
            return Ok(());
        }
        let input: Point3D = serde_json::from_slice(&data)?;
        let value = input.x.powf(2.0) + input.y.powf(2.0) + input.z.powf(2.0);
        stream.get_mut().write(&(serde_json::to_vec(&(f64::from(value).sqrt()))?))?;
        stream.get_mut().write(&("\n".as_bytes()))?;
        stream.get_mut().flush()?;

    }
    Ok(())
}


fn main() -> io::Result<()> {
    let listener = TcpListener::bind("0.0.0.0:1234")?;
    for stream in listener.incoming() {
        match stream {
            Err(e) => eprintln!("Error: {}", e),
            Ok(stream) => {
                thread::spawn(move || {
                    handle_client(stream).unwrap_or_else(|e| eprintln!("Error: {}", e));
                });
            }
        }
    }
    println!("Hello, world!");
    Ok(())
}
