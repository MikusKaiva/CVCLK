using System;
using System.Collections.ObjectModel;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;

namespace TheUI
{
    public partial class wintouch : Page
    {
        private int index;
        public static ObservableBool PanelEnabled { get; set; }
        public static ObservableControlStates ControlStates { get; set; }
        private static string selectedMacroName, selectedScreenName, selectedClickName, selectedDragName;

        public wintouch()
        {
            if (null == System.Windows.Application.Current)
            {
                new System.Windows.Application();
            }
            InitializeComponent();
            Init();
        }
        public wintouch(int w, int h)
        {
            if (null == System.Windows.Application.Current)
            {
                new System.Windows.Application();
            }
            InitializeComponent();
            Width = w;
            Height = h;
            Init();
        }

        public void EnablePanel()
        {
            Application.Current.Dispatcher.Invoke( (Action)delegate { PanelEnabled.Value = true; } );
        }

        public void DisablePanel()
        {
            Application.Current.Dispatcher.Invoke((Action)delegate { PanelEnabled.Value = false; });
        }     

        public void SetState(ObservableControlStates.StateEnum state)
        {
            ControlStates.State = state;
        }

        private void Init()
        {
            DataContext = LogEntries = new ObservableCollection<LogEntry>();
            lbxMacroName.DataContext = MacroNames = new ObservableCollection<string>();
            lbxScreen.DataContext = ScreenNames = new ObservableCollection<string>();
            lbxClick.DataContext = ClickNames = new ObservableCollection<string>();
            lbxDrag.DataContext = DragNames = new ObservableCollection<string>();
            PanelEnabled = new ObservableBool() { Value = false };
            ControlStates = new ObservableControlStates { State = ObservableControlStates.StateEnum.Stopped };
        }

        private void lbxClick_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            string val = (string)lbxClick.SelectedValue;
            if (val != null && val.Length != 0)
                selectedClickName = (string)lbxClick.SelectedValue;
        }

        private void lbxDrag_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            string val = (string)lbxDrag.SelectedValue;
            if (val != null && val.Length != 0)
                selectedDragName = (string)lbxDrag.SelectedValue;
        }

        private void lbxMacroName_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            string val = (string)lbxMacroName.SelectedValue;
            if (val != null && val.Length != 0)
                selectedMacroName = (string)lbxMacroName.SelectedValue;
        }

        private void lbxScreen_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            string val = (string)lbxScreen.SelectedValue;
            if (val != null && val.Length != 0)
                selectedScreenName = (string)lbxScreen.SelectedValue;
        }
    }

}
