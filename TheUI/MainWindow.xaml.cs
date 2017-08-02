using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;

namespace TheUI
{
    public partial class wintouch : Page
    {
        private int index;

        public static ObservableCollection<LogEntry> LogEntries { get; set; }
        public static ObservableCollection<string> MacroNames { get; set; }
        public static ObservableBool PanelEnabled { get; set; }

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

        public void EnablePanel()
        {
            Application.Current.Dispatcher.Invoke( (Action)delegate { PanelEnabled.Value = true; } );
        }

        public void AddDung(string name)
        {
            Application.Current.Dispatcher.Invoke((Action)delegate { MacroNames.Add(name); } );
        }

        public string GetSelectedDungName()
        {
            string ret = "";
            Application.Current.Dispatcher.Invoke((Action)delegate { ret = (string)lbxMacroName.SelectedValue; } );
            return ret;
        }

        private void Init()
        {
            DataContext = LogEntries = new ObservableCollection<LogEntry>();
            lbxMacroName.DataContext = MacroNames = new ObservableCollection<string>();
            PanelEnabled = new ObservableBool() { Value = false };
        }

        public Button GetBtn()
        {
            return btnStopMacro;
        }

        public ToggleButton GetRunPauseMacroBtn()
        {
            return btnRunMacro;
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            PanelEnabled.Value = false ;
        }

        private void btnStopMacro_Click(object sender, RoutedEventArgs e)
        {
            btnRunMacro.IsChecked = false;
        }
    }

    public class ObservableControlStates : PropertyChangedBase
    {
        public enum StateEnum
        {
            Stopped,
            Running,
            Paused
        }

        StateEnum state;
        bool runPauseBtnChecked;
        bool stopBtnEnabled;
        bool macroListEnabled;
        string runPauseBtnText;

        public StateEnum State
        {
            get => state;
            set
            {
                state = value;
                switch (value)
                {
                    case StateEnum.Stopped:
                        RunPauseBtnChecked = false;
                        RunPauseBtnText = "Run!";
                        StopBtnEnabled = false;
                        MacroListEnabled = true;
                        break;
                    case StateEnum.Running:
                        RunPauseBtnChecked = true;
                        RunPauseBtnText = "Pause!";
                        StopBtnEnabled = true;
                        MacroListEnabled = false;
                        break;
                    case StateEnum.Paused:
                        RunPauseBtnChecked = false;
                        RunPauseBtnText = "Resume!";
                        StopBtnEnabled = true;
                        MacroListEnabled = false;
                        break;
                    default:
                        break;
                }

                OnPropertyChanged("State");
            }
        }
        public bool RunPauseBtnChecked { get => runPauseBtnChecked; set { runPauseBtnChecked = value; OnPropertyChanged("RunPauseBtnChecked"); } }
        public bool StopBtnEnabled { get => stopBtnEnabled; set { stopBtnEnabled = value; OnPropertyChanged("StopBtnEnabled"); } }
        public bool MacroListEnabled { get => macroListEnabled; set { macroListEnabled = value; OnPropertyChanged("MacroListEnabled"); } }
        public string RunPauseBtnText { get => runPauseBtnText; set { runPauseBtnText = value; OnPropertyChanged("RunPauseBtnText"); } }
    }

    public class ObservableBool : PropertyChangedBase
    {
        bool val;

        public bool Value
        {
            get { return val; }
            set { val = value; OnPropertyChanged("Value"); }
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

    [ValueConversion(typeof(bool), typeof(bool))]
    public class InverseBooleanConverter : IValueConverter
    {
        #region IValueConverter Members

        public object Convert(object value, Type targetType, object parameter,
            System.Globalization.CultureInfo culture)
        {
            if (targetType != typeof(bool))
                throw new InvalidOperationException("The target must be a boolean");

            return !(bool)value;
        }

        public object ConvertBack(object value, Type targetType, object parameter,
            System.Globalization.CultureInfo culture)
        {
            throw new NotSupportedException();
        }

        #endregion
    }

}
