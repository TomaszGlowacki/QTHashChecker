

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QDateTime>
#include <QTextStream>
#include <QtGui>
#include <QCryptographicHash>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(1400, 700);

    LabeltoPathToFiles = new QLabel("Path to directory", this);
    LabeltoPathToFiles-> setGeometry(100,50,200,50);
    PathToFiles = new QTextEdit(this);
    QString path = QDir::currentPath() + "/workplace/";
    PathToFiles->setText(path);
    PathToFiles->setGeometry(300, 50, 700, 80);

    LabeltoNumberOfFiles = new QLabel("Number of files ", this);
    LabeltoNumberOfFiles-> setGeometry(100,130,150,50);
    NumberOfFiles = new QTextEdit(this);
    NumberOfFiles->setGeometry(300, 130, 200, 50);


    LabeltoPasword = new QLabel("Password ", this);
    LabeltoPasword-> setGeometry(100,200,150,50);
    Password = new QTextEdit(this);
    Password->setGeometry(300, 200, 200, 50);

    // hmmm, no need.
    /*
    LabeltoSecretText = new QLabel("Secret text ", this);
    LabeltoSecretText-> setGeometry(100,280,150,50);
    SecretText = new QTextEdit(this);
    SecretText->setGeometry(300, 280, 200, 50);
    */

    CreateFilesButton = new QPushButton("Create Files", this);
    CreateFilesButton->setGeometry(100, 350, 150, 50);
    CreateFilesButton->setCheckable(true);


    CheckFilesButton = new QPushButton("Check Files", this);
    CheckFilesButton->setGeometry(100, 450, 150, 50);

    ProgressLabel = new QLabel("", this);
    ProgressLabel->setGeometry(700, 450, 200, 50);
    progressBar = new QProgressBar(this);
    progressBar->setRange(0, 100);
    progressBar->setValue(0);
    progressBar->setGeometry(300, 450, 400, 50);


    // not so simple 2 actions
    connect(CreateFilesButton, SIGNAL(clicked(bool)), this, SLOT(CreateFilesButtonClicked()));
    connect(CheckFilesButton, SIGNAL(clicked(bool)), this, SLOT(CheckFilesButtonClicked()));

    //connect(m_button, SIGNAL(clicked(bool)), progressBar, SLOT(show()) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::encrypt(QString password, QString time)
{
    QString encryptedText("");
    encryptedText = QString(QCryptographicHash::hash((( password + time).toLatin1()), QCryptographicHash::Md5).toHex());
    return encryptedText;
}

void MainWindow::CreateSingleFile( QString name, int number)
{
    QString temp;
    temp = temp.number(number);
    QString filename=PathToFiles->toPlainText() + name + temp + ".txt";
    QFile file( filename );
    QDateTime dt;
    QString dtstring;
    QString filetext;
    if ( file.open(QIODevice::ReadWrite) )
    {
        dtstring = dt.currentDateTime().toString("yy-MM-dd HH:mm:ss.z");
        filetext = encrypt(Password->toPlainText(), dtstring);
        QTextStream stream( &file );
        stream << temp<< " " << dtstring << " " << filetext ;
    }
}

void MainWindow::CreateFileIfMatched( QString text, int number)
{
    QString temp;
    temp = temp.number(number);
    QString filename=PathToFiles->toPlainText() + "matched" + temp + ".txt";
    QFile file( filename );
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );
        stream << "Password: "<< text ;
    }
}

void MainWindow::WorkDone()
{
    progressBar->setValue(0);
    ProgressLabel->clear();
    ProgressLabel->setText("Done.");

    QCoreApplication::processEvents();
}

void MainWindow::UpdateProgressBar(int count)
{
    progressBar->setValue(progressBar->value() + count);
    progressBar->update();
    QCoreApplication::processEvents(); // I know it slows app, but I like to see moving progress bar without app freeze.
}

void MainWindow::CreateFilesButtonClicked()
{
    //QMessageBox mes;
    //mes.setText(PathToFiles->toPlainText());
    //mes.exec();

    if (!QDir(PathToFiles->toPlainText()).exists())
    {
        QDir().mkdir(PathToFiles->toPlainText());
    }

    int FilesNumber = NumberOfFiles->toPlainText().toInt();
    if (FilesNumber)
    {
        progressBar->setRange(0, FilesNumber);

        for (int i=1; i<= FilesNumber ; ++i)
        {
            CreateSingleFile( "" , i);
            UpdateProgressBar(1);
        }
    }

    WorkDone();
}

bool MainWindow::fileExists(QString path)
{
    QFileInfo check_file(path);
    if (check_file.exists() && check_file.isFile())
    {
        return true;
    }
    else
    {
        return false;
    }
}

QString MainWindow::Generate( int length, QString s, QString Datetime, QString hash, QString number)
{
    if(length <= 0)
    {
        QString CheckHash = encrypt(s, Datetime);
        if (CheckHash == hash )
        {
            //QMessageBox mes;
            //mes.setText(s);
            //mes.exec();
            CreateFileIfMatched( s, number.toInt());
            UpdateProgressBar(1);

            return s;
        }
    }
    else
    {
        if (!fileExists(PathToFiles->toPlainText() + "matched" + number + ".txt"))
        {
            for(unsigned int i = 0; i <= 255; i++)   //why creating alphabets? gimmy every char!
            {
                QString appended = s + QChar(i);
                Generate(length-1, appended,  Datetime,  hash, number );
            }
        }
    }
    return "";
};

QString MainWindow::CheckHash(QString hash, QString Datetime, QString number)
{
    int MaxLength = 10;
    QString ret = "";
    for( int i=1; i<=MaxLength; i++)
    {

        QString str;
        str = Generate(i, "", Datetime, hash, number);
        if (str != "")
            return str;

    }
    return ret;
};

void MainWindow::CheckFilesButtonClicked()
{

    int numoffiles = QDir(PathToFiles->toPlainText()).count()-2;  // exclude parent and this directory
    progressBar->setRange(0, numoffiles);
    progressBar->setValue(0);
    int i= 0;
    QDirIterator it(PathToFiles->toPlainText());


    QDir directory(PathToFiles->toPlainText());
    QStringList files = directory.entryList(QStringList() << "*.txt" , QDir::Files);
    foreach(QString filename, files)
    {

        i++;
        //QMessageBox mes;
        //mes.setText(QString("").number(i) + PathToFiles->toPlainText());
        //mes.exec();


        ProgressLabel->setText(it.fileName() + i);
        ProgressLabel->clear();
        QCoreApplication::processEvents();
        QFile file( PathToFiles->toPlainText() + filename);

        if (!file.open(QFile::ReadOnly | QFile::Text)) break;  // uff, golden line
        QTextStream in(&file);
        QString content;
        content = in.readAll();

        QString number = content.section(" ", 0 , 0);
        QString date = content.section(" ", 1 , 1);
        QString time = content.section(" ", 2 , 2);
        QString hash = content.section(" ", 3 , 3);


        //mes.setText(content + " " + filename);
        //mes.exec();

        QString finededstring = CheckHash(hash, date + " " + time, number);



        it.next();
    }

    WorkDone();
}







