/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QWidget *wdg_content;
    QHBoxLayout *horizontalLayout_2;
    QWidget *wdg_left;
    QVBoxLayout *verticalLayout;
    QPushButton *pb_user;
    QSpacerItem *verticalSpacer;
    QPushButton *pb_file_page;
    QPushButton *pb_trans_page;
    QPushButton *pb_share_page;
    QWidget *wdg_right;
    QHBoxLayout *horizontalLayout_3;
    QStackedWidget *sw_right;
    QWidget *page_file;
    QVBoxLayout *verticalLayout_2;
    QWidget *wdg_fileTools;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pb_path_3;
    QPushButton *pb_path_2;
    QPushButton *pb_path;
    QSpacerItem *horizontalSpacer;
    QPushButton *pb_search;
    QPushButton *pb_addFile;
    QPushButton *pb_delete;
    QPushButton *pb_share;
    QTableWidget *table_file;
    QWidget *page_transmit;
    QHBoxLayout *horizontalLayout_5;
    QTabWidget *tabWidget;
    QWidget *tab_upload;
    QHBoxLayout *horizontalLayout_7;
    QTableWidget *table_upload;
    QWidget *tab_download;
    QHBoxLayout *horizontalLayout_8;
    QTableWidget *table_download;
    QWidget *tab_complete;
    QHBoxLayout *horizontalLayout_9;
    QTableWidget *table_complete;
    QWidget *page_share;
    QHBoxLayout *horizontalLayout_6;
    QTabWidget *tw_share;
    QWidget *tab_share;
    QHBoxLayout *horizontalLayout_10;
    QTableWidget *table_share;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1280, 720);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        MainWindow->setFont(font);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        wdg_content = new QWidget(centralwidget);
        wdg_content->setObjectName(QString::fromUtf8("wdg_content"));
        horizontalLayout_2 = new QHBoxLayout(wdg_content);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        wdg_left = new QWidget(wdg_content);
        wdg_left->setObjectName(QString::fromUtf8("wdg_left"));
        wdg_left->setMinimumSize(QSize(360, 0));
        wdg_left->setMaximumSize(QSize(360, 16777215));
        wdg_left->setStyleSheet(QString::fromUtf8("background-color: rgb(238, 238, 238);"));
        verticalLayout = new QVBoxLayout(wdg_left);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pb_user = new QPushButton(wdg_left);
        pb_user->setObjectName(QString::fromUtf8("pb_user"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/resources/face/btn_avatar_a75.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_user->setIcon(icon);
        pb_user->setIconSize(QSize(35, 35));
        pb_user->setFlat(false);

        verticalLayout->addWidget(pb_user);

        verticalSpacer = new QSpacerItem(20, 473, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        pb_file_page = new QPushButton(wdg_left);
        pb_file_page->setObjectName(QString::fromUtf8("pb_file_page"));
        pb_file_page->setMinimumSize(QSize(0, 44));
        pb_file_page->setMaximumSize(QSize(16777215, 44));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/resources/images/file.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_file_page->setIcon(icon1);
        pb_file_page->setFlat(false);

        verticalLayout->addWidget(pb_file_page);

        pb_trans_page = new QPushButton(wdg_left);
        pb_trans_page->setObjectName(QString::fromUtf8("pb_trans_page"));
        pb_trans_page->setMinimumSize(QSize(0, 44));
        pb_trans_page->setMaximumSize(QSize(16777215, 44));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/resources/images/transmit.ico"), QSize(), QIcon::Normal, QIcon::Off);
        pb_trans_page->setIcon(icon2);
        pb_trans_page->setFlat(false);

        verticalLayout->addWidget(pb_trans_page);

        pb_share_page = new QPushButton(wdg_left);
        pb_share_page->setObjectName(QString::fromUtf8("pb_share_page"));
        pb_share_page->setMinimumSize(QSize(0, 44));
        pb_share_page->setMaximumSize(QSize(16777215, 44));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/resources/images/share.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_share_page->setIcon(icon3);
        pb_share_page->setFlat(false);

        verticalLayout->addWidget(pb_share_page);


        horizontalLayout_2->addWidget(wdg_left);

        wdg_right = new QWidget(wdg_content);
        wdg_right->setObjectName(QString::fromUtf8("wdg_right"));
        horizontalLayout_3 = new QHBoxLayout(wdg_right);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        sw_right = new QStackedWidget(wdg_right);
        sw_right->setObjectName(QString::fromUtf8("sw_right"));
        page_file = new QWidget();
        page_file->setObjectName(QString::fromUtf8("page_file"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(10);
        page_file->setFont(font1);
        verticalLayout_2 = new QVBoxLayout(page_file);
        verticalLayout_2->setSpacing(7);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        wdg_fileTools = new QWidget(page_file);
        wdg_fileTools->setObjectName(QString::fromUtf8("wdg_fileTools"));
        horizontalLayout_4 = new QHBoxLayout(wdg_fileTools);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        pb_path_3 = new QPushButton(wdg_fileTools);
        pb_path_3->setObjectName(QString::fromUtf8("pb_path_3"));
        pb_path_3->setMinimumSize(QSize(40, 0));
        pb_path_3->setMaximumSize(QSize(40, 16777215));
        pb_path_3->setFlat(true);

        horizontalLayout_4->addWidget(pb_path_3);

        pb_path_2 = new QPushButton(wdg_fileTools);
        pb_path_2->setObjectName(QString::fromUtf8("pb_path_2"));
        pb_path_2->setMinimumSize(QSize(40, 0));
        pb_path_2->setMaximumSize(QSize(40, 16777215));
        pb_path_2->setFlat(true);

        horizontalLayout_4->addWidget(pb_path_2);

        pb_path = new QPushButton(wdg_fileTools);
        pb_path->setObjectName(QString::fromUtf8("pb_path"));
        pb_path->setFlat(true);

        horizontalLayout_4->addWidget(pb_path);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        pb_search = new QPushButton(wdg_fileTools);
        pb_search->setObjectName(QString::fromUtf8("pb_search"));
        pb_search->setMinimumSize(QSize(50, 40));
        pb_search->setMaximumSize(QSize(50, 40));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/resources/images/search.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_search->setIcon(icon4);
        pb_search->setIconSize(QSize(40, 40));
        pb_search->setFlat(true);

        horizontalLayout_4->addWidget(pb_search);

        pb_addFile = new QPushButton(wdg_fileTools);
        pb_addFile->setObjectName(QString::fromUtf8("pb_addFile"));
        pb_addFile->setMinimumSize(QSize(50, 40));
        pb_addFile->setMaximumSize(QSize(50, 40));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/resources/images/addFile.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_addFile->setIcon(icon5);
        pb_addFile->setIconSize(QSize(40, 40));
        pb_addFile->setFlat(true);

        horizontalLayout_4->addWidget(pb_addFile);

        pb_delete = new QPushButton(wdg_fileTools);
        pb_delete->setObjectName(QString::fromUtf8("pb_delete"));
        pb_delete->setMinimumSize(QSize(50, 40));
        pb_delete->setMaximumSize(QSize(50, 40));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/resources/images/Cancel_32x32.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_delete->setIcon(icon6);
        pb_delete->setIconSize(QSize(40, 40));
        pb_delete->setFlat(true);

        horizontalLayout_4->addWidget(pb_delete);

        pb_share = new QPushButton(wdg_fileTools);
        pb_share->setObjectName(QString::fromUtf8("pb_share"));
        pb_share->setMinimumSize(QSize(50, 40));
        pb_share->setMaximumSize(QSize(50, 40));
        pb_share->setIcon(icon3);
        pb_share->setIconSize(QSize(40, 40));
        pb_share->setFlat(true);

        horizontalLayout_4->addWidget(pb_share);


        verticalLayout_2->addWidget(wdg_fileTools);

        table_file = new QTableWidget(page_file);
        if (table_file->columnCount() < 3)
            table_file->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        table_file->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        table_file->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        table_file->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        table_file->setObjectName(QString::fromUtf8("table_file"));
        table_file->setEditTriggers(QAbstractItemView::NoEditTriggers);
        table_file->setSelectionBehavior(QAbstractItemView::SelectRows);
        table_file->horizontalHeader()->setDefaultSectionSize(300);
        table_file->horizontalHeader()->setStretchLastSection(true);
        table_file->verticalHeader()->setVisible(false);

        verticalLayout_2->addWidget(table_file);

        sw_right->addWidget(page_file);
        page_transmit = new QWidget();
        page_transmit->setObjectName(QString::fromUtf8("page_transmit"));
        horizontalLayout_5 = new QHBoxLayout(page_transmit);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(page_transmit);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab_upload = new QWidget();
        tab_upload->setObjectName(QString::fromUtf8("tab_upload"));
        horizontalLayout_7 = new QHBoxLayout(tab_upload);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        table_upload = new QTableWidget(tab_upload);
        table_upload->setObjectName(QString::fromUtf8("table_upload"));

        horizontalLayout_7->addWidget(table_upload);

        tabWidget->addTab(tab_upload, QString());
        tab_download = new QWidget();
        tab_download->setObjectName(QString::fromUtf8("tab_download"));
        horizontalLayout_8 = new QHBoxLayout(tab_download);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        table_download = new QTableWidget(tab_download);
        if (table_download->columnCount() < 3)
            table_download->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        table_download->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        table_download->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        table_download->setHorizontalHeaderItem(2, __qtablewidgetitem5);
        table_download->setObjectName(QString::fromUtf8("table_download"));
        table_download->setEditTriggers(QAbstractItemView::NoEditTriggers);
        table_download->setSelectionBehavior(QAbstractItemView::SelectRows);
        table_download->horizontalHeader()->setDefaultSectionSize(290);
        table_download->horizontalHeader()->setStretchLastSection(true);
        table_download->verticalHeader()->setVisible(false);

        horizontalLayout_8->addWidget(table_download);

        tabWidget->addTab(tab_download, QString());
        tab_complete = new QWidget();
        tab_complete->setObjectName(QString::fromUtf8("tab_complete"));
        horizontalLayout_9 = new QHBoxLayout(tab_complete);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        table_complete = new QTableWidget(tab_complete);
        table_complete->setObjectName(QString::fromUtf8("table_complete"));

        horizontalLayout_9->addWidget(table_complete);

        tabWidget->addTab(tab_complete, QString());

        horizontalLayout_5->addWidget(tabWidget);

        sw_right->addWidget(page_transmit);
        page_share = new QWidget();
        page_share->setObjectName(QString::fromUtf8("page_share"));
        horizontalLayout_6 = new QHBoxLayout(page_share);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        tw_share = new QTabWidget(page_share);
        tw_share->setObjectName(QString::fromUtf8("tw_share"));
        tab_share = new QWidget();
        tab_share->setObjectName(QString::fromUtf8("tab_share"));
        horizontalLayout_10 = new QHBoxLayout(tab_share);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalLayout_10->setContentsMargins(0, 0, 0, 0);
        table_share = new QTableWidget(tab_share);
        table_share->setObjectName(QString::fromUtf8("table_share"));

        horizontalLayout_10->addWidget(table_share);

        tw_share->addTab(tab_share, QString());

        horizontalLayout_6->addWidget(tw_share);

        sw_right->addWidget(page_share);

        horizontalLayout_3->addWidget(sw_right);


        horizontalLayout_2->addWidget(wdg_right);


        horizontalLayout->addWidget(wdg_content);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);
        tw_share->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        pb_user->setText(QApplication::translate("MainWindow", "\345\220\215\345\255\227", nullptr));
        pb_file_page->setText(QApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
        pb_trans_page->setText(QApplication::translate("MainWindow", "\344\274\240\350\276\223", nullptr));
        pb_share_page->setText(QApplication::translate("MainWindow", "\345\205\261\344\272\253", nullptr));
        pb_path_3->setText(QApplication::translate("MainWindow", "<", nullptr));
        pb_path_2->setText(QApplication::translate("MainWindow", ">", nullptr));
        pb_path->setText(QApplication::translate("MainWindow", "\346\226\207\344\273\266 ", nullptr));
        pb_search->setText(QString());
        pb_addFile->setText(QString());
        pb_delete->setText(QString());
        pb_share->setText(QString());
        QTableWidgetItem *___qtablewidgetitem = table_file->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "\346\226\207\344\273\266\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = table_file->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\345\210\227", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = table_file->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "\345\244\247\345\260\217", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_upload), QApplication::translate("MainWindow", "\344\270\212\344\274\240", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = table_download->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = table_download->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "\345\244\247\345\260\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = table_download->horizontalHeaderItem(2);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "\350\277\233\345\272\246", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_download), QApplication::translate("MainWindow", "\344\270\213\350\275\275", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_complete), QApplication::translate("MainWindow", "\345\267\262\345\256\214\346\210\220", nullptr));
        tw_share->setTabText(tw_share->indexOf(tab_share), QApplication::translate("MainWindow", "\346\210\221\347\232\204\345\205\261\344\272\253", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
