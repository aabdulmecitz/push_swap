#!/usr/bin/env python3
import sys
import subprocess
import os
import colorsys

try:
    import tkinter as tk
    from tkinter import ttk
except ImportError:
    print("Error: tkinter is not installed. Please install it to use the graphical visualizer.")
    sys.exit(1)

def normalize(arr):
    sorted_arr = sorted(arr)
    return [sorted_arr.index(x) + 1 for x in arr]

def apply_op(op, a, b):
    if op == "sa" and len(a) > 1:
        a[0], a[1] = a[1], a[0]
    elif op == "sb" and len(b) > 1:
        b[0], b[1] = b[1], b[0]
    elif op == "ss":
        if len(a) > 1: a[0], a[1] = a[1], a[0]
        if len(b) > 1: b[0], b[1] = b[1], b[0]
    elif op == "pa" and len(b) > 0:
        a.insert(0, b.pop(0))
    elif op == "pb" and len(a) > 0:
        b.insert(0, a.pop(0))
    elif op == "ra" and len(a) > 0:
        a.append(a.pop(0))
    elif op == "rb" and len(b) > 0:
        b.append(b.pop(0))
    elif op == "rr":
        if len(a) > 0: a.append(a.pop(0))
        if len(b) > 0: b.append(b.pop(0))
    elif op == "rra" and len(a) > 0:
        a.insert(0, a.pop())
    elif op == "rrb" and len(b) > 0:
        b.insert(0, b.pop())
    elif op == "rrr":
        if len(a) > 0: a.insert(0, a.pop())
        if len(b) > 0: b.insert(0, b.pop())

