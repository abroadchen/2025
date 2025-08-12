public class ScenesMgr : BaseManager<ScenesMgr>
{
    public void LoadScene(string name, UnityAction fun)
    {
        SceneManager.LoadScene(name);
        fun();
    }

    public void LoadSceneAsyn(string name, UnityAction fun)
    {
        MonoMgr.GetInstance().StartCoroutine(ReallyLoadSceneAsyn(name, fun));
    }

    private IEnumerator ReallyLoadSceneAsyn(string name, UnityAction fun)
    {
        AsyncOperation ao = SceneManager.LoadSceneAsync(name);
        while (!ao.isDone)
        {
            EventCenter.GetInstance().EventTrigger("进度条更新", ao.progress);
            yield return ao.progress;
        }
        fun();
    }
}
