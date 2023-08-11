#include "timer_table_view.h"

TimerTableView::TimerTableView(QWidget* parent) : QTableView(parent)
{
    model_ = new TimerTableModel(this);

    auto item_delegate = new TimerItemDelegate(this);
    setItemDelegate(item_delegate);
    setContextMenuPolicy(Qt::CustomContextMenu);
    setModel(model_);
    setHorizontalHeader(new TimerTableHeaderView(Qt::Horizontal, this));
    horizontalHeader()->setStretchLastSection(true);
    verticalHeader()->setDefaultSectionSize(10);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);

    setColumnWidth(0, 200);
    setColumnWidth(1, 150);
    setColumnWidth(2, 100);
    setColumnWidth(3, 100);

    connect(item_delegate, &TimerItemDelegate::operBtnClicked, this, &TimerTableView::OnOperBtnClicked);
}

TimerTableView::~TimerTableView()
{
}

void TimerTableView::OnOperBtnClicked(int row, TimerItemOperIndex oper_idx)
{
    switch (oper_idx)
    {
    case kOperIndexTimer:
        break;
    case kOperIndexShowMessage:
        break;
    case kOperIndexHidden:
        break;
    }
}