#pragma once
#include <qheaderview.h>
#include <qicon.h>
#include <qpainter.h>
#include <qevent.h>
#include <QMap>
#include "global/config.h"

class TimerTableHeaderView : public QHeaderView
{
	Q_OBJECT

public:
	TimerTableHeaderView(Qt::Orientation orientation, QWidget* parent = nullptr);
	~TimerTableHeaderView();

	void paintSection(QPainter* painter, const QRect& rect, int logicalIndex) const override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;

private:
	void PaintFilterIcon(QPainter* painter, const QRect& rect, int logical_index) const;
	void PaintCutIcon(QPainter* painter, const QRect& rect, int logical_index) const;

	mutable QMap<int, QRect> filter_btns_rect_;
	mutable QMap<int, QRect> cut_btns_rect_;
	QPixmap filter_pixmap_;
	QPixmap filter_pressed_pixmap_;
	QPixmap cut_pixmap_;
	QPixmap cut_pressed_pixmap_;
	int filter_btn_pressed_log_idx_;
	int cut_btn_pressed_log_idx_;

signals:
	void filterBtnClicked(int logical_index);
	void cutBtnClicked(int logical_index);
};
