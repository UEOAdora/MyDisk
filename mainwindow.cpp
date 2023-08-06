#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets/QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("MyDisk");
    this->setWindowFlags(Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint );
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

void MainWindow::on_pb_file_page_clicked()
{
    ui->sw_right->setCurrentIndex(0);
}


void MainWindow::on_pb_trans_page_clicked()
{
    ui->sw_right->setCurrentIndex(1);
}


void MainWindow::on_pb_share_page_clicked()
{
    ui->sw_right->setCurrentIndex(2);
}

void MainWindow::slot_setInfo(QString name)
{
    ui->pb_user->setText(name);
}

