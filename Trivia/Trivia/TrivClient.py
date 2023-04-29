import socket

# קלט מספר פורט מהמשתמש
port = int(input("Please enter port number (1024-65535): "))
if port < 1024 or port > 65535:
    print("Invalid port number")
    exit()

# יצירת חיבור עם השרת
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect(('localhost', port))

# קליטת נתונים מהשרת והדפסתם
data = client_socket.recv(5)
print(data.decode())

# בדיקה אם הנתונים הם "Hello " והחזרת התשובה המתאימה
if data.decode() == "Hello":
    client_socket.sendall("Hello ".encode())
    response = client_socket.recv(5)
    print(response.decode())
else:
    print("Error: servers invalid input")

# סגירת החיבור
client_socket.close()


