#pragma once
#include <qheaderview.h>
#include <qicon.h>
#include <qpainter.h>
#include <qevent.h>
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
	mutable QVector<QRect> filter_btns_rect_;
	QPixmap filter_btn_pixmap;
	QPixmap filter_btn_pressed_pixmap;
	size_t filter_btn_pressed_idx_;

signals:
	void filterBtnClicked(int btn_idx);
};
