#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <QVector>
#include <QMessageBox>
#include <QDateTime>
#include <QSound>
#include "block.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void Init();
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent* e);
    void closeEvent (QCloseEvent* e);

    // 定时器事件函数
    void OnTimerOut();

    // 冲突检查
    bool Clash(QVector<QPoint> vec);

    // 越界检查
    bool outRange(QVector<QPoint> vec);

    // 生成新方块
    void newBlock();

    // 得分
    void Score();

    // 地图元素下移
    void MoveMap(QVector<int>);


private slots:
    void on_btn_start_clicked();

private:
    Ui::Widget *ui;
    QTimer m_timer;
    QTimer m_timer1;        // 游戏计时
    int m_w = 300;          // 宽度
    int m_h = 600;          // 高度
    int m_u = 30;           // 单个尺寸
    Block *m_cur = nullptr; // 当前下落方块
    int m_speed = 350;      // 原始速度
    int m_total = 0;        // 总得分
    int m_nextType = 0;     // 下一个形状

    int m_min = 0;
    int m_sec = 0;

    QVector<QVector<int>> m_map;
    QVector<QVector<QColor>> m_cc;  // 地图色块
};
#endif // WIDGET_H
