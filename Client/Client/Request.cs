using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client
{
        class LoginRequest
        {
            public string username;
            public string password;
            
            public LoginRequest(string username, string password)
            {
                this.username = username;
                this.password = password;
            }
        }

        class SignUpRequest
        {
            public string username;
            public string password;
            public string mail;

            public SignUpRequest(string username, string password, string mail)
            {
                this.username = username;
                this.password = password;
                this.mail = mail;
            }
        }


        class CreateRoomRequest
        {
            public string name;
            public int max;
            public int count;
            public int time;

            public CreateRoomRequest(string name, int max, int count, int time)
            {
                this.name = name;
                this.max = max;
                this.count = count;
                this.time = time;
            }
    }

        class GetPlayersInRoomRequest
        {
            public int roomId;
                
            public GetPlayersInRoomRequest(int roomId)
            {
                this.roomId = roomId;
            }
    }

        class JoinRoomRequest
        {
            public int id;
            public JoinRoomRequest(int roomId)
            {
                this.id = roomId;
            }
        }

        class SubmitAnswerRequest
        {
            public int answerId;
            public SubmitAnswerRequest(int ans)
            {
                answerId = ans;
            }
        };

}
