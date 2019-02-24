#ifndef GENOME_H
#define GENOME_H

#include<QString>

class Genome
{

public:
    Genome();
    QString name() const { return name_;}
    int nbTraits() const  { return nbTraits_;}
    void setname(QString name);

private:
    QString name_;
    int nbTraits_;
};

#endif // GENOME_H
