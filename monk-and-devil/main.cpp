#include <iostream>
#include <stack>

#define COUNT_MONK 3
#define COUNT_DEVIL 3
#define COUNT_ACTIONS 5

typedef struct
{
    int monk;
    int devil;
    int board_pos;
} State;

typedef struct Node
{
    State state;
    struct Node *parent;
} Node;

State create_state()
{
    return {COUNT_MONK, COUNT_DEVIL, 0};
}

Node *create_node(State state = create_state(), Node *parent = NULL)
{
    Node *node = (Node *)malloc(sizeof(Node));

    node->parent = parent;
    node->state = state;

    return node;
}

bool is_goal(State state)
{
    return !state.monk && !state.devil;
}

bool check_state(State state)
{
    if (state.monk < 0 || state.devil < 0 || state.monk > COUNT_MONK || state.devil > COUNT_DEVIL)
    {
        return false;
    }

    if (state.monk == COUNT_MONK || !state.monk)
    {
        return true;
    }

    if (state.devil != state.monk)
    {
        return false;
    }

    return true;
}

State get_next_state(State cur_st)
{
    cur_st.board_pos = !cur_st.board_pos;
    return cur_st;
}

bool move1monk(State cur_st, State &next_st)
{
    next_st = get_next_state(cur_st);
    switch (cur_st.board_pos)
    {
    case 0:
        next_st.monk--;
        break;

    case 1:
        next_st.monk++;
        break;
    default:
        return false;
    }

    return check_state(next_st);
}

bool move1devil(State cur_st, State &next_st)
{
    next_st = get_next_state(cur_st);
    switch (cur_st.board_pos)
    {
    case 0:
        next_st.devil--;
        break;

    case 1:
        next_st.devil++;
        break;
    default:
        return false;
    }

    return check_state(next_st);
}

bool move2monk(State cur_st, State &next_st)
{
    next_st = get_next_state(cur_st);
    switch (cur_st.board_pos)
    {
    case 0:
        next_st.monk -= 2;
        break;

    case 1:
        next_st.monk += 2;
        break;
    default:
        return false;
    }

    return check_state(next_st);
}

bool move2devil(State cur_st, State &next_st)
{
    next_st = get_next_state(cur_st);
    switch (cur_st.board_pos)
    {
    case 0:
        next_st.devil -= 2;
        break;

    case 1:
        next_st.devil += 2;
        break;
    default:
        return false;
    }

    return check_state(next_st);
}

bool move1monk1devil(State cur_st, State &next_st)
{
    next_st = get_next_state(cur_st);
    switch (cur_st.board_pos)
    {
    case 0:
        next_st.devil -= 1;
        next_st.monk -= 1;
        break;

    case 1:
        next_st.devil += 1;
        next_st.monk += 1;
        break;
    default:
        return false;
    }

    return check_state(next_st);
}

bool call_action(State cur_st, State &next_st, int num_action)
{
    switch (num_action)
    {
    case 1:
        return move1monk(cur_st, next_st);
    case 2:
        return move1devil(cur_st, next_st);
    case 3:
        return move2monk(cur_st, next_st);
    case 4:
        return move2devil(cur_st, next_st);
    case 5:
        return move1monk1devil(cur_st, next_st);
    default:
        return false;
    }
}

Node *find_solution_dfs(Node *root)
{
    std::stack<Node *> open_st;
    std::stack<Node *> close_st;

    bool close_arr[COUNT_MONK + 1][COUNT_DEVIL + 1][2] = {{{}}};

    open_st.push(root);

    while (!open_st.empty())
    {
        Node *cur_node = open_st.top();
        close_arr[cur_node->state.monk][cur_node->state.devil][cur_node->state.board_pos] = true;
        open_st.pop();
        close_st.push(cur_node);

        if (is_goal(cur_node->state))
        {
            return cur_node;
        }

        for (int i = 1; i <= COUNT_ACTIONS; i++)
        {
            State next_st = create_state();

            if (call_action(cur_node->state, next_st, i))
            {
                if (close_arr[next_st.monk][next_st.devil][next_st.board_pos])
                {
                    continue;
                }

                Node *next_node = create_node(next_st, cur_node);
                open_st.push(next_node);
            }
        }
    }

    return NULL;
}

void print_state(State state)
{
    for (int i = 0; i < state.monk; i++)
    {
        std::cout << "0";
    }

    for (int i = 0; i < state.devil; i++)
    {
        std::cout << "1";
    }

    for (int i = 0; i < COUNT_MONK + COUNT_DEVIL - state.monk - state.devil; i++)
    {
        std::cout << " ";
    }

    if (state.board_pos)
    {
        std::cout << "          __";
    }
    else
    {
        std::cout << "__          ";
    }

    for (int i = 0; i < state.monk + state.devil; i++)
    {
        std::cout << " ";
    }

    for (int i = 0; i < COUNT_DEVIL - state.devil; i++)
    {
        std::cout << "1";
    }

    for (int i = 0; i < COUNT_MONK - state.monk; i++)
    {
        std::cout << "0";
    }

    std::cout << std::endl;
}

void print_nodes(Node *goal)
{
    if (!goal)
    {
        return;
    }

    print_nodes(goal->parent);
    print_state(goal->state);
}

int main()
{
    Node *root = create_node();
    Node *goal = find_solution_dfs(root);

    print_nodes(goal);
    return 0;
}
