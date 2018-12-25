#include <gtest/gtest.h>

#include "Keyboard.hpp"

TEST(KeyboardTest, test_not_pressed)
{
    Keyboard keyboard;
    ASSERT_FALSE(keyboard.isPressed(sf::Keyboard::Key::Space));
}

TEST(KeyboardTest, test_pressed) {
    Keyboard keyboard;
    keyboard.press(sf::Keyboard::Key::Space);
    ASSERT_TRUE(keyboard.isPressed(sf::Keyboard::Key::Space));
}

TEST(KeyboardTest, test_pressed_two_times) {
    Keyboard keyboard;
    keyboard.press(sf::Keyboard::Key::Space);
    keyboard.press(sf::Keyboard::Key::Space);
    ASSERT_TRUE(keyboard.isPressed(sf::Keyboard::Key::Space));
}

TEST(KeyboardTest, test_released) {
    Keyboard keyboard;
    keyboard.press(sf::Keyboard::Key::Space);
    keyboard.release(sf::Keyboard::Key::Space);
    ASSERT_FALSE(keyboard.isPressed(sf::Keyboard::Key::Space));
}

TEST(KeyboardTest, test_released_two_times) {
    Keyboard keyboard;
    keyboard.press(sf::Keyboard::Key::Space);
    keyboard.release(sf::Keyboard::Key::Space);
    keyboard.release(sf::Keyboard::Key::Space);
    ASSERT_FALSE(keyboard.isPressed(sf::Keyboard::Key::Space));
}
