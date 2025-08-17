// See https://aka.ms/new-console-template for more information

//Console.WriteLine("Hello, World!");

namespace FlyingChess;

class Program 
{
    static void Main(string[] args)
    {
        #region 控制台初始化

        int w = 50;
        int h = 20;
        ConsoleInit(w, h);

        #endregion

        #region 场景选择相关
        E_SceneType sceneType = E_SceneType.Begin;
        while (true)
        {
            switch (sceneType)
            {
                case E_SceneType.Begin:
                    Console.Clear();
                    BeginOrEndScene(w, h,ref sceneType);
                    break;
                case E_SceneType.Game:
                    Console.Clear();
                    GameScene(w, h, ref sceneType);
                    break;
                case E_SceneType.End:
                    Console.Clear();
                    BeginOrEndScene(w, h, ref sceneType);
                    break;
            }
        }

        #endregion
    }

    #region 控制台初始化

    static void ConsoleInit(int w, int h)
    {
        Console.CursorVisible = false;
        Console.SetWindowSize(w, h);
        Console.SetBufferSize(w, h);
    }

    #endregion

    #region 开始场景逻辑

    static void BeginOrEndScene(int w, int h, ref E_SceneType nowSceneType)
    {
        Console.ForegroundColor = ConsoleColor.White;
        Console.SetCursorPosition(nowSceneType == E_SceneType.Begin ? w / 2 - 3 : w / 2 - 4, 8);
        Console.Write(nowSceneType == E_SceneType.Begin ? "飞行棋" : "游戏结束");

        int nowSelIndex = 0;
        bool isQuitBegin = false;
        while (true)
        {
            Console.SetCursorPosition(nowSceneType == E_SceneType.Begin ? w / 2 - 4 : w / 2 - 5, 13);
            Console.ForegroundColor = nowSelIndex == 0 ? ConsoleColor.Red : ConsoleColor.White;
            Console.Write(nowSceneType == E_SceneType.Begin ? "开始游戏" : "回到主菜单");
            Console.SetCursorPosition(w / 2 - 4, 15);
            Console.ForegroundColor = nowSelIndex == 1 ? ConsoleColor.Red : ConsoleColor.White;
            Console.Write("结束游戏");
            switch (Console.ReadKey(true).Key)
            {
                case ConsoleKey.W:
                    --nowSelIndex;
                    if (nowSelIndex < 0)
                        nowSelIndex = 0;
                    break;
                case ConsoleKey.S:
                    ++nowSelIndex;
                    if (nowSelIndex > 1)
                        nowSelIndex = 1;
                    break;
                case ConsoleKey.J:
                    if (nowSelIndex == 0)
                    {
                        nowSceneType = nowSceneType == E_SceneType.Begin ? E_SceneType.Game : E_SceneType.Begin;
                        isQuitBegin = true;
                    }
                    else
                    {
                        Environment.Exit(0);
                    }
                    break;
            }
            if (isQuitBegin)
                break;
        }
    }

    #endregion
    
    #region 游戏场景逻辑
    
    static void GameScene(int w, int h, ref E_SceneType nowSceneType)
    {
        DrawWall(w, h);
        Map map = new Map(14, 3, 80);
        map.Draw();
        Player player = new Player(0, E_PlayerType.Player);
        Player computer = new Player(0, E_PlayerType.Computer);
        DrawPlayer(player, computer, map);

        bool isGameOver = false;
        while (true)
        {
            if (PlayerRandomMove(w, h, ref player, ref computer, map, ref nowSceneType))
                break;
            if (PlayerRandomMove(w, h, ref computer, ref player, map, ref nowSceneType))
                break;
        }
    }
    #endregion

    static bool PlayerRandomMove(int w, int h, ref Player p, ref Player p2, Map map, ref E_SceneType nowSceneType)
    {
        Console.ReadKey(true);
        bool isGameOver = RandomMove(w, h, ref p, ref p2, map);
        map.Draw();
        DrawPlayer(p, p2, map);
        if (isGameOver)
        {
            Console.ReadKey(true);
            nowSceneType = E_SceneType.End;
        }

        return isGameOver;
    }

    #region 绘制不变内容

