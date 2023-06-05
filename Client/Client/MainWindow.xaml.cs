using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.IO;
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


namespace Client
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        
        public MainWindow()
        {
            Audio.mediaPlayer.MediaEnded += new EventHandler(Audio.Media_Ended);
            InitializeComponent();
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "MP3 files (*.mp3)|*.mp3|All files (*.*)|*.*";
            openFileDialog.FileName = Directory.GetCurrentDirectory() + "\\and_theme.mp3";
            Audio.mediaPlayer.Open(new Uri(openFileDialog.FileName));
            Audio.mediaPlayer.Play();
            
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            Audio.mediaPlayer.Close();
            Signup signup = new Signup();
            this.Close();
            signup.ShowDialog();
        }
    }
}
