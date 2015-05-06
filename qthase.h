#ifndef QTHASE_H
#define QTHASE_H

#include <QMainWindow>
#include <QUrl>
#include <QString>

class QPlainTextEdit;
class WebView;
class QAction;
class QWebInspector;
class QCloseEvent;

class QtHase : public QMainWindow
{
    Q_OBJECT

public:
    QtHase(QWidget *parent = 0);
    ~QtHase();

protected:
    virtual void closeEvent(QCloseEvent* event);

private:
    QPlainTextEdit* p_editor;
    WebView* p_view;
    QString p_fileName;
    QAction* p_actionSave;
    QWebInspector* p_inspector;

private slots:
    void updateView();
    void loadUrl(const QUrl& url);
    void openDocument();
    void saveDocument();
    void saveDocumentAs();
    void goNext();
    void goBack();
    void toggleInspector(bool on);
};

#endif // QTHASE_H
