#ifndef MQEDITOR_H
#define MQEDITOR_H

#include <QPlainTextEdit>


class LineNumberArea;
class LineCommandArea;
class QLabel;
class QHBoxLayout;


/****************************************************************************

        MQEditor


 ****************************************************************************/

class MQEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit MQEditor(QWidget *parent = 0);


    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int  lineNumberAreaWidth();

    //void line_command_AreaPaintEvent(QPaintEvent *event);
    int  line_command_height();

protected:
    void keyPressEvent ( QKeyEvent * event );
    void resizeEvent(QResizeEvent *event);

signals:
    
public slots:

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void updateLineNumberArea(const QRect &, int);
    void highlightCurrentBlock();

private:
    void insert_tab         (void);
    void increase_identation(void);
    void decrease_identation(void);
    void delete_back        (void);

    QWidget*            lineNumberArea;
    LineCommandArea*    line_command_area;
};





class LineNumberArea : public QWidget
{
public:
    LineNumberArea(MQEditor *editor) : QWidget(editor) {
        codeEditor = editor;
    }

    QSize sizeHint() const {
        return QSize(0, codeEditor->line_command_height());
    }

protected:
    void paintEvent(QPaintEvent *event) {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    MQEditor *codeEditor;
};


class LineCommandArea : public QWidget
{
    Q_OBJECT
public:
    LineCommandArea(MQEditor *editor);


public slots:
    void  on_cursor_update_position();

protected:

private:
    MQEditor *codeEditor;

    QHBoxLayout*    layout;
    QLabel*         txt_cursor_position;
};

#endif // MQEDITOR_H
