#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //default host
    ui->labelEditHost->setText("tcp://" + ui->lineEditIp->text() + ":" + ui->lineEditPort->text());

    //default topic
    ui->labelEditUri->setText(ui->lineEditUri->text());

    //create worker
    worker = new Worker();
    connect(&workerThread, &QThread::started, worker, &Worker::doWork);
    connect(worker, &Worker::resultReady, this, &MainWindow::updateText);
    worker->moveToThread(&workerThread);
}

MainWindow::~MainWindow()
{
    workerThread.quit();
    workerThread.wait();
    delete ui;
}

void MainWindow::on_btnStart_clicked()
{

    if(workerThread.isRunning()){

        //Stop section
        ui->btnStart->setText("Start");

        worker->setAbort(true);
        workerThread.quit();

        ui->statusBar->showMessage("Server stopped...");
    }
    else{

        //Start Section
        ui->btnStart->setText("Stop");

        worker->setHost(ui->labelEditHost->text());
        worker->setTopic(ui->labelEditUri->text());
        workerThread.start();

        ui->statusBar->showMessage("Server is listening...");
    }

}

void MainWindow::on_btnClear_clicked()
{
    ui->textBrowser->setText("");
}

void MainWindow::updateText(const QString &result)
{
    ui->textBrowser->append(result);
    ui->textBrowser->append("\n\n\n");
}

void MainWindow::on_lineEditIp_textChanged(const QString &arg1)
{
    /* tcp://10.0.0.208:6001 */
    ui->labelEditHost->setText("tcp://" + ui->lineEditIp->text() + ":" + ui->lineEditPort->text());
}

void MainWindow::on_lineEditPort_textChanged(const QString &arg1)
{
    /* tcp://10.0.0.208:6001 */
    ui->labelEditHost->setText("tcp://" + ui->lineEditIp->text() + ":" + ui->lineEditPort->text());
}

void MainWindow::on_lineEditUri_textChanged(const QString &arg1)
{
    ui->labelEditUri->setText(ui->lineEditUri->text());
}
