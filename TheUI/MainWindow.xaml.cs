using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace TheUI
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class wintouch : Page, INotifyPropertyChanged
    {
        public wintouch()
        {
            InitializeComponent();
        }
        public wintouch(int w, int h)
        {
            InitializeComponent();
            this.Width = w;
            this.Height = h;
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            MyButtonValue = "xx";
        }

        public void ShowMessage()
        {
            MessageBox.Show("Try me!");
        }


        private string myField;

        public string MyButtonValue
        {
            get
            {
                return this.myField;
            }
            set
            {
                if (value != this.myField)
                {
                    this.myField = value;
                    NotifyPropertyChanged("MyButtonValue");
                }
            }
        }

        protected void NotifyPropertyChanged(String propertyName)
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
        }

        public event PropertyChangedEventHandler PropertyChanged;
        //public String MyButtonValue { get; set; }

    }
}
