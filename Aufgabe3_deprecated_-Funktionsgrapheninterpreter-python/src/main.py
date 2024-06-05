import os
from pathlib import Path
import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import quad
from scipy.optimize import fsolve, minimize_scalar

# from tkinter import *
# Explicit imports to satisfy Flake8
from tkinter import Tk, Canvas, Entry, Text, Button, PhotoImage

# Get the current working directory
cwd = Path(os.getcwd())

OUTPUT_PATH = Path(__file__).parent
relative_path = cwd / 'resources/build/assets/frame0'
ASSETS_PATH = relative_path


def relative_to_assets(path: str) -> Path:
    return ASSETS_PATH / Path(path)

y_upper = 10
y_lower = -10
y_ticks = 10
x_upper = 10
x_lower = -10
x_ticks = 10
function = lambda x: x


def create_plot(function, y_upper, y_lower, y_ticks, x_upper, x_lower, x_ticks, num_points=1000):
    # Generate x values
    x = np.linspace(x_lower, x_upper, num_points)
    
    # Calculate y values, check for SyntaxError, set textbox to red if error and return
    try:
        y = function(x)
    except SyntaxError as e:
        entry_1.config(bg="#FF0000")
        return
    
    fig, ax = plt.subplots()

    # Plot the function
    ax.plot(x, y)

    # Set y-axis limits and ticks
    ax.set_ylim(y_lower, y_upper)
    ax.set_yticks(np.linspace(y_lower, y_upper, y_ticks))

    # Set x-axis limits and ticks
    ax.set_xlim(x_lower, x_upper)
    ax.set_xticks(np.linspace(x_lower, x_upper, x_ticks))

    # Add a grid
    ax.grid(True)

    # Move left y-axis and bottom x-axis to centre, passing through (0,0)
    if 0 <= y_upper and 0 >= y_lower:
        ax.spines['left'].set_position('zero')
    else:
        ax.spines['left'].set_position(('data', y_lower))
        
    if 0 <= x_upper and 0 >= x_lower:
        ax.spines['bottom'].set_position('zero')
    else:
        ax.spines['bottom'].set_position(('data', x_lower))

    # Eliminate upper and right axes
    ax.spines['right'].set_color('none')
    ax.spines['top'].set_color('none')

    # Show ticks in the left and lower axes only
    ax.xaxis.set_ticks_position('bottom')
    ax.yaxis.set_ticks_position('left')

    plt.show()

def get_extrema(func, interval):
    # Find the minimum
    res_min = minimize_scalar(func, bounds=interval, method='bounded')
    min_point = (res_min.x, res_min.fun)

    # Find the maximum by minimizing the negative of the function
    res_max = minimize_scalar(lambda x: -func(x), bounds=interval, method='bounded')
    max_point = (res_max.x, -res_max.fun)

    return f"min: {min_point}, max: {max_point}"

def find_x_intercepts(func, x0):
    return fsolve(func, x0)

def find_y_intercept(func):
    return func(0)

def get_intercepts(function):
    y_intercepts = find_y_intercept(function)
    x_intercepts = find_x_intercepts(function, 0)
    return f"y: {y_intercepts}, x: {x_intercepts}"

def get_integral(function, lowerX, upperX):
    result = quad(function, lowerX, upperX)
    return result

def plotItOut():

    # for each of the entry gets, catch for errors and if caught, turn the entry box red

    error_occured = False

    try:
        function = lambda x: eval(entry_1.get())
        entry_1.config(bg="#FFFFFF")
    except Exception as e:
        entry_1.config(bg="#FF0000")
        error_occured = True
    
    try:
        y_upper = int(entry_7.get())
        entry_2.config(bg="#FFFFFF")
    except Exception as e:
        entry_2.config(bg="#FF0000")
        error_occured = True
    
    try:
        y_lower = int(entry_6.get())
        entry_6.config(bg="#FFFFFF")
    except Exception as e:
        entry_6.config(bg="#FF0000")
        error_occured = True
    
    try:
        y_ticks = int(entry_4.get())
        entry_4.config(bg="#FFFFFF")
    except Exception as e:
        entry_4.config(bg="#FF0000")
        error_occured = True
    
    try:
        x_upper = int(entry_2.get())
        entry_7.config(bg="#FFFFFF")
    except Exception as e:
        entry_7.config(bg="#FF0000")
        error_occured = True
    
    try:
        x_lower = int(entry_5.get())
        entry_5.config(bg="#FFFFFF")
    except Exception as e:
        entry_5.config(bg="#FF0000")
        error_occured = True
    
    try:
        x_ticks = int(entry_3.get())
        entry_3.config(bg="#FFFFFF")
    except Exception as e:
        entry_3.config(bg="#FF0000")
        error_occured = True

    if error_occured:
        return

    create_plot(function, y_upper, y_lower, y_ticks, x_upper, x_lower, x_ticks)
    extrema_text = get_extrema(function, (x_lower, x_upper))
    intercepts_text = get_intercepts(function)
    integral_text = get_integral(function)

    # set correct canvas textboxes to include their text
    canvas.itemconfigure(extrema_text, text=extrema_text)
    canvas.itemconfigure(intercepts_text, text=intercepts_text)
    canvas.itemconfigure(integral_text, text=integral_text)


