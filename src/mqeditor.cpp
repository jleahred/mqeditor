/*

  · remove spaces at end of each block
    when writting and when saving

  · mark selected

  · find, replace, mark

  · command line with control key

  · configuration with yaml

  · borrar tabuladores a la izquierda, pendiente de mtk::s_trim. In remove tab

  */

#include "mqeditor.h"

#include <iostream>
#include <QTextBlock>
#include <QPainter>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCompleter>
#include <QApplication>
#include <QStringListModel>
#include <QScrollBar>
#include <QStringListModel>
#include <QSplitter>
#include <QLineEdit>

#include "support/mtk_string.h"





MQEditor::MQEditor(QWidget *parent)
    : QFrame(parent),
      line_command_area(new LineCommandArea(this)),
      main_layout(new QVBoxLayout(this))
{
    main_layout->setMargin(0);
    main_layout->setSpacing(0);


    QSplitter*  splitter_h=new QSplitter(this);
    splitter_h->setOrientation(Qt::Horizontal);


    QSplitter*  splitter_c1=new QSplitter(this);
    splitter_c1->setOrientation(Qt::Vertical);
    splitter_h->addWidget(splitter_c1);

    QSplitter*  splitter_c2=new QSplitter(this);
    splitter_c2->setOrientation(Qt::Vertical);
    splitter_h->addWidget(splitter_c2);

    {
        MQEditorSingle* ex = new MQEditorSingle(this);
        ex->signal_cursor_position_change.connect(line_command_area, &LineCommandArea::on_cursor_update_position);
        ex->signal_request_command.connect(line_command_area, &LineCommandArea::on_request_command_editor);
        splitter_c1->addWidget(ex);
        ex->setPlainText("1");
        ex->setPlainText(QString::number(splitter_c1->count()));
    }
    {
        MQEditorSingle* ex = new MQEditorSingle(this);
        ex->signal_cursor_position_change.connect(line_command_area, &LineCommandArea::on_cursor_update_position);
        splitter_c2->addWidget(ex);
        ex->setPlainText("2");
        ex->setPlainText(QString::number(splitter_c2->count()));
    }
    /*
    {
        MQEditorSingle* ex = new MQEditorSingle(this);

        splitter_v1->addWidget(ex);
        ex->setPlainText("3");
    }
    */
    {
        MQEditorSingle* ex = new MQEditorSingle(this);
        ex->signal_cursor_position_change.connect(line_command_area, &LineCommandArea::on_cursor_update_position);
        splitter_c2->addWidget(ex);
        ex->setPlainText("4");
        ex->setPlainText(QString::number(splitter_c2->count()));
    }
    {
        MQEditorSingle* ex = new MQEditorSingle(this);
        ex->signal_cursor_position_change.connect(line_command_area, &LineCommandArea::on_cursor_update_position);
        splitter_c2->addWidget(ex);
        ex->setPlainText("5");
        ex->setPlainText(QString::number(splitter_c2->count()));
    }

    main_layout->addWidget(splitter_h);
    main_layout->addWidget(line_command_area);
    this->setLayout(main_layout);
}






MQEditorSingle::MQEditorSingle(QWidget *parent) :
    QPlainTextEdit(parent), model_completer(new QStringListModel), command_manager(new Command_manager)
{
    lineNumberArea = new LineNumberArea(this);

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentBlock()));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(on_cursor_update_position()));

    updateLineNumberAreaWidth(0);
    highlightCurrentBlock();

    //  completer
    completer = new QCompleter(this);
    //completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setWrapAround(false);
    completer->setWidget(this);
    completer->setCompletionMode(QCompleter::PopupCompletion);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setModel(model_completer);
    signal_request_completion_list.connect(fill_text_completion);
    QObject::connect(completer, SIGNAL(activated(QString)),
                     this, SLOT(insertCompletion(QString)));


    MTK_CONNECT_THIS(*command_manager->register_command("help",                 ""),                                                command_help);
    MTK_CONNECT_THIS(*command_manager->register_command("ver",                  ""),                                                command_version);
    MTK_CONNECT_THIS(*command_manager->register_command("modifs",               "brief information about modifications"),           command_modifications);
    MTK_CONNECT_THIS(*command_manager->register_command("stats",                "some stats"),                                      command_stats);
    MTK_CONNECT_THIS(*command_manager->register_command("config",               "config information"),                              command_config);

}

MQEditorSingle::~MQEditorSingle()
{
}

