/*
 * ui.cpp
 * ======
 * Presentation Layer — complete Raylib GUI implementation.
 *
 * Features implemented:
 *   ✦ Animated particle starfield background
 *   ✦ Smooth fade transitions between screens
 *   ✦ Scanline post-processing overlay
 *   ✦ Animated hover buttons with glow
 *   ✦ Splash / loading screen with progress bar
 *   ✦ Product table with live scroll, row highlight, low-stock warnings
 *   ✦ Add / Remove forms with field validation and toast notifications
 *   ✦ Sort menu with animated selection
 *   ✦ Search screen with live results
 *   ✦ Statistics screen with animated bar chart and metric cards
 *   ✦ Settings screen (volumes, toggles)
 *   ✦ HUD: product count, total value, clock
 *
 * Layout: 1280 × 720  (16:9, scales on most displays)
 */

#include "../include/ui.h"
#include "../include/logic.h"

#include "raylib.h"
#include "raymath.h"

#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

// -------------------------------------------------------
// Window constants
// -------------------------------------------------------
static constexpr int   WIN_W  = 1280;
static constexpr int   WIN_H  = 720;
static constexpr float FPS    = 60.0f;
static constexpr int   TARGET = 60;

// -------------------------------------------------------
// Forward declarations (private helpers)
// -------------------------------------------------------
static void initParticles(AppState& s);
static void updateParticles(AppState& s, float dt);
static void drawBackground(const AppState& s);
static void drawScanlines();
static void drawHUD(const AppState& s);
static void drawToasts(AppState& s, float dt);

static bool drawButton(Button& btn, float dt);
static Button makeButton(float x, float y, float w, float h,
                         const std::string& label, Color color);
static void drawPanel(float x, float y, float w, float h,
                      const char* title = nullptr, Color borderColor = Palette::BORDER);
static void drawMetricCard(float x, float y, float w, float h,
                           const char* label, const char* value, Color accent);
static void drawGlowLine(float x1, float y1, float x2, float y2,
                         Color color, float thickness = 1.5f);

static void pushToast(AppState& s, const std::string& msg, Color color);
static void beginTransition(AppState& s, Screen next);
static void updateTransition(AppState& s, float dt);

// Screens
static void drawSplash(AppState& s, float dt);
static void drawMainMenu(AppState& s, float dt);
static void drawViewProducts(AppState& s, float dt);
static void drawAddProduct(AppState& s, float dt);
static void drawRemoveProduct(AppState& s, float dt);
static void drawSortMenu(AppState& s, float dt);
static void drawSearch(AppState& s, float dt);
static void drawStatistics(AppState& s, float dt);
static void drawSettings(AppState& s, float dt);

// -------------------------------------------------------
// Helpers: colour with alpha
// -------------------------------------------------------
static Color withAlpha(Color c, unsigned char a) {
    return { c.r, c.g, c.b, a };
}
static Color lerpColor(Color a, Color b, float t) {
    return {
        (unsigned char)(a.r + (b.r - a.r) * t),
        (unsigned char)(a.g + (b.g - a.g) * t),
        (unsigned char)(a.b + (b.b - a.b) * t),
        (unsigned char)(a.a + (b.a - a.a) * t)
    };
}

// -------------------------------------------------------
// Helpers: text formatting
// -------------------------------------------------------
static std::string fmtPrice(double v) {
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(2) << v << " BGN";
    return ss.str();
}
static std::string fmtInt(int v) { return std::to_string(v); }

// -------------------------------------------------------
// Particle system
// -------------------------------------------------------
static void initParticles(AppState& s) {
    s.particles.clear();
    s.particles.reserve(120);
    for (int i = 0; i < 120; ++i) {
        Particle p;
        p.pos  = { (float)(GetRandomValue(0, WIN_W)),
                   (float)(GetRandomValue(0, WIN_H)) };
        p.vel  = { (float)(GetRandomValue(-15, 15)) * 0.1f,
                   (float)(GetRandomValue(-30, -5)) * 0.1f };
        p.life = (float)(GetRandomValue(10, 100)) * 0.01f;
        p.size = (float)(GetRandomValue(1, 3));
        const int r = GetRandomValue(0, 2);
        if (r == 0)      p.color = Palette::ACCENT;
        else if (r == 1) p.color = Palette::ACCENT2;
        else             p.color = Palette::TEXT_DIM;
        s.particles.push_back(p);
    }
}

static void updateParticles(AppState& s, float dt) {
    if (!s.particlesOn) return;
    for (auto& p : s.particles) {
        p.pos.x += p.vel.x;
        p.pos.y += p.vel.y;
        p.life  -= dt * 0.08f;
        if (p.life <= 0.0f || p.pos.y < -10.0f) {
            // Respawn at bottom
            p.pos  = { (float)(GetRandomValue(0, WIN_W)), (float)WIN_H + 5.0f };
            p.vel  = { (float)(GetRandomValue(-10, 10)) * 0.1f,
                       (float)(GetRandomValue(-40, -10)) * 0.1f };
            p.life = (float)(GetRandomValue(50, 100)) * 0.01f;
        }
    }
}

static void drawBackground(const AppState& s) {
    // Deep gradient-like layered rects
    DrawRectangle(0, 0, WIN_W, WIN_H, Palette::BG_DARK);

    // Subtle grid
    const int GRID = 60;
    for (int x = 0; x < WIN_W; x += GRID)
        DrawLine(x, 0, x, WIN_H, withAlpha(Palette::BORDER, 22));
    for (int y = 0; y < WIN_H; y += GRID)
        DrawLine(0, y, WIN_W, y, withAlpha(Palette::BORDER, 22));

    // Floating glow blobs (simulated with layered circles)
    float t = s.bgTime;
    float bx1 = WIN_W * 0.5f + std::sin(t * 0.3f) * 200.0f;
    float by1 = WIN_H * 0.4f + std::cos(t * 0.2f) * 120.0f;
    DrawCircle((int)bx1, (int)by1, 180, withAlpha(Palette::ACCENT2, 12));
    DrawCircle((int)bx1, (int)by1, 100, withAlpha(Palette::ACCENT2,  7));

    float bx2 = WIN_W * 0.2f + std::cos(t * 0.25f) * 150.0f;
    float by2 = WIN_H * 0.6f + std::sin(t * 0.35f) *  80.0f;
    DrawCircle((int)bx2, (int)by2, 140, withAlpha(Palette::ACCENT, 10));

    // Particles
    if (s.particlesOn) {
        for (const auto& p : s.particles) {
            const unsigned char a = (unsigned char)(p.life * 200.0f);
            DrawCircleV(p.pos, p.size, withAlpha(p.color, a));
        }
    }
}

