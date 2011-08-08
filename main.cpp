#include <QtGui>

#include "markdownview.h"

int main(int ac, char **av)
{
	QApplication app(ac, av);
	if (app.arguments().size() != 2) {
		fprintf(stderr, "Usage: mdpreview <FILE>\n");
		return -1;
	}

	MarkdownView v(app.arguments().at(1));
	v.show();

	return app.exec();
}

