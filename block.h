#ifndef BLOCK_H
#define BLOCK_H

#include <QVector>
#include <QColor>
#include <QPainter>
#include <QDebug>

// 方块类型
enum BlockType{
    O,
    S,
    Z,
    L,
    J,
    T,
    I
};

// 方块类
class Block
{
public:
    Block(int row, int col, BlockType type){
        m_row = row;
        m_col = col;
        m_type = type;
        m_color = qRgb(qrand() % 255, qrand() % 255, qrand() % 255);

        if(type == BlockType::O) m_v = {{0, 0, 0},{1, 1, 0},{1, 1, 0}};
        if(type == BlockType::S) m_v = {{0, 0, 0},{0, 1, 1},{1, 1, 0}};
        if(type == BlockType::Z) m_v = {{0, 0, 0},{1, 1, 0},{0, 1, 1}};
        if(type == BlockType::L) m_v = {{1, 0, 0},{1, 0, 0},{1, 1, 0}};
        if(type == BlockType::J) m_v = {{0, 1, 0},{0, 1, 0},{1, 1, 0}};
        if(type == BlockType::T) m_v = {{1, 1, 1},{0, 1, 0},{0, 0, 0}};
        if(type == BlockType::I) m_v = {{1, 0, 0, 0},{1, 0, 0, 0},{1, 0, 0, 0},{1, 0, 0, 0}};
    }

    // 绘制函数
    void Draw(QPainter& painter, bool cc = false){
        // 提示显示
        if(cc)
        {
            painter.setPen(qRgb(0, 153, 230));
            painter.setBrush(QBrush(qRgb(158, 173, 134)));
        }
        else
        {
            painter.setPen(qRgb(158, 173, 134));
            painter.setBrush(QBrush(m_color));
        }

        for(int i = 0; i < m_v.size(); i++)
        {
            for(int j = 0; j < m_v.at(i).size(); j++)
            {
                if(m_v[i][j])
                {
                    painter.drawRect(m_col * m_u + m_u * j, m_row * m_u + m_u * (i - 4), m_u, m_u);
                }
            }
        }
    }

    // 获取最底部方块的行数
    QPoint getDown(){
        for(int i = m_v.size() - 1; i >= 0; i--)
            for(int j = 0; j < m_v.at(i).size(); j++)
                if(m_v[i][j])
                    return QPoint(i + m_row, j + m_col);
    }

    // 获取最顶部方块的行数
    QPoint getUp(){
        for(int i = 0; i < m_v.size(); i--)
            for(int j = 0; j < m_v.at(i).size(); j++)
                if(m_v[i][j])
                    return QPoint(i + m_row, j + m_col);
    }

    // 当前各方块位置
    QVector<QPoint> State(){
        QVector<QPoint> vec;
        for(int i = 0; i < m_v.size(); i++)
            for(int j = 0; j < m_v.at(i).size(); j++)
                if(m_v[i][j])
                    vec.append(QPoint(i + m_row, j + m_col));
        return vec;
    }

    // 左移后位置
    QVector<QPoint> LeftState(){
        QVector<QPoint> vec;
        for(auto p : State())
            vec.append(QPoint(p.x(), p.y() - 1));
        return vec;
    }

    // 右移后位置
    QVector<QPoint> RightState(){
        QVector<QPoint> vec;
        for(auto p : State())
            vec.append(QPoint(p.x(), p.y() + 1));
        return vec;
    }

    // 下移后位置
    QVector<QPoint> DownState(){
        QVector<QPoint> vec;
        for(auto p : State())
            vec.append(QPoint(p.x() + 1, p.y()));
        return vec;
    }

    // 旋转
    void Rotate(){
        int n = m_v.size();
        for (int layer = 0; layer < n / 2; layer++)
        {
            int first = layer;
            int last = n - 1 - layer;
            for (int i = first; i < last; i++)
            {
                int offset = i - first;
                int top = m_v[first][i];
                // 左边移到上边
                m_v[first][i] = m_v[last - offset][first];
                // 底边移到左边
                m_v[last - offset][first] = m_v[last][last - offset];
                // 右边移到底边
                m_v[last][last - offset] = m_v[i][last];
                // 上边移到右边
                m_v[i][last] = top;
            }
        }
    }


    // 变换后状态
    QVector<QPoint> RotateState(){
        QVector<QVector<int>> tmp = m_v;

        // 旋转
        int n = m_v.size();
        for (int layer = 0; layer < n / 2; layer++)
        {
            int first = layer;
            int last = n - 1 - layer;
            for (int i = first; i < last; i++)
            {
                int offset = i - first;
                int top = tmp[first][i];
                // 左边移到上边
                tmp[first][i] = tmp[last - offset][first];
                // 底边移到左边
                tmp[last - offset][first] = tmp[last][last - offset];
                // 右边移到底边
                tmp[last][last - offset] = tmp[i][last];
                // 上边移到右边
                tmp[i][last] = top;
            }
        }

        // 旋转后状态
        QVector<QPoint> vec;
        for(int i = 0; i < tmp.size(); i++)
            for(int j = 0; j < tmp.at(i).size(); j++)
                if(tmp[i][j])
                    vec.append(QPoint(i + m_row, j + m_col));
        return vec;
    }



public:
    QColor m_color;     // 颜色
    BlockType m_type;   // 类型
    QVector<QVector<int>> m_v;
    int m_row;          // 在地图中的行数
    int m_col;          // 在地图中的列数
    int m_u = 30;       // 方块大小
};

#endif // BLOCK_H
