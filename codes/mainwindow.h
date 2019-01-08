#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "worker.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnStart_clicked();
    void on_btnClear_clicked();
    void on_lineEditIp_textChanged(const QString &arg1);
    void on_lineEditPort_textChanged(const QString &arg1);
    void updateText(const QString &result);

    void on_lineEditUri_textChanged(const QString &arg1);

signals:
    void startDoWork();

private:
    Ui::MainWindow *ui;
    Worker *worker;
    QThread workerThread;
};

#endif // MAINWINDOW_H
