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
using System.Threading;

using System.Net.Sockets;
using System.Net;

namespace GUI
{
    /// <summary>
    /// Interaction logic for RoomMember.xaml
    /// </summary>
    public partial class RoomMember : Window
    {
        private TcpClient _client;
        private string _username;
        private Thread _thread;
        private NetworkStream _net;
        private Thread RefresherThread;
        private List<string> Players = new List<string>();
        public RoomMember(TcpClient client, string username, int roomId, string roomName)
        {
            InitializeComponent();
            Title.Text = roomName;
            _client = client;
            _username = username;
            string msgToSent = Serializer.serializeCodeOnly(Consts.GET_ROOM_STATE_CODE);

            NetworkStream net = _client.GetStream();
            _net = net;
            RefresherThread = new Thread(new ThreadStart(refresh));
            RefresherThread.IsBackground = true;
            RefresherThread.Start();
            //net.Write(System.Text.Encoding.ASCII.GetBytes(msgToSent), 0, msgToSent.Length);
            //byte[] serverMsg = new byte[5];
            //net.Read(serverMsg, 0, 5);
            //Consts.ResponseInfo resInf = Deserializer.deserializeSize(Encoding.Default.GetString(serverMsg));
            //if (resInf.id == Consts.ERR_CODE)
            //{
            //    byte[] errorBuffer = new byte[resInf.len];
            //    net.Read(errorBuffer, 0, resInf.len);
            //    Consts.ErrorResponse err = Deserializer.deserializeErrorResponse(Encoding.Default.GetString(errorBuffer));
            //    MessageBox.Show(err.msg, "Trivia Client", MessageBoxButton.OK, MessageBoxImage.Error);
            //    return;
            //}
            //byte[] serverBuffer = new byte[resInf.len];
            //
            //net.Read(serverBuffer, 0, resInf.len);
            //Consts.GetRoomStateResponse res = Deserializer.deserializeGetRoomStateResponse(Encoding.Default.GetString(serverBuffer));
            //
            //Admin.Text = "Room Admin: "+res.players[0];
            //for (int i = 0; i < res.players.Count(); i++)
            //{
            //    list.Items.Add(res.players[i]);
            //}
            Thread newThread = new Thread(new ThreadStart(WaitingForServerMsg));
            _thread = newThread;
            _thread.Start();
        }
        private void refresh()
        {
            List<string> PlayersR = new List<string>();
            while (true)
            {
                string msgToSent = Serializer.serializeCodeOnly(Consts.GET_ROOM_STATE_CODE);
                _net.Write(System.Text.Encoding.ASCII.GetBytes(msgToSent), 0, msgToSent.Length);
                byte[] serverMsg = new byte[5];
                _net.Read(serverMsg, 0, 5);
                Consts.ResponseInfo resInf = Deserializer.deserializeSize(Encoding.Default.GetString(serverMsg));
                if (resInf.id == Consts.ERR_CODE)
                {
                    byte[] errorBuffer = new byte[resInf.len];
                    _net.Read(errorBuffer, 0, resInf.len);
                    Consts.ErrorResponse err = Deserializer.deserializeErrorResponse(Encoding.Default.GetString(errorBuffer));
                    MessageBox.Show(err.msg, "Trivia Client", MessageBoxButton.OK, MessageBoxImage.Error);
                    return;
                }
                byte[] serverBuffer = new byte[resInf.len];

                _net.Read(serverBuffer, 0, resInf.len);
                Consts.GetRoomStateResponse res = Deserializer.deserializeGetRoomStateResponse(Encoding.Default.GetString(serverBuffer));

                this.Dispatcher.Invoke(() =>
                {
                    Admin.Text = "Room Admin: " + res.players[0];
                });
                for (int i = 0; i < res.players.Count(); i++)
                {
                    PlayersR.Add(res.players[i]);
                    Console.WriteLine(res.players[i]);
                }
                if (Players == null)
                {
                    for (int i = 0; i <PlayersR.Count(); i++)
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
        void WaitingForServerMsg()
        {
           
            byte[] newServerMsg = new byte[5];
            while(!_net.DataAvailable)
            {

            }
            _net.Read(newServerMsg, 0, 5);
            Consts.ResponseInfo resInf = Deserializer.deserializeSize(Encoding.Default.GetString(newServerMsg));
            if (resInf.id == Consts.ERR_CODE)
            {
                byte[] errorBuffer = new byte[resInf.len];
                _net.Read(errorBuffer, 0, resInf.len);
                Consts.ErrorResponse err = Deserializer.deserializeErrorResponse(Encoding.Default.GetString(errorBuffer));
                MessageBox.Show(err.msg, "Trivia Client", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }
            switch (resInf.id)
            {
                case Consts.LEAVE_ROOM_CODE:
                    string msgToSent = Serializer.serializeCodeOnly(Consts.LEAVE_ROOM_CODE);
                    _net.Write(System.Text.Encoding.ASCII.GetBytes(msgToSent), 0, msgToSent.Length);
                    byte[] serverMsg = new byte[5];
                    _net.Read(serverMsg, 0, 5);
                    resInf = Deserializer.deserializeSize(Encoding.Default.GetString(serverMsg));
                    if (resInf.id == Consts.ERR_CODE)
                    {
                        byte[] errorBuffer = new byte[resInf.len];
                        _net.Read(errorBuffer, 0, resInf.len);
                        Consts.ErrorResponse err = Deserializer.deserializeErrorResponse(Encoding.Default.GetString(errorBuffer));
                        MessageBox.Show(err.msg, "Trivia Client", MessageBoxButton.OK, MessageBoxImage.Error);
                        return;
                    }
                    byte[] serverBuffer = new byte[resInf.len];

                     _net.Read(serverBuffer, 0, resInf.len);
                     Consts.LeaveRoomResponse res = Deserializer.deserializeLeaveRoomResponse(Encoding.Default.GetString(serverBuffer));
                    this.Dispatcher.Invoke(() =>
                    {
                        this.Hide();
                        Menu win = new Menu(_client, _username);
                        win.Show();
                        this.Close();
                    });
                     _thread.Abort();
                    break;
                case Consts.START_GAME_CODE:
                    //Here I will direct the player to the game
                    break;
            }
        }
        private void BackToMenuClick(object sender, RoutedEventArgs e)
        {
            _thread.Abort();
            RefresherThread.Abort();
            string msgToSent = Serializer.serializeCodeOnly(Consts.LEAVE_ROOM_CODE);
            _net.Write(System.Text.Encoding.ASCII.GetBytes(msgToSent), 0, msgToSent.Length);
            byte[] serverMsg = new byte[5];
            _net.Read(serverMsg, 0, 5);
            Consts.ResponseInfo resInf = Deserializer.deserializeSize(Encoding.Default.GetString(serverMsg));
            if (resInf.id == Consts.ERR_CODE)
            {
                byte[] errorBuffer = new byte[resInf.len];
                _net.Read(errorBuffer, 0, resInf.len);
                Consts.ErrorResponse err = Deserializer.deserializeErrorResponse(Encoding.Default.GetString(errorBuffer));
                MessageBox.Show(err.msg, "Trivia Client", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }
            byte[] serverBuffer = new byte[resInf.len];

            _net.Read(serverBuffer, 0, resInf.len);
            Consts.LeaveRoomResponse res = Deserializer.deserializeLeaveRoomResponse(Encoding.Default.GetString(serverBuffer));
            if(res.status == Consts.REQUEST_VALID)
            {
                this.Hide();
                Menu win = new Menu(_client, _username);
                win.Show();
                this.Close();
            }
           
        }
    }
}
