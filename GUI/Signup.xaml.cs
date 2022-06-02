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
    /// Interaction logic for Window1.xaml
    /// </summary>
    public partial class Signup : Window
    {
        private TcpClient _client;
        public Signup(TcpClient client)
        {
            InitializeComponent();
            _client = client;
        }
        private void Button_Click(object sender, RoutedEventArgs e)
        {
            string userName = inputUsername.Text;
            string password = inputPassword.Text;
            string email = inputEmail.Text;
            string msgToSent;

            //Consts.Info res;

        }
    }
}
