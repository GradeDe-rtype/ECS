/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

#ifndef GRADE_DE_KEYBOARD_SFML_HPP_
    #define GRADE_DE_KEYBOARD_SFML_HPP_

    /*  ---- INCLUDES ---- */

    /*  ---- CLASS ---- */
namespace gd
{
    namespace KeyBoard
    {
        /**
         * \brief Enum that represents the keys on a keyboard.
         *
         * This enum defines various key codes for each key on a standard keyboard.
         * It is used for handling keyboard input and key events.
         */
        enum Key
        {
            /**
             * \brief Key code for unknown key.
             * Used to represent an unknown or undefined key.
             */
            Unknown = -1,

            /**
             * \brief Key code for the A key.
             */
            A = 0,

            /**
             * \brief Key code for the B key.
             */
            B,

            /**
             * \brief Key code for the C key.
             */
            C,

            /**
             * \brief Key code for the D key.
             */
            D,

            /**
             * \brief Key code for the E key.
             */
            E,

            /**
             * \brief Key code for the F key.
             */
            F,

            /**
             * \brief Key code for the G key.
             */
            G,

            /**
             * \brief Key code for the H key.
             */
            H,

            /**
             * \brief Key code for the I key.
             */
            I,

            /**
             * \brief Key code for the J key.
             */
            J,

            /**
             * \brief Key code for the K key.
             */
            K,

            /**
             * \brief Key code for the L key.
             */
            L,

            /**
             * \brief Key code for the M key.
             */
            M,

            /**
             * \brief Key code for the N key.
             */
            N,

            /**
             * \brief Key code for the O key.
             */
            O,

            /**
             * \brief Key code for the P key.
             */
            P,

            /**
             * \brief Key code for the Q key.
             */
            Q,

            /**
             * \brief Key code for the R key.
             */
            R,

            /**
             * \brief Key code for the S key.
             */
            S,

            /**
             * \brief Key code for the T key.
             */
            T,

            /**
             * \brief Key code for the U key.
             */
            U,

            /**
             * \brief Key code for the V key.
             */
            V,

            /**
             * \brief Key code for the W key.
             */
            W,

            /**
             * \brief Key code for the X key.
             */
            X,

            /**
             * \brief Key code for the Y key.
             */
            Y,

            /**
             * \brief Key code for the Z key.
             */
            Z,

            /**
             * \brief Key code for the 0 key.
             */
            Num0,

            /**
             * \brief Key code for the 1 key.
             */
            Num1,

            /**
             * \brief Key code for the 2 key.
             */
            Num2,

            /**
             * \brief Key code for the 3 key.
             */
            Num3,

            /**
             * \brief Key code for the 4 key.
             */
            Num4,

            /**
             * \brief Key code for the 5 key.
             */
            Num5,

            /**
             * \brief Key code for the 6 key.
             */
            Num6,

            /**
             * \brief Key code for the 7 key.
             */
            Num7,

            /**
             * \brief Key code for the 8 key.
             */
            Num8,

            /**
             * \brief Key code for the 9 key.
             */
            Num9,

            /**
             * \brief Key code for the Escape key.
             */
            Escape,

            /**
             * \brief Key code for the left Control key.
             */
            LControl,

            /**
             * \brief Key code for the left Shift key.
             */
            LShift,

            /**
             * \brief Key code for the left Alt key.
             */
            LAlt,

            /**
             * \brief Key code for the left OS-specific key (e.g., Windows, macOS).
             */
            LSystem,

            /**
             * \brief Key code for the right Control key.
             */
            RControl,

            /**
             * \brief Key code for the right Shift key.
             */
            RShift,

            /**
             * \brief Key code for the right Alt key.
             */
            RAlt,

            /**
             * \brief Key code for the right OS-specific key (e.g., Windows, macOS).
             */
            RSystem,

            /**
             * \brief Key code for the Menu key.
             */
            Menu,

            /**
             * \brief Key code for the [ key.
             */
            LBracket,

            /**
             * \brief Key code for the ] key.
             */
            RBracket,

            /**
             * \brief Key code for the ; key.
             */
            Semicolon,

            /**
             * \brief Key code for the , key.
             */
            Comma,

            /**
             * \brief Key code for the . key.
             */
            Period,

            /**
             * \brief Key code for the ' key.
             */
            Apostrophe,

            /**
             * \brief Key code for the / key.
             */
            Slash,

            /**
             * \brief Key code for the \ key.
             */
            Backslash,

