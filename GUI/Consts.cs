
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


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
        
        public const int PASSWORD_DONT_MATCH = 41;
        public const int REQUEST_VALID = 42;
        public const int USER_ALREADY_EXIST = 43;
        public const int USER_DONT_EXIST = 44;
        public const int USER_ALREADY_LOGIN = 45;
        public const int ROOM_DONT_EXIST = 46;
        public const int ROOM_MAX_OUT = 47;
        public const int WRONG_PARAMETERS = 48;

        public struct Info
        {
            public int id;
            public string buffer;
        }


    }

}
