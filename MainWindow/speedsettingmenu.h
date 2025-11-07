#pragma once

#include <QMenu>
#include "ui_speedsettingmenu.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SpeedSettingMenuClass; };
QT_END_NAMESPACE

class SpeedSettingMenu : public QMenu
{
	Q_OBJECT

		Q_PROPERTY(QAction* currentAction READ currentAction WRITE setCurrentAction NOTIFY currentActionChanged)

private:
	QAction* m_currentAction;
	QString labelString;

public:
	SpeedSettingMenu(QWidget *parent = nullptr);
	~SpeedSettingMenu();

	QAction* currentAction();
	void setCurrentAction(QAction* action);

	const QString& getLabelString();
	void setLabelString(const QString& labelString);

	QAction* getActionFromRate(double number);

signals:
	void currentActionChanged(QAction* currentAction);

private:
	Ui::SpeedSettingMenuClass *ui;
};
