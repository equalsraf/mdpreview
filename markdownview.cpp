#include "markdownview.h"
#include <QFile>

extern "C" {
#include <mkdio.h>
}


MarkdownView::MarkdownView( QString path, QWidget *parent)
:QWebView(parent), m_path(path)
{
	watcher = new QFileSystemWatcher(this);

	connect(watcher, SIGNAL(fileChanged(QString)),
			this, SLOT(loadFile()));
	//
	// This should not be necessary, but some editors
	// (a.k.a. Vim)  can circunvent watched files
	connect(watcher, SIGNAL(directoryChanged(QString)),
			this, SLOT(loadFile()));

	watcher->addPath(path);
	watcher->addPath( QFileInfo(path).path() );
	loadFile();
}

void MarkdownView::loadFile()
{

	QFile f(m_path);
	if ( !f.open(QIODevice::ReadOnly|QIODevice::Text) ){
		return;
	}

	QByteArray input = f.readAll();
	f.close();

	MMIOT *html = mkd_string( input.constData(), input.size(), 0 );
	if ( html == NULL ) {
		return;
	}

	mkd_compile(html, 0);
	char *t;
	int len = mkd_document(html, &t);
	setHtml(QString(t));
	mkd_cleanup(html);
	
	qDebug() << __func__;
}
