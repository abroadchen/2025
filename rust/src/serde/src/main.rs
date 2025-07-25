use serde::{Serialize, Deserialize};

#[derive(Debug, Serialize, Deserialize)]
struct ServerConfig {
    workers: u64,
    ignore: bool,
    auth_server: Option<String>,
}





fn main() {
    let config = ServerConfig {
        workers: 100,
        ignore: false,
        auth_server: None,
    };
    {
        let serialized = serde_json::to_string(&config).unwrap();
        println!("{}", serialized);

        let deserialized: ServerConfig = serde_json::from_str(&serialized).unwrap();
        println!("{:?}", deserialized);
    }
    println!("Hello, world!");
}
