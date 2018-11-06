#ifndef WINDOW_H
#define WINDOW_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QProgressBar>
#include <QTabBar>
#include <QMessageBox>


class Window : public QWidget
{
Q_OBJECT

    QPushButton *m_button;
    QProgressBar *progressBar;

    int value;

public slots:
    void slotButtonClicked(bool checked);

public:

    Window(QWidget *parent = 0);
    virtual ~Window();

};


#endif // WINDOW_H
