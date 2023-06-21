using Newtonsoft.Json;
using System;
using System.Collections.Generic;
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
    /// Interaction logic for Create.xaml
    /// </summary>
    public partial class Create : Window
    {
        public Create()
        {
            InitializeComponent();
            for (int i = 1; i <= 10; i++)
            {
                numOfQ.Items.Add(i);
                time.Items.Add(i * 5);
            }

        }

        private void ComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

        }

        private void TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {

        }

        private void create_Click(object sender, RoutedEventArgs e)
        {
            
            if(name.Text != "")
            {
                string players = numOfPlayers.Text;
                if (players.All(char.IsNumber))
                {
                    CreateRoomRequest req = new CreateRoomRequest(name.Text, int.Parse(players), int.Parse(numOfQ.Text), int.Parse(time.Text));
                    string msg = Convert.ToString(8, 2);
                    msg = Translations.padLeft(msg, 8);
                    string json = JsonConvert.SerializeObject(req);
                    msg += Translations.padLeft(Convert.ToString(json.Length, 2), 32);
                    msg += Translations.stringToBinary(json);
                    NetworkStream clientStream = Communicator.client.GetStream();

                    byte[] buffer = new ASCIIEncoding().GetBytes(msg);
                    clientStream.Write(buffer, 0, buffer.Length);
                    clientStream.Flush();

                    byte[] code = new byte[8];
                    int bytesRead = clientStream.Read(code, 0, 8);
                    string code_str = System.Text.Encoding.Default.GetString(code);
                    clientStream.Flush();
                }
            }
        }
    }
}
