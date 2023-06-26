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
    /// Interaction logic for Score.xaml
    /// </summary>
    public partial class Score : Window
    {
        bool _quiet = false;
        public Score(int _code, bool quiet)
        {
            _quiet = quiet;
            InitializeComponent();
            scores.Items.Clear();
            string msg = Convert.ToString(_code, 2);
            msg = Translations.padLeft(msg, 8);
            msg += Translations.padLeft("", 32);
            NetworkStream clientStream = Communicator.client.GetStream();
            byte[] buffer = new ASCIIEncoding().GetBytes(msg);
            clientStream.Write(buffer, 0, buffer.Length);
            clientStream.Flush();
            byte[] code = new byte[8];
            int bytesRead = clientStream.Read(code, 0, 8);
            string code_str = System.Text.Encoding.Default.GetString(code);
            byte[] size = new byte[32];
            bytesRead = clientStream.Read(size, 0, 32);
            string size_str = System.Text.Encoding.Default.GetString(size);
            byte[] rooms = new byte[Convert.ToInt32(size_str, 2) * 8];
            bytesRead = clientStream.Read(rooms, 0, Convert.ToInt32(size_str, 2) * 8);
            string rooms_str = System.Text.Encoding.Default.GetString(rooms);
            if(Convert.ToInt32(code_str, 2) == 1)
            {
                statsResponse res = JsonConvert.DeserializeObject<statsResponse>(Translations.binaryToString(rooms_str));
                for (int i = 0; i < res.statistics.Length; i++)
                {
                    scores.Items.Add(res.statistics[i]);
                }
            }
           
        }

        private void leave_Click(object sender, RoutedEventArgs e)
        {
            Menu menu = new Menu(_quiet);
            this.Close();
            menu.ShowDialog();
        }
    }
}