int MQEditorSingle::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;

    return space;
}


void MQEditorSingle::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    update_ViewportMargins();
}


void MQEditorSingle::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}


void MQEditorSingle::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    __resize();
}


void MQEditorSingle::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();
    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(QColor(100,100,100));
            //QFont font ("monospace", 10);
            //painter.setFont(font);
            QFont font = this->font();
            font.setPointSize(font.pointSize()-2);
            painter.setFont(font);
            painter.drawText(0, top, lineNumberArea->width()-2, fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}




void MQEditorSingle::highlightCurrentBlock()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QColor lineColor = QColor(Qt::blue).lighter(185);
        QTextEdit::ExtraSelection selection;
        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);



        QTextCursor cursor = this->textCursor();
        int last_selection_line = cursor.blockNumber();
        selection.cursor = cursor;
        selection.cursor.movePosition(QTextCursor::EndOfBlock);
        extraSelections.append(selection);
        selection.cursor.movePosition(QTextCursor::StartOfLine);
        selection.cursor.movePosition(QTextCursor::PreviousCharacter);
        while(last_selection_line == selection.cursor.blockNumber())
        {
            if(selection.cursor.atStart())
                break;
            extraSelections.append(selection);
            selection.cursor.movePosition(QTextCursor::StartOfLine);
            selection.cursor.movePosition(QTextCursor::PreviousCharacter);
        }
    }

    setExtraSelections(extraSelections);
}


void MQEditorSingle::insert_tab(void)
{
    QTextCursor  cursor = this->textCursor();
    int num_spaces2add = 4 - cursor.positionInBlock()%4;
    if(num_spaces2add==0)  num_spaces2add = 3;
    QString spaces2add (num_spaces2add, ' ');
    cursor.insertText(spaces2add);
}

void MQEditorSingle::increase_identation(void)
{
    QTextCursor cursor = this->textCursor();
    int first_block_selected = 0;
    int last_block_selected = 0;
    int min_pos=0;
    int extra_line=0;
    if(cursor.position() > cursor.anchor())
    {
        last_block_selected = cursor.blockNumber();
        if(cursor.atBlockStart()==false)
            extra_line = 1;
        cursor.setPosition(cursor.anchor());
        first_block_selected = cursor.blockNumber();
        min_pos = cursor.position();
    }
    else
    {
        first_block_selected = cursor.blockNumber();
        min_pos = cursor.position();
        cursor.setPosition(cursor.anchor());
        last_block_selected = cursor.blockNumber();
        if(cursor.atBlockStart()==false)
            extra_line = 1;
    }
    if(first_block_selected != last_block_selected)
    {
        cursor.setPosition(min_pos);
        for(int i=first_block_selected; i!=last_block_selected+extra_line; ++i)
        {
            cursor.movePosition(QTextCursor::StartOfBlock);
            cursor.insertText("    ");
            cursor.movePosition(QTextCursor::NextBlock);
            if(cursor.atEnd())
                break;
        }
    }
}

void MQEditorSingle::decrease_identation(void)
{
    QTextCursor cursor = this->textCursor();
    int first_block_selected = 0;
    int last_block_selected = 0;
    int min_pos=0;
    int extra_line=0;
    if(cursor.position() > cursor.anchor())
    {
        last_block_selected = cursor.blockNumber();
        if(cursor.atBlockStart()==false)
            extra_line = 1;
        cursor.setPosition(cursor.anchor());
        first_block_selected = cursor.blockNumber();
        min_pos = cursor.position();
    }
    else
    {
        first_block_selected = cursor.blockNumber();
        min_pos = cursor.position();
        cursor.setPosition(cursor.anchor());
        last_block_selected = cursor.blockNumber();
        if(cursor.atBlockStart()==false)
            extra_line = 1;
    }
    if(first_block_selected != last_block_selected)
    {
        cursor.setPosition(min_pos);
        for(int i=first_block_selected; i!=last_block_selected+extra_line; ++i)
        {
            cursor.movePosition(QTextCursor::StartOfBlock);
            //  try to remove 4 spaces at the beginning
            for(int j=0; j<4; ++j)
            {
                cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor);
                if(cursor.selectedText() == " ")
                    cursor.removeSelectedText();
                else
                    break;
            }
            cursor.movePosition(QTextCursor::NextBlock);
            if(cursor.atEnd())
                break;
        }
    }
}

