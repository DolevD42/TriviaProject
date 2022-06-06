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

namespace GUI
{
    /// <summary>
    /// Interaction logic for StatsWin.xaml
    /// </summary>
    public partial class StatsWin : Window
    {
        private TcpClient _client;
        private string _userName;

        public StatsWin(TcpClient client, string userName)
        {
            InitializeComponent();
            this._client = client;
            this._userName = userName;
            string msgToSent = Serializer.serializeCodeOnly(Consts.GET_HIGH_CODE);
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
                MessageBox.Show(err.msg, "Trivia Client", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }
            byte[] serverBuffer = new byte[resInf.len];

            net.Read(serverBuffer, 0, resInf.len);
            Consts.GetHighScoreResponse res = Deserializer.deserializeGetHighScoresResponse(Encoding.Default.GetString(serverBuffer));
            FirstScore.Text = res.statistics[0];
            SecondScore.Text = res.statistics[1];
            ThirdScore.Text = res.statistics[2];
        }
        private void BackToMenuClick(object sender, RoutedEventArgs e)
        {
            this.Hide();
            Menu win = new Menu(_client, _userName);
            win.Show();
            this.Close();
        }
    }
}
