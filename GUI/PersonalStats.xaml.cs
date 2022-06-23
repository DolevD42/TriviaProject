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
using System.Net.Sockets;
using System.Net;
namespace GUI
{
    /// <summary>
    /// Interaction logic for PersonalStats.xaml
    /// </summary>
    public partial class PersonalStats : Window
    {
        private TcpClient _client;
        private string _UserName;
        public PersonalStats(TcpClient client, string username)
        {
            InitializeComponent();
            _client = client;
            _UserName = username;
            string msgToSent = Serializer.serializeCodeOnly(Consts.GET_PERSONAL_CODE);
            NetworkStream net = _client.GetStream();
            net.Write(System.Text.Encoding.ASCII.GetBytes(msgToSent), 0, msgToSent.Length);
            byte[] serverMsg = new byte[5];
            net.Read(serverMsg, 0, 5);
            Consts.ResponseInfo resInf = Deserializer.deserializeSize(Encoding.Default.GetString(serverMsg));
            if (resInf.id == Consts.ERR_CODE)
            {
                byte[] errorBuffer = new byte[resInf.len];
                net.Read(errorBuffer, 0, resInf.len);
                Consts.ErrorResponse err = Deserializer.deserializeErrorResponse(Encoding.Default.GetString(errorBuffer));
                MessageBox.Show(err.message, "Trivia Client", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }
            byte[] serverBuffer = new byte[resInf.len];

            net.Read(serverBuffer, 0, resInf.len);
            Consts.getPersonalStatsResponse res = Deserializer.deserializeGetPersonalStatsResponse(Encoding.Default.GetString(serverBuffer));
            AverageTime.Text = "Your average answer time is " + res.statistics[0] + " sec.";
            TotalAnswers.Text = "You have answer a total of " + res.statistics[1] + " answers.";
            TotalGames.Text = "You played " + res.statistics[2] + " games.";
            CorrectAnswers.Text = "You answer a total of " + res.statistics[3] + " correct answers.";
        }
        private void BackToMenuClick(object sender, RoutedEventArgs e)
        {
            this.Hide();
            Menu win = new Menu(_client, _UserName);
            win.Show();
            this.Close();
        }
    }
}
