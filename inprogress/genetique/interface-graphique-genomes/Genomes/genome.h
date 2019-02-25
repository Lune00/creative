#ifndef GENOME_H
#define GENOME_H

#include<QString>

class Genome
{

public:
    Genome();
    Genome(QString name) { name_ = name ; nbTraits_ = 0 ;}
    QString name() const { return name_;}
    int nbTraits() const  { return nbTraits_;}
    void setname(QString name);
    void setcomments(QString comments) { comments_ = comments;}

private:
    QString name_;
    QString comments_;
    int nbTraits_;
};

inline bool operator==(const Genome& a, const Genome& b) {
    return a.name() == b.name();
}

#endif // GENOME_H
