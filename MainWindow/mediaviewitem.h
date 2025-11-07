#pragma once

#include <QWidget>
#include <qurl.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MediaViewItemClass; };
QT_END_NAMESPACE

class QMediaPlayer;

class MediaViewItem : public QWidget
{
	Q_OBJECT

private:
	QUrl urlResource;
	QMediaPlayer* mediaPlayer;

	QPixmap pixmap;

protected:
	bool eventFilter(QObject* watched, QEvent* event);

public:
	MediaViewItem();
	MediaViewItem(const QUrl& url);
	~MediaViewItem();

	void setUrl(const QUrl& url);
	const QUrl& url();

	void setSizeHint(QSize size);
	void setTitleHeight(int height);

signals:
	void requestPlay();
	void requestDelete();
	void requestChoose();

private slots:
	void do_metaDataChanged();
	void do_customContextMenuRequested(const QPoint& pos);

	void on_actPlay_triggered();
	void on_actDelete_triggered();
	void on_actAttribute_triggered();
	void on_actChoose_triggered();

private:
	Ui::MediaViewItemClass *ui;
};