integral_text = ""
extrema_text = ""
intercepts_text = ""

window = Tk()

window.geometry("942x375")
window.configure(bg = "#FFFFFF")


canvas = Canvas(
    window,
    bg = "#FFFFFF",
    height = 375,
    width = 942,
    bd = 0,
    highlightthickness = 0,
    relief = "ridge"
)

canvas.place(x = 0, y = 0) # Integral text
canvas.create_text(
    714.0,
    321.0,
    anchor="nw",
    text=integral_text,
    fill="#383838",
    font=("Inter SemiBold", 15 * -1)
)

canvas.create_text(
    714.0,
    296.0,
    anchor="nw",
    text="Extrema",
    fill="#383838",
    font=("Inter SemiBold", 16 * -1)
)

canvas.create_text( # Extrema text
    508.0,
    321.0,
    anchor="nw",
    text=extrema_text,
    fill="#383838",
    font=("Inter SemiBold", 15 * -1)
)

canvas.create_text(
    508.0,
    296.0,
    anchor="nw",
    text="Intercepts",
    fill="#383838",
    font=("Inter SemiBold", 16 * -1)
)

canvas.create_text( # Intercepts text
    278.0,
    321.0,
    anchor="nw",
    text=intercepts_text,
    fill="#383838",
    font=("Inter SemiBold", 15 * -1)
)

canvas.create_text(
    278.0,
    296.0,
    anchor="nw",
    text="Integral",
    fill="#383838",
    font=("Inter SemiBold", 16 * -1)
)

canvas.create_text(
    462.0,
    11.0,
    anchor="nw",
    text="QuickPlot",
    fill="#000000",
    font=("Inter SemiBold", 20 * -1)
)

button_image_1 = PhotoImage( # Plot button
    file=relative_to_assets("button_1.png"))
button_1 = Button(
    image=button_image_1,
    borderwidth=0,
    highlightthickness=0,
    command= plotItOut,
    relief="flat"
)
button_1.place(
    x=793.0,
    y=79.0,
    width=142.0,
    height=55.0
)

entry_image_1 = PhotoImage(
    file=relative_to_assets("entry_1.png"))
entry_bg_1 = canvas.create_image(
    584.0,
    106.0,
    image=entry_image_1
)
entry_1 = Entry(
    bd=0,
    bg="#FFFFFF",
    fg="#000716",
    highlightthickness=0
)
entry_1.place(
    x=395.0,
    y=86.0,
    width=378.0,
    height=38.0
)

canvas.create_text(
    299.0,
    95.0,
    anchor="nw",
    text="input here:",
    fill="#828282",
    font=("Inter", 15 * -1)
)

canvas.create_text(
    278.0,
    67.0,
    anchor="nw",
    text="Function",
    fill="#383838",
    font=("Inter", 16 * -1)
)

entry_image_2 = PhotoImage(
    file=relative_to_assets("entry_2.png"))
entry_bg_2 = canvas.create_image(
    647.0,
    169.0,
    image=entry_image_2
)
entry_2 = Entry(
    bd=0,
    bg="#FFFFFF",
    fg="#000716",
    highlightthickness=0
)
entry_2.place(
    x=601.0,
    y=149.0,
    width=92.0,
    height=38.0
)

canvas.create_text(
    508.0,
    158.0,
    anchor="nw",
    text="upper limit:",
    fill="#828282",
    font=("Inter", 15 * -1)
)

entry_image_3 = PhotoImage(
    file=relative_to_assets("entry_3.png"))
entry_bg_3 = canvas.create_image(
    881.0,
    169.0,
    image=entry_image_3
)
entry_3 = Entry(
    bd=0,
    bg="#FFFFFF",
    fg="#000716",
    highlightthickness=0
)
entry_3.place(
    x=835.0,
    y=149.0,
    width=92.0,
    height=38.0
)

canvas.create_text(
    714.0,
    154.0,
    anchor="nw",
    text="x-tick number:",
    fill="#828282",
    font=("Inter", 15 * -1)
)

entry_image_4 = PhotoImage(
    file=relative_to_assets("entry_4.png"))
