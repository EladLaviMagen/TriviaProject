using Microsoft.Win32;
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
using static System.Net.Mime.MediaTypeNames;
using System.Windows.Media;
using System.IO;

namespace Client
{
    /// <summary>
    /// Interaction logic for Menu.xaml
    /// </summary>
    public partial class Menu : Window
    {
        private MediaPlayer mediaPlayer = new MediaPlayer();
        public Menu()
        {
            InitializeComponent();
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "MP3 files (*.mp3)|*.mp3|All files (*.*)|*.*";
            openFileDialog.FileName = Directory.GetCurrentDirectory() + "\\theme.mp3";
            mediaPlayer.Open(new Uri(openFileDialog.FileName));
            mediaPlayer.Play();

        }

        private void ListBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

        }
        public void rest()
        {
            while (listBox.Items.Count > 0)
            {
                listBox.Items.RemoveAt(listBox.Items.Count - 1);
            }
        }

        private void ready_Click(object sender, RoutedEventArgs e)
        {

        }

        private void sign_out_Click(object sender, RoutedEventArgs e)
        {

        }

        private void shop_Click(object sender, RoutedEventArgs e)
        {

        }

        private void create_Click(object sender, RoutedEventArgs e)
        {

        }

        private void lead_Click(object sender, RoutedEventArgs e)
        {

        }

        private void profile_Click(object sender, RoutedEventArgs e)
        {

        }
    }
}
