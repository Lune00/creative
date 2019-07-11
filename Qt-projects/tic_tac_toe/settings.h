//#ifndef SETTINGS_H
//#define SETTINGS_H
#pragma once
#include<QString>

namespace settings {

    enum typeOfBoard{
        standard = 0, ultimate = 1, undefined = 2
    };

    inline QString enumToString(const typeOfBoard& type){
        switch (type) {
        case standard: return QString("Standard");
        case ultimate: return QString("Ultimate");
        default: return QString("undefined");
        }
    }

    inline typeOfBoard stringToEnum(const QString& string){
        if ( string == QString("Standard") )
            return typeOfBoard::standard;
        else if ( string == QString("Ultimate"))
            return typeOfBoard::ultimate;
        else
            return  typeOfBoard::undefined;
    }
}
//#endif // SETTINGS_H
