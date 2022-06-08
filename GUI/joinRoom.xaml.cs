using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Threading;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Threading;
using System.Windows.Shapes;
using System.Net.Sockets;
using System.Net;

namespace GUI
{
    /// <summary>
    /// Interaction logic for joinRoom.xaml
    /// </summary>
    public partial class joinRoom : Window
    {
        private TcpClient _client;
        private string _username;
        private List<int> _roomsId = new List<int>();
        private List<string> _roomNames = new List<string>();
        public joinRoom(TcpClient client, string username)
        {
            InitializeComponent();
            _client = client;
            _username = username;
            JoinButton.IsEnabled = false;
            string msgToSent = Serializer.serializeCodeOnly(Consts.GET_ROOMS_CODE);
            NetworkStream net = _client.GetStream();
            Thread RefresherThread = new Thread(() => refresh(net));
            RefresherThread.Start();
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
            Consts.GetRoomsResponse res = Deserializer.deserializeGetRoomsResponse(Encoding.Default.GetString(serverBuffer));
            for (int i = 0; i < res.roomsId.Count(); i++)
            {
                list.Items.Add(res.roomsId[i] + ":      " + res.rooms[i]);
                _roomsId.Add(res.roomsId[i]);
                _roomNames.Add(res.rooms[i]);
            }

        }

        private void refresh(NetworkStream rnet)
        {
            List<int> _roomsIdR = new List<int>();
            List<string> _roomNamesR = new List<string>();
            System.Threading.Thread.Sleep(3000);
            while (true)
            {
                string msgToSent = Serializer.serializeCodeOnly(Consts.GET_ROOMS_CODE);
                rnet.Write(System.Text.Encoding.ASCII.GetBytes(msgToSent), 0, msgToSent.Length);
                byte[] serverMsg = new byte[5];
                rnet.Read(serverMsg, 0, 5);
                Consts.ResponseInfo resInf = Deserializer.deserializeSize(Encoding.Default.GetString(serverMsg));
                if (resInf.id == Consts.ERR_CODE)
                {
                    byte[] errorBuffer = new byte[resInf.len];
                    rnet.Read(errorBuffer, 0, resInf.len);
                    Consts.ErrorResponse err = Deserializer.deserializeErrorResponse(Encoding.Default.GetString(errorBuffer));
                    MessageBox.Show(err.msg, "Trivia Client", MessageBoxButton.OK, MessageBoxImage.Error);
                    return;
                }
                byte[] serverBuffer = new byte[resInf.len];

                rnet.Read(serverBuffer, 0, resInf.len);
                Consts.GetRoomsResponse res = Deserializer.deserializeGetRoomsResponse(Encoding.Default.GetString(serverBuffer));
                for (int i = 0; i < res.roomsId.Count(); i++)
                {
                    //list.Items.Add(res.roomsId[i] + ":      " + res.rooms[i]);
                    _roomsIdR.Add(res.roomsId[i]);
                    _roomNamesR.Add(res.rooms[i]);
                }//add new list and 
            }
        }

        private void ListSelectionChanged(object sender, System.Windows.Controls.SelectionChangedEventArgs e)
        {
            JoinButton.IsEnabled = true;
        }
        private void JoinClick(object sender, RoutedEventArgs e)
        {
            Consts.JoinRoomRequest req;
            req.roomId = _roomsId[list.SelectedIndex];
            string msgToSent = Serializer.serializeMsgJoinRoom(req, Consts.JOIN_ROOM_CODE);
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
        }
        private void BackToMenuClick(object sender, RoutedEventArgs e)
        {
            this.Hide();
            Menu win = new Menu(_client, _username);
            win.Show();
            this.Close();
        }

    }
}
