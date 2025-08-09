// Modified SDL events

#pragma once
#include <GameEngine/Events/key_list.h>

#define KEY_RELEASED 0
#define KEY_PRESSED 1
#define KEY_REPEAT 2

#define BUTTON_RELEASED 0
#define BUTTON_PRESSED 1
#define BUTTON_REPEAT 2

#define NULL_EVENT 0

#define WINDOW_NULL_EVENT 0X200
#define WINDOW_RESIZED 0X201
#define WINDOW_CLOSED 0x202
#define WINDOW_MINIMIZED 0X203
#define WINDOW_MAXIMIZED 0x204
#define WINDOW_FOCUSED 0x205
#define WINDOW_NOT_FOCUSED 0x206
#define WINDOW_HIDDEN 0x207
#define WINDOW_SHOWN 0x208
#define WINDOW_RESTORED 0x209

#define MOUSE_MOTION 111
#define MOUSE_BUTTON_1 0
#define MOUSE_BUTTON_2 1
#define MOUSE_BUTTON_3 2
#define MOUSE_BUTTON_4 3
#define MOUSE_BUTTON_5 4
#define MOUSE_BUTTON_6 5
#define MOUSE_BUTTON_7 6
#define MOUSE_BUTTON_8 7
#define MOUSE_BUTTON_LAST MOUSE_BUTTON_8
#define MOUSE_BUTTON_LEFT MOUSE_BUTTON_1
#define MOUSE_BUTTON_RIGHT MOUSE_BUTTON_2
#define MOUSE_BUTTON_MIDDLE MOUSE_BUTTON_3

#define WHEEL_SCROLL 222

typedef enum {
    NULLEVENT = 0,

    PROGRAM_QUIT = 0x100,

    WINDOW_EVENT = 0x200,

    KEYBOARD_EVENT = 0x300,

    MOUSE_MOTION_EVENT = 0x400,
    MOUSE_BUTTON_EVENT,
    MOUSE_WHEEL_EVENT

} EventType;

// Eventuri preluate din SDL
typedef struct WindowEvent {
        EventType type;
        int action;
        int windowID;
        short event;
        short padding1;
        short padding2;
        short padding3;
        int data1;
        int data2;
} WindowEvent;

typedef struct Keysym {
        int key;
        int scancode;
        int mods;
} Keysym;

typedef struct KeyboardEvent {
        EventType type;
        int action;
        int windowID;
        short state;
        short repeat;
        short padding2;
        short padding3;
        Keysym keysym;
} KeyboardEvent;

typedef struct MouseMotionEvent {
        EventType type;
        int action;
        int timestamp;
        int windowID; /**< The window with mouse focus, if any */
        int which;    /**< The mouse instance id */
        int state;    /**< The current button state */
        int x;        /**< X coordinate, relative to window */
        int y;        /**< Y coordinate, relative to window */
        int xrel;     /**< The relative motion in the X direction */
        int yrel;     /**< The relative motion in the Y direction */
} MouseMotionEvent;

typedef struct MouseButtonEvent {
        EventType type;
        int action;
        int timestamp;
        int windowID; /**< The window with mouse focus, if any */
        int which;    /**< The mouse instance id*/
        short button; /**< The mouse button index */
        short state;  // pressed released
        short padding1;
        short padding2;
        int x; /**< X coordinate, relative to window */
        int y; /**< Y coordinate, relative to window */
} MouseButtonEvent;

typedef struct MouseWheelEvent {
        EventType type;
        int action;
        int timestamp;
        int windowID; /**< The window with mouse focus, if any */
        int which;    /**< The mouse instance id*/
        int x;        /**< The amount scrolled horizontally */
        int y;        /**< The amount scrolled vertically */
} MouseWheelEvent;

typedef union Event {
        Event() {
            last_ID++;
            event_ID = last_ID;
            type = NULLEVENT;
        }
        EventType type;
        int event_ID;
        WindowEvent window;
        KeyboardEvent key;
        MouseMotionEvent motion;
        MouseButtonEvent button;
        MouseWheelEvent wheel;

        friend class Program;

    private:
        static int last_ID;
} Event;
