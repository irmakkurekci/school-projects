#!!!!!----------------pip install dearpygui----------------------!!!!!
import dearpygui.dearpygui as dpg
import time
from gametree import * 

#init functions----------------------------------------------
def update_values(node = Node(0,[0, 0], 0, False, 0)):
    global curr_num, hum_score, ai_score, bank_score, isHumanTurn
    hum_score = node.ai_hum_scores[1]
    ai_score = node.ai_hum_scores[0]
    bank_score = node.bank
    isHumanTurn = node.isHumanTurn

    if curr_num == node.number:
        dpg.set_value("curr_num", f"Current number: {curr_num}")

    while curr_num < node.number:
        curr_num+=1
        dpg.set_value("curr_num", f"Current number: {curr_num}")
        if(curr_num < 100):
            time.sleep(0.01)
        elif (curr_num < 1000):
            time.sleep(0.001)
        elif (curr_num < 2000):
            time.sleep(0.0001)
        else:
            time.sleep(0.00001)

    dpg.set_value("hum_score", f"Human(your) score: {hum_score}")
    dpg.set_value("ai_score", f"AI score: {ai_score}")
    dpg.set_value("bank_score", f"Bank score: {bank_score}")
    dpg.set_value("turn_str", f"Turn: {'Human' if isHumanTurn else 'AI'}")



def strart_callback():  
    dpg.configure_item("main_menu", show = False)
    dpg.configure_item("game", show = True)
    dpg.set_primary_window(game_window, value=True)

    global curr_num, hum_score, ai_score, bank_score, isHumanTurn, isMiniMax
    curr_num = int(dpg.get_value("number"))
    isHumanTurn = True if dpg.get_value("first_turn") == "Human (you)" else False
    isMiniMax = True if dpg.get_value("algorithms") == "MiniMax" else False

    dpg.set_value("alg_str", f"Algorithm: {'MiniMax' if isMiniMax else 'Alpha-Beta'}")


    global game_logic
    game_logic = Game_logic(curr_num, isHumanTurn, isMiniMax)
    update_values(game_logic.gt.current_node)

    if not isHumanTurn:
        ai_move()
    else:
        dpg.configure_item("human_turn", show = True)

def multiply(user_data):
    dpg.configure_item("2", enabled = False)
    dpg.configure_item("3", enabled = False)
    dpg.configure_item("4", enabled = False)

    global game_logic
    if game_logic.gt.current_node.isHumanTurn:
        human_turn(user_data)


def human_turn(number):
    global game_logic
    curr_node = game_logic.gt.current_node 

    dpg.configure_item("human_turn", show = True)
    dpg.configure_item("ai_turn", show = False)

    for child in curr_node.children:
            if child.number == curr_node.number * int(number):
                game_logic.gt.current_node = child
                break

    update_values(game_logic.gt.current_node)
    if not check_end():
        ai_move()
    else:
        end_state()

def ai_move():
    global game_logic, think_strs
    dpg.configure_item("human_turn", show = False)

    dpg.configure_item("ai_turn", show = True)
    dpg.configure_item("think_str", show = True)
    dpg.configure_item("choosing", show = False)

    for i in range(9):
        dpg.set_value("think_str", f"AI is thinking {think_strs[i%3]}")
        time.sleep(0.11)

    dpg.configure_item("think_str", show = False)
    dpg.configure_item("choosing", show = True)

    new_node = game_logic.find_best_move()
    dpg.set_value("chosen_multiplier", f"AI has chosen multiplier {int(new_node.number // game_logic.gt.current_node.number)}")
    game_logic.gt.current_node = new_node

def after_move_ai():
    global game_logic
    update_values(game_logic.gt.current_node)
    if not check_end():
        dpg.configure_item("human_turn", show = True)
        dpg.configure_item("ai_turn", show = False)
        dpg.configure_item("2", enabled = True)
        dpg.configure_item("3", enabled = True)
        dpg.configure_item("4", enabled = True)
    else:
        end_state()

