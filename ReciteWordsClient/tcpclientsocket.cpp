#include "tcpclientsocket.h"
#include <QThread>
#include <QMessageBox>

extern int status;
TcpClientSocket::TcpClientSocket()
{

}

TcpClientSocket::TcpClientSocket(QString ip, QString port,QString nickName)
{
    connect(this,SIGNAL(connected()),this,SLOT(slotConnected()));
    connect(this,SIGNAL(readyRead()),this,SLOT(dataReceived()));
    this->nickName = nickName;
    serverIP = new QHostAddress();
    serverIP->setAddress(ip);
    int portNum = port.toLong();
    if(SWITCH)qDebug() << "TcpClientSocket Constuctor:"<< *serverIP << "  " << portNum << " " << nickName;
    this->connectToHost(*serverIP,portNum);

    connect(this,SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(handleConnectionError(QAbstractSocket::SocketError)));

}

TcpClientSocket::TcpClientSocket(QObject *parent)
{

}
TcpClientSocket::~TcpClientSocket()
{
    if(SWITCH)qDebug()<< "~TcpClientSocket disconnected";
    QMessageBox::warning(NULL, "warning", "网络异常，请检查网络连接");
    delete serverIP;
}

void TcpClientSocket::dataReceived()
{
    while(bytesAvailable()>0){
        char buf[1024];
        int length = bytesAvailable();
        this->read(buf,length);
        QString msg = buf;

        if(msg.count("Header") == 2){
            QString msg1,msg2;
            int index = msg.indexOf("{",1);
            msg1 = msg.left(index);
            msg2 = msg.mid(index);
            if(msg1.count("LEAVE") >= 1){
                emit updateClients(msg1,msg1.length());
            }
            else {
                emit updateClients(msg2,msg2.length());
            }
        }

        //注意这里的this->peerPort()和this->peerAddress()均是本机的，原因是不是tcpserver
        else emit updateClients(msg,length);
    }
}

void TcpClientSocket::disconnected()
{
    int length = 0;
    status=0;
    //发送LEAVE json数据
    QJsonObject json;
    json.insert("Header","LEAVE");          //DATA:打字数据，MSG:弹幕信息；CHAT:私聊；LIVE:离开
    json.insert("name", "");                //
    json.insert("speed", 0);                //打字速度
    json.insert("accuracy","");             //正确率
    json.insert("time",0);                  //在线时间(s)
    json.insert("to","");                   //与谁私聊，另开端口
    QJsonDocument document;
    document.setObject(json);
    QByteArray byte_array = document.toJson(QJsonDocument::Compact);
    QString jsonStr(byte_array);

    if((length = this->write(jsonStr.toUtf8(),jsonStr.length())) != jsonStr.length()){
        return;
    }
    //延时，等待发送完成
    QThread::msleep(400);
    this->disconnectFromHost();             //与Tcp服务器连接，发送离开信息
}

void TcpClientSocket::slotConnected()
{
    if(SWITCH)qDebug()<< "slotConnected";
     status=1;
    int length = 0;
    //发送LOGIN json数据
    QJsonObject json;
    json.insert("Header","LOGIN");          //DATA:打字数据，MSG:弹幕信息；CHAT:私聊；
    json.insert("name", nickName);          //My name
    json.insert("to","");                   //与谁私聊，另开端口
    json.insert("speed", 0);                //打字速度
    json.insert("accuracy","0%");           //正确率
    json.insert("time",0);                  //在线时间(s)
    QJsonDocument document;
    document.setObject(json);
    QByteArray byte_array = document.toJson(QJsonDocument::Compact);
    QString jsonStr(byte_array);

    if((length = this->write(jsonStr.toUtf8(),jsonStr.length())) != jsonStr.length()){
        return;
    }
}

void TcpClientSocket::handleConnectionError(QAbstractSocket::SocketError error)
{
    QString errorString;
    switch(error)
    {
    case QAbstractSocket::ConnectionRefusedError:
        errorString = "Connection refused!";
        break;
    case QAbstractSocket::RemoteHostClosedError:
        errorString = "Remote host closed.";
        break;
    case QAbstractSocket::HostNotFoundError:
        errorString = "Host not found!";
        break;
    case QAbstractSocket::NetworkError:
        errorString = "Network error!";
        break;
    case QAbstractSocket::AddressInUseError:
        errorString = "Address already in use!";
        break;
    case QAbstractSocket::UnknownSocketError:
    default:
        errorString = "Unknown socket error!";
        break;
    }

    QMessageBox::warning( NULL,("Warning"), errorString);
}

