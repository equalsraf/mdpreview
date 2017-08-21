#!/usr/bin/env python3
"""
A markdown live preview
"""

from PySide.QtGui import QApplication
from PySide.QtWebKit import QWebView
from PySide.QtCore import QFileSystemWatcher, QFileInfo
import sys
import markdown

class MarkdownView(QWebView):

    def __init__(self, path, parent=None, encoding='utf8'):
        QWebView.__init__(self, parent)
        self.path = path
        self.encoding = encoding
        self.__watcher = QFileSystemWatcher(self)

        self.__watcher.fileChanged.connect(self.loadFile)
        self.__watcher.directoryChanged.connect(self.loadFile)

        self.__watcher.addPath(self.path)
        self.__watcher.addPath(QFileInfo(self.path).path())

        self.setWindowTitle(self.path)

        self.loadFile()

    def loadFile(self):
        if not QFileInfo(self.path).exists():
            return

        inp = open(self.path).read()
        self.setHtml(markdown.markdown(inp, extensions=['meta', 'codehilite']))

app = QApplication(sys.argv)

if len(app.arguments()) != 2:
    print('Usage: mdpreview <path>')
    sys.exit(-1)

win = MarkdownView(app.arguments()[1])

win.show()
sys.exit(app.exec_())

