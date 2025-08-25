using System.Collections;
using System.Collections.Generic;
using UnityEngine;
[ExecuteAlways]
public class CustomGUIRoot : MonoBehaviour
{
    CustomGUIControl[] allControls;
    // Start is called before the first frame update
    void Start()
    {
        allControls = GetComponentsInChildren<CustomGUIControl>();       
    }

    void OnGUI()
    {
        // if (!Application.isPlaying)
            allControls = GetComponentsInChildren<CustomGUIControl>();
        for (var i = 0; i < allControls.Length; i++)
        {
            allControls[i].DrawGUI();
        }
    }
}
