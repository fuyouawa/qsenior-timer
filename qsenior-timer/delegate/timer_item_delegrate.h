#pragma once
#include <qstyleditemdelegate.h>
#include <qpushbutton.h>
#include <qapplication.h>
#include <qevent.h>
#include "global/config.h"

class TimerItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    TimerItemDelegate(QObject* parent);
    ~TimerItemDelegate();
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index) override;

private:
    struct {
        int row;
        int column;
        int btn_idx;
    } oper_btn_pressed_info_;

signals:
    void operBtnClicked(int row, TimerItemOperIndex oper_idx);
};