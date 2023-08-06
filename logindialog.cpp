#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include <QRegExp>
LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("注册登录");
    this->setWindowFlags(Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint );
    //注册分页
    ui->tw_login_register->setCurrentIndex(1);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

//注册提交
void LoginDialog::on_pb_commit__reg_clicked()
{
    //从控件获取文本
    QString zh = ui->le_zh_reg->text();
    QString passwd = ui->le_passwd_reg->text();
    QString confirm = ui->le_confirm_reg->text();
    QString name = ui->le_name_reg->text();
    //验证
    if (zh.isEmpty() || passwd.isEmpty() || confirm.isEmpty() || name.isEmpty())
    {
		QMessageBox::warning(this, "警告", "请填写完整");
		return;
	}
    //账号
    //qt正则 只有数字QString 11位
    QRegExp regExp(QString("^1[356789][0-9]\{9\}$"));
    bool ret = regExp.exactMatch(zh);
    if (!ret)
    {
		QMessageBox::warning(this, "警告", "账号格式不正确");
		return;
	}
    //密码
    // 长度小于20位
    if (passwd.length() > 20)
    {
        QMessageBox::warning(this, "警告", "密码长度不能超过20位");
        return;
    }
    //密码和确认密码一致
    if (passwd != confirm)
    {
		QMessageBox::warning(this, "警告", "密码和确认密码不一致");
		return;
	}
    //验证昵称 长度10位
    if (name.length() > 10)
    {
        QMessageBox::warning(this, "警告", "昵称长度不能超过10位");
        return;
    }
    //发送信号
    Q_EMIT SIG_registerCommit(zh, passwd, name);
}


void LoginDialog::on_pb_commit_clicked()
{
    //从控件获取文本
	QString zh = ui->le_zh->text();
	QString passwd = ui->le_passwd->text();
	//验证
    if (zh.isEmpty() || passwd.isEmpty())
    {
		QMessageBox::warning(this, "警告", "请填写完整");
		return;
	}
	//账号
	//qt正则 只有数字QString 11位
	QRegExp regExp(QString("^1[356789][0-9]\{9\}$"));
	bool ret = regExp.exactMatch(zh);
    if (!ret)
    {
		QMessageBox::warning(this, "警告", "账号格式不正确");
		return;
	}
	//密码
	// 长度小于20位
    if (passwd.length() > 20)
    {
		QMessageBox::warning(this, "警告", "密码长度不能超过20位");
		return;
	}
	//发送信号
	Q_EMIT SIG_loginCommit(zh, passwd);
}

void LoginDialog::closeEvent(QCloseEvent* event)
{
    if (QMessageBox::question(this, "提示", "是否退出") == QMessageBox::Yes)
    {
        event->accept();
        Q_EMIT SIG_close();
        
    }
    else
    {
        event->ignore();
    }
}


void LoginDialog::on_pb_clear__reg_clicked()
{
    ui->le_zh_reg->clear();
    ui->le_passwd_reg->clear();
    ui->le_confirm_reg->clear();
    ui->le_name_reg->clear();
}


void LoginDialog::on_pb_clear_clicked()
{
    ui->le_zh->clear();
    ui->le_passwd->clear();
}

