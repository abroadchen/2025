using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Lesson1_Mathf : MonoBehaviour
{
    public Transform target;
    public AudioSource audioS;
    public Texture tex;
    public Material m;
    // Start is called before the first frame update
    void Start()
    {
        print(Mathf.CeilToInt(1.1f));
        print(Mathf.FloorToInt(1.1f));
        print(Mathf.Clamp(1.1f, 0, 1));//钳制函数
        print(Mathf.Max(1, 2, 3, 4));
        print(Mathf.RoundToInt(1.1f));//四舍五入
        print(Mathf.IsPowerOfTwo(4));//判断是否为2的幂
        print(Mathf.Sign(0));//判断正负

        float rad = 1;
        float anger = rad * Mathf.Rad2Deg;
        print(anger);
        anger = 1;
        rad = anger * Mathf.Deg2Rad;


        print(Mathf.Sin(30 * Mathf.Deg2Rad));//参数是弧度
        rad = Mathf.Asin(0.5f);//得到弧度

        //magnitude 模长
        //normalized 单位向量  进行移动计算

        //位置+向量=位置 向量+位置=位置  平移位置
        //位置-位置=向量
        //位置+(-向量) = 位置
        //向量乘除 主要用于模长缩放

        //向量·向量 = 标量   xa * xb + ya * yb + za * zb
        //在自己向量上的投影长度 判断敌方的大致方位
        Debug.DrawLine(transform.position, transform.position + transform.forward, Color.red);
        Debug.DrawRay(transform.position, transform.right, Color.green);
        //Mathf.Acos(点乘结果)*Mathf.Rad2Deg
        //Vector3.Angle() 都可以算出两个向量的夹角

        //x=yazb-zayb y=zaxb-xazb z=xayb-yaxb
        //axb y>0 b在a的右侧 y<0 b在a的左侧

        //heading Y
        //pitch X
        //bank Z
        //同一旋转的表示不唯一 万向节死锁
        //[标量,3D向量]
        //绕n轴 旋转β
        //[cos(β/2),sin(β/2)n]
        //[cos(β/2), sin(β/2)x, sin(β/2)y, sin(β/2)z]
        //new Quaternion(sin(β/2)x, sin(β/2)y, sin(β/2)z, cos(β/2)) 
        //Quaternion.AngleAxis(角度,轴)
        //Quaternion.Euler(x,y,z) 欧拉角转四元
        //Quaternion q;
        //q.eulerAngles 四元转欧拉角
        //四元数相乘 旋转四元数

        //单位四元数 没有旋转量(角位移) 对象角度初始化
        //Quaternion.identity
        //插值运算 平滑旋转
        //向量指向转四元 让对象朝向某个方向
        //Quaternion.LookRotation(面朝向量)

        //延迟函数
        //Invoke("函数名", 延迟时间) //必须是本脚本的函数
        //有参数的包裹在无参的函数中调用
        //InvokeRepeating("函数名", 延迟时间, 间隔时间)
        //CancelInvoke() 取消所有
        //IsInvoking() 判断是否正在执行某个函数
        //脚本依附的对象失活/脚本自己失活 都不影响执行

        //新开的线程无法访问Unity相关对象的内容 记得关闭
        //声明一个变量作为公共内存容器

        //协程 代码分时执行 在原线程上开启
        //返回值 IEnumerator类型及其子类 yield return
        //StartCoroutine(函数) 启动协程

        //在Update和LateUpdate之间执行
        // 数字|null  下一帧执行
        // new WaitForSeconds(1)
        // new WaitForFixedUpdate() FixedUpdate和碰撞检测相关函数之后执行
        // new WaitForEndOfFrame() LateUpdate之后的渲染相关处理完成后 截图
        // yield break 跳出当前协程 后面的都不会执行
        // 组件失活协程执行

        //能够中间暂停返回的函数
        //IEnumerator ie = 函数();
        //ie.MoveNext();
        //ie.Current;

        //工程路径 Application.dataPath
        //Resource都会打包
        //Application.streamingAssetsPath 不会被压缩加密 移动平台只读 自定义动态加载的初始资源
        //Application.persistentDataPath 动态下载或动态创建的文件
        //Editor 编辑器相关的脚本


        //预设体对象 GameObject 加载需要实例化
        //音效文件 AudioClip
        //文本文件 TextAsset .txt .xml .bytes .json .html  .csv
        //图片文件 Texture
        UnityEngine.Object obj = Resources.Load("Prefabs/Cube");
        Instantiate(obj);

        audioS.clip = obj as AudioClip;


        ResourceRequest request = Resources.LoadAsync<Texture>("Prefabs/Cube");
        request.completed += LoadOver;

        StartCoroutine(Load());


        //Resources.UnloadAsset 不能释放GameObject对象
        Resources.UnloadUnusedAssets();
        GC.Collect();

        //场景切换 Build Settings->Scenes in Build -> 添加场景
        AsyncOperation ao = SceneManager.LoadSceneAsync("NewScene");
        ao.completed += (a) => { };

        StartCoroutine(LoadScene("NewScene"));
        DontDestroyOnLoad(gameObject);//该脚本依附的对象过场景不被移除





        //Loop 终点和起点自动相连
        GameObject line = new GameObject("Line");
        LineRenderer lr = line.AddComponent<LineRenderer>();
        m = Resources.Load<Material>("Material");
        lr.material = m;
        lr.positionCount = 2;
        lr.SetPositions(new Vector3[2] { startPos, nowTarget });


        //范围检测必要条件 碰撞器
        //Physics.OverlapBox()
        //参数1 立方体中心点
        //参数2 三边大小
        //参数3 角度
        //参数4 检测层级
        //参数5 是否忽略触发器 默认UseGlobal
        //返回值 在该范围内的触发器
        //Physics.OverlapBoxNonAlloc()
        //参数 传入一个数组进行存储
        //返回值 碰撞到的碰撞器数量

        //Ray r = new Ray(起点,方向)
        //r.origin 起点
        //r.direction 方向
        //Ray r2 = Camera.main.ScreenPointToRay(Input.mousePosition);
        //Physics.Raycast(r,out RaycastHit hit,1000,1<<8);
        //参数1 射线
        //参数2 检测的最大距离
        //参数3 检测的层级
        //参数4 是否忽略触发器
        //返回值 bool

        //RaycastHit hit; 物体信息类
        //参数1 射线
        //参数2 结构体
        //参数3 距离
        //参数4 检测的层级
        //参数5 是否忽略触发器
    }

    private void LoadOver(AsyncOperation operation)//线性加载
    {
        tex = (operation as ResourceRequest).asset as Texture;
    }

    private void OnGUI()
    {
        if (tex != null)
        {
            GUI.DrawTexture(new Rect(0, 0, 100, 100), tex);
        }
    }

    IEnumerator Load()//并行加载
    {
        ResourceRequest request = Resources.LoadAsync<Texture>("Prefabs/Cube");
        yield return request;
        tex = request.asset as Texture;

        // while (!request.isDone)
        // {
        //     print(request.progress); //进度 不准确 
        //     yield return null; //每帧都判断
        // }
    }

    IEnumerator LoadScene(string name)
    {
        AsyncOperation ao = SceneManager.LoadSceneAsync(name);
        yield return ao; 
    }

    float start = 0;
    float result = 0;
    float time = 0;
    private Vector3 nowTarget;
    private Vector3 startPos;
    private Transform B;
    // Update is called once per frame
    void Update()
    {
        start = Mathf.Lerp(start, 10, Time.deltaTime);//先快后慢
        //result = start + (end - start) * t;
        //跟随移动 摄像机跟随

        if (nowTarget != target.position)
        {
            nowTarget = target.position;
            time = 0;
            startPos = B.position;
        }
        time += Time.deltaTime;
        B.position = Vector3.Lerp(startPos, nowTarget, time);//匀速变化
        //Slerp球形插值 曲线运动
    }
}
