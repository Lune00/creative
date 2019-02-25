#include "genome.h"

Genome::Genome()
{
    name_ = QString();
    nbTraits_ = 0 ;
}
void Genome::setname(QString name)
{
    if( name_ != name)
        name_ = name ;
}
