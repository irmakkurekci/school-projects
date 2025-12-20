import tkinter as tk
from tkinter import messagebox
import random
from PIL import Image, ImageTk
import time

# Function to clear the frame
def clear_frame(frame):
    for widget in frame.winfo_children():
        widget.destroy()

first_click = None
second_click = None
check_in_progress = False
points = 80
cell_values = {'pic_1': 1 , 'text_1': 1, 'pic_2': 2 , 'text_2': 2, 'pic_3': 3 , 'text_3': 3,'pic_4': 4 , 'text_4': 4, 'pic_5': 5 , 'text_5': 5, 'pic_6': 6 , 'text_6': 6,
'pic_7': 7 , 'text_7': 7, 'pic_8': 8 , 'text_8': 8, 'pic_9': 9 , 'text_9': 9,'pic_10': 10 , 'text_10': 10, 'pic_11': 11 , 'text_11': 11, 'pic_12': 12 , 'text_12': 12,
'pic_13': 13 , 'text_13': 13, 'pic_14': 14 , 'text_14': 14, 'pic_15': 15 , 'text_15': 15,'pic_16': 16 , 'text_16': 16, 'pic_17': 17 , 'text_17': 17, 'pic_18': 18 , 'text_18': 18,
'pic_19': 19 , 'text_19': 19, 'pic_20': 20 , 'text_20': 20, 'pic_21': 21 , 'text_21': 21,'pic_22': 22 , 'text_22': 22, 'pic_23': 23 , 'text_23': 23, 'pic_24': 24 , 'text_24': 24,
'pic_25': 25 , 'text_25': 25, 'pic_26': 26 , 'text_26': 26, 'pic_27': 27 , 'text_27': 27,'pic_28': 28 , 'text_28': 28, 'pic_29': 29 , 'text_29': 29, 'pic_30': 30 , 'text_30': 30,
'pic_31': 31 , 'text_31': 31, 'pic_32': 32 , 'text_32': 32, 'pic_33': 33 , 'text_33': 33,'pic_34': 34 , 'text_34': 34, 'pic_35': 35 , 'text_35': 35, 'pic_36': 36 , 'text_36': 36}

lingoMatch_dict = {1:{'pic_1': 1 , 'text_1': 1} , 2:{'pic_2': 2 , 'text_2': 2} , 3:{'pic_3': 3 , 'text_3': 3} , 4:{'pic_4': 4 , 'text_4': 4} , 5:{'pic_5': 5 , 'text_5': 5} , 6:{'pic_6': 6 , 'text_6': 6}, 
7:{'pic_7': 7 , 'text_7': 7}, 8:{'pic_8': 8 , 'text_8': 8}, 9:{'pic_9': 9 , 'text_9': 9}, 10:{'pic_10': 10 , 'text_10': 10}, 11:{'pic_11': 11 , 'text_11': 11}, 12:{'pic_12': 12 , 'text_12': 12},
13:{'pic_13': 13 , 'text_13': 13}, 14:{'pic_14': 14 , 'text_14': 14}, 15:{'pic_15': 15 , 'text_15': 15}, 16:{'pic_16': 16 , 'text_16': 16}, 17:{'pic_17': 17 , 'text_17': 17}, 18:{'pic_18': 18 , 'text_18': 18},
19:{'pic_19': 19 , 'text_19': 19}, 20:{'pic_20': 20 , 'text_20': 20}, 21:{'pic_21': 21 , 'text_21': 21}, 22:{'pic_22': 22 , 'text_22': 22}, 23:{'pic_23': 23 , 'text_23': 23}, 24:{'pic_24': 24 , 'text_24': 24},
25:{'pic_25': 25 , 'text_25': 25}, 26:{'pic_26': 26 , 'text_26': 26}, 27:{'pic_27': 27 , 'text_27': 27}, 28:{'pic_28': 28 , 'text_28': 28}, 29:{'pic_29': 29 , 'text_29': 29}, 30:{'pic_30': 30 , 'text_30': 30},
31:{'pic_31': 31 , 'text_31': 31}, 32:{'pic_32': 32 , 'text_32': 32}, 33:{'pic_33': 33 , 'text_33': 33}, 34:{'pic_34': 34 , 'text_34': 34}, 35:{'pic_35': 35 , 'text_35': 35}, 36:{'pic_36': 36 , 'text_36': 36}}

