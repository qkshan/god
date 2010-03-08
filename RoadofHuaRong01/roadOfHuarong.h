#ifndef ROADOFHUARONG_H
#define ROADOFHUARONG_H

#include <QMainWindow>

class QAction;
class QLabel;
class QPushButton;

class FindDialog;


class RoadOfHR:public QMainWindow
{
Q_OBJECT
public:
    RoadOfHR();

protected:
    void closeEvent(QCloseEvent *);

private slots:
    void newGame();
    void open();
    bool save();
    void about();
    void find();
    void exit();
   // void updateStatusBar();
    void gameModified();

private:
    void createActions();
    void createMenus();

    void readSettings();
    void writeSettings();

    bool loadGame(const QString &fileName);
    bool saveGame(const QString &fileName);

    bool okToContinue();
    bool isGameModified();

    void setCurrentGame(const QString &fileName);
    void updateRecentGameActions();

    QString strippedName(const QString &fullGameName);

    FindDialog *findDialog;

    QWidget *centralWidget;
    QLabel *locationLabel;
    QPushButton *pushButton;

    QString curGame;
    enum { MaxRecentGames = 5 };

    QAction *recentGameActions[MaxRecentGames];
    QAction *separatorAction;

    QMenu *fileMenu;
    QMenu *helpMenu;


    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *exitAction;
    QAction *findAction;

    QAction *aboutGameAction;
    QAction *aboutQtAction;


};

#endif // ROADOFHUARONG_H
