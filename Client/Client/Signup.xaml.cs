using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json.Nodes;
using System.Threading.Tasks;
using System.Windows;
using System.Net.Sockets;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using Newtonsoft.Json;
using System.Text.Json.Serialization;
using Microsoft.Win32;
using System.IO;
using System.DirectoryServices.ActiveDirectory;

namespace Client
{
    /// <summary>
    /// Interaction logic for Signup.xaml
    /// </summary>
    public partial class Signup : Window
    {
        //DISCLAIMER, ALL PLACES I WHERE CODE IS REPEATED I WILL NOT DOCUEMENT AGAIN
        //MOST EXPLANATIONS WILL BE HERE
        bool _quiet = false;
        public Signup(bool quiet)
        {
            _quiet = quiet;
            InitializeComponent();
            if (!quiet)
            {
                //Activating music
                OpenFileDialog openFileDialog = new OpenFileDialog();
                openFileDialog.Filter = "MP3 files (*.mp3)|*.mp3|All files (*.*)|*.*";
                openFileDialog.FileName = Directory.GetCurrentDirectory() + "\\used_to.mp3";
                Audio.mediaPlayer.Open(new Uri(openFileDialog.FileName));
                Audio.mediaPlayer.Play();
            }
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            //Taking inputs
            string name = username.Text;
            string pass = password.Text;
            string email = mail.Text;
            //Checking inputs
            if(name == "" || pass == "" || email == "")
            {
                notify.Text = "Do not leave empty fields";
            }
            else
            {
                //Comms explanation:
                //Getting message code and padding it
                string msg = Convert.ToString(3, 2);
                msg = Translations.padLeft(msg, 8);
                //Serializing the information, and padding it before adding it and it's serialized size onto the message
                SignUpRequest sign = new SignUpRequest(name, pass, email);
                string json = JsonConvert.SerializeObject(sign);
                msg += Translations.padLeft(Convert.ToString(json.Length, 2), 32);
                msg += Translations.stringToBinary(json);
                //Checking if connection was already established
                if (Communicator.first)
                {
                    Communicator.client.Connect(Communicator.serverEndPoint);
                    Communicator.first = false;
                }
                
                NetworkStream clientStream = Communicator.client.GetStream();

                byte[] buffer = new ASCIIEncoding().GetBytes(msg);
                //Sending message
                clientStream.Write(buffer, 0, buffer.Length);
                //Deconstructing response:
                //Getting response code
                byte[] code = new byte[8];
                int bytesRead = clientStream.Read(code, 0, 8);
                string code_str = System.Text.Encoding.Default.GetString(code);
                //Getting size of response
                byte[] size = new byte[32];
                bytesRead = clientStream.Read(size, 0, 32);
                string size_str = System.Text.Encoding.Default.GetString(size);
                //Getting actual response
                byte[] err = new byte[Convert.ToInt32(size_str, 2) * 8];
                bytesRead = clientStream.Read(err, 0, Convert.ToInt32(size_str, 2) * 8);
                string err_str = System.Text.Encoding.Default.GetString(err);
                clientStream.Flush();
                //1 == Success
                if (Convert.ToInt32(code_str, 2) == 1)
                {
                    Audio.mediaPlayer.Close();
                    Menu menu = new Menu(_quiet);
                    this.Close();
                    menu.ShowDialog();
                }
                else
                {

                    ErrorResponse response = JsonConvert.DeserializeObject<ErrorResponse>(Translations.binaryToString(err_str));
                    notify.Text = response.message;
                }
            }
        }


        private void returnToMain(object sender, RoutedEventArgs e)
        {
            Audio.mediaPlayer.Close();
            MainWindow mainWindow = new MainWindow();
            this.Close();
            mainWindow.ShowDialog();
        }
    }
}
