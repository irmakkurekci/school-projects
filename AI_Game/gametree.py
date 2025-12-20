class Node:
    def __init__(self, number, ai_hum_scores, bank, isHumanTurn, level):
        self.number = number
        self.ai_hum_scores = ai_hum_scores.copy()
        self.bank = bank
        self.isHumanTurn = isHumanTurn
        self.children = []
        self.level = level
        self.best_score = float("-inf")

class Game_tree:
    def __init__(self, number, isHumanTurn):
        self.current_node = Node(number, [0, 0], 0, isHumanTurn, 1)
        self.create_tree(self.current_node)

    def check_score(self, node):

        if node.number % 2 == 0:
            node.ai_hum_scores[not node.isHumanTurn] -= 1
        else:
            node.ai_hum_scores[not node.isHumanTurn] += 1
        if node.number % 5 == 0:
            node.bank += 1

        if node.number >= 5000:
            node.ai_hum_scores[not node.isHumanTurn] += node.bank
            node.bank = 0
            return node
        
        return node

    def check_win(self, node):
        return node.number >= 5000

    def create_tree(self, node):
        for coef in [2,3,4]:
            curr_number = node.number * coef

            node.children.append(self.check_score(Node(curr_number, node.ai_hum_scores, node.bank, not node.isHumanTurn, node.level + 1)))
            if not self.check_win(node.children[len(node.children) - 1]):
                self.create_tree(node.children[len(node.children) - 1])


    def print_tree(self, node):
        print("num: ",node.number,"\tBank score", node.bank ,"\tai and human score: ", node.ai_hum_scores,"\thuman turn: ", node.isHumanTurn, '\tLevel: ', node.level)
        for i in node.children:
            self.print_tree(i)

class Game_logic:
    def __init__(self, number, isHumanTurn, isMiniMax):
        self.gt = Game_tree(number, isHumanTurn)
        self.isMiniMax = isMiniMax

    def mini_max(self, node):
        if node.children == []:
            return node.ai_hum_scores[False] - node.ai_hum_scores[True]

        if node.isHumanTurn:
            best_value = float('inf')
            for child in node.children:
                value = self.mini_max(child)
                best_value = min(best_value, value)
            return best_value
        else:
            best_value = float('-inf')
            for child in node.children:
                value = self.mini_max(child)
                best_value = max(best_value, value)
            return best_value

    def alpha_beta(self, node, alpha = float('-inf'), beta = float('inf')):
        if node.children == []:
            return node.ai_hum_scores[False] - node.ai_hum_scores[True]
        
        if node.isHumanTurn:
            best_value = float('inf')
            for child in node.children:
                value = self.alpha_beta(child, alpha, beta)
                best_value = min(best_value, value)
                beta = min(beta, value)

                if beta <= alpha:
                    break
            return best_value
        else:
            best_value = float('-inf')
            for child in node.children:
                value = self.alpha_beta(child, alpha, beta)
                best_value = max(best_value, value)
                alpha = max(alpha, value)

                if beta <= alpha:
                    break
            return best_value

    def find_best_move(self):
        best_value = float('-inf')
        best_move = None
        if self.isMiniMax:
            for child in self.gt.current_node.children:
                value = self.mini_max(child)
                if value > best_value:
                    best_value = value
                    best_move = child
        else:
            for child in self.gt.current_node.children:
                value = self.alpha_beta(child)
                if value > best_value:
                    best_value = value
                    best_move = child

        return best_move