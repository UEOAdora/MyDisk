#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QCloseEvent>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();
signals:
    void SIG_registerCommit(QString, QString, QString);
    void SIG_loginCommit(QString, QString);
    void SIG_close();
private slots:
    void on_pb_commit__reg_clicked();

    void on_pb_clear__reg_clicked();

    void on_pb_clear_clicked();

    void on_pb_commit_clicked();

private:
    Ui::LoginDialog *ui;
    //关闭事件
    void closeEvent(QCloseEvent *event);
};

#endif // LOGINDIALOG_H
