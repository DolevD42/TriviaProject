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


        }
        private void Statistics_Button(object sender, RoutedEventArgs e)
        {


        }
        private void Quit_Button_Button(object sender, RoutedEventArgs e)
        {


        }
    }
}
