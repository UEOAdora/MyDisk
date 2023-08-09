/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QLabel *lb_icon;
    QTabWidget *tw_login_register;
    QWidget *tab_login;
    QLabel *lb_zh;
    QLineEdit *le_zh;
    QLabel *lb_passwd;
    QLineEdit *le_passwd;
    QPushButton *pb_clear;
    QPushButton *pb_commit;
    QWidget *tab_register;
    QPushButton *pb_clear__reg;
    QLabel *lb_zh_reg;
    QLineEdit *le_passwd_reg;
    QLineEdit *le_zh_reg;
    QPushButton *pb_commit__reg;
    QLabel *lb_passwd_reg;
    QLineEdit *le_confirm_reg;
    QLabel *lb_confirm_reg;
    QLineEdit *le_name_reg;
    QLabel *lb_name__reg;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName(QString::fromUtf8("LoginDialog"));
        LoginDialog->resize(613, 328);
        LoginDialog->setMinimumSize(QSize(613, 328));
        LoginDialog->setMaximumSize(QSize(613, 328));
        QFont font;
        font.setPointSize(12);
        LoginDialog->setFont(font);
        LoginDialog->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lb_icon = new QLabel(LoginDialog);
        lb_icon->setObjectName(QString::fromUtf8("lb_icon"));
        lb_icon->setGeometry(QRect(0, 20, 261, 281));
        lb_icon->setPixmap(QPixmap(QString::fromUtf8(":/resources/tb/tb.jpg")));
        lb_icon->setScaledContents(true);
        tw_login_register = new QTabWidget(LoginDialog);
        tw_login_register->setObjectName(QString::fromUtf8("tw_login_register"));
        tw_login_register->setGeometry(QRect(260, 20, 361, 281));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        tw_login_register->setFont(font1);
        tab_login = new QWidget();
        tab_login->setObjectName(QString::fromUtf8("tab_login"));
        lb_zh = new QLabel(tab_login);
        lb_zh->setObjectName(QString::fromUtf8("lb_zh"));
        lb_zh->setGeometry(QRect(40, 60, 31, 16));
        le_zh = new QLineEdit(tab_login);
        le_zh->setObjectName(QString::fromUtf8("le_zh"));
        le_zh->setGeometry(QRect(90, 50, 191, 31));
        le_zh->setClearButtonEnabled(true);
        lb_passwd = new QLabel(tab_login);
        lb_passwd->setObjectName(QString::fromUtf8("lb_passwd"));
        lb_passwd->setGeometry(QRect(40, 130, 31, 16));
        le_passwd = new QLineEdit(tab_login);
        le_passwd->setObjectName(QString::fromUtf8("le_passwd"));
        le_passwd->setGeometry(QRect(90, 120, 191, 31));
        le_passwd->setEchoMode(QLineEdit::Password);
        le_passwd->setClearButtonEnabled(true);
        pb_clear = new QPushButton(tab_login);
        pb_clear->setObjectName(QString::fromUtf8("pb_clear"));
        pb_clear->setGeometry(QRect(50, 210, 93, 28));
        pb_commit = new QPushButton(tab_login);
        pb_commit->setObjectName(QString::fromUtf8("pb_commit"));
        pb_commit->setGeometry(QRect(190, 210, 93, 28));
        tw_login_register->addTab(tab_login, QString());
        tab_register = new QWidget();
        tab_register->setObjectName(QString::fromUtf8("tab_register"));
        pb_clear__reg = new QPushButton(tab_register);
        pb_clear__reg->setObjectName(QString::fromUtf8("pb_clear__reg"));
        pb_clear__reg->setGeometry(QRect(50, 210, 93, 28));
        lb_zh_reg = new QLabel(tab_register);
        lb_zh_reg->setObjectName(QString::fromUtf8("lb_zh_reg"));
        lb_zh_reg->setGeometry(QRect(40, 50, 31, 16));
        le_passwd_reg = new QLineEdit(tab_register);
        le_passwd_reg->setObjectName(QString::fromUtf8("le_passwd_reg"));
        le_passwd_reg->setGeometry(QRect(90, 80, 191, 31));
        le_passwd_reg->setEchoMode(QLineEdit::Password);
        le_passwd_reg->setClearButtonEnabled(true);
        le_zh_reg = new QLineEdit(tab_register);
        le_zh_reg->setObjectName(QString::fromUtf8("le_zh_reg"));
        le_zh_reg->setGeometry(QRect(90, 40, 191, 31));
        le_zh_reg->setClearButtonEnabled(true);
        pb_commit__reg = new QPushButton(tab_register);
        pb_commit__reg->setObjectName(QString::fromUtf8("pb_commit__reg"));
        pb_commit__reg->setGeometry(QRect(190, 210, 93, 28));
        lb_passwd_reg = new QLabel(tab_register);
        lb_passwd_reg->setObjectName(QString::fromUtf8("lb_passwd_reg"));
        lb_passwd_reg->setGeometry(QRect(40, 90, 31, 16));
        le_confirm_reg = new QLineEdit(tab_register);
        le_confirm_reg->setObjectName(QString::fromUtf8("le_confirm_reg"));
        le_confirm_reg->setGeometry(QRect(90, 120, 191, 31));
        le_confirm_reg->setEchoMode(QLineEdit::Password);
        le_confirm_reg->setClearButtonEnabled(true);
        lb_confirm_reg = new QLabel(tab_register);
        lb_confirm_reg->setObjectName(QString::fromUtf8("lb_confirm_reg"));
        lb_confirm_reg->setGeometry(QRect(40, 130, 31, 16));
        le_name_reg = new QLineEdit(tab_register);
        le_name_reg->setObjectName(QString::fromUtf8("le_name_reg"));
        le_name_reg->setGeometry(QRect(90, 160, 191, 31));
        le_name_reg->setClearButtonEnabled(true);
        lb_name__reg = new QLabel(tab_register);
        lb_name__reg->setObjectName(QString::fromUtf8("lb_name__reg"));
        lb_name__reg->setGeometry(QRect(40, 170, 31, 16));
        tw_login_register->addTab(tab_register, QString());
        QWidget::setTabOrder(le_zh_reg, le_passwd_reg);
        QWidget::setTabOrder(le_passwd_reg, le_confirm_reg);
        QWidget::setTabOrder(le_confirm_reg, le_name_reg);
        QWidget::setTabOrder(le_name_reg, pb_clear__reg);
        QWidget::setTabOrder(pb_clear__reg, pb_commit__reg);
        QWidget::setTabOrder(pb_commit__reg, tw_login_register);
        QWidget::setTabOrder(tw_login_register, le_zh);
        QWidget::setTabOrder(le_zh, le_passwd);
        QWidget::setTabOrder(le_passwd, pb_commit);
        QWidget::setTabOrder(pb_commit, pb_clear);

        retranslateUi(LoginDialog);

        tw_login_register->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QApplication::translate("LoginDialog", "Dialog", nullptr));
        lb_icon->setText(QString());
        lb_zh->setText(QApplication::translate("LoginDialog", "\350\264\246\345\217\267", nullptr));
        le_zh->setText(QApplication::translate("LoginDialog", "13351075356", nullptr));
        lb_passwd->setText(QApplication::translate("LoginDialog", "\345\257\206\347\240\201", nullptr));
        le_passwd->setText(QApplication::translate("LoginDialog", "1234", nullptr));
        pb_clear->setText(QApplication::translate("LoginDialog", "\346\270\205\347\251\272", nullptr));
        pb_commit->setText(QApplication::translate("LoginDialog", "\346\217\220\344\272\244", nullptr));
        tw_login_register->setTabText(tw_login_register->indexOf(tab_login), QApplication::translate("LoginDialog", "\347\231\273\345\275\225", nullptr));
        pb_clear__reg->setText(QApplication::translate("LoginDialog", "\346\270\205\347\251\272", nullptr));
        lb_zh_reg->setText(QApplication::translate("LoginDialog", "\350\264\246\345\217\267", nullptr));
