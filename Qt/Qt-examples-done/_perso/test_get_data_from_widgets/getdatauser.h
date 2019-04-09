#ifndef GETDATAUSER_H
#define GETDATAUSER_H

#include<QString>

class GetDataUser
{
public:
    GetDataUser();
    GetDataUser(QString);
    QString getText() const { return text;}
    void setText(QString t) {  text = t;}
private:
    QString text;
};

#endif // GETDATAUSER_H
