#ifndef MQEDITOR_H
#define MQEDITOR_H

#include <QPlainTextEdit>


class LineNumberArea;



class MQEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit MQEditor(QWidget *parent = 0);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

protected:
    void keyPressEvent ( QKeyEvent * event );
    void resizeEvent(QResizeEvent *event);

signals:
    
public slots:

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void updateLineNumberArea(const QRect &, int);
    void highlightCurrentLine();

private:
    void insert_tab(void);
    QWidget *lineNumberArea;

};



class LineNumberArea : public QWidget
{
public:
    LineNumberArea(MQEditor *editor) : QWidget(editor) {
        codeEditor = editor;
    }

    QSize sizeHint() const {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    MQEditor *codeEditor;
};


#endif // MQEDITOR_H