class Visualizer:
    def __init__(self, root, a, ops, total_elements):
        self.root = root
        self.root.title("aozkaya's cool push swap visualizer")
        self.root.geometry("1400x800")
        self.root.configure(bg="#09090b") # zinc-950
        
        self.initial_a = a[:]
        self.a = a
        self.b = []
        self.ops = ops
        self.total_elements = total_elements
        self.max_val = max(self.a) if self.a else 1
        
        self.op_idx = 0
        self.is_playing = False
        self.delay = 50
        
        self.setup_ui()
        self.generate_colors()
        
        self.root.bind('<Configure>', self.on_resize)
        self.draw_stacks()
        
    def setup_ui(self):
        # Main Layout
        self.main_frame = tk.Frame(self.root, bg="#09090b")
        self.main_frame.pack(fill=tk.BOTH, expand=True)
        
        # Sidebar
        self.sidebar = tk.Frame(self.main_frame, bg="#18181b", width=320, highlightthickness=1, highlightbackground="#27272a")
        self.sidebar.pack(side=tk.RIGHT, fill=tk.Y)
        self.sidebar.pack_propagate(False)
        
        # Sidebar Content
        title = tk.Label(self.sidebar, text="AOZKAYA'S COOL\nPUSH SWAP", font=("Helvetica", 20, "bold"), bg="#18181b", fg="#ffffff", pady=20)
        title.pack()
        
        # Stats
        stats_frame = tk.Frame(self.sidebar, bg="#18181b")
        stats_frame.pack(fill=tk.X, padx=20, pady=10)
        
        tk.Label(stats_frame, text="ELEMENTS", font=("Helvetica", 10, "bold"), bg="#18181b", fg="#a1a1aa").pack(anchor="w")
        tk.Label(stats_frame, text=f"{self.total_elements}", font=("Helvetica", 18), bg="#18181b", fg="#ffffff").pack(anchor="w", pady=(0,10))
        
        tk.Label(stats_frame, text="OPERATIONS", font=("Helvetica", 10, "bold"), bg="#18181b", fg="#a1a1aa").pack(anchor="w")
        self.ops_label = tk.Label(stats_frame, text=f"0 / {len(self.ops)}", font=("Helvetica", 24, "bold"), bg="#18181b", fg="#3b82f6")
        self.ops_label.pack(anchor="w", pady=(0,10))
        
        # Controls
        ctrl_frame = tk.Frame(self.sidebar, bg="#18181b")
        ctrl_frame.pack(fill=tk.X, padx=20, pady=10)
        
        btn_frame = tk.Frame(ctrl_frame, bg="#18181b")
        btn_frame.pack(fill=tk.X, pady=10)
        
        self.play_btn = tk.Button(btn_frame, text="PLAY", font=("Helvetica", 12, "bold"), bg="#22c55e", fg="white", bd=0, activebackground="#16a34a", activeforeground="white", command=self.toggle_play, cursor="hand2")
        self.play_btn.pack(side=tk.LEFT, fill=tk.X, expand=True, padx=(0,5), ipady=5)
        
        self.step_btn = tk.Button(btn_frame, text="STEP", font=("Helvetica", 12, "bold"), bg="#3f3f46", fg="white", bd=0, activebackground="#52525b", activeforeground="white", command=self.step, cursor="hand2")
        self.step_btn.pack(side=tk.LEFT, fill=tk.X, expand=True, padx=(5,5), ipady=5)
        
        self.reset_btn = tk.Button(btn_frame, text="RESET", font=("Helvetica", 12, "bold"), bg="#ef4444", fg="white", bd=0, activebackground="#dc2626", activeforeground="white", command=self.reset, cursor="hand2")
        self.reset_btn.pack(side=tk.LEFT, fill=tk.X, expand=True, padx=(5,0), ipady=5)
        
        # Speed
        tk.Label(ctrl_frame, text="ANIMATION SPEED", font=("Helvetica", 10, "bold"), bg="#18181b", fg="#a1a1aa").pack(anchor="w", pady=(10,0))
        self.speed_slider = ttk.Scale(ctrl_frame, from_=1, to_=1000, orient=tk.HORIZONTAL)
        self.speed_slider.set(800 if self.total_elements > 100 else 400)
        self.speed_slider.pack(fill=tk.X, pady=10)
        
        # History
        tk.Label(self.sidebar, text="OPERATION HISTORY", font=("Helvetica", 10, "bold"), bg="#18181b", fg="#a1a1aa").pack(anchor="w", padx=20, pady=(10,0))
        
        history_frame = tk.Frame(self.sidebar, bg="#18181b", highlightthickness=1, highlightbackground="#27272a")
        history_frame.pack(fill=tk.BOTH, expand=True, padx=20, pady=10)
        
        scrollbar = tk.Scrollbar(history_frame)
        scrollbar.pack(side=tk.RIGHT, fill=tk.Y)
        
        self.history_list = tk.Listbox(history_frame, bg="#09090b", fg="#e4e4e7", font=("Courier", 14), highlightthickness=0, selectbackground="#3b82f6", selectforeground="white", yscrollcommand=scrollbar.set, activestyle="none", borderwidth=0)
        self.history_list.pack(side=tk.LEFT, fill=tk.BOTH, expand=True, padx=5, pady=5)
        scrollbar.config(command=self.history_list.yview)
        
        for i, op in enumerate(self.ops):
            self.history_list.insert(tk.END, f"{i+1:04d} | {op.upper()}")
            
        # Canvas
        self.canvas_frame = tk.Frame(self.main_frame, bg="#09090b")
        self.canvas_frame.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
        
        self.canvas = tk.Canvas(self.canvas_frame, bg="#09090b", highlightthickness=0)
        self.canvas.pack(fill=tk.BOTH, expand=True, padx=20, pady=20)
        
    def generate_colors(self):
        self.colors = {}
        for val in range(1, self.total_elements + 1):
            hue = (val / self.total_elements) * 0.8
            rgb = colorsys.hls_to_rgb(hue, 0.5, 0.9)
            hex_color = '#%02x%02x%02x' % (int(rgb[0]*255), int(rgb[1]*255), int(rgb[2]*255))
            self.colors[val] = hex_color

    def toggle_play(self):
        self.is_playing = not self.is_playing
        if self.is_playing:
            self.play_btn.config(text="PAUSE", bg="#eab308", activebackground="#ca8a04")
            self.animate()
        else:
            self.play_btn.config(text="PLAY", bg="#22c55e", activebackground="#16a34a")

    def step(self):
        self.is_playing = False
        self.play_btn.config(text="PLAY", bg="#22c55e", activebackground="#16a34a")
        self.process_next_op()
        
    def reset(self):
        self.a = self.initial_a[:]
        self.b = []
        self.op_idx = 0
        self.is_playing = False
        self.play_btn.config(text="PLAY", bg="#22c55e", activebackground="#16a34a")
        self.ops_label.config(text=f"0 / {len(self.ops)}")
        self.history_list.yview_moveto(0)
        self.history_list.selection_clear(0, tk.END)
        self.draw_stacks()
        
    def process_next_op(self):
        if self.op_idx >= len(self.ops):
            self.is_playing = False
            self.play_btn.config(text="DONE", bg="#3b82f6", activebackground="#2563eb")
            return False
            
        op = self.ops[self.op_idx].strip()
        self.history_list.selection_clear(0, tk.END)
        self.history_list.selection_set(self.op_idx)
        self.history_list.see(self.op_idx)
        
        self.op_idx += 1
        if op:
            apply_op(op, self.a, self.b)
            self.ops_label.config(text=f"{self.op_idx} / {len(self.ops)}")
            self.draw_stacks(highlight_op=op)
        return True

    def animate(self):
        if not self.is_playing:
            return
            
        slider_val = self.speed_slider.get()
        delay_ms = int(500 - (slider_val * 0.499))
        if delay_ms < 1: delay_ms = 1
        
        batch_size = 1
        if slider_val > 900: batch_size = 2
        if slider_val > 950: batch_size = 5
        if slider_val > 990: batch_size = 20
        
        for _ in range(batch_size):
            if not self.process_next_op():
                return
                
        self.root.after(delay_ms, self.animate)

    def on_resize(self, event):
        if event.widget == self.canvas:
            self.draw_stacks()
            
    def draw_stacks(self, highlight_op=None):
        self.canvas.delete("all")
        width = self.canvas.winfo_width()
        height = self.canvas.winfo_height()
        
        if width <= 1 or height <= 1:
            return
            
        half_width = width / 2
        
        # Draw Watermarks
        self.canvas.create_text(half_width/2, height/2, text="A", font=("Helvetica", 200, "bold"), fill="#18181b")
        self.canvas.create_text(half_width + half_width/2, height/2, text="B", font=("Helvetica", 200, "bold"), fill="#18181b")
        
        total_slots = self.total_elements
        slot_width = (half_width - 40) / total_slots if total_slots > 0 else 1
        bar_w = max(1, slot_width * 0.8)
        
        # Draw A
        for i, val in enumerate(self.a):
            x_center = 20 + (i * slot_width) + (slot_width / 2)
            bar_h = (val / self.max_val) * (height - 40)
            
            x0 = x_center - (bar_w / 2)
            y0 = height - 20
            x1 = x_center + (bar_w / 2)
            y1 = y0 - bar_h
            
            color = self.colors.get(val, "#ffffff")
            if highlight_op:
                if highlight_op in ["sa", "ss"] and i < 2:
                    color = "#ffffff"
                elif highlight_op == "pa" and i == 0:
                    color = "#ffffff"
                elif highlight_op in ["ra", "rr"] and i == len(self.a) - 1:
                    color = "#ffffff"
                    
            self.canvas.create_rectangle(x0, y0, x1, y1, fill=color, outline="")
            
        # Draw B
        for i, val in enumerate(self.b):
            x_center = half_width + 20 + (i * slot_width) + (slot_width / 2)
            bar_h = (val / self.max_val) * (height - 40)
            
            x0 = x_center - (bar_w / 2)
            y0 = height - 20
            x1 = x_center + (bar_w / 2)
            y1 = y0 - bar_h
            
            color = self.colors.get(val, "#ffffff")
            if highlight_op:
                if highlight_op in ["sb", "ss"] and i < 2:
                    color = "#ffffff"
                elif highlight_op == "pb" and i == 0:
                    color = "#ffffff"
                elif highlight_op in ["rb", "rr"] and i == len(self.b) - 1:
                    color = "#ffffff"
                    
            self.canvas.create_rectangle(x0, y0, x1, y1, fill=color, outline="")
            
        # Draw center divider
        self.canvas.create_line(half_width, 20, half_width, height-20, fill="#27272a", width=2, dash=(4, 4))

