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
    /// Interaction logic for GameWin.xaml
    /// </summary>
    public partial class GameWin : Window
    {           
        private int time;
        private Thread Timer;
        private TcpClient _client;
        private string _username;
        private NetworkStream _net;
        public GameWin(TcpClient client, string username)
        {
            InitializeComponent();
            this._client = client;
            this._username = username;
            NetworkStream net = _client.GetStream();
            _net = net;
            string msgToSent = Serializer.serializeCodeOnly(Consts.GET_ROOM_STATE_CODE);//getting game state
            _net.Write(System.Text.Encoding.ASCII.GetBytes(msgToSent), 0, msgToSent.Length);
            byte[] serverMsg = new byte[5];
            _net.Read(serverMsg, 0, 5);
            Consts.ResponseInfo resInf = Deserializer.deserializeSize(Encoding.Default.GetString(serverMsg));//getting the state
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
            Consts.GetRoomStateResponse res = Deserializer.deserializeGetRoomStateResponse(Encoding.Default.GetString(serverBuffer));//getting the game req
            time = 30;//just for check
            Thread newThread = new Thread(new ThreadStart(Tick));
            Timer = newThread;
            Timer.Start();
        }
        /// <summary>
        /// The Main Function for the thread.
        /// </summary>
        private void Tick()
        {
            while (time != 0)
            {
                Clock.Text = time.ToString();
                Thread.Sleep(1000);
                time -= 1;
            }
        }
        private void Answer4_Click(object sender, RoutedEventArgs e)
        {}
        private void Answer3_Click(object sender, RoutedEventArgs e)
        { }
        private void Answer2_Click(object sender, RoutedEventArgs e)
        { }
        private void Answer1_Click(object sender, RoutedEventArgs e)
        { }
    }
}
