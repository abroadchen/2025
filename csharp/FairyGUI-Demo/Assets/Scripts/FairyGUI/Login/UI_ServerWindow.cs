/** This is an automatically generated class by FairyGUI. Please do not modify it. **/

using FairyGUI;
using FairyGUI.Utils;

namespace Login
{
    public partial class UI_ServerWindow : GComponent
    {
        public GButton m_btnBegin;
        public GButton m_btnChange;
        public GTextField m_txtName;
        public GButton m_btnClose;
        public Transition m_show;
        public Transition m_hide;
        public const string URL = "ui://ffsx6r1gtwkm1e";

        public static UI_ServerWindow CreateInstance()
        {
            return (UI_ServerWindow)UIPackage.CreateObject("Login", "ServerWindow");
        }

        public override void ConstructFromXML(XML xml)
        {
            base.ConstructFromXML(xml);

            m_btnBegin = (GButton)GetChild("btnBegin");
            m_btnChange = (GButton)GetChild("btnChange");
            m_txtName = (GTextField)GetChild("txtName");
            m_btnClose = (GButton)GetChild("btnClose");
            m_show = GetTransition("show");
            m_hide = GetTransition("hide");
        }
    }
}