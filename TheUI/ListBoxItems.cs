using System;
using System.Collections.ObjectModel;
using System.Windows;
using System.Windows.Controls;

namespace TheUI
{
    public partial class wintouch : Page
    {
        public static ObservableCollection<LogEntry> LogEntries { get; set; }
        public static ObservableCollection<string> MacroNames { get; set; }
        public static ObservableCollection<string> ScreenNames { get; set; }
        public static ObservableCollection<string> ClickNames { get; set; }
        public static ObservableCollection<string> DragNames { get; set; }

        public void AddDung(string name)
        {
            Application.Current.Dispatcher.Invoke((Action)delegate
            {
                MacroNames.Add(name);
                if (name == selectedMacroName)
                {
                    int idx = 0;
                    foreach (var item in lbxMacroName.Items)
                    {
                        if (item.ToString() == name)
                        {
                            break;
                        }
                        idx++;
                    }
                    lbxMacroName.SelectedIndex = idx;
                }
            });
        }

        public void AddScreen(string name)
        {
            Application.Current.Dispatcher.Invoke((Action)delegate
            {
                ScreenNames.Add(name);
                if (name == selectedScreenName)
                {
                    int idx = 0;
                    foreach (var item in lbxScreen.Items)
                    {
                        if (item.ToString() == name)
                        {
                            break;
                        }
                        idx++;
                    }
                    lbxScreen.SelectedIndex = idx;
                }
            });
        }

        public void AddClick(string name)
        {
            Application.Current.Dispatcher.Invoke((Action)delegate
            {
                ClickNames.Add(name);
                if (name == selectedClickName)
                {
                    int idx = 0;
                    foreach (var item in lbxClick.Items)
                    {
                        if (item.ToString() == name)
                        {
                            break;
                        }
                        idx++;
                    }
                    lbxClick.SelectedIndex = idx;
                }
            });
        }

        public void AddDrag(string name)
        {
            Application.Current.Dispatcher.Invoke((Action)delegate
            {
                DragNames.Add(name);
                if (name == selectedDragName)
                {
                    int idx = 0;
                    foreach (var item in lbxDrag.Items)
                    {
                        if (item.ToString() == name)
                        {
                            break;
                        }
                        idx++;
                    }
                    lbxDrag.SelectedIndex = idx;
                }
            });
        }

        private void Clear_Log(object sender, RoutedEventArgs e)
        {
            LogEntries.Clear();
        }

        public void Log(string msg)
        {
            DateTime time = DateTime.Now;
            string timeString = time.Hour.ToString() + ":";
            if (time.Minute <= 9) timeString += "0";
            timeString += time.Minute.ToString() + ":";
            if (time.Second <= 9) timeString += "0";
            timeString += time.Second.ToString() + "  ";

            Application.Current.Dispatcher.Invoke((Action)delegate
            {
                LogEntries.Add(new LogEntry() { Index = index++, DateTime = timeString, Message = msg });
            });
        }

        public void ClearLists()
        {
            Application.Current.Dispatcher.Invoke((Action)delegate
            {
                DragNames.Clear();
                ClickNames.Clear();
                ScreenNames.Clear();
                MacroNames.Clear();
            });
        }
    }
}
