#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MediaViewClass; };
QT_END_NAMESPACE

struct MediaViewPrivate;
class MediaViewItem;

class MediaView : public QWidget
{
	Q_OBJECT

private:
	std::unique_ptr<MediaViewPrivate> mediaViewPrivate;

	void resizeEvent(QResizeEvent* event);
	void paintEvent(QPaintEvent* event);

	void reLayout();

public:
	MediaView(QWidget *parent = nullptr);
	~MediaView();

	void setItemSize(QSize size);
	QSize itemSize();

	void setLayoutHorizontalSpacing(quint32 spacing);
	quint32 layoutHorizontalSpacing();
	void setLayoutVerticalSpacing(quint32 spacing);
	quint32 layoutVerticalSpacing();

	void setLayoutHorizontalMargin(quint32 margin);
	quint32 layotuHorizontalMargin();
	void setLayoutVerticalMargin(quint32 margin);
	quint32 layoutVerticalMargin();



	void addItems(const QList<MediaViewItem*>& itemList);
	void addItem(MediaViewItem* item);

	void removeItem(MediaViewItem* item);
	void removeAllItem();

signals:
	void requestPlay(const QUrl& url);
	void requestDelete(const QUrl& url);
	void requestChoose(const QUrl& url);

private slots:
	void do_requestPlay();
	void do_requestDelete();
	void do_requestChoose();

private:
	Ui::MediaViewClass *ui;
};