            /**
             * \brief Key code for the ` key.
             */
            Grave,

            /**
             * \brief Key code for the = key.
             */
            Equal,

            /**
             * \brief Key code for the - key (hyphen).
             */
            Hyphen,

            /**
             * \brief Key code for the Space key.
             */
            Space,

            /**
             * \brief Key code for the Enter/Return key.
             */
            Enter,

            /**
             * \brief Key code for the Backspace key.
             */
            Backspace,

            /**
             * \brief Key code for the Tab key.
             */
            Tab,

            /**
             * \brief Key code for the Page Up key.
             */
            PageUp,

            /**
             * \brief Key code for the Page Down key.
             */
            PageDown,

            /**
             * \brief Key code for the End key.
             */
            End,

            /**
             * \brief Key code for the Home key.
             */
            Home,

            /**
             * \brief Key code for the Insert key.
             */
            Insert,

            /**
             * \brief Key code for the Delete key.
             */
            Delete,

            /**
             * \brief Key code for the + key.
             */
            Add,

            /**
             * \brief Key code for the - key (minus, numpad).
             */
            Subtract,

            /**
             * \brief Key code for the * key.
             */
            Multiply,

            /**
             * \brief Key code for the / key.
             */
            Divide,

            /**
             * \brief Key code for the Left arrow key.
             */
            Left,

            /**
             * \brief Key code for the Right arrow key.
             */
            Right,

            /**
             * \brief Key code for the Up arrow key.
             */
            Up,

            /**
             * \brief Key code for the Down arrow key.
             */
            Down,

            /**
             * \brief Key code for the numpad 0 key.
             */
            Numpad0,

            /**
             * \brief Key code for the numpad 1 key.
             */
            Numpad1,

            /**
             * \brief Key code for the numpad 2 key.
             */
            Numpad2,

            /**
             * \brief Key code for the numpad 3 key.
             */
            Numpad3,

            /**
             * \brief Key code for the numpad 4 key.
             */
            Numpad4,

            /**
             * \brief Key code for the numpad 5 key.
             */
            Numpad5,

            /**
             * \brief Key code for the numpad 6 key.
             */
            Numpad6,

            /**
             * \brief Key code for the numpad 7 key.
             */
            Numpad7,

            /**
             * \brief Key code for the numpad 8 key.
             */
            Numpad8,

            /**
             * \brief Key code for the numpad 9 key.
             */
            Numpad9,

            /**
             * \brief Key code for the F1 key.
             */
            F1,

            /**
             * \brief Key code for the F2 key.
             */
            F2,

            /**
             * \brief Key code for the F3 key.
             */
            F3,

            /**
             * \brief Key code for the F4 key.
             */
            F4,

            /**
             * \brief Key code for the F5 key.
             */
            F5,

            /**
             * \brief Key code for the F6 key.
             */
            F6,

            /**
             * \brief Key code for the F7 key.
             */
            F7,

            /**
             * \brief Key code for the F8 key.
             */
            F8,

            /**
             * \brief Key code for the F9 key.
             */
            F9,

            /**
             * \brief Key code for the F10 key.
             */
            F10,

            /**
             * \brief Key code for the F11 key.
             */
            F11,

            /**
             * \brief Key code for the F12 key.
             */
            F12,

            /**
             * \brief Key code for the F13 key.
             */
            F13,

            /**
             * \brief Key code for the F14 key.
             */
            F14,

            /**
             * \brief Key code for the F15 key.
             */
            F15,

            /**
             * \brief Key code for the Pause key.
             */
            Pause,

            /**
             * \brief Keep last -- the total number of keyboard keys.
             */
            KeyCount,

            // Deprecated values:
            /**
             * \deprecated Use Grave instead.
             */
            Tilde     = Grave,

            /**
             * \deprecated Use Hyphen instead.
             */
            Dash      = Hyphen,

            /**
             * \deprecated Use Backspace instead.
             */
            BackSpace = Backspace,

            /**
             * \deprecated Use Backslash instead.
             */
            BackSlash = Backslash,

            /**
             * \deprecated Use Semicolon instead.
             */
            SemiColon = Semicolon,

            /**
             * \deprecated Use Enter instead.
             */
            Return    = Enter,

            /**
             * \deprecated Use Apostrophe instead.
             */
            Quote     = Apostrophe
        };
    };
}

#endif /* !GRADE_DE_KEYBOARD_SFML_HPP_ */
