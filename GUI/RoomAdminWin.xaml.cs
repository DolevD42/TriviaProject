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
    /// Interaction logic for RoomAdminWin.xaml
    /// </summary>
    public partial class RoomAdminWin : Window
    {
        private TcpClient _client;
        private string _userName;



        public RoomAdminWin(TcpClient client, string userName, string roomName, int questionCount, int answerTimeout, int maxUsers)
        {
            InitializeComponent();
            this._client = client;
            this._userName = userName;
            this.PlayersNum.Text = maxUsers.ToString();
            this.RoomName.Text = roomName;
            this.QuestionNum.Text = questionCount.ToString();
            this.QuestionTime.Text = answerTimeout.ToString();
        }
        private void StartGame_Click(object sender, RoutedEventArgs e)
        {


        }
    }
}
