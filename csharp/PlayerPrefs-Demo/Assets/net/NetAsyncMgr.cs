using System.Collections;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Text;
using UnityEngine;

public class NetAsyncMgr : MonoBehaviour
{
    private static NetAsyncMgr instance;
    public static NetAsyncMgr Instance => instance;
    
    private Socket socket;
    private byte[] cacheBytes = new byte[1024 * 1024];
    private int cacheNum = 0;
    // Start is called before the first frame update
    void Awake()
    {
        instance = this;
        DontDestroyOnLoad(this.gameObject);
    }

    // Update is called once per frame
    void Update()
    {
        
    }
    
    public void Connect(string ip, int port)
    {
        if (socket != null && socket.Connected) return;
        var ipPoint = new IPEndPoint(IPAddress.Parse(ip), port);
        socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        var args = new SocketAsyncEventArgs();
        args.RemoteEndPoint = ipPoint;
        args.Completed += (sender, e) =>
        { 
            if (e.SocketError == SocketError.Success)
            {
                Debug.Log("已连入");
                var receiveArgs = new SocketAsyncEventArgs();
                receiveArgs.SetBuffer(cacheBytes, 0, cacheBytes.Length);
                receiveArgs.Completed += ReceiveCallBack;
                socket.ReceiveAsync(receiveArgs);
            }
            else
            {
                print("连入失败" + e.SocketError);
            }
        };
        socket.ConnectAsync(args);
    }

    private void ReceiveCallBack(object obj, SocketAsyncEventArgs args)
    {
        if (args.SocketError == SocketError.Success)
        {
            print(Encoding.UTF8.GetString(args.Buffer, 0, args.BytesTransferred));
            args.SetBuffer(0, args.Buffer.Length);
            if (socket != null && socket.Connected) socket.ReceiveAsync(args);
            Close();
        }
        else
        {
            print("接受消息错误" + args.SocketError);
        }
    }

    public void Close()
    {
        if (socket == null) return;
        socket.Shutdown(SocketShutdown.Both);
        socket.Disconnect(false);
        socket.Close();
        socket = null;
    }
    
    public void Send(string str)
    {
        if (socket is not { Connected: true }) return;
        var bytes = Encoding.UTF8.GetBytes(str);
        var args = new SocketAsyncEventArgs();
        args.SetBuffer(bytes, 0, bytes.Length);
        args.Completed += (sender, e) =>
        {
            if (e.SocketError == SocketError.Success) return;
            print("发送消息错误" + e.SocketError);
            Close();
        };
        socket.SendAsync(args);
        Close();
    }
}
