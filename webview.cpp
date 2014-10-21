#include "webview.h"

#include <QGridLayout>
#include <QDialog>
#include <QDebug>

WebView::WebView(QWidget *parent) : QWebView(parent)
{
}

QWebView* WebView::createWindow(QWebPage::WebWindowType type) {
    Q_UNUSED(type);
    QDialog* widget = new QDialog(this);
    WebView* view = new WebView(widget);
    QGridLayout* layout = new QGridLayout(widget);
    layout->addWidget(view);
    subwindows.append(qMakePair(widget,view));
    widget->show();
    return view;
}
