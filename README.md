# Cub3D - Advanced Raycasting Engine

A deep dive into raycasting optimization, computational geometry, and custom rendering systems built entirely from scratch.

## How to Run

```bash
cd src
make
./cub3d
```

---

## Project Goals

- **Learn & Advance Techniques**: Push beyond traditional raycasting implementations
- **Pure Linear Algebra**: All 3D effects achieved through 2D plane calculations only
- **No Feature Repetition**: Each system brings unique functionality—no redundant implementations

---

## Rendering Architecture - Dual Raycast Engine

The core of this engine is built on **two independent raycasting systems** working in harmony:

### Scene Renderer - Grid-Based DDA Raycasting
**Location:** [src/render/scene](src/render/scene)

Traditional grid-based raycasting for static world geometry (walls, floors, ceilings).

**How it works:**
```
Grid Map (top-down view):
┌─────────────┐
│ 1 1 1 1 1 1 │  1 = Wall
│ 1 0 0 0 0 1 │  0 = Empty space
│ 1 0 0 D 0 1 │  D = Door
│ 1 0 P → → 1 │  P = Player, → = Ray
│ 1 1 1 1 1 1 │
└─────────────┘

DDA Algorithm:
1. Ray starts at player position
2. Steps through grid cells
3. Checks each cell for walls
4. Stops at first wall hit
5. Calculates distance for wall height
```

**Renders:**
- Walls (textured, aligned to grid)
- Floors
- Ceilings
- Grid-based geometry

---

### Object Renderer - Segment-Based Line Intersection
**Location:** [src/render/objects](src/render/objects)

Free-form segment rendering using line intersection algorithms for dynamic and non-grid-aligned geometry.

**How it works:**
```
Each object represented as 2D segment:

Enemy (segment from point A to B):
    A ●━━━━━━━● B
    
Player casts ray:
P ───────────→ Ray
    
Line intersection formula:
If ray intersects segment AB:
    Calculate intersection point
    Calculate distance
    Project to 3D column on screen
```

**Renders:**
- Enemies (dynamic, move toward player)
- Fireballs (projectiles with direction)
- Orbs (rotate around player)
- Particles (trail effects)
- Doorwalls (non-axis-aligned segments)

---

### Why Two Engines?

**Different Geometry, Different Algorithms:**

| Feature | Scene (DDA) | Objects (Intersection) |
|---------|-------------|----------------------|
| **Geometry** | Grid-aligned walls | Free-form segments |
| **Position** | Fixed to grid cells | Arbitrary 2D coordinates |
| **Algorithm** | Step through grid | Ray-segment intersection math |
| **Use Case** | Static environment | Dynamic entities |
| **Performance** | Fast (grid optimization) | Flexible (any angle/position) |

**Unified Rendering Pipeline:**
```
For each screen column (x):
    1. Cast ray through scene (DDA)
       → Get wall hit + distance
    
    2. Cast same ray through all objects (line intersection)
       → Get object hits + distances
    
    3. Sort all hits by distance
    
    4. Render closest hit to screen column x
    
Result: Seamless integration of grid walls and free-form objects!
```

**Example Frame:**
```
Player view with both engines:

┌──────────────────────────┐
│  Wall  │ Enemy │  Wall   │  ← Scene engine renders walls
│ (DDA)  │(Inter)│ (DDA)   │  ← Object engine renders enemy
│        │   ●   │         │  ← Depth sorting determines visibility
│        │  /█\  │         │
└──────────────────────────┘
```

This dual-engine approach allows:
- **Grid efficiency** for static world
- **Geometric freedom** for dynamic objects
- **Unified depth sorting** for correct visibility
- **Separation of concerns** in codebase

---

## Optimizations & Technical Deep Dive

### 1. Raypack - Rotation Optimization

