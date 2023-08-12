#include "timer_item_delegrate.h"

TimerItemDelegate::TimerItemDelegate(QObject* parent) :
    QStyledItemDelegate(parent),
    oper_btn_pressed_row_(-1),
    oper_btn_pixmap_(":/pictures/anymore.png")
{
}

TimerItemDelegate::~TimerItemDelegate()
{
}

void TimerItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QStyledItemDelegate::paint(painter, option, index);
    if (index.column() == kColumnOperations)
    {
        int btn_width = option.rect.height();
        QSize size = { btn_width, btn_width };

        QStyleOptionButton button;
        button.rect = QRect(option.rect.left(), option.rect.top(), btn_width, btn_width);
        button.state = QStyle::State_Enabled;
        button.icon = oper_btn_pixmap_.scaled(size, Qt::KeepAspectRatio);
        button.iconSize = size;

        if (oper_btn_pressed_row_ == index.row())
            button.state |= QStyle::State_Sunken;

        QApplication::style()->drawControl(QStyle::CE_PushButton, &button, painter);
    }
}

bool TimerItemDelegate::editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index)
{
    if (index.column() == kColumnOperations)
    {
        QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);
        int btn_width = option.rect.width();
        switch (event->type())
        {
        case QEvent::MouseButtonPress:
            oper_btn_pressed_row_ = index.row();
            return true;
        case QEvent::MouseButtonRelease:
            if (index.row() == oper_btn_pressed_row_) {
                emit operBtnClicked(oper_btn_pressed_row_);
            }
            oper_btn_pressed_row_ = -1;
            return true;
        }
    }
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}