/** This is an automatically generated class by FairyGUI. Please do not modify it. **/

using FairyGUI;
using FairyGUI.Utils;

namespace Login
{
    public partial class UI_ServerChooseWindow : GComponent
    {
        public GTextField m_txtName;
        public GLoader m_imgState;
        public GTextField m_txtRange;
        public GList m_listLeft;
        public GList m_listRight;
        public Transition m_show;
        public Transition m_hide;
        public const string URL = "ui://ffsx6r1gtwkm1g";

        public static UI_ServerChooseWindow CreateInstance()
        {
            return (UI_ServerChooseWindow)UIPackage.CreateObject("Login", "ServerChooseWindow");
        }

        public override void ConstructFromXML(XML xml)
        {
            base.ConstructFromXML(xml);

            m_txtName = (GTextField)GetChild("txtName");
            m_imgState = (GLoader)GetChild("imgState");
            m_txtRange = (GTextField)GetChild("txtRange");
            m_listLeft = (GList)GetChild("listLeft");
            m_listRight = (GList)GetChild("listRight");
            m_show = GetTransition("show");
            m_hide = GetTransition("hide");
        }
    }
}