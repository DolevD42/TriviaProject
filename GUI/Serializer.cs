using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
namespace GUI
{
    class Serializer
    {
		public static string serializeCodeOnly(int code)
        {
			string msg = "";
			msg += (char)code;
            for (int i = 0; i < 4; i++)
            {
				msg += (char)Consts.ZERO;
            }
			return msg;
        }
		public static string serializeInf(Consts.RequestInfo info)
        {
            string msg = "";
            msg += (char)info.id;
			int num = 0;
			int len = info.buffer.Length;
			for (int i = 3; i >= 0; i--)
			{
				if (i == 0)
				{
					num = len;
				}
				else
				{
					num = (int)len / (int)Math.Pow(256, i);
				}

				len = len - num;
				if (num == 0)
				{
					num = Consts.ZERO;
				}
				msg += (char) num;
			}
			msg += info.buffer;
			return msg;
        }
        public static string serializeMsgLogin(Consts.loginRequest req, int id)
        {
			string buffer = JsonConvert.SerializeObject(req);
			Consts.RequestInfo inf;
			inf.buffer = buffer;
			inf.id = id;
			return serializeInf(inf);
        }
        public static string serializeMsgSign(Consts.signupRequest req, int id)
        {
            string buffer = JsonConvert.SerializeObject(req);
            Consts.RequestInfo inf;
            inf.buffer = buffer;
            inf.id = id;

            return serializeInf(inf);
        }
		public static string serializeMsgCreateRoom(Consts.CreateRoomRequest req, int id)
		{
			string buffer = JsonConvert.SerializeObject(req);
			Consts.RequestInfo inf;
			inf.buffer = buffer;
			inf.id = id;
			return serializeInf(inf);
		}
		public static string serializeMsgJoinRoom(Consts.JoinRoomRequest req, int id)
        {
			string buffer = JsonConvert.SerializeObject(req);
			Consts.RequestInfo inf;
			inf.buffer = buffer;
			inf.id = id;
			return serializeInf(inf);
		}
		public static string serializeMsgGetPlayersInRoom(Consts.GetPlayersInRoomRequest req, int id)
		{
			string buffer = JsonConvert.SerializeObject(req);
			Consts.RequestInfo inf;
			inf.buffer = buffer;
			inf.id = id;
			return serializeInf(inf);
		}
		//public static string serializeGetGameReuslt(Consts.GetGameResultsResponse req, int id)
		//{
		//	string buffer = JsonConvert.SerializeObject(req);
		//	Consts.RequestInfo inf;
		//	inf.buffer = buffer;
		//	inf.id = id;
		//	return serializeInf(inf);
		//}
		public static string serializeSubmitAnswer(Consts.SubmitAnswerRequest req, int id)
		{
			string buffer = JsonConvert.SerializeObject(req);
			Consts.RequestInfo inf;
			inf.buffer = buffer;
			inf.id = id;
			return serializeInf(inf);
		}
	}
}
