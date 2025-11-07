#include "ui_playqueuedialog.h"
#include "playqueuedialog.h"
#include "tlistwidget.h"
#include <qboxlayout.h>

PlayQueueDialog::PlayQueueDialog(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::PlayQueueDialogClass())
	, currentListWidget(nullptr)
{
	ui->setupUi(this);
}

PlayQueueDialog::PlayQueueDialog(TListWidget* listWidget, QWidget* parent)
	: PlayQueueDialog(parent)
{
	setListWidget(listWidget);
}

PlayQueueDialog::~PlayQueueDialog()
{
	delete ui;
}

void PlayQueueDialog::setTitle(const QString& title)
{
	ui->labelTitle->setText(title);
}

void PlayQueueDialog::setListWidget(TListWidget* listWidget)
{
	for (auto& children : ui->centralWidget->children())
		children->deleteLater();

	currentListWidget = listWidget;

	if (!listWidget)
		return;

	listWidget->setParent(ui->centralWidget);
	QHBoxLayout* hLayout = new QHBoxLayout(ui->centralWidget);
	ui->centralWidget->setLayout(hLayout);

	hLayout->addWidget(listWidget);
}

TListWidget* PlayQueueDialog::tackListWidget(TListWidget* listWidget)
{
	if (currentListWidget)
		currentListWidget->setParent(nullptr);
	auto result = currentListWidget;

	setListWidget(listWidget);

	return result;
}

TListWidget* PlayQueueDialog::listWidget()
{
	return currentListWidget;
}
