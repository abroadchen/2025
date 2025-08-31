/** This is an automatically generated class by FairyGUI. Please do not modify it. **/

using FairyGUI;
using FairyGUI.Utils;

namespace Login
{
    public partial class UI_TipWindow : GComponent
    {
        public UI_WindowTip m_frame;
        public Transition m_show;
        public Transition m_hide;
        public const string URL = "ui://ffsx6r1gea6c0";

        public static UI_TipWindow CreateInstance()
        {
            return (UI_TipWindow)UIPackage.CreateObject("Login", "TipWindow");
        }

        public override void ConstructFromXML(XML xml)
        {
            base.ConstructFromXML(xml);

            m_frame = (UI_WindowTip)GetChild("frame");
            m_show = GetTransition("show");
            m_hide = GetTransition("hide");
        }
    }
}