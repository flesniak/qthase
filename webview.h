#ifndef WEBVIEW_H
#define WEBVIEW_H

#include <QWebView>
#include <QList>
#include <QPair>

class QDialog;

class WebView : public QWebView
{
    Q_OBJECT
public:
    explicit WebView(QWidget *parent = 0);

protected:
    virtual QWebView* createWindow(QWebPage::WebWindowType type);

private:
    QList< QPair<QDialog*,WebView*> > subwindows;
};

#endif // WEBVIEW_H
