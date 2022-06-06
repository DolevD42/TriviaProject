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
            Consts.StatusResponse res = Deserializer.deserializeJoinRoomResponse(Encoding.Default.GetString(serverBuffer));
            switch (res.status)
            {
                case Consts.ROOM_MAX_OUT:
                    MessageBox.Show("There is no place left in the room", "Trivia Client", MessageBoxButton.OK, MessageBoxImage.Exclamation);
                    break;
                case Consts.REQUEST_VALID:
                    this.Hide();
                    RoomMember win = new RoomMember(_client, _username, _roomsId[list.SelectedIndex], _roomNames[list.SelectedIndex]);
                    win.Show();
                    this.Close();
                    break;
            }
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
