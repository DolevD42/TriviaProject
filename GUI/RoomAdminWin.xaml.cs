using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading;
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
        private NetworkStream _net;
        private List<string> Players = new List<string>();
        Thread Refresher2;
        private float time;
        private int questCount;
        public RoomAdminWin(TcpClient client, string userName, string roomName, int questionCount, int answerTimeout, int maxUsers)
        {
            InitializeComponent();
            this._client = client;
            _net = _client.GetStream();
            
            Thread Refresher = new Thread(() => refresh(_net));
            Refresher2 = Refresher;
            Refresher.Start();
            this._userName = userName;
            this.PlayersNum.Text += maxUsers.ToString();
            this.Title.Text = roomName;
            this.QuestionNum.Text += questionCount.ToString();
            this.QuestionTime.Text += answerTimeout.ToString();
        }
        private void StartGame_Click(object sender, RoutedEventArgs e)
        {
            Refresher2.Abort();
            string msgToSent = Serializer.serializeCodeOnly(Consts.START_GAME_CODE);
            _net.Write(System.Text.Encoding.ASCII.GetBytes(msgToSent), 0, msgToSent.Length);
            byte[] serverMsg = new byte[5];
            _net.Read(serverMsg, 0, 5);
            Consts.ResponseInfo resInf = Deserializer.deserializeSize(Encoding.Default.GetString(serverMsg));
            if (resInf.id == Consts.ERR_CODE)
            {
                byte[] errorBuffer = new byte[resInf.len];
                _net.Read(errorBuffer, 0, resInf.len);
                Consts.ErrorResponse err = Deserializer.deserializeErrorResponse(Encoding.Default.GetString(errorBuffer));
                MessageBox.Show(err.message, "Trivia Client", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }
            byte[] serverBuffer = new byte[resInf.len];

            _net.Read(serverBuffer, 0, resInf.len);
            Consts.StartGameResponse res = Deserializer.deserializeStartGameResponse(Encoding.Default.GetString(serverBuffer));
            if (res.status == Consts.REQUEST_VALID)
            {
                this.Hide();
                GameWin win = new GameWin(_client, _userName, time, questCount);
                win.Show();
                this.Close();
            }

        }
        private void refresh(NetworkStream rnet)
        {

            List<string> PlayersR = new List<string>();
            while (true)
            {
                string msgToSent = Serializer.serializeCodeOnly(Consts.GET_ROOM_STATE_CODE);
                rnet.Write(System.Text.Encoding.ASCII.GetBytes(msgToSent), 0, msgToSent.Length);
                byte[] serverMsg = new byte[5];
                rnet.Read(serverMsg, 0, 5);
                Consts.ResponseInfo resInf = Deserializer.deserializeSize(Encoding.Default.GetString(serverMsg));
                if (resInf.id == Consts.ERR_CODE)
                {
                    byte[] errorBuffer = new byte[resInf.len];
                    rnet.Read(errorBuffer, 0, resInf.len);
                    Consts.ErrorResponse err = Deserializer.deserializeErrorResponse(Encoding.Default.GetString(errorBuffer));
                    MessageBox.Show(err.message, "Trivia Client", MessageBoxButton.OK, MessageBoxImage.Error);
                    return;
                }
                byte[] serverBuffer = new byte[resInf.len];

                rnet.Read(serverBuffer, 0, resInf.len);
                Consts.GetRoomStateResponse res = Deserializer.deserializeGetRoomStateResponse(Encoding.Default.GetString(serverBuffer));
                questCount =res.questionCount;
                time = res.answerTimeout;
                for (int i = 0; i < res.players.Count(); i++)
                {
                    PlayersR.Add(res.players[i]);
                    Console.WriteLine(res.players[i]);
                }
                if (Players == null)
                {
                    for (int i = 0; i < PlayersR.Count(); i++)
                    {
                        list.Items.Add(PlayersR[i]);
                        Players.Add(PlayersR[i]);
                    }
                }
                else
                {
                    for (int i = 0; i < Players.Count; i++)
                    {
                        if (!PlayersR.Contains(Players[i]))
                        {
                            Console.WriteLine("removing");
                            this.Dispatcher.Invoke(() =>
                            {
                                list.Items.Remove(Players[i]);
                                Players.Remove(Players[i]);
                            });

                        }
                    }
                    List<string> firstNotSecondRoomP = PlayersR.Except(Players).ToList();
                    if (firstNotSecondRoomP.Count != 0)
                    {
                        foreach (var player in firstNotSecondRoomP)
                        {
                            this.Dispatcher.Invoke(() =>
                            {
                                list.Items.Add(player);
                                Players.Add(player);
                            });
                        }
                    }
                }
                for (int i = 0; i < PlayersR.Count; i++)
                {
                    PlayersR.Remove(PlayersR[i]);
                }
                System.Threading.Thread.Sleep(3000);
            }
        }
        private void BackToMenuClick(object sender, RoutedEventArgs e)
        {
            Refresher2.Abort();
            string msgToSent = Serializer.serializeCodeOnly(Consts.CLOSE_ROOM_CODE);
            _net.Write(System.Text.Encoding.ASCII.GetBytes(msgToSent), 0, msgToSent.Length);
            byte[] serverMsg = new byte[5];
            _net.Read(serverMsg, 0, 5);
            Consts.ResponseInfo resInf = Deserializer.deserializeSize(Encoding.Default.GetString(serverMsg));
            if (resInf.id == Consts.ERR_CODE)
            {
                byte[] errorBuffer = new byte[resInf.len];
                _net.Read(errorBuffer, 0, resInf.len);
                Consts.ErrorResponse err = Deserializer.deserializeErrorResponse(Encoding.Default.GetString(errorBuffer));
                MessageBox.Show(err.message, "Trivia Client", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }
            byte[] serverBuffer = new byte[resInf.len];

            _net.Read(serverBuffer, 0, resInf.len);
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
