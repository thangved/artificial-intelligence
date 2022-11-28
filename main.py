from tkinter import *
import time

CELL_WIDTH = 40

start = (1, 0)

goal = (14, 16)

GAME = [
    [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1],
    [1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1],
    [1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1],
    [1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1],
    [1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1],
    [1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1],
    [1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1],
    [1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1],
    [1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1],
    [1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1],
    [1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1],
    [1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1],
    [1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1],
    [1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0],
    [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
]

win = Tk()
win.config(bg="#ffffff")
canvas = Canvas(win, bg="#ffffff", width=CELL_WIDTH *
                GAME[0].__len__(), height=CELL_WIDTH * GAME.__len__())
canvas.pack(side=TOP)

for i in range(len(GAME)):
    for j in range(len(GAME[i])):
        if GAME[i][j] == 1:
            canvas.create_rectangle(
                j * CELL_WIDTH, i * CELL_WIDTH, (j + 1) * CELL_WIDTH, (i + 1) * CELL_WIDTH, fill='#000000', outline='')

canvas.create_oval(start[1] * CELL_WIDTH + 2, start[0]
                   * CELL_WIDTH + 2, (start[1] + 1) * CELL_WIDTH - 2, (start[0] + 1) * CELL_WIDTH - 2, fill='red', outline='')

canvas.create_oval(goal[1] * CELL_WIDTH + 2, goal[0]
                   * CELL_WIDTH + 2, (goal[1] + 1) * CELL_WIDTH - 2, (goal[0] + 1) * CELL_WIDTH - 2, fill='#ffffff', outline='green')


def find_next_state(current: tuple, hash: dict):
    result = []

    # Move up
    if current[0] != 0 and GAME[current[0] - 1][current[1]] != 1:
        next = (current[0] - 1, current[1])
        if next not in hash.keys():
            result.append(next)

    # Move down
    if current[0] != len(GAME) - 1 and GAME[current[0] + 1][current[1]] != 1:
        next = (current[0] + 1, current[1])
        if next not in hash.keys():
            result.append(next)

    # Move left
    if current[1] != 0 and GAME[current[0]][current[1] - 1] != 1:
        next = (current[0], current[1] - 1)
        if next not in hash.keys():
            result.append(next)

    # Move right
    if current[1] != len(GAME[0]) - 1 and GAME[current[0]][current[1] + 1] != 1:
        next = (current[0], current[1] + 1)
        if next not in hash.keys():
            result.append(next)

    return result


def dfs(current_state: tuple, hash: dict):

    canvas.create_oval(current_state[1] * CELL_WIDTH + 2, current_state[0]
                       * CELL_WIDTH + 2, (current_state[1] + 1) * CELL_WIDTH - 2, (current_state[0] + 1) * CELL_WIDTH - 2, fill='red', outline='')

    if current_state == goal:
        return True

    hash[current_state] = True

    next_states = find_next_state(current_state, hash)

    for next_state in next_states:
        if dfs(next_state, hash):
            return True

    canvas.create_oval(current_state[1] * CELL_WIDTH + 2, current_state[0]
                       * CELL_WIDTH + 2, (current_state[1] + 1) * CELL_WIDTH - 2, (current_state[0] + 1) * CELL_WIDTH - 2, fill='#cccccc', outline='')

    return False


def on_click():
    print(dfs(start, dict()))


Button(win, text="Find", command=on_click).pack(side=TOP)

win.geometry('800x800')
win.mainloop()
