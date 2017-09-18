using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;

namespace TheUI
{
    public partial class wintouch : Page
    {
        public string GetSelectedDungName()
        {
            string ret = "";
            Application.Current.Dispatcher.Invoke((Action)delegate { ret = (string)lbxMacroName.SelectedValue; });
            return ret;
        }

        public string GetSelectedScreenName()
        {
            string ret = "";
            Application.Current.Dispatcher.Invoke((Action)delegate { ret = (string)lbxScreen.SelectedValue; });
            return ret;
        }

        public string GetSelectedClickName()
        {
            string ret = "";
            Application.Current.Dispatcher.Invoke((Action)delegate { ret = (string)lbxClick.SelectedValue; });
            return ret;
        }

        public string GetSelectedDragName()
        {
            string ret = "";
            Application.Current.Dispatcher.Invoke((Action)delegate { ret = (string)lbxDrag.SelectedValue; });
            return ret;
        }

        public ObservableControlStates.StateEnum GetState()
        {
            return ControlStates.State;
        }

        public Button GetStopBtn()
        {
            return btnStopMacro;
        }

        public ToggleButton GetRunPauseMacroBtn()
        {
            return btnRunMacro;
        }

        public Button GetShowScreenBtn()
        {
            return btnShowScreen;
        }

        public Button GetShowClickBtn()
        {
            return btnShowClick;
        }

        public Button GetShowDragBtn()
        {
            return btnShowDrag;
        }

        public string GetShowScreenBtnName()
        {
            string ret = "";
            Application.Current.Dispatcher.Invoke((Action)delegate { ret = btnShowScreen.Name; });
            return ret;
        }

        public string GetShowClickBtnName()
        {
            string ret = "";
            Application.Current.Dispatcher.Invoke((Action)delegate { ret = btnShowClick.Name; });
            return ret;
        }

        public string GetShowDragBtnName()
        {
            string ret = "";
            Application.Current.Dispatcher.Invoke((Action)delegate { ret = btnShowDrag.Name; });
            return ret;
        }

        public Button GetReloadBtn()
        {
            return btnReload;
        }
    }
}
