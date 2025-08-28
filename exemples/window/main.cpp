#include "../../src/graphics/graphics.h"

int main(void) {
    Program program;
    program.start();
    Window window("MyApp", 800, 800);
    program.useWindow(window);
    Event event;

    if (program.CheckForError())
        return 1;

    window.setColor(0, 100, 100, 255);

    while (!window.isClosed()) {
        window.clear();
        window.pollEvents(event);
        window.swap();
    }

    program.terminate();
    return 0;
}
