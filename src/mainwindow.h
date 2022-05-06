#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QMessageBox>
#include <QStringList>
#include "functions.h"
#include "config.h"
#include "QDebug"
#include "aboutwindow.h"
#include "FileOperator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void LoadConfig(QString str);
    QString getRandomNum(QVector<QString> &vector);
    void showNum(QString num, const QString &a, const QString &b);
    void InitializeCfg(QString str);
private slots:
    void on_select_clicked();
    void about_clicked();

private:
    QVector<poolPolicy> *myPool;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
