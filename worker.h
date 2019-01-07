#ifndef WORKER_H
#define WORKER_H

#include <QObject>

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr, QString host = "", QString topic = "");
    void setHost(QString);
    void setTopic(QString);
    void setAbort(bool);

private:
    QString host;
    QString topic;
    bool abort;

signals:
    void resultReady(const QString &result);

public slots:
    void doWork();

};

#endif // WORKER_H
