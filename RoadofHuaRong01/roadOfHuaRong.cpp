/*
  main.cpp
*/
#include <QtGui>

#include "roadOfHuarong.h"
#include "finddialog.h"


RoadOfHR::RoadOfHR()
{
    //spreadsheet = new Spreadsheet;
   // setCentralWidget(spreadsheet);
    createActions();
    createMenus();
   //createStatusBar();
    readSettings();

    findDialog = 0;//查找对话框

    //setWindowIcon(QIcon(":/../static/icon.png"));
    setCurrentGame("");

    centralWidget = new QWidget;
    pushButton = new QPushButton(tr("Go!"), centralWidget);
    //pushButton->resize(100,20);
    //pushButton->move(centralWidget->width()/2,0);

    QHBoxLayout *topLeftLayout = new QHBoxLayout;//布局
    topLeftLayout->addStretch();
    topLeftLayout->addWidget(pushButton);
    topLeftLayout->addStretch();
    

    QVBoxLayout *centralLayout = new QVBoxLayout;
    centralLayout->addLayout(topLeftLayout);
    centralLayout->addStretch();


    centralWidget->setLayout(centralLayout);
    this->setCentralWidget(centralWidget);
    //setFixedHeight(sizeHint().height());

}

void RoadOfHR::createActions()
{
    newAction = new QAction(tr("&New Game"), this);
    newAction->setShortcut(tr("Ctrl+N"));
    connect(newAction, SIGNAL(triggered()), this, SLOT(newGame()));

    openAction = new QAction(tr("&Open Game"), this);
    openAction->setShortcut(tr("Ctrl+O"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

    saveAction = new QAction(tr("&Save"), this);
    saveAction->setShortcut(tr("Ctrl+S"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

    findAction = new QAction(tr("&Find"), this);
    findAction->setShortcut(tr("Ctrl+F"));
    connect(findAction, SIGNAL(triggered()), this, SLOT(find()));

    exitAction = new QAction(tr("&Exit Game"), this);
    exitAction->setShortcut(tr("Ctrl+E"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(exit()));


    aboutGameAction = new QAction(tr("&About Game"), this);
    aboutGameAction->setShortcut(tr("F1"));
    connect(aboutGameAction, SIGNAL(triggered()), this, SLOT(about()));


    aboutQtAction = new QAction(tr("About &Qt"), this);
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void RoadOfHR::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);

    separatorAction = fileMenu->addSeparator();
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutGameAction);
    helpMenu->addAction(aboutQtAction);
    //helpMenu->addAction(findAction);

}


bool RoadOfHR::isGameModified()
{


    return FALSE;
}

//Slot
void RoadOfHR::gameModified()
{

}

//提示是否保存游戏
bool RoadOfHR::okToContinue()
{
    if (isGameModified())
    {
        int r = QMessageBox::warning(this, tr("Alert"),
                        tr("The Game has not been Saved. "
                           "Do you want to save your Game?"),
                        QMessageBox::Yes | QMessageBox::Default,
                        QMessageBox::No,
                        QMessageBox::Cancel | QMessageBox::Escape);

        if (r == QMessageBox::Yes)
        {
            return save();
        } else if (r == QMessageBox::Cancel)
        {
            return false;
        }
    }
    return true;
}


//新的游戏开局
void RoadOfHR::newGame()
{
    if(okToContinue())
    {
       // spreadsheet->clear();
        setCurrentGame("");
    }
}

//打开游戏进度文件
void RoadOfHR::open()
{
    if(okToContinue())
    {
        QString fileName = QFileDialog::getOpenFileName(this,
                                   tr("Open Spreadsheet"), ".",
                                   tr("Spreadsheet files (*.sp)"));

        if (!fileName.isEmpty())
            loadGame(fileName);
    }
}

//保存当前进度
bool RoadOfHR::save()
{
    return TRUE;
}

void RoadOfHR::exit()
{
    qApp->quit();
}

//根据用户名保存游戏进度
bool RoadOfHR::saveGame(const QString &fileName)
{
//    if (!spreadsheet->writeFile(fileName)) {
//        statusBar()->showMessage(tr("Saving canceled"), 2000);
//        return false;
//    }

    setCurrentGame(fileName);
//    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

//设置当前游戏进度名
void RoadOfHR::setCurrentGame(const QString &fileName)
{
    curGame = fileName;
    setWindowModified(false);

    QString shownName = "Untitled";
    if(!curGame.isEmpty())
    {
        shownName = strippedName(curGame);
        //recentFiles.removeAll(curFile);
        //recentFiles.prepend(curFile);
       // updateRecentFileActions();
    }

    setWindowTitle(tr("%1[*] - %2").arg(shownName)
                                   .arg(tr("RoadOfHuarong")));
}

//删除文件路径，保留名字
QString RoadOfHR::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

//查找对话框：与游戏无关，实验
void RoadOfHR::find()
{
    if (!findDialog)
    {
        findDialog = new FindDialog(this);
//        connect(findDialog, SIGNAL (findNext(const QString &,
//                                            Qt::CaseSensitivity)),
//                spreadsheet, SLOT (findNext(const QString &,
//                                            Qt::CaseSensitivity)));
//        connect(findDialog, SIGNAL(findPrevious(const QString &,
//                                                Qt::CaseSensitivity)),
//                 spreadsheet, SLOT(findPrevious(const QString &,
//                                                Qt::CaseSensitivity)));
    }

    if (findDialog->isHidden())
    {
        findDialog->show();
    }
    else
    {
        findDialog->activateWindow();
    }
}

void RoadOfHR::about()
{
    QMessageBox::about(this, tr("About RoadOfHuarong"),
            tr("<h2>RoadOfHuarong 1.1</h2>"
               "<p>Copyright &copy; 2010 my.duanli@gmail.com."
               "<p>RoadOfHuarong is a small Game that "
               "was done for fun."));
}

//记录上次游戏成绩
void RoadOfHR::writeSettings()
{
    //QSettings:在Windows中使用注册表；在Unix中把数据存贮在文本文件中
    QSettings settings("My.DuanLi@gmail.com", "RoadOfHuarong");
//    settings.setValue("geometry", geometry());
//    settings.setValue("recentFiles", recentFiles);
//    settings.setValue("showGrid", showGridAction->isChecked());
//    settings.setValue("autoRecalc", autoRecalcAction->isChecked());
}

//读取注册数据
void RoadOfHR::readSettings()
{
    QSettings settings("Software Inc.", "Spreadsheet");
//    QRect rect = settings.value("geometry",
//                                QRect(200, 200, 400, 400)).toRect();
//    move(rect.topLeft());
//    resize(rect.size());
//    recentFiles = settings.value("recentFiles").toStringList();
//
//    bool showGrid = settings.value("showGrid", true).toBool();
//    showGridAction->setChecked(showGrid);
//
//    bool autoRecalc = settings.value("autoRecalc", true).toBool();
//    autoRecalcAction->setChecked(autoRecalc);
}

//加载存档游戏
bool RoadOfHR::loadGame(const QString &fileName)
{
    return TRUE;

}


//关闭游戏
void RoadOfHR::closeEvent(QCloseEvent *event)
{
    if (okToContinue())
    {
        writeSettings();
        event->accept();
    }
    else
    {
        event->ignore();
    }
}


