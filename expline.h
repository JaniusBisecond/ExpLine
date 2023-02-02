#ifndef EXPLINE_H
#define EXPLINE_H

#include <QWidget>
#include <string>
#include <QString>
#include <fstream>

QT_BEGIN_NAMESPACE
namespace Ui { class Expline; }
QT_END_NAMESPACE

class Expline : public QWidget
{
    Q_OBJECT

public:
    Expline(QWidget *parent = nullptr);
    ~Expline();


private:
    void init();
    void readHistory();
    void closeEvent(QCloseEvent *event);
    void shrinkWindow(int start, int end);
    void showData();
    void saveData();
    void checkExperience();
    void visibleSetting(bool flag);
    void visibleExpSetting(bool flag);

private slots:
    void on_addBtn_clicked();
    void on_decBtn_clicked();
    void on_setBtn_clicked();
    void on_submitBtn_clicked();

    void on_expBtn_clicked();

private:
    Ui::Expline *ui;
    int _width = 670;
    int _height = 75;
    std::string _progressName;
    uint _level;
    uint _progress;
    uint _total;
    std::fstream _file;
};
#endif // EXPLINE_H
