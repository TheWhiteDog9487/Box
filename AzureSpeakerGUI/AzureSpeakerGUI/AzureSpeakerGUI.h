#pragma once
#include <speechapi_cxx.h>
using namespace Microsoft::CognitiveServices::Speech;
using namespace Microsoft::CognitiveServices::Speech::Audio;
//using namespace std;

#include <QtWidgets/QMainWindow>
#include "ui_AzureSpeakerGUI.h"

class AzureSpeakerGUI : public QMainWindow
{
    Q_OBJECT

public:
    AzureSpeakerGUI(QWidget *parent = nullptr);
    ~AzureSpeakerGUI();

private:
    Ui::AzureSpeakerGUIClass ui;
};