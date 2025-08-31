// Client.cs
// @author  June
// @date    2025.08.31
// @discription:

using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using UnityEngine;

namespace net
{
    public class Client : MonoBehaviour
    {
        void Start()
        {
            var socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            var ipPoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 8080);
            try
            {
                socket.Connect(ipPoint);
            }
            catch (SocketException e)
            {
                if (e.ErrorCode == 10061) print("服务器拒绝连接");
                else print("连接服务器失败" + e.ErrorCode);
                return;
            }

            var receiveBytes = new byte[1024];
            var receiveNum = socket.Receive(receiveBytes);
            print("收到服务器端发来的消息:" + Encoding.UTF8.GetString(receiveBytes, 0, receiveNum));

            socket.Send(Encoding.UTF8.GetBytes("hello, i am a client"));
            socket.Shutdown(SocketShutdown.Both);
            socket.Close();
        }
    }
}