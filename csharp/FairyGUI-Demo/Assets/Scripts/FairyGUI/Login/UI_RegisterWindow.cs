/** This is an automatically generated class by FairyGUI. Please do not modify it. **/

using FairyGUI;
using FairyGUI.Utils;

namespace Login
{
    public partial class UI_RegisterWindow : GComponent
    {
        public GTextInput m_inputAN;
        public GTextInput m_inputPW;
        public GButton m_btnClose;
        public GButton m_btnSure;
        public Transition m_show;
        public Transition m_hide;
        public const string URL = "ui://ffsx6r1gea6c7";

        public static UI_RegisterWindow CreateInstance()
        {
            return (UI_RegisterWindow)UIPackage.CreateObject("Login", "RegisterWindow");
        }

        public override void ConstructFromXML(XML xml)
        {
            base.ConstructFromXML(xml);

            m_inputAN = (GTextInput)GetChild("inputAN");
            m_inputPW = (GTextInput)GetChild("inputPW");
            m_btnClose = (GButton)GetChild("btnClose");
            m_btnSure = (GButton)GetChild("btnSure");
            m_show = GetTransition("show");
            m_hide = GetTransition("hide");
        }
    }
}