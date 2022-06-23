
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Numerics;
namespace GUI
{
    class Consts
    {
        public const int ERR_CODE = 41;
        public const int LOGIN_CODE = 42;
        public const int SIGNUP_CODE = 43;
        public const int LOGOUT_CODE = 44;
        public const int GET_ROOMS_CODE = 45;
        public const int GET_PLAYERS_CODE = 46;
        public const int GET_HIGH_CODE = 47;
        public const int GET_PERSONAL_CODE = 48;
        public const int JOIN_ROOM_CODE = 49;
        public const int CREATE_ROOM_CODE = 50;
        public const int CLOSE_ROOM_CODE = 51;
        public const int START_GAME_CODE = 52;
        public const int GET_ROOM_STATE_CODE = 53;
        public const int LEAVE_ROOM_CODE = 54;

        public const int SUBMIT_ANSWER_CODE = 56;
        public const int GET_QUESTION_CODE = 57;
        public const int LEAVE_GAME_CODE = 58;
        public const int GET_GAME_END_STATS = 55;

        public const int PASSWORD_DONT_MATCH = 41;
        public const int REQUEST_VALID = 42;
        public const int USER_ALREADY_EXIST = 43;
        public const int USER_DONT_EXIST = 44;
        public const int USER_ALREADY_LOGIN = 45;
        public const int ROOM_DONT_EXIST = 46;
        public const int ROOM_MAX_OUT = 47;
        public const int WRONG_PARAMETERS = 48;
        
        public const int ZERO = 126;
        public struct RequestInfo
        {
            public int id;
            public string buffer;
        }
        public struct ResponseInfo
        {
            public int id;
            public int len;
        }
        public struct loginRequest
        {
            public string username;
            public string password;
        }
        public struct signupRequest
        {
            public string username;
            public string password;
            public string email;
        }
        public struct StatusResponse
        {
            public int status;
        }
        public struct ErrorResponse
        {
            public string message;
        }
        public struct CreateRoomRequest
        {
            public string roomName;
            public int maxUsers;
            public int questionCount;
            public int answerTimeout;
        }
        public struct JoinRoomRequest
        {
            public int roomId;
        }
        public struct GetPlayersInRoomRequest
        {
            public int roomId;
        }
        public struct GetPlayersInRoomResponse
        {
            public List<string> players;
        }
        public struct  GetRoomsResponse
        {
            public int status;
            public List<string> rooms;
            public List<int> roomsId;
        }

        public struct getPersonalStatsResponse
        {
            public int status;
            public List<string> statistics;
        }

        public struct GetHighScoreResponse
        {
            public int status;
            public List<string> statistics;
        }
        public struct CloseRoomResponse
        {
            public int status;
        }
        public struct StartGameResponse
        {
            public int status;
        }
        public struct LeaveRoomResponse
        {
            public int status;
        }
        public struct GetRoomStateResponse
        {
            public int status;
            public bool hasGameBegun;
            public List<string> players;
            public int questionCount;
            public float answerTimeout;
        }
        public struct GetQuestionResponce
        {
            public int status;
            public string question;
            public List<string> answers;
            public List<int> IdPerQuestion;
        }
        public struct SubmitAnswerResponse
        {
            public int status;
            public int CorrectAnswerId;
        }
        public struct GetGameResultsResponse
        {
            public int status;
            //4 lists of player result
            public List<string> userName;
            public List<int> correctAnswerCount;
            public List<int> wrongAnswerCount;
            public List<float> averageAnswerTime;
        }
        public struct PlayerResults
        {
            public string userName;
            public int correctAnswerCount;
            public int wrongAnswerCount;
            public float averageAnswerTime;
        }
        public struct LeaveGameResponse
        {

            public int status;
        }
        public struct SubmitAnswerRequest
        {
            public int id;
            public float timePerAns;
        }

    }

}
