#include "timer_table_header_view.h"

TimerTableHeaderView::TimerTableHeaderView(Qt::Orientation orientation, QWidget* parent) :
    QHeaderView(orientation, parent),
    filter_btn_pressed_idx_(-1),
    filter_btns_rect_(kTimerTableHorizontalHeaderLabels.size())
{
    filter_btn_pixmap = QPixmap(":/pictures/filter.png");
    filter_btn_pressed_pixmap = QPixmap(":/pictures/filter_pressed.png");
}

TimerTableHeaderView::~TimerTableHeaderView()
{
}

void TimerTableHeaderView::paintSection(QPainter* painter, const QRect& rect, int logicalIndex) const
{
    painter->save();
    QHeaderView::paintSection(painter, rect, logicalIndex);
    painter->restore();

    if (logicalIndex != kTimerItemColomnOperation)
    {
        QIcon icon = logicalIndex == filter_btn_pressed_idx_ ? filter_btn_pressed_pixmap : filter_btn_pixmap;
        auto btn_rect = QRect(rect.right() - 22, rect.y() + 1, 20, 20);
        icon.paint(painter, btn_rect, Qt::AlignCenter);
        filter_btns_rect_[logicalIndex] = btn_rect;
    }
}


void TimerTableHeaderView::mousePressEvent(QMouseEvent* event)
{
    int index = logicalIndexAt(event->pos());
    if (index < filter_btns_rect_.size() && filter_btns_rect_[index].contains(event->pos())) {
        filter_btn_pressed_idx_ = index;
        updateSection(index);
        return;
    }
    QHeaderView::mousePressEvent(event);
}

void TimerTableHeaderView::mouseReleaseEvent(QMouseEvent* event)
{
    if (filter_btn_pressed_idx_ != -1) {
        int index = logicalIndexAt(event->pos());
        if (index == filter_btn_pressed_idx_) {
            emit filterBtnClicked(index);
        }
        filter_btn_pressed_idx_ = -1;
        updateSection(index);
    }
    QHeaderView::mouseReleaseEvent(event);
}