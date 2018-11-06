
#include "window.h"

Window::~Window() {};

Window::Window(QWidget *parent) : QWidget(parent)
{
    setFixedSize(1000, 500);

    m_button = new QPushButton("Hello World", this);
    m_button->setGeometry(50, 50, 150, 50);
    m_button->setCheckable(true);
    progressBar = new QProgressBar(this);
    progressBar->setRange(0, 100);
    progressBar->setValue(0);
    progressBar->setGeometry(100, 100, 280, 130);


    connect(m_button, SIGNAL(clicked(bool)), this, SLOT(slotButtonClicked(bool)));
};

void Window::slotButtonClicked(bool checked)
{
    if (checked) {
        m_button->setText("Checked");
    }
    else {
        m_button->setText("Hello World2222");
    }
    value++;
    QMessageBox mes;
    mes.setText("asd");
    mes.exec();
}
