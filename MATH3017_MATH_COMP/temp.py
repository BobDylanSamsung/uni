import sys
from copy import deepcopy

def print_board(board):
    for row in board:
        print(" ".join(row))
        print()

def check_winner(board, player):
    for row in board:
        if all([cell == player for cell in row]):
            return True

    for col in range(3):
        if all([board[row][col] == player for row in range(3)]):
            return True

    if all([board[i][i] == player for i in range(3)]) or all([board[i][2 - i] == player for i in range(3)]):
        return True

    return False

def is_full(board):
    return all([cell != ' ' for row in board for cell in row])

def minimax(board, depth, maximizing_player):
    if check_winner(board, 'O'):
        return -1
    elif check_winner(board, 'X'):
        return 1
    elif is_full(board):
        return 0

    if maximizing_player:
        max_eval = -sys.maxsize
        for row in range(3):
            for col in range(3):
                if board[row][col] == ' ':
                    new_board = deepcopy(board)
                    new_board[row][col] = 'X'
                    eval = minimax(new_board, depth + 1, False)
                    max_eval = max(max_eval, eval)
        return max_eval
    else:
        min_eval = sys.maxsize
        for row in range(3):
            for col in range(3):
                if board[row][col] == ' ':
                    new_board = deepcopy(board)
                    new_board[row][col] = 'O'
                    eval = minimax(new_board, depth + 1, True)
                    min_eval = min(min_eval, eval)
        return min_eval

def best_move(board):
    max_eval = -sys.maxsize
    move = None
    for row in range(3):
        for col in range(3):
            if board[row][col] == ' ':
                new_board = deepcopy(board)
                new_board[row][col] = 'X'
                eval = minimax(new_board, 0, False)
                if eval > max_eval:
                    max_eval = eval
                    move = (row, col)
    return move

def main():
    board = [[' ' for _ in range(3)] for _ in range(3)]
    print("Welcome to Tic Tac Toe!")
    print("Enter your move as row and column numbers separated by a space (0-2).")

    while not check_winner(board, 'X') and not check_winner(board, 'O') and not is_full(board):
        print_board(board)
        user_move = input("Your move: ")
        row, col = map(int, user_move.split())
        if board[row][col] == ' ':
            board[row][col] = 'O'
            if not check_winner(board, 'O') and not is_full(board):
                ai_move = best_move(board)
                board[ai_move[0]][ai_move[1]] = 'X'
        else:
            print("Invalid move. Try again.")

    print_board(board)
    if check_winner(board, 'X'):
        print("AI wins!")
    elif check_winner(board, 'O'):
        print("You win!")
    else:
        print("It's a draw!")

if __name__ == "__main__":
    main()