static void drawScanlines() {
    for (int y = 0; y < WIN_H; y += 3)
        DrawLine(0, y, WIN_W, y, withAlpha(BLACK, 28));
}

// -------------------------------------------------------
// HUD — top bar
// -------------------------------------------------------
static void drawHUD(const AppState& s) {
    // Top bar background
    DrawRectangle(0, 0, WIN_W, 40, withAlpha(Palette::BG_PANEL, 220));
    DrawLine(0, 40, WIN_W, 40, Palette::BORDER);
    drawGlowLine(0, 40, WIN_W, 40, Palette::ACCENT, 1.0f);

    // Logo / brand
    DrawText("◈ BOTEV INVENTORY", 16, 11, 16, Palette::ACCENT);

    // Stats in HUD
    const int count = (int)s.products.size();
    const double total = calcTotalValue(s.products);
    const int low   = countLowStock(s.products, LOW_STOCK_THRESHOLD);

    char buf[128];
    snprintf(buf, sizeof(buf), "Products: %d", count);
    DrawText(buf, 380, 12, 14, Palette::TEXT_DIM);

    snprintf(buf, sizeof(buf), "Value: %.2f BGN", total);
    DrawText(buf, 530, 12, 14, Palette::TEXT_DIM);

    if (low > 0) {
        snprintf(buf, sizeof(buf), "⚠ Low Stock: %d", low);
        DrawText(buf, 710, 12, 14, Palette::WARNING);
    }

    // Clock
    time_t now = time(nullptr);
    struct tm* lt = localtime(&now);
    snprintf(buf, sizeof(buf), "%02d:%02d:%02d", lt->tm_hour, lt->tm_min, lt->tm_sec);
    DrawText(buf, WIN_W - 90, 12, 14, Palette::TEXT_DIM);
}

// -------------------------------------------------------
// Toast notifications
// -------------------------------------------------------
static void pushToast(AppState& s, const std::string& msg, Color color) {
    s.toasts.push_back({ msg, color, 3.0f });
}

static void drawToasts(AppState& s, float dt) {
    float y = WIN_H - 60.0f;
    for (auto it = s.toasts.begin(); it != s.toasts.end(); ) {
        it->life -= dt;
        if (it->life <= 0.0f) { it = s.toasts.erase(it); continue; }

        const float alpha = std::min(it->life, 1.0f);
        const int   tw    = MeasureText(it->message.c_str(), 15) + 24;
        const int   tx    = WIN_W - tw - 16;
        DrawRectangleRounded({ (float)tx, y - 14, (float)tw, 30 },
                             0.3f, 8, withAlpha(Palette::BG_PANEL, (unsigned char)(alpha * 230)));
        DrawRectangleRoundedLines({ (float)tx, y - 14, (float)tw, 30 },
                                  0.3f, 8, 1.0f, withAlpha(it->color, (unsigned char)(alpha * 200)));
        DrawText(it->message.c_str(), tx + 12, (int)y - 7, 15,
                 withAlpha(Palette::TEXT_BRIGHT, (unsigned char)(alpha * 255)));

        y -= 40.0f;
        ++it;
    }
}

// -------------------------------------------------------
// Panel / card primitives
// -------------------------------------------------------
static void drawPanel(float x, float y, float w, float h,
                      const char* title, Color borderColor)
{
    DrawRectangleRounded({x, y, w, h}, 0.04f, 8, Palette::BG_PANEL);
    DrawRectangleRoundedLines({x, y, w, h}, 0.04f, 8, 1.5f, borderColor);
    if (title) {
        DrawText(title, (int)(x + 16), (int)(y + 14), 17, Palette::ACCENT);
        DrawLine((int)(x + 1), (int)(y + 38), (int)(x + w - 1), (int)(y + 38),
                 withAlpha(Palette::ACCENT, 60));
    }
}

static void drawGlowLine(float x1, float y1, float x2, float y2,
                         Color color, float /*thickness*/)
{
    DrawLine((int)x1, (int)y1, (int)x2, (int)y2, withAlpha(color, 80));
    DrawLine((int)x1, (int)(y1 + 1), (int)x2, (int)(y2 + 1), withAlpha(color, 40));
}

static void drawMetricCard(float x, float y, float w, float h,
                           const char* label, const char* value, Color accent)
{
    DrawRectangleRounded({x, y, w, h}, 0.08f, 8, Palette::BG_CARD);
    DrawRectangleRoundedLines({x, y, w, h}, 0.08f, 8, 1.5f, withAlpha(accent, 120));
    // accent strip on top
    DrawRectangleRounded({x, y, w, 4}, 0.5f, 4, withAlpha(accent, 180));

    DrawText(label, (int)(x + 12), (int)(y + 18), 13, Palette::TEXT_DIM);
    DrawText(value, (int)(x + 12), (int)(y + 38), 20, Palette::TEXT_BRIGHT);
}

// -------------------------------------------------------
// Animated button
// -------------------------------------------------------
static Button makeButton(float x, float y, float w, float h,
                         const std::string& label, Color color) {
    return { { x, y, w, h }, label, color, 0.0f, false };
}

static bool drawButton(Button& btn, float dt) {
    const bool hover   = CheckCollisionPointRec(GetMousePosition(), btn.bounds);
    const bool clicked = hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    // Lerp hover animation
    const float target = hover ? 1.0f : 0.0f;
    btn.hoverAnim += (target - btn.hoverAnim) * dt * 10.0f;
    const float h = btn.hoverAnim;

    // Background
    Color bg = lerpColor(withAlpha(btn.baseColor, 30),
                         withAlpha(btn.baseColor, 80), h);
    DrawRectangleRounded(btn.bounds, 0.15f, 8, bg);

    // Border
    Color border = lerpColor(withAlpha(btn.baseColor, 100),
                             btn.baseColor, h);
    DrawRectangleRoundedLines(btn.bounds, 0.15f, 8, 1.5f, border);

    // Glow on hover
    if (h > 0.05f) {
        DrawRectangleRoundedLines(
            { btn.bounds.x - 1, btn.bounds.y - 1,
              btn.bounds.width + 2, btn.bounds.height + 2 },
            0.15f, 8, 1.0f, withAlpha(btn.baseColor, (unsigned char)(h * 60)));
    }

    // Label
    const int tw = MeasureText(btn.label.c_str(), 16);
    const int tx = (int)(btn.bounds.x + (btn.bounds.width  - tw) * 0.5f);
    const int ty = (int)(btn.bounds.y + (btn.bounds.height - 16) * 0.5f);
    Color textColor = lerpColor(btn.baseColor, Palette::TEXT_BRIGHT, h);
    DrawText(btn.label.c_str(), tx, ty, 16, textColor);

    return clicked;
}

