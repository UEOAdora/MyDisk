#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
signals:
    void sig_close();//关闭信号
private slots:
    void on_pb_file_page_clicked();

    void on_pb_trans_page_clicked();

    void on_pb_share_page_clicked();
public slots:
    //设置界面
    void slot_setInfo(QString name);

public:
    //关闭事件
    void closeEvent(QCloseEvent* event);
};
#endif // MAINWINDOW_H

