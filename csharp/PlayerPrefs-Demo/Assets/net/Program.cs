// Program.cs
// @author  June
// @date    2025.08.31
// @discription:

using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

namespace net
{
    public class Program
    {
        static void Main(string[] args)
        {
            var socketTcp = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            try
            {
                var ipPoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 8080);
                socketTcp.Bind(ipPoint);
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                throw;
            }
            socketTcp.Listen(1024);
            Console.WriteLine("等待客户端连入");

            var socketClient = socketTcp.Accept();
            Console.WriteLine("已连入");

            var msg = new PlayerMsg();
            msg.playerID = 66;
            msg.playerData = new PlayerData();
            msg.playerData.name = "June";
            msg.playerData.atk = 100;
            msg.playerData.lev = 10;

            socketClient.Send(msg.Writing());
            var result = new byte[1024];
            var receiveNum = socketClient.Receive(result);
            Console.WriteLine("接收到了{0}发来的消息: {1}",
                socketClient.RemoteEndPoint.ToString(),
                Encoding.UTF8.GetString(result, 0, receiveNum));
            socketClient.Shutdown(SocketShutdown.Both);
            socketClient.Close();

            Console.WriteLine("按任意键退出!");
            Console.ReadKey();
        }
    }
}