// -------------------------------------------------------
// Screen transitions (fade-to-black)
// -------------------------------------------------------
static void beginTransition(AppState& s, Screen next) {
    if (s.transitioning) return;
    s.transitioning = true;
    s.nextScreen    = next;
    s.transitionAlpha = 0.0f;
}

static void updateTransition(AppState& s, float dt) {
    if (!s.transitioning) return;
    const float speed = 4.0f;
    if (s.transitionAlpha < 1.0f) {
        s.transitionAlpha += dt * speed;
    } else {
        s.currentScreen   = s.nextScreen;
        s.transitionAlpha -= dt * speed;
        if (s.transitionAlpha <= 0.0f) {
            s.transitionAlpha = 0.0f;
            s.transitioning   = false;
        }
    }
    // Black overlay
    DrawRectangle(0, 0, WIN_W, WIN_H,
                  withAlpha(BLACK, (unsigned char)(s.transitionAlpha * 255)));
}

// -------------------------------------------------------
// SPLASH SCREEN
// -------------------------------------------------------
static void drawSplash(AppState& s, float dt) {
    s.splashTimer += dt;

    // Animated logo text
    const float pulse = 0.5f + 0.5f * std::sin(s.splashTimer * 3.0f);
    Color logoColor = withAlpha(Palette::ACCENT, (unsigned char)(160 + pulse * 90));

    DrawText("BOTEV", WIN_W / 2 - MeasureText("BOTEV", 72) / 2,
             WIN_H / 2 - 90, 72, logoColor);
    DrawText("INVENTORY SYSTEM", WIN_W / 2 - MeasureText("INVENTORY SYSTEM", 22) / 2,
             WIN_H / 2 + 0, 22, Palette::TEXT_DIM);
    DrawText("v2.0  —  Raylib Edition",
             WIN_W / 2 - MeasureText("v2.0  —  Raylib Edition", 14) / 2,
             WIN_H / 2 + 34, 14, withAlpha(Palette::TEXT_DIM, 120));

    // Loading bar
    const float BAR_W = 320.0f;
    const float BAR_H = 4.0f;
    const float bx = (WIN_W - BAR_W) * 0.5f;
    const float by = WIN_H * 0.5f + 80.0f;
    DrawRectangle((int)bx, (int)by, (int)BAR_W, (int)BAR_H, withAlpha(Palette::BORDER, 100));
    const float fill = std::min(s.splashTimer / 2.0f, 1.0f);
    DrawRectangle((int)bx, (int)by, (int)(BAR_W * fill), (int)BAR_H, Palette::ACCENT);

    // Loading label
    const char* loadLabel = s.splashTimer < 0.5f ? "Initialising..."
                          : s.splashTimer < 1.0f ? "Loading products..."
                          : s.splashTimer < 1.5f ? "Building UI..."
                          :                        "Ready!";
    DrawText(loadLabel,
             WIN_W / 2 - MeasureText(loadLabel, 13) / 2,
             (int)(by + 12), 13, Palette::TEXT_DIM);

    // Corner decorations
    drawGlowLine(0, 0, 80, 0, Palette::ACCENT); drawGlowLine(0, 0, 0, 80, Palette::ACCENT);
    drawGlowLine(WIN_W - 80, 0, WIN_W, 0, Palette::ACCENT2);
    drawGlowLine(WIN_W, 0, WIN_W, 80, Palette::ACCENT2);

    if (s.splashTimer >= 2.4f && !s.transitioning)
        beginTransition(s, Screen::MAIN_MENU);
}

// -------------------------------------------------------
// MAIN MENU
// -------------------------------------------------------
static void drawMainMenu(AppState& s, float dt) {
    // Sidebar panel
    drawPanel(30, 52, 280, WIN_H - 72, "MAIN MENU");

    static std::vector<Button> menuBtns;
    if (menuBtns.empty()) {
        const float bx = 50.0f, bw = 240.0f, bh = 46.0f;
        float by = 110.0f;
        menuBtns = {
            makeButton(bx, by,       bw, bh, "[ View Products ]",  Palette::ACCENT),
            makeButton(bx, by + 56,  bw, bh, "[ Add Product ]",    Palette::SUCCESS),
            makeButton(bx, by + 112, bw, bh, "[ Remove Product ]", Palette::DANGER),
            makeButton(bx, by + 168, bw, bh, "[ Sort Products ]",  Palette::ACCENT2),
            makeButton(bx, by + 224, bw, bh, "[ Search ]",         Palette::WARNING),
            makeButton(bx, by + 280, bw, bh, "[ Statistics ]",     Palette::ACCENT),
            makeButton(bx, by + 336, bw, bh, "[ Settings ]",       Palette::TEXT_DIM),
        };
    }

    const Screen screens[] = {
        Screen::VIEW_PRODUCTS, Screen::ADD_PRODUCT, Screen::REMOVE_PRODUCT,
        Screen::SORT_MENU,     Screen::SEARCH,      Screen::STATISTICS,
        Screen::SETTINGS
    };
    for (int i = 0; i < (int)menuBtns.size(); ++i) {
        if (drawButton(menuBtns[i], dt))
            beginTransition(s, screens[i]);
    }

    // Right panel: quick preview
    drawPanel(330, 52, WIN_W - 360, WIN_H - 72, "INVENTORY OVERVIEW");

    // Metric cards row
    const int count   = (int)s.products.size();
    const double total = calcTotalValue(s.products);
    const int low     = countLowStock(s.products, LOW_STOCK_THRESHOLD);

    char vbuf[64];
    snprintf(vbuf, sizeof(vbuf), "%d items", count);
    drawMetricCard(350, 100, 185, 80, "TOTAL PRODUCTS", vbuf, Palette::ACCENT);

    snprintf(vbuf, sizeof(vbuf), "%.2f BGN", total);
    drawMetricCard(550, 100, 210, 80, "INVENTORY VALUE", vbuf, Palette::SUCCESS);

    snprintf(vbuf, sizeof(vbuf), "%d items", low);
    drawMetricCard(776, 100, 185, 80, "LOW STOCK", vbuf, low > 0 ? Palette::DANGER : Palette::SUCCESS);

    snprintf(vbuf, sizeof(vbuf), "%.2f BGN", averagePrice(s.products));
    drawMetricCard(976, 100, 185, 80, "AVG PRICE", vbuf, Palette::ACCENT2);

    // Mini product list preview (last 8)
    const int startY = 205;
    DrawText("RECENT PRODUCTS", 350, startY, 13, Palette::TEXT_DIM);
    DrawLine(350, startY + 20, WIN_W - 32, startY + 20, withAlpha(Palette::BORDER, 180));

    const int maxRows = 12;
    const int startIdx = std::max(0, (int)s.products.size() - maxRows);
    for (int i = startIdx; i < (int)s.products.size(); ++i) {
        const Product& p = s.products[i];
        const int row = i - startIdx;
        const int ry  = startY + 28 + row * 32;

        // Row bg alternating
        if (row % 2 == 0)
            DrawRectangle(350, ry - 2, WIN_W - 382, 30, withAlpha(Palette::BG_CARD, 80));

        Color rowColor = p.isLowStock() ? Palette::WARNING : Palette::TEXT_BRIGHT;

        char rbuf[128];
        snprintf(rbuf, sizeof(rbuf), "#%d", p.id);
        DrawText(rbuf, 358, ry + 6, 13, Palette::TEXT_DIM);

        snprintf(rbuf, sizeof(rbuf), "%s", p.name.c_str());
        DrawText(rbuf, 410, ry + 6, 14, rowColor);

        snprintf(rbuf, sizeof(rbuf), "%.2f BGN", p.price);
        DrawText(rbuf, 750, ry + 6, 13, Palette::TEXT_DIM);

        snprintf(rbuf, sizeof(rbuf), "Qty: %d", p.quantity);
        Color qColor = p.isLowStock() ? Palette::DANGER : Palette::SUCCESS;
        DrawText(rbuf, 900, ry + 6, 13, qColor);

        if (p.isLowStock())
            DrawText("[LOW]", 980, ry + 6, 12, Palette::DANGER);
    }
}