#ifndef QT_NO_TOOLTIP
        le_passwd_reg->setToolTip(QApplication::translate("LoginDialog", "<html><head/><body><p>\344\270\215\345\244\232\344\272\21620\344\275\215\345\257\206\347\240\201</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        le_zh_reg->setToolTip(QApplication::translate("LoginDialog", "<html><head/><body><p>\350\276\223\345\205\24511\344\275\215\346\211\213\346\234\272\345\217\267</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        le_zh_reg->setText(QString());
        pb_commit__reg->setText(QApplication::translate("LoginDialog", "\346\217\220\344\272\244", nullptr));
        lb_passwd_reg->setText(QApplication::translate("LoginDialog", "\345\257\206\347\240\201", nullptr));
        le_confirm_reg->setText(QString());
        lb_confirm_reg->setText(QApplication::translate("LoginDialog", "\347\241\256\350\256\244", nullptr));
#ifndef QT_NO_TOOLTIP
        le_name_reg->setToolTip(QApplication::translate("LoginDialog", "<html><head/><body><p>\344\270\215\350\266\205\350\277\20710\344\275\215</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        le_name_reg->setText(QString());
        lb_name__reg->setText(QApplication::translate("LoginDialog", "\346\230\265\347\247\260", nullptr));
        tw_login_register->setTabText(tw_login_register->indexOf(tab_register), QApplication::translate("LoginDialog", "\346\263\250\345\206\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
