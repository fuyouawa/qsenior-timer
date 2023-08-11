#include "timer_table_header_view.h"

TimerTableHeaderView::TimerTableHeaderView(Qt::Orientation orientation, QWidget* parent) :
    QHeaderView(orientation, parent),
    filter_btn_pressed_log_idx_(-1),
    cut_btn_pressed_log_idx_(-1),
    filter_pixmap_(":/pictures/filter.png"),
    filter_pressed_pixmap_(":/pictures/filter_pressed.png"),
    cut_pixmap_(":/pictures/cut.png"),
    cut_pressed_pixmap_(":/pictures/cut_pressed.png")
{
}

TimerTableHeaderView::~TimerTableHeaderView()
{
}

void TimerTableHeaderView::paintSection(QPainter* painter, const QRect& rect, int logical_index) const
{
    painter->save();
    QHeaderView::paintSection(painter, rect, logical_index);
    painter->restore();

    if (logical_index != kColumnOperations) {
        PaintFilterIcon(painter, rect, logical_index);
    }

    switch (logical_index)
    {
    case kColumnTimeCounter:
        PaintCutIcon(painter, rect, logical_index);
        break;
    default:
        break;
    }
}


void TimerTableHeaderView::mousePressEvent(QMouseEvent* event)
{
    int log_idx = logicalIndexAt(event->pos());
    if (filter_btns_rect_.contains(log_idx) &&
        filter_btns_rect_[log_idx].contains(event->pos()))
    {
        filter_btn_pressed_log_idx_ = log_idx;
    }
    else if (cut_btns_rect_.contains(log_idx) &&
        cut_btns_rect_[log_idx].contains(event->pos()))
    {
        cut_btn_pressed_log_idx_ = log_idx;
    }
    updateSection(log_idx);
    QHeaderView::mousePressEvent(event);
}

void TimerTableHeaderView::mouseReleaseEvent(QMouseEvent* event)
{
    int log_idx = logicalIndexAt(event->pos());
    if (log_idx == filter_btn_pressed_log_idx_) {
        emit filterBtnClicked(log_idx);
    }
    else if (log_idx == cut_btn_pressed_log_idx_) {
        emit cutBtnClicked(log_idx);
    }
    filter_btn_pressed_log_idx_ = -1;
    cut_btn_pressed_log_idx_ = -1;
    updateSection(log_idx);
    QHeaderView::mouseReleaseEvent(event);
}

void TimerTableHeaderView::PaintFilterIcon(QPainter* painter, const QRect& rect, int logical_index) const
{
    QIcon icon = logical_index == filter_btn_pressed_log_idx_ ? filter_pressed_pixmap_ : filter_pixmap_;
    auto btn_rect = QRect(rect.right() - 22, rect.y() + 1, 20, 20);
    icon.paint(painter, btn_rect, Qt::AlignCenter);
    filter_btns_rect_[logical_index] = btn_rect;
}

void TimerTableHeaderView::PaintCutIcon(QPainter* painter, const QRect& rect, int logical_index) const
{
    QIcon icon = logical_index == cut_btn_pressed_log_idx_ ? cut_pressed_pixmap_ : cut_pixmap_;
    auto btn_rect = QRect(rect.right() - 44, rect.y() + 1, 20, 20);
    icon.paint(painter, btn_rect, Qt::AlignCenter);
    cut_btns_rect_[logical_index] = btn_rect;
}
