enum Cursor_Mode { HIDDEN, NORMAL, DISABLED, DISABLED_RAW };
enum Transformation_Mode { Quaternion_Mode, Matrix_Mode };
enum Projection_Style { Orthographic_Style, Perspective_Style };

class Program_Settings {
    public:
        static Transformation_Mode transformation_mode;
        static Cursor_Mode cursor_mode;
        static Projection_Style proj_style;
        static bool vSync;
        static float aspectRatio;

    private:
};
