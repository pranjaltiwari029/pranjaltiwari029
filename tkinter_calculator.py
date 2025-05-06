import tkinter as tk

# Function to update the expression in the entry widget
def press(key):
    current = entry.get()
    entry.delete(0, tk.END)  # Clear current display
    entry.insert(tk.END, current + str(key))  # Insert new key

# Function to evaluate the expression
def evaluate():
    try:
        expression = entry.get()
        result = str(eval(expression))  # Evaluate the expression
        entry.delete(0, tk.END)
        entry.insert(tk.END, result)  # Display the result
    except Exception:
        entry.delete(0, tk.END)
        entry.insert(tk.END, "Error")  # Handle errors (e.g., invalid expression)

# Function to clear the display
def clear():
    entry.delete(0, tk.END)

# Create the main window
root = tk.Tk()
root.title("Basic Calculator")  # Set the window title
root.geometry("400x500")  # Set window size

# Create the entry widget for the display
entry = tk.Entry(root, font=("Arial", 20), borderwidth=2, relief="solid", width=16, justify='right')
entry.grid(row=0, column=0, columnspan=4)

# Create buttons for digits and operators
buttons = [
    ('7', 1, 0), ('8', 1, 1), ('9', 1, 2), ('/', 1, 3),
    ('4', 2, 0), ('5', 2, 1), ('6', 2, 2), ('*', 2, 3),
    ('1', 3, 0), ('2', 3, 1), ('3', 3, 2), ('-', 3, 3),
    ('0', 4, 0), ('.', 4, 1), ('=', 4, 2), ('+', 4, 3),
    ('C', 5, 0)
]

# Add buttons to the window
for (text, row, col) in buttons:
    if text == "=":
        button = tk.Button(root, text=text, font=("Arial", 20), command=evaluate)
    elif text == "C":
        button = tk.Button(root, text=text, font=("Arial", 20), command=clear)
    else:
        button = tk.Button(root, text=text, font=("Arial", 20), command=lambda key=text: press(key))
    button.grid(row=row, column=col, sticky="nsew", ipadx=10, ipady=10)

# Make buttons expand to fill the window evenly
for row in range(1, 6):
    root.grid_rowconfigure(row, weight=1)

for col in range(4):
    root.grid_columnconfigure(col, weight=1)

# Start the main event loop
root.mainloop()
