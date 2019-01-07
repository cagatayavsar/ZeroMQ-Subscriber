#include "worker.h"
#include "zmq.hpp"
#include <iostream>

Worker::Worker(QObject *parent, QString host, QString topic) : QObject(parent), host(host), topic(topic)
{}

void Worker::setHost(QString host)
{
    this->host = host;
}

void Worker::setTopic(QString topic)
{
    this->topic = topic;
}

void Worker::setAbort(bool abort)
{
    this->abort = abort;
}

void Worker::doWork()
{
    zmq::context_t context(1);
    zmq::socket_t subscriber (context, ZMQ_SUB);
    subscriber.connect(host.toStdString());

    std::string sTopic = topic.toStdString();
    zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, &sTopic[0], sTopic.size() * sizeof (sTopic[0]));

    abort = false;
    while (!abort){
        zmq::message_t message;

        //Read envelope with address
        subscriber.recv(&message);
        std::string address = std::string(static_cast<char*>(message.data()), message.size());

        //Read message contents
        subscriber.recv(&message);
        std::string contents = std::string(static_cast<char*>(message.data()), message.size());

        QString allContents = QString::fromStdString( "<h1>" + address + "</h1>" + contents);

        if(!abort)
            emit resultReady(allContents);
    }

}



