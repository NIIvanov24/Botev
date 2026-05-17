
<style>
  * { box-sizing: border-box; margin: 0; padding: 0; }
  body { font-family: var(--font-mono, monospace); }
  .readme { padding: 1.5rem 0; color: var(--color-text-primary); }
  h1 { font-size: 26px; font-weight: 500; margin-bottom: 0.4rem; }
  .tagline { font-size: 14px; color: var(--color-text-secondary); margin-bottom: 1.5rem; }
  .badges { display: flex; flex-wrap: wrap; gap: 8px; margin-bottom: 1.75rem; }
  .badge { font-size: 12px; padding: 3px 10px; border-radius: 99px; border: 0.5px solid var(--color-border-tertiary); color: var(--color-text-secondary); background: var(--color-background-secondary); font-family: var(--font-mono); }
  .badge.blue { background: #E6F1FB; color: #0C447C; border-color: #85B7EB; }
  .badge.green { background: #EAF3DE; color: #27500A; border-color: #97C459; }
  .badge.amber { background: #FAEEDA; color: #633806; border-color: #EF9F27; }
  section { margin-bottom: 2rem; }
  h2 { font-size: 17px; font-weight: 500; margin-bottom: 1rem; padding-bottom: 6px; border-bottom: 0.5px solid var(--color-border-tertiary); }
  .role-grid { display: grid; grid-template-columns: repeat(auto-fit, minmax(140px, 1fr)); gap: 10px; }
  .role-card { background: var(--color-background-secondary); border-radius: var(--border-radius-md); padding: 12px 14px; border: 0.5px solid var(--color-border-tertiary); }
  .role-icon { font-size: 22px; margin-bottom: 6px; }
  .role-title { font-size: 12px; font-weight: 500; color: var(--color-text-primary); }
  .role-desc { font-size: 11px; color: var(--color-text-secondary); margin-top: 3px; line-height: 1.5; }
  .features { display: grid; grid-template-columns: 1fr 1fr; gap: 8px; }
  .feat { display: flex; align-items: flex-start; gap: 8px; padding: 10px 12px; background: var(--color-background-primary); border: 0.5px solid var(--color-border-tertiary); border-radius: var(--border-radius-md); }
  .feat-icon { font-size: 18px; flex-shrink: 0; }
  .feat-text { font-size: 12px; }
  .feat-title { font-weight: 500; color: var(--color-text-primary); }
  .feat-desc { color: var(--color-text-secondary); margin-top: 1px; line-height: 1.4; }
  .arch-diagram { background: var(--color-background-secondary); border-radius: var(--border-radius-lg); padding: 1.25rem; border: 0.5px solid var(--color-border-tertiary); font-family: var(--font-mono); font-size: 12px; }
  .arch-layer { border-radius: var(--border-radius-md); padding: 10px 14px; margin-bottom: 8px; display: flex; align-items: center; justify-content: space-between; }
  .arch-layer.pres { background: #E6F1FB; border: 0.5px solid #85B7EB; color: #0C447C; }
  .arch-layer.logic { background: #EEEDFE; border: 0.5px solid #AFA9EC; color: #3C3489; }
  .arch-layer.data { background: #EAF3DE; border: 0.5px solid #97C459; color: #27500A; }
  .arch-arrow { text-align: center; font-size: 16px; color: var(--color-text-secondary); margin: -2px 0; }
  .arch-label { font-size: 13px; font-weight: 500; }
  .arch-file { font-size: 11px; opacity: 0.75; }
  .rule-note { font-size: 11px; margin-top: 10px; color: var(--color-text-secondary); background: var(--color-background-primary); border-left: 2px solid #7F77DD; padding: 6px 10px; border-radius: 0 var(--border-radius-md) var(--border-radius-md) 0; }
  table { width: 100%; border-collapse: collapse; font-size: 12px; }
  th { text-align: left; font-weight: 500; font-size: 11px; color: var(--color-text-secondary); padding: 6px 10px; border-bottom: 0.5px solid var(--color-border-tertiary); }
  td { padding: 7px 10px; border-bottom: 0.5px solid var(--color-border-tertiary); color: var(--color-text-primary); vertical-align: middle; }
  tr:last-child td { border-bottom: none; }
  code { font-family: var(--font-mono); font-size: 11px; background: var(--color-background-secondary); padding: 2px 5px; border-radius: 4px; color: var(--color-text-secondary); }
  .algo-cat { display: inline-block; font-size: 10px; padding: 2px 7px; border-radius: 99px; margin-right: 4px; font-weight: 500; }
  .cat-sort { background: #EEEDFE; color: #3C3489; }
  .cat-search { background: #E6F1FB; color: #0C447C; }
  .cat-recurse { background: #EAF3DE; color: #27500A; }
  .build-block { background: var(--color-background-secondary); border: 0.5px solid var(--color-border-tertiary); border-radius: var(--border-radius-md); padding: 12px 14px; margin-bottom: 10px; }
  .build-label { font-size: 11px; font-weight: 500; color: var(--color-text-secondary); margin-bottom: 6px; }
  pre { font-size: 11px; color: var(--color-text-primary); font-family: var(--font-mono); line-height: 1.6; white-space: pre-wrap; }
  .sprint-row { display: flex; align-items: center; gap: 8px; padding: 8px 0; border-bottom: 0.5px solid var(--color-border-tertiary); font-size: 12px; }
  .sprint-row:last-child { border-bottom: none; }
  .sprint-dot { font-size: 14px; }
  .imgui-row { display: flex; align-items: center; gap: 10px; padding: 7px 0; border-bottom: 0.5px solid var(--color-border-tertiary); font-size: 12px; }
  .imgui-row:last-child { border-bottom: none; }
  .arrow-right { color: var(--color-text-secondary); font-size: 14px; flex-shrink: 0; }
</style>

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
