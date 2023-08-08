#include "timer_item_delegrate.h"

TimerItemDelegate::TimerItemDelegate(QObject* parent) :
    QStyledItemDelegate(parent),
    oper_btn_pressed_info_({ -1, -1, -1 })
{
}

TimerItemDelegate::~TimerItemDelegate()
{
}

void TimerItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QStyledItemDelegate::paint(painter, option, index);
    if (index.column() == kTimerItemColomnOperation)
    {
        QStyleOptionButton button;
        int btn_width = option.rect.width() / kTimerItemOperationsText.size();
        for (int i = 0; i < kTimerItemOperationsText.size(); ++i)
        {
            QRect btn_rect = QRect(option.rect.left() + i * btn_width, option.rect.top(), btn_width, option.rect.height());
            button.rect = btn_rect;
            button.text = kTimerItemOperationsText[i];
            button.state = QStyle::State_Enabled;

            if (oper_btn_pressed_info_.column == index.column() && oper_btn_pressed_info_.row == index.row() && oper_btn_pressed_info_.btn_idx == i)
                button.state |= QStyle::State_Sunken;

            QApplication::style()->drawControl(QStyle::CE_PushButton, &button, painter);
        }
    }
}

bool TimerItemDelegate::editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index)
{
    if (index.column() == kTimerItemColomnOperation)
    {
        QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);
        int btn_width = option.rect.width() / kTimerItemOperationsText.size();
        int btn_idx = (mouse_event->pos().x() - option.rect.left()) / btn_width;
        switch (event->type())
        {
        case QEvent::MouseButtonPress:
            oper_btn_pressed_info_ = { index.row(), index.column(), btn_idx };
            return true;
        case QEvent::MouseButtonRelease:
            if (btn_idx == oper_btn_pressed_info_.btn_idx) {
                emit operBtnClicked(index, (TimerItemOperatorIndex)btn_idx);
            }
            oper_btn_pressed_info_ = { -1, -1, -1 };
            return true;
        }
    }
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}