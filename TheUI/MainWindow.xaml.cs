using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Windows;
using System.Windows.Controls;

namespace TheUI
{
    public partial class wintouch : Page
    {
        private int index;

        public static ObservableCollection<LogEntry> LogEntries { get; set; }
        public static ObservableCollection<string> MacroNames { get; set; }

        public wintouch()
        {
            InitializeComponent();
            Init();
        }
        public wintouch(int w, int h)
        {
            InitializeComponent();
            Width = w;
            Height = h;
            Init();
        }

        public void Log(string msg)
        {
            DateTime time = DateTime.Now;
            string timeString = time.Hour.ToString() + ":";
            if (time.Minute <= 9) timeString += "0";
            timeString += time.Minute.ToString() + ":";
            if (time.Second <= 9) timeString += "0";
            timeString += time.Second.ToString() + "  ";
            if (null == System.Windows.Application.Current)
            {
                new System.Windows.Application();
            }
            Application.Current.Dispatcher.Invoke((Action)delegate
            {
                LogEntries.Add(new LogEntry() { Index = index++, DateTime = timeString, Message = msg });
                MacroNames.Add(timeString);
            });
            
        }

        private void Init()
        {
            DataContext = LogEntries = new ObservableCollection<LogEntry>();
            lbxMacroName.DataContext = MacroNames = new ObservableCollection<string>();
        }

        public Button GetBtn()
        {
            return btnStopMacro;
        }
    }

    public class MacroName : PropertyChangedBase
    {
        public string Value { get; set; }
    }

    public class LogEntry : PropertyChangedBase
    {
        public string DateTime { get; set; }
        public int Index { get; set; }
        public string Message { get; set; }
    }

    public class CollapsibleLogEntry : LogEntry
    {
        public List<LogEntry> Contents { get; set; }
    }

    public class PropertyChangedBase : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        protected virtual void OnPropertyChanged(string propertyName)
        {
            Application.Current.Dispatcher.BeginInvoke((Action)(() =>
            {
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
            }));
        }
    }

    public static class AutoScrollHelper
    {
        public static readonly DependencyProperty AutoScrollProperty =
            DependencyProperty.RegisterAttached("AutoScroll", typeof(bool), typeof(AutoScrollHelper), new PropertyMetadata(false, AutoScrollPropertyChanged));


        public static void AutoScrollPropertyChanged(DependencyObject obj, DependencyPropertyChangedEventArgs args)
        {
            var scrollViewer = obj as ScrollViewer;
            if (scrollViewer == null) return;

            if ((bool)args.NewValue)
            {
                scrollViewer.ScrollChanged += ScrollViewer_ScrollChanged;
                scrollViewer.ScrollToEnd();
            }
            else
            {
                scrollViewer.ScrollChanged -= ScrollViewer_ScrollChanged;
            }
        }

        static void ScrollViewer_ScrollChanged(object sender, ScrollChangedEventArgs e)
        {
            if (e.ViewportHeightChange > 0 || e.ExtentHeightChange > 0 || e.ViewportHeightChange < 0 || e.ExtentHeightChange < 0)
            {
                var scrollViewer = sender as ScrollViewer;
                scrollViewer?.ScrollToEnd();
            }
        }

        public static bool GetAutoScroll(DependencyObject obj)
        {
            return (bool)obj.GetValue(AutoScrollProperty);
        }

        public static void SetAutoScroll(DependencyObject obj, bool value)
        {
            obj.SetValue(AutoScrollProperty, value);
        }
    }
}
