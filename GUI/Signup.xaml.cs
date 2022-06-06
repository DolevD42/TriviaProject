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
            string password = inputPassword.Password;
            string email = inputEmail.Text;

            Consts.signupRequest req;
            req.username = userName;
            req.password = password;
            req.email = email;
            string msgToSent = Serializer.serializeMsgSign(req, Consts.SIGNUP_CODE);
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
            Consts.StatusResponse res = Deserializer.deserializeSignUpResponse(Encoding.Default.GetString(serverBuffer));
            inputUsername.Text = "";
            inputPassword.Password = "";
            inputEmail.Text = "";
            switch (res.status)
            {
                case Consts.USER_ALREADY_EXIST:
                    MessageBox.Show("The user is already exist", "Trivia Client", MessageBoxButton.OK, MessageBoxImage.Exclamation);
                    break;
                case Consts.REQUEST_VALID:
                    this.Hide();
                    Menu win = new Menu(_client, userName);
                    this.Close();
                    win.Show();
                    break;
            }

        }
    }
}
