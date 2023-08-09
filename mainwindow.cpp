#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets/QMessageBox>
#include <QProgressBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("MyDisk");
    this->setWindowFlags(Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint );
    ////在表格里插入测试数据
    //QTableWidgetItem* item1 = new QTableWidgetItem("1.txt");
    //item1->setIcon(QIcon(":/resources/images/file.png"));
    //item1->setCheckState(Qt::Unchecked);
    //QTableWidgetItem* item2 = new QTableWidgetItem("2023-08-08 13:37:29");
    //QString size = FileInfo::getSize(19242300000);
    //QTableWidgetItem* item3 = new QTableWidgetItem(size);
    //int row = ui->table_file->rowCount();
    //ui->table_file->setRowCount(row + 1);
    //ui->table_file->setItem(row, 0, item1);
    //ui->table_file->setItem(row, 1, item2);
    //ui->table_file->setItem(row, 2, item3);
    //添加右键菜单
    ui->table_file->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->table_file, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slot_menuShow(QPoint)));
    //添加右键菜单 新建文件夹
    m_menu.addAction(QIcon(":/resources/images/folder.png"), "新建文件夹");
    //下载 删除 收藏 分享
    m_menu.addAction("下载");
    m_menu.addAction("删除");
    m_menu.addAction("收藏");
    m_menu.addAction("分享");
    connect(&m_menu, SIGNAL(triggered(QAction*)), this, SLOT(slot_dealMenu(QAction*)));

    m_menuAddFile.addAction("上传文件");
    m_menuAddFile.addAction("上传文件夹");
    connect(&m_menuAddFile, SIGNAL(triggered(QAction*)), this, SLOT(slot_dealMenuAddFile(QAction*)));
    ui->sw_right->setCurrentIndex(0);
    ui->tw_transmit->setCurrentIndex(1);
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

void MainWindow::slot_insertFileInfo(FileInfo& info)
{
        //在表格里插入测试数据
    QTableWidgetItem* item1 = new QTableWidgetItem(info.name);
    if (info.type == "dir") {
        item1->setIcon(QIcon(":/resources/images/folder.png"));
    }
    else {
        item1->setIcon(QIcon(":/resources/images/file.png"));
    }
    item1->setCheckState(Qt::Unchecked);
    QTableWidgetItem* item2 = new QTableWidgetItem(info.time);
    QTableWidgetItem* item3 = new QTableWidgetItem;
    //如果是文件夹则不显示大小
    if (info.type == "dir") {
        item3->setText("");
    }
    else {
        QString size = FileInfo::getSize(info.size);
        item3->setText(size);
    }
    int row = ui->table_file->rowCount();
    ui->table_file->setRowCount(row + 1);
    ui->table_file->setItem(row, 0, item1);
    ui->table_file->setItem(row, 1, item2);
    ui->table_file->setItem(row, 2, item3);
    //加入行悬停显示信息 显示	int fileid;QString name; QString dir;QString time; int size;QString md5;QString type;
    ui->table_file->item(row, 0)->setToolTip("名称:" + info.name + "\n" + "地址:" + info.dir + "\n" + "时间:" + info.time + "\n" + "大小:" + FileInfo::getSize(info.size) + "\n" + "MD5:" + info.md5 + "\n" + "类型:" + info.type + "\n" + "文件id:"+QString::number(info.fileid));
}

void MainWindow::slot_insertDownloadFile(FileInfo& info)
{
    //新增一行
    int row = ui->table_download->rowCount();
    ui->table_download->setRowCount(row + 1);
    //插入数据
    QTableWidgetItem* item1 = new QTableWidgetItem(info.name);
    QTableWidgetItem* item2 = new QTableWidgetItem;
    QString size = FileInfo::getSize(info.size);
    item2->setText(size);
    QProgressBar* progress = new QProgressBar;
    progress->setRange(0, info.size);
    progress->setValue(0);
    ui->table_download->setItem(row, 0, item1);
    ui->table_download->setItem(row, 1, item2);
    ui->table_download->setCellWidget(row, 2, progress);
    //加入行悬停显示信息 显示	int fileid;QString name; QString dir;QString time; int size;QString md5;QString type;
    ui->table_download->item(row, 0)->setToolTip("名称:" + info.name + "\n" + "地址:" + info.dir + "\n" + "时间:" + info.time + "\n" + "大小:" + FileInfo::getSize(info.size) + "\n" + "MD5:" + info.md5 + "\n" + "类型:" + info.type + "\n" + "文件id:" + QString::number(info.fileid));

}
#include <QDateTime>
void MainWindow::slot_insertUploadFile(FileInfo& info)
{
    //新增一行
    int row = ui->table_upload->rowCount();
    ui->table_upload->setRowCount(row + 1);
    //插入数据
    QTableWidgetItem* item1 = new QTableWidgetItem(info.name);
    QTableWidgetItem* item2 = new QTableWidgetItem;
    QString size = FileInfo::getSize(info.size);
    item2->setText(size);
    QProgressBar* progress = new QProgressBar;
    progress->setRange(0, info.size);
    progress->setValue(0);
    ui->table_upload->setItem(row, 0, item1);
    ui->table_upload->setItem(row, 1, item2);
    ui->table_upload->setCellWidget(row, 2, progress);
    //加入行悬停显示信息 显示	int fileid;QString name; QString dir;QString time; int size;QString md5;QString type;
    ui->table_upload->item(row, 0)->setToolTip("名称:" + info.name + "\n" + "地址:" + info.dir + "\n" + "时间:" + info.time + "\n" + "大小:" + FileInfo::getSize(info.size) + "\n" + "MD5:" + info.md5 + "\n" + "类型:" + info.type + "\n" + "文件id:" + QString::number(info.fileid));

}

