#pragma once
#include "../settings.h"
#include "../window/window.h"

class Program {
    public:
        Program();
        ~Program();
        void useWindow(Window &window, bool useDepthFunction = true);
        void start();
        void terminate();
        bool CheckForError();
        void setCursorMode(Cursor_Mode mode);
        void setMultisampling(int sampleCount);

    private:
        Window *_window;
        std::string errorMessage;
        bool terminated = 0;
};
