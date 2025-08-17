// See https://aka.ms/new-console-template for more information

//Console.WriteLine("Hello, World!");

namespace Princess
{
    class Program
    {
        static void Main(string[] args)
        {
            #region 1 控制台基础设置 

            Console.CursorVisible = false;
            int w = 50;
            int h = 20;
            Console.SetWindowSize(w, h);
            Console.SetBufferSize(w, h);

            #endregion

            #region 2 多个场景

            int nowSceneID = 1;

            string gameOverInfo = "";
            
            while (true)
            {
                switch (nowSceneID)
                {
                    case 1:
                        #region 开始场景逻辑 

                        Console.Clear();
                        Console.SetCursorPosition(w / 2 - 7, 8);
                        Console.Write("马里奥营救公主");
                        int nowSelIndex = 0;
                        while (true)
                        {
                            bool isQuitWhile = false;
                            Console.SetCursorPosition(w / 2 - 4, 13);
                            Console.ForegroundColor = nowSelIndex == 0 ? ConsoleColor.Red : ConsoleColor.White;
                            Console.Write("开始游戏");
                            Console.SetCursorPosition(w / 2 - 4, 15);
                            Console.ForegroundColor = nowSelIndex == 1 ? ConsoleColor.Red : ConsoleColor.White;
                            Console.Write("结束游戏");
                            char input = Console.ReadKey(true).KeyChar;
                            switch (input)
                            {
                                case 'W':
                                case 'w':
                                    --nowSelIndex;
                                    if (nowSelIndex < 0)
                                        nowSelIndex = 0;
                                    break;
                                case 'S':
                                case 's':
                                    ++nowSelIndex;
                                    if (nowSelIndex > 1)
                                        nowSelIndex = 1;
                                    break;
                                case 'J':
                                case 'j':
                                    if (nowSelIndex == 0)
                                    {
                                        nowSceneID = 2;
                                        isQuitWhile = true;
                                    }
                                    else
                                    {
                                        Environment.Exit(0);
                                    }
                                    break;
                            }
                            if (isQuitWhile)
                                break;
                        }

                        #endregion
                        break;
                    case 2:
                        Console.Clear();

                        #region 不变的红墙

                        Console.ForegroundColor = ConsoleColor.Red;
                        for (int i = 0; i < w; i += 2)
                        {
                            Console.SetCursorPosition(i, 0);
                            Console.Write("■");
                
                            Console.SetCursorPosition(i, h - 1);
                            Console.Write("■");
                    
                            Console.SetCursorPosition(i, h - 6);
                            Console.Write("■");
                        }
                        for (int i = 0; i < h; i++)
                        {
                            Console.SetCursorPosition(0, i);
                            Console.Write("■");
                   
                            Console.SetCursorPosition(w - 2, i);
                            Console.Write("■");
                        }
                        #endregion

                        #region boss属性

                        int bossX = 24;
                        int bossY = 15;
                        int bossAtkMin = 7;
                        int bossAtkMax = 13;
                        int bossHp = 100;
                        string bossIcon = "■";
                        ConsoleColor bossColor = ConsoleColor.Green;
                        #endregion

                        #region 玩家属性

                        int playerX = 4;
                        int playerY = 5;
                        int playerAtkMin = 8;
                        int playerAtkMax = 12;
                        int playerHp = 100;
                        string playerIcon = "○";
                        ConsoleColor playerColor = ConsoleColor.Yellow;

                        #endregion

                        #region 公主属性

                        int princessX = 24;
                        int princessY = 5;
                        string princessIcon = "★";
                        ConsoleColor princessColor = ConsoleColor.Magenta;

                        #endregion
                        char playerInput;

                        bool isFight = false;
                        bool isOver = false;
                        
                        while (true)
                        {
                            #region boss属性相关

                            if (bossHp > 0)
                            {
                                Console.SetCursorPosition(bossX, bossY);
                                Console.ForegroundColor = bossColor;
                                Console.Write(bossIcon);
                            }
                            else
                            {
                                Console.SetCursorPosition(princessX, princessY);
                                Console.ForegroundColor = princessColor;
                                Console.Write(princessIcon);
                            }

                            #endregion
                            #region 玩家属性相关

                            Console.SetCursorPosition(playerX, playerY);
                            Console.ForegroundColor = playerColor;
                            Console.Write(playerIcon);

                            playerInput = Console.ReadKey(true).KeyChar;

                            #endregion
                            #region 战斗 

                            if (isFight)
                            {
                                if (playerInput == 'J' || playerInput == 'j')
                                {
                                    if (playerHp <= 0)
                                    {
                                        nowSceneID = 3;
                                        gameOverInfo = "游戏失败";
                                        break;
                                    }
                                    else if (bossHp <= 0)
                                    {
                                        Console.SetCursorPosition(bossX, bossY);
                                        Console.Write("  ");
                                        isFight = false;
                              
                                    }
                                    else
                                    { 
                                        Random r = new Random();
                                        int atk = r.Next(playerAtkMin, playerAtkMax);
                                        bossHp -= atk;
                                        Console.ForegroundColor = ConsoleColor.Green;
                                        Console.SetCursorPosition(2, h - 4);
                                        Console.Write("                                                  ");
                                        Console.SetCursorPosition(2, h - 4);
                                        Console.Write("你对boss造成了{0}点伤害,boss剩余血量为{1}", atk, bossHp);
                                        if (bossHp > 0)
                                        {
                                            atk = r.Next(bossAtkMin, bossAtkMax);
                                            playerHp -= atk;
                                            Console.ForegroundColor = ConsoleColor.Yellow;
                                            Console.SetCursorPosition(2, h - 3);
                                            Console.Write("                                                  ");
                                            
                                            if (playerHp <= 0)
                                            {
                                                Console.SetCursorPosition(2, h - 3); 
                                                Console.Write("你被boss打死了");
                                            }
                                            else
                                            {
                                                Console.SetCursorPosition(2, h - 3);
                                                Console.Write("boss对你造成了{0}点伤害,你剩余血量为{1}", atk, playerHp); 
                                            }
                                        }
                                        else
                                        {
                                            Console.SetCursorPosition(2, h - 5);
                                            Console.Write("                                                  "); 
                                            Console.SetCursorPosition(2, h - 4);
                                            Console.Write("                                                  ");
                                            Console.SetCursorPosition(2, h - 3);
                                            Console.Write("                                                  ");
                                            Console.SetCursorPosition(2, h - 5);
                                            Console.Write("你击杀了boss,你获得1000点经验");   
                                            Console.SetCursorPosition(2, h - 4);
                                            Console.Write("快去救公主 按J继续");
                                       
                                        } 
                                    }
                                }
                            }
                            else
                            { 
                                #region 玩家移动
                                Console.SetCursorPosition(playerX, playerY);
                                Console.Write("  ");
                                switch (playerInput)
                                {
                                    case 'W':
                                    case 'w':
                                        --playerY;
                                        if (playerY < 1)
                                            playerY = 1;
                                        else if (playerX == bossX && playerY == bossY && bossHp > 0)
                                            ++playerY;
                                        else if (playerX == princessX && playerY == princessY && bossHp <= 0)
                                            ++playerY;
                                        break;
                                    case 'A':
                                    case 'a':
                                        playerX -= 2;
                                        if (playerX < 2)
                                            playerX = 2;
                                        else if (playerX == bossX && playerY == bossY && bossHp > 0)
                                            playerX += 2;
                                        else if (playerX == princessX && playerY == princessY && bossHp <= 0)
                                            playerX += 2;
                                        break;
                                    case 'S':
                                    case 's':
                                        ++playerY;
                                        if (playerY > h - 7)
                                            playerY = h - 7;
                                        else if (playerX == bossX && playerY == bossY && bossHp > 0)
                                            --playerY;
                                        else if (playerX == princessX && playerY == princessY && bossHp <= 0)
                                            --playerY;
                                        break;
                                    case 'D':
                                    case 'd':
                                       
                                        playerX += 2;
                                        if (playerX > w - 4)
                                            playerX = w - 4;
                                        else if (playerX == bossX && playerY == bossY && bossHp > 0)
                                            playerX -= 2;
                                        else if (playerX == princessX && playerY == princessY && bossHp <= 0)
                                            playerX -= 2;
                                        break;
                                    case 'J':
                                    case 'j':
                                        if ((playerX == bossX && playerY == bossY - 1 ||
                                             playerX == bossX && playerY == bossY + 1 ||
                                             playerX == bossX - 2 && playerY == bossY ||
                                             playerX == bossX + 2 && playerY == bossY) && bossHp > 0)
                                        {
                                            isFight = true;
                                            Console.SetCursorPosition(2, h - 5);
                                            Console.ForegroundColor = ConsoleColor.White;
                                            Console.Write("你攻击了BOSS, 按J继续");
                                            Console.SetCursorPosition(2, h - 4);
                                            Console.Write("玩家当前血量为{0}", playerHp);
                                            Console.SetCursorPosition(2, h - 3);
                                            Console.Write("boss当前血量为{0}", bossHp);
                                        }
                                        else if ((playerX == princessX && playerY == princessY - 1 ||
                                                  playerX == princessX && playerY == princessY + 1 ||
                                                  playerX == princessX - 2 && playerY == princessY ||
                                                  playerX == princessX + 2 && playerY == princessY) && bossHp <= 0)
                                        {
                                            nowSceneID = 3;
                                            gameOverInfo = "你成功营救公主";
                                            isOver = true;
                                            break;
                                        }
                                        break; 
                                    
                                }
                                #endregion 
                            }
                            if (isOver)
                                break;

                            #endregion
                        }
                        break;
                    case 3:

                        #region 结束场景逻辑

                        Console.Clear();
                        Console.SetCursorPosition(w / 2 - 4, 5);
                        Console.ForegroundColor = ConsoleColor.White;
                        Console.Write("恭喜你，你赢了");
                        Console.SetCursorPosition(w / 2 - 4, 7);
                        Console.ForegroundColor = ConsoleColor.Gray;
                        Console.Write(gameOverInfo);

                        int nowSelEndIndex = 0;
                        while (true)
                        {
                            bool isQuitEndWhile = false;
                            Console.SetCursorPosition(w / 2 - 6, 9);
                            Console.ForegroundColor = nowSelEndIndex == 0 ? ConsoleColor.Red : ConsoleColor.White;
                            Console.Write("回到开始界面");
                            Console.SetCursorPosition(w / 2 - 6, 11);
                            Console.ForegroundColor = nowSelEndIndex == 1 ? ConsoleColor.Red : ConsoleColor.White;
                            Console.Write("退出游戏");
                            
                            char input = Console.ReadKey(true).KeyChar;
                            switch (input)
                            {
                                case 'W':
                                case 'w':
                                    --nowSelEndIndex;
                                    if (nowSelEndIndex < 0)
                                        nowSelEndIndex = 0;
                                    break;
                                case 'S':
                                case 's':
                                    ++nowSelEndIndex;
                                    if (nowSelEndIndex > 1)
                                        nowSelEndIndex = 1;
                                    break;
                                case 'J':
                                case 'j':
                                    if (nowSelEndIndex == 0)
                                    {
                                        nowSceneID = 1;
                                        gameOverInfo = "";
                                        isQuitEndWhile = true;
                                    }
                                    else
                                    {
                                        Environment.Exit(0);
                                    }
                                    break;
                            }
                            if (isQuitEndWhile)
                                break;
                        }

                        #endregion
                        break;
                }
            }

            #endregion
        }
    }
}

