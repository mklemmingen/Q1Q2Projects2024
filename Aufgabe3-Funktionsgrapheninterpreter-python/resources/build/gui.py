
# This file was generated by the Tkinter Designer by Parth Jadhav
# https://github.com/ParthJadhav/Tkinter-Designer

import os
from pathlib import Path

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
    text="",
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
    text="",
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
    text="",
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
    command=lambda: print("button_1 clicked"),
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
window.mainloop()
