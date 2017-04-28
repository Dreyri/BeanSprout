#ifndef INPUT_CODES_H
#define INPUT_CODES_H

enum class MouseButton : int {
    Button_1 = 0,
    Button_2 = 1,
    Button_3 = 2,
    Button_4 = 3,
    Button_5 = 4,
    Button_6 = 5,
    Button_7 = 6,
    Button_8 = 7,
    Last = Button_8,
    Left = Button_1,
    Right = Button_2,
    Middle = Button_3
};

enum class MouseButtonState : int {
    Release = 0,
    Press = 1
};

#endif /* INPUT_CODES_H */
