import tkinter as tk
from tkinter import messagebox

def on_button_click():
    messagebox.showinfo("Hello", "You clicked the button!")

root = tk.Tk()
root.title("First Tkinter Program")
root.geometry("300x200")

label = tk.Label(root, text="using Tkinter!", font=("Arial", 14))
label.pack(pady=20)

button = tk.Button(root, text="press here", command=on_button_click)
button.pack(pady=10)

root.mainloop()
