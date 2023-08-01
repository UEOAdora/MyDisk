#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets/QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    //发送信号

    if (QMessageBox::question(this, "提示", "是否退出") == QMessageBox::Yes)
    {
        Q_EMIT sig_close();
        event->accept();
    }
    else
    {
        event->ignore();
    }

}