**The Problem:**
In classic raycasting engines, every time the player rotates their view, we recalculate raycasts for the **entire screen** (e.g., 800+ rays for 800px width). However, when rotating, most of what you see overlaps with the previous frame—only the edges change.

**The Observation:**
```
Player rotates left by 10°:
┌─────────────────────────┐
│  OUT  │   STILL VISIBLE   │  NEW  │
│ (old) │    (reusable!)    │ (new) │
└─────────────────────────┘
  10%          80%            10%
  
Only 10% of the view is actually new!
Why recalculate the other 90%?
```

**The Solution: Raypack**
Divide the screen into chunks ("raypacks") stored in a **doubly linked list**. When rotating:
- Move the invisible pack to the new edge
- Recalculate ONLY that pack
- Reuse all other packs

**How It Works:**

At initialization, the optimal pack size is calculated by finding the divisor of screen width closest to the target rotation size. The screen is then divided into packs stored as a linked list.

**Left Rotation:**
```
Before:  [ A ][ B ][ C ][ D ][ E ][ F ][ G ][ H ]
          ↑                                   ↑
        HEAD                                TAIL

After:   [ ? ][ A ][ B ][ C ][ D ][ E ][ F ][ G ]
          ↑                                   ↑
        HEAD                                TAIL
        
Process: Remove tail pack H → Insert at head → Recalculate only the new pack
Result: 7 out of 8 packs reused! Only 1 pack recalculated.
```

**Right Rotation:**
```
Before:  [ A ][ B ][ C ][ D ][ E ][ F ][ G ][ H ]
          ↑                                   ↑
        HEAD                                TAIL

After:   [ B ][ C ][ D ][ E ][ F ][ G ][ H ][ ? ]
          ↑                                   ↑
        HEAD                                TAIL
        
Process: Remove head pack A → Insert at tail → Recalculate only the new pack
Result: 7 out of 8 packs reused! Only 1 pack recalculated.
```

---

> **Implementation Details:** See [src/render/ray_list/render_ray_list.c](src/render/ray_list/render_ray_list.c) for the complete implementation of pack size calculation, linked list management, and rotation mechanics.

---

#### Performance Impact

**Example: 800px screen, 100-ray packs**

**Traditional Raycasting:**
```
Per rotation: 800 rays × raycast_cost = 800× cost
```

**Raypack System:**
```
Per rotation: 100 rays × raycast_cost = 100× cost
Reused: 700 rays (no computation needed)

Speedup: 800/100 = 8x faster! 
```

**Real-World Scenario:**
```
Player rapidly turning left during combat:
- 60 FPS gameplay
- 30° rotation per second = 0.5° per frame
- Pack shift every ~5 frames
  
Without raypack: 800 rays × 60 fps = 48,000 casts/sec
With raypack: 100 rays × 12 shifts/sec = 1,200 casts/sec

97.5% reduction in raycast calculations! 🚀
```

---

### 2. Objects in View Culling - Render Queue System

**The Problem:**
In a game with many dynamic objects (enemies, projectiles, particles), checking and rendering every object every frame is wasteful. Most objects are behind the player or outside the field of view.

**The Solution: Render Queue**
Build a sorted queue each frame containing only objects within FOV, ordered by distance for proper transparency rendering.

---

#### The Algorithm: Four-Step Process

**Step 1: Update Object Segment**

For dynamic objects, calculate the segment perpendicular to the player's view direction.

```
Player looking at enemy:

      P (Player)
      ↓ viewing direction
      
      ↓
      
    S ●━━━● E (Enemy center)
      
Calculate perpendicular segment:
- Find vector from player to enemy center
- Rotate 90° to get perpendicular
- Create segment of width W around enemy center
- Result: Segment [S, E] representing enemy facing player
```

This ensures objects always face the player camera correctly.

---

**Step 2: Check if Segment is in FOV**

Use angular range overlap to determine if any part of the object's segment is visible.