def check_end():
    global curr_num
    return curr_num >= 5000

def end_state():
    global game_logic, human_wins, ai_wins
    dpg.set_value("game_state", "GAME OVER")
    dpg.configure_item("game_state", pos = [window_width//2 - 300, window_height // 2 - 300])

    dpg.configure_item("human_turn", show = False)
    dpg.configure_item("ai_turn", show = False)
    dpg.configure_item("end", show = True)

    ai_hum_scores = game_logic.gt.current_node.ai_hum_scores
    if ai_hum_scores[0] - ai_hum_scores[1] > 0:
        dpg.set_value("winner_str", "Winner: AI!")
        ai_wins += 1
    elif ai_hum_scores[0] - ai_hum_scores[1] < 0:
        dpg.set_value("winner_str", "Winner: Human!")
        human_wins += 1
    else:
        dpg.set_value("winner_str", "It is a draw!")
        human_wins += 1
        ai_wins += 1

    dpg.set_value("wins", f"Human(your) wins: {human_wins}\n\nAI wins: {ai_wins}")
    dpg.configure_item("2", enabled = True)
    dpg.configure_item("3", enabled = True)
    dpg.configure_item("4", enabled = True)

def new_game():
    dpg.set_value("game_state", "GAME START")
    dpg.configure_item("game_state", pos = [window_width//2 - 325, window_height // 2 - 300])
    dpg.configure_item("end", show = False)

    dpg.configure_item("main_menu", show = True)
    dpg.configure_item("game", show = False)
    dpg.set_primary_window(main_menu_window, value=True)

#init GUI-----------------------------------------------------------    
dpg.create_context()

window_width = 1100
window_height = 700

game_logic = None
curr_num = 25
hum_score = 0
ai_score = 0
bank_score = 0
isHumanTurn = True
isMiniMax = True
think_strs = [".", "..", "..."]
human_wins = 0
ai_wins = 0

dpg.create_viewport(title="game_ai", decorated=True)
dpg.configure_viewport(0, x_pos=100, y_pos= 100, width = window_width, height = window_height)
dpg.set_viewport_max_height(window_height)
dpg.set_viewport_max_width(window_width)
dpg.set_viewport_min_width(window_width)
dpg.set_viewport_min_height(window_height)

with dpg.font_registry():
    smal_font = dpg.add_font(file="fonts/dogicapixel.ttf", size = 15)
    default_font = dpg.add_font(file="fonts/dogicapixel.ttf", size = 25)
    big_font = dpg.add_font(file="fonts/dogicapixelbold.ttf", size = 50)

#---------------------------------GAME WINDOW-----------------------------
with dpg.window(no_collapse=True, no_resize=True, no_close=True, show= False,
                no_title_bar=True, tag = "game") as game_window:
    
    with dpg.group():
        title = dpg.add_text(default_value="GAME START", 
                             pos = [window_width//2 - 325, window_height // 2 - 300], tag = "game_state")
        dpg.bind_item_font(title, big_font)

    with dpg.group():
        title = dpg.add_text(f"Current number: {curr_num}", tag = "curr_num",
                     pos = [window_width//2 - 250, window_height // 2 - 150])
        dpg.bind_item_font(title, default_font)
        
    with dpg.group(horizontal=True, horizontal_spacing=300, pos = [window_width//2 - 450, window_height // 2 - 50]):
        with dpg.group():
            dpg.add_text(f"Human(your) score: {hum_score}", tag = "hum_score")
            dpg.add_text(f"AI score: {ai_score}", tag = "ai_score")
            dpg.add_text(f"Bank score: {bank_score}", tag = "bank_score")

        with dpg.group():
            dpg.add_text(f"Turn: {'Human' if isHumanTurn else 'AI'}", tag="turn_str")
            dpg.add_text(f"Algorithm: {'MiniMax' if isMiniMax else 'Alpha-Beta pruning'}", tag="alg_str")


    with dpg.group(tag = "human_turn", show = True):
        with dpg.group():
            dpg.add_text(default_value="Choose by which digit to multiply the number:", 
                                pos = [window_width//2 - 360, window_height // 2 + 100], tag = "multiply_str")

        with dpg.group(horizontal=True, horizontal_spacing=100,
                    pos = [window_width//2 - 400, window_height // 2 + 150]):
            dpg.add_button(label="2", width = 200, height= 100, callback=multiply, tag = "2")
            dpg.add_button(label="3", width = 200, height= 100, callback=multiply, tag = "3")
            dpg.add_button(label="4", width = 200, height= 100, callback=multiply, tag = "4")

    with dpg.group(tag = "ai_turn", show = False):
        with dpg.group():
            dpg.add_text(default_value="AI is thinking", 
                                pos = [window_width//2 - 360, window_height // 2 + 100], tag = "think_str")

        with dpg.group(horizontal=True, horizontal_spacing=100,
                    pos = [window_width//2 - 400, window_height // 2 + 150], tag = "choosing", show=False):
            dpg.add_text("AI has chosen multiplier ", tag = "chosen_multiplier")
            dpg.add_button(label="next step", width = 200, height= 100, callback=after_move_ai, tag = "next")

    with dpg.group(tag = "end", show = False):
        with dpg.group():
            dpg.add_text(default_value="Winner: ", 
                                pos = [window_width//2 - 75, window_height // 2 + 100], tag = "winner_str")

        with dpg.group(horizontal=True, horizontal_spacing=150,
                    pos = [window_width//2 - 350, window_height // 2 + 150]):
            dpg.add_text("Human(your) wins: \n\nAI wins: ", tag = "wins")
            dpg.add_button(label="new game", width = 200, height= 100, callback=new_game, tag = "new_game")

#---------------------------------MAIN WINDOW-----------------------------
with dpg.window(no_collapse=True, no_resize=True, no_close=True,
                no_title_bar=True, tag = "main_menu") as main_menu_window:
    
    with dpg.group(horizontal=True):
        title = dpg.add_text(default_value="GAME WITH AI", 
                             pos = [window_width//2 - 375, window_height // 2 - 300])
        dpg.bind_item_font(title, big_font)

    with dpg.group():
        title = dpg.add_text("Settings:",
                     pos = [window_width//2 - 150, window_height // 2 - 150])
        dpg.bind_item_font(title, default_font)
        
    with dpg.group():
        dpg.add_text("Select an algorithm: ",
                     pos = [window_width//2 - 425, window_height // 2 - 85])

        dpg.add_radio_button(items=["MiniMax", "Alpha-Beta pruning"], tag = "algorithms", horizontal=True, 
                            default_value="MiniMax", pos = [window_width//2 - 375, window_height // 2 - 45])
        
    with dpg.group():
        dpg.add_text("Select who goes first: ",
                     pos = [window_width//2 - 425, window_height // 2 + 20 ])

        dpg.add_radio_button(items=["Human (you)", "AI"], tag = "first_turn", horizontal=True, 
                        default_value="Human (you)", pos = [window_width//2 - 375, window_height // 2 + 60])
        
    with dpg.group(horizontal=True):
        dpg.add_text("Enter number from 25 to 45: ",
                     pos = [window_width//2 - 425, window_height // 2 + 120 ])
        
        dpg.add_input_int(width = 300,default_value=25, min_value=25, max_value=45, tag = "number", 
                          min_clamped=True, max_clamped=True,
                          pos= [window_width//2 - 375, window_height // 2 + 165])
        dpg.add_button(label="START", width = 200, height= 100, callback=strart_callback,
                       pos = [window_width//2 + 200, window_height // 2 + 145 ])
        

dpg.bind_font(smal_font)

dpg.set_primary_window(window = main_menu_window, value = True)

dpg.show_viewport()
dpg.setup_dearpygui()
dpg.start_dearpygui()
dpg.destroy_context()