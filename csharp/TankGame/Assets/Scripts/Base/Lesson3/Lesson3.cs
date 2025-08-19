using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

public class Lesson3 : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        int randomNum = Random.Range(0, 100);
        float randomNumF = Random.Range(0f, 100f);//左右都包含
        UnityAction uac = () => { };
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
