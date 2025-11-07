#pragma once

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class PlayQueueDialogClass; };
QT_END_NAMESPACE

class TListWidget;

class PlayQueueDialog : public QDialog
{
	Q_OBJECT

private:
	TListWidget* currentListWidget;

public:
	PlayQueueDialog(QWidget *parent = nullptr);
	PlayQueueDialog(TListWidget* listWidget, QWidget* parent = nullptr);
	~PlayQueueDialog();

	void setTitle(const QString& title);

	void setListWidget(TListWidget* listWidget);
	TListWidget* tackListWidget(TListWidget* listWidget);
	TListWidget* listWidget();

private:
	Ui::PlayQueueDialogClass *ui;
};
