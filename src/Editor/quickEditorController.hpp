#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>
#include <QQuickTextDocument>

namespace quick {

    namespace Editor {

        class Util;
        class Search;
        class Errors;
        class Selection;
        class Highlighter;

        class Controller : public QObject {
            Q_OBJECT
            Q_PROPERTY(int fontSize READ getFontSize NOTIFY fontSizeChanged);
            Q_PROPERTY(bool expanded READ getExpanded NOTIFY expandedChanged);
            Q_PROPERTY(bool modified READ getModified NOTIFY modifiedChanged);
            Q_PROPERTY(QString fileUrl READ getFileUrl NOTIFY fileUrlChanged);
            Q_PROPERTY(QString fileName READ getFileName NOTIFY fileNameChanged);
            Q_PROPERTY(QQuickTextDocument* document READ getDocument WRITE setDocument NOTIFY documentChanged);
            Q_PROPERTY(quick::Editor::Errors* errors READ getErrors CONSTANT);
            Q_PROPERTY(quick::Editor::Search* search READ getSearch CONSTANT);
            Q_PROPERTY(quick::Editor::Selection* selection READ getSelection CONSTANT);
        public:
            friend class Util;
            static Controller* instance;
            static Qml::Register::Controller<Controller> Register;
            static auto Create() -> void;
        private:
            QString m_fileUrl;
            QString m_fileName;
            int m_fontSizeMin = 8;
            int m_fontSize = 11;
            int m_fontSizeMax = 20;
            bool m_expanded = true;
            bool m_modified = false;
            Highlighter* m_highlighter = nullptr;
            QQuickTextDocument* m_document;
			QString m_code_text;
        private:
            auto setFileUrl(const QString&) -> void;
            auto setFileName(const QString&) -> void;
        public slots:
            void setModified(bool);
            void run();
            void newFile();
            void openFile();
            void saveFile();
            void saveFileAs();
            void showSearch();
            void resetFontSize();
            void increaseFontSize();
            void decreaseFontSize();
            QString getText();
        public:
            auto setDocument(QQuickTextDocument*) -> void;
            auto getDocument() -> QQuickTextDocument*;
            auto getSelection() -> Selection*;
            auto getErrors() -> Errors*;
            auto getSearch() -> Search*;
            auto openFile(const QString&) -> void;
            auto getExpanded() -> bool;
            auto getFileUrl() -> QString;
            auto getFileName() -> QString;
            auto getModified() -> bool;
            auto toggleExpanded() -> void;
            auto getFontSize() -> int;
			auto setCodeText(const QString&) -> void;
            ~Controller();
        signals:
            void select(int start, int end);
            void fileNameChanged();
            void fontSizeChanged();
            void documentChanged();
            void expandedChanged();
            void modifiedChanged();
            void fileUrlChanged();
            void compile();
            void clear();
        };
    }
}
