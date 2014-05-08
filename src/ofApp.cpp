#include "ofApp.h"

#define TCP_PORT 3333
#define UDP_HOST "127.0.0.1"
#define UDP_PORT 4444
#define BUFFER_SIZE 1024

//--------------------------------------------------------------
void ofApp::setup(){
    initTCP();
    initUDP();
}

//--------------------------------------------------------------
void ofApp::update(){
    char buff[BUFFER_SIZE];
    
    if (!tcpServer.isConnected()) {
        initTCP(); // reinitialize
    }
    
    for(int i = 0; i < tcpServer.getLastID(); i++) // getLastID is UID of all clients
    {
        
        if( tcpServer.isClientConnected(i) ) { // check and see if it's still around
            // maybe the client is sending something
            int bytes = tcpServer.receiveRawBytes(i, buff, BUFFER_SIZE);
            if (bytes > 0) {
                ofLog() << "bytes: " << bytes;
                
                int res = udpSender.Send(buff, bytes);
                if (res == SOCKET_ERROR) {
                    initUDP();
                    udpSender.Send(buff, bytes);
                }
            }
        }
    }
    
    
}

void ofApp::exit() {
    tcpServer.close();
    udpSender.Close();
}

void ofApp::initTCP() {
    tcpServer.close();
    tcpServer.setup(TCP_PORT, true);
}

void ofApp::initUDP() {
    udpSender.Close();
    udpSender.Create();
    udpSender.SetNonBlocking(true);
    udpSender.Connect(UDP_HOST, UDP_PORT);
}