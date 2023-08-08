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
    QProgressBar* progress = new QProgressBar;
    progress->setRange(0, info.size);
    progress->setValue(0);
    ui->table_download->setItem(row, 0, item1);
    ui->table_download->setItem(row, 1, item2);
    ui->table_download->setCellWidget(row, 2, progress);
    //加入行悬停显示信息 显示	int fileid;QString name; QString dir;QString time; int size;QString md5;QString type;
    ui->table_download->item(row, 0)->setToolTip("名称:" + info.name + "\n" + "地址:" + info.dir + "\n" + "时间:" + info.time + "\n" + "大小:" + FileInfo::getSize(info.size) + "\n" + "MD5:" + info.md5 + "\n" + "类型:" + info.type + "\n" + "文件id:" + QString::number(info.fileid));

}

void MainWindow::slot_updateFileProgress(int fileid, int pos)
{
    //遍历表单 取ToolTip中的fileid 对比 判断是否相等 然后更新第二列的进度条
    int rows = ui->table_download->rowCount();
    for (int i = 0; i < rows; i++) {
        QTableWidgetItem* item = ui->table_download->item(i, 0);
		QString str = item->toolTip();
		QStringList list = str.split("\n");
		QString id = list.at(6);
		id = id.mid(4);
        if (id.toInt() == fileid) {
			QProgressBar* progress = (QProgressBar*)ui->table_download->cellWidget(i, 2);
			progress->setValue(pos);
			break;
		}
	}
}

void MainWindow::slot_menuShow(QPoint point)
{
    //在鼠标选中的位置显示右键菜单
    m_menu.exec(QCursor::pos());
}

void MainWindow::slot_dealMenu(QAction* action)
{
    //输出右键菜单属于的行的文件名
    QTableWidgetItem* item = ui->table_file->item(ui->table_file->currentRow(), 0);
    qDebug() << item->text();
    if (action->text() == "新建文件夹") {
        qDebug() << "新建文件夹";
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