entry_bg_4 = canvas.create_image(
    881.0,
    232.0,
    image=entry_image_4
)
entry_4 = Entry(
    bd=0,
    bg="#FFFFFF",
    fg="#000716",
    highlightthickness=0
)
entry_4.place(
    x=835.0,
    y=212.0,
    width=92.0,
    height=38.0
)

canvas.create_text(
    714.0,
    221.0,
    anchor="nw",
    text="y-tick number:",
    fill="#828282",
    font=("Inter", 15 * -1)
)

entry_image_5 = PhotoImage(
    file=relative_to_assets("entry_5.png"))
entry_bg_5 = canvas.create_image(
    441.0,
    169.0,
    image=entry_image_5
)
entry_5 = Entry(
    bd=0,
    bg="#FFFFFF",
    fg="#000716",
    highlightthickness=0
)
entry_5.place(
    x=395.0,
    y=149.0,
    width=92.0,
    height=38.0
)

canvas.create_text(
    299.0,
    158.0,
    anchor="nw",
    text="lower limit:",
    fill="#828282",
    font=("Inter", 15 * -1)
)

canvas.create_text(
    278.0,
    129.0,
    anchor="nw",
    text="X-axis ",
    fill="#383838",
    font=("Inter", 16 * -1)
)

entry_image_6 = PhotoImage(
    file=relative_to_assets("entry_6.png"))
entry_bg_6 = canvas.create_image(
    441.0,
    232.0,
    image=entry_image_6
)
entry_6 = Entry(
    bd=0,
    bg="#FFFFFF",
    fg="#000716",
    highlightthickness=0
)
entry_6.place(
    x=395.0,
    y=212.0,
    width=92.0,
    height=38.0
)

canvas.create_text(
    299.0,
    221.0,
    anchor="nw",
    text="lower limit:",
    fill="#828282",
    font=("Inter", 15 * -1)
)

canvas.create_text(
    276.0,
    192.0,
    anchor="nw",
    text="Y-axis",
    fill="#383838",
    font=("Inter", 16 * -1)
)

entry_image_7 = PhotoImage(
    file=relative_to_assets("entry_7.png"))
entry_bg_7 = canvas.create_image(
    647.0,
    232.0,
    image=entry_image_7
)
entry_7 = Entry(
    bd=0,
    bg="#FFFFFF",
    fg="#000716",
    highlightthickness=0
)
entry_7.place(
    x=601.0,
    y=212.0,
    width=92.0,
    height=38.0
)

canvas.create_text(
    508.0,
    217.0,
    anchor="nw",
    text="upper limit:",
    fill="#828282",
    font=("Inter", 15 * -1)
)

canvas.create_rectangle(
    -1.0,
    47.0,
    942.0005493164062,
    48.0,
    fill="#E7E1E1",
    outline="")

button_image_2 = PhotoImage( # How to see derivative button, opens pdf file with instructions
    file=relative_to_assets("button_2.png"))
button_2 = Button(
    image=button_image_2,
    borderwidth=0,
    highlightthickness=0,
    command=lambda: print("button_2 clicked"),
    relief="flat"
)
button_2.place(
    x=33.0,
    y=137.0,
    width=189.0,
    height=40.0
)

button_image_3 = PhotoImage( # How to Plot button, command open pdf file that explains it
    file=relative_to_assets("button_3.png"))
button_3 = Button(
    image=button_image_3,
    borderwidth=0,
    highlightthickness=0,
    command=lambda: print("button_3 clicked"),
    relief="flat"
)
button_3.place(
    x=33.0,
    y=86.0,
    width=189.0,
    height=40.0
)

canvas.create_text(
    107.0,
    56.0,
    anchor="nw",
    text="How...",
    fill="#000000",
    font=("Inter SemiBold", 15 * -1)
)

canvas.create_rectangle(
    244.62462443813274,
    -1.0,
    246.9843261912696,
    375.00117270832845,
    fill="#E6E0E0",
    outline="")

canvas.create_rectangle(
    245.0011917658511,
    282.00001043554107,
    1048.135986328125,
    283.97006514150274,
    fill="#E6E0E0",
    outline="")

image_image_1 = PhotoImage(
    file=relative_to_assets("image_1.png"))
image_1 = canvas.create_image(
    127.9999803895497,
    281.0,
    image=image_image_1
)

canvas.create_text(
    711.0,
    19.0,
    anchor="nw",
    text="...Plots pop up as new windows!",
    fill="#383838",
    font=("Inter SemiBold", 15 * -1)
)
window.resizable(False, False)
window.title("QuickPlot - graphs made a little easier")
window.iconbitmap("resources/build/assets/frame0/icon.ico")
window.mainloop()
