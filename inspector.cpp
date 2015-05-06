#include "inspector.h"

#include <QCloseEvent>
#include <QHideEvent>
#include <QShowEvent>
#include <QDebug>

inspector::inspector(QWidget* parent) : QWebInspector(parent) {
}

void inspector::closeEvent(QCloseEvent* event) {
    QWebInspector::closeEvent(event);
    if( event->isAccepted() )
      emit visibilityChanged(false);
}

void inspector::hideEvent(QHideEvent* event) {
    QWebInspector::hideEvent(event);
    if( event->isAccepted() )
      emit visibilityChanged(false);
}

void inspector::showEvent(QShowEvent* event) {
    QWebInspector::showEvent(event);
    if( event->isAccepted() )
      emit visibilityChanged(true);
}

