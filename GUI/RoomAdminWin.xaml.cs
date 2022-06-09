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
            this.PlayersNum.Text += maxUsers.ToString();
            this.Title.Text = roomName;
            this.QuestionNum.Text += questionCount.ToString();
            this.QuestionTime.Text += answerTimeout.ToString();
        }
        private void StartGame_Click(object sender, RoutedEventArgs e)
        {
            string msgToSent = Serializer.serializeCodeOnly(Consts.START_GAME_CODE);
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
            Consts.StartGameResponse res = Deserializer.deserializeStartGameResponse(Encoding.Default.GetString(serverBuffer));
            if (res.status == Consts.REQUEST_VALID)
            {
                //start the game
            }
        }
        private void BackToMenuClick(object sender, RoutedEventArgs e)
        {
            string msgToSent = Serializer.serializeCodeOnly(Consts.CLOSE_ROOM_CODE);
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
            Consts.CloseRoomResponse res = Deserializer.deserializeCloseRoomResponse(Encoding.Default.GetString(serverBuffer));
            if (res.status == Consts.REQUEST_VALID)
            {
                this.Hide();
                Menu win = new Menu(_client, _userName);
                win.Show();
                this.Close();
            }
        }
    }
}
