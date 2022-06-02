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
    public partial class CreateRoomWin : Window
    {
        private TcpClient _client;
        private string _UserName;
        public CreateRoomWin(TcpClient client, string userName)
        {
            InitializeComponent();
            this._client = client;
            this._UserName = userName;
        }

        private void But_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                string _RoomName;
                int _PlayersNumber, _QuestionNumber;
                int _QuestionTime;
                _RoomName = RoomName.Text;
                _PlayersNumber = Int16.Parse(PlayersNumber.Text);
                _QuestionNumber = Int16.Parse(QuestionsNumber.Text);
                _QuestionTime = Int16.Parse(QuestionTime.Text);
                Consts.CreateRoomRequest req;
                req.answerTimeout = _QuestionTime;
                req.maxUsers = _PlayersNumber;
                req.questionCount = _QuestionNumber;
                req.roomName = _RoomName;
                string msgToSent = Serializer.serializeMsgCreateRoom(req, Consts.CREATE_ROOM_CODE);
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
                Consts.StatusResponse res = Deserializer.deserializeCreateRoomResponse(Encoding.Default.GetString(serverBuffer));
                RoomName.Text = "";
                PlayersNumber.Text = "";
                QuestionsNumber.Text = "";
                QuestionTime.Text= "";
                switch (res.status)
                {
                    case Consts.ROOM_DONT_EXIST:
                        MessageBox.Show("Room not exist", "Trivia Client", MessageBoxButton.OK, MessageBoxImage.Exclamation);
                        break;
                    case Consts.ROOM_MAX_OUT:
                        MessageBox.Show("Room maxed out sorry", "Trivia Client", MessageBoxButton.OK, MessageBoxImage.Exclamation);
                        break;
                    case Consts.WRONG_PARAMETERS:
                        MessageBox.Show("Wrong parameters!", "Trivia Client", MessageBoxButton.OK, MessageBoxImage.Exclamation);
                        break;
                    case Consts.REQUEST_VALID:
                        this.Hide();
                        Menu win = new Menu(_client, _UserName);
                        this.Close();
                        win.Show();
                        break;
                }
            }
            catch (Exception Exc) { ErrorMessage.Content = "Server Error... Please go out of this page and try again..."; }
        }
    }
}
