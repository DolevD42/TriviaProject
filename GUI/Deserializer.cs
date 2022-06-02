using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
namespace GUI
{
    class Deserializer
    {
        public static Consts.ResponseInfo deserializeSize(string msg)
        {
            Consts.ResponseInfo res;
            res.id = (int)msg[0];
			int msgLen = 0;
			int num = 0;
			for (int i = 0; i < 4; i++)
			{
				num = (int)msg[4 - i];
				if (num == Consts.ZERO)
				{
					num = 0;
				}
				if (i == 0)
				{
					msgLen += num;
				}
				else
				{
					msgLen += num * (int) Math.Pow(256, i);
				}
			}
			res.len = msgLen;
			return res;
        }
		public static Consts.StatusResponse deserializeLoginResponse(string buffer)
		{
			return JsonConvert.DeserializeObject<Consts.StatusResponse>(buffer);
		}
		public static Consts.StatusResponse deserializeSignUpResponse(string buffer)
		{
			return JsonConvert.DeserializeObject<Consts.StatusResponse>(buffer);
		}
		public static Consts.ErrorResponse deserializeErrorResponse(string buffer)
		{
			return JsonConvert.DeserializeObject<Consts.ErrorResponse>(buffer);
		}

	}
}
