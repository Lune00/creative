#include "options.h"
#include "QVBoxLayout"
#include "QFile"
#include "QCoreApplication"
#include "QDebug"

OptionsDialog::OptionsDialog(QWidget *parent) : QDialog(parent)
{
    //Main Layout:
    QVBoxLayout* main_layout = new QVBoxLayout;

    //--Widgets:
    checkBox_activate_mutations_ = new QCheckBox("Activer mutations",this);
    checkBox_activate_mutations_->setLayoutDirection(Qt::RightToLeft);

    main_layout->addWidget(checkBox_activate_mutations_);
    main_layout->setSizeConstraint(QLayout::SetFixedSize);

    setLayout(main_layout);
}