void MQEditorSingle::delete_back        (void)
{
    //  if spaces till previous tab point, remove all of them

    if(this->textCursor().selectedText()!="")
        this->textCursor().removeSelectedText();
    else
    {
        QTextCursor  cursor = this->textCursor();
        int dist_prev_tab = cursor.positionInBlock() % 4;
        if(dist_prev_tab == 0)  dist_prev_tab = 4;
        cursor.setPosition(cursor.position() - dist_prev_tab +1, QTextCursor::KeepAnchor);
        if(mtk::s_trim(cursor.selectedText().toStdString(), ' ') == "")
            cursor.removeSelectedText();
    }
}


QString MQEditorSingle::textUnderCursor() const
{
    QTextCursor tc = textCursor();
    tc.select(QTextCursor::WordUnderCursor);
    return tc.selectedText();
}


void MQEditorSingle::keyReleaseEvent(QKeyEvent *event)
{
    if(last_key_pressed == QString("Ctrl+"))
    {
        signal_request_command(this);
        last_key_pressed = "";
    }
    else
        QPlainTextEdit::keyReleaseEvent(event);
}

void MQEditorSingle::keyPressEvent ( QKeyEvent * event )
{
    if(event->text() == "")
        last_key_pressed = QKeySequence(event->modifiers()).toString();
    else
        last_key_pressed = QKeySequence(event->modifiers() | event->key() ).toString();
    if (completer->popup()->isVisible()) {
        // The following keys are forwarded by the completer to the widget
       switch (event->key()) {
       case Qt::Key_Enter:
       case Qt::Key_Return:
       case Qt::Key_Escape:
       case Qt::Key_Tab:
       case Qt::Key_Backtab:
            event->ignore();
            return; // let the completer do default behavior
       default:
           break;
       }
    }


    if ((event->key() == Qt::Key_Tab)  &&  (event->modifiers()  &  Qt::ControlModifier) )
        return;

    if ((event->key() == Qt::Key_Tab)  &&  (event->modifiers()  &  Qt::ControlModifier  & Qt::ShiftModifier) )
        return;

    if (event->key() == Qt::Key_Backtab)
    {
        QTextCursor  anchor_pos_cursor = this->textCursor();
        anchor_pos_cursor.setPosition(this->textCursor().anchor());
        if(this->textCursor().blockNumber() != anchor_pos_cursor.blockNumber())
            decrease_identation();
        return;
    }

    if((event->key() == Qt::Key_Backspace))
    {
        delete_back();
    }

    if ((event->key() == Qt::Key_Tab)  )
    {
        QTextCursor  anchor_pos_cursor = this->textCursor();
        anchor_pos_cursor.setPosition(this->textCursor().anchor());
        if(this->textCursor().blockNumber() != anchor_pos_cursor.blockNumber())
            increase_identation();
        else
            insert_tab();
        return;
    }

    //  emacs movement keys...
    if ((event->key() == Qt::Key_P)  &&  (event->modifiers()  &  Qt::ControlModifier) )
    {
        QTextCursor cursor = this->textCursor();
        cursor.movePosition(QTextCursor::PreviousBlock);
        this->setTextCursor(cursor);
        return;
    }
    if ((event->key() == Qt::Key_N)  &&  (event->modifiers()  &  Qt::ControlModifier) )
    {
        QTextCursor cursor = this->textCursor();
        cursor.movePosition(QTextCursor::NextBlock);
        this->setTextCursor(cursor);
        return;
    }
    if ((event->key() == Qt::Key_P)  &&  (event->modifiers()  &  Qt::AltModifier) )
    {
        QTextCursor cursor = this->textCursor();
        for (int i=0; i<20; ++i)
            cursor.movePosition(QTextCursor::PreviousBlock);
        this->setTextCursor(cursor);
        return;
    }
    if ((event->key() == Qt::Key_N)  &&  (event->modifiers()  &  Qt::AltModifier) )
    {
        QTextCursor cursor = this->textCursor();
        for (int i=0; i<20; ++i)
            cursor.movePosition(QTextCursor::NextBlock);
        this->setTextCursor(cursor);
        return;
    }

    if ((event->key() == Qt::Key_A)  &&  (event->modifiers()  &  Qt::ControlModifier) )
    {
        QTextCursor cursor = this->textCursor();
        cursor.movePosition(QTextCursor::StartOfBlock);
        this->setTextCursor(cursor);
        return;
    }
    if ((event->key() == Qt::Key_E)  &&  (event->modifiers()  &  Qt::ControlModifier) )
    {
        QTextCursor cursor = this->textCursor();
        cursor.movePosition(QTextCursor::EndOfBlock);
        this->setTextCursor(cursor);
        return;
    }
    if ((event->key() == Qt::Key_F)  &&  (event->modifiers()  &  Qt::ControlModifier) )
    {
        QTextCursor cursor = this->textCursor();
        cursor.movePosition(QTextCursor::NextCharacter);
        this->setTextCursor(cursor);
        return;
    }
    if ((event->key() == Qt::Key_B)  &&  (event->modifiers()  &  Qt::ControlModifier) )
    {
        QTextCursor cursor = this->textCursor();
        cursor.movePosition(QTextCursor::PreviousCharacter);
        this->setTextCursor(cursor);
        return;
    }
    if ((event->key() == Qt::Key_F)  &&  (event->modifiers()  &  Qt::AltModifier) )
    {
        QTextCursor cursor = this->textCursor();
        cursor.movePosition(QTextCursor::NextWord);
        this->setTextCursor(cursor);
        return;
    }
    if ((event->key() == Qt::Key_B)  &&  (event->modifiers()  &  Qt::AltModifier) )
    {
        QTextCursor cursor = this->textCursor();
        cursor.movePosition(QTextCursor::PreviousWord);
        this->setTextCursor(cursor);
        return;
    }

    if ((event->key() == Qt::Key_D)  &&  (event->modifiers()  &  Qt::ControlModifier) )
    {
        QTextCursor cursor = this->textCursor();
        cursor.deleteChar();
        return;
    }
    if ((event->key() == Qt::Key_K)  &&  (event->modifiers()  &  Qt::ControlModifier) )
    {
        this->textCursor().deleteChar();
        while (this->textCursor().atBlockEnd() == false)
        {
            this->textCursor().deleteChar();
        }
        return;
    }


    if((event->modifiers() | event->key()) == QKeySequence("Ctrl+Space"))
        show_completer(textUnderCursor());
    else
    {
        QPlainTextEdit::keyPressEvent(event);
        QString  pressed_key_as_string = QKeySequence(event->key()).toString();
        QString  text_under_cursor = textUnderCursor();
        if(text_under_cursor.size() > 2  &&  ((event->text()!=""  &&  pressed_key_as_string[0].isLetterOrNumber())
                ||  completer->popup()->isVisible()))
            show_completer(text_under_cursor);
        else
            completer->popup()->hide();

    }
}


