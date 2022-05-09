#!/usr/bin/env python

import tkinter
import sys
import time


width = 1000
height = 700
size = 0
puzzle = []
moves = 0
time_score = 0
space = 0
pause = False
is_run = False
curr_move = 0

puzzle_width = 800
puzzle_height = 700


root = tkinter.Tk()
root.title('n_puzzle by alzaynou')
root.geometry(f"{width}x{height}")
canvas = tkinter.Canvas(root,width=width, height=height, bg="black")

def draw_puzzle(size, puzzle):
    global curr_move
    tkinter.Label(root, text=str(curr_move) +  "\t", bg="black", fg="grey", font=("Arial", 20)).place(x=puzzle_width + 20, y=900)
    curr_move += 1
    global canvas
    canvas.delete("all")
    for i in range(size):
        for j in range(size):
            if puzzle[i*size+j] != "0":
                canvas.create_rectangle(j*puzzle_width/size, i*puzzle_height/size, (j+1)*puzzle_width/size, (i+1)*puzzle_height/size, fill="white", outline="black")
            else:
                canvas.create_rectangle(j*puzzle_width/size, i*puzzle_height/size, (j+1)*puzzle_width/size, (i+1)*puzzle_height/size, fill="grey", outline="black")
    
    for i in range(size):
        for j in range(size):
            if puzzle[i*size+j] != "0":
                canvas.create_text(j*puzzle_width/size + puzzle_width/size/2, i*puzzle_height/size + puzzle_height/size/2, text=puzzle[i*size + j], fill="black", font=("Arial", 20))
    
    canvas.pack()


def read_info():
    buf = sys.stdin.readline()
    if (len(buf.split()) != 2 or buf.split()[0] != "TIME:"):
        exit()
    time_score = buf.split()[1]
    
    buf = sys.stdin.readline()
    if (len(buf.split()) != 2 or buf.split()[0] != "SPACE:"):
        exit()
    space = buf.split()[1]
    
    buf = sys.stdin.readline()
    if (len(buf.split()) != 2 or buf.split()[0] != "MOVES:"):
        exit()
    moves = buf.split()[1]

    buf = sys.stdin.readline()
    if (len(buf.split()) != 2 or buf.split()[0] != "SIZE:" or int(buf.split()[1]) < 3):
        exit()
    size = buf.split()[1]
    return int(time_score), int(space), int(moves), int(size)

def read_puzzle(size):
    buf = ""
    buf = sys.stdin.readline()
    if buf == "":
        return False
    for i in range(size):
        buf += sys.stdin.readline()
        puzzle = buf.split()
    draw_puzzle(size, puzzle)
    return True

def read_all_step():
    while True:
        if (pause):
            sys.stdout.flush()
            break
        read_puzzle(size)
        root.update()
        time.sleep(0.1)

def draw_manu(size):
    tkinter.Label(root, text="Size:       " + str(size), bg="black", fg="green", font=("Arial", 18)).place(x=puzzle_width + 20, y=40)
    tkinter.Label(root, text="Moves:    " + str(moves), bg="black", fg="green", font=("Arial", 18)).place(x=puzzle_width + 20, y=80)
    tkinter.Label(root, text="Time:     " + str(time_score), bg="black", fg="green", font=("Arial", 18)).place(x=puzzle_width + 20, y=120)
    tkinter.Label(root, text="Space:    " + str(space) , bg="black", fg="green", font=("Arial", 18)).place(x=puzzle_width + 20, y=160)
    tkinter.Label(root, text="Next step:    n", bg="black", fg="green", font=("Arial", 18)).place(x=puzzle_width + 20, y=200)
    tkinter.Label(root, text="Run:    r", bg="black", fg="green", font=("Arial", 18)).place(x=puzzle_width + 20, y=240)
    tkinter.Label(root, text="pause:    p", bg="black", fg="green", font=("Arial", 18)).place(x=puzzle_width + 20, y=280)
    tkinter.Label(root, text="Quit:    q", bg="black", fg="green", font=("Arial", 18)).place(x=puzzle_width + 20, y=320)


def key_press(event):
    global pause
    global is_run
    if event.char == "n":
        tkinter.Label(root, text="Next  ", bg="black", fg="red", font=("Arial", 20)).place(x=puzzle_width + 20, y=950)
        pause = True
        is_run = False
        read_puzzle(size)
    elif event.char == "r":
        if not is_run:
            is_run = True
            pause = False
            tkinter.Label(root, text="Run   ", bg="black", fg="red", font=("Arial", 20)).place(x=puzzle_width + 20, y=950)
            read_all_step()
    elif event.char == "q":
        pause = True
        tkinter.Label(root, text="Quit   ", bg="black", fg="red", font=("Arial", 20)).place(x=puzzle_width + 20, y=950)
        canvas.delete("all")
        sys.exit()
    elif event.char == "p":
        pause = True
        is_run = False
        tkinter.Label(root, text="Pause  ", bg="black", fg="red", font=("Arial", 20)).place(x=puzzle_width + 20, y=950)



def key_event():
    root.bind("<Key>", key_press)


time_score, space, moves, size = read_info()
puzzle = read_puzzle(size)
draw_manu(size)
key_event()

root.mainloop()
