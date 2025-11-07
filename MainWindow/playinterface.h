#pragma once

#include <QWidget>
#include <memory>
#include <qurl.h>

QT_BEGIN_NAMESPACE
namespace Ui { class PlayInterfaceClass; };
QT_END_NAMESPACE

struct PlayInterfacePrivate;
class QMediaPlayer;
class TListWidget;

class PlayInterface : public QWidget
{
	Q_OBJECT

		Q_PROPERTY(bool fullScreen READ isFullScreen WRITE setFullScreen RESET resetFullScreen NOTIFY fullScreenChanged)
		Q_PROPERTY(bool smallScreen READ isSmallScreen WRITE setSmallScreen RESET resetSmallScreen NOTIFY smallScreenChanged)

private:
	std::unique_ptr<PlayInterfacePrivate> playInterfacePrivate;

	void initAction();
	void initialize();
	void initMediaPlayer();

	void initToolWidget();

	void createPlayQueueDialog();
	void createUrlResourceInfoDialog();

	QModelIndex indexFromUrl(const QUrl& source);

protected:
	bool eventFilter(QObject* watched, QEvent* event);

public:
	PlayInterface(QWidget *parent = nullptr);
	~PlayInterface();

	//	fullScreen属性
	bool isFullScreen();
	void setFullScreen(bool fullScreen);
	bool resetFullScreen();

	//	smallScreen属性
	bool isSmallScreen();
	void setSmallScreen(bool smallScreen);
	bool resetSmallScreen();

	const QSize& normalSize();
	void setNormalSize(const QSize& size);

	void setCurrentPlayingMedia(const QUrl& source);
	QUrl currentPlayingMedia();

	TListWidget* playQueue();

	int urlRole();

	void removeMedia(const QUrl& source);
	void appendMedia(const QUrl& source);
	void appendMedia(const QList<QUrl>& sources);
	void playMedia(const QUrl& source);

	void setPosition(long long position);
	long long position();

	QMediaPlayer* getMediaPlayer();

signals:
	//	fullScreen属性
	void fullScreenChanged(bool isFullScreen);
	//	smallScreen属性
	void smallScreenChanged(bool isSmallScreen);

	void normalSizeChanged(const QSize& size);

	//	play队列信号
	void playQueueChanged(int count);
	void playQueueEmpty();
	void playQueueNotEmpty();

	void succeedPlayed(const QUrl& source);
	void currentSourceChanged(QUrl previous, qint64 previousPosition, QUrl current);

	void playbackStateChanged(quint32 newState);

private slots:
	//	playQueue槽函数
	void do_hadPlay();
	void do_haveNotPlay();

	void do_entered(const QModelIndex& index);
	void do_pressed(const QModelIndex& index, Qt::MouseButton button);
	void do_activated(const QModelIndex& index, Qt::MouseButton button);
	void do_droped();
	void do_requestDeletion(const QUrl& url);

	//	mediaplayer槽函数
	void do_positionChanged(qint64 position);
	void do_durationChanged(qint64 duration);
	void do_sourceChanged(const QUrl& media);
	void do_playbackStateChanged(quint32 newState);

	//	audioOutput槽函数
	void do_mutedChanged(bool muted);
	void do_volumeChanged(int volume);

	//	尝试播放结果处理函数
	void do_streamExceptions();
	void do_mediaStatusChanged(quint32 status);

	//	窗口全屏
	/*
	*	处理全屏后事件
	*/
	void do_fullScreenChanged(bool fullScreen);
	void do_smallScreenChanged(bool smallScreen);

	void do_keepOpen_timeout();

	//	进度条
	void on_slider_sliderPressed();
	void on_slider_sliderMoved(int position);
	void on_slider_sliderReleased();

	//	中间的槽函数
	void on_toolButtonPrevious_triggered();
	void on_toolButtonBackward_triggered();
	void on_toolButtonStartOrPause_triggered();
	void on_toolButtonForward_triggered();
	void on_toolButtonNext_triggered();

	//	右边的槽函数
	void on_toolButtonLangAndSubtitles_triggered();
	void on_toolButtonVolume_triggered();
	void on_actVolume_hovered();
	void on_toolButtonFull_triggered();
	void on_toolButtonSmallWindow_triggered();
	void on_toolButtonSettings_triggered();

private:
	Ui::PlayInterfaceClass *ui;
};
