#ifndef __MDPREVIEW__
#define __MDPREVIEW__

#include <QWebView>
#include <QtGui>
#include <QFileSystemWatcher>

class MarkdownView: public QWebView
{
	Q_OBJECT
public:
	MarkdownView(QString path, QWidget *parent=0);

protected slots:
	void loadFile();

private:
	QString m_path;
	QFileSystemWatcher *watcher;

};

#endif
