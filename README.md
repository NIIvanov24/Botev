

<div class="readme">
  <h1>📦 Inventory Management System</h1>
  <p class="tagline">A C++ console app (+ planned 🖥️ Dear ImGui GUI) for managing product inventory — built as a 9th-grade project following a three-tier architecture.</p>

  <div class="badges">
    <span class="badge blue">🛠️ C++17</span>
    <span class="badge green">📐 CMake 3.16+</span>
    <span class="badge amber">🏗️ Three-Tier Architecture</span>
    <span class="badge">🎓 9th Grade Project</span>
    <span class="badge">💾 File Persistence</span>
  </div>

  <section>
    <h2>👥 Team Roles</h2>
    <div class="role-grid">
      <div class="role-card">
        <div class="role-icon">🗂️</div>
        <div class="role-title">Scrum Master</div>
        <div class="role-desc">Sprint planning, GitHub Projects/Kanban, documentation</div>
      </div>
      <div class="role-card">
        <div class="role-icon">🧠</div>
        <div class="role-title">Back-End Dev 1</div>
        <div class="role-desc">Logic layer: sorting & searching algorithms</div>
      </div>
      <div class="role-card">
        <div class="role-icon">💽</div>
        <div class="role-title">Back-End Dev 2</div>
        <div class="role-desc">Data layer: file I/O & data structures</div>
      </div>
      <div class="role-card">
        <div class="role-icon">🎨</div>
        <div class="role-title">Front-End Dev</div>
        <div class="role-desc">Presentation layer: ImGui GUI integration</div>
      </div>
    </div>
  </section>

  <section>
    <h2>✨ Features</h2>
    <div class="features">
      <div class="feat"><div class="feat-icon">👁️</div><div class="feat-text"><div class="feat-title">View Products</div><div class="feat-desc">All products in a formatted table</div></div></div>
      <div class="feat"><div class="feat-icon">➕</div><div class="feat-text"><div class="feat-title">Add Products</div><div class="feat-desc">Add new products with validation</div></div></div>
      <div class="feat"><div class="feat-icon">🗑️</div><div class="feat-text"><div class="feat-title">Remove Products</div><div class="feat-desc">Remove any product by ID</div></div></div>
      <div class="feat"><div class="feat-icon">🔃</div><div class="feat-text"><div class="feat-title">Sort</div><div class="feat-desc">By price, quantity, or name (Bubble Sort)</div></div></div>
      <div class="feat"><div class="feat-icon">🔍</div><div class="feat-text"><div class="feat-title">Search</div><div class="feat-desc">By name, case-insensitive (Linear Search)</div></div></div>
      <div class="feat"><div class="feat-icon">📊</div><div class="feat-text"><div class="feat-title">Statistics</div><div class="feat-desc">Total value & low-stock count via recursion</div></div></div>
      <div class="feat"><div class="feat-icon">💾</div><div class="feat-text"><div class="feat-title">Persistent Storage</div><div class="feat-desc">Data saved to <code>assets/products.txt</code></div></div></div>
      <div class="feat"><div class="feat-icon">🖥️</div><div class="feat-text"><div class="feat-title">ImGui GUI</div><div class="feat-desc">Planned GUI integration (see below)</div></div></div>
    </div>
  </section>

  <section>
    <h2>🏗️ Architecture</h2>
    <div class="arch-diagram">
      <div class="arch-layer pres">
        <div><div class="arch-label">🖥️ Presentation Layer</div><div class="arch-file">presentation.h / presentation.cpp — UI & user input</div></div>
        <span>🎨</span>
      </div>
      <div class="arch-arrow">⬇️ calls</div>
      <div class="arch-layer logic">
        <div><div class="arch-label">🧠 Logic Layer</div><div class="arch-file">logic.h / logic.cpp — sorting, searching, recursion, validation</div></div>
        <span>⚙️</span>
      </div>
      <div class="arch-arrow">⬇️ calls</div>
      <div class="arch-layer data">
        <div><div class="arch-label">💽 Data Layer</div><div class="arch-file">data.h / data.cpp — file I/O & Product struct</div></div>
        <span>🗄️</span>
      </div>
      <div class="rule-note">🚫 The Presentation layer <strong>never</strong> accesses the Data layer directly.</div>
    </div>
  </section>

  <section>
    <h2>🧮 Algorithms</h2>
    <table>
      <thead><tr><th>Category</th><th>Algorithm</th><th>Location</th></tr></thead>
      <tbody>
        <tr><td><span class="algo-cat cat-sort">🔃 Sort</span></td><td>Bubble Sort (price)</td><td><code>sortByPrice()</code></td></tr>
        <tr><td><span class="algo-cat cat-sort">🔃 Sort</span></td><td>Bubble Sort (quantity)</td><td><code>sortByQuantity()</code></td></tr>
        <tr><td><span class="algo-cat cat-sort">🔃 Sort</span></td><td>Bubble Sort (name)</td><td><code>sortByName()</code></td></tr>
        <tr><td><span class="algo-cat cat-search">🔍 Search</span></td><td>Linear Search</td><td><code>searchByName()</code></td></tr>
        <tr><td><span class="algo-cat cat-search">🔍 Search</span></td><td>Binary Search</td><td><code>searchById()</code></td></tr>
        <tr><td><span class="algo-cat cat-recurse">♾️ Recursion</span></td><td>Total inventory value</td><td><code>calcTotalValue()</code></td></tr>
        <tr><td><span class="algo-cat cat-recurse">♾️ Recursion</span></td><td>Low-stock count</td><td><code>countLowStock()</code></td></tr>
      </tbody>
    </table>
  </section>

  <section>
    <h2>🔨 How to Build & Run</h2>
    <div class="build-block">
      <div class="build-label">✅ Requirements</div>
      <pre>🖥️  C++17 compiler (g++, clang++, MSVC)
