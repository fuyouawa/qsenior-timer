#include "timer_table_view.h"

TimerTableView::TimerTableView(QWidget* parent) :
    QTableView(parent),
    act_edit_(new QAction("编辑", this)),
    act_control_(new QAction("控制", this)),
    act_hidden_(new QAction("隐藏", this)),
    act_view_details_(new QAction("查看详情", this)),
    oper_btn_clicked_row_(-1)
{
    model_ = new TimerTableModel(this);

    auto item_delegate = new TimerItemDelegate(this);
    setItemDelegate(item_delegate);
    setContextMenuPolicy(Qt::CustomContextMenu);
    setModel(model_);

    hori_header_view_ = new TimerTableHeaderView(this);
    setHorizontalHeader(hori_header_view_);

    verticalHeader()->setDefaultSectionSize(10);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);

    setDragEnabled(false);

    for (size_t i = 0; i < model_->columnCount(); i++)
    {
        switch (i)
        {
        case kColumnOperations:
            hori_header_view_->setSectionResizeMode(i, QHeaderView::Fixed);
            setColumnWidth(i, 20);
            break;
        default:
            hori_header_view_->setSectionResizeMode(i, QHeaderView::Stretch);
            break;
        }
    }

    connect(item_delegate, &TimerItemDelegate::operBtnClicked, this, &TimerTableView::OnOperBtnClicked);
    connect(act_edit_, &QAction::triggered, this, &TimerTableView::OnEditTimer);
    connect(act_control_, &QAction::triggered, this, &TimerTableView::OnControlTimer);
    connect(act_hidden_, &QAction::triggered, this, &TimerTableView::OnHideTimer);
    connect(act_view_details_, &QAction::triggered, this, &TimerTableView::OnViewTimerDetails);
}

TimerTableView::~TimerTableView()
{
}

TimerTableModel* TimerTableView::Model() const
{
    return model_;
}

void TimerTableView::OnViewTimerDetails()
{
    if (oper_btn_clicked_row_ == -1) return;
    TimerInfoDlg dlg{ this, *model_->GetTimerItemStoreData(oper_btn_clicked_row_), model_->GetTimerName(oper_btn_clicked_row_) };
    dlg.exec();
}

void TimerTableView::OnHideTimer()
{
}

void TimerTableView::OnEditTimer()
{
    if (oper_btn_clicked_row_ == -1) return;
    QString origi_name = model_->GetTimerName(oper_btn_clicked_row_);
    QString origi_tags = model_->GetTags(oper_btn_clicked_row_);

    EditTimerDlg dlg{ this ,origi_name ,origi_tags };
    if (dlg.exec() == QDialog::Accepted) {
        auto [name, tags] = dlg.GetEdit();
        if (origi_tags != tags) {
            model_->item(oper_btn_clicked_row_, kColumnTags)->setText(tags);
            if (!TimerDb::Instance->ChangeTimerTags(origi_name, tags)) {
                ShowErrorMsg(TimerDb::Instance->LastError(), 1, this);
            }
        }
        if (origi_name != name) {
            model_->item(oper_btn_clicked_row_, kColumnTimerName)->setText(name);
            if (!TimerDb::Instance->ChangeTimerName(origi_name, name)) {
                ShowErrorMsg(TimerDb::Instance->LastError(), 1, this);
            }
        }
    }
}

void TimerTableView::OnControlTimer()
{
    if (oper_btn_clicked_row_ == -1) return;
    auto data = model_->GetTimerItemStoreData(oper_btn_clicked_row_);
    if (data->status == kStatusPaused)
        data->status = kStatusStanding;
    else
        data->status = kStatusPaused;
}

void TimerTableView::OnOperBtnClicked(int row)
{
    oper_btn_clicked_row_ = row;

    if (model_->GetTimerItemStoreData(row)->status == kStatusPaused)
        act_control_->setText("继续");
    else
        act_control_->setText("暂停");

    QMenu menu{ this };
    menu.addAction(act_view_details_);
    menu.addAction(act_control_);
    menu.addAction(act_hidden_);
    menu.addAction(act_edit_);
    menu.exec(QCursor::pos());
    oper_btn_clicked_row_ = -1;
}