questions = [
    {"question": "Nous ____ à la plage tous les étés.", "options": ["jouer", "aller", "conduire", "écouter"], "answer": "aller"},
    {"question": "Tu ____ très bien le piano.", "options": ["aller", "écouter", "conduire", "jouer"], "answer": "jouer"},
    {"question": "Il ____ à Paris depuis 2010.", "options": ["vivre", "apprendre", "lire", "voir"], "answer": "vivre"},
    {"question": "Elles ____ la vérité.", "options": ["aller", "connaître", "apprendre", "étudier"], "answer": "apprendre"},
    {"question": "Je ____ mon ami.", "options": ["donner", "voir", "étudier", "être"], "answer": "voir"},
    {"question": "Vous ____ trop vite en ville. ", "options": ["partir", "aller", "faire", "conduire"], "answer": "conduire"},
    {"question": "Elle ____ un livre en ce moment.", "options": ["jouer", "lire", "écouter", "vivre"], "answer": "lire"},
    {"question": "Nous ____ de notre mieux.", "options": ["voir", "apprendre", "faire", "lire"], "answer": "faire"},
    {"question": "Tu ____ à l'heure à ton rendez-vous ?", "options": ["arriver", "finir", "faire", "aller"], "answer": "arriver"},
    {"question": "Ils ____ de la musique classique. ", "options": ["lire", "apprendre", "écouter", "voir"], "answer": "écouter"},
    {"question": "Je ____ mes devoirs après le dîner.", "options": ["finir", "apprendre", "arriver", "vivre"], "answer": "finir"},
    {"question": "Vous ____ depuis longtemps ?", "options": ["conduire", "connaître", "conduire", "voir"], "answer": "connaître"},
    {"question": "Elle ____ une belle robe pour la fête.", "options": ["jouer", "étudier", "voir", "porter"], "answer": "porter"},
    {"question": "Nous ____ au marché tous les dimanches.", "options": ["lire", "finir", "aller", "jouer"], "answer": "aller"},
    {"question": "Tu ____ ton examen si tu révises bien.", "options": ["réussir", "aller", "étudier", "voir"], "answer": "réussir"},
    {"question": "Il ____ tôt le matin.", "options": ["finir", "partir", "étudier", "aller"], "answer": "partir"},
    {"question": "Elles ____ ensemble à l'université.", "options": ["être", "arriver", "aller", "étudier"], "answer": "étudier"},
    {"question": "Je ____ en bonne santé.", "options": ["être", "étudier", "arriver", "réussir"], "answer": "être"},
    {"question": "Vous ____ un discours inspirant.", "options": ["être", "donner", "emménager", "étudier"], "answer": "donner"},
    {"question": "Ils ____ dans un nouvel appartement.", "options": ["étudier", "être", "porter", "emménager"], "answer": "emménager"}
    # Add more questions as needed
]


current_image_index = 0
photo_left = None
photo_right = None
current_question_index = 0 
lingorace_active = False
timer_id = None
mini_map = None
player_position = 0.0
player_indicator = None
number_of_right_answers = 0
opponent_indicator = None
opponent_position = 0.0
mini_map_1 = None
opponent_id = None
match = False

# Function to update the points display
def update_points_display():
    points_label.config(text=f"Points: {points}")

def lingo_match_shuffle(lingoMatch_dict):
    lingomatch_list = []
    final_list = []
    final_lingomatch_list = []
    items = list(lingoMatch_dict.items())
    random.shuffle(items)
    shuffled_dict = dict(items)

    for counter in range(18):
        lingomatch_list.append(list(shuffled_dict.values())[counter])

    for counter_1 in lingomatch_list:
        final_list.append(list(counter_1.items()))

    for counter_2 in final_list:
        for counter_3 in counter_2:
            final_lingomatch_list.append(counter_3)

    random.shuffle(final_lingomatch_list)

    return final_lingomatch_list

def check_match(first_button, second_button):
    return True

# Function to check for a match and handle the points and display accordingly
'''def check_for_match(first_button, second_button, photo1, photo2, points_label):
    global points
    if check_match(first_button, second_button):  # You'll define this function based on your database check
        # If there's a match, do not revert images, just disable the buttons
        first_button.config(state='disabled')
        second_button.config(state='disabled')
        # Update points display (optional, since points don't change on a correct match)
        update_points_display()
    else:
        # If there's no match, revert the images and deduct a point
        revert_or_keep_images(first_button, second_button, photo1)
        points -= 1
        update_points_display()'''

