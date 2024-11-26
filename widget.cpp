#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    Init();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::Init()
{
    // 读文件
    QFile file("config.txt");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QByteArray buf = file.readLine();
        m_speed = QString(buf).toInt();
        file.close();
    }

    connect(&m_timer, &QTimer::timeout, this, &Widget::OnTimerOut);
    connect(&m_timer1, &QTimer::timeout, this, [=]()
    {
        m_sec++;
        if(m_sec == 60)
        {
            m_sec = 0;
            m_min++;
        }
        ui->lb_time_game->setText(QString("游戏时间：%1分%2秒").arg(m_min).arg(m_sec));
    });

    // 显示系统时间
    QTimer *timer = new QTimer;
    connect(timer, &QTimer::timeout, this, [=]()
    {
        QDateTime current_time = QDateTime::currentDateTime();
        QString currentTime = current_time.toString("yyyy-MM-dd hh:mm:ss");
        ui->lb_time_sys->setText(currentTime);
    });
    timer->setInterval(1000);
    timer->start();

    // 初始化地图
    for(int i = 0; i < 24; i++)
    {
        QVector<int> v(10, 0);
        m_map.append(v);

        QVector<QColor> c(10, qRgb(158, 173, 134));
        m_cc.append(c);
    }
    // 压入最后一行
    QVector<int> v(10, 1);
    m_map.append(v);

    QVector<QColor> c(10, qRgb(158, 173, 134));
    m_cc.append(c);

    // 下一个形状

    srand((unsigned)time(nullptr));
    m_nextType = qrand() % 7;

    // 背景音乐
    QSound::play("./wlxq.wav");
}


void Widget::paintEvent(QPaintEvent *)
{
    // 1、创建画家
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);             //抗锯齿

    // 2、绘制背景颜色
    QBrush brush(qRgb(158, 173, 134));                          //创建画刷
    painter.setBrush(brush);                                    //设置画刷,用来填充
    painter.drawRect(QRect(QPoint(0, 0), QPoint(m_w, m_h)));    //画矩形

    // 3、绘制已经固定的方块
    for(int i = 0; i < 25; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            if(m_map[i][j])
            {
                painter.setPen(QPen(qRgb(158, 173, 134)));
                painter.setBrush(QBrush(m_cc[i][j]));
                painter.drawRect(m_u * j, m_u * i, m_u, m_u);
            }
        }
    }

    // 4、绘制背景线条
    QPen pen(QColor(200, 200, 200));
    pen.setStyle(Qt::DotLine);                                  //设置画笔风格
    painter.setPen(pen);
    for(int i = 0; i < 20; i++)
        painter.drawLine(QPoint(0, m_u * i), QPoint(m_w, m_u * i));   //画直线
    for(int i = 0; i < 10; i++)
        painter.drawLine(QPoint(m_u * i, 0), QPoint(m_u * i, m_h));   //画直线

    // 5、绘制已下落方块
    if(m_cur)
        m_cur->Draw(painter);

    // 6、绘制下一个方块
    Block blk(15, 12, static_cast<BlockType>(m_nextType));
    blk.Draw(painter, true);
}


// 方向控制
void Widget::keyPressEvent(QKeyEvent *e)
{
    // 暂停
    if(e->key() == Qt::Key_P && e->modifiers() == Qt::ControlModifier)
    {
        qDebug() << "P";
        if(m_timer.isActive())
        {
            m_timer.stop();
            m_timer1.stop();
        }
        else
        {
            if(m_cur)
            {
                m_timer.setInterval(m_speed);
                m_timer.start();
                m_timer1.setInterval(1000);
                m_timer1.start();
            }
        }
    }

    if(!m_cur) return;

    // 整体左移
    if(e->key() == Qt::Key_A)
    {
        if(!Clash(m_cur->LeftState()))
        {
            m_cur->m_col--;
            update();
        }
    }

    // 整体右移
    if(e->key() == Qt::Key_D)
    {
        if(!Clash(m_cur->RightState()))
        {
            m_cur->m_col++;
            update();
        }
    }

    // 加速下降
    if(e->key() == Qt::Key_S)
    {
        if(!Clash(m_cur->DownState()))
        {
            m_cur->m_row++;
            update();
        }
        // 生成新的方块
        else
        {
            newBlock();
        }
    }

    // 阵型变换
    if(e->key() == Qt::Key_W)
    {
        if(!Clash(m_cur->RotateState()))
        {
            m_cur->Rotate();
            update();
        }
    }
}


void Widget::closeEvent(QCloseEvent *e)
{
    Q_UNUSED(e);

    // 写文件
    QFile file("score.txt");
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QString t = QString::number(m_total);
        file.write(t.toUtf8());
        file.close();
    }
}


void Widget::OnTimerOut()
{
    // 下落
    if(!Clash(m_cur->DownState()))
    {
        m_cur->m_row++;
        update();
    }
    // 生成新的方块
    else
    {
        newBlock();
    }

    update();
}


bool Widget::Clash(QVector<QPoint> vec)
{
    // 越界
    if(outRange(vec)) return true;

    // 冲突判断
    for(auto p : vec)
        if(m_map[p.x()][p.y()])
            return true;
    return false;
}


bool Widget::outRange(QVector<QPoint> vec)
{
    for(auto p : vec)
        if(p.x() >= 20 || p.y() < 0 || p.y() >= 10)
            return true;
    return false;
}


void Widget::newBlock()
{
    if(m_cur)
    {
        QSound::play("./hitbgm.wav");
        // 固定位置和颜色
        for(auto p : m_cur->State())
        {
            m_map[p.x()][p.y()] = 1;
            m_cc[p.x()][p.y()] = m_cur->m_color;
        }

        // 判断游戏是否结束
        QPoint pos = m_cur->getDown();
        if(pos.x() <= 3)
        {
            QSound::play("./fail.wav");
            m_timer.stop();
            m_timer1.stop();
            m_total = 0;
            m_min = 0;
            m_sec = 0;

            ui->btn_start->setEnabled(true);
            QMessageBox::critical(this, "失败", "游戏结束");
        }

        // 是否得分
        Score();

        delete m_cur;
    }

    // 产生新方块
    m_cur = new Block(0, 5, static_cast<BlockType>(m_nextType));

    // 随机下一个方块
    m_nextType = qrand() % 7;
}


void Widget::Score()
{
    QVector<int> vf;    // 消除的行数
    for(int row = 23; row >= 4; row--)
    {
        int num = 0;
        for(int col = 0; col < 10; col++)
        {
            if(m_map[row][col])
                num++;
        }

        if(num == 10)
            vf.append(row + vf.size());
    }

    // 未消除
    if(vf.size() == 0) return;

    // 消除，记分
    if(vf.size() == 1) m_total += 10;
    QSound::play("./texiao.wav");
    if(vf.size() == 2) m_total += 30;
    if(vf.size() == 3) m_total += 50;
    if(vf.size() == 4) m_total += 100;
    ui->lb_score->setText(QString("得分：%1").arg(m_total));

    // 消除行
    MoveMap(vf);
}


// 移除
void Widget::MoveMap(QVector<int> vf)
{
    for(int row : vf)
    {
        for(int r = row; r >= 4; r--)
        {
            m_map[r] = m_map[r - 1];
            m_cc[r] = m_cc[r - 1];
        }
        update();
    }
}


void Widget::on_btn_start_clicked()
{
    // 产生新方块
    newBlock();

    m_timer.setInterval(m_speed);
    m_timer.start();
    m_timer1.setInterval(1000);
    m_timer1.start();

    ui->btn_start->setEnabled(false);
}
