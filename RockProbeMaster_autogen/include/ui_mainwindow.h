/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QAction *actionOpen;
    QAction *actionWatch;
    QAction *action_D;
    QAction *action_Excel;
    QAction *action_create;
    QAction *action_open_workspace;
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QLabel *label_2;
    QLabel *label;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QTableWidget *detailsWidget;
    QLabel *processDetails;
    QProgressBar *progressBar;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_6;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QPushButton *loadButton;
    QPushButton *saveAllButton;
    QPushButton *addButton;
    QPushButton *deleteButton;
    QPushButton *saveButton;
    QPushButton *saveFileButton;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_4;
    QPushButton *updateStatusButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QWidget *page_2;
    QGroupBox *groupBox_4;
    QLineEdit *lineEdit;
    QTableWidget *videoWidget_2;
    QPushButton *startDetectionButton;
    QPushButton *openFileButton;
    QPushButton *startDetectionButton_2;
    QGroupBox *groupBox_5;
    QTextBrowser *resultText;
    QWidget *page_3;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QTableWidget *testWidget;
    QMenuBar *menubar;
    QMenu *menuweishenem1;
    QMenu *menu_2;
    QMenu *menu_3;
    QMenu *menu;
    QToolBar *toolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1027, 673);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName("actionExit");
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName("actionOpen");
        actionWatch = new QAction(MainWindow);
        actionWatch->setObjectName("actionWatch");
        action_D = new QAction(MainWindow);
        action_D->setObjectName("action_D");
        action_Excel = new QAction(MainWindow);
        action_Excel->setObjectName("action_Excel");
        action_create = new QAction(MainWindow);
        action_create->setObjectName("action_create");
        action_open_workspace = new QAction(MainWindow);
        action_open_workspace->setObjectName("action_open_workspace");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(20, 50, 961, 561));
        page = new QWidget();
        page->setObjectName("page");
        label_2 = new QLabel(page);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 470, 60, 18));
        label = new QLabel(page);
        label->setObjectName("label");
        label->setGeometry(QRect(282, 470, 60, 18));
        groupBox = new QGroupBox(page);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(0, 10, 720, 435));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName("verticalLayout_7");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");

        horizontalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout_7->addLayout(horizontalLayout_3);


        verticalLayout->addLayout(verticalLayout_7);

        detailsWidget = new QTableWidget(groupBox);
        if (detailsWidget->columnCount() < 12)
            detailsWidget->setColumnCount(12);
        QFont font;
        font.setBold(true);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font);
        detailsWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        detailsWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font);
        detailsWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setFont(font);
        detailsWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setFont(font);
        detailsWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setFont(font);
        detailsWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setFont(font);
        detailsWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        __qtablewidgetitem7->setFont(font);
        detailsWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        __qtablewidgetitem8->setFont(font);
        detailsWidget->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        __qtablewidgetitem9->setFont(font);
        detailsWidget->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        __qtablewidgetitem10->setFont(font);
        detailsWidget->setHorizontalHeaderItem(10, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        __qtablewidgetitem11->setFont(font);
        detailsWidget->setHorizontalHeaderItem(11, __qtablewidgetitem11);
        detailsWidget->setObjectName("detailsWidget");
        detailsWidget->setMinimumSize(QSize(700, 400));
        detailsWidget->setSortingEnabled(false);

        verticalLayout->addWidget(detailsWidget);

        processDetails = new QLabel(page);
        processDetails->setObjectName("processDetails");
        processDetails->setGeometry(QRect(76, 470, 200, 18));
        processDetails->setMinimumSize(QSize(200, 0));
        progressBar = new QProgressBar(page);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(348, 471, 112, 16));
        progressBar->setMaximumSize(QSize(16777215, 16));
        progressBar->setValue(0);
        layoutWidget = new QWidget(page);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(740, 20, 131, 501));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        groupBox_2 = new QGroupBox(layoutWidget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setMaximumSize(QSize(200, 200));
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        loadButton = new QPushButton(groupBox_2);
        loadButton->setObjectName("loadButton");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        loadButton->setFont(font1);
        loadButton->setStyleSheet(QString::fromUtf8(""));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/resources/images/pg1.ico"), QSize(), QIcon::Normal, QIcon::Off);
        loadButton->setIcon(icon);

        verticalLayout_2->addWidget(loadButton);

        saveAllButton = new QPushButton(groupBox_2);
        saveAllButton->setObjectName("saveAllButton");
        saveAllButton->setFont(font1);
        saveAllButton->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_2->addWidget(saveAllButton);

        addButton = new QPushButton(groupBox_2);
        addButton->setObjectName("addButton");
        addButton->setFont(font1);
        addButton->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_2->addWidget(addButton);

        deleteButton = new QPushButton(groupBox_2);
        deleteButton->setObjectName("deleteButton");
        deleteButton->setFont(font1);
        deleteButton->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_2->addWidget(deleteButton);

        saveButton = new QPushButton(groupBox_2);
        saveButton->setObjectName("saveButton");
        saveButton->setFont(font1);
        saveButton->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_2->addWidget(saveButton);

        saveFileButton = new QPushButton(groupBox_2);
        saveFileButton->setObjectName("saveFileButton");

        verticalLayout_2->addWidget(saveFileButton);


        verticalLayout_3->addLayout(verticalLayout_2);


        verticalLayout_6->addWidget(groupBox_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer);

        groupBox_3 = new QGroupBox(layoutWidget);
        groupBox_3->setObjectName("groupBox_3");
        verticalLayout_5 = new QVBoxLayout(groupBox_3);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        updateStatusButton = new QPushButton(groupBox_3);
        updateStatusButton->setObjectName("updateStatusButton");

        verticalLayout_4->addWidget(updateStatusButton);

        pushButton_2 = new QPushButton(groupBox_3);
        pushButton_2->setObjectName("pushButton_2");

        verticalLayout_4->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(groupBox_3);
        pushButton_3->setObjectName("pushButton_3");

        verticalLayout_4->addWidget(pushButton_3);


        verticalLayout_5->addLayout(verticalLayout_4);


        verticalLayout_6->addWidget(groupBox_3);


        horizontalLayout->addLayout(verticalLayout_6);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        groupBox_4 = new QGroupBox(page_2);
        groupBox_4->setObjectName("groupBox_4");
        groupBox_4->setGeometry(QRect(10, 30, 931, 351));
        lineEdit = new QLineEdit(groupBox_4);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(30, 30, 701, 31));
        videoWidget_2 = new QTableWidget(groupBox_4);
        if (videoWidget_2->columnCount() < 1)
            videoWidget_2->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        videoWidget_2->setHorizontalHeaderItem(0, __qtablewidgetitem12);
        videoWidget_2->setObjectName("videoWidget_2");
        videoWidget_2->setGeometry(QRect(30, 70, 881, 211));
        videoWidget_2->horizontalHeader()->setVisible(true);
        videoWidget_2->horizontalHeader()->setCascadingSectionResizes(false);
        videoWidget_2->horizontalHeader()->setHighlightSections(true);
        videoWidget_2->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        videoWidget_2->horizontalHeader()->setStretchLastSection(true);
        videoWidget_2->verticalHeader()->setVisible(true);
        startDetectionButton = new QPushButton(groupBox_4);
        startDetectionButton->setObjectName("startDetectionButton");
        startDetectionButton->setGeometry(QRect(830, 310, 81, 31));
        openFileButton = new QPushButton(groupBox_4);
        openFileButton->setObjectName("openFileButton");
        openFileButton->setGeometry(QRect(770, 30, 141, 31));
        startDetectionButton_2 = new QPushButton(groupBox_4);
        startDetectionButton_2->setObjectName("startDetectionButton_2");
        startDetectionButton_2->setGeometry(QRect(740, 310, 81, 31));
        groupBox_5 = new QGroupBox(page_2);
        groupBox_5->setObjectName("groupBox_5");
        groupBox_5->setGeometry(QRect(10, 390, 931, 161));
        resultText = new QTextBrowser(groupBox_5);
        resultText->setObjectName("resultText");
        resultText->setGeometry(QRect(30, 20, 881, 131));
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        label_3 = new QLabel(page_3);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(60, 50, 53, 15));
        label_4 = new QLabel(page_3);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(860, 40, 53, 15));
        label_5 = new QLabel(page_3);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(60, 510, 53, 15));
        label_6 = new QLabel(page_3);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(860, 500, 53, 15));
        testWidget = new QTableWidget(page_3);
        testWidget->setObjectName("testWidget");
        testWidget->setGeometry(QRect(270, 180, 351, 191));
        stackedWidget->addWidget(page_3);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1027, 21));
        menuweishenem1 = new QMenu(menubar);
        menuweishenem1->setObjectName("menuweishenem1");
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName("menu_2");
        menu_3 = new QMenu(menubar);
        menu_3->setObjectName("menu_3");
        menu = new QMenu(menubar);
        menu->setObjectName("menu");
        MainWindow->setMenuBar(menubar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);

        menubar->addAction(menuweishenem1->menuAction());
        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menubar->addAction(menu_3->menuAction());
        menuweishenem1->addAction(actionOpen);
        menuweishenem1->addAction(action_Excel);
        menuweishenem1->addAction(actionExit);
        menu->addAction(action_D);
        menu->addAction(actionWatch);
        menu->addSeparator();
        toolBar->addAction(actionOpen);
        toolBar->addAction(action_create);
        toolBar->addAction(action_open_workspace);
        toolBar->addAction(action_D);
        toolBar->addAction(actionWatch);
        toolBar->addAction(actionExit);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272\347\263\273\347\273\237(E)", nullptr));
