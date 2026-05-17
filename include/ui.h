/*
 * ui.h
 * ====
 * Presentation Layer — all Raylib rendering and user interaction.
 *
 * Responsibilities:
 *   - Window lifecycle (open/close).
 *   - Animated background, particles, transitions.
 *   - All screen rendering: main menu, product table, forms, stats.
 *   - User input handling (keyboard + mouse).
 *
 * Rules:
 *   - Calls Logic layer only — never Data layer directly.
 *   - No business logic lives here.
 */

#pragma once

#include "data.h"
#include <vector>
#include <string>
#include <functional>

// -------------------------------------------------------
// Colour palette  (dark cyberpunk theme)
// -------------------------------------------------------
#include "raylib.h"

namespace Palette {
    inline constexpr Color BG_DARK     = { 8,  12,  24, 255 };   // near-black navy
    inline constexpr Color BG_PANEL    = { 14, 22,  44, 255 };   // dark panel
    inline constexpr Color BG_CARD     = { 20, 32,  60, 255 };   // card background
    inline constexpr Color ACCENT      = { 0, 200, 255, 255 };   // cyan
    inline constexpr Color ACCENT2     = { 120, 60, 255, 255 };  // purple
    inline constexpr Color SUCCESS     = { 40, 220, 140, 255 };  // green
    inline constexpr Color WARNING     = { 255, 180,  40, 255 }; // amber
    inline constexpr Color DANGER      = { 255,  70,  70, 255 }; // red
    inline constexpr Color TEXT_BRIGHT = { 220, 235, 255, 255 };
    inline constexpr Color TEXT_DIM    = { 110, 135, 175, 255 };
    inline constexpr Color BORDER      = {  30,  55, 100, 255 };
}

// -------------------------------------------------------
// Screen identifiers
// -------------------------------------------------------
enum class Screen {
    SPLASH,
    MAIN_MENU,
    VIEW_PRODUCTS,
    ADD_PRODUCT,
    REMOVE_PRODUCT,
    SORT_MENU,
    SEARCH,
    STATISTICS,
    SETTINGS
};

// -------------------------------------------------------
// Particle system
// -------------------------------------------------------
struct Particle {
    Vector2 pos;
    Vector2 vel;
    float   life;     // 0..1, decreases over time
    float   size;
    Color   color;
};

// -------------------------------------------------------
// Animated button
// -------------------------------------------------------
struct Button {
    Rectangle   bounds;
    std::string label;
    Color       baseColor;
    float       hoverAnim;   // 0..1 lerped hover progress
    bool        pressed;
};

// -------------------------------------------------------
// Notification toast
// -------------------------------------------------------
struct Toast {
    std::string message;
    Color       color;
    float       life;        // seconds remaining
};

// -------------------------------------------------------
// Application state
// -------------------------------------------------------
struct AppState {
    std::vector<Product>& products;

    Screen currentScreen  = Screen::SPLASH;
    Screen previousScreen = Screen::MAIN_MENU;
    float  transitionAlpha = 0.0f;  // 0 = visible, 1 = fully black (mid-transition)
    bool   transitioning  = false;
    Screen nextScreen     = Screen::MAIN_MENU;

    // Splash
    float splashTimer = 0.0f;

    // Background
    float      bgTime   = 0.0f;
    std::vector<Particle> particles;

    // Scroll / table
    float tableScroll   = 0.0f;
    float tableScrollTarget = 0.0f;

    // Search
    char  searchBuf[128] = {};
    std::vector<Product> searchResults;
    bool  searchDone = false;

    // Add-product form
    char   nameBuf[64]  = {};
    char   priceBuf[32] = {};
    char   qtyBuf[16]   = {};
    int    catIndex     = 0;
    int    activeField  = 0;
    std::string formError;
    bool   formSuccess  = false;

    // Remove-product form
    char   removeIdBuf[16] = {};
    std::string removeMsg;

    // Sort
    int    sortChoice = -1;

    // Stats animation
    float  statsAnim = 0.0f;

    // Notifications
    std::vector<Toast> toasts;

    // Settings
    float musicVolume = 0.5f;
    float sfxVolume   = 0.5f;
    bool  particlesOn = true;
    bool  scanlines   = true;
};

// -------------------------------------------------------
// Main entry point (called from main.cpp)
// -------------------------------------------------------

/**
 * runApplication
 * Opens a Raylib window, runs the main loop, and returns when the user exits.
 * @param products  Reference to the live product list.
 */
void runApplication(std::vector<Product>& products);
