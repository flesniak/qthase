#ifndef QTHASE_H
#define QTHASE_H

#include <QMainWindow>
#include <QUrl>

class QTextEdit;
class WebView;

class QtHase : public QMainWindow
{
    Q_OBJECT

public:
    QtHase(QWidget *parent = 0);
    ~QtHase();

private:
    QTextEdit* p_editor;
    WebView* p_view;

private slots:
    void updateView();
    void loadUrl(const QUrl& url);
    void openDocument();
    void saveDocument();
    void goNext();
    void goBack();
};

#endif // QTHASE_H