# Function to revert images back to original after 2 seconds
def revert_or_keep_images(first_button, second_button, photo1):
    global points, match
    
    first_button.config(image=photo1)
    second_button.config(image=photo1)
    first_button.image = photo1
    second_button.image = photo1
    points -= 1  # Decrease points if not a match
    update_points_display()
    match = False

    # Reset the click trackers
    global first_click, second_click, check_in_progress
    first_click = None
    second_click = None
    check_in_progress = False


def check_for_match(photo1, points_label):
    global points, match, check_in_progress, first_click, second_click
    if first_click and second_click:
        if first_click.values == second_click.values:
            first_click.config(state='disabled')
            second_click.config(state='disabled')
            #match = True
            check_in_progress = False
            first_click = None
            second_click = None
            # Handle the match (e.g., keep cells revealed, update score)
        else:
            revert_or_keep_images(first_click, second_click, photo1)
            update_points_display()
            # Handle the mismatch (e.g., reset cells to hide their values/images)



# Function to handle cell click
def on_cell_click(event, cell_button, photo1, photo2, points_label):
    global first_click, second_click, check_in_progress
    # If a check is already in progress, ignore the click
    if check_in_progress:
        return
    
    cell_button.config(image=photo2)
    cell_button.image = photo2

    clicked_cell = event.widget  # Get the clicked cell/widget
    if first_click is None:
        first_click = clicked_cell
        # Optionally, reveal the value/image of the first cell
    elif second_click is None and clicked_cell != first_click:
        second_click = clicked_cell
        check_in_progress = True
        cell_button.after(1600, check_for_match, photo1, points_label)
        #check_for_match(first_click, second_click, photo1, points_label)



def go_home():
    clear_frame(main_frame)  # Clear the current frame or window
    show_home_screen() 



def update_image_lingolearn(index,cell_values):
    global current_image_index
    current_image_index = index
    
    # Update image on the left
    image_left = Image.open(f"{list(cell_values.keys())[index]}.png")
    photo_left = ImageTk.PhotoImage(image_left.resize((380, 380)))  # Resize as needed
    label_image_left.config(image=photo_left)
    label_image_left.image = photo_left  # Keep a reference

    # Update image on the right
    if index+1 < len(cell_values):
        image_right = Image.open(f"{list(cell_values.keys())[index+1]}.png")
        photo_right = ImageTk.PhotoImage(image_right.resize((380, 380)))  # Resize as needed
        label_image_right.config(image=photo_right)
        label_image_right.image = photo_right  # Keep a reference
    else:
        label_image_right.config(image='pic_1.png')
        index = 0  # No more images on the right

# Function for the "Next" button
def next_image():
    global current_image_index
    if current_image_index + 2 < len(cell_values):
        update_image_lingolearn(current_image_index + 2,cell_values)

# Function for the "Previous" button
def previous_image():
    global current_image_index
    if current_image_index - 2 >= 0:
        update_image_lingolearn(current_image_index - 2,cell_values)

def create_home_button():
    btn_home = tk.Button(main_frame, font= ("Centaur", 18,"bold"), text="Home Page", command=go_home, width=12, height=2, bg='gray')
    btn_home.place(relx=0.95, rely=0.05, x=-2, y=2, anchor="ne")


def answer_question(selected_option, correct_answer):
    global current_question_index, number_of_right_answers, lingorace_active, timer_id
    if selected_option == correct_answer:
        update_mini_map()
        number_of_right_answers += 1

    current_question_index += 1
    if number_of_right_answers > 6:
        messagebox.showinfo("Winner", "Congratulations! You won the game!")
        current_question_index = 0
        show_home_screen()

    elif current_question_index < len(questions):
        show_question(questions[current_question_index])
    else:
        messagebox.showinfo("End", "It seems you are out of fuel! Better luck next time.")
        current_question_index = 0  # Reset for next time
        show_home_screen()

def start_timer():
    global timer_id
    timer_id = root.after(70000, time_up)

# Function to handle time up
def time_up():
    global current_question_index
    if lingorace_active:
        messagebox.showinfo("Time's Up", "Sorry I'm quite good in this game! Better luck next time.")
        current_question_index = 0  # Reset for next time
        show_home_screen()


