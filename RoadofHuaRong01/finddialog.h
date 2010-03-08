#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>

class QCheckBox;//使用了他们的指针，只需要前向声明即可，可加快编译
class QLabel;
class QLineEdit;
class QPushButton;

class FindDialog : public QDialog
{
    Q_OBJECT
    public:
        FindDialog(QWidget *parent = 0);

    signals:
        void findNext(const QString &str, Qt::CaseSensitivity cs);
        void findPrevious(const QString &str, Qt::CaseSensitivity cs);

    private slots:
        void findClicked();
        void enableFindButton(const QString &text);

    private:
        QLabel *label;
        QLineEdit *lineEdit;
        QCheckBox *caseCheckBox;
        QCheckBox *backwardCheckBox;
        QPushButton *findButton;
        QPushButton *closeButton;
};

#else
#endif
