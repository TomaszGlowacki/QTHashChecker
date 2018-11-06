

#ifndef WINDOW_H
#define WINDOW_H

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
    ~Window();

};

#endif // WINDOW_H
