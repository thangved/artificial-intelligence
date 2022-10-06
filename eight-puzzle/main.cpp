#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

#define ROWS 3
#define COLS 3
#define EMPTY 0
#define OPERATORS 4

const std::string actions[] = {
    "First state",
    "Move cell EMPTY to UP",
    "Move cell EMPTY to DOWN",
    "Move cell EMPTY to LEFT",
    "Move cell EMPTY to RIGHT"};

typedef struct
{
    int eightPuzzle[ROWS][COLS];
    int empty_row;
    int empty_col;
} State;

typedef struct Node
{
    State state;
    struct Node *parent;
    int action;
    int heuristic;
} Node;

State get_goal_state()
{
    State state;
    state.empty_col = 0;
    state.empty_row = 0;

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            state.eightPuzzle[i][j] = i * COLS + j;
        }
    }

    return state;
}

void print_state(State state)
{
    std::cout << "-----\n";
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            std::cout << state.eightPuzzle[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "-----\n";
}

bool up_operator(State state, State &result)
{
    if (!state.empty_row)
    {
        return false;
    }

    result = state;

    result.eightPuzzle[state.empty_row][state.empty_col] = state.eightPuzzle[state.empty_row - 1][state.empty_col];

    result.eightPuzzle[state.empty_row - 1][state.empty_col] = EMPTY;

    result.empty_row--;

    return true;
}

bool down_operator(State state, State &result)
{
    if (state.empty_row == ROWS - 1)
    {
        return false;
    }

    result = state;

    result.eightPuzzle[state.empty_row][state.empty_col] = state.eightPuzzle[state.empty_row + 1][state.empty_col];

    result.eightPuzzle[state.empty_row + 1][state.empty_col] = EMPTY;

    result.empty_row++;

    return true;
}

bool left_operator(State state, State &result)
{
    if (!state.empty_col)
    {
        return false;
    }

    result = state;

    result.eightPuzzle[state.empty_row][state.empty_col] = state.eightPuzzle[state.empty_row][state.empty_col - 1];

    result.eightPuzzle[state.empty_row][state.empty_col - 1] = EMPTY;

    result.empty_col--;

    return true;
}

bool right_operator(State state, State &result)
{
    if (state.empty_col == COLS - 1)
    {
        return false;
    }

    result = state;

    result.eightPuzzle[state.empty_row][state.empty_col] = state.eightPuzzle[state.empty_row][state.empty_col + 1];

    result.eightPuzzle[state.empty_row][state.empty_col + 1] = EMPTY;

    result.empty_col++;

    return true;
}

bool cal_operator(const State &state, State &result, int op)
{
    switch (op)
    {
    case 1:
        return up_operator(state, result);
    case 2:
        return down_operator(state, result);
    case 3:
        return left_operator(state, result);
    case 4:
        return right_operator(state, result);

    default:
        std::cout << "Invalid operator";
    }
    return false;
}

bool compare_state(const State &state1, const State &state2)
{
    if (state1.empty_row != state2.empty_row)
    {
        return false;
    }

    if (state1.empty_col != state2.empty_col)
    {
        return false;
    }

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (state1.eightPuzzle[i][j] != state2.eightPuzzle[i][j])
            {
                return false;
            }
        }
    }

    return true;
}

bool is_goal(const State &state)
{
    return compare_state(state, get_goal_state());
}

bool is_existing_state(const std::vector<Node *> &vec, const State &state)
{
    for (auto st = vec.begin(); st != vec.end(); st++)
    {
        if (compare_state((*st)->state, state))
        {
            return true;
        }
    }
    return false;
}

int heuristic(const State &state)
{
    int count = 0;
    State goal = get_goal_state();

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            count += goal.eightPuzzle[i][j] != state.eightPuzzle[i][j];
        }
    }

    return count;
}

bool compare_heuristic(Node *a, Node *b)
{
    return a->heuristic < b->heuristic;
}

Node *find_goal(Node *root)
{
    std::vector<Node *> open_vec;
    std::vector<Node *> closed_vec;

    root->heuristic = heuristic(root->state);
    open_vec.push_back(root);

    while (!open_vec.empty())
    {
        Node *current_node = open_vec.front();
        open_vec.erase(open_vec.begin());
        closed_vec.push_back(current_node);

        if (is_goal(current_node->state))
        {
            return current_node;
        }

        for (int i = 1; i <= OPERATORS; i++)
        {
            State next_state;
            if (cal_operator(current_node->state, next_state, i))
            {

                if (!is_existing_state(closed_vec, next_state) && !is_existing_state(open_vec, next_state))
                {
                    Node *next_node = new Node;
                    next_node->parent = current_node;
                    next_node->state = next_state;
                    next_node->action = i;
                    next_node->heuristic = heuristic(next_state);
                    open_vec.push_back(next_node);

                    std::sort(open_vec.begin(), open_vec.end(), compare_heuristic);
                }
            }
        }
    }

    return NULL;
}

void print_nodes(Node *node)
{
    if (!node)
    {
        return;
    }

    print_nodes(node->parent);

    std::cout << "Action" << actions[node->action] << std::endl;

    print_state(node->state);
}

int main()
{
    Node *node = new Node;
    std::ifstream f;
    f.open("./data.txt");

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            f >> node->state.eightPuzzle[i][j];
            if (!node->state.eightPuzzle[i][j])
            {
                node->state.empty_row = i;
                node->state.empty_col = j;
            }
        }
    }
    f.close();

    Node *goal = find_goal(node);
    print_nodes(goal);

    return 0;
}
