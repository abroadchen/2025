using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Lesson2 : MonoBehaviour
{
    public Texture2D tex;
    // Start is called before the first frame update
    void Start()
    {
        Cursor.visible = false;
        //限制在窗口范围内 Confined
        Cursor.lockState = CursorLockMode.Locked;//还会隐藏 ESC解除
        Cursor.SetCursor(tex, Vector2.zero, CursorMode.Auto);
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
