#include "bus.h"
#include <QtDebug>


Bus::Bus()
{

}

QStandardItemModel *Bus::readCSV(QFile *file)
{
    file = new QFile();
    file->setFileName("E:\\Projects\\Qt\\pattern\\bus.csv");
    file->open(QFile::ReadOnly | QFile::Text);

    qDebug() << "Hi read CSV";
    QStandardItemModel * model = new QStandardItemModel();
    model->setColumnCount(9);

    QTextStream in(file);
    if(!in.atEnd()){
        QString line = in.readLine();
        QStringList stringList;
        for(QString item : line.split(";")){
            stringList << item;
        }
        model->setHorizontalHeaderLabels(stringList);

        qDebug() << stringList;
    }

    while(!in.atEnd()){
        QString line = in.readLine();
        QList<QStandardItem *> stdItemList;
        for(QString item : line.split(";")){
            stdItemList.append(new QStandardItem(item));
        }
        model->insertRow(model->rowCount(),stdItemList);
        qDebug() << stdItemList;
    }
    file->close();

    return model;
}
