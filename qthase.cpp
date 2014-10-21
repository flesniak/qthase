#include "qthase.h"

#include <QTextEdit>
#include <webview.h>
#include <QSplitter>
#include <QToolBar>
#include <QAction>
#include <QFileDialog>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QWebHistory>

#include <QDebug>

#define VERSION "0.1"

QtHase::QtHase(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle(trUtf8("Qt Hase %1").arg(VERSION));

    p_editor = new QTextEdit();
    p_view = new WebView();

    QSplitter* splitter = new QSplitter(centralWidget());
    splitter->addWidget(p_editor);
    splitter->addWidget(p_view);
    setCentralWidget(splitter);

    splitter->setStretchFactor(0,3);
    splitter->setStretchFactor(1,1);

    QToolBar* toolbar = new QToolBar();
    addToolBar(toolbar);
    QAction* actionOpen = toolbar->addAction(QIcon::fromTheme("document-open"),trUtf8("Dokument öffnen"));
    QAction* actionSave = toolbar->addAction(QIcon::fromTheme("document-save"),trUtf8("Dokument speichern"));
    QAction* actionUndo = toolbar->addAction(QIcon::fromTheme("edit-undo"),trUtf8("Rückgängig"));
    QAction* actionRedo = toolbar->addAction(QIcon::fromTheme("edit-redo"),trUtf8("Wiederholen"));
    QAction* actionRefresh = toolbar->addAction(QIcon::fromTheme("view-refresh"),trUtf8("Aktualisieren"));
    QAction* actionBack = toolbar->addAction(QIcon::fromTheme("go-previous"),trUtf8("Zurück"));
    QAction* actionNext = toolbar->addAction(QIcon::fromTheme("go-next"),trUtf8("Forwärts"));

    connect(p_editor,SIGNAL(textChanged()),SLOT(updateView()));
    //connect(p_view,SIGNAL(linkClicked(QUrl)),SLOT(loadUrl(QUrl)));
    connect(actionOpen,SIGNAL(triggered()),SLOT(openDocument()));
    connect(actionSave,SIGNAL(triggered()),SLOT(saveDocument()));
    connect(actionUndo,SIGNAL(triggered()),p_editor,SLOT(undo()));
    connect(actionRedo,SIGNAL(triggered()),p_editor,SLOT(redo()));
    connect(actionRefresh,SIGNAL(triggered()),SLOT(updateView()));
    connect(actionBack,SIGNAL(triggered()),SLOT(goBack()));
    connect(actionNext,SIGNAL(triggered()),SLOT(goNext()));

    updateView();
}

QtHase::~QtHase() {

}

void QtHase::updateView() {
    p_view->setHtml(p_editor->toPlainText());
}

void QtHase::loadUrl(const QUrl &url) {
    p_view->load(url);
}

void QtHase::openDocument() {
    QString fileName = QFileDialog::getOpenFileName(this, trUtf8("Datei öffnen"), QDir::homePath(), trUtf8("HTML-Dateien (*.html)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QFile::ReadOnly | QFile::Text))
            p_editor->setPlainText(file.readAll());
        else
            QMessageBox::critical(this,trUtf8("Fehler"),trUtf8("Fehler beim Öffnen der Datei"));
    }
}

void QtHase::saveDocument() {
    QString fileName = QFileDialog::getSaveFileName(this, trUtf8("Datei speichern"), QDir::homePath(), trUtf8("HTML-Dateien (*.html)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QFile::WriteOnly | QFile::Text)) {
            QByteArray data = p_editor->toPlainText().toUtf8();
            if( file.write(data) != data.size() )
                QMessageBox::critical(this,trUtf8("Fehler"),trUtf8("Fehler beim Speichern der Datei"));
            file.close();
        } else
            QMessageBox::critical(this,trUtf8("Fehler"),trUtf8("Fehler beim Speichern der Datei"));
    }
}

void QtHase::goBack() {
    if( p_view->history()->canGoBack() )
        p_view->back();
    else
        updateView();
}

void QtHase::goNext() {
    if( p_view->history()->canGoForward() )
        p_view->forward();
}