def main():
    if len(sys.argv) < 2:
        print("Usage: python3 visualize.py <numbers...>")
        sys.exit(1)
        
    args = sys.argv[1:]
    if len(args) == 1:
        args = args[0].split()
        
    try:
        numbers = [int(x) for x in args]
    except ValueError:
        print("Error: Invalid numbers passed to visualizer.")
        sys.exit(1)
        
    if len(numbers) == 0:
        return

    a = normalize(numbers)
    total_elements = len(a)

    try:
        proc = subprocess.run(["./push_swap"] + [str(x) for x in numbers], capture_output=True, text=True)
    except FileNotFoundError:
        print("Error: ./push_swap not found. Please compile the project first.")
        sys.exit(1)
        
    if "Error" in proc.stderr:
        print(f"push_swap returned an error:\n{proc.stderr}")
        sys.exit(1)
        
    ops = [op for op in proc.stdout.strip().split('\n') if op]
    
    root = tk.Tk()
    
    style = ttk.Style()
    if 'clam' in style.theme_names():
        style.theme_use('clam')
    style.configure("Horizontal.TScale", background="#18181b", troughcolor="#3f3f46")
    
    app = Visualizer(root, a, ops, total_elements)
    
    # Bring to front
    root.attributes('-topmost', True)
    root.update()
    root.attributes('-topmost', False)
    
    root.mainloop()

if __name__ == "__main__":
    main()
