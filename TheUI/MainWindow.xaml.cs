using System;
using System.ComponentModel;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;

namespace TheUI
{
    public partial class wintouch : Page
    {
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
                        RunPauseBtnText = "Run!";
                        StopBtnEnabled = false;
                        MacroListEnabled = true;
                        RunPauseBtnChecked = false;
                        break;
                    case StateEnum.Running:
                        RunPauseBtnText = "Pause!";
                        StopBtnEnabled = true;
                        MacroListEnabled = false;
                        RunPauseBtnChecked = true;
                        break;
                    case StateEnum.Paused:
                        RunPauseBtnText = "Resume!";
                        StopBtnEnabled = true;
                        MacroListEnabled = false;
                        RunPauseBtnChecked = false;
                        break;
                    default:
                        break;
                }
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
            if (/*e.ViewportHeightChange > 0 || */e.ExtentHeightChange > 0 || /*e.ViewportHeightChange < 0 || */e.ExtentHeightChange < 0)
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
