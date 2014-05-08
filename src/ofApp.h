#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void exit();
    
private:
    void initTCP();
    void initUDP();
    
    ofxTCPServer tcpServer;
    ofxUDPManager udpSender;
};