def show_question(question):

    question_label = tk.Label(main_frame, text=question["question"], font=('Centaur', 22), width=60, height=1, bg='light blue')
    question_label.place(relx=0.5, rely=0.2, anchor="center")

    for counter_10, option in enumerate(question["options"]):
        option_button = tk.Button(main_frame, text=option, command=lambda o=option: answer_question(o, question["answer"]), font=('Centaur', 14), width=8, height=1, bg='light blue')
        option_button.place(relx=(counter_10*0.1)+0.35, rely=0.26, anchor="center")

def end_lingorace():
    global lingorace_active, current_question_index, timer_id
    if timer_id:
        root.after_cancel(timer_id)
        timer_id = None
    lingorace_active = False
    current_question_index = 0  # Reset for next time
    show_home_screen()


def update_mini_map():
    global player_position, mini_map, player_indicator
    if player_position < mini_map.winfo_width() - 10:  # Subtract width of the indicator
        player_position += (mini_map.winfo_width() * 0.138)
        mini_map.coords(player_indicator, player_position, 10, player_position+10, 40)

def update_opponent_position():
    global opponent_position, mini_map_1, opponent_indicator, opponent_id, lingorace_active
    if lingorace_active and mini_map_1.winfo_exists():
        if opponent_position < mini_map_1.winfo_width() - 10:  # Check if there's space to move forward
            opponent_position += (mini_map_1.winfo_width() * 0.138)  # Update position
            mini_map_1.coords(opponent_indicator, opponent_position, 10, opponent_position+10, 40)  # Move indicator
            opponent_id = root.after(10000, update_opponent_position)

def opponent_start_timer():
    global opponent_id, lingorace_active
    opponent_id = root.after(10000, update_opponent_position)


# Function to start the game
def show_lingomatch():
    global points, points_label

    clear_frame(main_frame)
    
    main_frame.update()

    background_canvas = tk.Canvas(main_frame, width=1100, height=900)
    background_canvas.pack(fill='both', expand=True)
    background_canvas.create_image(0, 0, image=lingomatch_background_photo, anchor='nw')
    # Assuming 'main_frame' contains your grid
    main_frame.place(relx=0.5, rely=0.5, anchor='center')
    points_label = tk.Label(main_frame, text=f"Points: {points}", font=('Centaur', 24), width=8, height=1)
    points_label.place(relx=0.93, rely=0.16, x=-2, y=2, anchor="ne")
    create_home_button()
    

    image1 = Image.open('1.png')  # Replace with your image path
    image1 = image1.resize((125, 125), Image.ANTIALIAS)
    photo1 = ImageTk.PhotoImage(image1)

    col = 0
    # Create a 7x6 grid of buttons with images
    for i, counter_11 in enumerate(lingo_match_shuffle(lingoMatch_dict)):
        row = i%6
        if row == 0 and i != 0:
            col += 1
        # Load the first image for the button
        image2 = Image.open(f"{counter_11[0]}.png")
        image2 = image2.resize((125, 125), Image.ANTIALIAS)
        photo2 = ImageTk.PhotoImage(image2)

        # Create a button with the first image
        cell = tk.Button(main_frame, image=photo1, width=125, height=125, bg='light green', bd=0)
        cell.image = photo1  # Keep a reference so the image does not get garbage collected
        cell.values = counter_11[1]
        cell.place(relx=((row+1)/9)-0.02, rely=((col+1)/7)-0.03, anchor="center")  # Increase padx and pady to add space between cells
        cell.bind('<Button-1>', lambda event, cell_button=cell, p1=photo1, p2=photo2: on_cell_click(event, cell_button, p1, p2, points_label))

def show_lingolearn():

    clear_frame(main_frame)
    global label_image_left, label_image_right, lingolearn_background_photo

    background_canvas = tk.Canvas(main_frame, width=1100, height=900)
    background_canvas.pack(fill='both', expand=True)
    background_canvas.create_image(0, 0, image=lingolearn_background_photo, anchor='nw')

    
    # Create labels to display images
    
    label_image_left = tk.Label(main_frame)
    label_image_left.place(relx=0.20, rely=0.35, anchor='center')
    
    label_image_right = tk.Label(main_frame)
    label_image_right.place(relx=0.55, rely=0.35, anchor='center')

    
    # Create "Previous" and "Next" buttons
    btn_previous = tk.Button(main_frame, font= ("Centaur", 18,"bold"), text='Previous', command=previous_image, width=9, height=1, bg='red')
    btn_previous.place(relx=0.30, rely=0.65, anchor='center')

    btn_next = tk.Button(main_frame, font= ("Centaur", 18,"bold"), text='Next', command=next_image, width=9, height=1, bg='light green')
    btn_next.place(relx=0.45, rely=0.65, anchor='center')

    create_home_button()
    update_image_lingolearn(current_image_index,cell_values)

