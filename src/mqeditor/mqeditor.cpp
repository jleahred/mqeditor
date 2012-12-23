#include "mqeditor.h"
#include <iostream>
#include <QTextBlock>
#include <QPainter>


MQEditor::MQEditor(QWidget *parent) :
    QPlainTextEdit(parent)
{
    lineNumberArea = new LineNumberArea(this);

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();

}

int MQEditor::lineNumberAreaWidth()
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

void MQEditor::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}


void MQEditor::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

void MQEditor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}


void MQEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
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
            painter.setPen(Qt::black);
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}


void MQEditor::highlightCurrentLine()
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


void MQEditor::insert_tab(void)
{
    QTextCursor cursor = this->textCursor();
    int first_block_selected = 0;
    int last_block_selected = 0;
    int min_pos=0;
    int extra_line=0;
    if(cursor.position() != cursor.anchor())
    {
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
    else
    {
        QTextCursor  cursor = this->textCursor();
        int num_spaces2add = 4 - cursor.positionInBlock()%4;
        if(num_spaces2add==0)  num_spaces2add = 4;
        QString spaces2add (num_spaces2add, ' ');
        cursor.insertText(spaces2add);
    }
}


void MQEditor::keyPressEvent ( QKeyEvent * event )
{
    if ((event->key() == Qt::Key_Tab)  &&  (event->modifiers()  &  Qt::ControlModifier) )
        return;

    if ((event->key() == Qt::Key_Tab)  &&  (event->modifiers()  &  Qt::ControlModifier  & Qt::ShiftModifier) )
        return;

    if ((event->key() == Qt::Key_Tab)  )
    {
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


    QPlainTextEdit::keyPressEvent(event);
}
