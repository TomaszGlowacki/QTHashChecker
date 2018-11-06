#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QProgressBar>
#include <QTabBar>
#include <QMessageBox>
#include <QTextEdit>
#include <QLabel>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;

    QPushButton *CreateFilesButton;
    QPushButton *CheckFilesButton;


    QLabel *LabeltoNumberOfFiles;
    QTextEdit *NumberOfFiles;

    QLabel *LabeltoPathToFiles;
    QTextEdit *PathToFiles;

    QLabel *LabeltoPasword;
    QTextEdit *Password;

    QLabel *LabeltoSecretText;
    QTextEdit *SecretText;

    QLabel *ProgressLabel;
    QProgressBar *progressBar;

    volatile int value;


    void CreateSingleFile(QString name, int number);
    void WorkDone();
    QString encrypt(QString password, QString time);
    void UpdateProgressBar(int count);
    void CreateFileIfMatched( QString text, int number );
    QString CheckHash(QString hash, QString datetime, QString number);
    QString Generate( int length, QString s, QString Datetime, QString hash, QString number);
    bool fileExists(QString path);

    // no time for those, need more 2-4 days to implement for each.
    void CheckWithOpenCL();
    void CheckWIthCuda();

public slots:
    void CreateFilesButtonClicked();
    void CheckFilesButtonClicked();
public:
    MainWindow(QWidget *parent = 0);
    MainWindow(QWidget *parent, Ui::MainWindow *lui);
    virtual ~MainWindow();

};

#endif // MAINWINDOW_H
