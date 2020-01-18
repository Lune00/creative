#ifndef OPTIONS_H
#define OPTIONS_H

#include <QWidget>
#include <QDialog>
#include "QCheckBox"
#include "QGroupBox"

class OptionsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit OptionsDialog(QWidget *parent = nullptr);

private:

    QGroupBox* Mutations_;
    QCheckBox* checkBox_activate_mutations_;
};

#endif // OPTIONS_H