void  MQEditorSingle::request_completion_list(const QString&      text_under_cursor, QStringList&   return_completion_list)
{
    signal_request_completion_list.emit(this, text_under_cursor, return_completion_list);
}

void MQEditorSingle::show_completer(const QString& text_under_cursor)
{
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
#endif

    QStringList completion_words;
    request_completion_list(text_under_cursor, completion_words);

#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif
    model_completer->setStringList(completion_words);

    /*if (text_under_cursor != completer->completionPrefix()) {
        completer->setCompletionPrefix(text_under_cursor);
        completer->popup()->setCurrentIndex(completer->completionModel()->index(0, 0));
    }*/
    QRect cr = cursorRect();
    int width = completer->popup()->sizeHintForColumn(0)
            + completer->popup()->verticalScrollBar()->sizeHint().width();
    if(width>300)   width = 300;
    cr.setWidth(width);
    completer->complete(cr); // popup it up!
    completer->popup()->setCurrentIndex(completer->completionModel()->index(0, 0));
    return;
}



LineCommandArea::LineCommandArea(MQEditor *editor)
    :       QWidget(editor),
            codeEditor_requesting_command(0),
            layout(new QHBoxLayout(this)),
            txt_cursor_position(new QLabel(this)),
            command_line_edit(new QLineEdit(this))
{
    setAutoFillBackground(true);
    layout->setMargin(0);
    //codeEditor = editor;
    command_line_edit->setVisible(false);

    layout->addWidget(txt_cursor_position);
    layout->addWidget(command_line_edit);


    QFont  command_font ("monospace", 10);
    txt_cursor_position->setFont(command_font);
    txt_cursor_position->adjustSize();
    txt_cursor_position->setMargin(0);

    this->setStyleSheet("background-color: rgb(220, 220, 220);");
    this->setAutoFillBackground(true);

    this->setLayout(layout);

    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
}



void LineCommandArea::on_cursor_update_position(MQEditorSingle* codeEditor)
{
    txt_cursor_position->setText(QString("(%1,%2)")
            .arg(codeEditor->textCursor().blockNumber()+1)
            .arg(codeEditor->textCursor().positionInBlock()+1));
}

