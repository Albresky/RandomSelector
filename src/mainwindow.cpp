#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFont"
//#include <synchapi.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("随机摇号器");
    setWindowIcon(QIcon(":/res/icon.ico"));
    setFixedSize(400,280);

    // Label Text Initialization

    ui->StuNo->setText("学号");
    ui->Range->setText("摇号范围");
    ui->rangeFT->setText("到");

    // range index initialization
    ui->rangeStart->setMinimum(0);
    ui->rangeStart->setMaximum(65535);
    ui->rangeStart->setSingleStep(1);

    ui->rangeEnd->setMinimum(0);
    ui->rangeEnd->setMaximum(65535);
    ui->rangeEnd->setSingleStep(1);

    // 摇号数字Label
    QFont numFont;
    numFont.setPointSize(40);
    numFont.setFamily("微软雅黑");
    ui->number->setText("0");
    ui->number->setFont(numFont);

    // Apply Pushbtn Initialization
    ui->select->setText("摇号");

    // Allocate memory for selectPool
    myPool = new QVector<poolPolicy>;
    if(!isFile("./Config.ini"))
        InitializeCfg("./Config.ini");
    LoadConfig("./Config.ini");


    QObject::connect(ui->actionAbout,&QAction::triggered,this,&MainWindow::about_clicked);

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitializeCfg(QString str)
{
    qDebug()<<"Initialize Config.ini";
    Config cfg = Config(str);
    cfg.Set("Config","poolSize",QVariant("2"));
    cfg.Set("Pool_0","numPool",QVariant("1,2,3,4"));
    cfg.Set("Pool_1","stuID",QVariant("20220506"));
    cfg.Set("Pool_1","numPool",QVariant("5,6,7,8,9,10"));
}


void MainWindow::LoadConfig(QString str){
    Config *cfg = new Config(str);
    int poolSize = cfg->Get("Config","PoolSize").toInt();
    qDebug()<<"poolSize="<<poolSize;

    // Load Default Nums Pool
    poolPolicy *defaultPool = new poolPolicy;
    QString default_pool = cfg->Get("Pool_0","numPool").toString();
    qDebug()<<"defaultPool="<<default_pool<<Qt::endl<<"======";

    // Split string
    QStringList default_pool_list = default_pool.split(',');
    for(int i = 0;i<default_pool_list.size();i++)
    {
        defaultPool->numPool.push_back(default_pool_list[i]);
    }
    myPool->push_back(*defaultPool);

    for(int i=1;i<poolSize;i++)
    {
        poolPolicy *pool=new poolPolicy;
        QString pool_Num="Pool_"+QString::number(i);
        QString stuID=cfg->Get(pool_Num,"StuID").toString();
        qDebug()<<"stuID="<<stuID;
        pool->stuID=stuID;

        QString _pool=cfg->Get(pool_Num,"numPool").toString();
        qDebug()<<"numPool="<<_pool<<Qt::endl<<"======";
        QStringList _pool_list= _pool.split(',');

        for(int j=0;j<_pool_list.size();j++)
        {
            pool->numPool.push_back(_pool_list[j]);
        }
        myPool->push_back(*pool);
    }
    delete cfg;
}

QString MainWindow::getRandomNum(QVector<QString> &vector)
{
    int size = vector.size();
    QString rdm = "";
    //    srand((unsigned)time(nullptr));
    int index=rand();
    qDebug()<<"index="<<index;
    rdm = vector[index % size];
    qDebug()<<"rdm="+rdm;
    return rdm;
}

void MainWindow::showNum(const int &num, const int &a, const int &b)
{
    if(num<a||num>b)
    {
        qDebug()<<"a="<<a<<";b="<<b;
        QMessageBox::warning(this, QStringLiteral("警告"), QStringLiteral("序号范围非法2"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }
    //    bool flag = false;
    //    int iNum=num.toInt();
    //    for(int i=0;(i%10)<10;i++)
    //    {
    //        if(i==9)
    //            flag=true;

    //        ui->number->setText(QString::number(i));

    //        if(flag&&!(i-iNum))
    //        {
    ui->number->setText(QString::number(num));
    //            break;
    //        }
    //    }
}


void MainWindow::on_select_clicked()
{
    qDebug()<<"Btn clicked!";
    qDebug()<<"stuID="<<ui->stuNum->text();
    if(ui->stuNum->text().isEmpty())
    {
        QMessageBox::warning(this, QStringLiteral("警告"), QStringLiteral("未指定学号"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }
    QString rangeS=ui->rangeStart->text(),rangeE=ui->rangeEnd->text();
    if(rangeS.isEmpty()||rangeE.isEmpty()||rangeS>rangeE)
    {
        QMessageBox::warning(this, QStringLiteral("警告"), QStringLiteral("序号范围非法"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }
    QString stuID = ui->stuNum->text();
    QVector<poolPolicy>::Iterator it=myPool->end();
    for(--it;it!=myPool->begin();it--)
    {
        if(it->stuID==stuID)
            break;
    }
    qDebug()<<"stuID="<<it->stuID;
    QString num=getRandomNum(it->numPool);
    qDebug()<<"num="<<num;
    showNum(num.toInt(),ui->rangeStart->text().toInt(),ui->rangeEnd->text().toInt());
}

void MainWindow::about_clicked()
{
    aboutWindow *aboutWin =new aboutWindow();
    qDebug()<<"about Menubar-menu clicked";
    aboutWin->show();
}

