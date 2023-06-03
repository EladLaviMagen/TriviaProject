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

namespace Client
{
    /// <summary>
    /// Interaction logic for Signup.xaml
    /// </summary>
    public partial class Signup : Window
    {
        public Signup()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            string name = username.Text;
            string pass = password.Text;
            string email = mail.Text;
            if(name == "" || pass == "" || email == "")
            {
                notify.Text = "Do not leave empty fields";
            }
            else
            {
                string msg = Convert.ToString(3, 2);
                msg = Translations.padLeft(msg, 8);
                SignUpRequest sign = new SignUpRequest(name, pass, email);
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
                if(Convert.ToInt32(code_str, 2) == 1)
                {
                    clientStream.Flush();

                }
                else
                {
                    byte[] size = new byte[32];
                    bytesRead = clientStream.Read(size, 0, 32);
                    string size_str = System.Text.Encoding.Default.GetString(size);
                    byte[] err = new byte[Convert.ToInt32(size_str, 2)];
                    bytesRead = clientStream.Read(err, 0, Convert.ToInt32(size_str, 2));
                    string err_str = System.Text.Encoding.Default.GetString(err);
                    ErrorResponse response = JsonConvert.DeserializeObject<ErrorResponse>(Translations.binaryToString(err_str));
                    notify.Text = response.message;
                }
            }
        }


        private void returnToMain(object sender, RoutedEventArgs e)
        {
            MainWindow mainWindow = new MainWindow();
            this.Close();
            mainWindow.ShowDialog();
        }
    }
}