void LineCommandArea::on_request_command_editor(MQEditorSingle* editor)
{
    command_line_edit->setVisible(true);
    command_line_edit->setText(":");
    command_line_edit->setFocus();
    codeEditor_requesting_command = editor;
}




void MQEditorSingle::insertCompletion(const QString& completion_text)
{
    if (completer->widget() != this)
        return;
    QTextCursor tc = textCursor();
    tc.movePosition(QTextCursor::EndOfWord);
    tc.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor, textUnderCursor().length());
    tc.removeSelectedText();
    tc.insertText(completion_text);
    setTextCursor(tc);
}

void  MQEditorSingle::on_cursor_update_position()
{
    if(this->hasFocus())
        signal_cursor_position_change(this);
}


void  fill_text_completion(   MQEditorSingle*             editor,
                              const QString&        text_under_cursor,
                              QStringList&          return_completion_list)
{
    QStringList words = editor->toPlainText().split(QRegExp("[^a-zA-Z0-9_]"), QString::SkipEmptyParts);
    words.removeDuplicates();
    words.sort();

    QStringList          secondary_completion_list;
    QString str;
    foreach(str, words)
    {
        if(str != text_under_cursor  &&  str.toUpper().indexOf(text_under_cursor.toUpper())==0)
            return_completion_list.append(str);
        else if(str != text_under_cursor  &&  str.toUpper().indexOf(text_under_cursor.toUpper())>0)
            secondary_completion_list.append(str);
    }
    return_completion_list.append(secondary_completion_list);
}



void MQEditorSingle::command_help           (const std::string& cmd, const std::string& params, mtk::list<std::string>& response_lines )
{
    command_manager->command_help(cmd, params, response_lines);
}

void MQEditorSingle::command_version        (const std::string& cmd, const std::string& params, mtk::list<std::string>& response_lines )
{

}

void MQEditorSingle::command_modifications  (const std::string& cmd, const std::string& params, mtk::list<std::string>& response_lines )
{

}

void MQEditorSingle::command_stats          (const std::string& cmd, const std::string& params, mtk::list<std::string>& response_lines )
{

}

void MQEditorSingle::command_config         (const std::string& cmd, const std::string& params, mtk::list<std::string>& response_lines )
{

}



void     MQEditorSingle::update_ViewportMargins(void)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void MQEditorSingle::__resize(void)
{
    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));

    update_ViewportMargins();
}


struct Command_manager::command_info {
    mtk::non_copyable nc;

    command_info(const std::string& _name, const std::string& _description)
        :   name(_name), description(_description),
            signal_command_received(mtk::make_cptr(new mtk::Signal<const std::string& /*cmd*/, const std::string& /*params*/, mtk::list<std::string>& /*lines response*/> ))
        {}

    const std::string   group;
    const std::string   name;
    const std::string   description;
    mtk::CountPtr<  mtk::Signal<    const std::string&      /*cmd*/,
                                    const std::string&      /*params*/,
                                    mtk::list<std::string>& /*respnose lines to fill*/> >   signal_command_received;

};

mtk::CountPtr<mtk::Signal<const std::string& /*cmd*/, const std::string& /*params*/, mtk::list<std::string>& /*response lines*/> >
                                    Command_manager::register_command(
                                                                const std::string& name,
                                                                const std::string& description)
{

    if(map_commands.find(name) == map_commands.end())
    {
        map_commands[name] = mtk::make_cptr(new command_info(name, description));
    }
    return map_commands[name]->signal_command_received;
}


void Command_manager::command_help           (const std::string& cmd, const std::string& params, mtk::list<std::string>& response_lines )
{
    mtk::map<std::string, mtk::CountPtr<command_info> >::iterator it=map_commands.begin();
    while(it!=map_commands.end())
    {
        command_info&  ci = *it->second;
        response_lines.push_back(MTK_SS(ci.name << "  "  <<  ci.description));
        ++it;
    }
}


void LineCommandArea::keyPressEvent(QKeyEvent *event)
{
    QString key = QKeySequence(event->modifiers() | event->key()).toString();
    if(key=="Esc")
    {
        codeEditor_requesting_command->setFocus();
        codeEditor_requesting_command = 0;
        this->command_line_edit->setVisible(false);
        event->ignore();
    }
    else
        QWidget::keyPressEvent(event);
}
