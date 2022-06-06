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
    /// Interaction logic for RoomMember.xaml
    /// </summary>
    public partial class RoomMember : Window
    {
        private TcpClient _client;
        private string _username;
        public RoomMember(TcpClient client, string username, int roomId, string roomName)
        {
            InitializeComponent();
            Title.Text = roomName;
            _client = client;
            _username = username;
            Consts.GetPlayersInRoomRequest req;
            req.roomId = roomId;
            string msgToSent = Serializer.serializeMsgGetPlayersInRoom(req, Consts.GET_PLAYERS_CODE);

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
            Consts.GetPlayersInRoomResponse res = Deserializer.deserializeGetPlayersInRoomResponse(Encoding.Default.GetString(serverBuffer));
            
            Admin.Text = "Room Admin: "+res.players[0];
            for (int i = 0; i < res.players.Count(); i++)
            {
                list.Items.Add(res.players[i]);
            }
        }
        private void BackToMenuClick(object sender, RoutedEventArgs e)
        {
            //Here I will put the get out of the user from the room
            this.Hide();
            Menu win = new Menu(_client, _username);
            win.Show();
            this.Close();
        }
    }
}
