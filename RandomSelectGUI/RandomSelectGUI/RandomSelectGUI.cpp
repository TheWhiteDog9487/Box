#include "RandomSelectGUI.h"
#include "QFileDialog"
#include "QDebug"
#include "QMessageBox"
#include "QTimer"
#include <random>
#include <fstream>
#include <deque>
// #include <iostream>
// #include <memory>

// import std;
using namespace std;

random_device RD;
default_random_engine DRE(RD());
deque<wstring> FileContent;

// uniform_int_distribution<int> RN(最小, 最大);
// auto 结果 = RN(DRE);

RandomSelectGUI::RandomSelectGUI(QWidget* parent) : QWidget(parent) {
    static auto RandomTimer = new QTimer(this);
    ui.setupUi(this);

    connect(ui.SelectButton, &QPushButton::clicked, [&]() {
        auto FilePath = QFileDialog().getOpenFileName();
        ui.FilePath->setText(FilePath); });

    connect(ui.FilePath, &QLineEdit::textChanged, [&]() {
        ui.Start->setEnabled(true);
        FileContent.clear();
        wfstream fs(ui.FilePath->text().toStdWString());
        fs.imbue(::std::locale("zh_CN.UTF-8"));     // 匿名变量
        wstring Line = L"";
        if (!fs.is_open()) {
            QMessageBox::critical(this, "错误", "文件打开失败");
            // throw
            return;}
        else {
            wstring Line = L"";
            while (getline(fs, Line)) {
                FileContent.push_back(Line);}}
        fs.close(); });

    connect(ui.Start, &QPushButton::clicked, [&]() {
        ui.Start->setEnabled(false);
        ui.Stop->setEnabled(true);
        ui.NormalRandomMode->setEnabled(false);
        ui.EnhanceRandomMode->setEnabled(false);
        if (FileContent.empty()) {
            QMessageBox::critical(this, "错误", "文件为空");
            return;}
        RandomTimer->start(25); });

    connect(ui.Stop, &QPushButton::clicked, [&]() {
        ui.Start->setEnabled(true);
        ui.Stop->setEnabled(false);
        ui.NormalRandomMode->setEnabled(true);
        ui.EnhanceRandomMode->setEnabled(true);
        RandomTimer->stop(); });

    connect(ui.NormalRandomMode, &QRadioButton::clicked, [&]() {
        qDebug() << "普通";
        disconnect(RandomTimer, &QTimer::timeout,this,nullptr);
        connect(RandomTimer, &QTimer::timeout, [&]() {
            static deque<wstring>::iterator it = FileContent.begin();
            if (it == FileContent.end()) { 
                it = FileContent.begin(); }
            ui.Name->setText(QString::fromStdWString(*it));
            it++; }); });

    connect(ui.EnhanceRandomMode, &QRadioButton::clicked, [&]() {
        qDebug() << "增强";
        disconnect(RandomTimer, &QTimer::timeout, this, nullptr);
        connect(RandomTimer, &QTimer::timeout, [&]() {
            static deque<wstring>::iterator it = FileContent.begin();
            if (it == FileContent.end()) { it = FileContent.begin(); }
            uniform_int_distribution<int> RN(0, FileContent.size() - 1);
            it = FileContent.begin() + RN(DRE);
            ui.Name->setText(QString::fromStdWString(*it)); }); });

    connect(ui.Reload, &QPushButton::clicked, [&]() {
        emit ui.FilePath->textChanged(""); });


    emit ui.NormalRandomMode->click();

}

RandomSelectGUI::~RandomSelectGUI(){
}
