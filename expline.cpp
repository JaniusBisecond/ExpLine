#include "expline.h"
#include "ui_expline.h"
#include <synchapi.h>
#include <QDebug>

Expline::Expline(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Expline)
{
    ui->setupUi(this);
    init();
}

Expline::~Expline()
{
    delete ui;
}

void Expline::init()
{
    this->setFixedSize(_width,_height);
    readHistory();
    visibleSetting(true);
    visibleExpSetting(false);
    showData();
}

void Expline::readHistory()
{
    _file.open("./config.ini",std::fstream::in);
    if(_file)
    {
        _file>>_progressName >>_level >> _progress >> _total;
        _file.close();
    }
    else
    {
        _file.open("./config.ini",std::fstream::out);
        _file.close();
    }
}

void Expline::closeEvent(QCloseEvent *event)
{
    _progress = ui->progressBar->value();
    _level = ui->levelLable->text().toUInt();
    saveData();
}

void Expline::shrinkWindow(int start, int end)
{
    if(start < end)
    {
        while(start != end)
        {
            this->setFixedSize(_width,++start);
        }
    }
    else
    {
        while(start != end)
        {
            this->setFixedSize(_width,--start);
        }
    }
}

void Expline::showData()
{
    ui->programLable->setText(QString::fromStdString(_progressName)+":");
    ui->levelLable->setText(QString::number(_level));
    ui->progressBar->setRange(0,_total);
    ui->progressBar->setValue(_progress);
}

void Expline::saveData()
{
    _file.open("./config.ini",std::fstream::out);
    if(_file)
    {
        _file << _progressName <<" "<< _level<< " " << _progress<<" "<<_total;
        _file.close();
    }
}

void Expline::checkExperience()
{
    _total = ui->progressBar->maximum();
    if(_progress == _total)
    {
        ++_level;
        _progress = 0;
        ui->progressBar->setRange(0,0);
        visibleSetting(false);
        visibleExpSetting(true);
        shrinkWindow(_height,2*_height);
    }
}

void Expline::visibleSetting(bool flag)
{
    ui->setting->setVisible(flag);
}

void Expline::visibleExpSetting(bool flag)
{
    ui->expSetting->setVisible(flag);
}


void Expline::on_addBtn_clicked()
{
    _progress = ui->progressBar->value();
    ++_progress;
    checkExperience();
    showData();
}


void Expline::on_decBtn_clicked()
{
    int value = ui->progressBar->value();
    --value;
    ui->progressBar->setValue(value);
}


void Expline::on_setBtn_clicked()
{
    if(this->height() == _height*2)
    {
        shrinkWindow(_height*2,_height);
    }
    else
    {
        shrinkWindow(_height,2*_height);
    }
}


void Expline::on_submitBtn_clicked()
{
    _progressName = ui->nameEdit->text().toStdString();
    _total = ui->progressEdit->text().toUInt();
    _progress = 0;
    _level = 1;
    showData();
    shrinkWindow(_height*2,_height);
    ui->nameEdit->clear();
    ui->progressEdit->clear();
}


void Expline::on_expBtn_clicked()
{
    _total = ui->expEdit->text().toUInt();
    showData();
    shrinkWindow(_height*2,_height);
    visibleExpSetting(false);
    visibleSetting(true);
}

