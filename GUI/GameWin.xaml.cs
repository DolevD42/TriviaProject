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
            string msgToSent = Serializer.serializeCodeOnly(Consts.GET_ROOM_STATE_CODE);
            
        }
        public delegate void TickCallback();
        public delegate int ClockCallback();
        /// <summary>
        /// The Main Function for the thread.
        /// </summary>
        private void Tick()
        {
            while (!Clock.Dispatcher.Invoke(new ClockCallback(ClockTime)).Equals(0))
            {
                Thread.Sleep(1000);
                Clock.Dispatcher.Invoke(new TickCallback(Timer_Tick));
            }

        }

        void Timer_Tick()
        {
            Clock.Text = (Convert.ToInt16(Clock.Text) - 1).ToString();
        }

        int ClockTime()
        {
            return Convert.ToInt32(Clock.Text);
        }
    }
}