```
Top-down view:

        FOV = 60°
           ╱ ╲
          ╱   ╲
         ╱     ╲
        ╱   P   ╲
       ╱         ╲
      ●━━━━━━━━━━━● Enemy segment
      
Calculate:
1. Angle from player to segment.start
2. Angle from player to segment.end  
3. Player's FOV angular range
4. Check if ranges overlap

If overlap → Object is visible!
```

**Angular Range Overlap Example:**
```
Player FOV: [30°, 90°]
Object segment: [45°, 75°]

Overlap check:
max(30, 45) = 45
min(90, 75) = 75
45 ≤ 75 → TRUE, ranges overlap!

Object is in FOV ✓
```

Handles edge cases like FOV wrapping around 0°/360°.

---

**Step 3: Add to Sorted Render Queue**

Objects in FOV are inserted into a sorted linked list by distance (farthest first).

```
Example: Adding enemy at distance 8.5

Current queue (sorted by distance):
HEAD → [Door:12.0] → [Fireball:10.5] → [Orb:3.2] → NULL

Insert sorted (descending):
HEAD → [Door:12.0] → [Fireball:10.5] → [Enemy:8.5] → [Orb:3.2] → NULL
                                         ↑
                                      inserted!
```

**Why Farthest First?**
For proper transparency rendering. Distant objects rendered first, closer objects drawn on top with alpha blending.

```
Render order:
1. Door (12.0)      ← rendered first (back)
2. Fireball (10.5)  ← blended on top
3. Enemy (8.5)      ← blended on top  
4. Orb (3.2)        ← rendered last (front)

Result: Correct depth ordering with transparency ✓
```

---

**Step 4: Render Queue**

Iterate through sorted queue and render each object from farthest to nearest.

---

#### Complete Frame Pipeline

```
Every Frame:

1. Iterate all objects in game
   ├─ Fireball? → update_segment() → in_fov() → add_to_queue()
   ├─ Enemy? → update_segment() → in_fov() → add_to_queue()
   ├─ Orb? → update_segment() → in_fov() → add_to_queue()
   ├─ Door? → (static segment) → in_fov() → add_to_queue()
   └─ Particle? → update_segment() → in_fov() → add_to_queue()

2. Result: Sorted queue of visible objects
   [Obj20:dist=15.0] → [Obj5:dist=8.3] → [Obj12:dist=4.1] → NULL

3. Render queue (farthest to nearest)
   Transparent objects blend correctly!
```

---

#### Performance Impact

**Scenario: 50 objects in game world**

**Without Culling:**
```
Process all 50 objects every frame
Check intersection with 800 rays × 50 objects = 40,000 checks
```

**With Render Queue Culling:**
```
Check FOV: 50 simple angle checks
Visible objects (behind player + outside FOV culled): ~12 objects
Check intersection with 800 rays × 12 objects = 9,600 checks

76% reduction in intersection tests! 🚀
```

**Additional Benefits:**
- Automatic depth sorting for transparency
- Clean separation of visible/invisible objects
- Predictable rendering order
- Early rejection of behind-camera objects

---

> **Implementation Details:** See [src/render/objects/](src/render/objects/) folder for the complete render queue system:
> - `render_objects_queue.c` - Queue creation
> - `render_objects_queue_add.c` - Per-object type queue addition
> - `render_objects_queue_math.c` - Segment update & FOV checking
> - `src/objects/objects_list_operations.c` - Sorted insertion & distance calculation

---

### 3. Viewport Clipping

Only render pixels within screen boundaries. If an object's projected column is outside [0, screen_width], skip rendering that column.

```
Screen Bounds [0, 800px]
┌─────────────────────┐
│                     │
│  [Rendered]         │
│                     │
└─────────────────────┘
[Skip]              [Skip]
<-out of bounds     out of bounds->
```

---

### 4. Zero-Allocation Runtime

**Philosophy:** Pre-allocate everything at initialization. During gameplay, **zero malloc/free calls**.

