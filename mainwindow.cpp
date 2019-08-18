#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

#include <QLabel>
#include <QGraphicsItem>
#include <stdio.h>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <QDateTime>
#include <QTimer>
#include <QMatrix>
#include <QTransform>
#include <QWidget>
#include <QColor>
#include <string>


using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_SendButton_clicked()
{
    cout << ui->Insert->text().toStdString() <<endl;
    sendJSON("INSERT",ui->Insert->text().toStdString().c_str());
}


int MainWindow::sendJSON(string KEY, string data){
    char* str;
    int fd, numbytes;
    struct sockaddr_in client;

    fd = socket(AF_INET, SOCK_STREAM, 0);

    char sendBuff[MAXDATASIZE];
    char recvBuff[MAXDATASIZE];

    struct hostent *he;

    if (fd < 0)
    {
        printf("Error : Could not create socket\n");
        return 1;
    }
    else
    {
        client.sin_family = AF_INET;
        client.sin_port = htons(PORT);
        client.sin_addr.s_addr = inet_addr("127.0.0.1"); //192.168.100.6
        memset(client.sin_zero, '\0', sizeof(client.sin_zero));
    }

    if (::connect(fd, (const struct sockaddr *)&client, sizeof(client)) < 0)
    {
        printf("ERROR connecting to server\n");
        return 1;
    }


    json_object *jobj = json_object_new_object();

    json_object *jstring = json_object_new_string(data.c_str());

    json_object_object_add(jobj,KEY.c_str(), jstring);


    if (strcpy(sendBuff, json_object_to_json_string(jobj)) == NULL) {
        printf("ERROR strcpy()");
        exit(-1);
    }

    if (write(fd, sendBuff, strlen(sendBuff)) == -1)
    {
        printf("ERROR write()");
        exit(-1);
    }

    if ((numbytes=recv(fd,recvBuff,MAXDATASIZE,0)) < 0){

        printf("Error en recv() \n");
        exit(-1);
    }

    struct json_object *tempRecibido;
    json_object *parsed_jsonRecibido = json_tokener_parse(recvBuff);
    json_object_object_get_ex(parsed_jsonRecibido, "RECIBIDO", &tempRecibido);
    if (json_object_get_string(tempRecibido) != nullptr){
        cout << json_object_get_string(tempRecibido) << endl;
    }



    ///Se limpian los Buffers
    memset(recvBuff, 0, MAXDATASIZE);
    memset(sendBuff, 0, MAXDATASIZE);

    ::close(fd);

}