def show_lingorace():
    global lingorace_active, player_position, mini_map, player_indicator, timer_id, opponent_indicator, opponent_position, mini_map_1
    clear_frame(main_frame)

    background_canvas = tk.Canvas(main_frame, width=1100, height=900)
    background_canvas.pack(fill='both', expand=True)
    background_canvas.create_image(0, 0, image=lingorace_background_photo, anchor='nw')
    main_frame.place(relx=0.5, rely=0.5, anchor='center')
    create_home_button()
    lingorace_active = True 
    show_question(questions[current_question_index])
    mini_map = tk.Canvas(main_frame, width=420, height=50, bg='Green')
    mini_map.place(relx=0.25, rely=0.7, anchor='center')
    mini_map_1 = tk.Canvas(main_frame, width=420, height=50, bg='Green')
    mini_map_1.place(relx=0.25, rely=0.76, anchor='center')
    end_line = tk.Canvas(main_frame, width=3, height=120, bg='Black')
    end_line.place(relx=0.425, rely=0.73, anchor='center')
    player_indicator = mini_map.create_rectangle(player_position, 10, player_position+10, 40, fill="blue")
    opponent_indicator = mini_map_1.create_rectangle(opponent_position, 10, opponent_position+10, 40, fill="red")
    start_timer()
    opponent_start_timer()
    



def show_home_screen():
    # Clear existing widgets
    clear_frame(main_frame)
    global background_photo,lingorace_active, timer_id, player_position, number_of_right_answers, opponent_position, points	
    player_position = 0.0
    opponent_position = 0.0
    number_of_right_answers = 0
    points = 80
    if lingorace_active and timer_id:
        root.after_cancel(timer_id)  # Cancel the timer if returning to home
    lingorace_active = False
    
    background_canvas = tk.Canvas(main_frame, width=1100, height=900)
    background_canvas.pack(fill='both', expand=True)
    background_canvas.create_image(0, 0, image=background_photo, anchor='nw')


    btn_lingolearn = tk.Button(main_frame, font= ("Centaur", 18,"bold"), text="LingoLearn", command=show_lingolearn, width=12, height=2, bg='light blue')
    btn_lingolearn.place(relx=0.12, rely=0.09, anchor='center')

    btn_lingomatch = tk.Button(main_frame, font= ("Centaur", 18,"bold"), text="LingoMatch", command=show_lingomatch, width=12, height=2, bg='light blue')
    btn_lingomatch.place(relx=0.12, rely=0.22, anchor='center')

    btn_lingorace = tk.Button(main_frame, font= ("Centaur", 18,"bold"), text="LingoRace", command=show_lingorace, width=12, height=2, bg='light blue')
    btn_lingorace.place(relx=0.12, rely=0.35, anchor='center')

# Create the main window
root = tk.Tk()
root.title('LingoLeap')
root.geometry('1100x900')

root.config(bg='light cyan')

# Create a frame to hold the content
main_frame = tk.Frame(root, width=1100, height=900)
main_frame.pack(expand=True, fill='both')

background_image = Image.open('background2.png')
background_photo = ImageTk.PhotoImage(background_image.resize((1100, 900), Image.ANTIALIAS))
ligolearn_background_image = Image.open('lingolearn_background.png')
lingolearn_background_photo = ImageTk.PhotoImage(ligolearn_background_image.resize((1100, 900), Image.ANTIALIAS))
ligomatch_background_image = Image.open('lingomatch_background.png')
lingomatch_background_photo = ImageTk.PhotoImage(ligomatch_background_image.resize((1100, 900), Image.ANTIALIAS))
ligorace_background_image = Image.open('lingorace_background.png')
lingorace_background_photo = ImageTk.PhotoImage(ligorace_background_image.resize((1100, 900), Image.ANTIALIAS))


show_home_screen()

root.mainloop()