    static void DrawWall(int w, int h)
    {
        Console.ForegroundColor = ConsoleColor.Red;
        for (int i = 0; i < w; i += 2)
        {
            Console.SetCursorPosition(i, 0);
            Console.Write("■");
            Console.SetCursorPosition(i, h - 1);
            Console.Write("■");
            Console.SetCursorPosition(i, h - 6);
            Console.Write("■");
            Console.SetCursorPosition(i, h - 11);
            Console.Write("■");
        }

        for (int i = 0; i < h; i++)
        {
            Console.SetCursorPosition(0, i);
            Console.Write("■");
            Console.SetCursorPosition(w - 2, i);
            Console.Write("■");
        }
        
        Console.ForegroundColor = ConsoleColor.White;
        Console.SetCursorPosition(2, h - 10);
        Console.Write("□: 普通格子");//v1
        Console.ForegroundColor = ConsoleColor.Blue;
        Console.SetCursorPosition(2, h - 9);
        Console.Write("‖: 暂停一回合");//v1
        Console.ForegroundColor = ConsoleColor.Red;
        Console.SetCursorPosition(26, h - 9);
        Console.Write("●: 倒退5格");//v1
        Console.ForegroundColor = ConsoleColor.Yellow;
        Console.SetCursorPosition(2, h - 8);
        Console.Write("¤: 随机倒退 暂停 互换位置");//v1
        Console.ForegroundColor = ConsoleColor.Cyan;
        Console.SetCursorPosition(2, h - 7);
        Console.Write("★: 玩家");//v1
        Console.ForegroundColor = ConsoleColor.Magenta;
        Console.SetCursorPosition(12, h - 7);
        Console.Write("▲: 电脑");//v1
        Console.ForegroundColor = ConsoleColor.DarkGreen;
        Console.SetCursorPosition(22, h - 7);
        Console.Write("◎: 玩家和电脑重合");//v1
        Console.ForegroundColor = ConsoleColor.White;
        Console.SetCursorPosition(2, h - 5);
        Console.Write("按任意键开始扔色子");//v1
    }

    #endregion

    #region 绘制玩家

    static void DrawPlayer(Player player, Player computer, Map map)
    {
        if (player.nowIndex == computer.nowIndex)
        {
            Grid grid = map.grids[player.nowIndex];
            Console.SetCursorPosition(grid.pos.x, grid.pos.y);
            Console.ForegroundColor = ConsoleColor.DarkGreen;
            Console.Write("◎");
        }
        else
        {
            player.Draw(map);
            computer.Draw(map); 
        }
    }

    #endregion

    #region 清除显示内容

    static void ClearInfo(int h)
    {
        Console.SetCursorPosition(2, h - 5);
        Console.Write("                                   ");
        Console.SetCursorPosition(2, h - 4);
        Console.Write("                                   ");
        Console.SetCursorPosition(2, h - 3);
        Console.Write("                                   ");
        Console.SetCursorPosition(2, h - 2);
        Console.Write("                                   "); 
    }

    #endregion

    #region 扔色子逻辑

    static bool RandomMove(int w, int h, ref Player p, ref Player p2, Map map)
    {
        
        ClearInfo(h);
        Console.ForegroundColor = p.type == E_PlayerType.Player ? ConsoleColor.Cyan : ConsoleColor.Magenta;
        
        if (p.isPause)
        {
            Console.SetCursorPosition(2, h - 5);
            Console.Write("{0}需要暂停一回合", p.type == E_PlayerType.Player ? "你" : "电脑");
            Console.SetCursorPosition(2, h - 4);
            Console.Write("让{0}扔色子", p.type == E_PlayerType.Player ? "电脑" : "你");
            p.isPause = false;
            return false;
        }
        
        
        Random r = new Random();
        int randomNum = r.Next(1, 7);
        p.nowIndex += randomNum;
        
        Console.SetCursorPosition(2, h - 5);
        Console.Write("{0}扔出的点数为:{1}", p.type == E_PlayerType.Player ? "你" : "电脑", randomNum);
        if (p.nowIndex >= map.grids.Length - 1)
        {
            p.nowIndex = map.grids.Length - 1;
            Console.SetCursorPosition(2, h - 4);
            if (p.type == E_PlayerType.Player)
            {
                Console.Write("恭喜你获得胜利");
            }
            else
            {
                Console.Write("电脑获得胜利");
            }
            Console.SetCursorPosition(2, h - 3);
            Console.Write("按任意键继续");
            return true;
        }
        else
        {
            Grid grid = map.grids[p.nowIndex];
            switch (grid.type)
            {
                case E_Grid_Type.Normal:
                    Console.SetCursorPosition(2, h - 4);
                    Console.Write("{0}到达安全位置", p.type == E_PlayerType.Player ? "你" : "电脑");
                    Console.SetCursorPosition(2, h - 3);
                    Console.Write("让{0}扔色子", p.type == E_PlayerType.Player ? "电脑" : "你");
                    break;
                case E_Grid_Type.Boom:
                    p.nowIndex -= 5;
                    if (p.nowIndex < 0)
                        p.nowIndex = 0;
                    Console.SetCursorPosition(2, h - 4);
                    Console.Write("{0}踩到炸弹,退后5格", p.type == E_PlayerType.Player ? "你" : "电脑");
                    Console.SetCursorPosition(2, h - 3);
                    Console.Write("让{0}扔色子", p.type == E_PlayerType.Player ? "电脑" : "你");
                    break;
                case E_Grid_Type.Pause:
                    p.isPause = true;
                    Console.SetCursorPosition(2, h - 4);
                    Console.Write("{0}到达暂停点,等待1回合", p.type == E_PlayerType.Player ? "你" : "电脑");
                    Console.SetCursorPosition(2, h - 3);
                    Console.Write("让{0}扔色子", p.type == E_PlayerType.Player ? "电脑" : "你");
                    break;
                case E_Grid_Type.Tunnel:
                    
                    Console.SetCursorPosition(2, h - 4);
                    Console.Write("{0}掉入时空隧道", p.type == E_PlayerType.Player ? "你" : "电脑");
                    Console.SetCursorPosition(2, h - 3);
                    Console.Write("让{0}扔色子", p.type == E_PlayerType.Player ? "电脑" : "你");
                    
                    randomNum = r.Next(1, 91);
                    if (randomNum <= 30)
                    {
                        p.nowIndex -= 5;
                        if (p.nowIndex < 0)
                            p.nowIndex = 0;
                        Console.SetCursorPosition(2, h - 3);
                        Console.Write("触发倒退5格");
                    }
                    else if (randomNum <= 60)
                    {
                        p.isPause = true;
                        Console.SetCursorPosition(2, h - 3);
                        Console.Write("触发暂停1回合");
                    }
                    else
                    {
                        int temp = p.nowIndex;
                        p.nowIndex = p2.nowIndex;
                        p2.nowIndex = temp;
                        Console.SetCursorPosition(2, h - 3);
                        Console.Write("触发交换位置");
                    }
                    Console.SetCursorPosition(2, h - 2);
                    Console.Write("让{0}扔色子", p.type == E_PlayerType.Player ? "电脑" : "你");
                    break;
            }
        }
        return false;
    }

