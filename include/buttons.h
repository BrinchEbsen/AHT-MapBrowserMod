#ifndef BUTTONS_H
#define BUTTONS_H

#include <custom_types.h>
#include <symbols.h>
#include <common.h>

bool P1_IsButtonsJustPressed(Buttons button)
{
    static Buttons P1_was_button_just_pressed = 0;

    //If button was pressed, and has not been pressed yet, set the bit for that button
    if ((current_buttons & button) && !(P1_was_button_just_pressed & button))
    {
        P1_was_button_just_pressed |= (current_buttons & button);
        return true;
    }

    //If button was released, clear the bit for that button
    else if (!(current_buttons & button) && (P1_was_button_just_pressed & button))
    {
        P1_was_button_just_pressed &= ~button;
    }

    return false;
}

bool P1_IsButtonsHeldDown(Buttons button)
{
    if ((current_buttons & button))
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool P2_IsButtonsJustPressed(Buttons button)
{
    static Buttons P2_was_button_just_pressed = 0;

    //If button was pressed, and has not been pressed yet, set the bit for that button
    if ((current_buttonsP2 & button) && !(P2_was_button_just_pressed & button))
    {
        P2_was_button_just_pressed |= (current_buttonsP2 & button);
        return true;
    }

    //If button was released, clear the bit for that button
    else if (!(current_buttonsP2 & button) && (P2_was_button_just_pressed & button))
    {
        P2_was_button_just_pressed &= ~button;
    }

    return false;
}

bool P2_IsButtonsHeldDown(Buttons button)
{
    if ((current_buttonsP2 & button))
    {
        return true;
    }
    else
    {
        return false;
    }
}

#endif /* BUTTONS_H */
