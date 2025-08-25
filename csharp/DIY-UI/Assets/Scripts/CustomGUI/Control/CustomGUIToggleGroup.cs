using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CustomGUIToggleGroup : MonoBehaviour
{
    public CustomGUIToggle[] toggles;
    CustomGUIToggle frontTurTog;
    // Start is called before the first frame update
    void Start()
    {
        if (toggles.Length == 0) return;
        for (var i = 0; i < toggles.Length; i++)
        {
            CustomGUIToggle toggle = toggles[i];
            toggle.changeValue += (value) =>
            {
                if (value)
                {
                    for (var j = 0; j < toggles.Length; j++)
                    {
                        if (toggles[j] != toggle)
                        {
                            toggles[j].isSel = false;
                        }
                    }
                    frontTurTog = toggle;
                }
                else if (toggle == frontTurTog)
                {
                    toggle.isSel = true;
                }
            };
        }
    }

}
