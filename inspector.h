#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <QWebInspector>

class inspector : public QWebInspector {
    Q_OBJECT
public:
    inspector(QWidget* parent = 0);

protected:
    virtual void closeEvent(QCloseEvent* event);
    virtual void hideEvent(QHideEvent* event);
    virtual void showEvent(QShowEvent* event);

signals:
    void visibilityChanged(bool visible);
};

#endif //INSPECTOR_H