// -------------------------------------------------------
// VIEW PRODUCTS screen
// -------------------------------------------------------
static void drawViewProducts(AppState& s, float dt) {
    drawPanel(30, 52, WIN_W - 60, WIN_H - 72, "ALL PRODUCTS");

    static Button backBtn = makeButton(50, 70, 110, 30, "< BACK", Palette::TEXT_DIM);
    if (drawButton(backBtn, dt)) beginTransition(s, Screen::MAIN_MENU);

    // Column headers
    const int HY = 110;
    DrawText("ID",       60,  HY, 14, Palette::ACCENT);
    DrawText("NAME",     110, HY, 14, Palette::ACCENT);
    DrawText("PRICE",    540, HY, 14, Palette::ACCENT);
    DrawText("QTY",      680, HY, 14, Palette::ACCENT);
    DrawText("VALUE",    780, HY, 14, Palette::ACCENT);
    DrawText("STATUS",   920, HY, 14, Palette::ACCENT);
    DrawText("CATEGORY", 1030, HY, 14, Palette::ACCENT);
    DrawLine(50, HY + 20, WIN_W - 50, HY + 20, withAlpha(Palette::ACCENT, 80));

    if (s.products.empty()) {
        DrawText("No products in inventory.", WIN_W / 2 - 120, WIN_H / 2, 18, Palette::TEXT_DIM);
        return;
    }

    // Smooth scroll
    const float scrollSpeed = 120.0f;
    if (IsKeyDown(KEY_DOWN)) s.tableScrollTarget += scrollSpeed * dt;
    if (IsKeyDown(KEY_UP))   s.tableScrollTarget -= scrollSpeed * dt;
    s.tableScrollTarget = std::max(0.0f, s.tableScrollTarget);
    s.tableScroll += (s.tableScrollTarget - s.tableScroll) * dt * 12.0f;

    const int ROW_H   = 34;
    const int startY  = 140;
    const int visRows = (WIN_H - startY - 40) / ROW_H;

    // Clamp scroll
    const int maxScroll = std::max(0, (int)s.products.size() - visRows) * ROW_H;
    s.tableScrollTarget = std::min(s.tableScrollTarget, (float)maxScroll);

    const int startIdx = (int)(s.tableScroll / ROW_H);

    for (int i = startIdx; i < (int)s.products.size(); ++i) {
        const Product& p  = s.products[i];
        const int row     = i - startIdx;
        const int ry      = startY + row * ROW_H;
        if (ry > WIN_H - 50) break;

        // Row highlight on hover
        const Rectangle rowRect = { 50, (float)ry - 2, WIN_W - 100.0f, (float)ROW_H };
        const bool hovered = CheckCollisionPointRec(GetMousePosition(), rowRect);

        Color rowBg = (row % 2 == 0)
            ? withAlpha(Palette::BG_CARD, 60)
            : withAlpha(Palette::BG_DARK, 40);
        if (hovered) rowBg = withAlpha(Palette::ACCENT, 20);
        DrawRectangleRec(rowRect, rowBg);

        Color rowColor = p.isLowStock() ? Palette::WARNING : Palette::TEXT_BRIGHT;

        char buf[64];
        snprintf(buf, sizeof(buf), "%d", p.id);
        DrawText(buf, 60, ry + 8, 14, Palette::TEXT_DIM);

        DrawText(p.name.c_str(), 110, ry + 8, 14, rowColor);

        snprintf(buf, sizeof(buf), "%.2f", p.price);
        DrawText(buf, 540, ry + 8, 14, Palette::TEXT_BRIGHT);

        snprintf(buf, sizeof(buf), "%d", p.quantity);
        Color qColor = p.isLowStock() ? Palette::DANGER : Palette::SUCCESS;
        DrawText(buf, 680, ry + 8, 14, qColor);

        snprintf(buf, sizeof(buf), "%.2f BGN", p.lineValue());
        DrawText(buf, 780, ry + 8, 13, Palette::TEXT_DIM);

        if (p.isLowStock())
            DrawText("⚠ LOW", 920, ry + 8, 13, Palette::DANGER);
        else
            DrawText("✓ OK",  920, ry + 8, 13, Palette::SUCCESS);

        DrawText(categoryToString(p.category).c_str(), 1030, ry + 8, 13, Palette::ACCENT2);
    }

    // Scroll indicator
    if ((int)s.products.size() > visRows) {
        const float barH = (float)visRows / s.products.size() * (WIN_H - startY - 50);
        const float barY = startY + (s.tableScroll / maxScroll) * (WIN_H - startY - 50 - barH);
        DrawRectangle(WIN_W - 26, startY, 6, WIN_H - startY - 50, withAlpha(Palette::BORDER, 80));
        DrawRectangle(WIN_W - 26, (int)barY, 6, (int)barH, Palette::ACCENT);
    }

    // Footer
    char footer[80];
    snprintf(footer, sizeof(footer), "↑/↓ to scroll  |  %d product(s)", (int)s.products.size());
    DrawText(footer, 50, WIN_H - 30, 12, Palette::TEXT_DIM);
}

