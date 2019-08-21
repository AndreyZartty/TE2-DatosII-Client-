#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <strings.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <json-c/json.h>
#include <json-c/debug.h>
#include <json-c/json_object.h>
#include <QMessageBox>


#define PORT 3550
#define MAXDATASIZE 1000

class Thread;
class QTimer;

using namespace std;



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int sendJSON(string KEY, string data);
    int sendJSONedit(string pos, string data);

private slots:
    void on_SendButton_clicked();

    void on_SendInsertL_clicked();

    void on_SendEditL_clicked();

    void on_SendGetFromL_clicked();

    void on_SendDeleteFirstL_clicked();

    void on_SendInsertABB_clicked();

    void on_SendDeleteABB_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
