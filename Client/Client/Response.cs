using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client
{

        class ErrorResponse
        {
            public string message;
            public ErrorResponse(string message)
            {
                this.message = message;
            }
        }
        class RoomData
        {
            public int id;
            public string name;
            public int maxPlayers;
            public int numOfQuestions;
            public int timePerQuestion;
            public int isActive;

            public RoomData(int id, string name, int maxPlayers, int numOfQuestions, int timePerQuestion, int isActive)
            {
                this.id = id;
                this.name = name;
                this.maxPlayers = maxPlayers;
                this.numOfQuestions = numOfQuestions;
                this.timePerQuestion = timePerQuestion;
                this.isActive = isActive;
            }
        }
        class GetRoomsResponse
        {
            public int status;
            public string[] rooms;
            
            public GetRoomsResponse(int status, string[] rooms)
            {
                this.status = status;
                this.rooms = rooms;
            }
        }

        
}
