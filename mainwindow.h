#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include "common.h"
#include <QMenu>
#include <QDebug>
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
    QMenu m_menu;//菜单
    QMenu m_menuAddFile;//添加文件菜单
signals:
    void sig_close();//关闭信号
    void SIG_downloadFile(int fileid);//下载文件信号
    void SIG_uploadFile(QString path);//上传文件信号
    void SIG_uploadFolder(QString path);//上传文件夹信号
    void SIG_addFolder(QString name); //添加文件夹信号
public slots:
    void on_pb_file_page_clicked();

    void on_pb_trans_page_clicked();

    void on_pb_share_page_clicked();
    //设置界面
    void slot_setInfo(QString name);

    //插入文件信息
    void slot_insertFileInfo(FileInfo & info);

    void slot_insertDownloadFile(FileInfo& info);

    void slot_insertUploadFile(FileInfo& info);

    void slot_insertComplete(FileInfo& info);

    void slot_insertUploadComplete(FileInfo& info);

    void slot_updateFileProgress(int fileid, int pos);

    void slot_updateUploadFileProgress(int fileid, int pos);

    void slot_menuShow(QPoint point);

    void slot_dealMenu(QAction* action);

    void slot_folderButtonClick();

    void slot_dealMenuAddFile(QAction* action);

    void slot_deleteAllFileInfo();

public:
    //关闭事件
    void closeEvent(QCloseEvent* event);
private slots:
    void on_pb_addFile_clicked();
};
#endif // MAINWINDOW_H

