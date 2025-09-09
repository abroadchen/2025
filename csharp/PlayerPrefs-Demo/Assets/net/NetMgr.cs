using System;
using System.Collections;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using UnityEngine;

public class NetMgr : MonoBehaviour
{
    private static NetMgr instance;

    public static NetMgr Instance => instance;

    //�ͻ���Socket
    private Socket socket;
    //���ڷ�����Ϣ�Ķ��� �������� ���߳�������� �����̴߳�����ȡ
    private Queue<BaseMsg> sendMsgQueue = new Queue<BaseMsg>();
    //���ڽ�����Ϣ�Ķ��� �������� ���߳�������� ���̴߳�����ȡ
    private Queue<BaseMsg> receiveQueue = new Queue<BaseMsg>();

    ////��������Ϣ��ˮͰ��������
    //private byte[] receiveBytes = new byte[1024 * 1024];
    ////�����յ����ֽ���
    //private int receiveNum;

    //���ڴ���ְ�ʱ ����� �ֽ����� �� �ֽ����鳤��
    private byte[] cacheBytes = new byte[1024 * 1024];
    private int cacheNum = 0;

    //�Ƿ�����
    private bool isConnected = false;

    //����������Ϣ�ļ��ʱ��
    private int SEND_HEART_MSG_TIME = 2;
    private HeartMsg hearMsg = new HeartMsg();

    void Awake()
    {
        instance = this;
        DontDestroyOnLoad(this.gameObject);
        //�ͻ���ѭ����ʱ������˷���������Ϣ
        InvokeRepeating("SendHeartMsg", 0, SEND_HEART_MSG_TIME);
    }

    private void SendHeartMsg()
    {
        if (isConnected)
            Send(hearMsg);
    }

    // Update is called once per frame
    void Update()
    {
        if (receiveQueue.Count <= 0) return;
        var msg = receiveQueue.Dequeue();
        if (msg is not PlayerMsg playerMsg) return;
        print(playerMsg.playerID);
        print(playerMsg.playerData.name);
        print(playerMsg.playerData.lev);
        print(playerMsg.playerData.atk);
    }

    //���ӷ����
    public void Connect(string ip, int port)
    {
        //���������״̬ ֱ�ӷ���
        if (isConnected)
            return;

        if (socket == null)
            socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        //���ӷ����
        IPEndPoint ipPoint = new IPEndPoint(IPAddress.Parse(ip), port);
        try
        {
            socket.Connect(ipPoint);
            isConnected = true;
            //���������߳�
            ThreadPool.QueueUserWorkItem(SendMsg);
            //���������߳�
            ThreadPool.QueueUserWorkItem(ReceiveMsg);
        }
        catch (SocketException e)
        {
            if (e.ErrorCode == 10061)
                print("�������ܾ�����");
            else
                print("����ʧ��" + e.ErrorCode + e.Message);
        }
    }

    //������Ϣ
    public void Send(BaseMsg msg)
    {
        sendMsgQueue.Enqueue(msg);
    }

    /// <summary>
    /// ���ڲ��� ֱ�ӷ��ֽ�����ķ���
    /// </summary>
    /// <param name="bytes"></param>
    public void SendTest(byte[] bytes)
    {
        socket.Send(bytes);
    }

    private void SendMsg(object obj)
    {
        while (isConnected)
        {
            if (sendMsgQueue.Count > 0)
            {
                socket.Send(sendMsgQueue.Dequeue().Writing());
            }
        }
    }

    //��ͣ�Ľ�����Ϣ
    private void ReceiveMsg(object obj)
    {
        while (isConnected)
        {
            if (socket.Available <= 0) continue;
            var receiveBytes = new byte[1024 * 1024];
            var receiveNum = socket.Receive(receiveBytes);
            HandleReceiveMsg(receiveBytes, receiveNum);
            ////���Ȱ��յ��ֽ������ǰ4���ֽ�  ��ȡ�����õ�ID
            //int msgID = BitConverter.ToInt32(receiveBytes, 0);
            //BaseMsg baseMsg = null;
            //switch (msgID)
            //{
            //    case 1001:
            //        PlayerMsg msg = new PlayerMsg();
            //        msg.Reading(receiveBytes, 4);
            //        baseMsg = msg;
            //        break;
            //}
            ////�����ϢΪ�� ��֤���ǲ�֪�����͵���Ϣ û�н���
            //if (baseMsg == null)
            //    continue;
            ////�յ���Ϣ ������ϢΪ�ַ��� �����빫������
            //receiveQueue.Enqueue(baseMsg);
        }
    }

    //���������Ϣ �ְ���������ķ���
    private void HandleReceiveMsg(byte[] receiveBytes, int receiveNum)
    {
        var msgID = 0;
        var msgLength = 0;
        var nowIndex = 0;

        //�յ���Ϣʱ Ӧ�ÿ��� ֮ǰ��û�л���� ����еĻ� ����ֱ��ƴ�ӵ�����
        receiveBytes.CopyTo(cacheBytes, cacheNum);
        cacheNum += receiveNum;

        while (true)
        {
            //ÿ�ν���������Ϊ-1 �Ǳ�����һ�ν��������� Ӱ����һ�ε��ж�
            msgLength = -1;
            //�������һ����Ϣ
            if(cacheNum - nowIndex >= 8)
            {
                //����ID
                msgID = BitConverter.ToInt32(cacheBytes, nowIndex);
                nowIndex += 4;
                //��������
                msgLength = BitConverter.ToInt32(cacheBytes, nowIndex);
                nowIndex += 4;
            }

            if(cacheNum - nowIndex >= msgLength && msgLength != -1)
            {
                //������Ϣ��
                BaseMsg baseMsg = null;
                switch (msgID)
                {
                    case 1001:
                        var msg = new PlayerMsg();
                        msg.Reading(cacheBytes, nowIndex);
                        baseMsg = msg;
                        break;
                }
                if (baseMsg != null)
                    receiveQueue.Enqueue(baseMsg);
                nowIndex += msgLength;
                if (nowIndex != cacheNum) continue;
                cacheNum = 0;
            }
            else
            {
                //��������� ֤���зְ� 
                //��ô������Ҫ�ѵ�ǰ�յ������� ��¼����
                //�д��´ν��ܵ���Ϣ�� ��������
                //receiveBytes.CopyTo(cacheBytes, 0);
                //cacheNum = receiveNum;
                //��������� id�ͳ��ȵĽ��� ���� û�гɹ�������Ϣ�� ��ô������Ҫ��ȥnowIndex�ƶ���λ��
                if (msgLength != -1)
                    nowIndex -= 8;
                //���ǰ�ʣ��û�н������ֽ��������� �Ƶ�ǰ���� ���ڻ����´μ�������
                Array.Copy(cacheBytes, nowIndex, cacheBytes, 0, cacheNum - nowIndex);
                cacheNum = cacheNum - nowIndex;
            }

            break;
        }
        
    }

    public void Close()
    {
        if (socket == null) return;
        print("�ͻ��������Ͽ�����");

        //��������һ���Ͽ����ӵ���Ϣ�������
        //QuitMsg msg = new QuitMsg();
        //socket.Send(msg.Writing());
        //socket.Shutdown(SocketShutdown.Both);
        //socket.Disconnect(false);
        //socket.Close();
        socket = null;

        isConnected = false;
    }

    private void OnDestroy()
    {
        Close();
    }
}
