#ifndef MQEDITOR_H
#define MQEDITOR_H

#include <QPlainTextEdit>

#include "support/signalslot.hpp"       //  maiquel-toolkit-cpp
#include "support/list.hpp"
#include "support/map.hpp"


class LineNumberArea;
class LineCommandArea;
class QLabel;
class QHBoxLayout;
class QCompleter;
class QStringListModel;
class QVBoxLayout;
class QSplitter;
class Command_manager;
class QLineEdit;



/****************************************************************************

        MQEditor


 ****************************************************************************/


class  MQEditor  :  public  QFrame
{
    Q_OBJECT
public:
    explicit MQEditor(QWidget *parent = 0);
    virtual ~MQEditor() {};

private:
    QWidget*            frame_ex;
    LineCommandArea*    line_command_area;
    QVBoxLayout*        main_layout;
};





/****************************************************************************
        MQEditorSingle
 ****************************************************************************/
class MQEditorSingle : public QPlainTextEdit  , public  mtk::SignalReceptor
{
    Q_OBJECT
public:
    explicit MQEditorSingle(QWidget *parent = 0);
    virtual ~MQEditorSingle();


    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int  lineNumberAreaWidth();


    //  OUTPUT
    mtk::Signal<    MQEditorSingle*  >                                    signal_request_command;
    mtk::Signal<    MQEditorSingle*           /*editor*/,
                    const QString&      /*text_under_cursor*/,
                    QStringList&        /*return_completion_list*/>       signal_request_completion_list;

    mtk::Signal<    MQEditorSingle*  >                                    signal_cursor_position_change;



protected:
    void keyPressEvent ( QKeyEvent * event );
    void keyReleaseEvent(QKeyEvent *event);
    void resizeEvent(QResizeEvent *event);

signals:
    
public slots:
    void  on_cursor_update_position();

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void updateLineNumberArea(const QRect &, int);
    void highlightCurrentBlock();
    void insertCompletion(const QString &completion_text);

protected:
    QWidget*                            lineNumberArea;

    QCompleter*                         completer;
    QStringListModel*                   model_completer;
    mtk::CountPtr<Command_manager>      command_manager;


    void insert_tab         (void);
    void increase_identation(void);
    void decrease_identation(void);
    void delete_back        (void);


    virtual  QString                textUnderCursor() const;
    virtual  void                   show_completer(const QString &text_under_cursor);
    virtual  void                   request_completion_list(const QString&      text_under_cursor, QStringList&   return_completion_list);

    virtual  void                   update_ViewportMargins(void);
    virtual  void                   __resize              (void);

private:
    QString                 last_key_pressed;

    void command_help           (const std::string& cmd, const std::string& params, mtk::list<std::string>& response_lines );
    void command_version        (const std::string& cmd, const std::string& params, mtk::list<std::string>& response_lines );
    void command_modifications  (const std::string& cmd, const std::string& params, mtk::list<std::string>& response_lines );
    void command_stats          (const std::string& cmd, const std::string& params, mtk::list<std::string>& response_lines );
    void command_config         (const std::string& cmd, const std::string& params, mtk::list<std::string>& response_lines );
};


/****************************************************************************/




/****************************************************************************
  LineNumberArea
****************************************************************************/
class LineNumberArea : public QWidget
{
public:
    LineNumberArea(MQEditorSingle *editor) : QWidget(editor) {
        codeEditor = editor;
    }

    QSize sizeHint() const {
        return QSize(0, 0);
    }

protected:
    void paintEvent(QPaintEvent *event) {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    MQEditorSingle *codeEditor;
};


/****************************************************************************
  LineCommandArea
****************************************************************************/
class LineCommandArea : public QWidget,  public  mtk::SignalReceptor
{
    Q_OBJECT
public:
    LineCommandArea(MQEditor *editor);



    //  input
    void on_cursor_update_position(MQEditorSingle* editor);
    void on_request_command_editor(MQEditorSingle* editor);


public slots:

protected:
    virtual void keyPressEvent(QKeyEvent *);

private:
    MQEditorSingle* codeEditor_requesting_command;

    QHBoxLayout*    layout;
    QLabel*         txt_cursor_position;
    QLineEdit*      command_line_edit;
};



/****************************************************************************
  fill_text_completion
****************************************************************************/
/*
    writted with signal slot instead on class just as an example
  */
void  fill_text_completion(   MQEditorSingle*             editor,
                              const QString&        text_under_cursor,
                              QStringList&          return_completion_list);



/****************************************************************************
  Command_manager
****************************************************************************/
class Command_manager
{
public:

    void command_help           (const std::string& cmd, const std::string& params, mtk::list<std::string>& response_lines );

    //  REGISTER COMMANDS
    virtual mtk::CountPtr<mtk::Signal<const std::string& /*cmd*/, const std::string& /*params*/, mtk::list<std::string>& /*response lines*/> >
                                        register_command(   const std::string& name,
                                                            const std::string& description);
private:
    class command_info;
    mtk::map<std::string, mtk::CountPtr<command_info> >             map_commands;
};




#endif // MQEDITOR_H
