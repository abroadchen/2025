// GameScene.cs
// @author  June
// @date    2025.08.17
// @discription:


using System.Net.Http.Headers;
using Tetris.Lesson13;
using Tetris.Lesson3;
using Tetris.Lesson5;

namespace Tetris.Lesson1;

internal class GameScene : ISceneUpdate
{
    private Map map;
    private BlockWorker blockWorker;
    //private bool isRunning;
    //private Thread? inputThread;
    private int updateIndex = 0;
    public GameScene()
    {
        map = new Map(this);
        blockWorker = new BlockWorker();

        InputThread.Instance.inputEvent += CheckInputThread;
        //isRunning = true;
        //inputThread = new Thread(CheckInputThread);
        //inputThread.IsBackground = true;
        //inputThread.Start();
    }

    private void CheckInputThread()
    {
        //while (isRunning)
        //{
            if (!Console.KeyAvailable) return;
            lock (blockWorker)
            {
                var key = Console.ReadKey(true).Key;
                switch (key)
                {
                    case ConsoleKey.LeftArrow:
                        if (blockWorker.CanChange(EChangeType.Left, map))
                            blockWorker.Change(EChangeType.Left);
                        break;
                    case ConsoleKey.RightArrow:
                        if (blockWorker.CanChange(EChangeType.right, map))
                            blockWorker.Change(EChangeType.right);
                        break;
                    case ConsoleKey.A:
                        if (blockWorker.CanMoveRL(EChangeType.Left, map))
                            blockWorker.MoveRL(EChangeType.Left);
                        break;
                    case ConsoleKey.D:
                        if (blockWorker.CanMoveRL(EChangeType.right, map))
                            blockWorker.MoveRL(EChangeType.right);
                        break;
                    case ConsoleKey.S:
                        if (blockWorker.CanMove(map))
                            blockWorker.AutoMove();
                        break;
                } 
            }
        //}
    }

    public void StopThread()
    {
        InputThread.Instance.inputEvent -= CheckInputThread;
        //isRunning = false;
        //inputThread = null;
    }

    public void Update()
    {
        lock (blockWorker)
        {
            map.Draw();
            blockWorker.Draw();
        
            if (blockWorker.CanMove(map))
                blockWorker.AutoMove();
        }
        
        Thread.Sleep(500);
        
        
        
    }
}