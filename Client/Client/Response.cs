using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
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

    class GetRoomStateResponse
    {
        public int status;
        public bool hasGameBegun;
        public string[] players;
        public int questionCount;
        public int answerTimeout; 
        public GetRoomStateResponse(int s, bool h, string[] p, int q, int a)
        {
            status = s;
            hasGameBegun = h;
            players = p;
            questionCount = q;
            answerTimeout = a;
        }
    };

    class Response
    {
        public int status;
        public Response(int status)
        {
            this.status = status;
        }
    }

    class PlayerResults
    {
        public string username;
        public float averageAnswerTime;
        public int correctAnswerCount;
        public int answerTimeout;

        public PlayerResults(string name, float ave, int cor, int time)
        {
            username = name;
            averageAnswerTime = ave;
            correctAnswerCount = cor;
            answerTimeout = time;
        }
    };


    class GetGameResultsResponse
    {
        public int status;
        public PlayerResults[] results;
        public GetGameResultsResponse(int sta, PlayerResults[] res)
        {
            results = res;
            status = sta;
        }
    };

    class SubmitAnswerResponse
    {
        public int status;
        public int correctAns;
        public SubmitAnswerResponse(int sta, int cor)
        {
            status = sta;
            correctAns = cor;
        }
    };

    class GetQuestionResponse
    {
        public int status;
        public string question;
        public int[] id;
        public string[] answer;
        public GetQuestionResponse(int sta, string q, int[] i, string[] ans)
        {
            status = sta;
            question = q;
            id = i;
            answer = ans; 
        }
    };

}
