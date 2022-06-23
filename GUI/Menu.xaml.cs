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
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Net.Sockets;
using System.Net;


namespace GUI
{
    /// <summary>
    /// Interaction logic for Menu.xaml
    /// </summary>
    public partial class Menu : Window
    {
        private TcpClient _client;
        private string _UserName;
        public Menu(TcpClient client, string username)
        {
            InitializeComponent();
            _client = client;
            _UserName = username;
        }
        private void Create_room_Button(object sender, RoutedEventArgs e)
        {
            this.Hide();
            CreateRoomWin win = new CreateRoomWin(_client, _UserName);
            this.Close();
            win.Show();
        }
        private void Join_Room_Button(object sender, RoutedEventArgs e)
        {
            this.Hide();
            joinRoom win = new joinRoom(_client, _UserName);
            this.Close();
            win.Show();
        }
        private void High_Score_Button(object sender, RoutedEventArgs e)
        {
            this.Hide();
            StatsWin win = new StatsWin(_client, _UserName);
            this.Close();
            win.Show();
        }
        private void Personal_Stats_Button(object sender, RoutedEventArgs e)
        {
            this.Hide();
            PersonalStats win = new PersonalStats(_client, _UserName);
            this.Close();
            win.Show();
        }
        private void Quit_Button_Button(object sender, RoutedEventArgs e)
        {
            string msgToSent = Serializer.serializeCodeOnly(Consts.LOGOUT_CODE);
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
            Consts.StatusResponse res = Deserializer.deserializeLogOutResponse(Encoding.Default.GetString(serverBuffer));
            if(res.status == Consts.REQUEST_VALID)
            {
                this.Hide();
                this.Close();
            }

        }
    }
}
