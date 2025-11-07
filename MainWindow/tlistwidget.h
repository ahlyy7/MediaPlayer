#pragma once

#include <QListWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class TListWidgetClass; };
QT_END_NAMESPACE

class TListWidget : public QListWidget
{
	Q_OBJECT

private:
	Qt::MouseButton currentButton;

protected:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void mouseDoubleClickEvent(QMouseEvent* event) override;

	void dropEvent(QDropEvent* event) override;

public:
	TListWidget(QWidget *parent = nullptr);
	~TListWidget();

signals:
	void itemPressed(QListWidgetItem* item, Qt::MouseButton button);
	void itemClicked(QListWidgetItem* item, Qt::MouseButton button);
	void itemDoubleClicked(QListWidgetItem* item, Qt::MouseButton button);
	void itemActivated(QListWidgetItem* item, Qt::MouseButton button);

	void pressed(const QModelIndex& index, Qt::MouseButton button);
	void clicked(const QModelIndex& index, Qt::MouseButton button);
	void doubleClicked(const QModelIndex& index, Qt::MouseButton button);

	void activated(const QModelIndex& index, Qt::MouseButton button);

	void droped();

private slots:
	void do_itemPressed(QListWidgetItem* item);
	void do_itemClicked(QListWidgetItem* item);
	void do_itemDoubleClicked(QListWidgetItem* item);
	void do_itemActivated(QListWidgetItem* item);

	void do_pressed(const QModelIndex& index);
	void do_clicked(const QModelIndex& index);
	void do_doubleClicked(const QModelIndex& index);

	void do_activated(const QModelIndex& index);

private:
	Ui::TListWidgetClass *ui;
};
