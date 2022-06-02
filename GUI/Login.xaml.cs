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
    /// Interaction logic for Login.xaml
    /// </summary>
    public partial class Login : Window
    {
        private TcpClient _client;
        public Login()
        {  
            InitializeComponent();
            _client = new TcpClient();
            _client.Connect("127.0.0.1", 8876);
        }
        private void Button_Click(object sender, RoutedEventArgs e)
        {
            string userName = inputUsername.Text;
            string password = inpPass.Password;
            string msgToSent;

            Consts.Info res;

        }
    }
}
