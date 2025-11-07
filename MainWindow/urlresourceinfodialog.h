#pragma once

#include <QDialog>
#include <qurl.h>

QT_BEGIN_NAMESPACE
namespace Ui { class UrlResourceInfoDialogClass; };
QT_END_NAMESPACE

class QMediaPlayer;

class UrlResourceInfoDialog : public QDialog
{
	Q_OBJECT

private:
	QUrl urlResource;
	QWidget* obscured;
	QMediaPlayer* mediaPlayer;

protected:
	bool eventFilter(QObject* watched, QEvent* event);

public:
	UrlResourceInfoDialog(QWidget *parent = nullptr);
	UrlResourceInfoDialog(const QUrl& url, QWidget* parent = nullptr);
	~UrlResourceInfoDialog();

	void setUrl(const QUrl& url);
	const QUrl& url() const;

signals:
	void requestDeletion(const QUrl& url);

private slots:
	void on_actDelete_triggered();
	void on_openButton_clicked();

	void do_metaDataChanged();

private:
	Ui::UrlResourceInfoDialogClass *ui;
};
