#include <iostream>
#include <stack>

#define COUNT_GLASS 6
#define STEPS 3

typedef struct
{
    int glass[COUNT_GLASS];
} State;

typedef struct Node
{
    State state;
    struct Node *parent;
    int action;
} Node;

State create_state()
{
    State state;
    for (int i = 0; i < COUNT_GLASS; i++)
    {
        state.glass[i] = i % 2;
    }
    return state;
}

Node *create_node(Node *parent = NULL, State state = create_state(), int action = 0)
{
    Node *node = (Node *)malloc(sizeof(Node));
    *node = {state, parent, action};
    return node;
}

bool is_goal(State state)
{
    for (auto g : state.glass)
    {
        if (!g)
        {
            return false;
        }
    }
    return true;
}

State flip(State current_state, int start_index)
{
    start_index = std::min(start_index, start_index);
    int end_index = start_index + STEPS - 1;
    for (; start_index < end_index; start_index++)
    {
        current_state.glass[start_index] = !current_state.glass[start_index];
    }
    return current_state;
}

bool is_equals_state(const State &st1, const State &st2)
{
    for (int i = 0; i < COUNT_GLASS; i++)
    {
        if (st1.glass[i] != st2.glass[i])
        {
            return false;
        }
    }
    return true;
}

bool is_existing_state(std::stack<Node *> &st, const State &state)
{
    std::stack<Node *> temp;
    bool __return = false;
    while (!st.empty())
    {
        Node *node = st.top();
        st.pop();
        temp.push(node);
        if (is_equals_state(node->state, state))
        {
            __return = true;
        }
    }
    while (!temp.empty())
    {
        st.push(temp.top());
        temp.pop();
    }

    return __return;
}

Node *find_goal_dfs(Node *node)
{
    std::stack<Node *> open_st;
    std::stack<Node *> closed_st;

    open_st.push(node);

    while (!open_st.empty())
    {
        Node *current_node = open_st.top();
        open_st.pop();
        closed_st.push(current_node);

        if (is_goal(current_node->state))
        {
            return current_node;
        }

        for (int i = 0; i < COUNT_GLASS; i++)
        {
            State next_state = flip(current_node->state, i);
            if (is_existing_state(closed_st, next_state))
            {
                continue;
            }
            Node *next_node = create_node(current_node, next_state, i + 1);
            next_node->parent = current_node;
            open_st.push(next_node);
        }
    }

    return NULL;
}

void print_nodes(Node *goal)
{
    if (goal == NULL)
    {
        return;
    }

    print_nodes(goal->parent);
    std::cout << "Lat ly thu " << goal->action << std::endl;
    for (int i = 0; i < COUNT_GLASS; i++)
    {
        std::cout << goal->state.glass[i] << " ";
    }
    std::cout << std::endl;
}

int main()
{
    Node *node = create_node();
    Node *goal = find_goal_dfs(node);
    print_nodes(goal);
    return 0;
}
