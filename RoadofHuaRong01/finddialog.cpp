#include <QtGui>
#include "finddialog.h"

FindDialog::FindDialog(QWidget *parent)
    :QDialog(parent)
{
    label = new QLabel(tr("Find &what:"));//&快捷键ALT+w
    lineEdit = new QLineEdit;
    label->setBuddy(lineEdit);//ALT+W使编辑框获得焦点

    caseCheckBox = new QCheckBox(tr("Match &case"));
    backwardCheckBox = new QCheckBox(tr("Search &Backward"));
    findButton = new QPushButton(tr("&Find"));

    findButton->setDefault(true);//默认按钮Enter
    findButton->setEnabled(false);

    closeButton = new QPushButton(tr("Close"));

    connect(lineEdit, SIGNAL(textChanged(const QString&)),
            this, SLOT(enableFindButton(const QString&)));
    connect(findButton, SIGNAL(clicked()),
            this, SLOT(findClicked()));
    connect(closeButton, SIGNAL(clicked()),
            this, SLOT(close()));

    QHBoxLayout *topLeftLayout = new QHBoxLayout;//布局

    topLeftLayout->addWidget(label);
    topLeftLayout->addWidget(lineEdit);

    QVBoxLayout *LeftLayout = new QVBoxLayout;//布局
    LeftLayout->addLayout(topLeftLayout);
    LeftLayout->addWidget(caseCheckBox);
    LeftLayout->addWidget(backwardCheckBox);

    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(findButton);
    rightLayout->addWidget(closeButton);
    rightLayout->addStretch();

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(LeftLayout);
    mainLayout->addLayout(rightLayout);

    setLayout(mainLayout);
    setWindowTitle(tr("Find"));
    setFixedHeight(sizeHint().height());

}

void FindDialog::findClicked()
{
    QString text = lineEdit->text();
    Qt::CaseSensitivity cs =
            caseCheckBox->isChecked()?Qt::CaseSensitive
                :Qt::CaseInsensitive;
    if(backwardCheckBox->isChecked())
    {
        emit findPrevious(text, cs);
    }
    else
    {
        emit findNext(text, cs);
    }
}

void FindDialog::enableFindButton(const QString &text)
{
    findButton->setEnabled(!text.isEmpty());
}