// -------------------------------------------------------
// ADD PRODUCT screen
// -------------------------------------------------------
static void drawAddProduct(AppState& s, float dt) {
    const float PW = 520.0f, PH = 440.0f;
    const float PX = (WIN_W - PW) * 0.5f;
    const float PY = (WIN_H - PH) * 0.5f;

    drawPanel(PX, PY, PW, PH, "ADD NEW PRODUCT");

    static Button backBtn   = makeButton(PX + 10, PY + 8, 80, 28, "< BACK", Palette::TEXT_DIM);
    static Button addBtn    = makeButton(PX + PW * 0.5f - 90, PY + PH - 60, 180, 42, "ADD PRODUCT", Palette::SUCCESS);

    if (drawButton(backBtn, dt)) {
        memset(s.nameBuf, 0, sizeof(s.nameBuf));
        memset(s.priceBuf, 0, sizeof(s.priceBuf));
        memset(s.qtyBuf, 0, sizeof(s.qtyBuf));
        s.formError.clear(); s.activeField = 0;
        beginTransition(s, Screen::MAIN_MENU);
    }

    const float FX = PX + 30.0f;
    const float FW = PW - 60.0f;
    float FY = PY + 60.0f;
    const int FONT = 15;

    // Helper: draw labelled text field
    auto drawField = [&](const char* label, char* buf, int bufsz,
                         int fieldIdx, const char* hint) {
        const bool active = (s.activeField == fieldIdx);
        DrawText(label, (int)FX, (int)FY, 13, Palette::TEXT_DIM);
        FY += 20.0f;
        DrawRectangleRounded({FX, FY, FW, 36}, 0.1f, 4,
                             active ? withAlpha(Palette::ACCENT, 30) : withAlpha(Palette::BG_CARD, 200));
        DrawRectangleRoundedLines({FX, FY, FW, 36}, 0.1f, 4, 1.5f,
                                  active ? Palette::ACCENT : Palette::BORDER);

        if (active && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            // Keep active if clicked inside
        }
        if (CheckCollisionPointRec(GetMousePosition(), {FX, FY, FW, 36})
            && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            s.activeField = fieldIdx;

        const char* display = (buf[0] == '\0' && !active) ? hint : buf;
        Color tc = (buf[0] == '\0' && !active) ? Palette::TEXT_DIM : Palette::TEXT_BRIGHT;
        DrawText(display, (int)(FX + 10), (int)(FY + 9), FONT, tc);

        // Blinking cursor
        if (active && (int)(GetTime() * 2) % 2 == 0) {
            const int cw = MeasureText(buf, FONT);
            DrawText("|", (int)(FX + 10 + cw), (int)(FY + 9), FONT, Palette::ACCENT);
        }

        // Keyboard input
        if (active) {
            int key = GetCharPressed();
            while (key > 0) {
                const int len = (int)strlen(buf);
                if (len < bufsz - 1 && key >= 32) {
                    buf[len] = (char)key; buf[len + 1] = '\0';
                }
                key = GetCharPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE)) {
                const int len = (int)strlen(buf);
                if (len > 0) buf[len - 1] = '\0';
            }
            if (IsKeyPressed(KEY_TAB)) s.activeField = (fieldIdx + 1) % 3;
        }
        FY += 50.0f;
    };

    drawField("Product Name", s.nameBuf,  sizeof(s.nameBuf),  0, "e.g. Apple Juice");
    drawField("Price (BGN)",  s.priceBuf, sizeof(s.priceBuf), 1, "e.g. 1.99");
    drawField("Quantity",     s.qtyBuf,   sizeof(s.qtyBuf),   2, "e.g. 50");

    // Category chooser
    DrawText("Category", (int)FX, (int)FY, 13, Palette::TEXT_DIM);
    FY += 20.0f;
    const char* cats[] = { "FOOD", "DRINK", "DAIRY", "BAKERY", "OTHER" };
    float cx = FX;
    for (int i = 0; i < 5; ++i) {
        const bool sel = (s.catIndex == i);
        const int tw = MeasureText(cats[i], 13) + 16;
        DrawRectangleRounded({cx, FY, (float)tw, 28}, 0.3f, 4,
                             sel ? withAlpha(Palette::ACCENT2, 120) : withAlpha(Palette::BG_CARD, 180));
        DrawRectangleRoundedLines({cx, FY, (float)tw, 28}, 0.3f, 4, 1.5f,
                                  sel ? Palette::ACCENT2 : Palette::BORDER);
        DrawText(cats[i], (int)(cx + 8), (int)(FY + 7), 13,
                 sel ? Palette::TEXT_BRIGHT : Palette::TEXT_DIM);
        if (CheckCollisionPointRec(GetMousePosition(), {cx, FY, (float)tw, 28})
            && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            s.catIndex = i;
        cx += tw + 8;
    }

    // Error / success message
    if (!s.formError.empty())
        DrawText(s.formError.c_str(), (int)FX, (int)(PY + PH - 75), 13, Palette::DANGER);

    if (drawButton(addBtn, dt)) {
        std::string err;
        const Category cat = static_cast<Category>(s.catIndex);
        const double price  = atof(s.priceBuf);
        const int    qty    = atoi(s.qtyBuf);

        if (addNewProduct(s.products, s.nameBuf, price, qty, cat, err)) {
            pushToast(s, std::string("Added: ") + s.nameBuf, Palette::SUCCESS);
            saveProducts(s.products);
            memset(s.nameBuf, 0, sizeof(s.nameBuf));
            memset(s.priceBuf, 0, sizeof(s.priceBuf));
            memset(s.qtyBuf, 0, sizeof(s.qtyBuf));
            s.formError.clear(); s.activeField = 0;
        } else {
            s.formError = err;
        }
    }
}

// -------------------------------------------------------
// REMOVE PRODUCT screen
// -------------------------------------------------------
static void drawRemoveProduct(AppState& s, float dt) {
    const float PW = 420.0f, PH = 280.0f;
    const float PX = (WIN_W - PW) * 0.5f;
    const float PY = (WIN_H - PH) * 0.5f;

    drawPanel(PX, PY, PW, PH, "REMOVE PRODUCT", Palette::DANGER);

    static Button backBtn   = makeButton(PX + 10, PY + 8, 80, 28, "< BACK",  Palette::TEXT_DIM);
    static Button removeBtn = makeButton(PX + PW * 0.5f - 80, PY + PH - 60, 160, 40, "REMOVE", Palette::DANGER);

    if (drawButton(backBtn, dt)) {
        memset(s.removeIdBuf, 0, sizeof(s.removeIdBuf));
        s.removeMsg.clear();
        beginTransition(s, Screen::MAIN_MENU);
    }

    const float FX = PX + 30.0f, FW = PW - 60.0f;
    const float FY1 = PY + 70.0f;

    DrawText("Enter Product ID to delete:", (int)FX, (int)FY1, 14, Palette::TEXT_DIM);

    const bool fieldActive = true;
    DrawRectangleRounded({FX, FY1 + 22, FW, 38}, 0.1f, 4,
                         withAlpha(Palette::DANGER, 20));
    DrawRectangleRoundedLines({FX, FY1 + 22, FW, 38}, 0.1f, 4, 1.5f, Palette::DANGER);
    DrawText(s.removeIdBuf, (int)(FX + 10), (int)(FY1 + 31), 16, Palette::TEXT_BRIGHT);

    // Input
    int key = GetCharPressed();
    while (key > 0) {
        const int len = (int)strlen(s.removeIdBuf);
        if (len < 10 && key >= '0' && key <= '9') {
            s.removeIdBuf[len] = (char)key; s.removeIdBuf[len + 1] = '\0';
        }
        key = GetCharPressed();
    }
    if (IsKeyPressed(KEY_BACKSPACE)) {
        const int len = (int)strlen(s.removeIdBuf);
        if (len > 0) s.removeIdBuf[len - 1] = '\0';
    }

    // Preview
    if (strlen(s.removeIdBuf) > 0) {
        const int id = atoi(s.removeIdBuf);
        const Product* found = searchById(s.products, id);
        // Binary search needs sorted list; fallback to linear
        found = nullptr;
        for (auto& p : s.products) if (p.id == id) { found = &p; break; }

        if (found) {
            char info[128];
            snprintf(info, sizeof(info), "Found: %s  (%.2f BGN, Qty: %d)",
                     found->name.c_str(), found->price, found->quantity);
            DrawText(info, (int)FX, (int)(FY1 + 72), 13, Palette::WARNING);
        } else {
            DrawText("ID not found in inventory.", (int)FX, (int)(FY1 + 72), 13, Palette::DANGER);
        }
    }

    if (!s.removeMsg.empty())
        DrawText(s.removeMsg.c_str(), (int)FX, (int)(PY + PH - 70), 13, Palette::DANGER);

    if (drawButton(removeBtn, dt) && strlen(s.removeIdBuf) > 0) {
        const int id = atoi(s.removeIdBuf);
        // find name before delete
        std::string dname;
        for (auto& p : s.products) if (p.id == id) { dname = p.name; break; }

        if (deleteProduct(s.products, id)) {
            saveProducts(s.products);
            pushToast(s, "Removed: " + dname, Palette::DANGER);
            memset(s.removeIdBuf, 0, sizeof(s.removeIdBuf));
            s.removeMsg.clear();
        } else {
            s.removeMsg = "No product with ID " + std::string(s.removeIdBuf);
        }
    }
}

// -------------------------------------------------------
// SORT MENU screen
// -------------------------------------------------------
static void drawSortMenu(AppState& s, float dt) {
    const float PW = 400.0f, PH = 340.0f;
    const float PX = (WIN_W - PW) * 0.5f;
    const float PY = (WIN_H - PH) * 0.5f;

    drawPanel(PX, PY, PW, PH, "SORT PRODUCTS", Palette::ACCENT2);

    static Button backBtn = makeButton(PX + 10, PY + 8, 80, 28, "< BACK", Palette::TEXT_DIM);
    if (drawButton(backBtn, dt)) beginTransition(s, Screen::MAIN_MENU);

    static std::vector<Button> sortBtns;
    if (sortBtns.empty()) {
        const float bx = PX + 40, bw = PW - 80, bh = 44;
        sortBtns = {
            makeButton(bx, PY + 80,  bw, bh, "Sort by Price     (Bubble ↑)", Palette::ACCENT),
            makeButton(bx, PY + 136, bw, bh, "Sort by Quantity  (Bubble ↑)", Palette::WARNING),
            makeButton(bx, PY + 192, bw, bh, "Sort by Name      (Bubble A→Z)", Palette::ACCENT2),
        };
    }

    if (drawButton(sortBtns[0], dt)) {
        sortByPrice(s.products);
        saveProducts(s.products);
        pushToast(s, "Sorted by price.", Palette::ACCENT);
        beginTransition(s, Screen::VIEW_PRODUCTS);
    }
    if (drawButton(sortBtns[1], dt)) {
        sortByQuantity(s.products);
        saveProducts(s.products);
        pushToast(s, "Sorted by quantity.", Palette::WARNING);
        beginTransition(s, Screen::VIEW_PRODUCTS);
    }
    if (drawButton(sortBtns[2], dt)) {
        sortByName(s.products);
        saveProducts(s.products);
        pushToast(s, "Sorted by name.", Palette::ACCENT2);
        beginTransition(s, Screen::VIEW_PRODUCTS);
    }

    DrawText("Results will open in View Products screen.",
             (int)(PX + 20), (int)(PY + PH - 35), 12, Palette::TEXT_DIM);
}

// -------------------------------------------------------
// SEARCH screen
// -------------------------------------------------------
static void drawSearch(AppState& s, float dt) {
    drawPanel(30, 52, WIN_W - 60, WIN_H - 72, "SEARCH PRODUCTS");

    static Button backBtn = makeButton(50, 70, 110, 30, "< BACK", Palette::TEXT_DIM);
    if (drawButton(backBtn, dt)) {
        memset(s.searchBuf, 0, sizeof(s.searchBuf));
        s.searchResults.clear(); s.searchDone = false;
        beginTransition(s, Screen::MAIN_MENU);
    }

    // Search bar
    const float SX = 50.0f, SW = WIN_W - 200.0f;
    DrawText("Search by name:", (int)SX, 110, 13, Palette::TEXT_DIM);
    DrawRectangleRounded({SX, 128, SW, 40}, 0.1f, 4, withAlpha(Palette::BG_CARD, 200));
    DrawRectangleRoundedLines({SX, 128, SW, 40}, 0.1f, 4, 1.5f, Palette::ACCENT);
    DrawText(s.searchBuf, (int)(SX + 14), 138, 16, Palette::TEXT_BRIGHT);
    if ((int)(GetTime() * 2) % 2 == 0) {
        int cw = MeasureText(s.searchBuf, 16);
        DrawText("|", (int)(SX + 14 + cw), 138, 16, Palette::ACCENT);
    }

    // Keyboard input
    int key = GetCharPressed();
    while (key > 0) {
        const int len = (int)strlen(s.searchBuf);
        if (len < 127 && key >= 32) {
            s.searchBuf[len] = (char)key; s.searchBuf[len + 1] = '\0';
        }
        key = GetCharPressed();
    }
    if (IsKeyPressed(KEY_BACKSPACE)) {
        const int len = (int)strlen(s.searchBuf);
        if (len > 0) { s.searchBuf[len - 1] = '\0'; s.searchDone = false; }
    }

    // Search button
    static Button searchBtn = makeButton(WIN_W - 140.0f, 128, 110, 40, "SEARCH", Palette::ACCENT);
    if (drawButton(searchBtn, dt) || IsKeyPressed(KEY_ENTER)) {
        if (strlen(s.searchBuf) > 0) {
            s.searchResults = searchByName(s.products, s.searchBuf);
            s.searchDone = true;
        }
    }

    // Results
    if (s.searchDone) {
        char hdr[80];
        snprintf(hdr, sizeof(hdr), "Results for \"%s\"  (%d found)",
                 s.searchBuf, (int)s.searchResults.size());
        DrawText(hdr, (int)SX, 186, 14, Palette::TEXT_DIM);
        DrawLine((int)SX, 206, WIN_W - 50, 206, withAlpha(Palette::ACCENT, 60));

        if (s.searchResults.empty()) {
            DrawText("No products found.", WIN_W / 2 - 90, WIN_H / 2, 18, Palette::DANGER);
        } else {
            for (int i = 0; i < (int)s.searchResults.size(); ++i) {
                const Product& p = s.searchResults[i];
                const int ry = 216 + i * 34;
                if (ry > WIN_H - 50) break;

                if (i % 2 == 0) DrawRectangle(50, ry - 2, WIN_W - 100, 32, withAlpha(Palette::BG_CARD, 60));

                char buf[128];
                snprintf(buf, sizeof(buf), "#%d", p.id);
                DrawText(buf, 58, ry + 7, 13, Palette::TEXT_DIM);
                DrawText(p.name.c_str(), 100, ry + 7, 15, Palette::TEXT_BRIGHT);
                snprintf(buf, sizeof(buf), "%.2f BGN", p.price);
                DrawText(buf, 600, ry + 7, 13, Palette::TEXT_DIM);
                snprintf(buf, sizeof(buf), "Qty: %d", p.quantity);
                DrawText(buf, 780, ry + 7, 13, p.isLowStock() ? Palette::DANGER : Palette::SUCCESS);
            }
        }
    } else {
        DrawText("Type a name above and press SEARCH or ENTER.",
                 (int)SX, 200, 14, Palette::TEXT_DIM);
    }
}

// -------------------------------------------------------
// STATISTICS screen
// -------------------------------------------------------
static void drawStatistics(AppState& s, float dt) {
    s.statsAnim = std::min(s.statsAnim + dt * 0.8f, 1.0f);

    drawPanel(30, 52, WIN_W - 60, WIN_H - 72, "STATISTICS");

    static Button backBtn = makeButton(50, 70, 110, 30, "< BACK", Palette::TEXT_DIM);
    if (drawButton(backBtn, dt)) { s.statsAnim = 0.0f; beginTransition(s, Screen::MAIN_MENU); }

    const int count    = (int)s.products.size();
    const double total = calcTotalValue(s.products);
    const int low      = countLowStock(s.products, LOW_STOCK_THRESHOLD);
    const double avg   = averagePrice(s.products);

    char vbuf[64];

    // Metric row
    snprintf(vbuf, sizeof(vbuf), "%d", count);
    drawMetricCard( 50, 110, 200, 90, "TOTAL PRODUCTS",  vbuf, Palette::ACCENT);
    snprintf(vbuf, sizeof(vbuf), "%.2f BGN", total);
    drawMetricCard(270, 110, 220, 90, "TOTAL VALUE",     vbuf, Palette::SUCCESS);
    snprintf(vbuf, sizeof(vbuf), "%d items",  low);
    drawMetricCard(510, 110, 200, 90, "LOW STOCK",       vbuf, low > 0 ? Palette::DANGER : Palette::SUCCESS);
    snprintf(vbuf, sizeof(vbuf), "%.2f BGN", avg);
    drawMetricCard(730, 110, 200, 90, "AVERAGE PRICE",   vbuf, Palette::ACCENT2);

    const Product* pExp  = mostExpensive(s.products);
    const Product* pHigh = highestStock(s.products);
    snprintf(vbuf, sizeof(vbuf), "%s", pExp  ? pExp->name.c_str()  : "N/A");
    drawMetricCard(950, 110, 280, 90, "MOST EXPENSIVE",  vbuf, Palette::WARNING);

    // Bar chart: price per product (top 10)
    DrawText("PRODUCT VALUE CHART  (top 10)", 50, 220, 14, Palette::TEXT_DIM);
    DrawLine(50, 238, WIN_W - 50, 238, withAlpha(Palette::BORDER, 120));

    const int CHART_X = 50, CHART_Y = 245, CHART_W = WIN_W - 100, CHART_H = 260;
    const int maxBars = std::min(10, count);

    if (count == 0) {
        DrawText("No products to chart.", WIN_W / 2 - 100, WIN_H / 2, 16, Palette::TEXT_DIM);
    } else {
        // Find max line value for scale
        double maxVal = 1.0;
        for (auto& p : s.products) if (p.lineValue() > maxVal) maxVal = p.lineValue();

        const float barW  = (float)(CHART_W - 20) / maxBars - 6;
        const Color barColors[] = { Palette::ACCENT, Palette::ACCENT2, Palette::SUCCESS,
                                    Palette::WARNING, Palette::DANGER };

        for (int i = 0; i < maxBars && i < count; ++i) {
            const Product& p = s.products[i];
            const float frac = (float)(p.lineValue() / maxVal) * s.statsAnim;
            const float bh   = frac * (CHART_H - 40);
            const float bx   = CHART_X + i * (barW + 6) + 10;
            const float by   = CHART_Y + CHART_H - bh - 20;

            Color bc = barColors[i % 5];
            DrawRectangleRounded({bx, by, barW, bh}, 0.1f, 4, withAlpha(bc, 160));
            DrawRectangleRoundedLines({bx, by, barW, bh}, 0.1f, 4, 1.0f, bc);

            // Value label on top
            if (bh > 20.0f) {
                char lbuf[16];
                snprintf(lbuf, sizeof(lbuf), "%.0f", p.lineValue());
                DrawText(lbuf, (int)(bx + barW / 2 - MeasureText(lbuf, 11) / 2),
                         (int)(by - 14), 11, bc);
            }

            // Product name below (truncated)
            char nameShort[12] = {};
            strncpy(nameShort, p.name.c_str(), 9);
            if (p.name.size() > 9) { nameShort[9] = '.'; nameShort[10] = '.'; }
            DrawText(nameShort,
                     (int)(bx + barW / 2 - MeasureText(nameShort, 10) / 2),
                     CHART_Y + CHART_H - 16, 10, Palette::TEXT_DIM);
        }

        // Y-axis label
        char ybuf[32];
        snprintf(ybuf, sizeof(ybuf), "%.0f BGN", maxVal);
        DrawText(ybuf, CHART_X - 5, CHART_Y, 11, Palette::TEXT_DIM);
        DrawText("0", CHART_X - 5, CHART_Y + CHART_H - 40, 11, Palette::TEXT_DIM);
    }
}

// -------------------------------------------------------
// SETTINGS screen
// -------------------------------------------------------
static void drawSettings(AppState& s, float dt) {
    const float PW = 500.0f, PH = 380.0f;
    const float PX = (WIN_W - PW) * 0.5f;
    const float PY = (WIN_H - PH) * 0.5f;

    drawPanel(PX, PY, PW, PH, "SETTINGS");

    static Button backBtn = makeButton(PX + 10, PY + 8, 80, 28, "< BACK", Palette::TEXT_DIM);
    if (drawButton(backBtn, dt)) beginTransition(s, Screen::MAIN_MENU);

    const float FX = PX + 30.0f;
    float FY = PY + 60.0f;

    // Helper: slider
    auto drawSlider = [&](const char* label, float& val) {
        DrawText(label, (int)FX, (int)FY, 14, Palette::TEXT_DIM);
        const float SX = FX + 200, SW = PW - 270.0f;
        DrawRectangle((int)SX, (int)(FY + 4), (int)SW, 6, withAlpha(Palette::BORDER, 120));
        const float filled = val * SW;
        DrawRectangle((int)SX, (int)(FY + 4), (int)filled, 6, Palette::ACCENT);
        DrawCircle((int)(SX + filled), (int)(FY + 7), 8, Palette::ACCENT);

        // Draggable
        const Rectangle sliderHit = { SX - 5, FY, SW + 10, 18 };
        if (CheckCollisionPointRec(GetMousePosition(), sliderHit)
            && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            val = std::max(0.0f, std::min(1.0f,
                (GetMousePosition().x - SX) / SW));
        }

        char vbuf[8];
        snprintf(vbuf, sizeof(vbuf), "%.0f%%", val * 100);
        DrawText(vbuf, (int)(SX + SW + 10), (int)FY, 13, Palette::TEXT_DIM);
        FY += 44.0f;
    };

    // Helper: toggle
    auto drawToggle = [&](const char* label, bool& val) {
        DrawText(label, (int)FX, (int)FY, 14, Palette::TEXT_DIM);
        const float TX = FX + 200, TW = 48, TH = 24;
        Color bgC = val ? withAlpha(Palette::ACCENT, 160) : withAlpha(Palette::BORDER, 120);
        DrawRectangleRounded({TX, FY - 2, TW, TH}, 0.5f, 8, bgC);
        const float knobX = val ? TX + TW - TH + 2 : TX + 2;
        DrawCircle((int)(knobX + TH * 0.5f - 2), (int)(FY + TH * 0.5f - 2), TH * 0.4f, WHITE);
        if (CheckCollisionPointRec(GetMousePosition(), {TX, FY - 2, TW, TH})
            && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            val = !val;
        FY += 44.0f;
    };

    drawSlider("Music Volume", s.musicVolume);
    drawSlider("SFX Volume",   s.sfxVolume);
    drawToggle("Particles",    s.particlesOn);
    drawToggle("Scanlines",    s.scanlines);

    DrawText("Settings are applied immediately and not persisted to disk.",
             (int)FX, (int)(PY + PH - 30), 11, withAlpha(Palette::TEXT_DIM, 120));
}

// -------------------------------------------------------
// Main application loop
// -------------------------------------------------------
void runApplication(std::vector<Product>& products) {
    InitWindow(WIN_W, WIN_H, "BOTEV Inventory System — Raylib Edition");
    SetTargetFPS(TARGET);

    AppState state{ products };
    initParticles(state);
    state.currentScreen = Screen::SPLASH;

    while (!WindowShouldClose()) {
        const float dt = GetFrameTime();

        // Update
        state.bgTime += dt;
        updateParticles(state, dt);

        BeginDrawing();
        ClearBackground(Palette::BG_DARK);

        drawBackground(state);

        // Route to current screen
        switch (state.currentScreen) {
            case Screen::SPLASH:         drawSplash(state, dt);         break;
            case Screen::MAIN_MENU:      drawMainMenu(state, dt);       break;
            case Screen::VIEW_PRODUCTS:  drawViewProducts(state, dt);   break;
            case Screen::ADD_PRODUCT:    drawAddProduct(state, dt);     break;
            case Screen::REMOVE_PRODUCT: drawRemoveProduct(state, dt);  break;
            case Screen::SORT_MENU:      drawSortMenu(state, dt);       break;
            case Screen::SEARCH:         drawSearch(state, dt);         break;
            case Screen::STATISTICS:     drawStatistics(state, dt);     break;
            case Screen::SETTINGS:       drawSettings(state, dt);       break;
        }

        // Overlays
        if (state.currentScreen != Screen::SPLASH) drawHUD(state);
        if (state.scanlines) drawScanlines();
        drawToasts(state, dt);
        updateTransition(state, dt);

        EndDrawing();
    }

    CloseWindow();
}
