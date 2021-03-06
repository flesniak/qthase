#include "qthase.h"

#include "text.h"
#include "webview.h"
#include "inspector.h"

#include <QAction>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QSplitter>
#include <QToolBar>
#include <QWebHistory>

#include <QDebug>

#define VERSION "0.2"
#define TABSTOP 4

QtHase::QtHase(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle(trUtf8("Qt Hase %1").arg(VERSION));

    p_editor = new QPlainTextEdit();
    QFont font("Monospace", 9);
    QFontMetrics fontMet(font);
    p_editor->setFont(font);
    p_editor->setTabStopWidth(fontMet.width(QString(TABSTOP,'x')));
    p_editor->setTabChangesFocus(false);

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
    p_actionSave = toolbar->addAction(QIcon::fromTheme("document-save"),trUtf8("Dokument speichern"));
    QAction* actionSaveAs = toolbar->addAction(QIcon::fromTheme("document-save-as"),trUtf8("Neue Datei speichern"));
    QAction* actionUndo = toolbar->addAction(QIcon::fromTheme("edit-undo"),trUtf8("Rückgängig"));
    QAction* actionRedo = toolbar->addAction(QIcon::fromTheme("edit-redo"),trUtf8("Wiederholen"));
    QAction* actionRefresh = toolbar->addAction(QIcon::fromTheme("view-refresh"),trUtf8("Aktualisieren"));
    QAction* actionBack = toolbar->addAction(QIcon::fromTheme("go-previous"),trUtf8("Zurück"));
    QAction* actionNext = toolbar->addAction(QIcon::fromTheme("go-next"),trUtf8("Forwärts"));
    toolbar->addSeparator();
    QAction* actionShowInspector = toolbar->addAction(QIcon::fromTheme("edit-find"),trUtf8("Inspektor anzeigen"));
    actionShowInspector->setCheckable(true);
    p_actionSave->setEnabled(false);

    connect(p_editor,SIGNAL(textChanged()),SLOT(updateView()));
    //connect(p_view,SIGNAL(linkClicked(QUrl)),SLOT(loadUrl(QUrl)));
    connect(actionOpen,SIGNAL(triggered()),SLOT(openDocument()));
    connect(p_actionSave,SIGNAL(triggered()),SLOT(saveDocument()));
    connect(actionSaveAs,SIGNAL(triggered()),SLOT(saveDocumentAs()));
    connect(actionUndo,SIGNAL(triggered()),p_editor,SLOT(undo()));
    connect(actionRedo,SIGNAL(triggered()),p_editor,SLOT(redo()));
    connect(actionRefresh,SIGNAL(triggered()),SLOT(updateView()));
    connect(actionBack,SIGNAL(triggered()),SLOT(goBack()));
    connect(actionNext,SIGNAL(triggered()),SLOT(goNext()));
    connect(actionShowInspector,SIGNAL(triggered(bool)),SLOT(toggleInspector(bool)));

    p_editor->setPlainText(text::startupText);

    updateView();

    QWebSettings::globalSettings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
    p_inspector = new inspector();
    p_inspector->setPage(p_view->page());
    connect(p_inspector,SIGNAL(visibilityChanged(bool)),actionShowInspector,SLOT(setChecked(bool)));
}

QtHase::~QtHase() {
}

void QtHase::closeEvent(QCloseEvent *event) {
    p_inspector->close();
    QMainWindow::closeEvent(event);
}

void QtHase::updateView() {
    p_view->setHtml(p_editor->toPlainText());
    p_actionSave->setEnabled(true);
}

void QtHase::loadUrl(const QUrl &url) {
    p_view->load(url);
}

void QtHase::openDocument() {
    QString fileName = QFileDialog::getOpenFileName(this, trUtf8("Datei öffnen"), QDir::homePath(), trUtf8("HTML-Dateien (*.html)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if( file.open(QFile::ReadOnly | QFile::Text) ) {
            p_editor->setPlainText(file.readAll());
            p_fileName = fileName;
            p_actionSave->setEnabled(false); //load successful
        } else
            QMessageBox::critical(this,trUtf8("Fehler"),trUtf8("Fehler beim Öffnen der Datei"));
    }
}

void QtHase::saveDocument() {
    if( p_fileName.length() ) {
        QFile file(p_fileName);
        if( file.open(QFile::WriteOnly | QFile::Text) ) {
            QByteArray data = p_editor->toPlainText().toUtf8();
            if( file.write(data) != data.size() ) {
                QMessageBox::critical(this,trUtf8("Fehler"),trUtf8("Fehler beim Speichern der Datei"));
                p_fileName.clear();
            }
            file.close();
            p_actionSave->setEnabled(false); //save successful
        } else {
            QMessageBox::critical(this,trUtf8("Fehler"),trUtf8("Fehler beim Speichern der Datei"));
            p_fileName.clear();
        }
    } else
        saveDocumentAs(); //if no filename is set yet, ask for one.
}

void QtHase::saveDocumentAs() {
    QString fileName = QFileDialog::getSaveFileName(this, trUtf8("Datei speichern"), QDir::homePath(), trUtf8("HTML-Dateien (*.html)"));
    if( !fileName.isEmpty() ) {
        p_fileName = fileName;
        saveDocument();
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

void QtHase::toggleInspector(bool on) {
    p_inspector->setVisible(on);
}
