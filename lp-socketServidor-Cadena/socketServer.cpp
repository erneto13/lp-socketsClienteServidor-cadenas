#include <iostream>
#include <winsock2.h>

using namespace std;

class Server{
public:
    WSADATA WSAData; //information about the Windows Sockets implementation.
    SOCKET server, client;
    SOCKADDR_IN serverAddr, clientAddr; //especifica una dirección de transporte y un puerto para la familia de direcciones de AF_INET.
    char buffer[1024];
    Server(){
        WSAStartup(MAKEWORD(2,0), &WSAData); // inicia el uso del archivo DLL de Winsock mediante un proceso.
        server = socket(AF_INET, SOCK_STREAM, 0);

        serverAddr.sin_addr.s_addr = INADDR_ANY;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(8001);//La función htons convierte un u_short del host al orden de bytes de red TCP/IP

        bind(server, (SOCKADDR *)&serverAddr, sizeof(serverAddr));
        listen(server, 0);

        cout << "Escuchando para conexiones entrantes." << endl;
        int clientAddrSize = sizeof(clientAddr);
        if((client = accept(server, (SOCKADDR *)&clientAddr, &clientAddrSize)) != INVALID_SOCKET)
        {
            cout << "Cliente conectado" << endl;
        }
    }

void Recibir() {
    recv(client, buffer, sizeof(buffer), 0);
    cout << "El cliente dice: " << buffer << endl;
    memset(buffer, 0, sizeof(buffer));
}

};


int main()
{
    Server *Servidor = new Server();
    while(true)
    {
        Servidor->Recibir();
    }
}
