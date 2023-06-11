using Microsoft.Win32;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net.Sockets;
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
    /// Interaction logic for Login.xaml
    /// </summary>
    public partial class Login : Window
    {
        public Login()
        {
            InitializeComponent();
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "MP3 files (*.mp3)|*.mp3|All files (*.*)|*.*";
            openFileDialog.FileName = Directory.GetCurrentDirectory() + "\\hey.mp3";
            Audio.mediaPlayer.Open(new Uri(openFileDialog.FileName));
            Audio.mediaPlayer.Play();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            string name = username.Text;
            string pass = password.Text;
            if (name == "" || pass == "")
            {
                notify.Text = "Do not leave empty fields";
            }
            else
            {
                string msg = Convert.ToString(1, 2);
                msg = Translations.padLeft(msg, 8);
                LoginRequest sign = new LoginRequest(name, pass);
                string json = JsonConvert.SerializeObject(sign);
                msg += Translations.padLeft(Convert.ToString(json.Length, 2), 32);
                msg += Translations.stringToBinary(json);
                Communicator.client.Connect(Communicator.serverEndPoint);
                NetworkStream clientStream = Communicator.client.GetStream();

                byte[] buffer = new ASCIIEncoding().GetBytes(msg);
                clientStream.Write(buffer, 0, buffer.Length);
                clientStream.Flush();

                byte[] code = new byte[8];
                int bytesRead = clientStream.Read(code, 0, 8);
                string code_str = System.Text.Encoding.Default.GetString(code);
                clientStream.Flush();
                if (Convert.ToInt32(code_str, 2) == 1)
                {
                    Audio.mediaPlayer.Close();
                    Menu menu = new Menu();
                    this.Close();
                    menu.ShowDialog();
                }
                else
                {
                    byte[] size = new byte[32];
                    bytesRead = clientStream.Read(size, 0, 32);
                    string size_str = System.Text.Encoding.Default.GetString(size);
                    byte[] err = new byte[Convert.ToInt32(size_str, 2) * 8];
                    bytesRead = clientStream.Read(err, 0, Convert.ToInt32(size_str, 2) * 8);
                    string err_str = System.Text.Encoding.Default.GetString(err);
                    ErrorResponse response = JsonConvert.DeserializeObject<ErrorResponse>(Translations.binaryToString(err_str));
                    notify.Text = response.message;
                }
            }
        }

        private void returnToMain(object sender, RoutedEventArgs e)
        {
            Audio.mediaPlayer.Close();
            MainWindow main = new MainWindow();
            this.Close();
            main.ShowDialog();
        }
    }
}
