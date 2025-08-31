/** This is an automatically generated class by FairyGUI. Please do not modify it. **/

using FairyGUI;
using FairyGUI.Utils;

namespace Login
{
    public partial class UI_LoginWindow : GComponent
    {
        public GTextInput m_inputAN;
        public GTextInput m_inputPW;
        public GButton m_cbPW;
        public GButton m_cbAuto;
        public GButton m_btnRe;
        public GButton m_btnSure;
        public Transition m_show;
        public Transition m_hide;
        public Transition m_t2;
        public const string URL = "ui://ffsx6r1gea6c4";

        public static UI_LoginWindow CreateInstance()
        {
            return (UI_LoginWindow)UIPackage.CreateObject("Login", "LoginWindow");
        }

        public override void ConstructFromXML(XML xml)
        {
            base.ConstructFromXML(xml);

            m_inputAN = (GTextInput)GetChild("inputAN");
            m_inputPW = (GTextInput)GetChild("inputPW");
            m_cbPW = (GButton)GetChild("cbPW");
            m_cbAuto = (GButton)GetChild("cbAuto");
            m_btnRe = (GButton)GetChild("btnRe");
            m_btnSure = (GButton)GetChild("btnSure");
            m_show = GetTransition("show");
            m_hide = GetTransition("hide");
            m_t2 = GetTransition("t2");
        }
    }
}