**Implementation:**
```
Initialization:
- Allocate pool of 100 enemies
- Allocate pool of 50 fireballs  
- Allocate pool of 200 particles

Game Start:
- Active objects occupy positions in map
- Inactive objects positioned at (-1000, -1000) (out of bounds)

During Game:
- "Spawning" = move from inactive pool to active position
- "Destroying" = move back to inactive pool position
- No allocation/deallocation
```

**Benefits:**
- No memory fragmentation
- Predictable performance (no allocation spikes)
- No memory leaks possible during gameplay
- Cache-friendly (contiguous memory)

---

## Object System Architecture

All objects are represented as **segments** in 2D space. The rendering pipeline projects these segments into 3D view.

### Dynamic Segments
Segment endpoints **recalculated every frame** based on player position.

| Object | Calculation | Purpose |
|--------|-------------|---------|
| **Fireball** | `position += direction * speed * dt` | Projectile moving in straight line |
| **Orb** | `angle += rotation_speed * dt`<br>`pos = player_pos + rotate(offset, angle)` | Circular orbit around player |
| **Enemy** | `direction = normalize(player_pos - enemy_pos)`<br>Pathfinding with collision checks | AI chase behavior |
| **Particles** | Store previous N positions of fireball | Trail effect |

**Why Dynamic?**
These objects need an "upright" segment relative to the player's current view. We calculate segment points perpendicular to the player's viewing angle.

```
         Player View
             │
             │ viewing direction
             ↓
        
    ┌───┐   
    │ E │  Enemy (dynamic segment)
    └───┘
     ╱ ╲   Segment calculated perpendicular
    ╱   ╲  to player's current viewing angle
```

### Static Segments
Segment endpoints **never change** after initialization.

| Object | Why Static |
|--------|------------|
| **Doors** | Fixed position in world grid |
| **Doorwalls** | Non-axis-aligned walls with fixed endpoints |

---

## Hybrid Rendering: DDA + Line Intersection

**The Challenge:** Traditional DDA raycasting works on grid-aligned walls. How do we render non-axis-aligned geometry (like angled doorwalls)?

**The Solution:** Combine two algorithms.

### DDA (Digital Differential Analyzer)
Grid-based raycasting for walls:
```
Grid Map:
┌─┬─┬─┬─┐
│ │ │█│ │
├─┼─┼─┼─┤
│ │ │ │ │  Ray steps through grid cells
├─┼─┼─┼─┤  until hitting wall (█)
│P│→│→│→│█
└─┴─┴─┴─┘
```

### Line Intersection Algorithm
For segments (doorwalls, objects):
```
Ray: P + t * direction
Segment: S1 + u * (S2 - S1)

Solve for intersection:
P + t*D = S1 + u*(S2-S1)

Returns: intersection point + distance
```

**Combined Pipeline:**
1. Cast ray using DDA → get wall intersections
2. Check ray against all segments → get segment intersections
3. Compare distances → render closest intersection
4. Result: Seamless mix of grid walls and free-form segments

---

## HUD & Rendering Systems

### Custom Image System (cub3_images)

**Why build from scratch?**
To understand image processing fundamentals and avoid MLX parser limitations.

**Features:**
- Manual pixel buffer manipulation
- Custom alpha blending: `result = src * alpha + dst * (1 - alpha)`
- Direct memory access for performance
- Support for custom `.cub3` image format

**Custom Image Format:**
A Python script ([png_to_cub3.py](png_to_cub3.py)) converts PNG images to the custom `.cub3` format:
- No external dependencies (pure Python PNG parser)
- Outputs hex color values per pixel
- Includes white threshold feature for color normalization
- Format: `.cub3:width:height` header followed by hex RGBA values

```bash
# Convert PNG to .cub3 format
python3 png_to_cub3.py sprite.png sprite.cub3 5
```

**Use Case:** 
Process transparent UI elements, custom effects, and blend multiple image layers without relying on MLX's built-in functions.

