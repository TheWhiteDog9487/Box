#pragma once

#include <QtWidgets/QWidget>
#include "ui_RandomSelectGUI.h"

class RandomSelectGUI : public QWidget
{
    Q_OBJECT

public:

    RandomSelectGUI(QWidget *parent = nullptr);
    ~RandomSelectGUI();

private:
    Ui::RandomSelectGUIClass ui;
};
