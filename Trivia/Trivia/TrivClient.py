import socket
import json
# קלט מספר פורט מהמשתמש
def bin_to_str(x):
    ''' Converts a Binary String to an (ASCII) string'''
    my_int = my_int = int(x, base=2)
    my_str = my_int.to_bytes((my_int.bit_length() + 7)//8, 'big').decode()
    return my_str

def string_to_binary(s):
    # Convert the string to a bytes object using UTF-8 encoding
    b = bytes(s, 'utf-8')
    # Convert the bytes object to a binary string
    binary_str = ''.join(['{0:08b}'.format(byte) for byte in b])
    return binary_str

def int_to_binary(num):
    # Convert the integer to binary using the built-in bin() function
    binary_str = bin(num)
    # Remove the '0b' prefix that is added by the bin() function
    binary_str = binary_str[2:]
    return binary_str

port = int(input("Please enter port number (1024-65535): "))
if port < 1024 or port > 65535:
    print("Invalid port number")
    exit()

# יצירת חיבור עם השרת
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect(('localhost', port))

# קליטת נתונים מהשרת והדפסתם
message_send = ""
login = {"username": "user1", "password": 1234}
signUp = {"username": "user1", "password": 1234, "mail": "ggg@gmail.com"}
choice = int(input("enter 1 for signUp and 2 for login: "))
if(choice == 1):
    signUp["username"] = input("enter name: ")
    signUp["password"] = input("enter password: ")
    signUp["mail"] = input("enter mail: ")
    JsonStr = json.dumps(signUp)
    size = len(JsonStr)
    print(size)
    sizeStr = int_to_binary(size)
    count = len(sizeStr)
    while count < 32:
        sizeStr = "0" + sizeStr
        count += 1
    message_send = "00001011"
    message_send += sizeStr
    message_send += string_to_binary(JsonStr)
elif(choice == 2):
    login["username"] = input("enter name: ")
    login["password"] = input("enter password: ")
    JsonStr = json.dumps(login)
    size = len(JsonStr)
    print(size)
    sizeStr = int_to_binary(size)
    count = len(sizeStr)
    while count < 32:
        sizeStr = "0" + sizeStr
        count += 1
    message_send = "00000001"
    message_send += sizeStr
    message_send += string_to_binary(JsonStr)

print(message_send)
client_socket.send(message_send.encode())
response = client_socket.recv(8).decode()
print(response)
response = client_socket.recv(32).decode()
print(response)
response = bin_to_str(client_socket.recv(1024).decode())
print(response)
# סגירת החיבור
while True:
    x = 0
client_socket.close()