---

### Font Renderer - Printf for Images

A complete text rendering system enabling dynamic text in-game.

**Font Generation Pipeline:**
A Python script ([z_font_maker/font_maker.py](z_font_maker/font_maker.py)) converts TTF fonts to sprite sheets:
- Renders all ASCII characters (A-Z, a-z, 0-9, symbols)
- Calculates optimal width for each character
- Generates sprite atlas with color-coded pixels
- Output: `font.png` with all glyphs laid out in rows

**Architecture:**
```
TTF Font → Python script → Sprite sheet → C code parser → Runtime rendering

Text "SCORE: 100" → 
  For each char:
    - Look up in atlas by ASCII value
    - Draw to screen buffer at (x, y)
    - Advance x by char_width
```

**Features:**
- Custom typeface from any TTF file
- Runtime text generation
- Printf-style formatting
- Automatic character width calculation

**Example:**
```c
draw_text(image, x, y, "Health: %d", player.health);
```

Enables:
- Score display
- Health/ammo counters
- Menu text
- Debug information
- All without external font libraries at runtime

---

### Interactive Button System

**Dual Input Support: Mouse + Keyboard**

The button system supports both mouse and keyboard navigation with a cached "current button" state.

**How it works:**
```
Current Button Cache:
- Store pointer to currently selected button
- Render with hover state visual feedback
- Update via mouse OR keyboard

Mouse Navigation:
- Move mouse over button → becomes current
- Button shows hover state
- Click to activate

Keyboard Navigation:
- Arrow keys / Tab → change current button
- Current button shows hover state
- Enter to activate
```

**State Management:**
```
Button states:
NORMAL → Not selected
HOVER  → Current button (mouse over OR keyboard selected)
ACTIVE → Being clicked/activated

Update loop:
1. Check mouse position → if over button, set as current
2. Check keyboard input → if arrow/tab, move to next button
3. Render current button with hover state
4. Handle click/enter on current button
```

**Text Buttons for Map Selection:**
- Scan `_maps/` directory using `readdir()`
- Generate button for each `.cub` file
- Navigate with mouse or keyboard
- Visual feedback on hover/click
- Callback system for button actions

---

## Memory Management - Garbage Collector

Three-tier allocation strategy for clean memory management.

### Tier 1: Static Allocation
**Lifetime:** Program start → Program end

**Allocated:**
- MLX window and display
- Core renderer structures
- Input event handlers
- Global game state

**Cleanup:** At program exit only

---

### Tier 2: Dynamic Allocation
**Lifetime:** Game/level start → Game/level end

**Allocated:**
- Map data (walls, textures)
- Active player state
- Object pools (enemies, projectiles)
- Level-specific resources

**Cleanup:** When returning to menu or loading new map

---

### Tier 3: Temporary Allocation
**Lifetime:** Function scope

**Allocated:**
- Parsing intermediate data
- Pathfinding work arrays
- Collision detection temporaries
- String processing buffers

**Cleanup:** At end of utility function

**Registered to GC:**
```c
// All allocations go through GC
void *ptr = gc_malloc(size, TIER_TEMPORARY);
// Automatic cleanup when tier is cleared
gc_clear(TIER_TEMPORARY);
```

**Benefits:**
- No manual free() needed
- Clear ownership and lifecycle
- Easy cleanup on error
- Prevents memory leaks
- Bulk deallocation per tier

---

## Map Selection System

Dynamic file system browser built with custom UI:

**Implementation:**
1. `opendir("_maps/")` → read directory
2. Filter for `.cub` extension
3. Generate text button for each file
4. Store filename in button callback data
5. On click → load selected map

**Features:**
- Automatic detection of new maps
- No hardcoded map list
- Shine effect on hover
- Campaign progression tracking

---

**Built with C, Mathematics, and a Deep Desire to Understand How Things Work**