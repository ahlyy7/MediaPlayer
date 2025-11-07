#include "ui_mediaview.h"
#include "mediaview.h"
#include <qevent.h>
#include <qgridlayout.h>
#include <mediaviewitem.h>

struct MediaViewPrivate
{
	QSize itemSize;

	QGridLayout* gridLayout = nullptr;

	quint32 horizontalCount;

	bool needReload = false;

	QList<MediaViewItem*> itemList;

	int minHorizontalMargin = 0;
	int minVerticalMargin = 0;
};

void MediaView::resizeEvent(QResizeEvent* event)
{
	reLayout();

	auto width = this->width();

	//	contral = count * itemSize + (count - 1) * spacing
	//	margin = (width - contral) / 2;

	auto contral = mediaViewPrivate->horizontalCount * mediaViewPrivate->itemSize.width() + (mediaViewPrivate->horizontalCount - 1) * mediaViewPrivate->gridLayout->horizontalSpacing();
	auto horizontalMargin = (width - contral) / 2;

	mediaViewPrivate->gridLayout->setContentsMargins(
		//	left
		horizontalMargin,

		//	top
		mediaViewPrivate->minVerticalMargin,

		//	right
		horizontalMargin,

		//	bottom
		mediaViewPrivate->minVerticalMargin
	);

	event->accept();
	QWidget::resizeEvent(event);
}

void MediaView::paintEvent(QPaintEvent* event)
{
	if (mediaViewPrivate->needReload)
	{
		auto [itemWidth, itemHeight] = mediaViewPrivate->itemSize;

		quint32 row = 0U, column = 0U;

		for (auto& item : mediaViewPrivate->itemList)
		{
			item->setSizeHint(mediaViewPrivate->itemSize);
			item->setTitleHeight(itemHeight - itemWidth);

			mediaViewPrivate->gridLayout->addWidget(item, row, column);

			if (++column == mediaViewPrivate->horizontalCount)
			{
				++row;
				column = 0U;
			}
		}

		mediaViewPrivate->needReload = false;
	}

	event->accept();
	QWidget::paintEvent(event);
}

void MediaView::reLayout()
{
	//	count * itemWidth + (count - 1) * specing + 2 * margin <= width()

	auto width = this->width();
	auto specing = layoutHorizontalSpacing();
	auto margin = layotuHorizontalMargin();
	auto itemWidth = mediaViewPrivate->itemSize.width();

	//	width + specing - 2 * margin
	//	----------------------------
	//		itemWidth + specing

	mediaViewPrivate->horizontalCount = (width + specing - 2U * margin) / (itemWidth + specing);
	mediaViewPrivate->horizontalCount = std::max(mediaViewPrivate->horizontalCount, 1U);



	QSize minimumSize(
		mediaViewPrivate->itemSize.width() + 2 * layotuHorizontalMargin(),
		mediaViewPrivate->itemSize.height() + 2 * layoutVerticalMargin()
	);
	setMinimumSize(minimumSize);



	auto count = mediaViewPrivate->itemList.size();
	auto verticalCount = (count + mediaViewPrivate->horizontalCount - 1) / mediaViewPrivate->horizontalCount;

	auto itemHeight = mediaViewPrivate->itemSize.height();
	specing = layoutVerticalSpacing();
	margin = layoutVerticalMargin();

	setFixedHeight(itemHeight * verticalCount + (specing - 1) * count + margin * 2);

	mediaViewPrivate->needReload = true;
}

MediaView::MediaView(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::MediaViewClass())
	, mediaViewPrivate(new MediaViewPrivate())
{
	ui->setupUi(this);

	auto& layout = mediaViewPrivate->gridLayout;
	layout = new QGridLayout(this);
	layout->setSpacing(0);
	layout->unsetContentsMargins();

	setItemSize({ 10, 10 });
	setLayoutHorizontalMargin(0U);
	setLayoutVerticalMargin(0U);
	setLayoutHorizontalSpacing(0U);
	setLayoutVerticalSpacing(0U);
}

MediaView::~MediaView()
{
	delete ui;

	removeAllItem();
}

void MediaView::setItemSize(QSize size)
{
	if (mediaViewPrivate->itemSize == size)
		return;

	mediaViewPrivate->itemSize = size;

	reLayout();
}

QSize MediaView::itemSize()
{
	return mediaViewPrivate->itemSize;
}

void MediaView::setLayoutHorizontalSpacing(quint32 spacing)
{
	if (layoutHorizontalSpacing() == spacing)
		return;

	mediaViewPrivate->gridLayout->setHorizontalSpacing(spacing);

	reLayout();
}

quint32 MediaView::layoutHorizontalSpacing()
{
	return mediaViewPrivate->gridLayout->horizontalSpacing();
}

void MediaView::setLayoutVerticalSpacing(quint32 spacing)
{
	if (layoutVerticalSpacing() == spacing)
		return;

	mediaViewPrivate->gridLayout->setVerticalSpacing(spacing);

	reLayout();
}

quint32 MediaView::layoutVerticalSpacing()
{
	return mediaViewPrivate->gridLayout->verticalSpacing();
}

void MediaView::setLayoutHorizontalMargin(quint32 margin)
{
	mediaViewPrivate->minHorizontalMargin = margin;

	reLayout();
}

quint32 MediaView::layotuHorizontalMargin()
{
	return mediaViewPrivate->minHorizontalMargin;
}

void MediaView::setLayoutVerticalMargin(quint32 margin)
{
	mediaViewPrivate->minVerticalMargin = margin;

	reLayout();
}

quint32 MediaView::layoutVerticalMargin()
{
	return mediaViewPrivate->minVerticalMargin;
}

void MediaView::addItems(const QList<MediaViewItem*>& itemList)
{
	for (auto& item : itemList)
	{
		item->setParent(this);
		connect(item, &MediaViewItem::requestPlay, this, &MediaView::do_requestPlay);
		connect(item, &MediaViewItem::requestDelete, this, &MediaView::do_requestDelete);
		connect(item, &MediaViewItem::requestChoose, this, &MediaView::do_requestChoose);
	}
	mediaViewPrivate->itemList.append(itemList);

	reLayout();
}

void MediaView::addItem(MediaViewItem* item)
{
	item->setParent(this);
	connect(item, &MediaViewItem::requestPlay, this, &MediaView::do_requestPlay);
	connect(item, &MediaViewItem::requestDelete, this, &MediaView::do_requestDelete);
	connect(item, &MediaViewItem::requestChoose, this, &MediaView::do_requestChoose);
	mediaViewPrivate->itemList.append(item);

	reLayout();
}

void MediaView::removeItem(MediaViewItem* item)
{
	auto& itemList = mediaViewPrivate->itemList;
	auto result = std::find(itemList.cbegin(), itemList.cend(), item);

	itemList.erase(result);
}

void MediaView::removeAllItem()
{
	for (auto item : mediaViewPrivate->itemList)
		delete item;

	mediaViewPrivate->itemList.clear();
}

void MediaView::do_requestPlay()
{
	emit requestPlay(static_cast<MediaViewItem*>(sender())->url());
}

void MediaView::do_requestDelete()
{
	emit requestDelete(static_cast<MediaViewItem*>(sender())->url());
}

void MediaView::do_requestChoose()
{
	emit requestChoose(static_cast<MediaViewItem*>(sender())->url());
}
