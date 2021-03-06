#ifndef MQEDITOR_H
#define MQEDITOR_H

#include <QPlainTextEdit>

#include "support/signalslot.hpp"       //  maiquel-toolkit-cpp


class LineNumberArea;
class LineCommandArea;
class QLabel;
class QHBoxLayout;
class QCompleter;
class QStringListModel;

/****************************************************************************

        MQEditor


 ****************************************************************************/

class MQEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit MQEditor(QWidget *parent = 0);
    virtual ~MQEditor() {}


    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int  lineNumberAreaWidth();

    //void line_command_AreaPaintEvent(QPaintEvent *event);
    int  line_command_height();


    mtk::Signal<    MQEditor*           /*editor*/,
                    const QString&      /*text_under_cursor*/,
                    QStringList&        /*return_completion_list*/>       signal_request_completion_list;

protected:
    void keyPressEvent ( QKeyEvent * event );
    void resizeEvent(QResizeEvent *event);

signals:
    
public slots:

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void updateLineNumberArea(const QRect &, int);
    void highlightCurrentBlock();
    void insertCompletion(const QString &completion_text);

protected:
    QWidget*            lineNumberArea;
    LineCommandArea*    line_command_area;

    QCompleter*         completer;
    QStringListModel*   model_completer;

    void insert_tab         (void);
    void increase_identation(void);
    void decrease_identation(void);
    void delete_back        (void);

    virtual  QString                textUnderCursor() const;
    virtual  void                   show_completer(const QString &text_under_cursor);
    virtual  void                   request_completion_list(const QString&      text_under_cursor, QStringList&   return_completion_list);


};


/****************************************************************************/




/****************************************************************************
  LineNumberArea
****************************************************************************/
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


/****************************************************************************
  LineCommandArea
****************************************************************************/
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



/****************************************************************************
  fill_text_completion
****************************************************************************/
/*
    writted with signal slot instead on class just as an example
  */
void  fill_text_completion(   MQEditor*             editor,
                              const QString&        text_under_cursor,
                              QStringList&          return_completion_list);



#endif // MQEDITOR_H
