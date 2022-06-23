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
    /// Interaction logic for GameEndStats.xaml
    /// </summary>
    public partial class GameEndStats : Window
    {
        private TcpClient _client;
        private string _username;
        private NetworkStream _net;
        private Thread GetStat;
        private bool hasEnd =  false;
        private List<string> _userNames;
        private List<int> _correctAnswerCount;
        private List<int> _wrongAnswerCount;
        private List<float> _averageAnswerTime;
        private List<Consts.PlayerResults> PResult;
        
        public GameEndStats(TcpClient client, string userName)
        {
            InitializeComponent();
            this._client = client;
            this._username = userName;
            NetworkStream net = _client.GetStream();
            _net = net;
            GetStat = new Thread(new ThreadStart(GetStater));
            GetStat.IsBackground = true;
            GetStat.Start();
            //listPlayersAndStats.Items.Add(_userNames);
            //listPlayersAndStats.Items.Add(_correctAnswerCount);
            //listPlayersAndStats.Items.Add(_wrongAnswerCount);
            //listPlayersAndStats.Items.Add(_averageAnswerTime);
        }
        private void GetStater()
        {
            do
            {
                string msgToSent = Serializer.serializeCodeOnly(Consts.GET_GAME_END_STATS);//getting game state
                _net.Write(System.Text.Encoding.ASCII.GetBytes(msgToSent), 0, msgToSent.Length);
                byte[] serverMsg = new byte[5];
                _net.Read(serverMsg, 0, 5);
                Consts.ResponseInfo resInf = Deserializer.deserializeSize(Encoding.Default.GetString(serverMsg));//getting the state
                if (resInf.id == Consts.ERR_CODE)
                {
                    byte[] errorBuffer = new byte[resInf.len];
                    _net.Read(errorBuffer, 0, resInf.len);
                    Consts.ErrorResponse err = Deserializer.deserializeErrorResponse(Encoding.Default.GetString(errorBuffer));
                    MessageBox.Show(err.message, "Trivia Client", MessageBoxButton.OK, MessageBoxImage.Error);
                    return;
                }
                byte[] serverBuffer = new byte[resInf.len];

                _net.Read(serverBuffer, 0, resInf.len);
                Consts.GetGameResultsResponse res = Deserializer.deserializeGetGameResultsResponse(Encoding.Default.GetString(serverBuffer));//getting the game req
                if(res.status != Consts.REQUEST_VALID)
                {
                    continue;
                }

                /*for (int i = 0; i < res.userName.Count; i++)
                {
                    if (!_userNames.Contains(res.userName[i]))
                    {//if user not in list
                        Console.WriteLine("switched not zero ", _userNames[i].ToString(), _wrongAnswerCount[i], _correctAnswerCount[i].ToString(), _averageAnswerTime[i]);
                        this.Dispatcher.Invoke(() =>
                        {//adding the new user
                            _userNames.Add(res.userName[i]);
                            _correctAnswerCount.Add(res.correctAnswerCount[i]);
                            _wrongAnswerCount.Add(res.wrongAnswerCount[i]);
                            _averageAnswerTime.Add(res.averageAnswerTime[i]);
                            //listPlayersAndStats.Items.Add("Username:" + res.userName[i] +"\n");
                            //listPlayersAndStats.Items.Add("Username:" + res.wrongAnswerCount[i] + "\n");
                            //listPlayersAndStats.Items.Add("Username:" + res.averageAnswerTime[i] + "\n");
                            //listPlayersAndStats.Items.Add("Username:" + res.correctAnswerCount[i] + "\n");
                        });
                    }
                    if (_userNames.Contains(res.userName[i]) && (!_wrongAnswerCount.Contains(res.wrongAnswerCount[i]) || !_correctAnswerCount.Contains(res.correctAnswerCount[i]) || !_averageAnswerTime.Contains(res.averageAnswerTime[i])))//if player is in there but score diffrent
                    {//update user profile
                        _userNames.Remove(_userNames[i]);
                        _correctAnswerCount.Remove(_correctAnswerCount[i]);
                        _wrongAnswerCount.Remove(_wrongAnswerCount[i]);
                        _averageAnswerTime.Remove(_averageAnswerTime[i]);
                        _userNames.Add(res.userName[i]);
                        _correctAnswerCount.Add(res.correctAnswerCount[i]);
                        _wrongAnswerCount.Add(res.wrongAnswerCount[i]);
                        _averageAnswerTime.Add(res.averageAnswerTime[i]);
                        listPlayersAndStats.Items.Remove("Username:" + _userNames[i] + "\n");
                        listPlayersAndStats.Items.Remove("Username:" +_averageAnswerTime[i] + "\n");
                        listPlayersAndStats.Items.Remove("Username:" + _wrongAnswerCount[i] + "\n");
                        listPlayersAndStats.Items.Remove("Username:" + _correctAnswerCount[i] + "\n");//deleting old stats
                        //listPlayersAndStats.Items.Add("Username:" + res.userName[i] + "\n");//adding new stats
                        //listPlayersAndStats.Items.Add("Username:" + res.wrongAnswerCount[i] + "\n");
                        //listPlayersAndStats.Items.Add("Username:" + res.averageAnswerTime[i] + "\n");
                        //listPlayersAndStats.Items.Add("Username:" + res.correctAnswerCount[i] + "\n");
                    }

                }
                Consts.PlayerResults curRes;
                for (int i = 0; i < _userNames.Count; i++)
                {
                    curRes.userName = _userNames[i];
                    curRes.correctAnswerCount = _correctAnswerCount[i];
                    curRes.averageAnswerTime = _averageAnswerTime[i];
                    curRes.wrongAnswerCount = _wrongAnswerCount[i];
                    PResult.Add(curRes);
                    _userNames.Remove(_userNames[i]);
                    _correctAnswerCount.Remove(_correctAnswerCount[i]);
                    _wrongAnswerCount.Remove(_wrongAnswerCount[i]);
                    _averageAnswerTime.Remove(_averageAnswerTime[i]);
                }
                
                Consts.PlayerResults temp;
                for (int j = 0; j <= PResult.Count - 2; j++)
                {
                    for (int i = 0; i <= PResult.Count - 2; i++)
                    {
                        if (PResult[i].correctAnswerCount > PResult[i + 1].correctAnswerCount)
                        {
                            temp = PResult[i + 1];
                            PResult[i + 1] = PResult[i];
                            PResult[i] = temp;
                        }
                    }
                }
                for (int i = 0; i < PResult.Count; i++)
                {
                    listPlayersAndStats.Items.Add(i +" Place" + "Username:" + PResult[i].userName +", ");
                    listPlayersAndStats.Items.Add("wrong Answers:" + PResult[i].wrongAnswerCount + ", ");
                    listPlayersAndStats.Items.Add("Average Time:" + PResult[i].averageAnswerTime + ", ");
                    listPlayersAndStats.Items.Add("correct answers:" + PResult[i].correctAnswerCount + "\n");
                }
                PResult.Clear();
                */
                for (int i = 0; i < res.userName.Count; i++)
                {
                    this.Dispatcher.Invoke(() =>
                    {
                        listPlayers.Items.Add((i + 1).ToString() +". " + res.userName[i]);
                        listCorrectAnswers.Items.Add(res.correctAnswerCount[i]);
                        listWrongAnswers.Items.Add(res.wrongAnswerCount[i]);
                        listAverageTime.Items.Add(res.averageAnswerTime[i]);
                    });
                }
                int winnerPlace = 0;
                float result1 = 0;
                float result2 = 0;
                for (int i = 1; i < res.userName.Count; i++)
                {
                    result1 = res.correctAnswerCount[winnerPlace] / ((res.correctAnswerCount[winnerPlace] + res.wrongAnswerCount[winnerPlace]) * res.averageAnswerTime[winnerPlace]);
                    result2 = res.correctAnswerCount[i] / ((res.correctAnswerCount[i] + res.wrongAnswerCount[i]) * res.averageAnswerTime[i]);
                    if (result2 > result1)
                    {
                        winnerPlace = i;
                    }
                }
                this.Dispatcher.Invoke(() =>
                {
                    Title.Text = "Winner: " + res.userName[winnerPlace];
                });
                Thread.Sleep(3);
                hasEnd = true;
            } while(!hasEnd);

        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            //getting into the game result
            string msgToSent = Serializer.serializeCodeOnly(Consts.LEAVE_GAME_CODE);//getting game state
            _net.Write(System.Text.Encoding.ASCII.GetBytes(msgToSent), 0, msgToSent.Length);
            byte[] serverMsg = new byte[5];
            _net.Read(serverMsg, 0, 5);
            Consts.ResponseInfo resInf = Deserializer.deserializeSize(Encoding.Default.GetString(serverMsg));//getting the state
            if (resInf.id == Consts.ERR_CODE)
            {
                byte[] errorBuffer = new byte[resInf.len];
                _net.Read(errorBuffer, 0, resInf.len);
                Consts.ErrorResponse err = Deserializer.deserializeErrorResponse(Encoding.Default.GetString(errorBuffer));
                MessageBox.Show(err.message, "Trivia Client", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }
            byte[] serverBuffer = new byte[resInf.len];

            _net.Read(serverBuffer, 0, resInf.len);
            Consts.LeaveGameResponse res = Deserializer.deserializeLeaveGameResponse(Encoding.Default.GetString(serverBuffer));//getting the game req
            if(res.status == Consts.REQUEST_VALID)
            {
                this.Hide();
                Menu win = new Menu(_client, _username);
                this.Close();
                win.Show();
            }
        }
    }
}
