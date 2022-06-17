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
        private float time;
        private float timeConst;
        private Thread Timer;
        private TcpClient _client;
        private string _username;
        private NetworkStream _net;
        private int questionCount;
        private bool button1WasClicked = false;
        private bool button2WasClicked = false;
        private bool button3WasClicked = false;
        private bool button4WasClicked = false;
        public GameWin(TcpClient client, string username, float _time, int questCount)
        {
            InitializeComponent();
            this._client = client;
            this._username = username;
            NetworkStream net = _client.GetStream();
            _net = net;
            string msgToSent = Serializer.serializeCodeOnly(Consts.GET_QUESTION_CODE);//getting game state
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
            Consts.GetQuestionResponce res = Deserializer.deserializeGetQuestionResponse(Encoding.Default.GetString(serverBuffer));//getting the game req
            
            time = _time;
            timeConst = _time;
            questionCount = questCount;
            Question.Text = res.question;
            Ans1.Text = res.answers[0];
            Ans2.Text = res.answers[1];
            Ans3.Text = res.answers[2];
            Ans4.Text = res.answers[3];
            Thread newThread = new Thread(new ThreadStart(Tick));
            Timer = newThread;
            Timer.Start();
        }
        /// <summary>
        /// The Main Function for the thread.
        /// </summary>
        private void Tick()
        {
            if (questionCount != 0)
            {
                questionCount -= 1;
                while (time != 0.0)
                {
                    Clock.Text = time.ToString();
                    Thread.Sleep(1000);
                    this.Dispatcher.Invoke(() =>
                    {
                        time -= 1;
                    });
                }
                if (time == 0.0)
                {
                    //sending the massage automaticly if dident sended
                    if (!button4WasClicked && !button3WasClicked && !button2WasClicked && !button1WasClicked)
                    {
                        //sending answer -1
                        Consts.SubmitAnswerRequest req;
                        req.id = -1;
                        req.timePerAns = timeConst;
                        string msgToSent = Serializer.serializeSubmitAnswer(req, Consts.SUBMIT_ANSWER_CODE);
                        _net.Write(System.Text.Encoding.ASCII.GetBytes(msgToSent), 0, msgToSent.Length);
                        byte[] serverMsg = new byte[5];
                        _net.Read(serverMsg, 0, 5);
                        Consts.ResponseInfo resInf = Deserializer.deserializeSize(Encoding.Default.GetString(serverMsg));
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
                        Consts.SubmitAnswerResponse resSendAns = Deserializer.deserializeSubmitedAnswerResponse(Encoding.Default.GetString(serverBuffer));//getting the game req
                        //getting error for answer -1
                        int idAns = resSendAns.idForCorrectAnswer;                                                                                                                //refreshing timer again
                        time = timeConst;
                    }
                    else
                    {
                        //getting the new question
                        string msgToSent = Serializer.serializeCodeOnly(Consts.GET_QUESTION_CODE);
                        _net.Write(System.Text.Encoding.ASCII.GetBytes(msgToSent), 0, msgToSent.Length);
                        byte[] serverMsg = new byte[5];
                        _net.Read(serverMsg, 0, 5);
                        Consts.ResponseInfo resInf = Deserializer.deserializeSize(Encoding.Default.GetString(serverMsg));
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
                        Consts.GetQuestionResponce res = Deserializer.deserializeGetQuestionResponse(Encoding.Default.GetString(serverBuffer));//getting the game req
                        Question.Text = res.question;
                        Ans1.Text = res.answers[0];
                        Ans2.Text = res.answers[1];
                        Ans3.Text = res.answers[2];
                        Ans4.Text = res.answers[3];
                        time = timeConst;
                    }

                }
            }
            else
            {
                Timer.Abort();
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
                    MessageBox.Show(err.msg, "Trivia Client", MessageBoxButton.OK, MessageBoxImage.Error);
                    return;
                }
                byte[] serverBuffer = new byte[resInf.len];

                _net.Read(serverBuffer, 0, resInf.len);
                Consts.LeaveGameResponse res = Deserializer.deserializeLeaveGameResponse(Encoding.Default.GetString(serverBuffer));//getting the game req
                this.Hide();
                //Menu win = new Menu(_client, _username);
                //win.Show(); showing the new screen
                this.Close();
            }

        }
        private void Answer4_Click(object sender, RoutedEventArgs e)
        {
            button4WasClicked = true;
            Consts.SubmitAnswerRequest req;
            req.id = 3;
            req.timePerAns = time;
            string msgToSent = Serializer.serializeSubmitAnswer(req, Consts.SUBMIT_ANSWER_CODE);
            _net.Write(System.Text.Encoding.ASCII.GetBytes(msgToSent), 0, msgToSent.Length);
            byte[] serverMsg = new byte[5];
            _net.Read(serverMsg, 0, 5);
            Consts.ResponseInfo resInf = Deserializer.deserializeSize(Encoding.Default.GetString(serverMsg));
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
            Consts.SubmitAnswerResponse resSendAns = Deserializer.deserializeSubmitedAnswerResponse(Encoding.Default.GetString(serverBuffer));//getting the game req                                                                                                                               //getting error for answer -1
            int idAns = resSendAns.idForCorrectAnswer;
            if (idAns == 3)
            {
                MessageBox.Show("you got the right answer");
            }
            else
            {
                MessageBox.Show("you got the wrong answer");
            }
            time = timeConst;
        }
        private void Answer3_Click(object sender, RoutedEventArgs e)
        {
            button3WasClicked = true;
            Consts.SubmitAnswerRequest req;
            req.id = 2;
            req.timePerAns = time;
            string msgToSent = Serializer.serializeSubmitAnswer(req, Consts.SUBMIT_ANSWER_CODE);
            _net.Write(System.Text.Encoding.ASCII.GetBytes(msgToSent), 0, msgToSent.Length);
            byte[] serverMsg = new byte[5];
            _net.Read(serverMsg, 0, 5);
            Consts.ResponseInfo resInf = Deserializer.deserializeSize(Encoding.Default.GetString(serverMsg));
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
            Consts.SubmitAnswerResponse resSendAns = Deserializer.deserializeSubmitedAnswerResponse(Encoding.Default.GetString(serverBuffer));//getting the game req                                                                                                                               //getting error for answer -1
            int idAns = resSendAns.idForCorrectAnswer;
            if (idAns == 2)
            {
                MessageBox.Show("you got the right answer");
            }
            else
            {
                MessageBox.Show("you got the wrong answer");
            }
            time = timeConst;
        }
        private void Answer2_Click(object sender, RoutedEventArgs e)
        {
            button2WasClicked = true;
            Consts.SubmitAnswerRequest req;
            req.id = 1;
            req.timePerAns = time;
            string msgToSent = Serializer.serializeSubmitAnswer(req, Consts.SUBMIT_ANSWER_CODE);
            _net.Write(System.Text.Encoding.ASCII.GetBytes(msgToSent), 0, msgToSent.Length);
            byte[] serverMsg = new byte[5];
            _net.Read(serverMsg, 0, 5);
            Consts.ResponseInfo resInf = Deserializer.deserializeSize(Encoding.Default.GetString(serverMsg));
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
            Consts.SubmitAnswerResponse resSendAns = Deserializer.deserializeSubmitedAnswerResponse(Encoding.Default.GetString(serverBuffer));//getting the game req                                                                                                                               //getting error for answer -1
            int idAns = resSendAns.idForCorrectAnswer;
            if (idAns == 1)
            {
                MessageBox.Show("you got the right answer");
            }
            else
            {
                MessageBox.Show("you got the wrong answer");
            }
            time = timeConst;
        }
        private void Answer1_Click(object sender, RoutedEventArgs e)
        {
            button1WasClicked = true;
            Consts.SubmitAnswerRequest req;
            req.id = 0;
            req.timePerAns = time;
            string msgToSent = Serializer.serializeSubmitAnswer(req, Consts.SUBMIT_ANSWER_CODE);
            _net.Write(System.Text.Encoding.ASCII.GetBytes(msgToSent), 0, msgToSent.Length);
            byte[] serverMsg = new byte[5];
            _net.Read(serverMsg, 0, 5);
            Consts.ResponseInfo resInf = Deserializer.deserializeSize(Encoding.Default.GetString(serverMsg));
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
            Consts.SubmitAnswerResponse resSendAns = Deserializer.deserializeSubmitedAnswerResponse(Encoding.Default.GetString(serverBuffer));//getting the game req                                                                                                                               //getting error for answer -1
            int idAns = resSendAns.idForCorrectAnswer;
            if (idAns == 0)
            {
                MessageBox.Show("you got the right answer");
            }
            else
            {
                MessageBox.Show("you got the wrong answer");
            }
            time = timeConst;
        }
    }
}
