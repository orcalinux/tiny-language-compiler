// TextEditor class definition

#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QWidget>
#include <QObject>
#include <QTextEdit>
#include <QTextCursor>
#include <QTextBlock>

namespace Tiny::Widgets {

    class TextEditor : public QTextEdit {
        Q_OBJECT
       public:
        explicit TextEditor(QWidget* parent = nullptr);

        void markUnknowTokens(int line, int column = -1, int charCount = 0);
        void markReservedToken(int line, int column = -1, int charCount = 0);
        void resetFormat();
        void markParseError(int line, int column, int charCount, QString message, bool markWholeLine = false);
       signals:

       public slots:

       private:
        void initStyle();
        void initConfig();
    };

}  // namespace Tiny::Widgets

#endif  // TEXTEDITOR_H