#if QT_CONFIG(tooltip)
        actionExit->setToolTip(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272\347\263\273\347\273\237", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionExit->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+E", nullptr));
#endif // QT_CONFIG(shortcut)
        actionOpen->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266(O)", nullptr));
#if QT_CONFIG(tooltip)
        actionOpen->setToolTip(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionOpen->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        actionWatch->setText(QCoreApplication::translate("MainWindow", "\346\237\245\347\234\213\346\243\200\346\265\213\346\203\205\345\206\265\357\274\210W\357\274\211", nullptr));
#if QT_CONFIG(tooltip)
        actionWatch->setToolTip(QCoreApplication::translate("MainWindow", "\346\237\245\347\234\213\346\243\200\346\265\213\344\277\241\346\201\257", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionWatch->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+W", nullptr));
#endif // QT_CONFIG(shortcut)
        action_D->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213\346\243\200\346\265\213\357\274\210D\357\274\211", nullptr));
#if QT_CONFIG(tooltip)
        action_D->setToolTip(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213\346\243\200\346\265\213", nullptr));
#endif // QT_CONFIG(tooltip)
        action_Excel->setText(QCoreApplication::translate("MainWindow", "\346\237\245\347\234\213Excel\350\241\250\346\240\274", nullptr));
#if QT_CONFIG(tooltip)
        action_Excel->setToolTip(QCoreApplication::translate("MainWindow", "\346\237\245\347\234\213", nullptr));
#endif // QT_CONFIG(tooltip)
        action_create->setText(QCoreApplication::translate("MainWindow", "\345\210\233\345\273\272\345\267\245\345\214\272\357\274\210C\357\274\211", nullptr));
#if QT_CONFIG(tooltip)
        action_create->setToolTip(QCoreApplication::translate("MainWindow", "\345\210\233\345\273\272\345\267\245\345\214\272", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        action_create->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+C", nullptr));
#endif // QT_CONFIG(shortcut)
        action_open_workspace->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\345\267\245\345\214\272", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\345\244\204\347\220\206\345\206\205\345\256\271\357\274\232", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\345\244\204\347\220\206\350\277\233\345\272\246\357\274\232", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\346\243\200\346\265\213\346\203\205\345\206\265", nullptr));
        QTableWidgetItem *___qtablewidgetitem = detailsWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "\345\272\217\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = detailsWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "\346\241\251\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = detailsWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "\350\264\237\350\264\243\344\272\272", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = detailsWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "\346\227\245\346\234\237", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = detailsWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "\350\215\257\346\237\261(\344\270\252\346\225\260)", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = detailsWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "\344\270\213\350\215\257\346\235\206(\344\270\252\346\225\260)", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = detailsWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "\350\256\276\350\256\241\344\272\225\346\267\261", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = detailsWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "\351\233\267\347\256\241\344\270\252\346\225\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = detailsWidget->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "\350\215\257\346\237\261\344\270\252\346\225\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = detailsWidget->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "\344\270\213\350\215\257\346\235\206\346\225\260\347\233\256", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = detailsWidget->horizontalHeaderItem(10);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("MainWindow", "\344\272\272\345\267\245\345\244\215\346\243\200", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = detailsWidget->horizontalHeaderItem(11);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("MainWindow", "\347\212\266\346\200\201", nullptr));
        processDetails->setText(QCoreApplication::translate("MainWindow", "\346\227\240", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\347\274\226\350\276\221", nullptr));
        loadButton->setText(QCoreApplication::translate("MainWindow", "\345\212\240\350\275\275\346\225\260\346\215\256", nullptr));
        saveAllButton->setText(QCoreApplication::translate("MainWindow", "\345\205\250\351\203\250\344\277\235\345\255\230", nullptr));
        addButton->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\346\235\241\347\233\256", nullptr));
        deleteButton->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244\346\235\241\347\233\256", nullptr));
        saveButton->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230\345\275\223\345\211\215", nullptr));
        saveFileButton->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\207\272\346\226\207\344\273\266", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "\347\273\237\350\256\241", nullptr));
        updateStatusButton->setText(QCoreApplication::translate("MainWindow", "\346\233\264\346\226\260\347\212\266\346\200\201", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\205\245\346\226\207\344\273\266", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "\351\242\204\347\225\2314", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "\346\243\200\346\265\213", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = videoWidget_2->horizontalHeaderItem(0);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("MainWindow", "Video Files", nullptr));
        startDetectionButton->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213\346\243\200\346\265\213", nullptr));
        openFileButton->setText(QCoreApplication::translate("MainWindow", "open file", nullptr));
        startDetectionButton_2->setText(QCoreApplication::translate("MainWindow", "\344\272\272\345\267\245\345\244\215\346\237\245", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("MainWindow", "\346\243\200\346\265\213\347\273\223\346\236\234", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        menuweishenem1->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MainWindow", "\345\270\256\345\212\251", nullptr));
        menu_3->setTitle(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\347\274\226\350\276\221", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