void MainWindow::slot_insertComplete(FileInfo& info)
{
    //新增一行
    int row = ui->table_complete->rowCount();
    ui->table_complete->setRowCount(row + 1);
    //插入数据
    QTableWidgetItem* item1 = new QTableWidgetItem(info.name);
    QTableWidgetItem* item2 = new QTableWidgetItem;
    QString size = FileInfo::getSize(info.size);
    item2->setText(size);
    QTableWidgetItem* item3 = new QTableWidgetItem;
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    item3->setText(time);
    QPushButton* btn = new QPushButton;
    btn->setFlat(true);
    btn->setIcon(QIcon(":/resources/images/folder.png"));
    btn->setToolTip(info.absolutePath);
    connect(btn, SIGNAL(clicked()), this, SLOT(slot_folderButtonClick()));
    ui->table_complete->setItem(row, 0, item1);
    ui->table_complete->setItem(row, 1, item2);
    ui->table_complete->setItem(row, 2, item3);
    ui->table_complete->setCellWidget(row, 3, btn);
    //加入行悬停显示信息 显示	int fileid;QString name; QString dir;QString time; int size;QString md5;QString type;
    ui->table_complete->item(row, 0)->setToolTip("名称:" + info.name + "\n" + "地址:" + info.dir + "\n" + "时间:" + info.time + "\n" + "大小:" + FileInfo::getSize(info.size) + "\n" + "MD5:" + info.md5 + "\n" + "类型:" + info.type + "\n" + "文件id:" + QString::number(info.fileid));

}

void MainWindow::slot_insertUploadComplete(FileInfo& info)
{
    //新增一行
    int row = ui->table_complete->rowCount();
    ui->table_complete->setRowCount(row + 1);
    //插入数据
    QTableWidgetItem* item1 = new QTableWidgetItem(info.name);
    QTableWidgetItem* item2 = new QTableWidgetItem;
    QString size = FileInfo::getSize(info.size);
    item2->setText(size);
    QTableWidgetItem* item3 = new QTableWidgetItem;
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    item3->setText(time);
    QPushButton* btn = new QPushButton;
    btn->setFlat(true);
    btn->setText("上传完成");
   
    ui->table_complete->setItem(row, 0, item1);
    ui->table_complete->setItem(row, 1, item2);
    ui->table_complete->setItem(row, 2, item3);
    ui->table_complete->setCellWidget(row, 3, btn);
    //加入行悬停显示信息 显示	int fileid;QString name; QString dir;QString time; int size;QString md5;QString type;
    ui->table_complete->item(row, 0)->setToolTip("名称:" + info.name + "\n" + "地址:" + info.dir + "\n" + "时间:" + info.time + "\n" + "大小:" + FileInfo::getSize(info.size) + "\n" + "MD5:" + info.md5 + "\n" + "类型:" + info.type + "\n" + "文件id:" + QString::number(info.fileid));

}

void MainWindow::slot_updateFileProgress(int fileid, int pos)
{
    //遍历表单 取ToolTip中的fileid 对比 判断是否相等 然后更新第二列的进度条
    int rows = ui->table_download->rowCount();
    for (int i = 0; i < rows; i++) {
//        QTableWidgetItem* item = ui->table_download->item(i, 0);
//		QString str = item->toolTip();
//		QStringList list = str.split("\n");
//		QString id = list.at(6);
//		id = id.mid(4);
        QTableWidgetItem* item = ui->table_download->item(i, 0);
        QStringList list = item->toolTip().split("\n");
        QString id = list.at(list.size() - 1).split(":").at(1);
        int iid = id.toInt();
        qDebug()<<iid<<" "<<fileid;
        if (iid == fileid) {
			QProgressBar* progress = (QProgressBar*)ui->table_download->cellWidget(i, 2);
			progress->setValue(pos);
            if (progress->value() >= progress->maximum())
            {
                ////插入已完成的信息 获取之前的info
                //FileInfo info = m_mapFileidToFileInfo.value(iid);
                //this->slot_insertComplete();
                ////删除该条
                ui->table_download->removeRow(i);
			}
			break;
		}
	}
}

