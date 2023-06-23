using System;
using System.Collections.Generic;
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
using System.Windows.Shapes;

namespace Client
{
    /// <summary>
    /// Interaction logic for AdminRoom.xaml
    /// </summary>
    public partial class AdminRoom : Window
    {
        bool _admin = false;
        public AdminRoom(bool admin)
        {
            _admin = admin;
            InitializeComponent();
            if(!admin)
            {
                Start.Visibility = Visibility.Collapsed;
                Start.IsEnabled = false;
                close.Content = "Leave room";
            }
        }

        private void membersList_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

        }

        private void Start_Click(object sender, RoutedEventArgs e)
        {

        }

        private void Close_Click(object sender, RoutedEventArgs e)
        {

        }
    }
}
