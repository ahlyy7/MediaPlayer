#include "ui_tlistwidget.h"
#include "tlistwidget.h"
#include <qevent.h>

void TListWidget::mousePressEvent(QMouseEvent* event)
{
	currentButton = event->button();
	QListWidget::mousePressEvent(event);
}

void TListWidget::mouseReleaseEvent(QMouseEvent* event)
{
	currentButton = event->button();
	QListWidget::mouseReleaseEvent(event);
}

void TListWidget::mouseDoubleClickEvent(QMouseEvent* event)
{
	currentButton = event->button();
	QListWidget::mouseDoubleClickEvent(event);
}

void TListWidget::dropEvent(QDropEvent* event)
{
	QListWidget::dropEvent(event);
	emit droped();
}

TListWidget::TListWidget(QWidget *parent)
	: QListWidget(parent)
	, ui(new Ui::TListWidgetClass())
{
	ui->setupUi(this);

	connect(this, &QListWidget::itemPressed, this, &TListWidget::do_itemPressed);
	connect(this, &QListWidget::itemClicked, this, &TListWidget::do_itemClicked);
	connect(this, &QListWidget::itemDoubleClicked, this, &TListWidget::do_itemDoubleClicked);
	connect(this, &QListWidget::itemActivated, this, &TListWidget::do_itemActivated);

	connect(this, &QListWidget::pressed, this, &TListWidget::do_pressed);
	connect(this, &QListWidget::clicked, this, &TListWidget::do_clicked);
	connect(this, &QListWidget::doubleClicked, this, &TListWidget::do_doubleClicked);
	connect(this, &QListWidget::activated, this, &TListWidget::do_activated);
}

TListWidget::~TListWidget()
{
	delete ui;
}

void TListWidget::do_itemPressed(QListWidgetItem* item)
{
	emit itemPressed(item, currentButton);
}

void TListWidget::do_itemClicked(QListWidgetItem* item)
{
	emit itemClicked(item, currentButton);
}

void TListWidget::do_itemDoubleClicked(QListWidgetItem* item)
{
	emit itemDoubleClicked(item, currentButton);
}

void TListWidget::do_itemActivated(QListWidgetItem* item)
{
	emit itemActivated(item, currentButton);
}

void TListWidget::do_pressed(const QModelIndex& index)
{
	emit pressed(index, currentButton);
}

void TListWidget::do_clicked(const QModelIndex& index)
{
	emit clicked(index, currentButton);
}

void TListWidget::do_doubleClicked(const QModelIndex& index)
{
	emit doubleClicked(index, currentButton);
}

void TListWidget::do_activated(const QModelIndex& index)
{
	emit activated(index, currentButton);
}
