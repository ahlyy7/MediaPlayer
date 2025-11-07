#pragma once

#include <QtWidgets/QMainWindow>
#include <qurl.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindowClass; };
QT_END_NAMESPACE

class PlayInterface;
struct MainWindowPrivate;

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    std::unique_ptr<MainWindowPrivate> mainWindowPrivate;
    friend struct MainWindowPrivate;

    void initialize();

    bool eventFilter(QObject* watched, QEvent* event);

    void closeEvent(QCloseEvent* event);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actOpenDir_triggered();
    void on_actOpenFile_triggered();
    void on_actOpenURL_triggered();

    void do_smallScreenChanged(bool smallScreen);
    void do_currentSourceChanged(QUrl previous, qint64 previousPosition, QUrl current);

    void on_homePageButton_clicked();
    void on_playQueueButton_clicked();

    void on_actBack_triggered();

    void on_stackedWidget_currentChanged(int current);

    void on_toolButtonLeftPage_clicked();
    void on_toolButtonRightPage_clicked();
    void on_spinBoxCurrentPage_valueChanged(int value);

    void do_finished();

    void do_requestPlay(const QUrl& url);
    void do_requestDelete(const QUrl& url);
    void do_requestChoose(const QUrl& url);

    void do_playbackStateChanged(quint32 newState);

private:
    Ui::MainWindowClass *ui;
};
