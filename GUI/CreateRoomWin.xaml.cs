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

namespace GUI
{
    /// <summary>
    /// Interaction logic for StatsWin.xaml
    /// </summary>
    public partial class CreateRoomWin : Window
    {
        public CreateRoomWin()
        {
            InitializeComponent();
        }
        private void But_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                string _RoomName, _PlayersNumber, _QuestionNumber, _QuestionTime;
                _RoomName = RoomName.Text;
                _PlayersNumber = PlayersNumber.Text;
                _QuestionNumber = QuestionsNumber.Text;
                _QuestionTime = QuestionTime.Text;

            }
            catch (Exception Exc) { ErrorMessage.Content = "Server Error... Please go out of this page and try again..."; }
        }
    }
}
