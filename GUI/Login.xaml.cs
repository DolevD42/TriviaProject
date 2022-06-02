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
            Consts.loginRequest req;
            req.username = userName;
            req.password = password;
            string msgToSent = Serializer.serializeMsg(req, Consts.LOGIN_CODE);
            NetworkStream net = _client.GetStream();
            net.Write(System.Text.Encoding.ASCII.GetBytes(msgToSent), 0, msgToSent.Length);
            byte[] serverMsg = new byte[5];
            net.Read(serverMsg, 0, 5);
            Consts.ResponseInfo resInf = Deserializer.deserializeSize(Encoding.Default.GetString(serverMsg));
            if(resInf.id == Consts.ERR_CODE)
            {
                byte[] errorBuffer = new byte[resInf.len];
                net.Read(errorBuffer, 0, resInf.len);
                Consts.ErrorResponse err = Deserializer.deserializeErrorResponse(Encoding.Default.GetString(errorBuffer));
                MessageBox.Show(err.msg, "Trivia Client", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }
            byte[] serverBuffer = new byte[resInf.len];

            net.Read(serverBuffer, 0, resInf.len);
            Consts.StatusResponse res = Deserializer.deserializeLoginResponse(Encoding.Default.GetString(serverBuffer));
            inputUsername.Text = "";
            inpPass.Password = "";
            switch (res.status)
            {
                case Consts.USER_DONT_EXIST:
                    MessageBox.Show("The username you enter doesn't exist", "Trivia Client", MessageBoxButton.OK, MessageBoxImage.Exclamation);
                    break;
                case Consts.PASSWORD_DONT_MATCH:
                    MessageBox.Show("The password you enter doesn't match the username", "Trivia Client", MessageBoxButton.OK, MessageBoxImage.Exclamation);
                       break;
                case Consts.USER_ALREADY_LOGIN:
                    MessageBox.Show("User already logged in", "Trivia Client", MessageBoxButton.OK, MessageBoxImage.Exclamation);
                    break;
                case Consts.REQUEST_VALID:
                    this.Hide();
                    Menu win = new Menu(_client, userName);
                    this.Close();
                    break;
            }
        }

        }
    }
}
