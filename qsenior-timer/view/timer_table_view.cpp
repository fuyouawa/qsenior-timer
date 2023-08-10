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
}

TimerTableView::~TimerTableView()
{
}