    #endregion
}

#region 场景选择相关

internal enum E_SceneType 
{
    Begin,
    Game,
    End
}

#endregion

#region 格子结构体和格子枚举

internal enum E_Grid_Type
{
    Normal,
    Boom,
    Pause,
    Tunnel
}

internal struct Vector2
{
    public int x;
    public int y;
    
    public Vector2(int x, int y)
    {
        this.x = x;
        this.y = y;
    }
}

internal struct Grid
{
    public E_Grid_Type type;
    public Vector2 pos;

    public Grid(int x, int y, E_Grid_Type type)
    {
        pos.x = x;
        pos.y = y;
        this.type = type;
    }

    public void Draw()
    {
        Console.SetCursorPosition(pos.x, pos.y);
        switch (type)
        {
            case E_Grid_Type.Normal:
                Console.ForegroundColor = ConsoleColor.White;
                Console.Write("□");
                break;
            case E_Grid_Type.Boom:
                Console.ForegroundColor = ConsoleColor.Red;
                Console.Write("●");
                break;
            case E_Grid_Type.Pause:
                Console.ForegroundColor = ConsoleColor.Blue;
                Console.Write("‖");
                break;
            case E_Grid_Type.Tunnel:
                Console.ForegroundColor = ConsoleColor.Yellow;
                Console.Write("¤");
                break;
        }
    }
}

#endregion

#region 地图结构体

internal struct Map
{
    public Grid[] grids;

    public Map(int x, int y, int num)
    {
        grids = new Grid[num];

        int indexX = 0;//计数
        int indexY = 0;
        int stepNum = 2;
        Random r = new Random();
        int randomNum;
        for (int i = 0; i < num; i++)
        {
            randomNum = r.Next(0, 101);
            if (randomNum < 85 || i == 0 || i == num - 1)
            {
                grids[i].type = E_Grid_Type.Normal;
            }
            else if (randomNum >= 85 && randomNum < 90)
            {
                grids[i].type = E_Grid_Type.Boom;
            }
            else if (randomNum >= 90 && randomNum < 95)
            {
                grids[i].type = E_Grid_Type.Pause;
            }
            else
            {
                grids[i].type = E_Grid_Type.Tunnel;
            }

            grids[i].pos = new Vector2(x, y);
            if (indexX == 10)
            {
                y += 1;
                ++indexY;
                if (indexY == 2)
                {
                    indexX = 0;
                    indexY = 0;
                    stepNum = -stepNum;
                }
            }
            else
            {
                x += stepNum;
                ++indexX;
            }
        }
    }

    public void Draw()
    {
        for (int i = 0; i < grids.Length; i++)
        {
            grids[i].Draw();
        }
    }
}

#endregion

#region 玩家枚举和玩家结构体

internal enum E_PlayerType
{
    Player,
    Computer
}

internal struct Player
{
    public E_PlayerType type;
    public int nowIndex;
    public bool isPause;

    public Player(int index, E_PlayerType type)
    {
        nowIndex = index;
        this.type = type;
        isPause = false;
    }

    public void Draw(Map mapInfo)
    {
        Grid grid = mapInfo.grids[nowIndex];
        Console.SetCursorPosition(grid.pos.x, grid.pos.y);
        switch (type)
        {
            case E_PlayerType.Player:
                Console.ForegroundColor = ConsoleColor.Cyan;
                Console.Write("★");
                break;
            case E_PlayerType.Computer:
                Console.ForegroundColor = ConsoleColor.Magenta;
                Console.Write("▲");
                break;
        }
    }
}

#endregion