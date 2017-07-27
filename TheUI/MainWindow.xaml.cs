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

        public ObservableCollection<LogEntry> LogEntries { get; set; }

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
            LogEntries.Add(new LogEntry() { Index = index++, DateTime = timeString, Message = msg });
        }

        private void Init()
        {
            DataContext = LogEntries = new ObservableCollection<LogEntry>();
        }
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
}