void MainWindow::slot_updateUploadFileProgress(int fileid, int pos)
{
    //遍历表单 取ToolTip中的fileid 对比 判断是否相等 然后更新第二列的进度条
    int rows = ui->table_upload->rowCount();
    for (int i = 0; i < rows; ++i) {
        //        QTableWidgetItem* item = ui->table_download->item(i, 0);
        //		QString str = item->toolTip();
        //		QStringList list = str.split("\n");
        //		QString id = list.at(6);
        //		id = id.mid(4);
        QTableWidgetItem* item = ui->table_upload->item(i, 0);
        QStringList list = item->toolTip().split("\n");
        QString id = list.at(list.size() - 1).split(":").at(1);
        int iid = id.toInt();
        qDebug() << iid << " " << fileid;
        if (iid == fileid) {
            QProgressBar* progress = (QProgressBar*)ui->table_upload->cellWidget(i, 2);
            progress->setValue(pos);
            if (progress->value() >= progress->maximum())
            {
                ////插入已完成的信息 获取之前的info
                //FileInfo info = m_mapFileidToFileInfo.value(iid);
                //this->slot_insertComplete();
                ////删除该条
                //到99 删除
                
                ui->table_upload->removeRow(i);
            }
            if (progress->value() == 99)
            {
				ui->table_upload->removeRow(i);
			}
            break;
        }
    }
}

void MainWindow::slot_menuShow(QPoint point)
{
    //在鼠标选中的位置显示右键菜单
    m_menu.exec(QCursor::pos());
}
#include <QInputDialog>
void MainWindow::slot_dealMenu(QAction* action)
{
    //输出右键菜单属于的行的文件名
    QTableWidgetItem* item = ui->table_file->item(ui->table_file->currentRow(), 0);
    qDebug() << item->text();
    if (action->text() == "新建文件夹") {
        qDebug() << "新建文件夹";
        //弹出一个对话框
        QString name = QInputDialog::getText(this, "新建文件夹", "请输入文件夹名称");
        //去重
        int rows = ui->table_file->rowCount();
        for (int i = 0; i < rows; ++i) {
			QTableWidgetItem* item = ui->table_file->item(i, 0);
            if (item->text() == name)
            {
                QMessageBox::warning(this, "警告", "文件夹名称不能重复");
            }
        }
        //过滤 / \\ ? * : " < > | 等特殊字符
        if (name.isEmpty())
        {
			name = "新建文件夹";
		}
        QString tmp = name;
        if (tmp.remove(" ").isEmpty())
        {
			QMessageBox::warning(this, "警告", "文件夹名称不能全是空格");
			return;
		}
        if (name.contains("/") || name.contains("\\") || name.contains("?") || name.contains("*") || name.contains(":") || name.contains("\"") || name.contains("<") || name.contains(">") || name.contains("|"))
        {
            QMessageBox::warning(this, "警告", "文件夹名称不能包含/ \\ ? * : \" < > | 等特殊字符");
            return;
        }
        //发送信号
        Q_EMIT SIG_addFolder(name);
    }
    else if (action->text() == "下载") {
        qDebug() << "下载";
        //遍历表单 看哪一行被选中select 获取控件
        int rows = ui->table_file->rowCount();
        for (int i = 0; i < rows; i++) {
            QTableWidgetItem* item = ui->table_file->item(i, 0);
            if (item->checkState() == Qt::Checked) {
                //看对应的文件的id
                //获取该行tooltip中最后一行的文件id
                QStringList list = item->toolTip().split("\n");
                QString fileid = list.at(list.size() - 1).split(":").at(1);
                qDebug() <<" test "<< fileid;
                //转换为int
                int id = fileid.toInt();
                //查看是否在当前下载列表中 todo
                //不在
                //发一个下载的信号
                Q_EMIT SIG_downloadFile(id);
            }

        }

    }
    else if (action->text() == "删除") {
        qDebug() << "删除";
    }
    else if (action->text() == "收藏") {
        qDebug() << "收藏";
    }
    else if (action->text() == "分享") {
        qDebug() << "分享";
    }
}
#include <QProcess>
void MainWindow::slot_folderButtonClick()
{
    QPushButton* btn = (QPushButton*)sender();
    QString path = btn->toolTip().replace('/', '\\');
    QProcess::startDetached("explorer",QStringList()<< QString("/select,")<< path);
}

void MainWindow::on_pb_addFile_clicked()
{
    //弹出菜单
	m_menuAddFile.exec(QCursor::pos());
}
#include <QFileDialog>
void MainWindow::slot_dealMenuAddFile(QAction* action)
{
    if (action->text() == "上传文件") {
        qDebug() << "上传文件";
        //弹窗 选择文件
        QString path = QFileDialog::getOpenFileName(this, "选择文件", "C:\\Users\\Administrator\\Desktop");
        if (path.isEmpty())
        {
            return;
        }
        //判断是否正在上传
        //上传文件的信息 在核心类打包 存储文件信息 所以要用信号传递
        Q_EMIT SIG_uploadFile(path);
    }
    else if (action->text() == "上传文件夹") {
        qDebug() << "上传文件夹";
    }
}

void MainWindow::slot_deleteAllFileInfo()
{
    //逐行删除
    int rows = ui->table_file->rowCount();
    for (int i = rows - 1; i >= 0; --i) {
		ui->table_file->removeRow(i);
	}
}