📦  CMake 3.16+</pre>
    </div>
    <div class="build-block">
      <div class="build-label">🚀 Build with CMake</div>
      <pre>mkdir build && cd build
cmake ..
cmake --build .
./inventory</pre>
    </div>
    <div class="build-block">
      <div class="build-label">⚡ Build manually (g++)</div>
      <pre>g++ -std=c++17 -Iinclude src/main.cpp src/data.cpp \
    src/logic.cpp src/presentation.cpp -o inventory
./inventory</pre>
    </div>
  </section>

  <section>
    <h2>📋 Sprint Plan</h2>
    <div class="build-block">
      <div class="sprint-row"><span class="sprint-dot">📁</span><span>Sprint reports live in <code>docs/</code></span></div>
      <div class="sprint-row"><span class="sprint-dot">📌</span><span>GitHub Project Kanban tracks task progress</span></div>
      <div class="sprint-row"><span class="sprint-dot">➡️</span><span><strong>To Do</strong> → <strong>In Progress</strong> → <strong>Review</strong> → <strong>Done</strong></span></div>
    </div>
  </section>

  <section>
    <h2>🖼️ ImGui Integration (Planned)</h2>
    <p style="font-size:12px; color: var(--color-text-secondary); margin-bottom: 10px;">Console functions are designed as 1-to-1 replacements with ImGui windows:</p>
    <div class="build-block">
      <div class="imgui-row"><code>renderProductTable()</code><span class="arrow-right">→</span><span style="font-size:12px; color: var(--color-text-secondary);">📊 <code>ImGui::BeginTable</code> / <code>TableNextRow</code></span></div>
      <div class="imgui-row"><code>showMainMenu()</code><span class="arrow-right">→</span><span style="font-size:12px; color: var(--color-text-secondary);">📋 <code>ImGui::BeginMainMenuBar</code></span></div>
      <div class="imgui-row"><code>showAddProductForm()</code><span class="arrow-right">→</span><span style="font-size:12px; color: var(--color-text-secondary);">✏️ <code>InputText</code>, <code>InputDouble</code></span></div>
      <div class="imgui-row"><code>showSortMenu()</code><span class="arrow-right">→</span><span style="font-size:12px; color: var(--color-text-secondary);">🔽 <code>ImGui::BeginCombo</code></span></div>
      <div class="imgui-row"><code>showStatistics()</code><span class="arrow-right">→</span><span style="font-size:12px; color: var(--color-text-secondary);">📈 <code>ImGui::Text</code> in stats panel</span></div>
    </div>
    <p style="font-size:11px; color: var(--color-text-secondary); margin-top: 8px;">💡 See <code>CMakeLists.txt</code> for the commented-out ImGui build instructions.</p>
  </section>
</div>
